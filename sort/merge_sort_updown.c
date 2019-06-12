#include <stdio.h>
#include <stdlib.h>

#define LENGTH(array) ((sizeof(array)) / (sizeof(array[0])))

/***********自上而下进行归并排序**********/
/*
 *合并两个有序的数组，使其有序，
 */
void merge(int *a, int start, int end)
{
    int middle;
    int i, j, k;
    int *temp;

    if (NULL == a || start > end) {
        exit(1);
    }

    if (start == end) {
        return;
    }

    middle = (start + end) / 2;
    i = start;
    j = middle + 1;
    temp = (int *)malloc(sizeof(int) * (end + 1));
    memset(temp, 0, sizeof(int) * (end + 1));
    k = 0; 

    while (i <= middle && j <= end) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }

    while (i <= middle) {
        temp[k++] = a[i++];
    }

    while (j <= end) {
        temp[k++] = a[j++];
    }
    
    for (i = 0; i < k; i++) {
        a[i + start] = temp[i];//重点
    }

    free(temp);
    temp = NULL;
}

void merge_sort(int *a, int start, int end) {//自上而下
    int middle = 0;

    if (NULL == a || start >= end) {
        return;
    }

    middle = (start + end) / 2;
    /*
     * 开始递归，产生两个有序数组
     */
    merge_sort(a, start, middle);
    merge_sort(a, middle + 1, end);
    merge(a, start, end);
}

int main() {
    int a[] = {9, 8, 6, 12, 1, 2, 4, 7};
    int i;

    merge_sort(a, 0, LENGTH(a) - 1);

    for (i = 0; i < LENGTH(a); i++) {
        printf("%d\n", a[i]);
    }

    return 0;
}
