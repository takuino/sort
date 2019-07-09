#include <stdio.h>

// 素数
#define N 2999

int A[N];

// *p と *q の値を入れ替える関数
void swap(int *p, int *q){
  int tmp;
  tmp = *p;
  *p = *q;
  *q = tmp;
}



int quick_select(int A[], int n, int k){
    int i, j, x, pivot;
    
    // 真ん中の要素をピボットとする
    pivot = A[n/2];
    A[n/2] = A[0];
    A[0] = pivot;
    for(i = j = x = 1; i < n; i++){
        if(A[i] <= pivot){
            swap(A + i, A + j);
            if(A[j] == pivot){
                swap(A + j,A + x);
                x++;
            }
            j++;
        }
    }
    
    if(j - x < k + 1 && k + 1 <= j) return pivot;
    else if(j < k + 1) return quick_select(A + j, n - j, k - j);
    else return quick_select(A + x, j - x, k);
}



int median_of_median(int A[], int n, int k){
    int a, b, B[N], r, i, j, l, pivot;
    if(n <= 5){
        return quick_select(A, n, n/2);
    }
    else{
        for(a = 0; a < n; a++){
            B[a] = A[a];
        }
        for(a = b = 0; 5*a < n - 5; a++){
            B[a] =  quick_select(B + 5*a, 5, 2);
            b++;
        }
        B[b] = quick_select(B + 5*b, n - 5*b, (n - 5*b)/2);
    pivot = median_of_median(B + 0, b + 1, (b + 1)/2);
    for(i = 0; i < n; i++){
        if(pivot == A[i]){
            l = i;
        }
    }
        A[l] = A[0];
        A[0] = pivot;
        for(i = j = 1; i < n; i++){
            if(A[i] <= pivot){
                swap(A + i, A + j);
                j++;}
        }
    swap(A + 0,A + j - 1);
        r = j - 1;
    if(r == k) return pivot;
    else if(r < k) return quick_select(A + j, n - j, k - r - 1);
    else return quick_select(A + 0, j - 1, k);
    }
}



int main(){
  int i;
  A[0] = 0;
  A[1] = 17; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
