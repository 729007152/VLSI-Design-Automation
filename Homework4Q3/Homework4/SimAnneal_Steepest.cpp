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

float dfdx1(float x1, float x2);
float dfdx2(float x1, float x2);
float linesearchx1(float x1, float x2);//not used for this homework
float sim_annealingx1(float x1, float x2, float FURTHEST);
float sim_annealingx2(float x1, float x2, float FURTHEST);
float linesearchx2(float x1, float x2);//not used for this homework
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
    float x1Next = 1;
    float x2Next = 1;
    float result;

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
    x1 = sim_annealingx1(INITIALX1, INITIALX2, FURTHEST);
    x2 = sim_annealingx2(INITIALX1, INITIALX2, FURTHEST);

    cout << "Minimum x1 value: " << x1Next << endl;
    cout << "Minimum x2 value: " << x2Next << endl;
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
    //cout << "The partial derivative of f(x1, x2) with respect to x1 at (" << x1 <<", " << x2<<") is :" << result << endl;
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
    //cout << "The partial derivative of f(x1, x2) with respect to x2 at (" << x1 <<", " << x2<<") is :" << result << endl;
    return result;
  }

  /**
  * Brief:  This function will find the local minimal in the x1 direction. We
  *         first set the initial step size equal to the gradient with opposite direction.
  *         Then, we check if our step made us pass the minimum, if this is true then we half
  *         the step size. If not, then update to our new x1 value as well as our lam.
  * Input:  x1, x2 - Receives the initial point to begin searching for the minimum
  * Return: x1 - returns the value x1 must be in order to be at the local minimum
  *              in the x1 direction.
  */
float linesearchx1(float x1, float x2){
    float lower;
    float upper;
    float minimum;
    float lam=20-x1;

    cout << "looking min in x1...\n" << endl;

        if(x1>20){
            x1 = 0;
        }
        if((-dfdx1(x1, x2) < -dfdx1(x1+lam,x2)) && (-dfdx1(x1+lam,x2) < 0) ){
            cout << "min: " << minimum << endl;
        }
        while(lam > e){ //First we check ahead of x1
            if((calc_function(x1+lam,x2)>calc_function(x1+lam-1,x2))){
                lam = lam-1;
                cout << lam << endl;
                cout << "-dfdx1(x1+lam,x2)<-dfdx1(x1+lam-1,x2)" << endl;
                cout << "-dfdx1(x1+lam, x2)=" << -dfdx1(x1+lam, x2) << endl;

            } else if(calc_function(x1+lam,x2)<calc_function(x1+lam-1,x2)){ //if the further point is smaller than the close closer point,
                cout << "Inside else if..." << endl; //for debugging
                if(calc_function(minimum,x2)>calc_function(x1+lam-1,x2))    //update if we are at the lowest point
                    minimum = x1+lam;
                lam = lam-1;
                if(calc_function(x1+lam,x2)>calc_function(x1+lam-1,x2)){
                    cout << "lam=lam*0.999999" << endl;
                    lam=lam-1.000001;
                    lam=lam*0.999999;
                }
                cout << "min: " << minimum << endl;

            }else{
                cout << "In else.." << endl;
                lam = lam-1;
                cout << lam << endl;
            }cout << "lam: " << lam << endl;
        }

        lam = -x1;  // Now time to step back words

        while(lam < e){ //This will do what the first while loop did but this time, we check values behind x1
            cout << "in while.." << endl;
            if((-dfdx1(x1+lam,x2) < -dfdx2(x1+lam*+1,x2))){ // Start at the lower bound of our space, so 0 and step by 1
                lam = lam+1;

            } else if((-dfdx1(x1+lam, x2) > -dfdx1(x1+lam+1,x2)) && (-dfdx1(x1+lam*+1,x2) > 0)){
                if(calc_function(minimum,x2)>calc_function(x1+lam+1,x2)) // Update minimum if we discover the lowest point yet
                    minimum = x1+lam;
                lam = lam + 1;
                cout << "min: " << minimum << endl;
                if(abs(-dfdx1(x1+lam, x2)) < abs(-dfdx1(x1+lam+1,x2))){ // If we just passed a minimum, backtrack and take now take really small steps
                    lam = lam - 1.000001; //backtrack
                    lam = lam*0.9999999;  // now take really small steps
                }

            }else{
                lam = lam+1;
            }
            cout << "-dfdx1("<< x1+lam << ",x2) = " << -dfdx1(x1+lam,x2) << endl;
            cout << "lam: " << lam <<endl;
            cout << "current min: " << minimum << endl;
        }

        cout << x1 << endl;
        cout<< "Lam: " << lam << endl;
    return minimum;
    }










float sim_annealingx1(float x1, float x2, float furthest){
    float lam;
    float minimum;
    float d;

    cout << "Sim annealing for x1.." << endl;

    ///First: determine our move///
    cout << "d = " << d << endl;
    minimum = x1;
    cout << "(x1,x2)=" << "(" << x1 << "," << x2 << ")" << endl;
    ///Second: Iterate through T shrinking it on every iteration///
    for(float T= 5 ; T>=e ; T=T*0.9999){
    ///Third: calculate present configuration and next configuration if find their delta///
    ///Fourth: compare delta to determine whether to accept or not and also accounting for the probability///
    d=-.1+ static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.1+0.1))); // we get a random distance 5 to -5 to explore
        if(calc_function(minimum+d,x2)<calc_function(minimum,x2)){
        //if(calc_function(minimum+d,x2)-calc_function(minimum,x2)<0){   //check if delta is negative. If so then we have a better solution
            cout << "calc_function("<<minimum+d<<",x2)-calc_function("<<minimum<<",x2)=" << calc_function(minimum+d,x2)-calc_function(minimum,x2) << endl;
            cout << calc_function(minimum+d,x2) << "-" << calc_function(minimum,x2) << "=" << calc_function(minimum+d,x2)-calc_function(minimum,x2) << endl;
            minimum = minimum + d;
            cout << "d = " << d << endl;
            cout << "minimum = " << minimum << endl;
        } else if(1/exp((calc_function(minimum+d,x2)-calc_function(minimum,x2))/T) > (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))){  //This will check if e^(-d/T) is greater than a random prob value between  0.0-1.0
            cout << "exp(-d/T): " << 1/(exp((calc_function(minimum+d,x2)-calc_function(minimum,x2)))/T) <<"\tvs.\t" << (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) << endl;
            minimum = minimum + d;
            cout << "Bad move accepted..\n" << endl;
        }
        cout << "rand " << d << endl;
        cout << "T = " << T << endl;
    }
    cout << "minimum = " << minimum << endl;
    return minimum;
}

float sim_annealingx2(float x1, float x2, float furthest){
    float lam;
    float minimum;
    float d;

    ///First: determine our move///
    cout << "d = " << d << endl;
    minimum = x2;
    cout << "(x1,x2)=" << "(" << x1 << "," << x2 << ")" << endl;
    ///Second: Iterate through T shrinking it on every iteration///
    for(float T=5 ; T>=e ; T=T*0.9999){
    ///Third: calculate present configuration and next configuration if find their delta///
    ///Fourth: compare delta to determine whether to accept or not and also accounting for the probability///
    d=-.1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(.1+.1))); // we get a random distance 5 to -5 to explore
        if(calc_function(x1,minimum+d)-calc_function(x1,minimum)<0){   //check if delta is negative. If so then we have a better solution
            cout << "calc_function(x1," << minimum+d << ")-calc_function(x1,"<<minimum<<")=" << calc_function(x1,minimum+d)-calc_function(x1,minimum) << endl;
            cout << calc_function(x1,minimum+d) << "-" << calc_function(x1,minimum) << "=" << calc_function(x1,minimum+d)-calc_function(x1,minimum) << endl;
            minimum = minimum + d;
            cout << "d = " << d << endl;
            cout << "minimum = " << minimum << endl;
        } else if(1/exp((calc_function(x1,minimum+d)-calc_function(x1,minimum))/T) > (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))){  //This will check if e^(-d/T) is greater than a random prob value between  0.0-1.0
            cout << "exp(-d/T): " << 1/exp((calc_function(x1,minimum+d)-calc_function(x1,minimum))/T) <<"\tvs.\t" << (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) << endl;
            minimum = minimum + d;
            cout << "Bad move accepted..\n" << endl;
        }
        cout << "rand " << d << endl;
        cout << "T = " << T << endl;
    }
    cout << "minimum = " << minimum << endl;
    return minimum;
}

/**
  * Brief:  This function will find the local minimal in the x2 direction. We
  *         first set the initial step size equal to the gradient with opposite direction.
  *         Then, we check if our step made us pass the minimum, if this is true then we half
  *         the step size. If not, then update our new x2 value as well as our lam.
  * Input:  x1, x2 - Receives the initial point to begin searching for the minimum
  * Return: x2 - returns the value x2 must be in order to be at the local minimum
  *              in the x2 direction.
  */
float linesearchx2(float x1, float x2){
    float lower;
    float upper;
    float minimum;
    float lam=20-x2;

    //while (abs(dfdx2(x1, x2)) > e){
        if(x2>20){
            x2 = 0;
        }
        if((-dfdx2(x1, x2) < -dfdx2(x1,x2+lam)) && (-dfdx2(x1,x2+lam) > 0) ){
        //if(calc_function(x1, x2) > calc_function(x1+lam,x2)){
            minimum = x2+lam;
            cout << "min: " << minimum << endl;
        }
        while(lam > e){
            //cout << "in while.." << endl;
            if((-dfdx2(x1,x2)>-dfdx2(x1,x2+lam))){
                lam = lam*0.99;
                cout << lam << endl;
            } else if((-dfdx2(x1, x2) < -dfdx2(x1,x2+lam)) && (-dfdx2(x1,x2+lam) < 0)){
                minimum = x2+lam;
                lam = lam*0.99;
                cout << "min: \n\n" << minimum << endl;
            }else{
            lam = lam*0.99;
            cout << lam << endl;
            }
        }

        lam = -x2;

        while(lam < e){
            cout << "in while.." << endl;
            if((-dfdx2(x1,x2+lam) < -dfdx2(x1,x2+lam*+1))){
                lam = lam+1;
                cout << lam << endl;
            } else if((-dfdx2(x1, x2+lam) > -dfdx2(x1,x2+lam+1)) && (-dfdx2(x1,x2+lam*+1) > 0)){
                minimum = x2+lam;
                lam = lam + 1;
                cout << "min: " << minimum << endl;
                if(abs(-dfdx2(x1, x2+lam)) < abs(-dfdx2(x1,x2+lam+1))){
                    lam = lam - 1;
                    lam = lam*0.999999;
                }

            }else{
                cout << "in else..." << endl;
                cout << "-dfdx2(x1,x2+lam+lam) = " << -dfdx2(x1,x2+lam+1) << endl;
                cout << "-dfdx2(x1,x2+lam) = " << -dfdx2(x1, x2+lam) << endl;
                cout << "x2+lam: " << x2+lam << endl;
                cout << "x2+lam+1: " << x2+lam+1 << endl;
                lam = lam+1;
                cout << lam << endl;
            }
            cout << "-dfdx2(x1," << x2+lam <<") = " << -dfdx2(x1,x2+lam) << endl;
        }

        cout << x2 << endl;
        cout<< "Lam: " << lam << endl;
        cout << "The partial derivative of f(x1, x2) with respect to x1 at (" << x1 <<", " << x2 <<") is: " << -dfdx2(x1, x2) << endl;
    //}
    return minimum;
}







  float calc_function(float x1, float x2){
      float result;
      result = (x1*x1) - (7*x1) + (x2*x2*x2) - (x2*x1) - (17*x1);
      return result;
  }
