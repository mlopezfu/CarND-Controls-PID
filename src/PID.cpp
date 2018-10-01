#include "PID.h"
#include <iostream>
#include <math.h>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {
}

PID::~PID() {

}

void PID::Init(double Kp, double Ki, double Kd) {
  	PID::Kp = Kp;
  	PID::Ki = Ki;
  	PID::Kd = Kd;

  	p_error = 0.0;
  	i_error = 0.0;
  	d_error = 0.0;

  	// Previous cte.
  	previous_cte = 0.0;

  	// Counters.
  	step = 0;

	// to try optimization
	dif_kp=0.001;
  	twiddle_total_error=0.0;
  	min_Kp_error=1000;
}

void PID::UpdateError(double cte) {
	  // Proportional error.
  p_error = cte;

  
  // Integral error.
  i_error += cte;

  // Diferential error.
  d_error = cte - previous_cte;
  total_error=p_error * Kp + i_error * Ki + d_error * Kd;
  previous_cte = cte;
  //Twiddle();
  step++;
}

double PID::TotalError() {
	return total_error;
}

void PID::Twiddle(){
	twiddle_total_error+=total_error;
  	if ( step % 100 == 0 )
    {
          if (min_Kp_error>twiddle_total_error){
          	// Si el error nuevo es mejor que el anterior
			min_Kp_error=twiddle_total_error;
		  	PID::Kp += dif_kp;	
		  }
		  else{
		  	// Incrementar en el otro sentido.
		    dif_kp *= -1;
		  	PID::Kp += dif_kp;
		  }
		  twiddle_total_error=0.0;
		  cout << "Kp " << Kp << " Ki " << Ki << " Kd " << Kd << endl;
    }


/* 
    p = [0, 0, 0]
    dp = [1, 1, 1]
    robot = make_robot()
    x_trajectory, y_trajectory, best_err = run(robot, p)

    it = 0
    while sum(dp) > tol:
        print("Iteration {}, best error = {}".format(it, best_err))
        for i in range(len(p)):
            p[i] += dp[i]
            robot = make_robot()
            x_trajectory, y_trajectory, err = run(robot, p)

            if err < best_err:
                best_err = err
                dp[i] *= 1.1
            else:
                p[i] -= 2 * dp[i]
                robot = make_robot()
                x_trajectory, y_trajectory, err = run(robot, p)

                if err < best_err:
                    best_err = err
                    dp[i] *= 1.1
                else:
                    p[i] += dp[i]
                    dp[i] *= 0.9
        it += 1
    return p
    */
}