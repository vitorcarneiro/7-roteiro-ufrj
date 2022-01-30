/*
Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
EEL270 - Computacao II - Turma 2021/2
Prof. Marcelo Luiz Drumond Lanza
Autor: Vitor Carneiro Silva de Oliveira
Descricao: Implementacao funcao MostrarMonitor

$Author$
$Date$
$Log$

*/

#ifdef __linux__
#define _XOPEN_SOURCE 600
#include <unistd.h>			/* useseconds -usleep*/
#undef _XOPEN_SOURCE
#endif

#ifdef __FreeBSD__
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "aula0701.h"

tipoErros
MostrarMonitor (useconds_t tempoEspera,
                tipoPixel monitor [NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS], 
                unsigned numeroMaximoLinhas,
                unsigned numeroMaximoColunas)
{	
	unsigned indiceLinha, indiceColuna;
    /*Limpa cli*/
	system("clear");

	if (numeroMaximoLinhas > NUMERO_MAXIMO_LINHAS || numeroMaximoLinhas <= 0)
		return numeroLinhasInvalido;

	if (numeroMaximoColunas > NUMERO_MAXIMO_COLUNAS || numeroMaximoColunas <= 0)
		return numeroColunasInvalido;

	if (!monitor || !numeroMaximoLinhas || !numeroMaximoColunas || !tempoEspera)
		return argumentoInvalido;		

	for (indiceLinha = 1; indiceLinha <= numeroMaximoLinhas + 4; indiceLinha++)
	{
		for (indiceColuna = 1; indiceColuna <= numeroMaximoColunas + 4; indiceColuna++)
        {
            if (indiceLinha == 1 || indiceLinha == numeroMaximoLinhas + 4) 
                printf("-");

            else if (indiceColuna == 1 || indiceColuna == numeroMaximoColunas + 4)
                printf("|");

            else if (indiceLinha == 2 || indiceLinha == numeroMaximoLinhas + 3 ||
                    indiceColuna == 2 || indiceColuna == numeroMaximoColunas + 3)
                    printf(" ");

            else
			printf("%c", monitor[indiceLinha - 3][indiceColuna - 3] == apagado ? APAGADO :
					(monitor[indiceLinha - 3][indiceColuna - 3] == aceso ?
                    ACESO : DEFEITUOSO
                    ));
        }
		
        printf("\n");
	}
	usleep(tempoEspera);
	
	return ok;
}

tipoErros
GerarDistribuicaoInicial(tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS], /* E/S */
                            unsigned numeroMaximoLinhas, /* E */
                            unsigned numeroMaximoColunas, /* E */
                            float percentualDefeituosos, /* E */
                            float percentualApagados) /* E */
{
    unsigned indiceLinha, indiceColuna;	

    if (!monitor || !numeroMaximoLinhas || !numeroMaximoColunas)
    {
        printf("entrou em: argumentoInvalido \n");
		return argumentoInvalido;
    }

    if (numeroMaximoLinhas > NUMERO_MAXIMO_LINHAS || numeroMaximoLinhas <= 0)
    {
        printf("entrou em: numeroLinhasInvalido \n");
		return numeroLinhasInvalido;
    }

	if (numeroMaximoColunas > NUMERO_MAXIMO_COLUNAS || numeroMaximoColunas <= 0)
    {
        printf("entrou em: numeroColunasInvalido \n");
		return numeroColunasInvalido;
    }

    if (percentualDefeituosos < 0 || percentualDefeituosos > 100 || percentualApagados < 0 || percentualApagados > 100)
    {
        printf("entrou em: valorPercentualInvalido \n");
        return valorPercentualInvalido;
    }   

	srand((unsigned) time (NULL)); /* Muda a semente para aletoaridade*/

    /* monitor recebe valores aleatorios de -1 a 1 que representam pixels*/	
	for (indiceLinha = 0; indiceLinha < numeroMaximoLinhas; indiceLinha++)
    {
		for (indiceColuna = 0; indiceColuna < numeroMaximoColunas; indiceColuna++)
		{
			if (percentualDefeituosos != 0 && rand() % 101 < percentualDefeituosos)
				monitor[indiceLinha][indiceColuna] = defeituoso;
			
			else if (percentualApagados != 0 && rand() % 101 < percentualDefeituosos + percentualApagados)
				monitor[indiceLinha][indiceColuna] = apagado;
			
			else
				monitor[indiceLinha][indiceColuna] = aceso;
		}
    }

	return ok;
}

/* $RCSfile$ */
