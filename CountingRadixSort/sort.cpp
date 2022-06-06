#include <cstdio>
#include <cstdlib>

#include "sort.h"

/* 
 * HW 2 part
 */
int string_compare(char* s1, char *s2)
{ 
/*
 * We assume that s1 and s2 are non-null pointers
 */
  int i;

  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
    return 0;
  else
    {
      if (s1[i] < s2[i])
	return -1;
      else
	return 1;
    }
} /*>>>*/

void insertion_sort(char** A, int l, int r)
{ 
  int i;
  char* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (string_compare(A[i], key) > 0))
        {
	  A[i+1] = A[i];
	  i = i - 1;
	}

      A[i+1] = key;
    }
}


 int string_compare_2(char* s1, char *s2, int A_length, int key_length, int d)
{

  if(d<=key_length && d<=A_length)
  {
    if(s1[d-1] == s2[d-1])
       return 0;
    
    else if (s1[d-1] < s2[d-1])
        return -1;
    
    else
        return 1;
  }
    
  else if(d>key_length && d>A_length)
    return 0;
  
  else if(d<=key_length && d>A_length)
    return -1;
  
  else
    return 1;
  
}

void insertion_sort_digit(char** A, int* A_len, int l, int r, int d)
{
    int key_length;
    int i;
    char* Key;
    int k;
   

    for (k = l+1; k <= r; k++)
    {
        Key = A[k];
        key_length = A_len[k];
        i = k - 1;
        while ((i >= l) && ( 0 < string_compare_2(A[i], Key, A_len[i], key_length, d) ))
        {
            A[i+1] = A[i];
            A_len[i+1] = A_len[i];
            i = i - 1;
        }
        A[i+1] = Key;
        A_len[i+1] = key_length;
    }


}



void counting_sort_digit(char** A, int* A_len, char** B, int* B_len, int n, int d)
{
    
    int max = 256;
    int *count_Int  = new int[max];
    int i;

    for(i = 0; i<=max; i++)
    {
        count_Int[i] = 0;
    }

    for(i = 0; i < n; i++)
    {
        if(d>A_len[i])
        {
        
            count_Int [0]++;
        }
        else
        {
            count_Int[A[i][d-1]]++;
        }
    }
    
    for(int i = 1; i<=max; i++)
    {
        count_Int [i] =  count_Int [i] + count_Int[i-1];
    }
    
    for(int i = n-1; i>=0; i--)
    
    {
        if(d<=A_len[i])
        {
          B[count_Int [A[i][d-1]]-1] = A[i];
          B_len[count_Int[A[i][d-1]]-1] = A_len[i];
          count_Int[A[i][d-1]] = count_Int[A[i][d-1]] - 1;
        }
        else
        {
          B[count_Int [0]-1] = A[i];
          B_len[count_Int [0]-1] = A_len[i];
          count_Int [0] = count_Int [0] - 1;
        }
    }
    
    for(int i = 0; i<n; i++)
    {
        A[i] = B[i];
        A_len[i] = B_len[i];
    }
    
    delete[] count_Int ;
}

void radix_sort_is(char** A, int* A_len, int n, int m)
{ 
    for(int d = m ; d>0; d--)

      {
        insertion_sort_digit(A, A_len, 0, n-1, d);
      }
}

void radix_sort_cs(char** A, int* A_len, int n, int m)
{
    char** outputArray= new char*[n];
     int* outputLenght = new int[n];
     
     for(int d = m ; d>0; d--)

     {
       counting_sort_digit(A, A_len, outputArray, outputLenght, n, d);
     }
     
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(char** A, int l, int r)
{
  for (int i = l+1; i < r; i++)
    if (string_compare(A[i-1],A[i]) > 0)
      return false;
  return true;
}
