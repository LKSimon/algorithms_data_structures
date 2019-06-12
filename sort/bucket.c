#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned int  max(unsigned int *p, unsigned int length);//找最大值
void 		  bucket_sort(unsigned int *p, unsigned int length, unsigned int max);//实现桶排序

int main() {
	unsigned int array[11] = {2, 3, 7, 4, 11, 8, 9, 7, 12, 15, 13};
	unsigned int m, length, i;

	length = sizeof(array) / sizeof(unsigned int);
	m = max(array, length);

	printf("待排序数组遍历： \n");
	for (i = 0; i < length; i++) {
		printf("array[%u] = %u\n", i, array[i]);
	}

	printf("length = %u\nmax = %u\n", length, m);
	bucket_sort(array, length, m);
	
	//遍历数组
	printf("桶排序后数组遍历: \n");
	for (i = 0; i < length; i++) {
		printf("array[%u] = %u\n", i, array[i]);
	}

	return 0;
}


unsigned int max(unsigned int *p, unsigned int length) {
	unsigned int max;
	int i;

	if (p == NULL) {
		printf("指针p不能为空指针");
		exit(-1);
	}
	
	if (length <= 0) {
		printf("length 需大于 0");
		exit(-1);
	}

	for (i = 1, max = p[0]; i < length; i++) {
		if (max < p[i]) {
			max = p[i];
		}
	}

	return max;
}

void bucket_sort(unsigned int *p, unsigned int length, unsigned int max) {
	unsigned int *p1;
	unsigned int i, j;

	if (p == NULL) {
		printf("指针p不能为空指针");
		exit(-1);
	}

	if (length <= 0) {
		printf("数组长度需大于零");
		exit(-1);
	}

	if (length == 1) {
		return;
	}

	//申请内存
	p1 = (unsigned int *)malloc((max + 1) * sizeof(unsigned int));
	if (p1 == NULL) {
		printf("malloc函数申请内存失败");
		exit(-1);
	}
	memset(p1, 0, ((max + 1) * sizeof(unsigned int)));

	//计数
	for	(i = 0; i < length; i++) {
		p1[p[i]]++;
	}

	//排序
	for (i = 0, j = 0; i <= max && j < length; i++) {
		if (p1[i] == 0) {
			continue;
		}

		for (; p1[i] > 0; p1[i]--) {
			p[j++] = i;
		}
	}

	free(p1);
}
