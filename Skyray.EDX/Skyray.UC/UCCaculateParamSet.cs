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
    public partial class UCCaculateParamSet : UCMultiple
    {
      
        public UCCaculateParamSet()
        {
            InitializeComponent();

            //numAvalue.Value = (decimal)WorkCurveHelper.NiCuNiParam.aValue;
            //numNvalue.Value = (decimal)WorkCurveHelper.NiCuNiParam.nValue;
            //numkvalue.Value = (decimal)WorkCurveHelper.NiCuNiParam.kValue;
            //numbvalue.Value = (decimal)WorkCurveHelper.NiCuNiParam.bValue;
            //numlimitvalue.Value = (decimal)WorkCurveHelper.NiCuNiParam.limit;
            dbInputlimit.Text = WorkCurveHelper.NiCuNiCustomParam.Limit.ToString();
            txtCustomFiled1.Text = WorkCurveHelper.NiCuNiCustomParam.CustomFiled1;
            txtCustomFiled2.Text = WorkCurveHelper.NiCuNiCustomParam.CustomFiled2;
            dbOptValue.Text = WorkCurveHelper.NiCuNiCustomParam.OptValue.ToString();

        }

        private void btWCancel_Click(object sender, EventArgs e)
        {
            EDXRFHelper.GotoMainPage(this);
        }

        private void btWSubmit_Click(object sender, EventArgs e)
        {
            //WorkCurveHelper.NiCuNiParam.aValue = (double)numAvalue.Value;
            //WorkCurveHelper.NiCuNiParam.nValue = (double)numNvalue.Value;
            //WorkCurveHelper.NiCuNiParam.kValue = (double)numkvalue.Value;
            //WorkCurveHelper.NiCuNiParam.bValue = (double)numbvalue.Value;
            //WorkCurveHelper.NiCuNiParam.limit = (double)numlimitvalue.Value;
            //ReportTemplateHelper.SaveAttribute("DataParam/NiFormulaParam", "aValue", WorkCurveHelper.NiCuNiParam.aValue.ToString());
            //ReportTemplateHelper.SaveAttribute("DataParam/NiFormulaParam", "nValue", WorkCurveHelper.NiCuNiParam.nValue.ToString());
            //ReportTemplateHelper.SaveAttribute("DataParam/NiFormulaParam", "kValue", WorkCurveHelper.NiCuNiParam.kValue.ToString());
            //ReportTemplateHelper.SaveAttribute("DataParam/NiFormulaParam", "bValue", WorkCurveHelper.NiCuNiParam.bValue.ToString());
            //ReportTemplateHelper.SaveAttribute("DataParam/NiFormulaParam", "limit", WorkCurveHelper.NiCuNiParam.limit.ToString());
            double dbvalue =0;
            double dboptvalue = 0; 
            double.TryParse(dbInputlimit.Text,out  dbvalue);
            WorkCurveHelper.NiCuNiCustomParam.Limit = dbvalue > 0 ? dbvalue : 0.5;
            double.TryParse(dbOptValue.Text, out  dboptvalue); 
            WorkCurveHelper.NiCuNiCustomParam.OptValue = dboptvalue > 0 ? dboptvalue : 1;
            WorkCurveHelper.NiCuNiCustomParam.CustomFiled1 = txtCustomFiled1.Text.ToLower();
            WorkCurveHelper.NiCuNiCustomParam.CustomFiled2 = txtCustomFiled2.Text.ToLower();
            ReportTemplateHelper.SaveAttribute("DataParam/NiCustomFiled", "Limit", WorkCurveHelper.NiCuNiCustomParam.Limit.ToString());
            ReportTemplateHelper.SaveAttribute("DataParam/NiCustomFiled", "OptValue", WorkCurveHelper.NiCuNiCustomParam.OptValue.ToString());
            ReportTemplateHelper.SaveAttribute("DataParam/NiCustomFiled", "CustomFiled1", WorkCurveHelper.NiCuNiCustomParam.CustomFiled1.ToString());
            ReportTemplateHelper.SaveAttribute("DataParam/NiCustomFiled", "CustomFiled2", WorkCurveHelper.NiCuNiCustomParam.CustomFiled2.ToString());
            EDXRFHelper.GotoMainPage(this);
        }

       



      
    }
}
