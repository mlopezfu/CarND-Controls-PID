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

  /* Auxiliar */
  double previous_cte;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;
  /*
  * Auxiliar
  */ 
  int step; 
  double min_Kp_error;
  double min_Ki_error;
  double min_Kd_error;
  double dif_kp;
  double dif_ki;
  double dif_kd;
  double min_total_error;
  double total_error;
  double twiddle_total_error;
  double min_error;
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
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
  /*
  * Optimize total PID error.
  */
  void Twiddle();
};

#endif /* PID_H */
