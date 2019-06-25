// Compilar usando gcc BBPBigNumbers.c -o BBPBigNumbers -lm -lgmp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <string.h>
#include <time.h>

void main()
{

	// Inicialização das variáveis
	int i;
	int n = 1000000;

	// Declaração das variáveis do tipo mpf_t
	mpf_t pi, aux;
	mpf_t aux_a, aux_b, aux_c, aux_d, aux_e;
	mpf_t a, b, c, d, e;
	mpf_t oito, dezesseis;

	// Inicialização das variáveis do tipo mpf_t
	mpf_init(pi);
	mpf_init(aux);
	mpf_init(aux_a);
	mpf_init(aux_b);
	mpf_init(aux_c);
	mpf_init(aux_d);
	mpf_init(aux_e);
	mpf_init(a);
	mpf_init(b);
	mpf_init(c);
	mpf_init(d);
	mpf_init(e);
	mpf_init_set_ui(oito, 8);
	mpf_init_set_ui(dezesseis, 16);

	for (i = 0; i < n; i++)
	{
		// a = 8*i + 1;
		mpf_mul_ui(a, oito, i);
		mpf_add_ui(a, a, 1);
		// b = 8*i + 4;
		mpf_mul_ui(b, oito, i);
		mpf_add_ui(b, b, 4);
		// c = 8*i + 5;
		mpf_mul_ui(c, oito, i);
		mpf_add_ui(c, c, 5);
		// d = 8*i + 6;
		mpf_mul_ui(d, oito, i);
		mpf_add_ui(d, d, 6);
		// e = pow(16,i);
		mpf_pow_ui(e, dezesseis, i);

		mpf_ui_div(aux_a, 4, a); // aux_a = 4/a
		mpf_ui_div(aux_b, 2, b); // aux_b = 2/b
		mpf_ui_div(aux_c, 1, c); // aux_c = 1/c
		mpf_ui_div(aux_d, 1, d); // aux_d = 1/d
		mpf_ui_div(aux_e, 1, e); // aux_e = 1/e

		// aux = (1 / e) * ((4 / a) - (2 / b) - (1 / c) - (1 / d));
		// aux = (aux_e)*(aux_a - aux_b - aux_c - aux_d);
		mpf_sub(aux, aux_a, aux_b);
		mpf_sub(aux, aux, aux_c);
		mpf_sub(aux, aux, aux_d);
		mpf_mul(aux, aux, aux_e);

		//pi = pi + aux;
		mpf_add(pi, pi, aux);
	}

	gmp_printf("pi: %.6Ff\n", pi); // Printa o valor de pi

	// Liberação da memória
	mpf_clear(pi);
	mpf_clear(aux);
	mpf_clear(aux_e);
	mpf_clear(aux_a);
	mpf_clear(aux_b);
	mpf_clear(aux_c);
	mpf_clear(aux_d);
	mpf_clear(dezesseis);
	mpf_clear(a);
	mpf_clear(b);
	mpf_clear(c);
	mpf_clear(d);
	mpf_clear(e);
}
