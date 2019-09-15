//Name: Minh Nguyen
//ECEN VLSI Design Automation
//Homework 2 Question 3

#include <iostream>
#include <cmath>
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
float dfdx1(float x1, float x2);
float dfdx2(float x1, float x2);
float linesearchx1(float x1, float x2);
float linesearchx2(float x1, float x2);
float calc_function(float x1, float x2);


// Constant declaration and initialization
extern float const INITIALX1 = 0;
extern float const INITIALX2 = 0;
extern float const e = 0.000001;


int main()
{
    // main variable initialization and declaration
    float x1 = INITIALX1;   // current iteration variable for x1. Set to our initial x1 value for the first iteration.
    float x2 = INITIALX2;   // current iteration variable for x2. Set to our initial x2 value for the first iteration.
    float x1Next = 1;
    float x2Next = 1;
    float result;

    cout << "The objective function to be solved using 'The Steepest Decent Method' is:\n f(x1,x2) = x1(x1 - 13) + x2^2 + x1(x2 + 7)" << endl;


    // 1. Search for the minimum in the x1 and x2 direction
    int iterate=1;
    while((abs(x1-x1Next)>(e/10)) || (abs(x2-x2Next)>(e/10))){
        cout << "\n\n///////////////////////////////////////////////////////////////////////////////////////////////" << endl;
        cout << "//////////////////////////////////Steepest Decent Algorithm///////////////////////////////////" << endl;
        cout << "//////////////////////////////////Iteration " << iterate << "/////////////////////////////////////////////////" << endl;
        cout << "///////////////////////////////////////////////////////////////////////////////////////////////" << endl;
        x1Next = linesearchx1(x1, x2);
        x2Next = linesearchx2(x1, x2);
        x1 = linesearchx1(x1Next, x2Next);
        x2 = linesearchx2(x1Next, x2Next);
        cout << "x1: " << x1 << endl;
        cout << "x2: " << x2 << endl;
        iterate++;
    }



    // 2. Calculate function value minimum (x1, x2) value
    result = calc_function(x1, x2);
    cout << "\n\nThe minimum value of the function yields a: " << result << endl;
    cout << "Minimum x1 value: " << x1 << endl;
    cout << "Minimum x2 value: " << x2 << endl;



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
    result = ((2*x1)+ x2 - 6);
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
    result = ((2*x2) + x1);
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
  float linesearchx1 (float x1, float x2){
    int iteration = 1;
    float lam = -dfdx1(x1, x2); //We initially set the step size equal to the current gradient and

    cout << "\n\n\t\tInitiated a line search in the x1 direction\n";
    cout << "Initial step size is "<< lam << endl;
    while (abs(dfdx1(x1, x2)) > e){     // Check if we are within our tolerance.
        cout << "\t==================== Linesearch x1 Iteration " << iteration << " ====================" << endl;
        cout << "The partial derivative of f(x1, x2) with respect to x1 at (" << x1 <<", " << x2 <<") is: " << dfdx1(x1, x2) << endl;

        // Check if we passed the minimum and if our initial point is passed the minimum
        if(-dfdx1(x1 + lam, x2) < 0)
            if(-dfdx1(x1 + lam/2, x2) < 0){ // Checks if we are too far passed the minimum and if our initial point is passed the minimum.
                lam = lam - (2*lam);
                cout << "Initial point is passed the minimum. Lam: " << lam << " x1: " << x1 << endl;
            } else { // If we are just pass the min then take a half step back.
                lam = lam/2;
            }

        // This else is the condition that we did not pass the minimum.
        else{
            if(-dfdx2(x1, x2 + lam) == 0){
                lam = lam + x2;
                x2 = lam;
            }
            if(-dfdx1(x1 + lam, x2)> -dfdx2(x1, x2)){ // Checks the case that we are stepping in the wrong direction.
                lam = -lam;
                cout << "Wrong way. Lam: " << lam << " x1: " << x1 << endl;
            } else { // This is the case where we are closer to the minimum but did not pass it.
                    lam = lam +x1;
                    x1 = lam;
                    cout << "Closer to the min. Lam: " << lam << " x1: " << x1 << endl;
            }
        }
        iteration ++;
    }
    cout << "dfdx1 is less than our tolerance at our current point. The final x1 value is " << x1 << endl;
    cout << "Lam is " << lam << endl;
    return x1;
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
  float linesearchx2 (float x1, float x2){
    int iteration = 1;
    float lam = dfdx2(x1, x2); //We initially set the step size equal to the current gradient and

    cout << "\n\n\t\tInitiated a line search in the x2 direction\n";
    cout << "Initial step size is "<< lam << endl;

    while (abs(dfdx2(x1, x2)) > e){
        cout << "\t==================== Linesearch x2 iteration " << iteration << " ====================" << endl;
        //cout << "The partial derivative of f(x1, x2) with respect to x1 at (" << x1 <<", " << x2 <<") is: " << dfdx2(x1, x2) << endl;

        // Check if we passed the minimum and if our initial point is passed the minimum
        if(-dfdx2(x1, x2 + lam) < 0)
            if(-dfdx2(x1, x2 + lam/2) < 0){ // Checks if we are too far passed the minimum and if our initial point is passed the minimum.
                lam = lam - abs(lam)*2;
                cout << "Initial point is passed the minimum. Lam: " << lam << " x2: " << x2 << endl;
                cout << "The partial derivative of f(x1, x2) with respect to x1 at (" << x1 <<", " << x2+lam <<") is: " << dfdx2(x1, x2+lam) << endl;
            } else { // If we are just pass the min then take a half step back.
                lam = lam/2;
            }

        // This else is the condition that we did not pass the minimum.
        else{/*
            if(-dfdx2(x1, x2 + lam)> -dfdx2(x1, x2)){ // Checks if we are stepping in the wrong direction.
                lam = -abs(lam)+.5;
                cout << "Wrong way. Lam: " << lam << " x2: " << x2 << endl;
                cout << "The partial derivative of f(x1, x2) with respect to x1 at (" << x1 <<", " << x2+lam <<") is: " << dfdx2(x1, x2+lam) << endl;
            } else { // This is the case where we are closer to the minimum but did not pass it.
                    lam = lam + x2;
                    x2 = lam;
                    cout << "Closer to the min. Lam: " << lam << " x2: " << x2 << endl;
            }*/
            if(-dfdx2(x1, x2 + lam) == 0){
                lam = lam + x2;
                x2 = lam;
            }
            if(-dfdx2(x1, x2 + lam)> -dfdx2(x1, x2)){ // Checks if we are stepping in the wrong direction.
                lam = -abs(lam)+abs(lam)*.5;
                cout << "Wrong way. Lam: " << lam << " x2: " << x2 << endl;
                cout << "The partial derivative of f(x1, x2) with respect to x2 at (" << x1 <<", " << x2+lam <<") is: " << dfdx2(x1, x2+lam) << endl;
            } else { // This is the case where we are closer to the minimum but did not pass it.
                    lam = lam + x2;
                    x2 = lam;
                    cout << "Closer to the min. Lam: " << lam << " x2: " << x2 << endl;
            }}
        iteration ++;
    }
    cout << "dfdx2 is less than our tolerance at our current point. The final x2 value is " << x2 << endl;
    return x2;
  }

  float calc_function(float x1, float x2){
      float result;
      result = (x1*x1 - 13.0*x1) + x2*x2 + (x2*x1 + 7.0*x1);
      return result;
  }
