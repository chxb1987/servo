#include	<header.h>
#include	<extern.h>
/*
int COMMON_VECT_CNTL_ParameterVerification()
{
    double  In;         // ������ ���� ���

    // ���� �Ķ���� ����
    if ( (Rs<2.0e-3) || (Rs>20.0) )
        return  CODE_Rs;
    if ( (Rr<2.0e-3) || (Rr>20.0) )
        return  CODE_Rr;

    // �δ��Ͻ� : 1.0e-3*mH -> H
    Ls=1.0e-3*Ls_mH;
    Lr=1.0e-3*Lr_mH;
    Lm=1.0e-3*Lm_mH;

    if ( (Ls<2.0e-3) || (Ls>1.0) )
        return  CODE_Ls_mH;
    if ( (Lr<2.0e-3) || (Lr>1.0) )
        return  CODE_Lr_mH;
    if ( (Lm<2.0e-3) || (Lm>1.0) )
        return  CODE_Lm_mH;
    if ( (Lm>(0.985*Ls)) || (Lm>(0.985*Lr)) )
        return  CODE_Lm_mH;

    // �δ��Ͻ�(Ls, Lr)�� ����
    In=Vs_rat/(we_rat*Ls);                              // ������ ���� ���
    if ( (In<(0.1*Is_rat)) || (In>(0.8*Is_rat)) )       // ������ ������ ���������� 10% ~ 80%�� �ƴ� ���
        return  CODE_Ls_mH;

    if ( (Lr<(0.9*Ls)) || (Lr>(1.1*Ls)) )
        return  CODE_Lr_mH;

    // ������
    Tr=Lr/Rr;
    if ( (Tr<0.02) || (Tr>2.0) )                        // ������ : 0.02 ~ 2.0��
        return  ERR_Tr_Over;

    // ������ ����
    if ( (Rs<(0.5*Rr)) || (Rs>(20.0*Rr)) )
        return  CODE_Rs;

    // ���� �δ��Ͻ��� ����
    sigma_Ls=Ls-(Lm*Lm)/Lr;
    sigma=sigma_Ls/Ls;
    if (sigma<0.02)
            return  ERR_sigma_Under;                    // �����ڼ��� �۰� ������ ���
    else if (sigma>0.2)
            return  ERR_sigma_Over;                     // �����ڼ��� ũ�� ������ ���

    // ��Ÿ �Ķ���� ���
    inv_Tr=1.0/Tr;
    inv_Ls=1.0/Ls;
    inv_Lm=1.0/Lm;
    SlipCoeff=Ls/Tr;
    sigma_Tr=sigma*Tr;
    inv_sigma_Tr=1.0/sigma_Tr;
    sigma_minus_1_div_sigma_Ls=(sigma-1.0)/sigma_Ls;
    inv_sigma_Ls=1.0/sigma_Ls;
    inv_Ls_plus_sigma_Ls=1.0/(sigma_Ls+Ls);             // ���� ���Ѱ� ���
    sigma_Ls_div_1_plus_sigma=sigma_Ls/(1.0+sigma);     // ���� ���Ѱ� ���
    Lm_div_Lr=Lm/Lr;
    Lr_div_Lm=Lr/Lm;

    // ���������
    if ( (K_Damp_Is<0.1) || (K_Damp_Is>1.0) )
        return  CODE_K_Damp_Is;
    if ( (PM_Is<(PI/20.0)) || (PM_Is>(5.0*PI/12.0)) )
        return  CODE_PM_Is;
    if ( (GM_Is<2.5) || (GM_Is>10.0) )
        return  CODE_GM_Is;

    // ���� ����� ����
    inv_GM_Is_square_minus_1=1.0/(GM_Is*GM_Is-1.0);         // 1.0/(GM*GM-1.0)
    inv_GM_Is=1.0/GM_Is;
    wp_Is_Coeff=(GM_Is*PM_Is+PI_1_2*GM_Is*(GM_Is-1.0))*inv_GM_Is_square_minus_1;
    Kp_Is_Coeff=sigma_Ls*inv_GM_Is;

    wp_Is=wp_Is_Coeff*inv_Ts;                   // Td_Is=Ts
    Kp_Is=Kp_Is_Coeff*wp_Is;
    Ki_Is=Kp_Is*(2.0*wp_Is-inv_PI_1_4*wp_Is*wp_Is*Ts+(Rs+Rr)*inv_sigma_Ls);

    if (Ki_Is<=10.0)
        return  ERR_Ki_Is_Under;            // ��������� ���� ����
    if (Kp_Is>Ki_Is)
        return  ERR_Kp_Is_Over;
    else if (Kp_Is<0.0)
        return  ERR_Kp_Is_Under;


    // �Ķ���� ������ ����.
    return  0;
}
*/

int COMMON_S_VECT_CNTL_ParameterVerification()
{
    int ErrCode;

    // ������� �ʿ��� �Ķ���͸� �а� �����Ѵ�.
    ErrCode=COMMON_VECT_CNTL_ParameterVerification();
    if (ErrCode!=0)
        return  ErrCode;


    // ���ڵ� �Ķ����
    if (code_encoderPulse < 50) return  CODE_EncoderPulse;

    ROTOR_ANGLE_PER_PULSE = PI_2/(4.0*code_encoderPulse);             // 4ä�� => �Ѱ��� �޽��� ��谢 ������


    if ( (Default_wr_FilterPole<20.0) || (Default_wr_FilterPole>500.0) )
        return  CODE_Default_wr_FilterPole;
    wr_FilterPole=Default_wr_FilterPole;                    // �ӵ� �������� ���� ��


    //  �ڼ������ ����    �� ����� ��������
    if ( (Fr_CntlPeriodIndex<1) || (Fr_CntlPeriodIndex>30) )
        return  CODE_Fr_CntlPeriodIndex;
    if ( (FW_VoltageCoeff<0.2) || (FW_VoltageCoeff>1.2) )           // ����� ���� ���� ���
        return  CODE_FW_VoltageCoeff;
    if ( (Base_Flux_Coeff<0.1) || (Base_Flux_Coeff>2.5) )               // Base Flux < 250%
        return  CODE_Base_Flux_Coeff;
    if ( (ExcitationTime<0.1) || (ExcitationTime>3.0) )
        return  CODE_ExcitationTime;

    if ( (K_Damp_Fr<0.0) || (K_Damp_Fr>1.0) )
        return  CODE_K_Damp_Fr;
    if ( (GM_Fr<2.5) || (GM_Fr>25.0) )
        return  CODE_GM_Fr;
    if ( (PM_Fr<(PI/12.0)) || (PM_Fr>(5.0*PI/12.0)) )
        return  CODE_PM_Fr;

    Fr_rat=sqrt(Fs_rat*Fs_rat-0.75*0.75*sigma_Ls*sigma_Ls*Is_rat*Is_rat)/(Lm/Lr+sigma_Ls/Lm);
    Fr_B=Base_Flux_Coeff*Fr_rat;
    inv_Fr_B=1.0/Fr_B;
    Fr_ref=Fr_B;
    HalfExcitationTime=0.5*ExcitationTime;

    // ����� ���� ���ļ�
    we_FW_Coeff = 1.0/  sqrt(Ls*Ls*(Fr_B/Lm)*(Fr_B/Lm)+sigma_Ls*sigma_Ls*(Is_max*Is_max-(Fr_B/Lm)*(Fr_B/Lm))) ;
    we_FW1_Coeff = sqrt((Ls*Ls+sigma_Ls*sigma_Ls)/(2.0*Ls*Ls*sigma_Ls*sigma_Ls))/Is_max ;

    // �ڼ� �����
    inv_GM_Fr_square_minus_1=1.0/(GM_Fr*GM_Fr-1.0);     // 1.0/(GM*GM-1.0)
    inv_GM_Fr=1.0/GM_Fr;
    wp_Fr_Coeff=(GM_Fr*PM_Fr+PI_1_2*GM_Fr*(GM_Fr-1.0))*inv_GM_Fr_square_minus_1;
    Kp_Fr_Coeff=(Tr/Lm)*inv_GM_Fr;

    wp_Fr=wp_Fr_Coeff/(Fr_CntlPeriodIndex*Ts);          // Td_Is=(Fr_CntlPeriodIndex*Ts)
    Kp_Fr=Kp_Fr_Coeff*wp_Fr;
    Ki_Fr=Kp_Fr*(2.0*wp_Fr-inv_PI_1_4*wp_Fr*wp_Fr*(Fr_CntlPeriodIndex*Ts)+Tr);

    if (Ki_Fr<=1.0e-6)
        return  ERR_Ki_Fr_Under;                        // �ڼ������ ���� ����


    // �Ķ���� ������ ����.
    return  0;
}


// �������� ��ũ��� �ʿ��� �Ķ����
int S_TORQUE_CNTL_Parameter()
{
    int ErrCode;

    // ������� �ʿ��� �Ķ���͸� �а� �����Ѵ�.
    ErrCode=COMMON_S_VECT_CNTL_ParameterVerification();
    if (ErrCode!=0)
        return  ErrCode;

    // �Ķ���� ������ ����.
    return  0;
}


// �������� �ӵ���� �ʿ��� �Ķ����
int S_SPEED_CNTL_Parameter()
{
    int ErrCode;

    // ������� �ʿ��� �Ķ���͸� �а� �����Ѵ�.
    ErrCode=COMMON_S_VECT_CNTL_ParameterVerification();
    if (ErrCode!=0)
        return  ErrCode;

    // �ӵ������
    if ( (wr_CntlPeriodIndex<1) || (wr_CntlPeriodIndex>30) )
        return  CODE_wr_CntlPeriodIndex;

    if ( (K_Damp_wr<0.05) || (K_Damp_wr>1.0) )
        return  CODE_K_Damp_wr;

    if ( (wr_DampingRatio<0.6) || (wr_DampingRatio>1.5) )
        return  CODE_wr_DampingRatio;

    if ( (wr_FilterPoleCoeff<5.0) || (wr_FilterPoleCoeff>30.0) )
        return  CODE_wr_FilterPoleCoeff;

    if ( (wn_wr_Coeff<2.0) || (wn_wr_Coeff>30.0) )
        return  CODE_wn_wr_Coeff;

    if ( (Max_wn_wr<(2.0*PI*0.5)) || (Max_wn_wr>(2.0*PI*20.0)) )
        return  CODE_Max_wn_wr;

    if ( (Jm<0.0001) || (Jm>300.0) )
        return  CODE_Jm;

    //  �ӵ������ ����
    inv_Te_rat=1.0/Te_rat;

    wn_wr=wn_wr_Coeff*( (P_pair*Te_rat/wr_rat)/Jm );    // speed rising time=(P/2.0)*(Te_rat/wr_rat)/Jm
    if (wn_wr>Max_wn_wr)    wn_wr=Max_wn_wr;    // max_wn_wr*10.0 ==> measurement noise cutoff frequency

    wr_FilterPole=wr_FilterPoleCoeff*wn_wr;         // �ӵ� �������� ���� ��
    Kp_wr=(Jm*2.0*wr_DampingRatio*wn_wr)*(Lr_div_Lm*inv_Kt/Fr_B);
    Ki_wr=(Jm*wn_wr*wn_wr)*(Lr_div_Lm*inv_Kt/Fr_B);

    // �Ķ���� ������ ����.
    return  0;
}

void S_SpeedCntl_RFO()
{
	double 	IntegralLimit;
	
	// �ӵ� ���� : ���ڴ� ���
	wr=wr_m0;
	
	// �ӵ�����
	wr_ref=wr_rat * reference_out;
	
	wr_CycleIndex++;
	wr_Cycle+=Ts;
	if (wr_CycleIndex>=wr_CntlPeriodIndex)
	{
		wr_err=wr_ref-wr;
		wr_ErrInt+=Ki_wr*wr_err*inv_P_pair*wr_Cycle;
		IntegralLimit=Kp_wr*fabs(K_Damp_wr*wr_ref-wr)*inv_P_pair + Is_DQ_max[QS];
		if (wr_ErrInt>IntegralLimit)	
			wr_ErrInt=IntegralLimit;
		else if (wr_ErrInt<-IntegralLimit)	
			wr_ErrInt=-IntegralLimit;

		// Q-�� ���� ���	
		Is_DQ_ref[QS]=Kp_wr*(K_Damp_wr*wr_ref-wr)*inv_P_pair+wr_ErrInt;
		
		// �ʱ� �ڼ������ÿ��� �ӵ�������� ���б⸦ ������� �ʴ´�.
		if (gfRunTime<0.05)
			wr_ErrInt=0.0;
		
		wr_Cycle=0.0;
		wr_CycleIndex=0;
	}	
	
	// Q-�� ���� ��� => ������� ���� ��������
	S_VectCntl_RFO();	
}

void S_TorqueCntl_RFO()
{
	// ��ũ Ref.
	Te_ref=Te_rat*reference_out;
	inv_Fr_ref=1.0/Fr_ref;
	Is_DQ_ref[QS]=(inv_Kt*Lr_div_Lm)*(Te_ref*inv_Fr_ref);
	
	// Q-�� ���� ��� => ������� ���� ��������
	S_VectCntl_RFO();	
}


//***********************************************************

// Indirect Rotor Flux Oriented Vector Control with Sensor
void S_VectCntl_RFO()
{	
	double	I_DS_FW2;
	
	// �ִ� ��� ���� 
	Vs_max=0.57735*Vdc;
	
	// �ӵ� ���� : ���ڴ� ���
	wr=wr_m0;
	
	//*****************************************
	
	//���� �� ������  ��ǥ��ȯ : ���ܰ��� ������ ���  
	Is_DQ[DS] = CosTheta*Is_dq[ds] + SinTheta*Is_dq[qs];
	Is_DQ[QS] = -SinTheta*Is_dq[ds] + CosTheta*Is_dq[qs];
	
	// ȸ���� �ڼ� ����
	Fr += inv_Tr*(Lm*Is_DQ[DS]-Fr)*Ts;
	
	// ������� : ����� �ڼ��� ������ �Ŀ� ������ �߻���Ų��.
	if (Fr>(0.01*Fr_B))
	{
		inv_Fr=1.0/Fr;
		w_sl=(Lm*Is_DQ[QS])*(inv_Tr*inv_Fr);
	}		
	else
	{
		inv_Fr=1.0/(0.01*Fr_B);	
		w_sl=inv_Tr*Lm*Is_DQ[QS]*inv_Fr;	
	}		
	
	w_sl0+=250.0*(w_sl-w_sl0)*Ts;
	wr_m0 = wr_m; // debug ���͸� ������ ��
	;
	we=wr_m+w_sl;
	we0=wr_m0+w_sl0;				// ���� ���ļ��� ���͸�
	
	// ���� ���� : ���͸��� ���ļ��� ����ϸ� �ȵȴ�.
	theta += we*Ts;
	
	if (theta>PI)		theta-=PI_2;
	else if (theta<-PI)	theta+=PI_2;
	CosTheta=cos(theta + we0*Ts);
	SinTheta=sin(theta + we0*Ts);

	//******************************************************************
	
	// ȸ���� �ڼ� �������� : �ڼ� ���� ���� ==> ����� ����, Q-�� ���� ���� ���� �����ȴ�.
	Vs_max = 0.57735*Vdc;													// 1.0/sqrt(3.0)=0.57735027
	Vs_max_FW += 50.0*(FW_VoltageCoeff*(Vs_max-Rs*Is_max) - Vs_max_FW)*Ts;		// DC���� ������ �����ϴ� 60Hz �ڸո�� ������� ���� ������ ���͸� �Ѵ�.	
	
	we_FW=we_FW_Coeff *Vs_max_FW;    	// <==  1.0/  sqrt(Ls*Ls*(Fr_B/Lm)*(Fr_B/Lm)+sigma_Ls*sigma_Ls*(Is_max*Is_max-(Fr_B/Lm)*(Fr_B/Lm)))  * Vs_max_FW
	we_FW1=we_FW1_Coeff *Vs_max_FW;  	// <==  sqrt((Ls*Ls+sigma_Ls*sigma_Ls)/(2.0*Ls*Ls*sigma_Ls*sigma_Ls))/Is_max * Vs_max_FW
		
	if (gfRunTime<0.05)
	{
		Fr_ref=Fr_B;
		Is_DQ_max[DS]=0.75*Is_max;		// D-�� ������ ���ǻ� �ִ� ������ 75%�̳��� �����Ѵ�.	
		Is_DQ_max[QS]=sqrt( fabs(Is_max*Is_max - Is_DQ_ref[DS]*Is_DQ_ref[DS]) );
	}	
	else
	{	
		if (fabs(we0)<we_FW)
		{
			Fr_ref0=Fr_B;
			Is_DQ_max[DS]=0.75*Is_max;		// D-�� ������ ���ǻ� �ִ� ������ 75%�̳��� �����Ѵ�.	
			Is_DQ_max[QS]=sqrt( fabs(Is_max*Is_max - Is_DQ_ref[DS]*Is_DQ_ref[DS]) );
		}		
		else if (fabs(we0)<we_FW1)
		{	
			Fr_ref0=Fr_B*(we_FW1/fabs(we0));		// ==> Lm*sqrt( ((Vs_max_FW*Vs_max_FW)/(we0*we0)-sigma_Ls*sigma_Ls*Is_max*Is_max)/(Ls*Ls-sigma_Ls*sigma_Ls) )
			Is_DQ_max[DS]=0.75*Is_max;		// D-�� ������ ���ǻ� �ִ� ������ 75%�̳��� �����Ѵ�.	
			Is_DQ_max[QS]=sqrt( fabs(Is_max*Is_max - Is_DQ_ref[DS]*Is_DQ_ref[DS]) );
		}		
		else	
		{
			I_DS_FW2=Vs_max_FW/(1.414*fabs(we0)*Ls);
			Fr_ref0=Lm*I_DS_FW2;		
			Is_DQ_max[DS]=I_DS_FW2*sqrt(1.0 + 1.0/(sigma*sigma));	
			Is_DQ_max[QS]=I_DS_FW2/sigma;
		}	
		
		if (Fr_ref0>Fr_B)
				Fr_ref0=Fr_B;
				
		Fr_ref=Fr_ref0;
	}
	
	//***************************************************************

	// ȸ���� �ڼ� �����
	
	Fr_CycleIndex++;
	Fr_Cycle+=Ts;
	if (Fr_CycleIndex>=Fr_CntlPeriodIndex)
	{

		Fr_Err=Fr_ref-Fr;
		Fr_ErrInt+=Ki_Fr*Fr_Err*Fr_Cycle;

		if (Fr_ErrInt>Is_DQ_max[DS])		
				Fr_ErrInt=Is_DQ_max[DS];
		else if (Fr_ErrInt<-Is_DQ_max[DS])	
				Fr_ErrInt=-Is_DQ_max[DS];
		Is_DQ_ref[DS]=Kp_Fr*Fr_Err+Fr_ErrInt;	// + Fr_ref*inv_Lm;
		
		// ���� �ֱ� �ε��� �� �ð� �ʱ�ȭ
		Fr_Cycle=0.0;
		Fr_CycleIndex=0;	
	}	
	
	//*********************************************************
	
	// D-�� ���� ��� : Feedforwrd Term + PI Controller Output	
	if (Is_DQ_ref[DS]>Is_DQ_max[DS])	
		Is_DQ_ref[DS]=Is_DQ_max[DS];
	else if (Is_DQ_ref[DS]<-Is_DQ_max[DS])	
		Is_DQ_ref[DS]=-Is_DQ_max[DS];	

	//Q-�� ���� ���		
	if (Is_DQ_ref[QS]>Is_DQ_max[QS])		
		Is_DQ_ref[QS]=Is_DQ_max[QS];
	else if (Is_DQ_ref[QS]<-Is_DQ_max[QS])	
		Is_DQ_ref[QS]=-Is_DQ_max[QS];	

	
	// D-�� ���� ����� : �ڼ������ -> D-�� ���� Ref.
	Vs_DQ_ref_P[DS]=codeKpIs*(K_Damp_Is*Is_DQ_ref[DS]-Is_DQ[DS]);
	Vs_DQ_max[DS]=Vs_max + fabs(Vs_DQ_ref_P[DS]);						// ���б��� ���Ѱ� ����
	Is_DQ_ErrInt[DS] += codeKiIs*(Is_DQ_ref[DS] - Is_DQ[DS])*Ts;
	if (Is_DQ_ErrInt[DS]>Vs_DQ_max[DS])		
			Is_DQ_ErrInt[DS] = Vs_DQ_max[DS];
	else if (Is_DQ_ErrInt[DS]<-Vs_DQ_max[DS])	
			Is_DQ_ErrInt[DS] = -Vs_DQ_max[DS];
	Vs_DQ_ref_PI[DS]=Vs_DQ_ref_P[DS] + Is_DQ_ErrInt[DS];

	// Q-�� ���� ����� : ��ũ ��� ==> Q-�� ���� ���	
	Vs_DQ_ref_P[QS]=codeKpIs*(K_Damp_Is*Is_DQ_ref[QS]-Is_DQ[QS]);
	Vs_DQ_max[QS]=Vs_max + fabs(Vs_DQ_ref_P[QS]);					// ���б��� ���Ѱ� ����
	Is_DQ_ErrInt[QS] += codeKiIs*(Is_DQ_ref[QS]- Is_DQ[QS])*Ts;
	if (Is_DQ_ErrInt[QS]>Vs_DQ_max[QS])			
			Is_DQ_ErrInt[QS] = Vs_DQ_max[QS];
	else if (Is_DQ_ErrInt[QS]<-Vs_DQ_max[QS])		
			Is_DQ_ErrInt[QS] = -Vs_DQ_max[QS];
	Vs_DQ_ref_PI[QS] = Vs_DQ_ref_P[QS] + Is_DQ_ErrInt[QS];
	
	// ������ �� ������ ����
	if (gfRunTime<0.05)
	{
		Vs_DQ_ref[DS] = Vs_DQ_ref_PI[DS] - we0*sigma_Ls*Is_DQ_ref[QS];	
		Vs_DQ_ref[QS] = Vs_DQ_ref_PI[QS] + we0*sigma_Ls*Is_DQ_ref[DS] + we0*Lm_div_Lr*Fr;
	}		
	else
	{
		Vs_DQ_ref[DS] = Vs_DQ_ref_PI[DS] - we0*sigma_Ls*Is_DQ_ref[QS];	
		Vs_DQ_ref[QS] = Vs_DQ_ref_PI[QS] + we0*sigma_Ls*Is_DQ_ref[DS] + we0*Lm_div_Lr*Fr_ref;
	}	
	
	// ����Ÿ�� ���� -> ���� ���� ���
	// ������ ���� : �ð�����(Ts) ���� 
	Us_dq[ds]=Vs_dq[ds];
	Us_dq[qs]=Vs_dq[qs];
	CosDeltaTheta=cos(we0*Ts);
	SinDeltaTheta=sin(we0*Ts);
	Vs_dq[ds] = Us_dq[ds]*CosDeltaTheta + Us_dq[qs]*SinDeltaTheta;
	Vs_dq[qs] = -Us_dq[ds]*SinDeltaTheta + Us_dq[qs]*CosDeltaTheta;
	
	// ��������� -> ���� ��ǥ�� ���� ��� : �� ��ǥ��ȯ, ����Ÿ�� ����
	Vs_dq_ref[ds] = (CosTheta*Vs_DQ_ref[DS] - SinTheta*Vs_DQ_ref[QS]) + (Vs_dq_ref[ds]-Vs_dq[ds]);
	Vs_dq_ref[qs] = (SinTheta*Vs_DQ_ref[DS] + CosTheta*Vs_DQ_ref[QS]) + (Vs_dq_ref[qs]-Vs_dq[qs]);
	
	//************************************************************************************************
	
	// ������ũ ���
	Te=Kt*Lm_div_Lr*Fr*Is_DQ[QS];
}

