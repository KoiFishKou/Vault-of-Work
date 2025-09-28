#CS 3503 Assignment 2 - Advanced Representation Direct Mapping and Signed Numbers

#Author
Khuong Hoang

#Description
Using CS3503_Assignment1_KH as a base, updated the number conversion function implementation provided by Owl Tech to include:
-oct_to_bin: Octal to binary conversion
-oct_to_hex: Octal to hexadecimal conversion
-hex_to_bin: Hexadecimal to binary conversion
and functions to represent signed number in different binary formats:
-to_sign_magnitude
-to_ones_complement
-to_twos_complement

#Updates
-Including the functions added, global variables were added to track and print a summary of total conversions done, conversions passed and conversions failed.
-The parsing system was overhauled due to differences in the formatting of a1_tests and a2_tests. First a2 test require a string. Due to this, I found that it was redundant to have input_value be a string as I would be changing from the .txt a string into a integer back into a string. Therefore, the conversions to integer is now done within the useCommand() function and stored as input_value_int. Furthermore, there are inherent differences in the number of tokens received from a2_tests. With a1 providing (command, input, base, expected_output)[4] while a2 provides (command, input, expected_output). Initially, I assumed the format would not change so I just allowed each position be filled as the parse went down. However, this creates the issue where expected_output would be stored in base for a2 functions. So instead, I stored each token in a array then created a if statement based on the number of tokens to assign the correct token to their position.
-Finally, I realized that the reason I had trouble with my files is due to where my build was located so now I was able to test using relative pathing. So the project run without changing the file pathing now.

#Parting thoughts
-Using one project for a base for another really highlights the need to create adaptable code, a good bit of the previous code had to be restructured due to previous assumption. However, there was minimum changes required in other regions and part where it was  easy to implement a change due the layout I had. Overall, a lot of adaptions that I think was required but will be easier if I were to return again.


#Build Instruction
-Open the project folder in your preferred C IDE
-Allow the IDE to generate the build system.
-Run the program if you are just checking a2_test.txt, else change the file open to your preferred .txt file.

#Notes:
-Initially built in Clion using C
-Included both a1 and a2 tests because I wanted to ensure all functions still worked. Left for other to tests or have a base to create further tests.

#Summaries:
From a1:
=== Test Summary ===
Total tests: 100
Passed: 100/100
Failed: 0/100
====================

from a2:
=== Test Summary ===
Total tests: 51
Passed: 51/51
Failed: 0/51
====================
