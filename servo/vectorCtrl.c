#include	<header.h>
#include	<extern.h>

int vectorCtrlLoop()
{
	int LoopCtrl,temp;
	int iTripCode=0;

	int iCommand;
	double fReference;

	commonVariableInit();
	iTripCode = HardwareParameterVerification();
	if( iTripCode !=0 ) return iTripCode;

	iTripCode = SL_SPEED_CNTL_Parameter();        
	if( iTripCode != 0)	return iTripCode;			// debug


	temp = (int)(floor(codeMotorCtrlMode+0.5));
	if( temp == 4 ) wr_FilterPole=Default_wr_FilterPole; // torque mode

	IER &= ~M_INT3;      // debug for PWM
	InitEPwm_ACIM_Inverter(); 	// debug
	EPwm1Regs.ETSEL.bit.INTEN = 1;    		            // Enable INT
	IER |= M_INT3;      // debug for PWM

	gRunFlag =1;
    strncpy(MonitorMsg," RUN ",20);
	gfRunTime = 0.0; 
	LoopCtrl = 1;		

    gMachineState = STATE_INIT_RUN;
	
	while(LoopCtrl == 1)
	{
		if(gPWMTripCode != 0){
			iTripCode = gPWMTripCode; LoopCtrl = 0;
			break;
		}		
		get_command(&iCommand,&fReference);
		monitor_proc();

		// if( iCommand == CMD_START)      reference_in = fReference;
		if( iCommand == CMD_STOP)  reference_in = 0.0;

		switch( gMachineState )
		{
        case STATE_RUN:
            strncpy(MonitorMsg," RUN ",20);
			if		 (  iCommand == CMD_NULL ) 			ramp_proc( reference_in, &reference_out);
            else if(( iCommand == CMD_SPEED_UP1   ) && (reference_in <  3.0  )) reference_in += 0.01;
            else if(( iCommand == CMD_SPEED_UP   ) && (reference_in <  3.0  )) reference_in += 0.1;
			else if(( iCommand == CMD_SPEED_DOWN ) && ( reference_in > 0.01 )) reference_in -= 0.1;
			else if(  iCommand == CMD_STOP ) { 
				reference_in = 0.0; gMachineState = STATE_GO_STOP;
			}
			else if(  iCommand == CMD_START ) ramp_proc( reference_in, &reference_out);
			else{
				reference_in = 0.0; gMachineState = STATE_GO_STOP;
			}
			break;

		case STATE_GO_STOP:
			if( iCommand == CMD_START ) {
				strncpy(MonitorMsg,"RUN ",20);
				gMachineState = STATE_RUN;
				reference_in = fReference; 
			}				
			else if( fabs( reference_out ) < 0.01 ){
				strncpy(MonitorMsg,"READY ",20);
				gMachineState = STATE_READY;
			    commonVariableInit();
				LoopCtrl =0;
			}
			else{
 				reference_in = 0.0;
				ramp_proc(reference_in, &reference_out);
			}
			break;
		}
	}
	return iTripCode;
}


