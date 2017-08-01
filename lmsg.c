#include "lmsg.h"

volatile lmchain glmchain;

uint32_t lmess_get(void** arg1, void** arg2)
{
	sem_lock(&glmchain.semaphor);
	lmess* m = 0;
	if(m = glmchain.root)
	{
		glmchain.root = glmchain.root->next;
		if(!glmchain.root) glmchain.last = 0;
	}
	sem_unlock(&glmchain.semaphor);
	if(m)
	{
		if(arg1) *arg1 = m->arg1;
		if(arg2) *arg2 = m->arg2;
		free(m);
		return m->code;
	}
	return 0;
}

void lmess_send(uint32_t code, void* arg1, void* arg2)
{
	lmess* m = malloc(sizeof(lmess));
	m->next = 0;
	m->arg1 = arg1;
	m->arg2 = arg2;
	m->code = code;
	sem_lock(&glmchain.semaphor);
	if(glmchain.root)
	{
		glmchain.last->next = m;
		glmchain.last = m;
	} else {
		glmchain.last = glmchain.root = m;
	}
	sem_unlock(&glmchain.semaphor);
}