// Compilar usando gcc BBPPthreads.c -o BBPPthreads -lm -lgmp -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

void *calc(void *n)
{
	// O char recebido é usado p/ identificar a thread e o caso que essa rodará
	char type = *(char *)n;
	printf("Entering Thread %c\n", type);

	int valor0, valor1; // valores genéricos p/ equação valor1/(8*i + valor0) usada nas funções

	mpf_t oito;
	mpf_init_set_ui(oito, 8);

	// Define as constantes usadas em cada caso
	switch (type)
	{
	case 'A':
		// a = 8*i + 1;
		valor0 = 1;
		valor1 = 4;
		break;
	case 'B':
		// b = 8*i + 4;
		valor0 = 4;
		valor1 = 2;
		break;
	case 'C':
		// c = 8*i + 5;
		valor0 = 5;
		valor1 = 1;
		break;
	case 'D':
		// d = 8*i + 6;
		valor0 = 6;
		valor1 = 1;
		break;
	case 'E':
		// e = pow(16,i);
		valor0 = 16;
		valor1 = 1;
		mpf_add_ui(oito, oito, 8); // 8+8 = 16
		break;
	}

	mpf_t *coeficientes;

	int it = 100; // número de iterações

	// Um vetor que guarda o resultado de todas as interações da função é criado
	coeficientes = (mpf_t *)malloc(it * sizeof(mpf_t));

	for (int i = 0; i < it; i++) // O vetor é preenchido
	{
		mpf_init(coeficientes[i]);

		if (type == 'E') // No caso E: a variável oito é setada como 16 p/ evitar a criação de outra variável
		{
			mpf_pow_ui(coeficientes[i], oito, i);
			mpf_ui_div(coeficientes[i], 1, coeficientes[i]); // e = 1/e
		}
		else
		{
			// a/b/c/d = valor1/(8*i + valor0) onde valor1 e valor0 são setados de acordo com cada caso (a,b,c,d)
			mpf_mul_ui(coeficientes[i], oito, i);
			mpf_add_ui(coeficientes[i], coeficientes[i], valor0);
			mpf_ui_div(coeficientes[i], valor1, coeficientes[i]);
		}
	}

	printf("Thread %c returning\n", type);
	return coeficientes;
}

pthread_t CallThread(char *name) // Função que cria a thread e retorna o seu id
{
	// Um id e um status são atribuídos a nova thread
	pthread_t thread_id;
	int rstatus;

	printf("Call thread name: %c\n", *name);

	// Criação da thread que chamará a função calc e mandará (void*)name como parâmetro da mesma
	rstatus = pthread_create(&thread_id, NULL, calc, (void *)name);

	if (rstatus != 0)
	{
		// Se status não valer 0, houve um erro na criação da thread
		printf("Erro ao criar o thread %c\n", *name);
		exit(EXIT_FAILURE);
	}
	else
	{
		// Se status valer 0, a thread foi criada com sucesso
		printf("Thread %c iniciada com sucesso!\n", *name);
	}

	return thread_id;
}

void *WaitThread(pthread_t id, char name) // Função que aguarda o resultado calculado pela função que a thread está rodando, o atribui a out e o retorna
{
	printf("Chama o join %c\n", name);
	void *out;							   // ponteiro auxiliar que recebe o resultado calculado na função que a thread está rodando
	int jstatusA = pthread_join(id, &out); // o resultado calculado na thread identificada pelo id é atribuído a out
	printf("Fez o join %c\n", name);

	if (jstatusA != 0)
	{
		// Se status não valer 0, houve um erro ao atribuir o resultado da thread a join
		printf("Erro ao dar join %c\n", name);
		exit(EXIT_FAILURE);
	}
	else
	{
		// Se status valer 0, houve um erro ao atribuir o resultado da thread a join
		printf("Thread %c finalizada com sucesso!\n", name);
	}

	return out;
}

// Função que desaloca o espaço alocado para os vetores que guardam o resultado de cada iteração em cada caso
void ClearThread(int it, mpf_t *calc_valueA, mpf_t *calc_valueB, mpf_t *calc_valueC, mpf_t *calc_valueD, mpf_t *calc_valueE)
{
	for (int i = 0; i < it; i++)
	{
		mpf_clear(calc_valueA[i]);
		mpf_clear(calc_valueB[i]);
		mpf_clear(calc_valueC[i]);
		mpf_clear(calc_valueD[i]);
		mpf_clear(calc_valueE[i]);
	}
}

int main()
{
	mpf_t pi, aux;

	int it = 100; // número de iterações

	mpf_init(pi);
	mpf_init(aux);

	// Nomeação das threads que serão criadas
	char typeA = 'A';
	char typeB = 'B';
	char typeC = 'C';
	char typeD = 'D';
	char typeE = 'E';

	// Criação das threads juntamente com seus respectivos ids
	pthread_t thread_idA = CallThread(&typeA);
	pthread_t thread_idB = CallThread(&typeB);
	pthread_t thread_idC = CallThread(&typeC);
	pthread_t thread_idD = CallThread(&typeD);
	pthread_t thread_idE = CallThread(&typeE);

	// O resultado calculado pela função que cada thread está chamando é atribuido a variáveis out
	void *outA = WaitThread(thread_idA, 'A');
	void *outB = WaitThread(thread_idB, 'B');
	void *outC = WaitThread(thread_idC, 'C');
	void *outD = WaitThread(thread_idD, 'D');
	void *outE = WaitThread(thread_idE, 'E');

	// Como as threads retornam void, é feito um cast em cada saída
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

		//pi = pi + aux;
		mpf_add(pi, pi, aux);
	}

	gmp_printf("pi: %.30Ff\n", pi);

	// Liberação da memória

	ClearThread(it, calc_valueA, calc_valueB, calc_valueC, calc_valueD, calc_valueE);

	free(calc_valueA);
	free(calc_valueB);
	free(calc_valueC);
	free(calc_valueD);
	free(calc_valueE);

	return 0;
}
