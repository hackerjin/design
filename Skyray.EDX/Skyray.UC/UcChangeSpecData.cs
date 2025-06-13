using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Skyray.EDX.Common;
using Skyray.Language;
using Skyray.EDXRFLibrary;

namespace Skyray.UC
{
    /// <summary>
    /// 计算强度类
    /// </summary>
    public partial class UcChangeSpecData : Skyray.Language.UCMultiple
    {
        /// <summary>
        /// 计算强度
        /// </summary>
        public UcChangeSpecData()
        {
            InitializeComponent();

            string adjustParam = ReportTemplateHelper.LoadSpecifiedParamsValue(AppDomain.CurrentDomain.BaseDirectory + "AppParams.xml", "application/fineGainAdjustParam");

            float K = float.Parse(adjustParam.Split(new char[] { ',' })[0]);
            float B = float.Parse(adjustParam.Split(new char[] { ',' })[1]);
            float C = float.Parse(adjustParam.Split(new char[] { ',' })[2]);

            this.cuFormula.Text = "y=" + K.ToString() + "*x*x" + (B >= 0 ? "+" : "") + B.ToString() + "*x" + (C >= 0 ? "+" : "") + C.ToString();

            this.isAdjustSpecData.Checked = WorkCurveHelper.isAdjustSpecData;
        }


        public bool CalculateCurve(PointF[] Points, int dim, bool izero, ref  double[] x)
        {
            double[] transX = new double[x.Length];
            if (izero)
            {
                double[,] A = new double[Points.Length, dim];
                double[] B = new double[Points.Length];
                int intValid = 0;
                for (int i = 0; i < Points.Length; i++)
                {
                    for (int j = 0; j < dim; j++)
                    {
                        A[intValid, j] = Math.Pow(Points[i].X, j + 1);
                    }
                    B[intValid] = Points[i].Y;
                    intValid++;
                }
                if (intValid < dim)
                {
                    return false;
                }
                MatrixFun.MatrixEquation(Points.Length, dim, A, B, transX);
                for (int i = 0; i < x.Length; i++)
                {
                    x[i] = transX[i];
                }
            }
            else
            {
                double[,] A = new double[Points.Length, dim + 1];
                double[] B = new double[Points.Length];
                int intValid = 0;
                for (int i = 0; i < Points.Length; i++)
                {
                    A[intValid, 0] = 1;
                    for (int j = 0; j < dim; j++)
                        A[intValid, j + 1] = Math.Pow(Points[i].X, j + 1);
                    B[intValid] = Points[i].Y;
                    intValid++;
                }
                if (intValid < dim + 1)
                {
                    return false;
                }
                MatrixFun.MatrixEquation(Points.Length, dim + 1, A, B, transX);
                for (int i = 0; i < x.Length; i++)
                {
                    x[i] = transX[transX.Length - i - 1];
                }
            }

            return true;
        }


        private void btWSubmit_Click(object sender, EventArgs e)
        {
            string[] datas = this.cuTestData.Text.Trim().Split(new char[]{'\n'});
            PointF[] points = new PointF[datas.Length +1];

            if (datas.Length < 2)
            {
                Msg.Show("当前数据不足以生成公式");
                return;
            }
            else
            {
                for (int i = 0; i < datas.Length; i++)
                {

                    points[i].X = float.Parse(datas[i].Split(new char[] { ' ' })[0]) / (float)this.cuInitCountRate.Value;
                    points[i].Y = float.Parse(datas[i].Split(new char[] { ' ' })[1]) / (float)this.cuInitPeakChan.Value;

                }
            }

            points[datas.Length].X = 1f;
            points[datas.Length].Y = 1f;

            double[] coeff = new double[] { 0, 0, 0 };
            CalculateCurve(points, 2, false, ref coeff);

            string adjustParam = ((float)coeff[0]).ToString() + "," + ((float)coeff[1]).ToString() + "," + ((float)coeff[2]).ToString(); 
           
            this.cuFormula.Text = "y=" + ((float)coeff[0]).ToString() + "*x*x" + (coeff[1] >= 0 ? "+" : "") + ((float)coeff[1]).ToString() + "*x" + (coeff[2] >= 0 ? "+" : "") + ((float)coeff[2]).ToString();


            WorkCurveHelper.fineGainAdjustParam = new RectangleF((float)coeff[0], (float)coeff[1], (float)coeff[2], 0);
            WorkCurveHelper.initCountRate = (float)this.cuInitCountRate.Value;

            ReportTemplateHelper.SaveSpecifiedParamsValue(AppDomain.CurrentDomain.BaseDirectory + "AppParams.xml", "application/fineGainAdjustParam", adjustParam);
            ReportTemplateHelper.SaveSpecifiedParamsValue(AppDomain.CurrentDomain.BaseDirectory + "AppParams.xml", "application/initCountRate", WorkCurveHelper.initCountRate.ToString());


        }

        private void isAdjustSpecData_CheckedChanged(object sender, EventArgs e)
        {
            WorkCurveHelper.isAdjustSpecData = this.isAdjustSpecData.Checked;
            ReportTemplateHelper.SaveSpecifiedParamsValue(AppDomain.CurrentDomain.BaseDirectory + "AppParams.xml", "application/isAdjustSpecData", WorkCurveHelper.isAdjustSpecData.ToString());

        }
       
    }
}
