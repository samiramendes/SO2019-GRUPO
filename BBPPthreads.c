#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

void *calc(void *n)	
{
	char type = *(char *)n;
	printf("Entering Thread %c\n", type);

	int valor0, valor1;

	mpf_t oito;
	mpf_init(oito);
	mpf_add_ui(oito, oito, 8);

	switch (type)
	{
	case 'A':
		valor0 = 1;
		valor1 = 4;
		break;
	case 'B':
		valor0 = 4;
		valor1 = 2;
		break;
	case 'C':
		valor0 = 5;
		valor1 = 1;
		break;
	case 'D':
		valor0 = 6;
		valor1 = 1;
		break;
	case 'E':
		valor0 = 16;
		valor1 = 1;
		mpf_add_ui(oito, oito, 8); // 8+8 = 16
		break;
	}

	mpf_t *coeficientes;
	int it = 10;

	coeficientes = (mpf_t *)malloc(it * sizeof(mpf_t));

	for (int i = 0; i < it; i++)
	{
		mpf_init(coeficientes[i]);

		if (type == 'E')
		{
			mpf_pow_ui(coeficientes[i], oito, i);			 // No caso E: oito = 16
			mpf_ui_div(coeficientes[i], 1, coeficientes[i]); // e = 1/e
		}
		else
		{
			mpf_mul_ui(coeficientes[i], oito, i);
			mpf_add_ui(coeficientes[i], coeficientes[i], valor0);
			mpf_ui_div(coeficientes[i], valor1, coeficientes[i]);
		}
	}

	printf("Thread %c returning\n", type);
	return coeficientes;
}

pthread_t CallThread(char *name)
{
	pthread_t thread_id;
	int rstatus;

	printf("Call thread name: %c\n", *name);

	rstatus = pthread_create(&thread_id, NULL, calc, (void *)name);

	if (rstatus != 0)
	{
		printf("Erro ao criar o thread %c\n", *name);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Thread %c iniciada com sucesso!\n", *name);
	}

	return thread_id;
}

void *WaitThread(pthread_t id, char name)
{
	printf("Chama o join %c\n", name);
	void *out;
	int jstatusA = pthread_join(id, &out);
	printf("Fez o join %c\n", name);

	if (jstatusA != 0)
	{
		printf("Erro ao dar join %c\n", name);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Thread %c finalizada com sucesso!\n", name);
	}

	return out;
}

void ClearThread(int it, void *calc_valueA, void *calc_valueB, void *calc_valueC, void *calc_valueD, void *calc_valueE)
{
	mpf_t *A = (mpf_t*)calc_valueA;
	mpf_t *B = (mpf_t*)calc_valueB;
	mpf_t *C = (mpf_t*)calc_valueC;
	mpf_t *D = (mpf_t*)calc_valueD;
	mpf_t *E = (mpf_t*)calc_valueE;

	printf("liberando a memoria");

	for (int i = 0; i < it; i++)
	{
		mpf_clear(A[i]);
		mpf_clear(B[i]);
		mpf_clear(C[i]);
		mpf_clear(D[i]);
		mpf_clear(E[i]);
	}
}

int main()
{
	mpf_t pi, aux;

	int it = 10;

	mpf_inits(pi, aux);

	char typeA = 'A';
	char typeB = 'B';
	char typeC = 'C';
	char typeD = 'D';
	char typeE = 'E';

	pthread_t thread_idA = CallThread(&typeA);
	pthread_t thread_idB = CallThread(&typeB);
	pthread_t thread_idC = CallThread(&typeC);
	pthread_t thread_idD = CallThread(&typeD);
	pthread_t thread_idE = CallThread(&typeE);

	void *outA = WaitThread(thread_idA, 'A');
	void *outB = WaitThread(thread_idB, 'B');
	void *outC = WaitThread(thread_idC, 'C');
	void *outD = WaitThread(thread_idD, 'D');
	void *outE = WaitThread(thread_idE, 'E');

	mpf_t *calc_valueA = (mpf_t *)outA;
	mpf_t *calc_valueB = (mpf_t *)outB;
	mpf_t *calc_valueC = (mpf_t *)outC;
	mpf_t *calc_valueD = (mpf_t *)outD;
	mpf_t *calc_valueE = (mpf_t *)outE;

	for (int i = 0; i < it; i++)
	{
		// aux = (1 / e) * ((4 / a) - (2 / b) - (1 / c) - (1 / d));
		// aux = (aux_e)*(aux_a - aux_b - aux_c - aux_d);
		mpf_sub(aux, calc_valueA[i], calc_valueB[i]);
		mpf_sub(aux, aux, calc_valueC[i]);
		mpf_sub(aux, aux, calc_valueD[i]);
		mpf_mul(aux, aux, calc_valueE[i]);

		gmp_printf("aux: %.9Ff\n", aux);

		//pi = pi + aux;
		mpf_add(pi, pi, aux);
	}

	gmp_printf("A: %.6Ff\n", calc_valueA[99]);
	gmp_printf("B: %.6Ff\n", calc_valueB[99]);
	gmp_printf("C: %.6Ff\n", calc_valueC[99]);
	gmp_printf("D: %.6Ff\n", calc_valueD[99]);
	gmp_printf("E: %.6Ff\n", calc_valueE[99]);
	gmp_printf("pi: %.30Ff\n", pi);

	// getchar();

	ClearThread(it,&calc_valueA, &calc_valueB, &calc_valueC, &calc_valueD, &calc_valueE);

	return 0;
}
