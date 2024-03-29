#include "sortings.h"
#include <string.h>
#include <stdlib.h>

#define ASCII_CONST 128

void swap(char **str1, char **str2)
{
    char *tmp = *str1;
    *str1 = *str2;
    *str2 = tmp;
}

array_size_t get_max_length(strings_array_t strings, size_t strings_count)
{
    size_t max = strlen(strings[0]);
    for (size_t i = 0; i < strings_count; ++i)
    {
        size_t tmp_size = strlen(strings[i]);
        if (tmp_size > max)
        {
            max = tmp_size;
        }
    }
    return max;
}

void count_sort(strings_array_t array, size_t size, size_t k, comparator_func_t cmp)
{
    strings_array_t tmp_array = malloc(sizeof(char *) * size);
    int *ascii_array = malloc(sizeof(int) * ASCII_CONST);
    for (int i = 0; i < ASCII_CONST; ++i)
        ascii_array[i] = 0;
    for (size_t i = 0; i < size; ++i)
    {
        int tmp = k < strlen(array[i]) ? (int)(unsigned char)array[i][k] + 1 : 0;
        ascii_array[tmp]++;
    }
    if (cmp("a", "b") < 0)
    {
        for (int i = 1; i < ASCII_CONST; ++i)
            ascii_array[i] += ascii_array[i - 1];
    } else
    {
        for (int i = ASCII_CONST - 2; i >= 0; --i)
            ascii_array[i] += ascii_array[i + 1];

    }
    for (int i = (int)size - 1; i >= 0; --i)
    {
        tmp_array[ascii_array[k < strlen(array[i]) ? (int)(unsigned char)array[i][k] + 1 : 0] - 1] = array[i];
        ascii_array[k < strlen(array[i]) ? (int)(unsigned char)array[i][k] + 1 : 0]--;
    }
    for (size_t i = 0; i < size; ++i)
    {
        array[i] = tmp_array[i];
    }
    free(tmp_array);
    free(ascii_array);
}

void bubble(strings_array_t array, array_size_t size, comparator_func_t cmp)
{
    for (size_t i = 0; i < size; ++i)
        for (size_t j = i; j < size; ++j)
            if (cmp(array[j], array[i]) < 0)
                swap(&array[i], &array[j]);
}

void insertion(strings_array_t array, array_size_t size, comparator_func_t cmp)
{
    for (array_size_t i = 1; i < size; i++)
    {
        char *tmp = array[i];
        for (int j = (int)i - 1; j >= 0; j--)
        {
            if (cmp(array[j], tmp) < 0)
                break;
            array[j + 1] = array[j];
            array[j] = tmp;
        }
    }
}

void merge(strings_array_t array, array_size_t size, comparator_func_t cmp)
{
    array_size_t step = 1;
    strings_array_t  temp = malloc(size * sizeof(char *));
    while (step < size)
    {
        array_size_t index = 0;
        array_size_t left = 0;
        array_size_t middle = left + step;
        array_size_t right = left + step * 2;
        do
        {
            middle = middle < size ? middle : size;
            right = right < size ? right : size;
            array_size_t i1 = left, i2 = middle;
            for (; i1 < middle && i2 < right; )
                if (cmp(array[i1], array[i2]) < 0)
                    temp[index++] = array[i1++];
                else
                    temp[index++] = array[i2++];
            while (i1 < middle)
                temp[index++] = array[i1++];
            while (i2 < right)
                temp[index++] = array[i2++];
            left += step * 2;
            middle += step * 2;
            right += step * 2;
        } while (left < size);
        for (array_size_t i = 0; i < size; i++)
            array[i] = temp[i];
        step *= 2;
    }
    free(temp);
}

void quick_split(strings_array_t array, unsigned int begin, unsigned int end, comparator_func_t cmp)
{
    while (begin < end)
    {
        if ((array[begin] <= array[(begin + end - 1) / 2] && array[(begin + end - 1) / 2] <= array[end - 1]) ||
            (array[end - 1] <= array[(begin + end - 1) / 2] && array[(begin + end - 1) / 2] <= array[begin]))
            swap(&array[begin], &array[(begin + end - 1) / 2]);
        else if ((array[begin] <= array[end - 1] && array[end - 1] <= array[(begin + end - 1) / 2]) ||
                 (array[(begin + end - 1) / 2] <= array[end - 1] && array[end - 1] <= array[begin]))
            swap(&array[begin], &array[end - 1]);
        unsigned int left = begin, middle = begin + 1, right = end;
        for (unsigned int i = 0; i < end - begin - 1; i++)
        {
            const int cmp_result = cmp(array[middle], array[begin]);
            if (cmp_result < 0) {
                left++;
                swap(&array[middle], &array[left]);
                middle++;
            } else if (cmp_result > 0) {
                right--;
                swap(&array[middle], &array[right]);
            } else
                middle++;
        }
        swap(&array[begin], &array[left]);
        quick_split(array, begin, left, cmp);
        begin = right;
    }
}

void quick(strings_array_t array, array_size_t size, comparator_func_t cmp)
{
    quick_split(array, 0, size, cmp);
}

void radix(strings_array_t array, array_size_t size, comparator_func_t cmp)
{
    size_t max = get_max_length(array, size);
    for (size_t digit = max; digit > 0; digit--) {
        count_sort(array, size, digit - 1, cmp);
    }
}
