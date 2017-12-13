# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Basic Build Instructions

1. Clone this repo.
2. ./clean.sh
3. ./build.sh
4. ./run.sh

Simulator setting:

* Screen resolution: 640x480
* Graphics quality: Fastest

## PID Components

### P Component

The proportional component contributes to reducing CTE and make the car move quicker to the designed path. However, it may also cause overshooting issue and make the car unstable.

### I Component

The integral component is used to compenstate the system bias built in the car. Since there is no system bias in this simulated environment, the I component in this project is set to be zero, with the ability to be tuned as well.

### D Component

The differential component is used for correcting overshooting problem and stablizing the car.

## PID Components Optimization

In this project, the PID components are selected by twiddling algorithm.
 
The twiddle process is using the following settings:

* 1300 steps in each iteration
* 300 steps left out, 1000 steps for evaluating the total error
* Initial PID parameters are set as:
  * Kp = 0.1
  * Ki = 0
  * Kd = 4
* Initial tunning parameters are set as:
  * Dpp = 0.01
  * Dpi = 0
  * Dpd = 0.01
* Ki component is set to be 0 and not tuned
* Twiddle tolerance is set to be 0.001
* Throttle is set to be 0.4, and not tuned

In `main.cpp`, once set `enable_twiddle = true`, the program will use the above settings to twiddle PID parameters. After several iterations, the total error drops and increases again. The program can be terminated once the expected total error is reached, and can also be terminated if the sum of tuning parameters becomes very small (smaller than predefined tolerance). Here, I set a small tolerance to let more iterations run.

The final paramters are selected at 15th iteration, with a minimum total error and an increasing error afterwards. Some details are shown below. 

<img src="https://github.com/jane212/CarND-Term2-PIDControl/blob/master/optimal.png" width="300">

The tuned parameters are:

* Kp = 0.184872
* Ki = 0
* Kd = 4.07324

They are currently in use in `main.cpp` with `enable_twiddle = false`. The car could safely drive a lap the simulator's track. (See test_run.mov)



