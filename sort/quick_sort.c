#include <stdio.h>

#define LENGTH(array) (sizeof(array) / sizeof(a[0]))

void quick_sort(int *a, int left, int right)
{
    int i, j, m, key;

    i = left;
    j = right;
    key = a[left];//以每次数组的第一个元素为key值。

    if (left >= right) {
        return;
    }

    while (i < j) {
        while(i < j && a[j] > key) {
            j--;
        }
        a[i] = a[j];
    
        while(i < j && a[i] <=  key) {
            i++;
        }
        a[j] = a[i];
    }
    a[i] = key;//此时i = j.

    quick_sort(a, left, i - 1);
    quick_sort(a, i + 1, right);
}


int main()
{
    int i;
    int a[8] = {2, 3, 12, 45, 23, 42, 23, 56}; 

    quick_sort(a, 0, 7);

    for (i = 0; i < 8; i++) {
        printf("%d\n", a[i]);
    }

    return 0;
}
