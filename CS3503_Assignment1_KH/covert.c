#include <string.h>
#include <stdint.h>
#include "convert.h"
#include <stdio.h>

//Filter which function to use based on the function_name, then use function.
void useCommand(const char* function_name,uint32_t input_value,int input_base, char *expected_output, FILE *outfile) {
    char got[65]; //Hold computed results

    if (strcmp(function_name,"div_convert")==0) {
        div_convert(input_value, input_base, got);
    }
    else if (strcmp(function_name,"sub_convert")==0) {
        sub_convert(input_value, input_base, got);
    }
    //Compare expected vs got values and print to output.txt
    if (strcmp(expected_output, got) == 0)
        fprintf (outfile,"Test: %s (%u, %d) -> Expected: \"%s\", Got: \"%s\" [ PASS ]\n",
            function_name, input_value, input_base, expected_output, got);
    else
        fprintf (outfile,"Test: %s (%u, %d) -> Expected: \"%s\", Got: \"%s\" [ FAIL ]\n",
            function_name, input_value, input_base, expected_output, got);
}

void div_convert(uint32_t input_value,int input_base, char *out) {
    char temp[65];
    int pos = 0;
    char confirmation[65];
    strcpy(confirmation,out);

    //Zero cases
    if (input_value == 0) {
        strcpy(out,"0");
        return;
    }

    //Conversion from right to left
    while (input_value > 0) {
        int remainder = input_value % input_base;
        input_value = input_value / input_base;
        if
            (remainder < 10) temp[pos++] = '0' + remainder;
        else
            temp[pos++] = 'A' + remainder - 10;
    }

    //reverse the results
    for (int i = 0; i < pos; i++) {
        out[i] = temp[pos - i - 1];
    }
    out[pos] = '\0'; // null-terminate
}


void sub_convert(uint32_t input_value,int input_base, char *expected_output) {
    char temp[65];
    int pos = 0;

    //Zero cases
    if (input_value == 0) {
        strcpy(expected_output,"0");
        return;
    }

    //Find the highest power
    uint32_t power = 1;
    while (power <= input_value / input_base) {
        power = power * input_base;
    }

    //Subtract the multiples of power
    while (power > 0) {
        uint32_t digit = input_value / power;
        input_value = input_value - (digit * power);

        //Conversion to character
        if (digit < 10) {
            temp[pos++] = '0' + digit;
        }
        else
            temp[pos++] = 'A' + (digit - 10);

        power = power / input_base;
    }
    for (int i = 0; i < pos; i++) {
        expected_output[i] = temp[i];
    }
    expected_output[pos] = '\0';
}

void print_tables(uint32_t input_value,FILE *outfile) {
    char bin[33], oct[12], hex[9];

    if (input_value == 0) {
        strcpy(bin,"0");
        strcpy(oct,"0");
        strcpy(hex,"0");
    }
    //Original
    div_convert(input_value,2,bin);
    div_convert(input_value,8,oct);
    div_convert(input_value,16,hex);
    fprintf (outfile,"Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin,oct,input_value,hex);
    fflush(stdout);

    //Left shift by 3
    uint32_t shifted = input_value << 3;
    div_convert(shifted,2,bin);
    div_convert(shifted,8,oct);
    div_convert(shifted,16,hex);
    fprintf (outfile, "Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin,oct,shifted,hex);
    fflush(stdout);

    //With oxFF
    uint32_t masked = input_value & 0xFF;
    div_convert(masked,2,bin);
    div_convert(masked,8,oct);
    div_convert(masked,16,hex);
    fprintf (outfile, "With 0xff: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin,oct,masked,hex);
    fflush(stdout);
}