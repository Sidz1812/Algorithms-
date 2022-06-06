#include <cstdio>
#include <cstdlib>

#include "sort.h"


int ivector_length(int* v, int n)
{
  int sum;

  sum = 0;
  for (int i = 0; i < n; i++)
    sum += (v[i] < 0) ? -v[i] : v[i];

  return sum;
}

/*
 * insertion sort
 */
void insertion_sort(int** A, int n, int l, int r)
{ 
  int i;
  int* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (ivector_length(A[i], n) > ivector_length(key, n)))
        {
	  A[i+1] = A[i];
	  i = i - 1;
	}

      A[i+1] = key;
    }
}

/*
*   TO IMPLEMENT: Improved Insertion Sort for problem 1.
*/
void insertion_sort_im(int** A, int n, int l, int r)
{
    int* key_Val;
    int i;
    int k = 0;

    int Arr[r+1];
    int* vector_len=Arr;
      
      while(k<=r)
      {
        Arr[k]=(ivector_length(A[k], n));
        k++;
      }



      for (int j = l+1; j <= r; j++)
      {
          key_Val = A[j];
          i = j - 1;
          int key_Len=Arr[j];

          while ((i >= l) && (vector_len[i] > key_Len))
         {
            A[i+1] = A[i];
            Arr[i+1]= Arr[i];
            i = i - 1;
          }

          A[i+1] = key_Val;
          Arr[i+1]=key_Len;
      }

}

/*
*   TO IMPLEMENT: Improved Merge Sort for problem 2.
*/
void merge(int** Arr_1, int* Arr_2, int l, int m, int r, int n)
{
  int *Temp_arr_1 = new int[r-l+1];
  int **temp_arr_2 = new int*[r-l+1];
 
  int i = l;
  int k = 0;
  int j = m + 1;


        while (i <= m && j <= r)
        {
            if (Arr_2[i] < Arr_2[j])
            {
                Temp_arr_1[k] = Arr_2[i];
                temp_arr_2[k]= Arr_1[i];
                k++;
                i++;
            }
        
            else
            {
                Temp_arr_1[k] = Arr_2[j];
                temp_arr_2[k] = Arr_1[j];
                k++;
                j++;
            }
        }


        while (i <= m)
        {
          Temp_arr_1[k] = Arr_2[i];
          temp_arr_2[k] = Arr_1[i];
          k++;
          i++;
        }


        while (j <= r)
        {
          Temp_arr_1[k] = Arr_2[j];
          temp_arr_2[k] = Arr_1[j];
          k++;
          j++;
        }


       for (i = l; i <= r; i++)
       {
         Arr_2[i] = Temp_arr_1[i-l];
         Arr_1[i] = temp_arr_2[i-l];
       }

}

void merge_sort_steps(int** Arr_1, int* Arr_2, int l, int r, int n)
{
     int m;
        if(l < r)
        {
            m = (l + r) / 2;
            merge_sort_steps(Arr_1, Arr_2, l, m, n);
            merge_sort_steps(Arr_1, Arr_2, m+1, r, n);
            merge(Arr_1, Arr_2, l, m,r, n);
        }
    
}


void merge_sort(int** A, int n, int p, int r)
{
    int i = p;
    int vectorLengthArray[r+1];
      while(i<=r)
      {
        vectorLengthArray[i] = ivector_length(A[i], n);
        i++;
      }
        merge_sort_steps(A,vectorLengthArray,p,r,n);
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(int** A, int n, int l, int r)
{
  for (int i = l+1; i <= r; i++)
    if (ivector_length(A[i-1], n) > ivector_length(A[i], n))
      return false;
  return true;
}


/*
 * generate sorted/reverse/random arrays of type hw1type
 */
int** create_ivector(int n, int m)
{
  int** iv_array;

  iv_array = new int*[m];
  for (int i = 0; i < m; i++)
    iv_array[i] = new int[n];

  return iv_array;
}

void remove_ivector(int** iv_array, int m)
{
  for (int i = 0; i < m; i++)
    delete[] iv_array[i];
  delete[] iv_array;
}

int** create_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = (i+j)/n;

  return iv_array;
}

int** create_reverse_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = ((m-i)+j)/n;

  return iv_array;
}

int** create_random_ivector(int n, int m, bool small)
{
  random_generator rg;
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      {
	rg >> iv_array[i][j];
	if (small)
	  iv_array[i][j] %= 100;
	else
	  iv_array[i][j] %= 65536;
      }

  return iv_array;
}

