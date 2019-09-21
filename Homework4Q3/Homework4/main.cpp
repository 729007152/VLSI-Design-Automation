//Name: Minh Nguyen
//ECEN VLSI Design Automation
//Homework 2 Question 3

#include <iostream>
#include <cmath>
#include <math.h>
#include <stdlib.h>

using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////
// This program focuses on finding the minimum of f(x1,x2) = x1(x1 - 13) + x2^2 + x1(x2 + 7) //
// using the Steepest decent method. The program will display the intermediate result of     //
// each iteration, and also the moving direction and step size of each iteration. All        //
// parameters used by this program, will be displayed as well.                               //

// Givens:                                                                                   //
//      Objective Function: f(x1,x2) = x1(x1 - 13) + x2^2 + x1(x2 + 7)                       //
//      Termination Criterion: e = 0.000001                                                  //
//      Initial Solution = (0, 0)                                                            //


// Prototype declaration
float const FURTHEST = 5;

//float dfdx1(float x1, float x2);
//float dfdx2(float x1, float x2);
float sim_annealingx1(float x1, float x2);
float sim_annealingx2(float x1, float x2);
float calc_function(float x1, float x2);


// Constant declaration and initialization
extern float const INITIALX1 = 7;
extern float const INITIALX2 = 17;
extern float const e = 0.000001;


int main()
{
    // main variable initialization and declaration
    float x1 = INITIALX1;   // current iteration variable for x1. Set to our initial x1 value for the first iteration.
    float x2 = INITIALX2;   // current iteration variable for x2. Set to our initial x2 value for the first iteration.

    cout << "The objective function to be solved using 'simulated annealing ' is:\n f(x1,x2) = x1(x1 - 7) + x2^3 - x1(x2 - 13)" << endl;


    for(float i=0 ; i<= 25 ; i=i+0.01){// This for is only for debugging it can be disreguarded
        //cout << static_cast <float> (rand()) / static_cast <float> (RAND_MAX) << endl;
        //cout << ((float(rand()) / float(RAND_MAX)) * (10 - 5)) << endl;
        cout << -5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(5+5)))<< endl;
        cout << "calc_function("<<i+0.01<<",x2)-calc_function("<<i+i<<",x2)=" << calc_function(i+0.01,x2)-calc_function(i,x2) << endl;
        cout << calc_function(i ,17) << "-" << calc_function(i+0.01,17) << calc_function(i+0.01,x2)-calc_function(i,x2) << endl;
        cout << "rand=" << -.1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(.1+.1))) << endl;
    }

    // simulate annealing
    x1 = sim_annealingx1(INITIALX1, INITIALX2);
    x2 = sim_annealingx2(INITIALX1, INITIALX2);

    cout << "Minimum x1 value after simulated annealing: " << x1 << endl;
    cout << "Minimum x2 value after simulated annealing: " << x2 << endl;

    return 0;
}

/**
  * Brief:  This program determines instantaneous gradient of the multi-variable function under
  *         test through its partial derivatives in the x1 and x2 component. This function will
  *         return the partial derivative of the x1 component given a point.
  * Input:  x1, x2 - Point to calculate the partial derivative df/dx1.
  * Return: dx1 - gradient f(x1, x2) in the x1 component
  **/
  float dfdx1(float x1, float x2){
    float result = 0;
    result = ((2*x1)- x2 - 24);
    return result;
  }

  /**
  * Brief:  This program determines instantaneous gradient of the multi-variable function under
  *         test through its partial derivatives in the x1 and x2 component. This function will
  *         return the partial derivative of the x2 component given a point.
  * Input:  x1, x2 - Point to calculate the partial derivative df/dx2.
  * Return: dx2 - gradient f(x1, x2) in the x2 component
  **/
  float dfdx2(float x1, float x2){
    float result = 0;
    result = ((3*x2*x2) - x1);
    return result;
  }

float sim_annealingx1(float x1, float x2){
    float lam;
    float minimum;
    float d;

    cout << "Sim annealing for x1.." << endl;

    ///First: determine our move///
    cout << "d = " << d << endl;
    minimum = x1;
    cout << "(x1,x2)=" << "(" << x1 << "," << x2 << ")" << endl;
    ///Second: Iterate through T shrinking it on every iteration until we are small than our tolerance e
    for(float T= 5 ; T>=e ; T=T*0.9999){
    ///Third: calculate present configuration and next configuration if find their delta///
    ///Fourth: compare delta to determine whether to accept or not and also accounting for the probability///
    d=-.1+ static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.1+0.1))); // we get a random distance 5 to -5 to explore
        if(calc_function(minimum+d,x2)<calc_function(minimum,x2)){
        //if(calc_function(minimum+d,x2)-calc_function(minimum,x2)<0){   //check if delta is negative. If so then we have a better solution
            cout << "calc_function("<<minimum+d<<",x2)-calc_function("<<minimum<<",x2)=" << calc_function(minimum+d,x2)-calc_function(minimum,x2) << endl;
            cout << calc_function(minimum+d,x2) << "-" << calc_function(minimum,x2) << "=" << calc_function(minimum+d,x2)-calc_function(minimum,x2) << endl;
            if((minimum+d>0)&&(minimum+d<20)) //make sure we are within our range
                minimum = minimum + d;
            cout << "d = " << d << endl;
            cout << "minimum = " << minimum << endl;
        } else if(1/exp((calc_function(minimum+d,x2)-calc_function(minimum,x2))/T) > (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))){  //This will check if e^(-d/T) is greater than a random prob value between  0.0-1.0
            cout << "exp(-d/T): " << 1/(exp((calc_function(minimum+d,x2)-calc_function(minimum,x2)))/T) <<"\tvs.\t" << (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) << endl;
            if((minimum+d>0)&&(minimum+d<20)) //make sure we are within our range
                minimum = minimum + d;
            cout << "Bad move accepted..\n" << endl;
        }
        cout << "rand " << d << endl;
        cout << "T = " << T << endl;
    }
    cout << "minimum = " << minimum << endl;
    return minimum;
}

float sim_annealingx2(float x1, float x2){
    float lam;
    float minimum;
    float d;

    ///First: determine our move///
    cout << "d = " << d << endl;
    minimum = x2;
    cout << "(x1,x2)=" << "(" << x1 << "," << x2 << ")" << endl;
    ///Second: Iterate through T shrinking it on every iteration until we are smaller than our tolerance e///
    for(float T=5 ; T>=e ; T=T*0.9999){
    ///Third: calculate present configuration and next configuration if find their delta///
    ///Fourth: compare delta to determine whether to accept or not and also accounting for the probability///
    d=-.1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(.1+.1))); // we get a random distance 5 to -5 to explore
        if(calc_function(x1,minimum+d)-calc_function(x1,minimum)<0){   //check if delta is negative. If so then we have a better solution
            cout << "calc_function(x1," << minimum+d << ")-calc_function(x1,"<<minimum<<")=" << calc_function(x1,minimum+d)-calc_function(x1,minimum) << endl;
            cout << calc_function(x1,minimum+d) << "-" << calc_function(x1,minimum) << "=" << calc_function(x1,minimum+d)-calc_function(x1,minimum) << endl;
            if((minimum+d>0)&&(minimum+d<20)) //make sure we are within our range
                minimum = minimum + d;
            cout << "d = " << d << endl;
            cout << "minimum = " << minimum << endl;
        } else if(1/exp((calc_function(x1,minimum+d)-calc_function(x1,minimum))/T) > (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))){  //This will check if e^(-d/T) is greater than a random prob value between  0.0-1.0
            cout << "exp(-d/T): " << 1/exp((calc_function(x1,minimum+d)-calc_function(x1,minimum))/T) <<"\tvs.\t" << (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) << endl;
            if((minimum+d>0)&&(minimum+d<20)) //make sure we are within our range
                minimum = minimum + d;
            cout << "Bad move accepted..\n" << endl;
        }
        cout << "rand " << d << endl;
        cout << "T = " << T << endl;
    }
    cout << "minimum = " << minimum << endl;
    return minimum;
}


  float calc_function(float x1, float x2){
      float result;
      result = (x1*x1) - (7*x1) + (x2*x2*x2) - (x2*x1) - (17*x1);
      return result;
  }
