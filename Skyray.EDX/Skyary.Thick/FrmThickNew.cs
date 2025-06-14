﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Skyray.EDX.Common;
using Skyray.Controls;
using Skyray.UC;
using Skyray.EDXRFLibrary;
using Skyray.EDX.Common.Component;
using Skyray.Print;
using Skyray.Language;
using Skyray.Camera;
using Skyray.EDX.Common.UIHelper;
using Skyray.EDX.Common.ReportHelper;
using System.Xml;
using System.Runtime.InteropServices;
using Skyray.API;
using Skyray.Dog;
using System.IO;
using Lephone.Data.Common;
using AForge.Controls;


namespace Skyray.Thick
{
    public partial class FrmThickNew : MultipleForm, IRefreshFillInfo
    {
        private MediumAccess access = new MediumAccess();
        private DeviceMeasure deviceMeasure = new DeviceMeasure();
        private Timer timer;
        private List<DataTable> lstDataTable = new List<DataTable>();
        private List<DataTable> lstStatics = new List<DataTable>();
        private List<object> listCu = new List<object>();
        private List<object> lstResulte = new List<object>();
        private ToolStripW currentStripW;
        private MenuStripW menuStripW1;
        private Image image;
        SkyrayCamera cameral;
        private string oriFormText = string.Empty;
        /// <summary>
        /// 工作曲线
        /// </summary>
        private DbObjectList<WorkCurve> lstWorkCurve;


        private FrmLoading FrmLoad = new FrmLoading();
        public FrmThickNew()
        {
            InitializeComponent();
            //System.Diagnostics.Stopwatch sw = new System.Diagnostics.Stopwatch();
            //sw.Start();
            FrmLoad.ShowInformation = "Loading...";
            FrmLoad.Show();
            DifferenceDevice.interClassMain.handle = this.Handle;
            DifferenceDevice.interClassMain.deviceMeasure.interfacce.OwnerHandle = this.Handle;
            DifferenceDevice.interClassMain.XrfChart = this.xrfChart1;

            DifferenceDevice.interClassMain.uc = DifferenceDevice.uc;
            LoadInfo(false);
            HardwareDog.RefreshInfos += new HardwareDog.RefreshMainText(HardwareDog_RefreshInfos);
            DifferenceDevice.interClassMain.ActionBeforeConnectStart = () =>
            {
                DifferenceDevice.interClassMain.SetNavEnabled(this, new List<string>() { "ConnectDevice", "Device" }, false);
            };
            Port.ActionAfterDeviceInfoNotGot = () =>
            {
                DifferenceDevice.interClassMain.DoAfterDevInfoNotGot(this);
            };
            Port.ActionAfterDeviceInfoChecked = () =>
            {
                DifferenceDevice.interClassMain.SetNavEnabled(this, new List<string>() { "ConnectDevice", "Device" }, true);
            };
            Port.ActionReconnect = () =>
            {
                WorkCurveHelper.SafeCall(this, () =>
                {
                    DifferenceDevice.interClassMain.ConnectDevice();
                });
            };
            //DifferenceDevice.interClassMain.ConnectDevice();

            // RefreshWholeData();
            DifferenceDevice.interClassMain.progressInfo.ToolStripStatusLabelMeasureTime = this.tslabelMeasureTime;
            DifferenceDevice.interClassMain.progressInfo.ToolStripStatusLabelSurplusTime = this.tsLabelSuplusTime;
            DifferenceDevice.interClassMain.progressInfo.ToolStripProgressBar = this.tsTimeProcessBar;
            timer = new System.Windows.Forms.Timer();
            timer.Enabled = false;
            if (WorkCurveHelper.DeviceCurrent.ComType == ComType.FPGA)
                timer.Interval = 500;
            else
                timer.Interval = 100;
            image = Properties.Resources.xsimple_009_green;
            timer.Tick += new EventHandler(timer_Tick);//定时器事件
            this.tabControlInfo.SelectedTab = this.tabPageDevice;
            DifferenceDevice.interClassMain.MainForm = this;
            cameral = DifferenceDevice.interClassMain.FindCameralUserControl(containerObject1);
            if (cameral != null)
            {
                cameral.IsCameralFlip = WorkCurveHelper.IsOpenRegister;    //yuzhao20150611_由于在dmoflip出现在某些电脑中无法使用的问题，故该功能还原为可设置
                //cameral.IsCameralFlip = true;                            //yuzhao20150611_由于在dmoflip出现在某些电脑中无法使用的问题，故该功能还原为可设置
                // cameral.Open();

            }

            string sql = "select * from WorkCurve as a join Condition as b on a.Condition_Id = b.Id join Device as d on d.Id=b.Device_Id where d.Id =" + WorkCurveHelper.DeviceCurrent.Id + " and a.IsDefaultWorkCurve = 1";
            WorkCurve current = WorkCurve.FindBySql(sql).Count == 0 ? null : WorkCurve.FindBySql(sql)[0];
            if (current != null && current.ElementList != null)
            {//20131217
                if (WorkCurveHelper.CalcType == CalcType.PeakDivBase)
                    foreach (var a in current.ElementList.Items)
                    {
                        a.IsShowContent = false;
                    }
                WorkCurveHelper.WorkCurveCurrent = current;

                
                DifferenceDevice.MediumAccess.OpenCurveSubmit();
            }

            HistoryRecord lastRecord = HistoryRecord.FindRecent(1)[0];
            NetPortImplement.lastId = lastRecord.Id;
           
            WorkCurveHelper.ucHistoryRecord1 = this.ucHistoryRecord1;

           
            EDXRFHelper.DisplayWorkCurveControls();
            DifferenceDevice.interClassMain.GetSpecGraphicObject(null);
            EDXRFHelper.OnLoadDataSource += new EDXRFHelper.LoadDataSource(EDXRFHelper_OnLoadDataSource);
            Skyray.Language.Lang.Model.LanguageChanged += new EventHandler(Model_LanguageChanged);
            DifferenceDevice.uc.OnPrintTemplateSource += new EventDelegate.PrintTemplateSource(uc_OnPrintTemplateSource);
            oriFormText = this.Text;

            WorkCurveHelper.ucCameraControl1 = this.ucCameraControl1;



            if (WorkCurveHelper.DeviceCurrent.HasMotorSpin && WorkCurveHelper.DeviceCurrent.MotorSpinDirect == 1)
            {
                WorkCurveHelper.Y1Coeff = WorkCurveHelper.YCoeff;
            }
            //平台行程参数在运行过程中可以在用户界面进行更改
            WorkCurveHelper.TabWidth = WorkCurveHelper.DeviceCurrent.MotorXMaxStep == 0 ? 1 : WorkCurveHelper.DeviceCurrent.MotorXMaxStep;
            WorkCurveHelper.TabHeight = WorkCurveHelper.DeviceCurrent.MotorYMaxStep == 0 ? 1 : WorkCurveHelper.DeviceCurrent.MotorYMaxStep;
            
            //以下位置参数在平台运动过程中会变化，此处进行一次初始化
            WorkCurveHelper.X = WorkCurveHelper.ResetX;
            WorkCurveHelper.Y = WorkCurveHelper.ResetY;
            WorkCurveHelper.Z = WorkCurveHelper.ResetZ;

            WorkCurveHelper.largeViewX = WorkCurveHelper.ResetX;
            WorkCurveHelper.largeViewY = WorkCurveHelper.ResetY;


            WorkCurveHelper.LargeViewDis = WorkCurveHelper.InOutDis - WorkCurveHelper.TwoCameraDis;

            //当机器没有Y1轴时，其也可能被错误配置为有，则在发出移动指令后有可能出错
            if (!WorkCurveHelper.DeviceCurrent.HasMotorSpin)
            {
                WorkCurveHelper.TestDis = 0;
                ReportTemplateHelper.SaveSpecifiedParamsValue(AppDomain.CurrentDomain.BaseDirectory + "AppParams.xml", "application/TestDis", WorkCurveHelper.TestDis.ToString());
            }
            else
                WorkCurveHelper.TestDis = float.Parse(ReportTemplateHelper.LoadSpecifiedParamsValue(AppDomain.CurrentDomain.BaseDirectory + "AppParams.xml", "application/TestDis"));

          

            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;

            WorkCurveHelper.dataStore = ModbusTcp.slave.DataStore;

            //new System.Threading.Thread(new System.Threading.ThreadStart(ModbusTcp.Main)).Start();

            WorkCurveHelper.curFrmThick = this;
            ReportTemplateHelper.SaveSpecifiedParamsValue(AppDomain.CurrentDomain.BaseDirectory + "AppParams.xml", "application/ChangeUser", false.ToString());


            new System.Threading.Thread(new System.Threading.ThreadStart(() =>
            {
                try
                {
                    bool bFindHardDog = HardwareDog.CheckHardwareDog(WorkCurveHelper.snFilePath, true, this);
                    if (!bFindHardDog)
                    {
                        WorkCurveHelper.SafeCall(this, () =>
                        {
                            string text = this.Text;
                            MotorInstance.CheckDog(ref text);
                            this.Text = text;
                        });
                    }

                    WorkCurveHelper.SafeCall(this, () =>
                    {
                        DifferenceDevice.interClassMain.ConnectDevice();
                        cameral.Open();
                        AutoBackupHelper.sVersion = "Thick";
                        AutoBackupHelper.StartProbeProcess();
                        WorkCurveHelper.Ewh.Set();
                        timer.Enabled = true;

                    });
                }
                catch (Exception)
                {
                }

            })) { IsBackground = true }.Start();


            //if (WorkCurveHelper.DeviceCurrent.HasMotorX && WorkCurveHelper.DeviceCurrent.HasMotorY && WorkCurveHelper.DeviceCurrent.HasMotorZ && DifferenceDevice.interClassMain.deviceMeasure.interfacce.port.ConnectState)
            //{
            //    ucCameraControl1.MotorReset();
            //}


            ////CheckHardwareDog();
            //WinMethod.SendMessage(DifferenceDevice.interClassMain.deviceMeasure.interfacce.OwnerHandle, DeviceInterface.CUSTOM_MESSAGE_HIDE, 0, 0);

            dgvMeasure.ColumnHeadersDefaultCellStyle.Font = new System.Drawing.Font("Tahoma", 12, FontStyle.Bold);
            dgvMeasure.DefaultCellStyle.Font = new System.Drawing.Font("Tahoma", 12);
            dgvMeasure.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;


            WorkCurveHelper.ucHistoryRecord1 = this.ucHistoryRecord1;
            //sw.Stop();
            //string showtime1 = sw.Elapsed.TotalMilliseconds.ToString();
            //Console.WriteLine("主界面占用时间：{0}ms", showtime1);
        }



        void HardwareDog_RefreshInfos(string text)
        {
            WorkCurveHelper.SafeCall(this, () => { this.Text = oriFormText + "--" + text; });
        }

        //private System.Windows.Forms.Timer timerHardwareDog;
        //public void CheckHardwareDog()
        //{
        //    bool isInSevenDays = false;
        //    string surPlus = string.Empty;
        //    int type = (int)HardwareDog.SNConfirm(WorkCurveHelper.snFilePath, out isInSevenDays, out surPlus);
        //    switch (type)
        //    {
        //        case -3:
        //        case -2:
        //            string text = this.Text;
        //            MotorInstance.CheckDog(ref text);
        //            this.Text = text;
        //            break;
        //        case -1:
        //            //this.Text = HardwareDog.Deadline;
        //            break;
        //        case 0:
        //            //if (HardwareDog.Sevendays != null && HardwareDog.Sevendays != string.Empty)
        //            //{
        //            //    this.Text = HardwareDog.Sevendays;
        //            //}
        //            if (isInSevenDays)
        //            {
        //                if (!surPlus.Equals(string.Empty) || surPlus != "")
        //                {
        //                    this.Text = surPlus;
        //                }
        //                timerHardwareDog = new System.Windows.Forms.Timer();
        //                timerHardwareDog.Enabled = true;
        //                timerHardwareDog.Interval = 12 * 60 * 60 * 1000;
        //                timerHardwareDog.Tick += new EventHandler(timerHardwareDog_Tick);
        //            }
        //            break;
        //        case 1:
        //            FrmHardwareDogCA fhd = new FrmHardwareDogCA(type);
        //            fhd.ShowDialog();
        //            break;


        //    }


        //}
        ///// <summary>
        ///// 刷新界面，仅仅为了显示，跟硬件加密狗内时钟无关。
        ///// </summary>
        ///// <param name="source"></param>
        ///// <param name="e"></param>
        //private void timerHardwareDog_Tick(object source, EventArgs e)
        //{
        //    bool isInSevenDays = false;
        //    string surPlus = string.Empty;
        //    int type = (int)HardwareDog.SNConfirm(WorkCurveHelper.snFilePath, out isInSevenDays, out surPlus);
        //    if (type == 0)
        //    {
        //        //if (HardwareDog.Sevendays != null && HardwareDog.Sevendays != string.Empty)
        //        //{
        //        //    this.Text = HardwareDog.Sevendays;
        //        //}
        //        if (!surPlus.Equals(string.Empty) || surPlus != "")
        //        {
        //            this.Text = surPlus;
        //        }
        //    }
        //    else if (type == 1)
        //    {
        //        this.Text = HardwareDog.Deadline;
        //        timerHardwareDog.Enabled = false;
        //    }
        //}




        public void updateRetestRecord(long newId)
        {

            if (DifferenceDevice.CurCameraControl.ChkRetest.Checked)
            {

                long deleteId = WorkCurveHelper.testIds[this.retestIndex - 1];

                //将被复测记录删除
                Lephone.Data.SqlEntry.SqlStatement sqlstate = new Lephone.Data.SqlEntry.SqlStatement("delete from HistoryCompanyOtherInfo where History_Id=" + deleteId.ToString() + ";delete from HistoryRecord where Id=" + deleteId.ToString() + " ;delete from HistoryElement where HistoryRecord_Id=" + deleteId.ToString());
                Lephone.Data.DbEntry.Context.ExecuteNonQuery(sqlstate);

                //将新记录的id改为被删除记录的id
                sqlstate = new Lephone.Data.SqlEntry.SqlStatement("update HistoryCompanyOtherInfo  set History_Id = " + deleteId.ToString() + " where History_Id=" + newId.ToString() + ";update HistoryRecord set Id = " + deleteId.ToString() + " where Id=" + newId.ToString() + " ;update  HistoryElement set HistoryRecord_Id= " + deleteId.ToString() + " where HistoryRecord_Id=" + newId.ToString());
                Lephone.Data.DbEntry.Context.ExecuteNonQuery(sqlstate);
            }

        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {

            if (DifferenceDevice.interClassMain.deviceMeasure.interfacce.State != DeviceState.Idel)
                return false;



            if (keyData == Keys.Space)
            {
                if (DifferenceDevice.CurCameraControl.ChkRetest.Checked)
                {
                    if (this.retestIndex >= 1 && this.retestIndex <= this.dgvMeasure.Rows.Count)
                    {


                        DifferenceDevice.interClassMain.deviceMeasure.interfacce.TestButtonPressed = true;
                        DifferenceDevice.interClassMain.DoTestOnButtonPressed();
                    }
                    else
                    {
                        Msg.Show("请先选择复测点！");
                        return false;
                    }
                }
                else
                {
                    if (DifferenceDevice.CurCameraControl.skyrayCamera1.alTempTestPoints.Count > 0)
                    {
                        if (DifferenceDevice.CurCameraControl.skyrayCamera1.ContiTestPoints.Count == 0)
                        {
                            DifferenceDevice.CurCameraControl.skyrayCamera1.ContiTestPoints = (System.Collections.ArrayList)DifferenceDevice.CurCameraControl.skyrayCamera1.alTempTestPoints.Clone();

                            if (WorkCurveHelper.testParamsBackup != null)
                            {
                                DifferenceDevice.interClassMain.bIsCameraStartTest = true;
                                WorkCurveHelper.testNum = DifferenceDevice.CurCameraControl.skyrayCamera1.ContiTestPoints.Count;
                                WorkCurveHelper.curDeviceNum = 0;
                                WorkCurveHelper.dataStore.InputDiscretes[2] = true;
                                WorkCurveHelper.contiOffsetInTemp = 0;
                                WorkCurveHelper.testTimes = WorkCurveHelper.testNum * WorkCurveHelper.testParamsBackup.MeasureParams.MeasureNumber;
                                ((Skyray.UC.Thick)WorkCurveHelper.curThick).newSpec_OnExcuteTestBackGroudWorker1(WorkCurveHelper.testParamsBackup);

                            }

                        }
                    }
                    else
                    {
                        DifferenceDevice.interClassMain.deviceMeasure.interfacce.TestButtonPressed = true;
                        DifferenceDevice.interClassMain.DoTestOnButtonPressed();

                    }
                }



                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }
        


        private int backupDis = 0;
        public void showHide(bool flag)
        {

            if (flag)
            {
                this.splitContainer4.SplitterDistance = 700;
                this.splitContainer1.SplitterDistance = backupDis;
                

            }
            else
            {
            
                this.splitContainer4.SplitterDistance = this.splitContainer4.Height;
                backupDis = this.splitContainer1.SplitterDistance== this.splitContainer1.Width ? this.splitContainer1.Width-500 :this.splitContainer1.SplitterDistance;
                this.splitContainer1.SplitterDistance = this.splitContainer1.Width;
          
              
            }

        }

        private void LoadInfo(bool flag)
        {
            WorkCurveHelper.NaviItems.Clear();
            MenuLoadHelper.MenuStripCollection.Clear();
            menuStripW1 = null;
            ToolStripW ts = new ToolStripW();
            MenuStripW ms = new MenuStripW();
            foreach (var ctrl in this.Controls)
            {
                if (ctrl.GetType() == typeof(ToolStripW))
                {
                    ts = (ToolStripW)ctrl;
                    ts.Name = "logout";
                }
                if (ctrl.GetType() == typeof(MenuStripW))
                {
                    ms = (MenuStripW)ctrl;
                    ms.Name = "logout";
                }
            }
            if (ts != null && ts.Name == "logout")
                this.Controls.Remove(ts);
            if (ms != null && ms.Name == "logout")
                this.Controls.Remove(ms);
            DifferenceDevice.interClassMain.refreshFillinof = this;
            DifferenceDevice.uc.LoadControls(true);
            DifferenceDevice.interClassMain.LoadToolsConfig();
            currentStripW = WorkCurveHelper.GetToolStripW(this.Width).ToArray()[0];
            currentStripW.ImageScalingSize = new Size(LanguageModel.imageSize, LanguageModel.imageSize);
            this.Controls.Add(currentStripW);
            menuStripW1 = MenuLoadHelper.GetMainFormMenuStrip();
            menuStripW1.Font = LanguageModel.newFont;
            this.Controls.Add(menuStripW1);
            currentStripW.SetStyle(Style.Office2007Blue);
            menuStripW1.SetStyle(Style.Office2007Blue);
            if (flag)
            {
                this.FrmThick_Shown(null, null);
            }

        }

        bool EDXRFHelper_OnLoadDataSource()
        {
            return LoadDataPrintTemplate();
        }

        private void Model_LanguageChanged(object sender, EventArgs e)
        {
            RefreshWholeData();
            //主菜单
            //string[] names = new string[] {  Info.Settings, Info.Condition,Info.Workgion, Info.Curve, Info.Spec, Info.Quality, 
            //                                Info.Report,Info.UserManage ,Info.Tools, Info.Language, Info.Helper};
            string[] names = new string[] { Info.Settings, Info.Condition,Info.Workgion, Info.Curve, Info.Spec, Info.Quality, 
                                            Info.Report,Info.UserManage ,Info.Tools, Info.Language,Info.Camera, Info.Helper,Info.Others,Info.Exit,Info.ChangeUser };

            for (int i = 0; i < names.Length; i++)
            {
                menuStripW1.Items[i].Text = names[i];
            }
            var naviteim = WorkCurveHelper.NaviItems.Find(x => x.Name == "cboMode");//查找模式控件
            if (naviteim != null)//非空
            {
                naviteim.ComboStrip.Items[0] = Info.Normal;//正常模式
                naviteim.ComboStrip.Items[1] = Info.Intelligent;//智能模式 
            }
            LangHelper.ChangeCameraLang();
        }

        public void RefreshMeasureDialog()
        {
        }

        private bool LoadDataPrintTemplate()
        {
            if (DifferenceDevice.interClassMain.specList == null || DifferenceDevice.interClassMain.specList.Specs.Length == 0)
                return false;
            if (!EDXRFHelper.LoadTemplate(DirectPrintLibcs.lst, WorkCurveHelper.WorkCurveCurrent, DifferenceDevice.interClassMain.specList))
                return false;
            DataTable dt = WorkCurveHelper.DGVToDataTable(this.dgvMeasure);
            if (dt == null || dt.Rows.Count == 0 || dt.Columns.Count == 0)
                return false;
            TreeNodeInfo info;
            info = DirectPrintLibcs.lst.Find(w => w.Name == "TestResult");
            if (info != null)
                DirectPrintLibcs.lst.Remove(info);
            if (dt != null && dt.Columns.Count > 0)
            {
                DirectPrintLibcs.lst.Add(new TreeNodeInfo
                {
                    Type = CtrlType.Grid,
                    Name = "TestResult",
                    Table = dt,
                    Text = Info.TestResult,
                    Caption = Info.TestResult
                });
            }
            info = DirectPrintLibcs.lst.Find(w => w.Name == "StatisticsInfo");
            if (info != null)
                DirectPrintLibcs.lst.Remove(info);
            dt = WorkCurveHelper.DGVToDataTable(this.dgvStatics);
            if (dt == null || dt.Rows.Count == 0 || dt.Columns.Count == 0)
                return false;
            if (dt != null && dt.Rows.Count > 0 && dt.Columns.Count > 0)
            {
                dt.Columns[0].Caption = "";
                DirectPrintLibcs.lst.Add(new TreeNodeInfo
                {
                    Type = CtrlType.Grid,
                    Name = "StatisticsInfo",
                    Table = dt,
                    Text = Info.StatisticsInfo,
                    Caption = Info.StatisticsInfo
                });
            }
            return true;
        }

        bool uc_OnPrintTemplateSource()
        {
            return LoadDataPrintTemplate();
        }

        private void Tick_Normal()
        {
            //修改：何晓明 20110714 软件关闭时几率性dgvDevice.RowCount=0            
            if (this.dgvDevice.RowCount == 0)
            {
                if (!dgvDevice.Columns.Contains(ColumnDeviceLabel))
                    dgvDevice.Columns.Add(ColumnDeviceLabel);
                if (!dgvDevice.Columns.Contains(ColumnDeviceValue))
                    dgvDevice.Columns.Add(ColumnDeviceValue);
                ContructDevice();
            }
            if (WorkCurveHelper.DeviceCurrent.HasChamber && WorkCurveHelper.DeviceCurrent.Chamber.Count > 0)
            {
                this.dgvDevice["ColumnDeviceValue", this.dgvDevice.RowCount - 1].Value = DifferenceDevice.interClassMain.deviceMeasure.interfacce.GetChamberIndex();
            }
            DifferenceDevice.interClassMain.deviceMeasure.interfacce.GetReturnParams();
            //DeviceParameter listParms = DifferenceDevice.interClassMain.deviceMeasure.interfacce.DeviceParam;
            //if (listParms != null)
            //{
            //    this.dgvDevice["ColumnDeviceValue", 0].Value = listParms.TubCurrent.ToString("f0") + " μA";
            //    this.dgvDevice["ColumnDeviceValue", 1].Value = listParms.TubVoltage.ToString("f0") + " kV";
            //}

            /////如果为初始化模式下，则管压、管流取初始化测量条件中的值
            //if (DifferenceDevice.interClassMain.optMode == OptMode.Initalize)
            //{
            //    InitParameter initParms = DifferenceDevice.interClassMain.deviceMeasure.interfacce.InitParam;
            //    if (initParms != null)
            //    {
            //        this.dgvDevice["ColumnDeviceValue", 0].Value = initParms.TubCurrent.ToString("f0") + " μA";
            //        this.dgvDevice["ColumnDeviceValue", 1].Value = initParms.TubVoltage.ToString("f0") + " kV";
            //    }
            //}


            this.dgvDevice["ColumnDeviceValue", 0].Value = DifferenceDevice.interClassMain.deviceMeasure.interfacce.ReturnCurrent.ToString("f0") + " μA";

          
           
            this.dgvDevice["ColumnDeviceValue", 1].Value = DifferenceDevice.interClassMain.deviceMeasure.interfacce.ReturnVoltage.ToString("f0") + " kV";
         
                
            if (DifferenceDevice.interClassMain.deviceMeasure.interfacce.connect != DeviceConnect.Connect || DifferenceDevice.interClassMain.deviceMeasure.interfacce.StopFlag)
            {
                this.dgvDevice["ColumnDeviceValue", 0].Value = "0 μA";
                this.dgvDevice["ColumnDeviceValue", 1].Value = "0 kV";
            }

            //this.dgvDevice["ColumnDeviceValue", 2].Value = DifferenceDevice.interClassMain.deviceMeasure.interfacce.ReturnGain.ToString();
            //this.dgvDevice["ColumnDeviceValue", 3].Value = DifferenceDevice.interClassMain.deviceMeasure.interfacce.ReturnFineGain.ToString();
            this.dgvDevice["ColumnDeviceValue", 2].Value = DifferenceDevice.interClassMain.deviceMeasure.interfacce.ReturnCountRate.ToString("f2");
            this.dgvDevice["ColumnDeviceValue", 3].Value = (DifferenceDevice.interClassMain.deviceMeasure.interfacce.usedTime).ToString() + " s";
            DeviceParameter listParms = DifferenceDevice.interClassMain.deviceMeasure.interfacce.DeviceParam;
            if (listParms != null && DifferenceDevice.interClassMain.spec != null && DifferenceDevice.interClassMain.spec.SpecData != null)
            {
                if (WorkCurveHelper.DeviceCurrent.ComType == ComType.FPGA)
                {
                    this.dgvDevice["ColumnDeviceValue", 4].Value = SpecHelper.FitChannOfMaxValue(50, (int)WorkCurveHelper.DeviceCurrent.SpecLength - 50, DifferenceDevice.interClassMain.spec.SpecDatas).ToString("f1");
                }
                else
                {
                    if (DifferenceDevice.interClassMain.optMode == OptMode.Initalize)
                        this.dgvDevice["ColumnDeviceValue", 4].Value = SpecHelper.FitChannOfMaxValue(50, (int)WorkCurveHelper.DeviceCurrent.SpecLength - 50, DifferenceDevice.interClassMain.spec.SpecDatas).ToString("f1");
                    else
                        this.dgvDevice["ColumnDeviceValue", 4].Value = SpecHelper.FitChannOfMaxValue(listParms.BeginChann, listParms.EndChann, DifferenceDevice.interClassMain.spec.SpecDatas).ToString("f1");

                }

            }
            else
            {
                this.dgvDevice["ColumnDeviceValue", 4].Value = "0";
            }

            this.dgvDevice["ColumnDeviceValue", 5].Value = DifferenceDevice.interClassMain.currentTestTimes.ToString();
            string str = string.Empty;
            //if (WorkCurveHelper.DeviceCurrent.VacuumPumpType == VacuumPumpType.Atmospheric)
            //    str = "kPa";
            //else
            //{
            //    str = "Pa";
            //}
            //if (WorkCurveHelper.DeviceCurrent.ComType == ComType.FPGA && WorkCurveHelper.DeviceCurrent.VacuumPumpType == VacuumPumpType.Atmospheric)
            //    this.dgvDevice["ColumnDeviceValue", 10].Value = (DifferenceDevice.interClassMain.deviceMeasure.interfacce.ReturnVacuum / 1000).ToString("f1") + str;
            //else
            //    this.dgvDevice["ColumnDeviceValue", 10].Value = DifferenceDevice.interClassMain.deviceMeasure.interfacce.ReturnVacuum.ToString("f1") + str;
            this.dgvDevice["ColumnDeviceValue", 6].Value = DifferenceDevice.interClassMain.deviceMeasure.interfacce.ReturnEncoderValue.ToString("f1") + str;
            if (WorkCurveHelper.TestOnButtonPressedEnabled)
            {
                DifferenceDevice.interClassMain.DoTestOnButtonPressed();
            }

            /////是否使用电磁阀门
            if (WorkCurveHelper.IsUseElect && WorkCurveHelper.IsContinueVol)
            {
                DifferenceDevice.interClassMain.DoOpenCoverStartElect();
            }
            else if (WorkCurveHelper.bCustomDevice || WorkCurveHelper.bOpenOutSample)
            {
                DifferenceDevice.interClassMain.DoOpenCoverInOutSample();
            }

            if (WorkCurveHelper.testingOpenCover)
            {
                string filePath = "谱数据.txt";
                try
                {
                    // 检查文件是否存在
                    if (!File.Exists(filePath))
                    {
                        // 文件不存在，创建文件
                        File.Create(filePath).Close();
                    }
                    using (StreamWriter sw = new StreamWriter(filePath, true))
                    {

                        sw.WriteLine(DateTime.Now.ToString());
                        sw.WriteLine("继续测试记录");


                    }
                }
                catch
                {
                }

                ((UC.Thick)DifferenceDevice.interClassMain).testContinue();

            }

        }

        private void Tick_ExceptNormal()
        {
            //if (DifferenceDevice.interClassMain.deviceMeasure.interfacce.DeviceParam != null && (DifferenceDevice.interClassMain.deviceMeasure.interfacce.DeviceParam.IsVacuum
            //     || DifferenceDevice.interClassMain.deviceMeasure.interfacce.DeviceParam.IsVacuumDegree) && WorkCurveHelper.DeviceCurrent.HasVacuumPump)
            //{

            Tick_Normal();
            NaviItem itemMoveStation = WorkCurveHelper.NaviItems.Find(w => w.Name == "MoveWorkStation");
            if (itemMoveStation != null)
            {
                var value = Math.Abs(WorkCurveHelper.Volumngreen - DifferenceDevice.interClassMain.deviceMeasure.interfacce.ReturnVacuum);
                //if (value == 0)
                //    return;

                if (value <= WorkCurveHelper.MoveStationVisible)
                {
                    itemMoveStation.EnabledControl = true;
                    this.ucCameraControl1.DisableControlNew(WorkCurveHelper.DeviceCurrent);
                    WorkCurveHelper.Volumngreen = DifferenceDevice.interClassMain.deviceMeasure.interfacce.ReturnVacuum;
                }
                else
                {
                    itemMoveStation.EnabledControl = false;
                    Device tempDevice = Device.New;
                    tempDevice.HasMotorX = false;
                    tempDevice.HasMotorY = false;
                    tempDevice.HasMotorZ = false;
                    if (this.ucCameraControl1 != null)
                        this.ucCameraControl1.DisableControlNew(tempDevice);
                    if (this.ucCameraControl1 != null)
                        this.ucCameraControl1.Flag = false;
                }
            }
            //}
        }


        private void timer_Tick(object source, EventArgs e)
        {
            if (!DifferenceDevice.interClassMain.HasAutoDetection && WorkCurveHelper.IsOnStartDetedtion)
            {
                DifferenceDevice.interClassMain.HasAutoDetection = true;
                DifferenceDevice.interClassMain.AutoDetection();
            }
            if (DifferenceDevice.interClassMain.deviceMeasure.interfacce.connect == DeviceConnect.Connect && !DifferenceDevice.interClassMain.deviceMeasure.interfacce.StopFlag)
            {
                if (!colorChange)
                {
                    this.tslCircle.Image = Properties.Resources.xsimple_009_green;
                    this.xrfChart1.IMeasure = true;
                }
                colorChange = true;
                Tick_Normal();

            }
            else
            {
                if (colorChange)
                {
                    this.tslCircle.Image = Properties.Resources.xsimple_004_red;
                    this.xrfChart1.IMeasure = false;
                }
                colorChange = false;
                Tick_ExceptNormal();
            }
        }

        private bool colorChange = true;
        bool DoReceive = false;
        protected override void DefWndProc(ref Message m)
        {           
            switch (m.Msg)
            {
                case DeviceInterface.WM_ReceiveData://测量完成                    
                    if (DifferenceDevice.interClassMain != null && !DoReceive && DifferenceDevice.interClassMain.startTest)
                    {
                        DoReceive = true;
                        try
                        {
                            OnReceiveData(m.LParam.ToInt32());
                        }
                        catch
                        { }
                        DoReceive = false;
                    }

                    break;
                case DeviceInterface.WM_EndInitial:
                    int value = m.WParam.ToInt32();
                    OnInitialEnd(Convert.ToBoolean(value));
                    break;
                case DeviceInterface.WM_EndTest:
                    OnTestEnd(m.LParam.ToInt32());

                    if ((WorkCurveHelper.testNum == 1 && WorkCurveHelper.testTimes == 0) || WorkCurveHelper.testNum == 0)
                    {


                        


                        if (WorkCurveHelper.DeviceCurrent.HasMotorSpin)
                        {
                            MotorOperator.MotorOperatorY1Thread((int)(WorkCurveHelper.TestDis * WorkCurveHelper.Y1Coeff));
                            DifferenceDevice.CurCameraControl.skyrayCamera1.Start();
                        }
                        if (WorkCurveHelper.filterReset)
                        {

                            if (DifferenceDevice.interClassMain.deviceMeasure.interfacce.FilterMotor.Exist && DifferenceDevice.interClassMain.deviceMeasure.interfacce.DeviceParam.TargetMode != TargetMode.TwoTarget)
                            {
                                DifferenceDevice.interClassMain.deviceMeasure.interfacce.FilterMotor.MoveTo(5);
                            }
                        }
                    }
                    break;
                case DeviceInterface.WM_MoveStop:
                    OnMoveStop();
                    break;
                case DeviceInterface.WM_DeviceDisConnect:
                    OnDeviceConnect();
                    break;
                case DeviceInterface.Wm_OpenCover:
                    if (DifferenceDevice.interClassMain != null)
                    {
                        DifferenceDevice.interClassMain.TestStartAfterControlState(true);
                        DifferenceDevice.IsConnect = false;
                        WorkCurveHelper.specMessage.localMesage.Add(new MessageFormat(Info.CoverOpen, 0));
                        Msg.Show(Info.CoverOpen);
                        WorkCurveHelper.testingOpenCover = true;
                    }
                    break;

                case DeviceInterface.Wm_SuspendTest:
                    if (DifferenceDevice.interClassMain != null)
                    {
                        DifferenceDevice.interClassMain.TestStartAfterControlState(true);
                        DifferenceDevice.IsConnect = false;
                        WorkCurveHelper.specMessage.localMesage.Add(new MessageFormat(Info.suspendTest, 0));

                    }
                    break;
                case DeviceInterface.Wm_Connection:
                    OnConnection();
                    break;
                case DeviceInterface.Wm_PreheatOpenVoltage:
                    OnPreHeatOpenVoltage(m.LParam.ToInt32());
                    break;
                case DeviceInterface.Wm_PreheatOpenEnd:
                    OnPreHeatOpenEnd(m.LParam.ToInt32());
                    break;
                case DeviceInterface.Wm_ProcessInit:
                    DifferenceDevice.interClassMain.TestInitalize(true, false, false, 0);
                    break;
                case DeviceInterface.Wm_PumpStart:
                    DifferenceDevice.interClassMain.PumpStartProcess(m.LParam.ToInt32());
                    break;
                case DeviceInterface.Wm_PumpEnd:
                    DifferenceDevice.interClassMain.PumpEndProcess();
                    break;
                case DeviceInterface.Wm_AutoAscendZ:
                    DifferenceDevice.interClassMain.AscendZAutoEnd();
                    break;
                case DeviceInterface.Wm_NextInitializationElem:
                    int id = m.LParam.ToInt32() + 1;
                    DifferenceDevice.interClassMain.TestInitalize(true, false, true, id);
                    break;
                case DeviceInterface.Wm_InitAddCurrent:
                    DifferenceDevice.interClassMain.TestInitializeAddCurrent();
                    break;
                case DeviceInterface.Wm_ContinueCalibrateElem:
                    int elem = m.LParam.ToInt32() + 1;
                    DifferenceDevice.ithick.ExcuteCurveCalibrate(null, elem, OptMode.CurveCalibrate);
                    break;
                case DeviceInterface.Wm_CalibrateElemFinish:
                    WorkCurveHelper.WorkCurveCurrent.SetBasePureSpec(WorkCurveHelper.GetbasePureSpec());
                    Msg.Show(Info.AdjustFinshed);
                    //DifferenceDevice.interClassMain.TestEndCurrentProcess();
                    break;
                case DeviceInterface.Wm_LoadAllCurve:
                    LoadAllWorkCruve();
                    break;
                default:
                    base.DefWndProc(ref m);
                    break;
            }
        }

        //protected override bool ProcessDialogKey(Keys keyData)
        //{
        //    if (keyData == Keys.F2)
        //    {
        //        NewWorkSpec newSpec = new NewWorkSpec(DifferenceDevice.interClassMain.currentSelectMode);
        //        WorkCurveHelper.OpenUC(newSpec, false, Info.Start);
        //        return true;
        //    }
        //    else if (keyData == Keys.F3)
        //    {
        //        DifferenceDevice.uc.ExcutePrint(null);
        //        return true;
        //    }
        //    else if (keyData == Keys.F4)
        //    {
        //        DifferenceDevice.interClassMain.TestInitalize(true);
        //        return true;
        //    }
        //    else if (keyData == Keys.F5)
        //    {
        //        EDXRFHelper.DirectPrint(temp);
        //        return true;
        //    }
        //    else
        //    {
        //        return base.ProcessDialogKey(keyData);
        //    }
        //}

        #region
        private void OnConnection()
        {
            if (DifferenceDevice.interClassMain != null)
                DifferenceDevice.interClassMain.PauseStart();
        }

        private void OnDeviceConnect()
        {
            if (DifferenceDevice.interClassMain != null)
            {
                DifferenceDevice.interClassMain.TestStartAfterControlState(true);
                Msg.Show(Info.NoDeviceConnect);
                //DifferenceDevice.interClassMain.ConnectDevice();
            }
        }

        private void OnMoveStop()
        {
            if (DifferenceDevice.interClassMain != null)
                DifferenceDevice.interClassMain.MessageStopMove(DifferenceDevice.interClassMain.optMode);
        }

        private void OnInitialEnd(bool success)
        {
            if (DifferenceDevice.interClassMain != null)
                DifferenceDevice.interClassMain.TestInitilizeEnd(success);
        }

        private void OnPreHeatOpenEnd(int usedTime)
        {
            if (DifferenceDevice.interClassMain != null)
                DifferenceDevice.interClassMain.PreHeatOpenVoltageEnd();
        }

        private void OnPreHeatOpenVoltage(int useTime)
        {
            if (DifferenceDevice.interClassMain != null)
                DifferenceDevice.interClassMain.ReceiveOpenVoltageTime(useTime);
        }

        private void OnReceiveData(int useTime)
        {
            if (DifferenceDevice.interClassMain != null)
                DifferenceDevice.interClassMain.UpdateSpecGraphic(useTime);
        }

        private void OnTestEnd(int useTime)
        {

            if (DifferenceDevice.interClassMain != null)
                DifferenceDevice.interClassMain.CallTerminateTestFun(DifferenceDevice.interClassMain.optMode, useTime, WorkCurveHelper.WorkCurveCurrent);
        }
        #endregion
        private void RefreshWholeData()
        {
            ////构造定性分析
            //ContructQulity();

            ////构造设备
            ContructDevice();

            ////构造曲线
            //ContructCurve();

            //构造工作谱
            //ContructSpec();
        }

        ///// <summary>
        ///// 定性分析
        ///// </summary>
        //private void ContructQulity()
        //{
        //    this.dgvQuality.RowCount = 9;
        //    this.dgvQuality["ColumnLabel", 0].Value = Info.Count;
        //    this.dgvQuality["ColumnLabel", 1].Value = Info.Channel;
        //    this.dgvQuality["ColumnLabel", 2].Value = Info.Energy;
        //    this.dgvQuality["ColumnLabel", 3].Value = Info.Ka;
        //    this.dgvQuality["ColumnLabel", 4].Value = Info.Kb;
        //    this.dgvQuality["ColumnLabel", 5].Value = Info.La;
        //    this.dgvQuality["ColumnLabel", 6].Value = Info.Lb;
        //    this.dgvQuality["ColumnLabel", 7].Value = Info.Le;
        //    this.dgvQuality["ColumnLabel", 8].Value = Info.Lr;

        //    //AddToDic(
        //}

        private void ContructDevice()
        {
            this.dgvDevice.RowCount = 7;
            if (WorkCurveHelper.DeviceCurrent.HasChamber && WorkCurveHelper.DeviceCurrent.Chamber.Count > 0)
            {
                this.dgvDevice.RowCount++;
                this.dgvDevice["ColumnDeviceLabel", this.dgvDevice.RowCount - 1].Value = Info.ChamberIndex;
            }
            this.dgvDevice["ColumnDeviceLabel", 0].Value = Info.Current;
            this.dgvDevice["ColumnDeviceLabel", 1].Value = Info.Voltage;
            this.dgvDevice["ColumnDeviceLabel", 2].Value = Info.CountRate;
            this.dgvDevice["ColumnDeviceLabel", 3].Value = Info.MeasureTime;
            this.dgvDevice["ColumnDeviceLabel", 4].Value = Info.PeakChannel;
            this.dgvDevice["ColumnDeviceLabel", 5].Value = Info.CountTimes;
            this.dgvDevice["ColumnDeviceLabel", 6].Value = Info.EncoderValue;

            //this.dgvDevice["ColumnDeviceLabel", 0].Value = Info.Current;
            //this.dgvDevice["ColumnDeviceLabel", 1].Value = Info.Voltage;
            //this.dgvDevice["ColumnDeviceLabel", 2].Value = Info.Gain;
            //this.dgvDevice["ColumnDeviceLabel", 3].Value = Info.FineGain;
            //this.dgvDevice["ColumnDeviceLabel", 4].Value = Info.CountRate;
            //this.dgvDevice["ColumnDeviceLabel", 5].Value = Info.MeasureTime;
            //this.dgvDevice["ColumnDeviceLabel", 6].Value = Info.PeakChannel;
            //this.dgvDevice["ColumnDeviceLabel", 7].Value = Info.Filter;
            //this.dgvDevice["ColumnDeviceLabel", 8].Value = Info.Collimator;
            //this.dgvDevice["ColumnDeviceLabel", 9].Value = Info.CountTimes;
            //this.dgvDevice["ColumnDeviceLabel", 10].Value = Info.EncoderValue;

        }

        //private void ContructCurve()
        //{
        //    this.dgvCurve.RowCount = 13;
        //    if (WorkCurveHelper.DeviceCurrent != null && WorkCurveHelper.DeviceCurrent.HasTarget && WorkCurveHelper.DeviceCurrent.Target != null && WorkCurveHelper.DeviceCurrent.Target.Count > 0)
        //    {
        //        this.dgvCurve.RowCount = 16;
        //    }
        //    this.dgvCurve["ColumnCurveLabel", 0].Value = Info.WorkingCurve;
        //    this.dgvCurve["ColumnCurveLabel", 1].Value = Info.MeasureTime;
        //    this.dgvCurve["ColumnCurveLabel", 2].Value = Info.Current;
        //    this.dgvCurve["ColumnCurveLabel", 3].Value = Info.Voltage;
        //    this.dgvCurve["ColumnCurveLabel", 4].Value = Info.Filter;
        //    this.dgvCurve["ColumnCurveLabel", 5].Value = Info.Collimator;
        //    this.dgvCurve["ColumnCurveLabel", 6].Value = Info.VacuumizeByTime;
        //    this.dgvCurve["ColumnCurveLabel", 7].Value = Info.AdjustCountRate;
        //    this.dgvCurve["ColumnCurveLabel", 8].Value = Info.MaxCountRate;
        //    this.dgvCurve["ColumnCurveLabel", 9].Value = Info.MinCountRate;
        //    this.dgvCurve["ColumnCurveLabel", 10].Value = Info.InitalElem;
        //    this.dgvCurve["ColumnCurveLabel", 11].Value = Info.InitalChann;
        //    this.dgvCurve["ColumnCurveLabel", 12].Value = Info.Condition;
        //    if (WorkCurveHelper.DeviceCurrent != null && WorkCurveHelper.DeviceCurrent.HasTarget && WorkCurveHelper.DeviceCurrent.Target != null && WorkCurveHelper.DeviceCurrent.Target.Count > 0)
        //    {
        //        this.dgvCurve["ColumnCurveLabel", 13].Value = Info.TargetIndex;
        //        this.dgvCurve["ColumnCurveLabel", 14].Value = Info.TargetMode;
        //        this.dgvCurve["ColumnCurveLabel", 15].Value = Info.TubCurrentRatio;
        //    }
        //}

        //private void ContructSpec()
        //{
        //    this.dgvWorkSpec.RowCount = 13;
        //    this.dgvWorkSpec["ColumnSpecLable", 0].Value = Info.SampleName;
        //    this.dgvWorkSpec["ColumnSpecLable", 1].Value = Info.Supplier;
        //    this.dgvWorkSpec["ColumnSpecLable", 2].Value = Info.Weight;
        //    this.dgvWorkSpec["ColumnSpecLable", 3].Value = Info.Shape;
        //    this.dgvWorkSpec["ColumnSpecLable", 4].Value = Info.SpecDate;
        //    this.dgvWorkSpec["ColumnSpecLable", 5].Value = Info.MeasureTime;
        //    this.dgvWorkSpec["ColumnSpecLable", 6].Value = Info.Operator;
        //    this.dgvWorkSpec["ColumnSpecLable", 7].Value = Info.Current;
        //    this.dgvWorkSpec["ColumnSpecLable", 8].Value = Info.Voltage;
        //    this.dgvWorkSpec["ColumnSpecLable", 9].Value = Info.Filter;
        //    this.dgvWorkSpec["ColumnSpecLable", 10].Value = Info.Collimator;
        //    this.dgvWorkSpec["ColumnSpecLable", 11].Value = Info.Channel;
        //    this.dgvWorkSpec["ColumnSpecLable", 12].Value = Info.Summary;
        //}


        #region IRefreshFillInfo Members
        public void ChangeCheckedCurve()
        {
            LoadAllWorkCruve();

        }

        public void RefreshTarget()
        {
            // this.ContructCurve();
        }

        public void SetStyle(Style style)
        {

        }

        public void RefreshQuality()
        {
            //this.dgvQuality["ColumnValue", 0].Value = this.xrfChart1.CurrentChannelCount;//当前值
            //this.dgvQuality["ColumnValue", 1].Value = this.xrfChart1.ICurrentChannel;//当前道
            //double energy = this.xrfChart1.DEnergy;//能量
            //this.dgvQuality["ColumnValue", 2].Value = energy.ToString("0.00000");
            //this.dgvQuality["ColumnValue", 3].Value = Atoms.GetAtoms(energy, XLine.Ka);//得到特定能量特定谱线的元素
            //this.dgvQuality["ColumnValue", 4].Value = Atoms.GetAtoms(energy, XLine.Kb);
            //this.dgvQuality["ColumnValue", 5].Value = Atoms.GetAtoms(energy, XLine.La);
            //this.dgvQuality["ColumnValue", 6].Value = Atoms.GetAtoms(energy, XLine.Lb);
            //this.dgvQuality["ColumnValue", 7].Value = Atoms.GetAtoms(energy, XLine.Lr);
            //this.dgvQuality["ColumnValue", 8].Value = Atoms.GetAtoms(energy, XLine.Le);
        }

        public void RefreshCurve(Skyray.EDXRFLibrary.InitParameter InitParameter, Skyray.EDXRFLibrary.DeviceParameter deviceParams)
        {
            //this.dgvCurve["ColumnCurveValue", 0].Value = WorkCurveHelper.WorkCurveCurrent == null ? "" : WorkCurveHelper.WorkCurveCurrent.Name;
            //this.dgvCurve["ColumnCurveValue", 1].Value = deviceParams.PrecTime.ToString();
            //this.dgvCurve["ColumnCurveValue", 2].Value = deviceParams.TubCurrent.ToString(); 
            //this.dgvCurve["ColumnCurveValue", 3].Value = deviceParams.TubVoltage.ToString();
            //this.dgvCurve["ColumnCurveValue", 4].Value = (deviceParams.FilterIdx).ToString();
            //this.dgvCurve["ColumnCurveValue", 5].Value = (deviceParams.CollimatorIdx).ToString();
            //this.dgvCurve["ColumnCurveValue", 6].Value = deviceParams.VacuumTime.ToString();
            //this.dgvCurve["ColumnCurveValue", 7].Value = deviceParams.IsAdjustRate ? "1" : "0";
            //this.dgvCurve["ColumnCurveValue", 8].Value = deviceParams.MaxRate.ToString();
            //this.dgvCurve["ColumnCurveValue", 9].Value = deviceParams.MinRate.ToString();
            //this.dgvCurve["ColumnCurveValue", 10].Value = InitParameter.ElemName.ToString();
            //this.dgvCurve["ColumnCurveValue", 11].Value = InitParameter.Channel.ToString();
            //this.dgvCurve["ColumnCurveValue", 12].Value = deviceParams.Name;
            //if (WorkCurveHelper.DeviceCurrent != null && WorkCurveHelper.DeviceCurrent.HasTarget && WorkCurveHelper.DeviceCurrent.Target != null && WorkCurveHelper.DeviceCurrent.Target.Count > 0)
            //{
            //    this.dgvCurve["ColumnCurveValue", 13].Value = deviceParams.TargetIdx;
            //    this.dgvCurve["ColumnCurveValue", 14].Value = deviceParams.TargetMode.ToString();
            //    this.dgvCurve["ColumnCurveValue", 15].Value = deviceParams.CurrentRate.ToString();
            //}
        }

        public void RefreshDevice()
        {

        }

        public void RefreshSpec(Skyray.EDXRFLibrary.Spectrum.SpecListEntity specList, Skyray.EDXRFLibrary.Spectrum.SpecEntity spec)
        {
            //this.dgvWorkSpec["ColumnSpecValue", 0].Value = specList.SampleName;
            //this.dgvWorkSpec["ColumnSpecValue", 1].Value = specList.Supplier;
            //if (specList.Weight.HasValue)
            //    this.dgvWorkSpec["ColumnSpecValue", 2].Value = specList.Weight.Value.ToString("f4");

            //this.dgvWorkSpec["ColumnSpecValue", 3].Value = specList.Shape;
            //this.dgvWorkSpec["ColumnSpecValue", 4].Value = specList.SpecDate.ToString();
            //this.dgvWorkSpec["ColumnSpecValue", 5].Value = spec.UsedTime.ToString();
            //this.dgvWorkSpec["ColumnSpecValue", 6].Value = specList.Operater;
            //if (spec.DeviceParameter != null)
            //{
            //    this.dgvWorkSpec["ColumnSpecValue", 7].Value = spec.DeviceParameter.TubCurrent.ToString();
            //    this.dgvWorkSpec["ColumnSpecValue", 8].Value = spec.DeviceParameter.TubVoltage.ToString();
            //    this.dgvWorkSpec["ColumnSpecValue", 9].Value = (spec.DeviceParameter.FilterIdx).ToString();
            //    this.dgvWorkSpec["ColumnSpecValue", 10].Value = (spec.DeviceParameter.CollimatorIdx).ToString();
            //    this.dgvWorkSpec["ColumnSpecValue", 11].Value = (specList.InitParam == null) ? "" : specList.InitParam.Channel.ToString();//specList.InitParam.Channel.ToString();
            //}
        }



        public void RefreshMeasureResult(int currentTimes, ElementList elementList)
        {
            if (dgvMeasure.Columns.Count == 0)
                return;


            int recordIndex = 0;
            if (DifferenceDevice.CurCameraControl.ChkRetest.Checked)
            {
                currentTimes = retestIndex;
                recordIndex = retestIndex - 1;
            }
            else
                recordIndex = DifferenceDevice.interClassMain.recordList.Count - 1;


            string[] elementName = new string[elementList.Items.Count - 1];
            string[] valuse = new string[elementList.Items.Count - 1];
            double totalthick = 0;
            int cnt = 0;
            List<HistoryElement> lstElem = HistoryElement.FindBySql("select * from HistoryElement where HistoryRecord_Id = '" + DifferenceDevice.interClassMain.recordList[recordIndex].ToString() + "'");

            if (WorkCurveHelper.HistoryAverageRows > 1 && currentTimes > 1 && DifferenceDevice.interClassMain.startTest)
            {
                for (int i = 0; i < dgvMeasure.Columns.Count; i++)
                {
                    if (i == 0)
                    {
                        dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = currentTimes;
                        continue;
                    }
                    string str = (this.dgvMeasure.Columns[i].Name.IndexOf("|") == -1) ? this.dgvMeasure.Columns[i].Name : this.dgvMeasure.Columns[i].Name.Substring(0, this.dgvMeasure.Columns[i].Name.IndexOf("|"));
                    //CurveElement element = elementList.Items.ToList().Find(delegate(CurveElement w) { return String.Compare(w.Caption, str.Trim(), true) == 0; });
                    CurveElement element = elementList.Items.ToList().Find(delegate(CurveElement w) { return String.Compare(w.DefineElemName, str.Trim(), true) == 0; });

                    if (element == null)
                        continue;
                    if (dgvMeasure.Columns[i].Tag.ToString().Equals("Content"))
                    {
                        if (WorkCurveHelper.WorkCurveCurrent.IsThickShowAreaThick)
                        {
                            double tva = 0;
                            if (lstElem != null && lstElem.Find(w => w.elementName == element.Caption) != null)
                            {
                                bool isdouble = double.TryParse(lstElem.Find(w => w.elementName == element.Caption).contextelementValue, out tva);
                                dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = tva.ToString("f" + WorkCurveHelper.ThickBit);
                            }
                        }
                        else
                        {
                            double temop = element.Content >= 100 ? 100 : element.Content;
                            string strResult = string.Empty;
                            //2014-03-18  修改千分比的数值转换错误
                            switch (element.ContentUnit)
                            {
                                case ContentUnit.ppm:
                                    strResult = (temop * 10000).ToString("f" + WorkCurveHelper.SoftWareContentBit.ToString());
                                    break;
                                case ContentUnit.permillage:
                                    strResult = (temop * 10).ToString("f" + WorkCurveHelper.SoftWareContentBit.ToString());
                                    break;
                                case ContentUnit.per:
                                    strResult = temop.ToString("f" + WorkCurveHelper.SoftWareContentBit.ToString());
                                    break;
                            }
                            dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = strResult;
                            //dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = (element.ContentUnit.ToString().Equals("per")) ? temop.ToString("f" + WorkCurveHelper.SoftWareContentBit) : (temop * 10000).ToString("f" + WorkCurveHelper.SoftWareContentBit);

                        }
                    }
                    else if (dgvMeasure.Columns[i].Tag.ToString().Equals("Error"))
                    {
                        string strError = string.Empty;
                        //2014-03-18  修改千分比的数值转换错误
                        switch (element.ContentUnit)
                        {
                            case ContentUnit.ppm:
                                strError = (element.Content * 10000).ToString("f" + WorkCurveHelper.SoftWareContentBit.ToString());
                                break;
                            case ContentUnit.permillage:
                                strError = (element.Error * 10).ToString("f" + WorkCurveHelper.SoftWareContentBit.ToString());
                                break;
                            case ContentUnit.per:
                                strError = element.Error.ToString("f" + WorkCurveHelper.SoftWareContentBit.ToString());
                                break;
                        }
                        //dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = (element.ContentUnit.ToString().Equals("per")) ? element.Error.ToString("f" + WorkCurveHelper.SoftWareContentBit) : (element.Error * 10000).ToString("f" + WorkCurveHelper.SoftWareContentBit);
                        dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = strError;
                    }
                    else if (dgvMeasure.Columns[i].Tag.ToString().Equals("Thick"))
                    {
                        double tva = 0;
                        if (lstElem != null && lstElem.Find(w => w.elementName == element.Caption) != null)
                        {

                            bool isdouble = double.TryParse(lstElem.Find(w => w.elementName == element.Caption).thickelementValue, out tva);
                            // double Contva = (element.ThicknessUnit.ToString().Equals("um")) ? tva : (tva / 0.0254);
                            double Contva = 0;
                            switch (element.ThicknessUnit)
                            {
                                case ThicknessUnit.ur:
                                    Contva = tva * 0.0254;
                                    break;
                                case ThicknessUnit.um:
                                case ThicknessUnit.gl:
                                    Contva = tva;
                                    break;
                            }
                            if (Contva <= WorkCurveHelper.ThicknessLimit)
                                dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = tva.ToString("f" + WorkCurveHelper.ThickBit);
                            else
                            {
                                dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = "--";
                            }
                            totalthick += element.Thickness;
                            if (elementList.CustomFields.Count > 0)
                            {
                                elementName[cnt] = element.Caption;
                                valuse[cnt] = tva.ToString("f" + WorkCurveHelper.ThickBit);
                                cnt++;
                            }

                        }
                        else
                        {
                            totalthick += element.Thickness;
                            if (elementList.CustomFields.Count > 0)
                            {
                                elementName[cnt] = element.Caption;
                                valuse[cnt] = element.Thickness.ToString();
                                cnt++;
                            }

                            //if (element.Thickness == -1)  //超范围的值
                            if (element.Thickness <= WorkCurveHelper.ThicknessLimit)
                            {
                                switch (element.ThicknessUnit)
                                {
                                    case ThicknessUnit.ur:
                                        dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = (element.Thickness / 0.0254).ToString("f" + WorkCurveHelper.ThickBit);
                                        break;
                                    case ThicknessUnit.um:
                                    case ThicknessUnit.gl:
                                        dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = element.Thickness.ToString("f" + WorkCurveHelper.ThickBit);
                                        break;
                                }
                            }
                            //dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = (element.ThicknessUnit.ToString().Equals("um")) ? element.Thickness.ToString("f" + WorkCurveHelper.ThickBit) : (element.Thickness / 0.0254).ToString("f" + WorkCurveHelper.ThickBit);
                            else
                                dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = "--";
                        }

                        string baseelemName = WorkCurveHelper.WorkCurveCurrent.ElementList.Items.ToList().Find(w => w.LayerNumBackUp == Info.Substrate || w.LayerNumBackUp == "基材" || w.LayerNumBackUp == "Substrate").Caption;

                        if ((FpWorkCurve.thickMode == ThickMode.NiNi || FpWorkCurve.thickMode == ThickMode.NiCuNi || FpWorkCurve.thickMode == ThickMode.NiCuNiFe
                            || FpWorkCurve.thickMode == ThickMode.NiCuNiFe2 || FpWorkCurve.thickMode == ThickMode.NewNiCuNi) && dgvMeasure.Columns[i].Name.ToUpper().Equals(baseelemName.ToUpper()))
                        {
                            dgvMeasure.Columns[i].HeaderText = "Ni2" + "(" + element.ThicknessUnit.ToString() + ")";

                        }


                    }
                    else if (dgvMeasure.Columns[i].Tag.ToString().Equals("AreaDensity"))
                    {
                        double tempdensityValue = elementList.GetAreaDensity(element.LayerNumber);
                        List<AreaDensityUnit> units = AreaDensityUnit.FindAll();
                        AreaDensityUnit ss = units.Find(w => w.Name == WorkCurveHelper.WorkCurveCurrent.AreaThickType);
                        if (ss != null && ss.Name != null && ss.Name != string.Empty) tempdensityValue = double.Parse(ss.cofeK) * tempdensityValue;
                        dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = tempdensityValue.ToString("F" + WorkCurveHelper.ThickBit.ToString());
                    }


                }

            }
            else
            {

                for (int i = 0; i < dgvMeasure.Columns.Count; i++)
                {
                    if (i == 0)
                    {
                        dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = currentTimes;
                        continue;
                    }
                    string str = (this.dgvMeasure.Columns[i].Name.IndexOf("|") == -1) ? this.dgvMeasure.Columns[i].Name : this.dgvMeasure.Columns[i].Name.Substring(0, this.dgvMeasure.Columns[i].Name.IndexOf("|"));
                    CurveElement element = elementList.Items.ToList().Find(delegate(CurveElement w) { return String.Compare(w.DefineElemName, str.Trim(), true) == 0; });

                    // CurveElement element = elementList.Items.ToList().Find(delegate(CurveElement w) { return String.Compare(w.Caption, str.Trim(), true) == 0; });
                    if (element == null)
                        continue;

                    //if (WorkCurveHelper.CalcType == CalcType.PeakDivBase)
                    //{

                    //     if (dgvMeasure.Columns[i].Tag.ToString().Equals("Thick"))
                    //    {
                    //        totalthick += element.Thickness;
                    //        dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = (element.ThicknessUnit.ToString().Equals("um")) ? element.Thickness.ToString("f" + WorkCurveHelper.ThickBit) : (element.Thickness / 0.0254).ToString("f" + WorkCurveHelper.ThickBit);
                    //    }
                    //    else if (dgvMeasure.Columns[i].Tag.ToString().Equals("AreaDensity"))
                    //    {
                    //        double tempdensityValue = elementList.GetAreaDensity(element.LayerNumber);
                    //        List<AreaDensityUnit> units = AreaDensityUnit.FindAll();
                    //        AreaDensityUnit ss = units.Find(w => w.Name == WorkCurveHelper.WorkCurveCurrent.AreaThickType);
                    //        if (ss != null && ss.Name != null && ss.Name != string.Empty) tempdensityValue = double.Parse(ss.cofeK) * tempdensityValue;
                    //        dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = tempdensityValue.ToString("F" + WorkCurveHelper.ThickBit.ToString());
                    //    }
                    //}
                    //else
                    //{
                    if (dgvMeasure.Columns[i].Tag.ToString().Equals("Content"))
                    {
                        if (WorkCurveHelper.WorkCurveCurrent.IsThickShowAreaThick)
                        {
                            double tva = 0;
                            if (lstElem != null && lstElem.Find(w => w.elementName == element.Caption) != null)
                            {
                                bool isdouble = double.TryParse(lstElem.Find(w => w.elementName == element.Caption).contextelementValue, out tva);
                                dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = tva.ToString("f" + WorkCurveHelper.ThickBit);
                            }
                        }
                        else
                        {
                            double temop = element.Content >= 100 ? 100 : element.Content;
                            string strResult = string.Empty;
                            //2014-03-18  修改千分比的数值转换错误
                            switch (element.ContentUnit)
                            {
                                case ContentUnit.ppm:
                                    strResult = (element.Content * 10000).ToString("f" + WorkCurveHelper.SoftWareContentBit.ToString());
                                    break;
                                case ContentUnit.permillage:
                                    strResult = (element.Content * 10).ToString("f" + WorkCurveHelper.SoftWareContentBit.ToString());
                                    break;
                                case ContentUnit.per:
                                    strResult = element.Content.ToString("f" + WorkCurveHelper.SoftWareContentBit.ToString());
                                    break;
                            }
                            dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = strResult;
                            //dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = (element.ContentUnit.ToString().Equals("per")) ? temop.ToString("f" + WorkCurveHelper.SoftWareContentBit) : (temop * 10000).ToString("f" + WorkCurveHelper.SoftWareContentBit);

                        }
                    }
                    else if (dgvMeasure.Columns[i].Tag.ToString().Equals("Error"))
                    {
                        string strError = string.Empty;
                        //2014-03-18  修改千分比的数值转换错误
                        switch (element.ContentUnit)
                        {
                            case ContentUnit.ppm:
                                strError = (element.Content * 10000).ToString("f" + WorkCurveHelper.SoftWareContentBit.ToString());
                                break;
                            case ContentUnit.permillage:
                                strError = (element.Error * 10).ToString("f" + WorkCurveHelper.SoftWareContentBit.ToString());
                                break;
                            case ContentUnit.per:
                                strError = element.Error.ToString("f" + WorkCurveHelper.SoftWareContentBit.ToString());
                                break;
                        }
                        //dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = (element.ContentUnit.ToString().Equals("per")) ? element.Error.ToString("f" + WorkCurveHelper.SoftWareContentBit) : (element.Error * 10000).ToString("f" + WorkCurveHelper.SoftWareContentBit);
                        dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = strError;
                    }
                    else if (dgvMeasure.Columns[i].Tag.ToString().Equals("Thick"))
                    {

                        totalthick += element.Thickness;
                        if (elementList.CustomFields.Count > 0)
                        {
                            elementName[cnt] = element.Caption;
                            valuse[cnt] = element.Thickness.ToString();
                            cnt++;
                        }
                        //if (element.Thickness == -1)  //超范围的值
                        if (element.Thickness <= WorkCurveHelper.ThicknessLimit)
                        {
                            switch (element.ThicknessUnit)
                            {
                                case ThicknessUnit.ur:
                                    dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = (element.Thickness / 0.0254).ToString("f" + WorkCurveHelper.ThickBit);
                                    break;
                                case ThicknessUnit.um:
                                case ThicknessUnit.gl:
                                    dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = element.Thickness.ToString("f" + WorkCurveHelper.ThickBit);
                                    break;
                            }
                        }
                        // dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = (element.ThicknessUnit.ToString().Equals("um")) ? element.Thickness.ToString("f" + WorkCurveHelper.ThickBit) : (element.Thickness / 0.0254).ToString("f" + WorkCurveHelper.ThickBit);
                        else
                            dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = "--";

                        string baseelemName = WorkCurveHelper.WorkCurveCurrent.ElementList.Items.ToList().Find(w => w.LayerNumBackUp == Info.Substrate || w.LayerNumBackUp == "基材" || w.LayerNumBackUp == "Substrate").Caption;

                        if ((FpWorkCurve.thickMode == ThickMode.NiNi || FpWorkCurve.thickMode == ThickMode.NiCuNi || FpWorkCurve.thickMode == ThickMode.NiCuNiFe
                            || FpWorkCurve.thickMode == ThickMode.NiCuNiFe2 || FpWorkCurve.thickMode == ThickMode.NewNiCuNi) && dgvMeasure.Columns[i].Name.ToUpper().Equals(baseelemName.ToUpper()))
                        {
                            dgvMeasure.Columns[i].HeaderText = "Ni2" + "(" + element.ThicknessUnit.ToString() + ")";

                        }


                    }
                    else if (dgvMeasure.Columns[i].Tag.ToString().Equals("AreaDensity"))
                    {
                        double tempdensityValue = elementList.GetAreaDensity(element.LayerNumber);
                        List<AreaDensityUnit> units = AreaDensityUnit.FindAll();
                        AreaDensityUnit ss = units.Find(w => w.Name == WorkCurveHelper.WorkCurveCurrent.AreaThickType);
                        if (ss != null && ss.Name != null && ss.Name != string.Empty) tempdensityValue = double.Parse(ss.cofeK) * tempdensityValue;
                        dgvMeasure.Rows[currentTimes - 1].Cells[i].Value = tempdensityValue.ToString("F" + WorkCurveHelper.ThickBit.ToString());
                    }


                }
            }

            foreach (var custom in elementList.CustomFields)
            {
                double value = double.Epsilon;
                TabControlHelper.CustomFieldByFortum(custom.Expression, elementName, valuse, 0, out value);
                if (value < WorkCurveHelper.ThicknessLimit)
                    dgvMeasure.Rows[currentTimes - 1].Cells[custom.Name].Value = value.ToString("f" + WorkCurveHelper.SoftWareContentBit.ToString());
                else
                    dgvMeasure.Rows[currentTimes - 1].Cells[custom.Name].Value = "--";
                // dgvMeasure.Rows[currentTimes - 1].Cells[custom.Name].Value = value.ToString("f" + WorkCurveHelper.SoftWareContentBit.ToString());
            }

            //设置判定值   20171012  添加XRF判定
            if (WorkCurveHelper.CurrentStandard != null && WorkCurveHelper.CurrentStandard.StandardDatas != null && WorkCurveHelper.CurrentStandard.StandardDatas.Count > 0 && DifferenceDevice.interClassMain.recordList != null && DifferenceDevice.interClassMain.recordList.Count >= currentTimes)
            {
                Dictionary<string, string> DElementRetult = new Dictionary<string, string>();
                string strCustomStandName = string.Empty;
                string strJustValue = ExcelTemplateParams.TestRetultForThick(DifferenceDevice.interClassMain.recordList[currentTimes - 1].ToString(), out strCustomStandName);
                if (strJustValue == ExcelTemplateParams.PassResults)
                {
                    this.dgvMeasure.Rows[currentTimes - 1].Cells[WorkCurveHelper.CurrentStandard.StandardName].Value = ExcelTemplateParams.PassResults;
                    this.dgvMeasure.Rows[currentTimes - 1].Cells[WorkCurveHelper.CurrentStandard.StandardName].Style.ForeColor = Color.Green;
                }
                else if (strJustValue == ExcelTemplateParams.STDResults)
                {
                    this.dgvMeasure.Rows[currentTimes - 1].Cells[WorkCurveHelper.CurrentStandard.StandardName].Value = ExcelTemplateParams.STDResults;
                    this.dgvMeasure.Rows[currentTimes - 1].Cells[WorkCurveHelper.CurrentStandard.StandardName].Style.ForeColor = Color.Green;
                }
                else if (strJustValue == ExcelTemplateParams.FalseResults)
                {
                    this.dgvMeasure.Rows[currentTimes - 1].Cells[WorkCurveHelper.CurrentStandard.StandardName].Value = ExcelTemplateParams.FalseResults;
                    this.dgvMeasure.Rows[currentTimes - 1].Cells[WorkCurveHelper.CurrentStandard.StandardName].Style.ForeColor = Color.Red;
                }

            }

            WorkCurveHelper.testedRows += 1;


            //dgvMeasure.Rows[currentTimes - 1].Cells["AreaDensity"].Value = elementList.AreaDensity.ToString("f" + WorkCurveHelper.ThickBit);
            RefreshStaticsInfo(currentTimes, elementList);
            if (WorkCurveHelper.WorkCurveCurrent != null && this.ucHistoryRecord1 != null && (DifferenceDevice.interClassMain.openSpecFlag
                || (currentTimes == DifferenceDevice.interClassMain.selectSpeclist.Count && !DifferenceDevice.interClassMain.openSpecFlag)) && DifferenceDevice.interClassMain.IsExistHistory)
                //如果包含历史记录表示为最后一次刷新并且保存了历史记录 RoHS中可以不包含
                this.ucHistoryRecord1.LoadRefreshUI(WorkCurveHelper.WorkCurveCurrent.Name);
        }
        public void RefreshStaticsInfo(int currentTimes, ElementList elementList)
        {
            try
            {
                for (int j = 0; j < dgvStatics.Rows.Count; j++)
                {
                    if (dgvStatics.Rows[j].Cells["statColumns"].Value != null && dgvStatics.Rows[j].Cells["statColumns"].Tag != null)
                    {
                        string statColumns = (dgvStatics.Rows[j].Cells["statColumns"].Value.ToString().IndexOf("(") != -1) ?
                            dgvStatics.Rows[j].Cells["statColumns"].Value.ToString().Replace(dgvStatics.Rows[j].Cells["statColumns"].Value.ToString().Substring(dgvStatics.Rows[j].Cells["statColumns"].Value.ToString().IndexOf("(")), "") : dgvStatics.Rows[j].Cells["statColumns"].Value.ToString();
                        double maxValue = 0d;
                        double minValue = 0d;
                        double avaValue = 0d;
                        double sdValue = 0d;
                        string tag = dgvStatics.Rows[j].Cells["statColumns"].Tag.ToString();
                        if (tag.Equals("Content"))
                        {
                            TabControlHelper.CaculateStaticsData(ref minValue, ref maxValue, ref avaValue,
                                                      ref sdValue, dgvMeasure, currentTimes, statColumns, tag);
                            dgvStatics.Rows[j].Cells["MaxValue"].Value = maxValue.ToString("f" + WorkCurveHelper.SoftWareContentBit);
                            dgvStatics.Rows[j].Cells["MinValue"].Value = minValue.ToString("f" + WorkCurveHelper.SoftWareContentBit);
                            dgvStatics.Rows[j].Cells["MeanValue"].Value = avaValue.ToString("f" + WorkCurveHelper.SoftWareContentBit);
                            dgvStatics.Rows[j].Cells["SDValue"].Value = sdValue.ToString("f" + WorkCurveHelper.SoftWareContentBit);
                            dgvStatics.Rows[j].Cells["RSDValue"].Value = (sdValue <= 0 || avaValue <= 0) ? sdValue.ToString("f" + WorkCurveHelper.SoftWareContentBit) : ((sdValue / avaValue) * 100).ToString("f" + WorkCurveHelper.SoftWareContentBit);
                        }
                        else if (tag.Equals("Thick"))
                        {
                            string baseelemName = WorkCurveHelper.WorkCurveCurrent.ElementList.Items.ToList().Find(w => w.LayerNumBackUp == Info.Substrate || w.LayerNumBackUp == "基材" || w.LayerNumBackUp == "Substrate").Caption;

                            if ((FpWorkCurve.thickMode == ThickMode.NiNi || FpWorkCurve.thickMode == ThickMode.NiCuNi || FpWorkCurve.thickMode == ThickMode.NiCuNiFe
                                || FpWorkCurve.thickMode == ThickMode.NiCuNiFe2) && dgvStatics.Rows[j].Cells["statColumns"].Value.ToString().Split('(')[0].ToUpper().Equals("NI2"))
                            {
                                // statColumns = "Fe";
                                statColumns = baseelemName;
                            }
                            TabControlHelper.CaculateStaticsData(ref minValue, ref maxValue, ref avaValue,
                                                      ref sdValue, dgvMeasure, currentTimes, statColumns, tag);
                            dgvStatics.Rows[j].Cells["MaxValue"].Value = maxValue.ToString("f" + WorkCurveHelper.ThickBit);
                            dgvStatics.Rows[j].Cells["MinValue"].Value = minValue.ToString("f" + WorkCurveHelper.ThickBit);
                            dgvStatics.Rows[j].Cells["MeanValue"].Value = avaValue.ToString("f" + WorkCurveHelper.ThickBit);
                            dgvStatics.Rows[j].Cells["SDValue"].Value = sdValue.ToString("f" + WorkCurveHelper.ThickBit);
                            dgvStatics.Rows[j].Cells["RSDValue"].Value = (sdValue <= 0 || avaValue <= 0) ? sdValue.ToString("f" + WorkCurveHelper.ThickBit) : ((sdValue / avaValue) * 100).ToString("f" + WorkCurveHelper.ThickBit);




                        }
                        else if (tag.Equals("AreaDensity"))
                        {
                            //TabControlHelper.CaculateStaticsData(ref minValue, ref maxValue, ref avaValue,
                            // ref sdValue, dgvMeasure, currentTimes, "AreaDensity", tag);statColumns
                            TabControlHelper.CaculateStaticsData(ref minValue, ref maxValue, ref avaValue,
                                   ref sdValue, dgvMeasure, currentTimes, statColumns, tag);
                            dgvStatics.Rows[j].Cells["MaxValue"].Value = maxValue.ToString("f" + WorkCurveHelper.ThickBit);
                            dgvStatics.Rows[j].Cells["MinValue"].Value = minValue.ToString("f" + WorkCurveHelper.ThickBit);
                            dgvStatics.Rows[j].Cells["MeanValue"].Value = avaValue.ToString("f" + WorkCurveHelper.ThickBit);
                            dgvStatics.Rows[j].Cells["SDValue"].Value = sdValue.ToString("f" + WorkCurveHelper.ThickBit);
                            dgvStatics.Rows[j].Cells["RSDValue"].Value = (sdValue <= 0 || avaValue <= 0) ? sdValue.ToString("f" + WorkCurveHelper.ThickBit) : ((sdValue / avaValue) * 100).ToString("f" + WorkCurveHelper.ThickBit);
                        }
                    }
                }
            }
            catch
            { }
        }



        public void UpdateWorkSpec(Skyray.EDXRFLibrary.DeviceParameter deviceParams, Skyray.EDXRFLibrary.Spectrum.SpecListEntity specList)
        {
            //this.dgvWorkSpec["ColumnSpecValue", 0].Value = specList.SampleName;
            //this.dgvWorkSpec["ColumnSpecValue", 1].Value = specList.Supplier;
            //if (specList.Weight.HasValue)
            //    this.dgvWorkSpec["ColumnSpecValue", 2].Value = specList.Weight.Value.ToString("f4");

            //this.dgvWorkSpec["ColumnSpecValue", 3].Value = specList.Shape;
            //this.dgvWorkSpec["ColumnSpecValue", 4].Value = specList.SpecDate.ToString();
            //this.dgvWorkSpec["ColumnSpecValue", 5].Value = deviceParams.PrecTime.ToString();
            //this.dgvWorkSpec["ColumnSpecValue", 6].Value = specList.Operater;
            //this.dgvWorkSpec["ColumnSpecValue", 7].Value = deviceParams.TubCurrent.ToString();
            //this.dgvWorkSpec["ColumnSpecValue", 8].Value = deviceParams.TubVoltage.ToString();
            //this.dgvWorkSpec["ColumnSpecValue", 9].Value = (deviceParams.FilterIdx).ToString();
            //this.dgvWorkSpec["ColumnSpecValue", 10].Value = (deviceParams.CollimatorIdx).ToString();
            //this.dgvWorkSpec["ColumnSpecValue", 11].Value = deviceParams.Condition.InitParam.Channel.ToString();
            //this.dgvWorkSpec["ColumnSpecValue", 12].Value = specList.SpecSummary;
        }

        public void ContructMeasureRefreshData(int count, ElementList elementList)
        {

            if (DifferenceDevice.CurCameraControl.ChkRetest.Checked)
                return;

            string sIsShowBaseMaterial = ReportTemplateHelper.LoadSpecifiedValue("FPThick", "IsShowBaseMaterial");
            this.dgvMeasure.Columns.Clear();
            if (count < 1 || elementList == null || elementList.Items.Count == 0)
                return;
            DataGridViewTextBoxColumn elemColumns = new DataGridViewTextBoxColumn();
            elemColumns.Name = "Count";
            elemColumns.HeaderText = Info.Number;
            elemColumns.ReadOnly = true;
            elemColumns.SortMode = DataGridViewColumnSortMode.NotSortable;
            elemColumns.Width = 75;
            this.dgvMeasure.Columns.Add(elemColumns);
            // var query = from elementl in elementList.Items.ToList().FindAll(w => w.IsShowElement) orderby elementl.LayerNumber group elementl by new { elementl.LayerNumBackUp, elementl.ThicknessUnit };
            var query = from elementl in elementList.Items.ToList().FindAll(w => w.Caption != string.Empty) orderby elementl.LayerNumber group elementl by new { elementl.LayerNumBackUp, elementl.ThicknessUnit };
            foreach (var elementlQuery in query)
            {
                if (elementlQuery.Key.LayerNumBackUp.ToString() == Info.Substrate && sIsShowBaseMaterial.ToString() == "1") continue;
                List<CurveElement> CurveElementlist = elementList.Items.ToList().FindAll(delegate(CurveElement v) { return v.LayerNumBackUp == elementlQuery.Key.LayerNumBackUp && v.ThicknessUnit == elementlQuery.Key.ThicknessUnit; });
                string columnName = string.Empty;
                string headName = string.Empty;
                CurveElementlist.ForEach(ss =>
                {
                    //if (WorkCurveHelper.WorkCurveCurrent.IsThickShowContent)
                    if (ss.IsShowContent && WorkCurveHelper.CalcType != CalcType.PeakDivBase)
                    {
                        elemColumns = new DataGridViewTextBoxColumn();
                        elemColumns.SortMode = DataGridViewColumnSortMode.NotSortable;
                        elemColumns.ReadOnly = true;
                        elemColumns.Name = ss.DefineElemName; //ss.Caption;
                        elemColumns.Tag = "Content";
                        if (ss.ContentUnit.ToString().Equals("per"))
                            headName = "%";
                        else
                            headName = ss.ContentUnit.ToString();
                        if (WorkCurveHelper.WorkCurveCurrent.IsThickShowAreaThick)
                        {
                            //面密度单位
                            string dUnit = Info.strAreaDensityUnit;
                            List<AreaDensityUnit> units = AreaDensityUnit.FindAll();
                            if (units.Find(w => w.Name == WorkCurveHelper.WorkCurveCurrent.AreaThickType) != null)
                                dUnit = WorkCurveHelper.WorkCurveCurrent.AreaThickType;
                            headName = dUnit;
                        }
                        elemColumns.HeaderText = ss.Caption + "(" + headName + ")";
                        elemColumns.Width = 90;

                        dgvMeasure.Columns.Add(elemColumns);
                    }
                    if (ss.IsShowElement)
                        columnName += ss.DefineElemName + "|";
                    // columnName += ss.Caption + "|";
                });
                if (columnName == string.Empty) continue;
                if (WorkCurveHelper.WorkCurveCurrent.IsThickShowAreaThick)
                {
                    string dUnit = Info.strAreaDensityUnit;
                    List<AreaDensityUnit> units = AreaDensityUnit.FindAll();
                    if (units.Find(w => w.Name == WorkCurveHelper.WorkCurveCurrent.AreaThickType) != null) dUnit = WorkCurveHelper.WorkCurveCurrent.AreaThickType;
                    //面密度
                    elemColumns = new DataGridViewTextBoxColumn();
                    elemColumns.Name = (columnName == "") ? "" : columnName.Substring(0, columnName.Length - 1);
                    headName = dUnit;
                    elemColumns.Tag = "AreaDensity";
                    elemColumns.HeaderText = elemColumns.Name + "(" + headName + ")";
                    elemColumns.ReadOnly = true;
                    elemColumns.SortMode = DataGridViewColumnSortMode.NotSortable;
                    elemColumns.Width = 90;
                    this.dgvMeasure.Columns.Add(elemColumns);
                }
                else
                {   //厚度
                    elemColumns = new DataGridViewTextBoxColumn();
                    elemColumns.Name = (columnName == "") ? "" : columnName.Substring(0, columnName.Length - 1);
                    headName = (elementlQuery.Key.ThicknessUnit.ToString().Equals("ur")) ? "u〞" : elementlQuery.Key.ThicknessUnit.ToString();
                    elemColumns.Tag = "Thick";
                    elemColumns.HeaderText = elemColumns.Name + "(" + headName + ")";

                    string baseelemName = WorkCurveHelper.WorkCurveCurrent.ElementList.Items.ToList().Find(w => w.LayerNumBackUp == Info.Substrate || w.LayerNumBackUp == "基材" || w.LayerNumBackUp == "Substrate").Caption;

                    if ((FpWorkCurve.thickMode == ThickMode.NiNi || FpWorkCurve.thickMode == ThickMode.NiCuNi || FpWorkCurve.thickMode == ThickMode.NiCuNiFe
                        || FpWorkCurve.thickMode == ThickMode.NiCuNiFe2 || FpWorkCurve.thickMode == ThickMode.NewNiCuNi) && elemColumns.Name.ToUpper().Equals(baseelemName.ToUpper()))
                        elemColumns.HeaderText = "Ni2" + "(" + headName + ")";


                    elemColumns.ReadOnly = true;
                    elemColumns.SortMode = DataGridViewColumnSortMode.NotSortable;
                    elemColumns.Width = 90;
                    this.dgvMeasure.Columns.Add(elemColumns);


                }

                if (ReportTemplateHelper.IsShowError)
                {
                    var headerCellW = new DataGridViewColumnHeaderCellW();
                    headerCellW.DataSourceType = typeof(Info);
                    headerCellW.FieldName = "strError";
                    headerCellW.Prefix = (columnName == "") ? "" : columnName.Substring(0, columnName.Length - 1);
                    var columnw = new DataGridViewTextBoxColumnW(headerCellW);
                    columnw.Name = (columnName == "") ? "" : columnName.Substring(0, columnName.Length - 1) + "|" + "Error";
                    columnw.ReadOnly = true;
                    columnw.SortMode = DataGridViewColumnSortMode.NotSortable;
                    columnw.Width = 90;
                    columnw.Tag = "Error";
                    this.dgvMeasure.Columns.Add(columnw);
                }

            }
            foreach (var custom in WorkCurveHelper.WorkCurveCurrent.ElementList.CustomFields)
            {
                elemColumns = new DataGridViewTextBoxColumn();
                elemColumns.Name = custom.Name;
                elemColumns.HeaderText = custom.Name;
                elemColumns.ReadOnly = true;
                elemColumns.SortMode = DataGridViewColumnSortMode.NotSortable;
                elemColumns.Width = 90;
                this.dgvMeasure.Columns.Add(elemColumns);
            }
            //elemColumns = new DataGridViewTextBoxColumn();
            //elemColumns.Name = "AreaDensity";
            //elemColumns.Tag = "AreaDensity";
            //elemColumns.HeaderText = Info.strAreaDensity;
            //elemColumns.ReadOnly = true;
            //elemColumns.SortMode = DataGridViewColumnSortMode.NotSortable;
            //elemColumns.Width = 120;
            //this.dgvMeasure.Columns.Add(elemColumns);




            if ((WorkCurveHelper.CurrentStandard != null) && !string.IsNullOrEmpty(WorkCurveHelper.CurrentStandard.StandardName))
            {
                elemColumns = new DataGridViewTextBoxColumn();
                elemColumns.Name = WorkCurveHelper.CurrentStandard.StandardName;
                elemColumns.HeaderText = WorkCurveHelper.CurrentStandard.StandardName;
                elemColumns.ReadOnly = true;
                elemColumns.AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
                elemColumns.SortMode = DataGridViewColumnSortMode.NotSortable;
                this.dgvMeasure.Columns.Add(elemColumns);
            }
            this.dgvMeasure.RowCount = count;


            WorkCurveHelper.testedRows = 0;
            //此处说明已经开始新的测试结果界面
            this.retestIndex = 0;
        }

        public void CreateContructStatis(ElementList elementList)
        {
            this.dgvStatics.Columns.Clear();
            this.dgvStatics.Rows.Clear();
            if (elementList == null || elementList.Items.Count == 0)
                return;
            DataGridViewTextBoxColumn elemColumns = new DataGridViewTextBoxColumn();
            elemColumns.Name = "statColumns".ToString();
            elemColumns.HeaderText = Info.ElementName;
            elemColumns.ReadOnly = true;
            elemColumns.SortMode = DataGridViewColumnSortMode.NotSortable;
            elemColumns.Width = 80;
            this.dgvStatics.Columns.Add(elemColumns);

            string[] staticsHeadText = { Info.MaxValue, Info.MinValue, Info.MeanValue, Info.SDValue };
            elemColumns = new DataGridViewTextBoxColumn();
            elemColumns.Name = "MaxValue";
            elemColumns.HeaderText = Info.MaxValue;
            elemColumns.ReadOnly = true;
            elemColumns.SortMode = DataGridViewColumnSortMode.NotSortable;
            elemColumns.Width = 80;
            this.dgvStatics.Columns.Add(elemColumns);

            elemColumns = new DataGridViewTextBoxColumn();
            elemColumns.Name = "MinValue";
            elemColumns.HeaderText = Info.MinValue;
            elemColumns.ReadOnly = true;
            elemColumns.SortMode = DataGridViewColumnSortMode.NotSortable;
            elemColumns.Width = 80;
            this.dgvStatics.Columns.Add(elemColumns);

            elemColumns = new DataGridViewTextBoxColumn();
            elemColumns.Name = "MeanValue";
            elemColumns.HeaderText = Info.MeanValue;
            elemColumns.ReadOnly = true;
            elemColumns.SortMode = DataGridViewColumnSortMode.NotSortable;
            elemColumns.Width = 80;
            this.dgvStatics.Columns.Add(elemColumns);

            elemColumns = new DataGridViewTextBoxColumn();
            elemColumns.Name = "SDValue";
            elemColumns.HeaderText = Info.SDValue;
            elemColumns.ReadOnly = true;
            elemColumns.SortMode = DataGridViewColumnSortMode.NotSortable;
            elemColumns.Width = 80;
            this.dgvStatics.Columns.Add(elemColumns);

            elemColumns = new DataGridViewTextBoxColumn();
            elemColumns.Name = "RSDValue";
            elemColumns.HeaderText = Info.RSDValue;
            elemColumns.ReadOnly = true;
            elemColumns.SortMode = DataGridViewColumnSortMode.NotSortable;
            elemColumns.Width = 100;
            this.dgvStatics.Columns.Add(elemColumns);

            var query = from elementl in elementList.Items.ToList().FindAll(w => w.IsShowElement) orderby elementl.LayerNumber group elementl by new { elementl.LayerNumBackUp, elementl.ThicknessUnit };


            this.dgvStatics.RowCount = query.Count() > 0 ? query.Count() : 1;



            //if (WorkCurveHelper.WorkCurveCurrent.IsThickShowAreaThick)
            //    this.dgvStatics.RowCount += query.Count();

            //if (WorkCurveHelper.WorkCurveCurrent.IsThickShowContent)
            //this.dgvStatics.RowCount += elementList.Items.ToList().FindAll(w => w.IsShowElement && w.IsShowContent).Count + 1;
            //this.dgvStatics.RowCount += elementList.Items.ToList().FindAll(w => w.IsShowElement && w.IsShowContent).Count;
            this.dgvStatics.RowCount += elementList.Items.ToList().FindAll(w => w.IsShowContent).Count;
            query = from elementl in elementList.Items.ToList().FindAll(w => w.Caption != string.Empty) orderby elementl.LayerNumber group elementl by new { elementl.LayerNumBackUp, elementl.ThicknessUnit };
            int j = 0;
            foreach (var elementlQuery in query)
            {
                string unit_h = string.Empty;
                string unit = string.Empty;
                string caption = string.Empty;
                unit = (elementlQuery.Key.ThicknessUnit.ToString().Equals("ur")) ? "u〞" : elementlQuery.Key.ThicknessUnit.ToString();
                List<CurveElement> CurveElementlist = elementList.Items.ToList().FindAll(delegate(CurveElement v) { return v.LayerNumBackUp == elementlQuery.Key.LayerNumBackUp && v.ThicknessUnit == elementlQuery.Key.ThicknessUnit; });

                CurveElementlist.ForEach(ss =>
                {
                    if (ss.IsShowElement)
                        caption += ss.DefineElemName + "|";
                    //  caption += ss.Caption + "|";
                    //if (WorkCurveHelper.WorkCurveCurrent.IsThickShowContent)
                    if (WorkCurveHelper.CalcType != CalcType.PeakDivBase)
                    {
                        if (ss.IsShowContent)
                        {
                            unit_h = string.Empty;
                            unit_h = (ss.ContentUnit.ToString().Equals("per")) ? "%" : ss.ContentUnit.ToString();
                            dgvStatics.Rows[j].Cells["statColumns"].Value = ss.DefineElemName + "(" + unit_h + ")";// ss.Caption + "(" + unit_h + ")";
                            dgvStatics.Rows[j].Cells["statColumns"].Tag = "Content";
                            j++;
                        }
                    }
                });

                if (caption == string.Empty) continue;
                if (WorkCurveHelper.WorkCurveCurrent.IsThickShowAreaThick)
                {
                    string dUnit = Info.strAreaDensityUnit;
                    List<AreaDensityUnit> units = AreaDensityUnit.FindAll();
                    if (units.Find(w => w.Name == WorkCurveHelper.WorkCurveCurrent.AreaThickType) != null) dUnit = WorkCurveHelper.WorkCurveCurrent.AreaThickType;

                    dgvStatics.Rows[j].Cells["statColumns"].Value = (caption == "") ? "" : caption.Substring(0, caption.Length - 1) + "(" + dUnit + ")";
                    dgvStatics.Rows[j].Cells["statColumns"].Tag = "AreaDensity";
                    j++;
                }
                else
                {

                    string baseelemName = WorkCurveHelper.WorkCurveCurrent.ElementList.Items.ToList().Find(w => w.LayerNumBackUp == Info.Substrate || w.LayerNumBackUp == "基材" || w.LayerNumBackUp == "Substrate").Caption;

                    dgvStatics.Rows[j].Cells["statColumns"].Value = (caption == "") ? "" : caption.Substring(0, caption.Length - 1) + "(" + unit + ")";
                    if ((FpWorkCurve.thickMode == ThickMode.NiNi || FpWorkCurve.thickMode == ThickMode.NiCuNi || FpWorkCurve.thickMode == ThickMode.NiCuNiFe
                        || FpWorkCurve.thickMode == ThickMode.NiCuNiFe2 || FpWorkCurve.thickMode == ThickMode.NewNiCuNi) && caption.Substring(0, caption.Length - 1).ToUpper().Equals(baseelemName.ToUpper()))
                        dgvStatics.Rows[j].Cells["statColumns"].Value = "Ni2" + "(" + unit + ")";


                    dgvStatics.Rows[j].Cells["statColumns"].Tag = "Thick";
                    j++;
                }

                #region 备注
                //this.dgvStatics.RowCount = 2 * elementList.Items.Count;
                //int j = 0;
                //for (int i = 0; i < elementList.Items.Count; i++)
                //{
                //    string unit = string.Empty;
                //    if (elementList.Items[i].ThicknessUnit.ToString().Equals("ur"))
                //        unit = "u〞";
                //    else
                //        unit = elementList.Items[i].ThicknessUnit.ToString();
                //    dgvStatics.Rows[j].Cells["statColumns"].Value = elementList.Items[i].Caption + "(" + unit + ")";
                //    j++;
                //    if (elementList.Items[i].ContentUnit.ToString().Equals("per"))
                //        unit = "%";
                //    else
                //        unit = elementList.Items[i].ContentUnit.ToString();
                //    dgvStatics.Rows[j].Cells["statColumns"].Value = elementList.Items[i].Caption + "(" + unit + ")";
                //    j++;
                //}
                #endregion
            }



            //this.dgvStatics.RowCount += 1;
            //dgvStatics.Rows[dgvStatics.RowCount - 1].Cells["statColumns"].Value = Info.strAreaDensity;
            //dgvStatics.Rows[dgvStatics.RowCount - 1].Cells["statColumns"].Tag = "AreaDensity";
        }
        #endregion

        private int retestIndex = 0;

        private void dgvMeasure_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0)
                return;

            if (retestIndex == 0)
            {
                WorkCurveHelper.testIds.Clear();

                DbObjectList<HistoryRecord> records = HistoryRecord.FindRecent(this.dgvMeasure.RowCount);
                foreach (var his in records)
                    WorkCurveHelper.testIds.Add(his.Id);
                WorkCurveHelper.testIds.Sort();
            }
            retestIndex = e.RowIndex + 1;


            if (DifferenceDevice.CurCameraControl.skyrayCamera1.alTempTestPoints.Count > 0
                            && DifferenceDevice.CurCameraControl.buttonWStart.Enabled && !WorkCurveHelper.goingToDest
                            )
            {
                WorkCurveHelper.goingToDest = true;


                //首先确定第一行测试记录在alTemp中的起始点序号
                int startIndex = WorkCurveHelper.contiOffsetInTemp;
                int num = e.RowIndex / WorkCurveHelper.testParamsBackup.MeasureParams.MeasureNumber;
                MotorOperator.getZ();

                int destHeight = DifferenceDevice.CurCameraControl.skyrayCamera1.alContiTestHeights[startIndex + num];
                if (DifferenceDevice.CurCameraControl.skyrayCamera1.Mode == SkyrayCamera.CameraMode.Multiple)
                {
                    MotorOperator.MotorOperatorZThread((int)WorkCurveHelper.Z - destHeight);
                }

                MotorOperator.getXY();
                Point srcPoint = new Point((int)WorkCurveHelper.X, (int)WorkCurveHelper.Y);
                Point destPoint = (Point)DifferenceDevice.CurCameraControl.skyrayCamera1.alTempTestPoints[startIndex + num];
                int distanceX = srcPoint.X - destPoint.X;
                int distanceY = destPoint.Y - srcPoint.Y;
                MotorOperator.MotorOperatorXYThread(distanceX, distanceY);
            }

        }

        private void FrmThick_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (WorkCurveHelper.AskToClose)
            {
                if (DialogResult.OK != Msg.Show(Info.IsExitApplication, MessageBoxButtons.OKCancel, MessageBoxIcon.Warning))
                {
                    e.Cancel = true;
                    //修改： 何晓明 20100714 软件关闭时几率性dgvDevice.RowCount=0
                    timer.Enabled = true;
                    //
                    return;
                }
            }
            try
            {
                DifferenceDevice.interClassMain.deviceMeasure.interfacce.port.CloseVoltage();
                DifferenceDevice.interClassMain.deviceMeasure.interfacce.port.CloseVoltageLamp();
                DifferenceDevice.interClassMain.deviceMeasure.Stop();
                DifferenceDevice.interClassMain.messageProcess.localMesage.Clear();
                DifferenceDevice.interClassMain.messageProcess.cancle = true;
                if (cameral != null)
                    cameral.Close();
                WorkCurveHelper.specMessage.cancle = true;
                //BackupHelper.UnRegisterFileChange();
                //BackupHelper.ApplicationEndCopyData();

                if (e.CloseReason == CloseReason.UserClosing)
                {
                    string strFilePath = AppDomain.CurrentDomain.BaseDirectory + "UI.xml";
                    XmlHelper.GenerateXmlFile(strFilePath);
                    XmlDocument doc = new XmlDocument();
                    doc.Load(strFilePath);
                    //XmlHelper.RecordContainerValue(doc, this.Name, "containerObject2", containerObject2);
                    //XmlHelper.RecordContainerValue(doc, this.Name, "containerObject6", containerObject6);
                    //XmlHelper.RecordContainerValue(doc, this.Name, "containerObject3", containerObject3);

                    XmlHelper.RecordContainerValue(doc, this.Name, "containerCamer1", ucCameraControl1.containerCamer1);
                    XmlHelper.RecordContainerValue(doc, this.Name, "containercamer2", ucCameraControl1.containercamer2);
                    XmlHelper.RecordContainerValue(doc, this.Name, "splitContainer1", splitContainer1);
                    XmlHelper.RecordContainerValue(doc, this.Name, "splitContainer2", splitContainer2);
                    XmlHelper.RecordContainerValue(doc, this.Name, "splitContainer3", splitContainer3);
                    XmlHelper.RecordContainerValue(doc, this.Name, "splitContainer4", splitContainer4);
                    XmlHelper.RecordContainerValue(doc, this.Name, "splitContainer5", splitContainer5);
                    XmlHelper.RecordContainerValue(doc, this.Name, "splitContainerMotor", ucCameraControl1.splitContainerMotor);
                    //  XmlHelper.RecordContainerValue(doc, this.Name, "splitContainerCamer", ucCameraControl1.splitContainerCamer);  
                    XmlHelper.RecordContainerValue(doc, this.Name, "splitContainerHistory", ucHistoryRecord1.splitContainerHistory);  

                    doc.Save(strFilePath);
                }
            }
            catch (Exception ex)
            {
                Msg.Show(ex.Message);
                Log.Error("关闭窗体[Thick]时发生异常: " + ex.ToString());
            }
            finally
            {
                if (DifferenceDevice.interClassMain.deviceMeasure.interfacce.port != null)
                    DifferenceDevice.interClassMain.deviceMeasure.interfacce.port.Disconnect();
                if (DifferenceDevice.interClassMain.deviceMeasure.deviceThread != null)
                    DifferenceDevice.interClassMain.deviceMeasure.deviceThread.Abort();
                DifferenceDevice.interClassMain.deviceMeasure.interfacce.KillThread(true);
                DifferenceDevice.interClassMain.messageProcess.excuteThead.Abort();
                DifferenceDevice.interClassMain.deviceMeasure.interfacce.KillExe("Skyray.NewProcessBar");
                DifferenceDevice.interClassMain.deviceMeasure.interfacce.ExitCOMThread();

                System.Environment.Exit(0);

            }

        }

        private void FrmThick_Shown(object sender, EventArgs e)
        {


            // timer.Enabled = true;
            Skyray.Language.Lang.Model.LangObj.Add(new LangInfo
            {
                IsForm = false,
                PropertyNames = new string[] { "Text" },

                ObjToChangeLang = new object[] 
            { 
                WorkCurveHelper.NaviItems ,
                UCHistoryRecord.AutoDic,
                this.statusStripW1.Items
            }
            });
            Skyray.Language.Lang.Model.LangObj.Add(new LangInfo
            {
                IsForm = true,
                PropertyNames = Skyray.Language.Param.PropertyNames,
                ObjToChangeLang = DifferenceDevice.interClassMain.skyrayCamera
            });

            Skyray.Language.Lang.Model.DGVS.Add(this.dgvStatics);
            Skyray.Language.Lang.Model.DGVS.Add(this.dgvMeasure);

            Skyray.Language.Lang.Model.RegistDGVColAddedEvent();

            if (Skyray.Language.Lang.Model.CheckToSaveText()) Skyray.Language.Lang.Model.SaveAllText();

            if (!Skyray.Language.Param.SaveTextToDB)
            {
                Skyray.Language.Lang.Model.ChangeLanguage();
            }
            ////AutoBackupHelper.sVersion = "Thick";
            ////AutoBackupHelper.StartProbeProcess();
            ////WorkCurveHelper.Ewh.Set();
            //BackupHelper.StartProbeProcess();

            //if (cameral != null)
            //{   
            //    cameral.Open();
            //}
            FrmLoad.Close();
            // WorkCurveHelper.deviceMeasure.interfacce.IsDropTime = true; 
            // DifferenceDevice.interClassMain.ConnectDevice();
            Skyray.EDXRFLibrary.SurfaceSourceLight ss = Skyray.EDXRFLibrary.SurfaceSourceLight.FindAll()[0];
            if (ss != null)
                ucCameraControl1.SetScorllValue = ss.FirstLight;
            if (WorkCurveHelper.IsResetMotor && WorkCurveHelper.DeviceCurrent.HasMotorX && WorkCurveHelper.DeviceCurrent.HasMotorY && WorkCurveHelper.DeviceCurrent.HasMotorZ && DifferenceDevice.interClassMain.deviceMeasure.interfacce.port.ConnectState)
            {
                ucCameraControl1.MotorReset();
            }
        }

        private void FrmThick_Activated(object sender, EventArgs e)
        {
            DifferenceDevice.interClassMain.deviceMeasure.interfacce.RegisterHoeKeys();
        }

        private void FrmThick_Leave(object sender, EventArgs e)
        {
            DifferenceDevice.interClassMain.deviceMeasure.interfacce.UnRegisterHotKeys();
        }

        protected override void WndProc(ref Message m)
        {
            const int WM_HOTKEY = 0x0312;
            //const int WM_DEVICECHANGE = 0x219;
            //修改： 何晓明 20100714 软件关闭时几率性dgvDevice.RowCount=0
            const int WM_SYSTEMCOMMAND = 0x0112;
            const int SC_CLOSE = 0xF060;
            //
            switch (m.Msg)
            {
                case WM_HOTKEY:
                    if (DifferenceDevice.interClassMain.deviceMeasure.interfacce.connect == DeviceConnect.DisConnect)
                    {
                        switch (m.WParam.ToInt32())
                        {
                            case 200:
                                //NewWorkSpec newSpec = new NewWorkSpec(DifferenceDevice.interClassMain.currentSelectMode);
                                //WorkCurveHelper.OpenUC(newSpec, false, Info.Start);
                                if (NewWorkSpec.signObject == null)
                                {
                                    //NewWorkSpec newSpec = new NewWorkSpec(DifferenceDevice.interClassMain.currentSelectMode);
                                    NewWorkSpec newSpec = NewWorkSpec.GetInstance(DifferenceDevice.interClassMain.currentSelectMode);
                                    WorkCurveHelper.OpenUC(newSpec, false, Info.Start, true);
                                }
                                break;
                            case 300:
                                DifferenceDevice.interClassMain.TestInitalize(true, false, false, 0);
                                //DifferenceDevice.uc.ExcutePrint(null);
                                break;
                            case 400:
                                DifferenceDevice.MediumAccess.ExcuteAutoDemarcateEnergy();
                                break;
                            case 500:
                                EDXRFHelper.LoadLoadSourceEvent();
                                EDXRFHelper.DirectPrint();
                                break;

                        }
                    }
                    break;
                //case WM_DEVICECHANGE:
                //    if (WorkCurveHelper.DeviceCurrent.ComType != ComType.USB)
                //        return;
                //    if (DifferenceDevice.interClassMain.deviceNameList != null && DifferenceDevice.interClassMain.deviceNameList.Count > 0 && DifferenceDevice.IsExitUsb)
                //    {
                //        HardwareClass hc = new HardwareClass();
                //        foreach (string str in DifferenceDevice.interClassMain.deviceNameList)
                //        {
                //            if (DifferenceDevice.interClassMain == null)
                //                continue;
                //            DifferenceDevice.IsExitUsb = false;
                //        }
                //    }
                //    break;
                //修改： 何晓明 20100714 软件关闭时几率性dgvDevice.RowCount=0
                case WM_SYSTEMCOMMAND:
                    if ((int)m.WParam == SC_CLOSE)
                    {
                        timer.Enabled = false;
                    }
                    break;

                case DeviceInterface.CUSTOM_MESSAGE: //处理消息
                    ShowWindow(FindWindow(null, "ProcessBox"), 1);

                    break;
                case DeviceInterface.CUSTOM_MESSAGE_HIDE:
                    ShowWindow(FindWindow(null, "ProcessBox"), 0);
                    //IntPtr findPtr = FindWindow(null, "Thick");

                    SetForegroundWindow(this.Handle);
                    break;
                //
            }
            base.WndProc(ref m);
        }
        [System.Runtime.InteropServices.DllImport("user32.dll", EntryPoint = "SetForegroundWindow")]
        public static extern bool SetForegroundWindow(IntPtr hWnd);//设置此窗体为活动窗体

        [DllImport("User32.dll", EntryPoint = "FindWindow")]
        private static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        [DllImport("user32.dll", EntryPoint = "ShowWindow", SetLastError = true)]
        static extern bool ShowWindow(IntPtr hWnd, uint nCmdShow);
        private void FrmThick_Load(object sender, EventArgs e)
        {
            try
            {
                string strFilePath = AppDomain.CurrentDomain.BaseDirectory + "UI.xml";
                XmlDocument doc = new XmlDocument();
                doc.Load(strFilePath);
                //XmlHelper.SetContainerValue(doc, this.Name, "containerObject2", containerObject2);
                //XmlHelper.SetContainerValue(doc, this.Name, "containerObject6", containerObject6);
                //XmlHelper.SetContainerValue(doc, this.Name, "containerObject3", containerObject3);
                XmlHelper.SetContainerValue(doc, this.Name, "containerCamer1", ucCameraControl1.containerCamer1);
                XmlHelper.SetContainerValue(doc, this.Name, "containercamer2", ucCameraControl1.containercamer2);

                XmlHelper.SetContainerValue(doc, this.Name, "splitContainer1", splitContainer1);
                XmlHelper.SetContainerValue(doc, this.Name, "splitContainer2", splitContainer2);
                XmlHelper.SetContainerValue(doc, this.Name, "splitContainer3", splitContainer3);
                XmlHelper.SetContainerValue(doc, this.Name, "splitContainer4", splitContainer4);
                XmlHelper.SetContainerValue(doc, this.Name, "splitContainer5", splitContainer5);
                XmlHelper.SetContainerValue(doc, this.Name, "splitContainerMotor", ucCameraControl1.splitContainerMotor);

                // XmlHelper.SetContainerValue(doc, this.Name, "splitContainerCamer", ucCameraControl1.splitContainerCamer); 

                //  XmlHelper.SetContainerValue(doc, this.Name, "containerObject8", containerObject8);


                //读取计算精度
                //string strPar=ReportTemplateHelper.LoadSpecifiedValue("SoftWareCaculate", "ContentBit");
                //try
                //{
                //    WorkCurveHelper.SoftWareContentBit =Convert.ToInt32(strPar);
                //}
                //catch
                //{
                //    WorkCurveHelper.SoftWareContentBit =4;
                //}

                //strPar=ReportTemplateHelper.LoadSpecifiedValue("SoftWareCaculate", "ThickBit");
                //try
                //{
                //    WorkCurveHelper.ThickBit =Convert.ToInt32(strPar);
                //}
                //catch
                //{
                //    WorkCurveHelper.ThickBit =4;
                //}


            }
            catch
            { }
        }


        #region IRefreshFillInfo 成员


        public void RefreshWorkRegion()
        {
            //throw new NotImplementedException();
        }

        #endregion

        private void FrmThick_Deactivate(object sender, EventArgs e)
        {
            DifferenceDevice.interClassMain.deviceMeasure.interfacce.UnRegisterHotKeys();
        }

        #region IRefreshFillInfo 成员


        public void RefreashExploreReport(DataGridViewW dataGrid, string AuK)
        {
            //throw new NotImplementedException();
        }

        public void SaveExcel()
        {


        }

        public void PrintExcel()
        {


        }

        #endregion

        private void FrmThick_SizeChanged(object sender, EventArgs e)
        {
            FormWindowState state = this.WindowState;
            if (state != FormWindowState.Minimized)
                DifferenceDevice.interClassMain.grobleState = state;
        }
        #region IRefreshFillInfo 成员


        public void Exist()
        {
            this.Close();
        }

        #endregion

        public void LogOut()
        {
            bool ChangeUser = bool.Parse(ReportTemplateHelper.LoadSpecifiedParamsValue(AppDomain.CurrentDomain.BaseDirectory + "AppParams.xml", "application/ChangeUser"));
            if (ChangeUser)
            {

                FrmAdminPass temp = new FrmAdminPass();
                temp.ShowDialog();
                if (WorkCurveHelper.AdminPass)
                {

                    System.Diagnostics.Process.Start(Application.ExecutablePath);
                    System.Diagnostics.Process.GetCurrentProcess().Kill();
                    Application.Exit();//退出当前项目，如果是子项目，则不会停止主项目
                    System.Environment.Exit(0);//停止所有项目
                }
                else
                    ReportTemplateHelper.SaveSpecifiedParamsValue(AppDomain.CurrentDomain.BaseDirectory + "AppParams.xml", "application/ChangeUser", false.ToString());
                    


            }
            else 
            {
              
                if (DialogResult.Yes == Msg.Show(Info.IsLogOut, MessageBoxButtons.YesNo, MessageBoxIcon.Question))
                {
                    System.Diagnostics.Process.Start(Application.ExecutablePath);

                    System.Diagnostics.Process.GetCurrentProcess().Kill();
                    Application.Exit();//退出当前项目，如果是子项目，则不会停止主项目
                    System.Environment.Exit(0);//停止所有项目
                }

                


            }
        }

        #region IRefreshFillInfo 成员


        public void RefreshHistory()
        {
            this.ucHistoryRecord1.LoadRefreshUI(WorkCurveHelper.WorkCurveCurrent.Name);

            foreach (Form child in Application.OpenForms)
            {
                var control = child.Controls[0];
                // if (control is UCHistoryRecordSplitScreen)
                if (control is UCHistoryRecord)
                {
                    if (WorkCurveHelper.WorkCurveCurrent != null)
                    {
                        //UCHistoryRecordSplitScreen ucHistoryRecord1 = control as UCHistoryRecordSplitScreen;
                        UCHistoryRecord ucHistoryRecord1 = control as UCHistoryRecord;
                        ucHistoryRecord1.LoadRefreshUI(WorkCurveHelper.WorkCurveCurrent.Name);
                    }
                }
            }
        }

        public void RefreshStartStatus(bool visibled)
        {
        }
        public void RefreshChinawareResult(string strChiawareInfo, string strCentainty, List<HistoryElement> elementlist)
        {

        }
        #endregion

        private void tbControlMain_Selected(object sender, TabControlEventArgs e)
        {
            if (e.TabPageIndex == 2 && WorkCurveHelper.WorkCurveCurrent != null && this.ucHistoryRecord1 != null)
                this.ucHistoryRecord1.LoadRefreshUI(WorkCurveHelper.WorkCurveCurrent.Name);
        }

        public void PrintBlueExcel()
        { }

        /// <summary>
        /// 加载显示所有曲线
        /// </summary>
        public void LoadAllWorkCruve()
        {
            if (WorkCurveHelper.DeviceCurrent != null)
            {
                var deviceId = WorkCurveHelper.DeviceCurrent.Id;
                string sql = "select * from WorkCurve where Condition_Id in (select Id from condition where Type = 0 and Device_id = "
                    + deviceId + ") and FuncType=" + (int)WorkCurveHelper.DeviceFunctype + " and IsShowMain=1 order by LOWER(Name)";

                lstWorkCurve = WorkCurve.FindBySql(sql);
            }
            else
            {
                lstWorkCurve = WorkCurve.FindAll();
            }
            this.dgvWorkCurve.Rows.Clear();

            int current = 0;
            for (int i = 0; i < lstWorkCurve.Count; i++)
            {
                string CruveNameAll = (lstWorkCurve[i].RemarkName == string.Empty || lstWorkCurve[i].RemarkName == null || lstWorkCurve[i].RemarkName == "") ? lstWorkCurve[i].Name : lstWorkCurve[i].Name + "(" + lstWorkCurve[i].RemarkName + ")";
                this.dgvWorkCurve.Rows.Add(CruveNameAll);
                if (lstWorkCurve[i].Name == WorkCurveHelper.WorkCurveCurrent.Name)
                    current = i;
            }

            this.dgvWorkCurve.ClearSelection();
            if (dgvWorkCurve.Rows.Count > 0)
            {
                lblShowWorkCurveName.Text = Info.CurrentWorkCurve + WorkCurveHelper.WorkCurveCurrent.Name;
                dgvWorkCurve.Rows[current].Selected = true;

                string CurveName = WorkCurveHelper.WorkCurveCurrent.Name;
                if (CurveName.StartsWith("Ni-Cu-Ni-")) CurveName = "Ni-Cu-Ni-New";
                switch (CurveName)
                {
                    //case "Ni-Cu-Ni-FeNdB":
                    //    FpWorkCurve.thickMode = ThickMode.NiNi;
                    //    break;
                    case "NiP-Fe":
                        FpWorkCurve.thickMode = ThickMode.NiP;
                        break;
                    case "Coating":
                        FpWorkCurve.thickMode = ThickMode.Plating;
                        break;
                    //case "Ni-Cu-Ni-Mag":
                    //    FpWorkCurve.thickMode = ThickMode.NiCuNi;
                    //    break;
                    //case "Ni-Cu-Ni-Fe":
                    //    //case "Ag-Ni-Cu-Ni-Fe":
                    //    //case "Sn-Ni-Cu-Ni-Fe":
                    //    //case "Au-Ni-Cu-Ni-Fe":
                    //    FpWorkCurve.thickMode = ThickMode.NiCuNiFe;
                    //    break;
                    case "Ni-Cu-Ni-New":
                        FpWorkCurve.thickMode = ThickMode.NewNiCuNi;
                        break;
                    case "Ag-Ni-Cu-Ni-Fe":
                    case "Sn-Ni-Cu-Ni-Fe":
                    case "Au-Ni-Cu-Ni-Fe":
                        FpWorkCurve.thickMode = ThickMode.NiCuNiFe2;
                        break;
                    default:
                        FpWorkCurve.thickMode = ThickMode.Normal;
                        break;
                }
                if (WorkCurveHelper.WorkCurveCurrent.IsNiP2 && WorkCurveHelper.WorkCurveCurrent.Condition.DeviceParamList.Count > 1)
                {
                    FpWorkCurve.thickMode = ThickMode.NiP2;
                }

            }
        }

        private void ucCameraControl1_DoubleClick(object sender, EventArgs e)
        {
            if (DifferenceDevice.IsThick)
            {

            }
        }

        private void dgvWorkCurve_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (lstWorkCurve.Count <= 0) return;

            WorkCurveHelper.WorkCurveCurrent = lstWorkCurve[dgvWorkCurve.SelectedRows[0].Index];
            WorkCurveHelper.CalcType = WorkCurveHelper.WorkCurveCurrent.CalcType;
            lblShowWorkCurveName.Text = Info.CurrentWorkCurve + WorkCurveHelper.WorkCurveCurrent.Name;
            DifferenceDevice.MediumAccess.OpenCurveSubmit();
            DifferenceDevice.MediumAccess.RefreshHistory();
        }

        private bool bIsValueAverage(ElementList elements)
        {
            bool returnRows = false;
            int rows = WorkCurveHelper.HistoryAverageRows - 1;
            if (DifferenceDevice.interClassMain.listHistoryElement.Count / elements.Items.Count >= 1 && rows > 1)
                returnRows = true;
            return returnRows;
        }

        private void splitContainer3_Panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void dgvWorkSpec_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

    }
}
