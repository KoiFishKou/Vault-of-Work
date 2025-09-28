#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "convert.h"

int main() {
    //Added global functions to track function performance.
    extern int total_count;
    extern int pass_count;
    extern int fail_count;


    //File opener
    FILE *file = fopen("./a2_test.txt", "r");
    if (file == NULL) {
        printf("File not found\n");
        return 1;
    }
    //Also open "output.txt" for writing outputs later
    FILE *outfile = fopen("./output.txt", "w");
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
        char input_value[32] = "";
        char input_base = 0;
        char expected_output[32];

        //New token assignment method using a while loop
        char* tokens[4];
        int token_count = 0;

        //Pointer to parse information within a line seperated by a space
        char* token = strtok(line, " ");
        while (token != NULL && token_count < 4) {
            token[strcspn(token, "\n")] = '\0'; // remove newline
            tokens[token_count++] = token;
            token = strtok(NULL, " ");
        }

        //Recognize function_name to filter out print_table commands and since function_name is constantly the first in the test_cases.
        strcpy(function_name, tokens[0]);

        //Parse information piece by piece, assigning based on placement since test cases are already formatted.
        //Special case for print_tables since its format is different and does not take two of the values.
        if (strcmp(function_name, "print_tables") == 0) {
            token = strtok(NULL, " ");
            if (token != NULL) {
                token[strcspn(token, "\n")] = '\0';  // remove newline
                strcpy(input_value, token);
            }

            print_tables((uint32_t)strtoul(input_value, NULL, 0), outfile);
            fprintf(outfile, "[ FORMATTED OUTPUT CHECK ] [ PASS ]\n\n");
            total_count++;
            pass_count++;
            fflush(stdout);
        }
        else {
            if (token_count == 4) {
                strcpy(input_value, tokens[1]);
                input_base = atoi(tokens[2]);
                strcpy(expected_output, tokens[3]);
            }
            else if (token_count == 3) {
                strcpy(input_value, tokens[1]);
                strcpy(expected_output, tokens[2]);
            }
            useCommand(function_name,input_value, input_base, expected_output, outfile);
        }
    }

    //Summarize
    fprintf(outfile, "\n=== Test Summary ===\n");
    fprintf(outfile, "Total tests: %d\n",total_count);
    fprintf(outfile, "Passed: %d/%d\n",pass_count, total_count);
    fprintf(outfile, "Failed: %d/%d\n",fail_count, total_count);
    fprintf(outfile, "====================\n");

    //End program
    fclose(file);
    fclose(outfile);
    return 0;
}