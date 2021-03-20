#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sortings.h"

typedef void (*sort_func_t)(strings_array_t, array_size_t, comparator_func_t);

int is_num(const char *string)
{
    for (int i = 0; ; i++)
    {
        if (string[i] == 0)
            return 1;
        if (string[i] < '0' || string[i] > '9')
            return 0;
    }
}

int des_cmp(const char *str1, const char *str2) {
    return strcmp(str2, str1);
}

int set_arguments_value(int argc, char **argv, int *strings_num, char *in_file, char *out_file,
                        sort_func_t *sortFunc, comparator_func_t *cmp)
{
    if (argc != 6)
        return -1;
    if (!is_num(argv[1]))
        return -1;
    *strings_num = (int)strtoll(argv[1], NULL, 10);
    if (*strings_num < 0)
        return -1;
    strncpy(in_file, argv[2], 100);
    strncpy(out_file, argv[3], 100);
    if (strcmp(argv[4], "bubble") == 0)
    {
        *sortFunc = bubble;
    } else if (strcmp(argv[4], "insertion") == 0)
    {
        *sortFunc = insertion;
    } else if (strcmp(argv[4], "merge") == 0)
    {
        *sortFunc = merge;
    } else if (strcmp(argv[4], "quick") == 0)
    {
        *sortFunc = quick;
    } else if (strcmp(argv[4], "radix") == 0)
    {
        *sortFunc = radix;
    } else
        return -1;
    if (strcmp(argv[5], "asc") == 0)
    {
        *cmp = strcmp;
    } else if (strcmp(argv[5], "des") == 0)
    {
        *cmp = des_cmp;
    } else
    {
        return -1;
    }
    return 0;
}

int read_strings_from_file(const char *filename, strings_array_t strings, int strings_num)
{
    FILE *input = fopen(filename, "rt");
    if (input == NULL)
        return -1;
    for (int i = 0; i < strings_num; ++i)
    {
        if (fgets(strings[i], MAX_INPUT_STRING_SIZE, input) == NULL)
            return -1;
    }
    char *last_string = strings[strings_num - 1];
    size_t last_string_len = strlen(last_string);
    if (last_string[last_string_len - 1] != '\n')
    {
        last_string[last_string_len] = '\n';
        last_string[last_string_len + 1] = '\0';
    }
    fclose(input);
    return 0;
}

int write_strings_to_file(const char *filename, strings_array_t strings, int strings_num)
{
    FILE *output = fopen(filename, "wt");
    if (output == NULL)
        return -1;
    for (int i = 0; i < strings_num; ++i)
    {
        if (fputs(strings[i], output) == -1)
            return -1;
    }
    fclose(output);
    return 0;
}

int main(int argc, char *argv[])
{
    array_size_t strings_num;
    char in_file[100];
    char out_file[100];
    sort_func_t sortFunc;
    comparator_func_t cmp;
    int setting_result = set_arguments_value(argc, argv, &strings_num, in_file, out_file, &sortFunc, &cmp);
    if (setting_result != 0)
        return setting_result;
    if (strings_num == 0)
    {
        char *n[1] = {"\n"};
        int writing_result = write_strings_to_file(out_file, n, 1);
        if (writing_result != 0)
            return -1;
        return 0;
    }
    strings_array_t strings = NULL;
    strings = malloc(sizeof(char *) * strings_num);
    if (strings == NULL)
        return -1;
    for (array_size_t i = 0; i < strings_num; ++i)
        strings[i] = malloc(sizeof(char) * MAX_INPUT_STRING_SIZE);
    int reading_result = read_strings_from_file(in_file, strings, strings_num);
    if (reading_result != 0)
        return reading_result;
    sortFunc(strings, strings_num, cmp);
    int writing_result = write_strings_to_file(out_file, strings, strings_num);
    if (writing_result != 0)
        return writing_result;
    for (array_size_t i = 0; i < strings_num; ++i)
        free(strings[i]);
    free(strings);
    return 0;
}