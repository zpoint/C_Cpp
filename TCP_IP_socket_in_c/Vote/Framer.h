#pragma once
#include <stdint.h>
#include <stdio.h>
#include "DelimFramer.c"

int GetNextMsg(FILE *in, uint8_t *buf, size_t bufSize);
int PutMsg(uint8_t buf[], size_t msgSize, FILE *out);
