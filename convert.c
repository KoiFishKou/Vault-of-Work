#include <string.h>
#include <stdint.h>
#include "convert.h"
#include <stdio.h>
#include <stdlib.h>

//Variables for summary
int total_count = 0, pass_count = 0, fail_count = 0;

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

void oct_to_bin(const char *input_value, char *out) {
    int length = strlen(input_value);
    char temp[65];
    //Bit-map
    const char* oct_to_bin_table[8] = {"000","001","010","011","100","101","110","111"};

    //Zero handling
    if (strcmp(input_value, "0") == 0) {
        strcpy(out, "000");
        return;
    }

    //Position to bitmap index translation and binary output building
    int transfer = 0;
    for (int pos = 0; pos < length; pos++) {
        int digit = input_value[pos] - '0';
        for (int i = 0; i < 3; i++) {
            temp[transfer++] = oct_to_bin_table[digit][i];
        }
    }
    temp[transfer] = '\0'; //Add null
    strcpy(out,temp);
}

void oct_to_hex(const char *oct, char *out) {
    char bin[65];
    char padded[70];

    //Zero handling
    if (strcmp(oct, "0") == 0) {
        strcpy(out,"0");
        return;
    }

    //Convert octal -> binary first
    oct_to_bin(oct,bin);

    //Pad to 4
    int length = strlen(bin);
    int pad = 4 - (length % 4); //# of 0 to add
    if (pad == 4) pad = 0;
    // Build padded string
    for (int i = 0; i < pad; i++) padded[i] = '0';
    strcpy(padded + pad, bin);
    length += pad;

    //4-bit Map
    const char hex_digit[] = "0123456789ABCDEF";
    int pos = 0;
    for (int i = 0; i < length; i += 4) {
        int value = (padded[i] - '0') * 8 + (padded[i + 1] - '0') * 4 + (padded[i + 2] - '0') * 2 + (padded[i + 3] - '0');
        out[pos++] = hex_digit[value];
    }
    out[pos] = '\0';

    // Remove leading zeros if any
    char *front_zero = out;
    while (*front_zero == '0') front_zero++;
    if (*front_zero != '\0') {
        memmove(out, front_zero, strlen(front_zero) + 1);
    }
}

void hex_to_bin(const char *hex, char *out) {
    //Hex to binary map
    const char *hex_map[16] = {
        "0000","0001","0010","0011",
        "0100","0101","0110","0111",
        "1000","1001","1010","1011",
        "1100","1101","1110","1111"
    };

    int pos = 0; //position in out
    for (int i = 0; hex[i] != '\0'; i++) {
        char c = hex[i];
        int value;

        //integer value of hex digit
        if (c >= '0' && c <= '9') value = c - '0';
        else if (c >= 'A' && c <= 'F') value = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') value = c - 'a' + 10;
        else continue; // skip invalid characters

        //copy corresponding 4-bit binary string
        for (int j = 0; j < 4; j++) {
            out[pos++] = hex_map[value][j];
        }
    }
    out[pos] = '\0';
}

void to_sign_magnitude(int input_value, char *out) {
    char temp[33];  //32-bit binary + null
    uint32_t abs_val = (input_value < 0) ? -input_value : input_value;

    div_convert(abs_val, 2, temp);  //convert magnitude
    int len = strlen(temp);

    //pad to 32 bits
    int pad = 32 - len;
    for (int i = 0; i < pad; i++) out[i] = '0';
    strcpy(out + pad, temp);

    //set sign bit
    if (input_value < 0) out[0] = '1';
}

void to_ones_complement(int input_value, char *out) {
    char temp[33];  // 32-bit + null
    uint32_t abs_val = (input_value < 0) ? -input_value : input_value;

    div_convert(abs_val, 2, temp);  // convert magnitude to binary
    int len = strlen(temp);

    // Pad to 32 bits
    int pad = 32 - len;
    for (int i = 0; i < pad; i++) out[i] = '0';
    strcpy(out + pad, temp);

    // Flip bits if negative
    if (input_value < 0) {
        for (int i = 0; i < 32; i++) {
            out[i] = (out[i] == '0') ? '1' : '0';
        }
    }

    out[32] = '\0';
}

void to_twos_complement(int input_value, char *out) {
    char temp[33];
    uint32_t abs_val = (input_value < 0) ? -input_value : input_value;

    div_convert(abs_val, 2, temp);//to binary
    int len = strlen(temp);

    //pad to 32 bits
    int pad = 32 - len;
    for (int i = 0; i < pad; i++) out[i] = '0';
    strcpy(out + pad, temp);

    //if negative, flip bits and add 1
    if (input_value < 0) {
        // Flip bits
        for (int i = 0; i < 32; i++) {
            out[i] = (out[i] == '0') ? '1' : '0';
        }

        //add 1
        for (int i = 31; i >= 0; i--) {
            if (out[i] == '0') {
                out[i] = '1';
                break;
            } else {
                out[i] = '0';
            }
        }
    }
    out[32] = '\0';
}

//Filter which function to use based on the function_name, then use function.
void useCommand(const char* function_name,char *input_value,int input_base, char *expected_output, FILE *outfile) {
    char got[65]; //Hold computed results
    uint32_t input_value_int = (uint32_t)strtoul(input_value, NULL, 0);

    if (strcmp(function_name,"div_convert")==0) {
        div_convert(input_value_int, input_base, got);
    }
    else if (strcmp(function_name,"sub_convert")==0) {
        sub_convert(input_value_int, input_base, got);
    }
    else if (strcmp(function_name,"oct_to_bin")==0) {
        oct_to_bin(input_value, got) ;
    }
    else if (strcmp(function_name,"oct_to_hex")==0) {
        oct_to_hex(input_value, got);
    }
    else if (strcmp(function_name,"hex_to_bin")==0) {
        hex_to_bin(input_value, got);
    }
    else if (strcmp(function_name,"to_sign_magnitude")==0) {
        to_sign_magnitude(input_value_int, got);
    }
    else if (strcmp(function_name,"to_ones_complement")==0) {
        to_ones_complement(input_value_int, got);
    }
    else if (strcmp(function_name,"to_twos_complement")==0) {
        to_twos_complement(input_value_int, got);
    }
    else {
        printf("unknown function\n");
    }
    //Compare expected vs got values and print to output.txt
    if (strcmp(expected_output, got) == 0) {
        total_count++;
        pass_count++;
        fprintf (outfile,"Test: %s (%s, %d) -> Expected: \"%s\", Got: \"%s\" [ PASS ]\n",
            function_name, input_value, input_base, expected_output, got);
    }else {
        total_count++;
        fail_count++;
        fprintf (outfile,"Test: %s (%s, %d) -> Expected: \"%s\", Got: \"%s\" [ FAIL ]\n",
            function_name, input_value, input_base, expected_output, got);
    }
}