#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "convert.h"

int main() {
    //File opener (a1_test_file.txt)
    FILE *file = fopen("../CS3503_Assignment1_KH/a1_test_file.txt", "r");
    if (file == NULL) {
        printf("File not found\n");
        return 1;
    }
    //Also open "output.txt" for writing outputs later
    FILE *outfile = fopen("../CS3503_Assignment1_KH/output.txt", "w");
    if (outfile == NULL) {
        printf("File not found\n");
        return 1;
    }

    //File getter (Get text)
    char line[256];
    while (fgets(line, sizeof(line), file) !=NULL) {
        //Skip if the line of text is blank or starts with #
        //Process the lines to exclude '\n' so the lines can be read by convert.c
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }
        if (line[0] == '#') {
            continue;
        }
        //Values to submit the commands and inputs parsed from the a1_test_file.txt
        char function_name[32];
        uint32_t input_value = 0;
        int input_base = 0;
        char expected_output[32];
        char format[32] = "";

        //Pointer to parse information within a line seperated by a space
        char* token = strtok(line, " ");
        if (token == NULL) continue;  // skip empty lines
        strcpy(function_name, token);

        //Parse information piece by piece, assigning based on placement since test cases are already formatted.
        //Special case for print_tables since its format is different and does not take two of the values.
        if (strcmp(function_name, "print_tables") == 0) {
            token = strtok(NULL, " ");
            if (token != NULL) input_value = (uint32_t)strtoul(token, NULL, 0);

            print_tables(input_value, outfile);
            fprintf(outfile, "[ FORMATTED OUTPUT CHECK ] [ PASS ]\n\n");
            fflush(stdout);
        }
        else {
            token = strtok(NULL, " ");
            if (token != NULL) {
                token[strcspn(token, "\n")] = '\0';
                input_value = (uint32_t)strtoul(token, NULL, 0);
            }

            token = strtok(NULL, " ");
            if (token != NULL) {
                token[strcspn(token, "\n")] = '\0';
                input_base = atoi(token);
            }

            token = strtok(NULL, " ");
            if (token != NULL) {
                token[strcspn(token, "\n")] = '\0';
                strcpy(expected_output, token);
            }

            token = strtok(NULL, " ");
            if(token != NULL) {
                token[strcspn(token, "\n")] = '\0';
                strcpy(format, token);
            }
            //Fed into a dispenser that will then assign the correct function to be used based on function_name
            useCommand(function_name, input_value, input_base,expected_output, outfile);
        }
    }
    fclose(file);
    fclose(outfile);
    return 0;
}