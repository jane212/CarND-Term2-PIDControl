#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */


  double p_error;
  double i_error;
  double d_error;

  double dpp = 0.01;
  double dpi = 0;
  double dpd = 0.01;

  double steer_value;

  double cte_i;
  double cte_pre;
  double totalErr;
  double bestErr = 1e9;

  int step;
  int min_steps = 300;

  int p_plus;

  int i_plus;

  int d_plus;

  bool terminate;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp_, double Ki_, double Kd_);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  void TunePara(double& para, double& d_para, int& plus);

  void Twiddle(double tol, int tuned);

  void Print();


};


#endif /* PID_H */
