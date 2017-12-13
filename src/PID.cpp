#include "PID.h"
#include <iostream>

//using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {


	p_error = 0.0;
	i_error = 0.0;
	d_error = 0.0;
	steer_value = 0.0;

	Kp = Kp_;
	Ki = Ki_;
	Kd = Kd_;


	cte_i = 0.0;
	cte_pre = 0.0;
	step = 0;
	totalErr = 0.0;

	p_plus = 1;

	d_plus = 1;

	terminate = false;

}

void PID::UpdateError(double cte) {
	cte_i += cte;
	double diff = cte - cte_pre;
	cte_pre = cte;
	p_error = -Kp*cte;
	i_error = -Ki*cte_i;
	d_error = -Kd*diff;

	steer_value = p_error + i_error + d_error;

	step++;

	if (step>min_steps){
		totalErr += cte*cte;
	}
}

void PID::TunePara(double& para, double& d_para, int& plus) {

	if (totalErr<bestErr){
		bestErr = totalErr;		
	    d_para *= 1.1;
	    
	}

	else{
		plus = (-1)*plus;
		para += d_para * plus; //reset
		d_para *= 0.9;
	}
	para += d_para * plus;
}

void PID::Twiddle(double tol, int tuned) {



	switch(tuned){
		case 1:
			std::cout<< "p tuned: "<<std::endl;
			std::cout<<"\t"<<Kp<<std::endl;
			TunePara(Kp, dpp, p_plus);
			std::cout<<"\t"<<Kp<<std::endl;
			break;
		// case 1:
		// 	std::cout<< "i tuned: "<<Ki<<' -> ';
		// 	TunePara(Ki, dpi, i_plus);
		// 	std::cout<<Ki<<std::endl;
			break;
		case -1:
			std::cout<< "d tuned: "<<std::endl;
			std::cout<<"\t"<<Kd<<std::endl;
			TunePara(Kd, dpd, d_plus);
			std::cout<<"\t"<<Kd<<std::endl;
			break;
	}

	if(dpp+dpi+dpd<tol){
		terminate = true;
	}
}

void PID::Print() {

    std::cout<<"Results at: "<<step<<std::endl;
    std::cout<<"Kp: "<<Kp<<std::endl;
    std::cout<<"Ki: "<<Ki<<std::endl;
    std::cout<<"Kd: "<<Kd<<std::endl;
    std::cout<<"dpp: "<<dpp<<std::endl;
    std::cout<<"dpi: "<<dpi<<std::endl;
    std::cout<<"dpd: "<<dpd<<std::endl;
    std::cout<<"Total Error: "<<totalErr<<std::endl;
    std::cout<<"Best Error: "<<bestErr<<std::endl;
}


