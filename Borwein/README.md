# SO2019-GRUPO15
Trabalho da disciplina SSC0640-101-2019 Sistemas Operacionais 

Implementação do método de Borwein 

Método de compilação:

1. Sequencial 

gcc BBP.c -o BBP -lm 

Método de execução para que a saída seja printada no arquivo saida.txt.

./BBP <entrada_pi.txt> saida_pi.txt

1. Sequencial com Big Numbers

gcc BBPBigNumbers.c -o BBPbn -lm 

Método de execução para que a saída seja printada no arquivo saida.txt.

./BBPbn <entrada_pi.txt> saida_pi.txt

1. Paralelo 

gcc BBPPthreads.c -o BBPPthread -lm -lgmp -lpthread 

Método de execução para que a saída seja printada no arquivo saida.txt.

./BBPPthread <entrada_pi.txt> saida_pi.txt

