//
//  main.cpp
//  numMethod_hw9
//
//  Created by Michael Leong on 18/11/2022.
//

#include <iostream>

using namespace std;

//using dynamic programming to calculate c[]
void cTable(double points[][2], int n, double c[]) {
    //table to store result
    double table[n][n];
    
    //init table
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            table[i][j] = 0;
        }
    }
    
    //init 1st col table
    for(int i = 0; i < n; i++) {
        //y_i
        table[i][0] = points[i][1];
    }
    
    //calculate
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < n-i; j++) {
            table[j][i] = (table[j+1][i-1]-table[j][i-1])/(points[j+i][0]-points[j][0]);
        }
    }
    
    //test print
    /*for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << table[i][j] << ' ';
        }
        cout << '\n';
    }*/
    
    //copy result to c[]
    for(int i = 0; i < n; i++) {
        c[i] = table[0][i];
    }
}

double hornerMethod(int deg, double x, double coeff[], int index, double points[][2]) {
    
    if(deg > 0) {
        return (hornerMethod(deg-1, x, coeff, index+1, points)*(x-points[index][0]))+coeff[index];
    }
    
    return coeff[index];
}

//Newton's divided differences
double P(double x, double points[][2], int n, double c[]) {
    double result = c[0];
    
    /*for(int i = 1; i < n; i++) {
        double temp = c[i];
        for(int j = 0; j < i; j++) {
            temp *= (x-points[j][0]);
            //cout << points[j][0] << ' ';
        }
        result += temp;
    }*/
    //cout << '\n';
    
    result = hornerMethod(n, x, c, 0, points);
    
    return result;
}

int main(int argc, const char * argv[]) {
    double points[5][2] = {0};
    
    points[0][0] = 0.6;
    points[0][1] = 1.433329;
    points[1][0] = 0.7;
    points[1][1] = 1.632316;
    points[2][0] = 0.8;
    points[2][1] = 1.896481;
    points[3][0] = 0.9;
    points[3][1] = 2.247908;
    points[4][0] = 1.0;
    points[4][1] = 2.718282;
    
    int n = 5;
    double c[n];
    //set c
    cTable(points, n, c);
    
    cout << P(0.82, points, n, c) << '\n';
    cout << P(0.98, points, n, c) << '\n';
    
    return 0;
}
