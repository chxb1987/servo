#ifndef		__GLOBAL_VARIABLES_
#define		__GLOBAL_VARIABLES_

int adcCurrentA;
int adcCurrentB;
int adcVdc;

// pmsmCtrl.c
Uint16 encoderMaxCount;

double inv_encoderMaxCount;
double inv_QepTime;
int32 POSCNT_old;

double POS_REF;
double POS_REAL;
double POS_REAL_delay1;
double POS_ERR;
double POS_REF_OFFSET;
double SPEED_REF;
double SPEED_REAL;
double SPEED_ERR;

double MAX_SPEED;


double uspeed_kp;
double speed_err_ki;
double speed_err_ki_delay1;
double speed_anti_windup;
double uspeed_ki;
double uspeed_ki_delay1;
double uspeed_IP;
double torque_real;

double ud_kp;
double ud_ki;
double ud_ki_delay1;
double ud_IP;
double Id_err;
double Id_err_delay1;
double Id_real;
double Id_ref;
double Id_err_ki;
double Id_err_ki_delay1;
double d_current_anti_windup;

double uq_kp;
double uq_ki;
double uq_ki_delay1;
double uq_IP;
double Iq_err;
double Iq_err_delay1;
double Iq_ref;
double Iq_err_ki;
double Iq_err_ki_delay1;
double q_current_anti_windup;
double Vq_real;

double Torque_MAX;
double ACC_MAX;             //  = 4.2;

Uint16 enc_flag=1;

double POS_REF_OLD;
double POS_REF_NEW;
double POS_INIT;
double prof_t1;
double prof_t2;
double prof_t3;
double profile_gen_time;        //  =1000000000.0;
int profile_FLAG;
int SIGN_FLAG;
int cal_FLAG ;
double Dist_New;
double Dist_min;
double init_t1;
double init_t2;
double SPEED_M;

double SPD_REF_PLC;

Uint16 POS_INIT_FLAG;


// testing
int lpfadcIa;
int lpfadcIb;

double exSensRef;

double dAdcIa;
double dAdcIb;
double dAdcVdc;
double dAdcTemp;
double dAdcSens;
double dAdcCmd;

double * scopePoint[50];

// control and flag
CODE_INFO code_inform = {0,0,0,0,0,0,{0}};
union PROTECT_FLAG protect_reg;
union DIGITAL_FUNCTION func_flag;
union DIGITAL_OUT_FUNC relay_flag;
TRIP_INFO TripInfo = {0,0,0,0,0," No Trip Data       "};
TRIP_INFO TripInfoNow = {0,0,0,0,0," No Trip Data       "};
int terminal_input_state;
char MonitorMsg[25]={0};

// flag
int init_charge_flag = 0;
int gRunFlag=0;
int gTripFlag = 0;
int gTripSaveFlag=0;
int gTripSavePoint;
int gPWMTripCode;
int Flag_TripDataBackup = 0;
int EepromSaveFlag = 0;

int gMachineState=0;
int gControlMode;
int gDeChargeFlag;

int sendAdcDataFlag;
int scopeCount=0;

UNION16 scopeData[4][SCOPE_MAX_NUMBER];

// reference
double  reference_in=0.0;
double  reference_out=0.0;
double  analog_ref;
double  AnaCmdReference=0;
double  IncScanRef=0.0;
double  IncRef=0.0;
double  DecRef=0.0;

// count and time

int     timer0_count;
Uint16  MAX_PWM_CNT;
double  inv_MAX_PWM_CNT;
Uint16  DutyCount[3];
double  DutyRatio[3];
double  GainUpdateTimer;

double  Ts;
double  inv_Ts;
double  gfRunTime=0;
double  ref_time;
unsigned long   gulStartCount;
unsigned int    gStartInitFinish;

// frequency
double  P_pair;
double  inv_P_pair;

double  Freq_rat;
double  inv_Freq_rat;
double  inv_motor_rate_hz;
double  Freq_ref=0.0;
double  Freq_set=0.0;
double  frequency=0.0;
double  Freq_out=0.0;

double  Freq_slip_rat;
double  Freq_slip=0.0;

double  rpmOut;
double  rpm=0.0;
double  rpm_ref=0.0;
double  rpm_err=0.0;
double  rpm_Coeff;
double  rpm_m=0.0;

// angle
double  we_rat;
double  we=0.0;
double  we0=0.0;
double  we_in=0.0;
double  we_FW=0.0;
double  we_FW1=0.0;

int     wr_ctrl_index   = 1;
int     wr_CycleIndex   = 0;
double  wr=0.0;
double  wr_rat;
double  wr_ref=0.0;
double  wr_ref0=0.0;
double  wr_err=0.0;
double  wr_ErrInt=0.0;

double  wr_Cycle=0.0;
double  w_sl=0.0;
double  w_sl0=0.0;
double  Delta_wr_Filter_Pole=0.0;
double  Delta_wr=0.0;

double  wm_rat;
double  wr_m=0.0;
double  wr_m0=0.0;

double  theta=0.0;
double  theta_m=0.0;
double  SinTheta=0.0;
double  CosTheta=1.0;
double  SinTheta1=0.0;
double  CosTheta1=0.0;
double  SinDeltaTheta=0.0;
double  CosDeltaTheta=0.0;
double  SinCosDeltaTheta=0.0;
double  inv_SinCosDeltaTheta=0.0;
double  DeltaLambda=0.0;
double  DeltaTheta=0.0;

// Current
double  OverCurLimit;
double  Is_rat;
double  inv_Is_rat;
double  Is_max;
double  Is_mag;
double  LPF_Ia;
double  Is_mag_rms;
double  sgn_Is[3]={0.0,0.0,0.0};
double  sgn_I_QS=0.0;

double  Is_abc[3];
double  Is_dq[2];
double  Is_dq_ref[2]={0.0,0.0};
double  Is_dq_ErrInt[2]={0.0,0.0};

double  Is_DQ[2]={0.0,0.0};
double  Is_DQ_ref[2]={0.0,0.0};
double  Is_DQ_max[2]={0.0,0.0};
double  Is_DQ_ErrInt[2]={0.0,0.0};
double  prev_I_QS=0.0;
double  I_DS0=0.0;
double  I_DS0_0=0.0;
double  I_DS_err=0.0;
double  Is_Leq_Req;

// Voltage
double  Vs_rat;
double  Vdc;
double  Vs_ref=0.0;
double  sensVdc;
double  Vdc_factor;          // 2010 01 13
double  Vdc_calc_offset;     // 2010 01 13 for Vdc calc
double  Vs_Coeff_Leq_Req;

double  Vs_abc_ref[3];
double  Vs_abc[3];
double  Us_dq[2];
double  Vs_dq[2];
double  Vs_DQ[2];

double  Vs_max=0.0;
double  Vs_abc[3]={0.0,0.0,0.0};
double  Vs_abc_ref[3]={0.0,0.0,0.0};
double  Vs_dq[2]={0.0,0.0};
double  Vs_dq_ref[2]={0.0,0.0};
double  Vo=0.0;                 // zero sequence
double  Us_dq[2]={0.0,0.0};
double  Vs_DQ[2]={0.0,0.0};
double  Vs_DQ_max[2]={0.0,0.0};
double  Vs_DQ_ref[2]={0.0,0.0};
double  Vs_DQ_comp[2]={0.0,0.0};
double  Vs_max_FW=0.0;
double  Vs_DQ_ref_P[2]={0.0,0.0};
double  Vs_DQ_ref_PI[2]={0.0,0.0};
double  Vs_IR_comp=0.0;
double  del_Vs_comp=0.0;


// power and torque

double Te_rat;
double inv_Te_rat;
double Kt;
double inv_Kt;
double S_lin;
double S_rat;
double  Pf=0.0;
double  Slip=0.0;
double  Power_core=0.0;
double  Power_core_rat=0.0;
double  Power_gap=0.0;

double  Re_Power=0.0;
double  Im_Power=0.0;
double  P_total;

double	Te_max=0.0;
double	Te_ref=0.0;
double	Te=0.0;
double	LPF_Te=0.0;
double	Max_Trq_Coeff=0.0;


// Flux
double  Fs_rat;
double  Fs_ref=0.0;
double  Fs_ref0=0.0;
double  inv_Fs_ref=0.0;
double  Fs=0.0;
double  inv_Fs=0.0;
double  Fs_dq[2]={0.0,0.0};
double  Fs1=0.0;

double  Fr=0.0;
double  inv_Fr=0.0;
double  Fr_ref=0.0;
double  inv_Fr_ref=0.0;
double  Fr_ref0=0.0;
double  Fr_Err=0.0;
double  Fr_ErrInt=0.0;

// Dead Time
double 	C_ce_nF;
double 	C_ce;
double 	inv_C_ce;

// Motor Name Plate Parameter

double  inv_motor_rat_hz;
double  wr_rat;
double  wm_rat;
double  Te_rat;
double  inv_Te_rat;
double  Fs_rat;
double  Fr_rat;
double  Kt;
double  inv_Kt;
double  P_pair;
double  inv_P_pair;
double  rpm_Coeff;

// Machine Parameter
double  sigma;
double  sigma_Ls;
double  SlipCoeff;
double  inv_sigma_Tr;
double  sigma_Tr;
double  sigma_minus_1_div_sigma_Ls;
double  inv_sigma_Ls;
double  inv_Ls;
double  Tr;
double  inv_Tr;
double  inv_Ls_plus_sigma_Ls;               // ��� ���Ѱ� ���
double  sigma_Ls_div_1_plus_sigma;          // ��� ���Ѱ� ���
double  Lm_div_Lr;                      // Lm/Lr
double  Lr_div_Lm;                      // Lr/Lm

// Vector Control with/out sensor
double  wn_wr;
double  I_QS_rat;
double inv_I_QS_rat;

// V/F
double  S_rat;
double  S_lin;
double  Freq_slip_rat;

double  Kp_wr;
double  Ki_wr;

double  Fs_B;
double  inv_Fs_B;

double  wr_FilterPole;

unsigned AutoTuningFlag=0;

double  Jm_SampleData[2]={0.0,0.0};
double  Jm_ID_wr[4]={0.0,0.0,0.0,0.0};
double  Jm_ID_Te[4]={0.0,0.0,0.0,0.0};
double  Jm_ID_t[4]={0.0,0.0,0.0,0.0};

double  Req;
double  Leq;

double  GainUpdateTimer;
double  Vs_Coeff_Leq_Req;

double LPF_Is;
double LPF_Is_Square;
double LPF_Vs_Square;
double LPF_Re_Power;

double  Is_Leq_Req;
double Freq_rat;
double inv_Freq_rat;

// Sci.c
int scib_rx_msg_flag = 0;
int scic_rx_msg_flag = 0;

int scia_tx_start_addr=0;
int scia_tx_end_addr=0;
int scia_rx_msg_flag = 0;

char gStr1[50] = {0};
char gStr2[10] = {0};

int gSciInFlag;

char gSciaRxBuf[NUM_SCI_RX_BUF+1];
char gSciaTxBuf[NUM_SCI_TX_BUF+1];

int	gSciaTxInPoint;
int	gSciaTxOutPoint;
int	gSciaTxEndFlag;

int giSciCmdFunction;
int giSciCmdAddr;
double gdouSciCmdData;

// analog to digital converter
int adc_result[6]={0};
int adcIa;
int adcIb;
int adcVdc;
int adcIgbtTemperature;
int adcExSensor;
int adcCmdAnalog;

//filter
double lpfIa;
double lpfIb;

double lpfIrmsCutOffRreq = 1.0;
double lpfIaIn[3];
double lpfIaOut[3];
double lpfIrmsK[4];
//double lpfIrmsCutOffRreq = 1.0;
double lpfIbIn[3];
double lpfIbOut[3];

double lpfVdc;
double lpfVdcCutoffFreq = 1000.0;
double lpfVdcIn[3];
double lpfVdcOut[3];
double lpfVdcK[4];

//============================================
//   CODE variable 
//============================================
double   codeMotorDirection;     // 1
double   codeAccelTime1;         // 2
double   codeDecelTime1;         // 3
double   codeMotorCtrlMode;      // 4
double   code_start_ref;         // 5
double   codeSpeed1;             // 6
double   codeSetVdc;             // 7
double   codeProtectOff;         // 8
double   codePwmFreq;            // 9

double   codeRatePower;          // 10
double   codeRateCurrent;        // 11
double   codeRateRpm;            // 12
double   codeRateEffiency;       // 13
double   codeRateHz;             // 14
double   codeRateVolt;           // 15
double   codeMotorPole;          // 16
double   codePresSensRef;        // 17

double   codeIaOffset;           // 20
double   codeIbOffset;           // 21

double I_sense_value;           // 22
double u_phase_I_sense_span;    // 24
double v_phase_I_sense_span;    // 26
double vdc_sense_zero;          // 27
double vdc_sense_span;          // 28

double code_adc_Vdc_low;        // 36
double code_adc_Vdc_high;       // 37
double code_Vdc_calc_low;       // 38
double code_Vdc_calc_high;      // 39

// group6
double VF_DeadTimeGain;         // 40
double VF_ExcitationTime;       // 41
double VF_Fs_Coeff;             // 42
double VF_Freq_TrqBoost;        // 43
double VF_Vs_Coeff_TrqBoost;    // 44
double VF_Rs_ThermalCoeff;      // 45
double VF_IR_Comp_FilterPole;   // 46
double VF_Slip_Comp_FilterPole; // 47
double VF_Rs;                   // 48

double code_kpPosi;
double code_kpSpeed;
double code_kiSpeed;
double code_kpIdq;
double code_kiIdq;
double code_encoderPulse;

double codeScopeLoopCount;

double codeScopePointCh1;
double codeScopeScaleCh1;
double codeScopeOffsetCh1;

double codeScopePointCh2;
double codeScopeScaleCh2;
double codeScopeOffsetCh2;

double codeScopePointCh3;
double codeScopeScaleCh3;
double codeScopeOffsetCh3;

double codeScopePointCh4;
double codeScopeScaleCh4;
double codeScopeOffsetCh4;

// end of code
double invCodeScopeScaleCh1;
double invCodeScopeScaleCh2;
double invCodeScopeScaleCh3;
double invCodeScopeScaleCh4;

int scopeLoopCount;
int scopePointCh1;
int scopePointCh2;
int scopePointCh3;
int scopePointCh4;

double over_speed_level;		// 303
double e_thermal_level;			// 304
double pre_charge_time;			// 305
double over_I_time;				// 307

double code_Vdc_scaler;			// 308  2011.0613
double code_Vdc_offseter;		// 309

double Data_Check;				// 800
double Data_Backup;				// 801
double Data_Load;				// 802
double Data_Init;				// 803
#endif


