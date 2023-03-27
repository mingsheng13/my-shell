/*
 * Name: Ming Sheng Chai
 * Student Number: 21203216
 * Email: ming.chai@ucdconnect.ie
 * */


#pragma once

void promptUserInput();

char* timestamp();
char* userInput();
char** splitInput(char* line);
int execProgram(char** args);

char* trimWhitespace(char* input);
char* trimNewline(char* input);

void signalHandler(int signal);