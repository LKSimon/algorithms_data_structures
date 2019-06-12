#include <stdio.h>
#include <stdlib.h>

#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )

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

/*合并所有有序数组为1的数组*/
void merge_group(int *a, int len, int gap) {
    int i;

    for (i = 0; (((2 * gap) + i) - 1) < len; i += (2 * gap)) {
        merge(a, i, ((i + (2 * gap)) - 1));
    }

    if ((i + gap - 1) < (len - 1)) {
        merge(a, i, len - 1);
    }
}

/*合并, 按照数组元素个数为1开始，然后合并数组元素个数为2的数组，依次4、8...直到不满足数组索引与数组长度的关系*/
void merge_sort_downup(int *a, int len) {
    int gap;
    if (a == NULL || len <= 0) {
        return;
    }

    for (gap = 1; gap < len; gap = gap * 2) {
        merge_group(a, len, gap);
    }
}

int main() {
    int a[] = {9, 8, 6, 12, 1, 2, 4, 7};
    int i;

    merge_sort_downup(a, LENGTH(a));

    for (i = 0; i < LENGTH(a); i++) {
        printf("%d\n", a[i]);                                                                                                      
    }  

    return 0;
}
