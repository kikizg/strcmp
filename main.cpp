#include <cstdio>
#include <cstring>
#include "clock.h"

#define ITER 1000000000

void test_strncmp(double *time, int *value);
void test_strcmp(double *time, int *value);
void test_memcmp(double *time, int *value);
void test_fastcompare(double *time, int *value);
void test_simplecompare(double *time, int *value);
void test_bcmp(double *time, int *value);
void test_bncmp(double *time, int *value);

int fast_compare(const char *ptr0, const char *ptr1, int len);
int simple_compare(const char *ptr0, const char *ptr1, int len);
int bcmp(const char *ptr0, const char *ptr1);
int bncmp(const char *ptr0, const char *ptr1, int len);

int main (int argc, char **argv, char **envp)
{
	double time;
	int value;

	test_strncmp(&time, &value);
	printf("Function int strncmp(char*, char*, size_t) took %f [second] and returns %i\n", time, value);

	test_strcmp(&time, &value);
	printf("Function int strcmp(char*, char*) took %f [second] and returns %i\n", time, value);

	test_memcmp(&time, &value);
	printf("Function int memcmp(char*, char*, size_t) took %f [second] and returns %i\n", time, value);

	test_fastcompare(&time, &value);
	printf("Function int fastcompare(char*, char*, int) took %f [second] and returns %i\n", time, value);

	test_bncmp(&time, &value);
	printf("Function int bncmp(char*, char*, int) took %f [second] and returns %i\n", time, value);

	test_bcmp(&time, &value);
	printf("Function int bcmp(char*, char*) took %f [second] and returns %i\n", time, value);

	test_simplecompare(&time, &value);
	printf("Function int simplecompare(char*, char*, int) took %f [second] and returns %i\n", time, value);
}

void test_strncmp(double *time, int *value)
{
	char str1[] = "This is a first string.";
	char str2[] = "This is a second string.";
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	size_t len = len1 > len2 ? len2 : len1;

	RN::Clock clk;

	int ret;
	for (int i = 0; i < ITER; i++)
	{
		str1[0] += i;
		str2[0] += str1[0] + i;
		ret = strncmp(str1, str2, len);
	}
	*time = clk.Now();
	*value = ret;
}

void test_strcmp(double *time, int *value)
{
	char str1[] = "This is a first string.";
	char str2[] = "This is a second string.";

	RN::Clock clk;

	int ret;
	for (int i = 0; i < ITER; i++)
	{
		str1[0] += i;
		str2[0] += str1[0] + i;
		ret = strcmp(str1, str2);
	}
	*time = clk.Now();
	*value = ret;
}

void test_memcmp(double *time, int *value)
{
	char str1[] = "This is a first string.";
	char str2[] = "This is a second string.";
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	size_t len = len1 > len2 ? len2 : len1;

	RN::Clock clk;

	int ret;
	for (int i = 0; i < ITER; i++)
	{
		str1[0] += i;
		str2[0] += str1[0] + i;
		ret = memcmp(str1, str2, len);
	}
	*time = clk.Now();
	*value = ret;
}

void test_fastcompare(double *time, int *value)
{
	char str1[] = "This is a first string.";
	char str2[] = "This is a second string.";
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	size_t len = len1 > len2 ? len2 : len1;

	RN::Clock clk;

	int ret;
	for (int i = 0; i < ITER; i++)
	{
		str1[0] += i;
		str2[0] += str1[0] + i;
		ret = fast_compare(str1, str2, len);
	}
	*time = clk.Now();
	*value = ret;
}

void test_simplecompare(double *time, int *value)
{
	char str1[] = "This is a first string.";
	char str2[] = "This is a second string.";
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	size_t len = len1 > len2 ? len2 : len1;

	RN::Clock clk;

	bool ret;
	for (int i = 0; i < ITER; i++)
	{
		str1[0] += i;
		str2[0] += str1[0] + i;
		ret = simple_compare(str1, str2, len);
	}
	*time = clk.Now();
	*value = ret;
}

void test_bncmp(double *time, int *value)
{
	char str1[] = "This is a first string.";
	char str2[] = "This is a second string.";
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	size_t len = len1 > len2 ? len2 : len1;

	RN::Clock clk;

	bool ret;
	for (int i = 0; i < ITER; i++)
	{
		str1[0] += i;
		str2[0] += str1[0] + i;
		ret = bncmp(str1, str2, len);
	}
	*time = clk.Now();
	*value = ret;
}
void test_bcmp(double *time, int *value)
{
	char str1[] = "This is a first string.";
	char str2[] = "This is a second string.";
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	size_t len = len1 > len2 ? len2 : len1;

	RN::Clock clk;

	bool ret;
	for (int i = 0; i < ITER; i++)
	{
		str1[0] += i;
		str2[0] += str1[0] + i;
		ret = bcmp(str1, str2);
	}
	*time = clk.Now();
	*value = ret;
}

int fast_compare(const char *ptr0, const char *ptr1, int len)
{
	int fast = len / sizeof(size_t) + 1;
	int offset = (fast - 1) * sizeof(size_t);
	int current_block = 0;

	if (len <= sizeof(size_t))
	{
		fast = 0;
	}


	size_t *lptr0 = (size_t*)ptr0;
	size_t *lptr1 = (size_t*)ptr1;

	while(current_block < fast)
	{
		if (lptr0[current_block] ^ lptr1[current_block])
		{
			int pos;
			for (pos = current_block * sizeof(size_t); pos < len; ++pos)
			{
				if ((ptr0[pos] ^ ptr1[pos]) || (ptr0[pos] == 0) || (ptr1[pos] == 0))
				{
					return  (int)((unsigned char)ptr0[pos] - (unsigned char)ptr1[pos]);
				}
			}
		}
		++current_block;
	}

	while(len > offset)
	{
		if(ptr0[offset] ^ ptr1[offset])
		{ 
			return (int)((unsigned char)ptr0[offset] - (unsigned char)ptr1[offset]); 
		}
		++offset;
	}
	return 0;
}

int simple_compare(const char *ptr0, const char *ptr1, int len)
{
	int fast = len / sizeof(size_t) + 1;
	int offset = (fast - 1) * sizeof(size_t);

	if (len >= sizeof(size_t))
	{
		int current_block = 0;
		const size_t *lptr0 = reinterpret_cast<const size_t*>(ptr0);
		const size_t *lptr1 = reinterpret_cast<const size_t*>(ptr1);

		while(current_block < fast)
		{
			if (lptr0[current_block] ^ lptr1[current_block])
			{
				return 1;
			}
			++current_block;
		}
	}

	while (len > offset)
	{
		if(ptr0[offset] ^ ptr1[offset])
		{ 
			return static_cast<int>(
					static_cast<unsigned char>(ptr0[offset]) -
					static_cast<unsigned char>(ptr1[offset])); 
		}
		++offset;
	}
	return 0;
}

int bcmp(const char *ptr0, const char *ptr1)
{
	do
	{
		if (*ptr0 ^ *ptr1)
		{
			return 1;
		}
		ptr0++, ptr1++;
	} while (*ptr0 && *ptr1);
	return 0;
}

int bncmp(const char *ptr0, const char *ptr1, int len)
{
	int idx = 0;
	do
	{
		if (*ptr0 ^ *ptr1)
		{
			return 1;
		}
		ptr0++, ptr1++, idx++;
	} while (idx < len && *ptr0 && *ptr1);
	return 0;
}
