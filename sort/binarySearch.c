#include <stdio.h>
#include <stdlib.h>

//二分查找， 以int型由小到大有序数组为例实现二分查找
int *binarySearch(int *array, int length, int aim) {
	int left, right, middle;
	int i = 0;

	//验证数组是否由小到大
	for (i = 0; i < (length - 1); i++) {
		if (array[i] > array[i + 1]) {
			printf("所传递参数数组非由小到大有序");
			exit(-1);
		}
	}

	middle = (length + 1) / 2;
	left = 0;
	right = length - 1;

	while(left <= right) {
		if (aim > array[middle]) {
			left = middle + 1;
		} else if (aim < array[middle]) {
			right = middle - 1;
		} else {
			printf("已找到目标数字%d, 要查找的数字在数组的地址是%p\n", aim, &array[middle]);
			return &array[middle];
		}

		middle = (left + right) / 2;
	}

	printf("未找到目标数字%d\n", aim);

	return NULL;
}

//测试binarySearch函数
void binarySearchTest() {
	int arr[7] = {1,2,3,4,5,6,7};//原数组
	int aimArr[3] = {2, 1, 7};//待查找目标数组
	int aim, i, *ptr = NULL;

	printf("开始测试int型有序数组二分查找， 原数组为：\n");
	for (i = 0; i < (sizeof(arr) / sizeof(int)); i ++) {
		printf("arr[%d] = %d, 地址为： %p\n", i, arr[i], &arr[i]);
	}

	for (i = 0; i < (sizeof(aimArr) / sizeof(int)); i ++) {
		aim = aimArr[i];
		printf("\n\n开始测试查找数字：%d\n", aim);
		ptr = binarySearch(arr, (sizeof(arr) / sizeof(int)), aim);
		if(NULL == ptr) {
			printf("未找到数字%d\n", aim);
		} else {
			printf("找到了数字%d, 地址为%p\n", aim, ptr);
		}
	}
	printf("\n全部测试完成\n");
}

int main() {
	binarySearchTest();

	return 0;
}
