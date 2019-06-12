#include <stdio.h>

void max_heapify(int *a, int length, int i);
void build_max_heap(int *a, int length);
void heap_sort(int *a, int length);

//调整堆lg(n)
void
max_heapify(int *a, int length, int i) {
    int left, right, largest;

    left = 2 * i + 1;
    right = 2 * i + 2;

    if (left <= (length - 1) && a[left] > a[i]) {
        largest = left;
    } else {
        largest = i;
    }

    if (right <= (length - 1) && a[right] > a[largest]) {
        largest = right;
    }

    if (largest != i) {
        a[i] = a[i] + a[largest];
        a[largest] = a[i] - a[largest];
        a[i] = a[i] - a[largest];
        max_heapify(a, length, largest);
    }
}

//建堆O(n)
void
build_max_heap(int *a, int length) {
    int i;

    for (i = (length / 2) - 1; i >= 0; i--) {
        max_heapify(a, length, i);
    }
}

void
heap_sort(int *a, int length) {
    int i;

    build_max_heap(a, length);
    
    for (i = length - 1; i > 0; i--) {
        a[0] = a[0] + a[i];
        a[i] = a[0] - a[i];
        a[0] = a[0] - a[i];
        length--;
        max_heapify(a, length, 0);
    }
}


int main() {
    int a[5] = {12, 4, 7, 3, 6};
    int i;

    /*
    for (i = 0; i < 5; i++) {                                                                                                            
         printf("%d\n", a[i]);
    }
    */

    heap_sort(a, 5);

    for (i = 0; i < 5; i++) {
        printf("%d\n", a[i]);
    }

    return 0;
}
