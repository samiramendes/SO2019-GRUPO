# SO2019-GRUPO15
Trabalho da disciplina SSC0640-101-2019 Sistemas Operacionais 

Algoritmo Monte Carlo:

1. Sequencial sem gmp:

Compilação: gcc MonteCarlo.c -o MonteCarlo -lm 

Execução: ./MonteCarlo <entrada_pi.txt> saida_pi.txt

2. Sequencial com gmp:

Compilação: gcc MonteCarloBigNumbers.c -o MonteCarloBN -lm -lgmp

Execução: ./MonteCarloBN <entrada_pi.txt> saida_pi.txt

3. Paralelo:

Compilação: gcc MonteCarloPthreads.c -o MonteCarloPt -lm -lgmp -lpthread

Execução ./MonteCarloPt <entrada_pi.txt> saida_pi.txt