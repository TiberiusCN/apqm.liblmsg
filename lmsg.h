#pragma once

#include <stdlib.h>
#include <inttypes.h>
#include <apqm/semaphor.h>

typedef struct lmess
{
	struct lmess* next;
	void* arg1;
	void* arg2;
	uint32_t code;
} lmess;

typedef struct lmchain
{
	lmess* root;
	lmess* last;
	char semaphor;
} lmchain;

extern volatile lmchain glmchain;

uint32_t lmess_get(void** arg1, void** arg2);
void lmess_send(uint32_t code, void* arg1, void* arg2);