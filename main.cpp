//Name: Minh Nguyen
//ECEN VLSI Design Automation
//Homework 2 Question 3

#include <iostream>
#include <cmath>

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


// Constant declaration and initialization
float const INITIALX1 = 0;
float const INITIALX2 = 0;
float const e = 0.000001;


int main()
{
    // main variable initialization and declaration
    float d1 = 0;           // Search direction for x1
    float d2 = 0;           // Search direction for x2
    float x1 = INITIALX1;   // current iteration variable for x1. Set to our initial x1 value for the first iteration.
    float x2 = INITIALX2;   // current iteration variable for x2. Set to our initial x2 value for the first iteration.

//================== The main steps for the steepest decent algorithm is as follows ===========================//
//                        1. If ||Df(xk)|| < e, done
//                        2. Otherwise, dk = -Df(xk), and let Lk be an optimal solution to
//                           minimize f(xk Ldk) subject to L >= 0
//                        3. Let x(k+1) = xk + Lkdk
//                        4. k = k + 1
//                        5. Goto 1

    cout << "The objective function to be solved using 'The Steepest Decent Method' is:\n f(x1,x2) = x1(x1 - 13) + x2^2 + x1(x2 + 7)" << endl;


    // 1. Check if our initial pints gradient e > 0

    x1 = linesearchx1(INITIALX1, INITIALX2);
    x2 = linesearchx2(INITIALX1, INITIALX2);

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
  * Brief:  This function will find the local minimal in the x1 direction
  * Input:  x1, x2 - Receives the initial point to begin searching for the minimum
  * Return: x1 - returns the value x1 must be in order to be at the local minimum
  *              in the x1 direction.
  */
  float linesearchx1 (float x1, float x2){
    float step = 1;
    float newstep = 1;
    float newx1 = 0;
    int iteration = 1;
    float lam = 0.5;
    x1 = x1 + lam;

    cout << "\n\n\t\tInitiated a line search in the x1 direction\n";
    cout << "Initial step size is "<< lam << endl;
    while (abs(dfdx1(x1, x2)) > e){
        cout << "\t==================== Iteration " << iteration << " ====================" << endl;
        cout << "The partial derivative of f(x1, x2) with respect to x1 at (" << x1 <<", " << x2 <<") is: " << dfdx1(x1, x2) << endl;
        //x1 = x1 + lam;
        if(abs(dfdx1(x1, x2)) > abs(dfdx1(x1 + lam, x2)) && abs(dfdx1(x1 + lam, x2)) > 1.0){
            if((-1 * dfdx1(x1 + lam, x2)) >= 0){
                lam = lam + 0.5;
                x1 = x1 + lam;
                cout <<"x1 is on the left of the minimum, move forward. x1 is now "<< x1 << endl;
            }
            else{
                lam = -lam;
                x1 = x1 + lam;
                cout << "Passed the minimum. Step back. x1 is now "<< x1 << endl;
            }
        }
        else if((-1.0 > dfdx1(x1, x2)) || (dfdx1(x1, x2) < 1.0)){
                if ((dfdx1(x1, x2) > 0.0)){//lam = lam - e;
                    //lam  = abs(lam*dfdx1(x1)) - lam;
                    x1 = x1 - lam/4;
                    cout << "We are to the right of the minimum. Time to go back and take a smaller step. x1 is now " << x1 << endl;
                }
               else if ((dfdx1(x1, x2) < 0.0)){//lam = lam - e;
                    //lam  = lam*dfdx1(x1, x2);
                    x1 = x1 + abs(lam/6);
                    cout << "The step we took is close to the minimum and to the left. Take a small step forward. Current x1 is now " << x1 << endl;
                }
            }
        else {
            //lam = -1 * (lam - e);
            lam  = -lam - 1;
            x1 = x1 + lam/2;
            cout << "step in the wrong direction. x1 is now " << x1 << endl;
        }
        iteration ++;
    }
    cout << "dfdx1 is less than our tolerance at our current point. The final x1 value is " << x1 << endl;
    return x1;
  }

  /**
  * Brief:  This function will find the local minimal in the x2 direction
  * Input:  x1, x2 - Receives the initial point to begin searching for the minimum
  * Return: x2 - returns the value x2 must be in order to be at the local minimum
  *              in the x2 direction.
  */
  float linesearchx2 (float x1, float x2){;
    int iteration = 1;
    float lam = 0.5;
    x2 = x2 + lam;

    cout << "\n\n\t\tInitiated a line search in the x1 direction\n";
    cout << "Initial step size is "<< lam << endl;
    while (abs(dfdx2(x1, x2)) > e){
        cout << "\t==================== Iteration " << iteration << " ====================" << endl;
        cout << "The partial derivative of f(x1, x2) with respect to x1 at (" << x1 <<", " << x2 <<") is: " << dfdx2(x1, x2) << endl;
        if(abs(dfdx2(x1, x2)) > abs(dfdx2(x1, x2 + lam)) && abs(dfdx2(x1, x2 + lam)) > 1.0){
            if((-1 * dfdx1(x1, x2 + lam)) >= 0){
                lam = lam + 0.5;
                x2 = x2 + lam;
                cout <<"x2 is on the left of the minimum, move forward. x2 is now "<< x2 << endl;
            }
            else{
                lam = -lam;
                x2 = x2 + lam;
                cout << "Passed the minimum. Step back. x2 is now "<< x2 << endl;
            }
        }
        else if((-1.0 > dfdx2(x1, x2)) || (dfdx2(x1, x2) < 1.0)){
                if ((dfdx2(x1, x2) > 0.0)){
                    x2 = x2 - lam/4;
                    cout << "We are to the right of the minimum. Time to go back and take a smaller step. x2 is now " << x2 << endl;
                }
               else if ((dfdx2(x1, x2) < 0.0)){
                    x2 = x2 + abs(lam/6);
                    cout << "The step we took is close to the minimum and to the left. Take a small step forward. Current x2 is now " << x2 << endl;
                    cout << "Lam is " << lam << endl;
                }
            }
        else {
            lam  = -lam - 1;
            x2 = x2 + lam/2;
            cout << "step in the wrong direction. x2 is now " << x2 << endl;
        }
        iteration ++;
    }
    cout << "dfdx2 is less than our tolerance at our current point. The final x2 value is " << x2 << endl;
    return x2;
  }
