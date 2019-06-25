# SO2019-GRUPO15
Trabalho da disciplina SSC0640-101-2019 Sistemas Operacionais 

Algoritmo Gauss-Legendre:

1. Sequencial sem gmp:

Compilação: gcc Gauss-Legendre.c -o Gauss-Legendre -lm -lgmp

Execução: ./Gauss-Legendre <entrada_pi.txt> saida_pi.txt

2. Sequencial com gmp:

Compilação: gcc Gauss-LegendreBigNumbers.c -o Gauss-LegendreBN -lm -lgmp

Execução: ./Gauss-LegendreBN <entrada_pi.txt> saida_pi.txt

3. Paralelo:

Compilação: gcc Gauss-LegendrePthread.c -o Gauss-LegendrePthread -lm -lgmp -lpthread

Execução ./Gauss-LegendrePthread <entrada_pi.txt> saida_pi.txt