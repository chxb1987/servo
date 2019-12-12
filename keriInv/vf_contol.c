#include	<header.h>
#include	<extern.h>

int vf_loop_control(double cmd_ref)
{
	int LoopCtrl;
	int trip_code=0;
	int command;
	double ref_in0;

//	simple_scalar_control_variable_init();

	commonVariableInit();
	trip_code = HardwareParameterVerification();
	reference_in = cmd_ref;

	if( trip_code !=0 ) return trip_code;

	IER &= ~M_INT3;      // debug for PWM
	InitEPwm_ACIM_Inverter(); 	// debug
	EPwm1Regs.ETSEL.bit.INTEN = 1;    		            // Enable INT
	IER |= M_INT3;      // debug for PWM

	gRunFlag =1;
	strncpy(MonitorMsg,"INIT_RUN",20);
	gfRunTime = 0.0; 
	LoopCtrl = 1;		
	gMachineState = STATE_INIT_RUN;

	while(LoopCtrl == 1)
	{
		Nop();
		trip_code = trip_check();
		if( trip_code !=0 ){
		    LoopCtrl = 0;
		}
		get_command( & command, & ref_in0);	            //
		// if( command == CMD_START ) reference_in = ref_in0;

		switch( gMachineState )
		{
		case STATE_INIT_RUN:
			if( command == CMD_STOP){
                strncpy(MonitorMsg,"READY",20); gMachineState = STATE_READY; LoopCtrl= 0;
		    } else if( gfRunTime < 0.2 ){
				Freq_ref=0.0;	rpm_ref=0.0; reference_out = 0.0;
			} else{
				strncpy(MonitorMsg,"RUN",20);
				    gMachineState = STATE_RUN;
				    reference_out = code_start_ref;
				    reference_in = code_start_ref;
			}
			break;
		case STATE_RUN:
			if( command == CMD_NULL ){
			    ramp_proc(reference_in, & reference_out);
			} else if( command == CMD_STOP ) {
				strncpy(MonitorMsg,"GO_STOP",20); gMachineState = STATE_GO_STOP; reference_in = 0.0;
			} else if( command == CMD_SPEED_UP ){
				reference_in += 0.05;
				if( reference_in > 3.0 ) reference_in = 3.0;
			} else if( command == CMD_SPEED_DOWN ){
				reference_in -= 0.05;
				if( reference_in < -3.0 ) reference_in = -3.0;
			} else if( command == CMD_START ){
				ramp_proc(reference_in, & reference_out);
			}
			break;
		case STATE_GO_STOP:
			if( command == CMD_START ) {
				strncpy(MonitorMsg,"RUN",20); gMachineState = STATE_RUN;
				// reference_in = reference_out; 
			} else if ((fabs(reference_out) <= code_start_ref )){
                strncpy(MonitorMsg,"READY",20);
                gMachineState = STATE_READY;
                reference_out = Freq_out = 0.0;
                commonVariableInit( );
                LoopCtrl = 0;
			} else {
				reference_in = 0.0;
				ramp_proc(reference_in, &reference_out);
			}
			break;
		}
	}
	return trip_code;
}		

void vf_simple_control()
{
    Freq_out = codeRateHz * reference_out;
    // rpm_Coeff = 60.0 * inv_P_pair / PI_2;
    we = PI_2 * Freq_out;
    rpm = rpm_Coeff * we;   //  rpm = rpm_Coeff * wr

    theta += we * Ts;       //회전방향 변환 정방향을때 +, 역방향회전일때 - 해줄것

    if (theta>PI)       theta-=PI_2;
    else if (theta<-PI) theta+=PI_2;

    SinTheta = sin(theta);
    CosTheta = cos(theta);


    if( reference_out > 1.0 ){
        Vs_ref = fabs( Vs_rat / reference_out );// debug 2019.1002
    } else {
        Vs_ref = fabs( Freq_out / codeRateHz * Vs_rat );
    }

    Vs_dq_ref[ds] = Vs_ref * CosTheta;
    Vs_dq_ref[qs] = Vs_ref * SinTheta;

    Is_DQ[DS] =  CosTheta * Is_dq[ds] + SinTheta * Is_dq[qs];
    Is_DQ[QS] = -SinTheta * Is_dq[ds] + CosTheta * Is_dq[qs];
    Vs_DQ[DS] =  CosTheta * Vs_dq[ds] + SinTheta * Vs_dq[qs];
    Vs_DQ[QS] = -SinTheta * Vs_dq[ds] + CosTheta * Vs_dq[qs];

/*
    Is_DQ[DS] =  CosTheta * 1.0;
    Is_DQ[QS] = SinTheta * 1.0;
    Vs_DQ[DS] =  CosTheta * 300.0;
    Vs_DQ[QS] =  SinTheta * 300.0;
*/
}


void slip_comp_scalar_ctrl()
{
   double   Es_m;
   double   sgn_freq;
   double   Det_slip;            // sqrt()�븞�쓽 遺��샇寃��궗
   double   Det_emf;

   // �쟾�븬 異붿젙�떆 �떆媛꾩��뿰(Ts)�쓣 蹂댁긽
   CosDeltaTheta=cos(we*Ts);
   SinDeltaTheta=sin(we*Ts);
   Us_dq[ds]=Vs_dq[ds]*CosDeltaTheta + Vs_dq[qs]*SinDeltaTheta;
   Us_dq[qs]=-Vs_dq[ds]*SinDeltaTheta + Vs_dq[qs]*CosDeltaTheta;
   Vs_dq[ds]=Us_dq[ds];
   Vs_dq[qs]=Us_dq[qs];

   // 二쇳뙆�닔 紐낅졊
//   if ( gfRunTime < gExcitationTime)      // DC �뿬�옄 ==> Flux Setup
   if( gMachineState == STATE_INIT_RUN){
      Freq_ref = Freq_out= reference_out= we = theta = SinTheta=0.0;
      CosTheta=1.0;
      Vs_ref = VF_Vs_Coeff_TrqBoost * Vs_rat;
   }
   else
   {
      Freq_ref = Freq_rat * reference_out;
      if (Freq_ref > VF_Freq_TrqBoost)
      {
         // 二쇳뙆�닔�쓽 遺��샇
         if (Freq_ref >= 0.0)   sgn_freq =  1.0;
         else                  sgn_freq = -1.0;

         // �뒳由� 蹂댁긽
         Slip = fabs(Freq_slip)*inv_Freq_rat;
         Power_core_rat = codeRatePower*(1.0-codeRateEffiency/(1.0-S_rat))-1.5*Is_rat*Is_rat*VF_Rs;
         Power_core=0.5*( (1.0+Slip)/(1+S_rat)*(Freq_out*inv_Freq_rat) + (1.0+Slip*Slip)/(1.0+S_rat*S_rat)*(Freq_out*inv_Freq_rat)*(Freq_out*inv_Freq_rat) )*Power_core_rat;
         LPF1(Ts,VF_Slip_Comp_FilterPole,1.5*(Vs_dq[ds]*Is_dq[ds]+Vs_dq[qs]*Is_dq[qs] - VF_Rs_ThermalCoeff*VF_Rs*Is_mag*Is_mag)-Power_core,&Power_gap);
         Det_slip = Freq_ref*Freq_ref + S_lin*Power_gap;

         if (Det_slip < 0.0)
               LPF1(Ts,VF_Slip_Comp_FilterPole,-0.5*sqrt(fabs(S_lin*Power_gap)),&Freq_slip);
         else   LPF1(Ts,VF_Slip_Comp_FilterPole,0.5*(sqrt(Det_slip)-fabs(Freq_ref)),&Freq_slip);

         // �뒳由� �젣�븳
         if (Freq_slip>2.0*Freq_slip_rat)         Freq_slip=2.0*Freq_slip_rat;
         else if (Freq_slip<-2.0*Freq_slip_rat)   Freq_slip=-2.0*Freq_slip_rat;

         Freq_out=Freq_ref + sgn_freq*Freq_slip;

      }
      else
      {
         Freq_out=Freq_ref;
         Power_gap=0.0;
         Freq_slip=0.0;
      }

      we=PI_2*Freq_out;
      theta+=we*Ts;

      if (theta>PI)         theta-=PI_2;
      else if (theta<-PI)   theta+=PI_2;

      SinTheta=sin(theta);      CosTheta=cos(theta);

      Vs_max=0.57735*Vdc;
      Es_m=VF_Fs_Coeff*fabs(Freq_out)*inv_Freq_rat*Vs_rat;
      if (Es_m>Vs_max)   Es_m=Vs_max;

      Is_DQ[DS]= CosTheta*Is_dq[ds] + SinTheta*Is_dq[qs];
      Is_DQ[QS]=-SinTheta*Is_dq[ds] + CosTheta*Is_dq[qs];

      Det_emf=(Es_m*Es_m)-(VF_Rs*Is_DQ[QS])*(VF_Rs*Is_DQ[QS]);  //sqrt�븞�쓽 �쓬�닔�뿬遺�議곗궗
      if ( (Det_emf>0.0) && (fabs(Freq_out)>VF_Freq_TrqBoost) )
            LPF1(Ts,VF_IR_Comp_FilterPole,0.9*(VF_Rs*Is_DQ[DS]+sqrt(Det_emf)-Es_m),&Vs_IR_comp);
      else   LPF1(Ts,VF_IR_Comp_FilterPole,VF_Vs_Coeff_TrqBoost*Vs_rat,&Vs_IR_comp);

      // �쟾瑜� �젣�븳湲�
      if (Is_mag>Is_max)
      {
         del_Vs_comp=(2.0*Vs_rat*inv_Is_rat)*(Is_mag-Is_max);

         if (del_Vs_comp>0.2*Vs_rat)         del_Vs_comp=0.2*Vs_rat;
         else if (del_Vs_comp<-0.2*Vs_rat)   del_Vs_comp=-0.2*Vs_rat;
      }
      else   del_Vs_comp=0.0;

      // 理쒖쥌 �쟾�븬 紐낅졊
      Vs_ref = Es_m + Vs_IR_comp - del_Vs_comp;      // IR蹂댁긽, �쟾瑜섑겕湲� �젣�븳
      if (Vs_ref>Vs_max)   Vs_ref=Vs_max;
   }
   // 異쒕젰 �쟾�븬
   Vs_dq_ref[ds]=Vs_ref*CosTheta + VF_DeadTimeGain*(Vs_dq_ref[ds]-Vs_dq[ds]);
   Vs_dq_ref[qs]=Vs_ref*SinTheta + VF_DeadTimeGain*(Vs_dq_ref[qs]-Vs_dq[qs]);

   rpm = 60 * Freq_out * inv_P_pair ;
}
// End of file.
