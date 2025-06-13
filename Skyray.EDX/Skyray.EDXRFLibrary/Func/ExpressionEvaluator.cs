using System;
using System.Collections.Generic;
using System.Linq;

public enum TokenType
{
    Number,
    Operator,
    LeftParenthesis,
    RightParenthesis
}


namespace Skyray.EDXRFLibrary
{

    public class Token
    {
        public TokenType Type { get; set; }
        public string Value { get; set; }

        public Token(TokenType type, string value)
        {
            Type = type;
            Value = value;
        }
    }

    public class ExpressionEvaluator
    {
        public static double Evaluate(string expression)
        {
            var tokens = Tokenize(expression);
            var rpn = ConvertToRPN(tokens);
            return EvaluateRPN(rpn);
        }

        private static List<Token> Tokenize(string input)
        {
            List<Token> tokens = new List<Token>();
            int i = 0;
            while (i < input.Length)
            {
                if (char.IsWhiteSpace(input[i]))
                {
                    i++;
                    continue;
                }

                if (char.IsDigit(input[i]) || input[i] == '.')
                {
                    int start = i;
                    bool hasDot = false;
                    while (i < input.Length && (char.IsDigit(input[i]) || input[i] == '.'))
                    {
                        if (input[i] == '.')
                        {
                            if (hasDot) throw new FormatException("Invalid number format.");
                            hasDot = true;
                        }
                        i++;
                    }
                    string numStr = input.Substring(start, i - start);
                    if (numStr.Length == 0 || numStr.EndsWith("."))
                        throw new FormatException("Invalid number format.");
                    tokens.Add(new Token(TokenType.Number, numStr));
                }
                else if ("+-*/".Contains(input[i]))
                {
                    string op = input[i].ToString();
                    if (input[i] == '-')
                    {
                        bool isUnary = tokens.Count == 0 ||
                                       tokens.Last().Type == TokenType.Operator ||
                                       tokens.Last().Type == TokenType.LeftParenthesis;
                        if (isUnary) op = "u-";
                    }
                    tokens.Add(new Token(TokenType.Operator, op));
                    i++;
                }
                else if (input[i] == '(')
                {
                    tokens.Add(new Token(TokenType.LeftParenthesis, "("));
                    i++;
                }
                else if (input[i] == ')')
                {
                    tokens.Add(new Token(TokenType.RightParenthesis, ")"));
                    i++;
                }
                else
                {
                    //throw new FormatException($"Invalid character: '{input[i]}'");
                }
            }
            return tokens;
        }

        private static List<Token> ConvertToRPN(List<Token> tokens)
        {
            var precedence = new Dictionary<string, int> { { "u-", 4 }, { "*", 3 }, { "/", 3 }, { "+", 2 }, { "-", 2 } };
            Stack<string> stack = new Stack<string>();
            List<Token> output = new List<Token>();

            foreach (var token in tokens)
            {
                if (token.Type == TokenType.Number)
                {
                    output.Add(token);
                }
                else if (token.Value == "(")
                {
                    stack.Push(token.Value);
                }
                else if (token.Value == ")")
                {
                    while (stack.Peek() != "(")
                    {
                        output.Add(new Token(TokenType.Operator, stack.Pop()));
                        if (stack.Count == 0) throw new ArgumentException("Mismatched parentheses");
                    }
                    stack.Pop();
                }
                else if (token.Type == TokenType.Operator)
                {
                    string currentOp = token.Value;
                    while (stack.Count > 0 && stack.Peek() != "(" &&
                           precedence[currentOp] <= precedence[stack.Peek()])
                    {
                        output.Add(new Token(TokenType.Operator, stack.Pop()));
                    }
                    stack.Push(currentOp);
                }
            }

            while (stack.Count > 0)
            {
                string op = stack.Pop();
                if (op == "(") throw new ArgumentException("Mismatched parentheses");
                output.Add(new Token(TokenType.Operator, op));
            }

            return output;
        }

        private static double EvaluateRPN(List<Token> rpn)
        {
            Stack<double> stack = new Stack<double>();
            double num = 0;
            foreach (var token in rpn)
            {
                if (token.Type == TokenType.Number)
                {

                    if (!double.TryParse(token.Value, out num))

                        throw new FormatException("Invalid number: {token.Value}");
                    // throw new FormatException($"Invalid number: {token.Value}");
                    stack.Push(num);
                }
                else
                {
                    string op = token.Value;
                    if (op == "u-")
                    {
                        if (stack.Count < 1) throw new InvalidOperationException("Invalid expression");
                        stack.Push(-stack.Pop());
                    }
                    else
                    {
                        if (stack.Count < 2) throw new InvalidOperationException("Invalid expression");
                        double b = stack.Pop(), a = stack.Pop();
                        switch (op)
                        {
                            case "+": stack.Push(a + b); break;
                            case "-": stack.Push(a - b); break;
                            case "*": stack.Push(a * b); break;
                            case "/":
                                if (b == 0) throw new DivideByZeroException();
                                stack.Push(a / b);
                                break;
                        }
                    }
                }
            }

            if (stack.Count != 1) throw new InvalidOperationException("Invalid expression");
            return stack.Pop();
        }
    }
}