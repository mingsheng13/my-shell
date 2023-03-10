//
// Created by cms on 3/9/23.
//

#ifndef ASSIGNMENT2_UTILS_H
#define ASSIGNMENT2_UTILS_H

#endif //ASSIGNMENT2_UTILS_H
void promptUserInput();

char* timestamp();
char* userInput();
char** splitInput(char* line);
int execProgram(char** args);

char* trimWhitespace(char* input);
char* trimNewline(char* input);

void signalHandler(int signal);