# SO2019-GRUPO15
Trabalho da disciplina SSC0640-101-2019 Sistemas Operacionais 

Implementação do método de Black Scholes 

Método de compilação:

1. Sequencial 

gcc blackScholes.c -o blackScholes -lm 

Método de execução para que a saída seja printada no arquivo saida.txt.

./blackScholes <entrada_pi.txt> saida_pi.txt

1. Paralelo 

gcc blackScholesParallel.c -o blackScholesParallel -lm -lpthread 

Método de execução para que a saída seja printada no arquivo saida.txt.

./blackScholesParallel <entrada_pi.txt> saida_pi.txt

