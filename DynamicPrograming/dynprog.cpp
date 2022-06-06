#include <cstring>
#include <iostream>
#include <limits.h>

#include "dynprog.h"

using namespace std;


/*
 * Bottom up implementation of Smith-Waterman algorithm
 */
void SW_bottomUp(char* X, char* Y, char** P, int** H, int n, int m){
    
    for(int i=0; i<=n; i++)
    {
        H[i][0] = 0;
        P[i][0] = '0';
    }
    
    for(int i=0; i<=m; i++)
    {
        H[0][i]=0;
        
    }
    
    int p1, p2, p3;
    for (int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            if (X[i-1]==Y[j-1])
                p1 = H[i-1][j-1] + 2;
            
            else
            {
                p1 = H[i-1][j-1] - 1;
            }
            
            p2 = H[i-1][j] - 1;
            p3 = H[i][j-1] - 1;
            
            H[i][j] = max(max(p1,p2),max(p2,p3));
            
            if (H[i][j] == p1)
                P[i][j]= 'd';
            
            else if (H[i][j] == p2)
                P[i][j]= 'u';
            
            else
                P[i][j]= 'l';
        }
    }

}

/*
 * Top-down with memoization implementation of Smith-Waterman algorithm
 */
void memoized_SW(char* X, char* Y, char** P, int** H, int n, int m)
{
    for (int i=0; i<=n; i++)
    {
        H[i][0] = 0;
        P[i][0]= '0';
    }
    for (int i = 0; i<=m; i++)
    {
        H[0][i]=0;
        P[i][0]='0';
    }
    for(int i=1; i<n+1;i++)
    {
        for(int j=1; j<m+1;j++)
        {
            H[i][j] = INT32_MIN;
        }
    }
    memoized_SW_AUX(X, Y, P, H, n, m);
}

/*
 * Auxilary recursive function of top-down with memoization implementation of Smith-Waterman algorithm
 */
int memoized_SW_AUX(char* X, char* Y, char** P, int** H, int n, int m)
{
    int p1, p2, p3;
    if(n==0 || m==0)
        return 0;
    
    else if(H[n][m]!= INT32_MIN)
        return H[n][m];
    
    else if(X[n-1]==Y[m-1])
        p1 = memoized_SW_AUX(X, Y, P, H, n-1, m-1)+ 2;
    
    else
    {
        p1 = memoized_SW_AUX(X, Y, P, H, n-1, m-1) - 1;
    }
    
    p2 = memoized_SW_AUX(X, Y, P, H, n-1, m) - 1;
    p3 = memoized_SW_AUX(X, Y, P, H, n, m-1) - 1;
    H[n][m]= max(max(p1,p2),max(p2,p3));
    
    if(H[n][m]== p1)
        P[n][m] = 'd';
    
    
    else if(H[n][m]==p2)
        P[n][m]= 'u';
    
    else
    {
        P[n][m] = 'l';
    }
    
    return H[n][m];
}

/*
 * Print X'
 */
void print_Seq_Align_X(char* X, char** P, int n, int m)
{
    
    if(n<=0 || m<=0)
        return;
    
    if (P[n][m]=='d')
    {
        print_Seq_Align_X(X, P, n-1, m-1);
        cout<<X[n-1];
    }
    else if(P[n][m] == 'l')
    {
        print_Seq_Align_X(X, P, n, m-1);
        cout<< "-";
    }
    else
    {
        print_Seq_Align_X(X, P, n-1, m);
        cout<< X[n-1];
    }
	
}

/*
 * Print Y'
 */
void print_Seq_Align_Y(char* Y, char** P, int n, int m)
{
    if(n<=0 || m<=0)
        return;
    
    if (P[n][m]=='d')
    {
        print_Seq_Align_Y(Y, P, n-1, m-1);
        cout<<Y[m-1];
    }
    else if(P[n][m] == 'l')
    {
        print_Seq_Align_Y(Y, P, n, m-1);
        cout<< Y[m-1];
    }
    else
    {
        print_Seq_Align_Y(Y, P, n-1, m);
        cout<< "-";
    }
}
