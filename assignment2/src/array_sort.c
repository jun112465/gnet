/*
#include "../header/queue.h"

void quick_sort(int *arr, int left, int right){
    // 내림차순 정렬
    if(left >= right) return;

    // pivot을 가운데 값으로 설정
    int pivot = right;
    int check = left;
    int next = left;
    int swp;

    // partitioning
    while(check < pivot){
        if(arr[check] > arr[pivot]){
            swp = arr[next];
            arr[next] = arr[check];
            arr[check] = swp;
            next++;
        }
        check++;
    }
    swp = arr[next];
    arr[next] = arr[pivot];
    arr[pivot] = swp;

    // divide & conquer
    quick_sort(arr, left, next - 1);    // Sort elements before the pivot
    quick_sort(arr, next + 1, right);   // Sort elements after the pivot
}


void merge(int *arr, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 임시 배열 생성
    int L[n1], R[n2];

    // 임시 배열에 데이터 복사
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // 두 배열을 병합
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? R[j++] : L[i++];
    
    // 남은 요소들을 복사
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void merge_sort(int *arr, int left, int right){
    if(left < right){
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
*/