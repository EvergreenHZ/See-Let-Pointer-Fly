#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>


void* Malloc(size_t);

void Error(char* msg);

void Log(char* msg);

int rand_int(int module);

void print_array(int*A, int len);
