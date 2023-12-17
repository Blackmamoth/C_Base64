#include "base64.h"

void to_binary_string(char dest[], const char src[])
{
    size_t length = strlen(src);
    char *binary_string = (char *)malloc((length * 8) + 1);
    binary_string[0] = '\0';
    for (size_t i = 0; i < length; i++)
    {
        char ch = src[i];
        for (int j = 7; j >= 0; j--)
        {
            if (ch & (1 << j))
            {
                strcat(binary_string, "1");
            }
            else
            {
                strcat(binary_string, "0");
            }
        }
    }
    strcpy(dest, binary_string);
    free(binary_string);
}

void encode(char src[])
{
    int i = 0;
    size_t length = strlen(src);
    char binary_string[(length * 8) + 1];
    if (binary_string == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for char buffer.\n");
        exit(EXIT_FAILURE);
    }
    to_binary_string(binary_string, src);
    length = strlen(binary_string);
    while (length % 6 != 0)
    {
        strcat(binary_string, "0");
        length = strlen(binary_string);
    }
    int num_of_segments = (length + 5) / 6;
    char segments[num_of_segments][7];
    for (i = 0; i < num_of_segments; i++)
    {
        strncpy(segments[i], binary_string + i * 6, 6);
        segments[i][6] = '\0';
    }
    int decimal_values[num_of_segments];
    for (i = 0; i < num_of_segments; i++)
    {
        decimal_values[i] = strtol(segments[i], NULL, 2);
    }
    char base64_string[1024];
    for (i = 0; i < num_of_segments; i++)
    {
        base64_string[i] = b64_table[decimal_values[i]];
    }
    length = strlen(base64_string);
    while (length % 4 != 0)
    {
        base64_string[i] = '=';
        length = strlen(base64_string);
        i++;
    }
    base64_string[i] = '\0';
    printf("%s", base64_string);
}

int main()
{
    char src[] = "g";
    encode(src);
}