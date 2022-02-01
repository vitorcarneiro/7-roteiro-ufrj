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
		return argumentoInvalido;

    if (numeroMaximoLinhas > NUMERO_MAXIMO_LINHAS || numeroMaximoLinhas <= 0)
		return numeroLinhasInvalido;

	if (numeroMaximoColunas > NUMERO_MAXIMO_COLUNAS || numeroMaximoColunas <= 0)
		return numeroColunasInvalido;

    if (percentualDefeituosos < 0 || percentualDefeituosos > 100 || percentualApagados < 0 || percentualApagados > 100)
    {
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
			
			else if (percentualApagados != 0 && rand() % 101 <= percentualDefeituosos + percentualApagados)
				monitor[indiceLinha][indiceColuna] = apagado;
			
			else
				monitor[indiceLinha][indiceColuna] = aceso;
		}
    }

	return ok;
}

tipoErros
LimparMonitor(tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS], /* E/S */
				unsigned numeroMaximoLinhas, /* E */
				unsigned numeroMaximoColunas)
{
    unsigned indiceLinha, indiceColuna;	

    if (!monitor || !numeroMaximoLinhas || !numeroMaximoColunas)
		return argumentoInvalido;

    if (numeroMaximoLinhas > NUMERO_MAXIMO_LINHAS || numeroMaximoLinhas <= 0)
		return numeroLinhasInvalido;

	if (numeroMaximoColunas > NUMERO_MAXIMO_COLUNAS || numeroMaximoColunas <= 0)
		return numeroColunasInvalido;

    /* monitor recebe valores aleatorios de -1 a 1 que representam pixels*/	
	for (indiceLinha = 0; indiceLinha < numeroMaximoLinhas; indiceLinha++)
		for (indiceColuna = 0; indiceColuna < numeroMaximoColunas; indiceColuna++)
			if (monitor[indiceLinha][indiceColuna] == aceso)
				monitor[indiceLinha][indiceColuna] = apagado;
		
	return ok;
}


tipoErros
DesenharReta (tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS], /* E/S */
				unsigned numeroMaximoLinhas, /* E */
				unsigned numeroMaximoColunas, /* E */
				unsigned linhaA, /* E */
				unsigned colunaA, /* E */
				unsigned linhaB, /* E */
				unsigned colunaB) /* E */
{
/* (colunaA - colunaB)x + (linhaA * colunaB - linhaB * colunaA) = (linhaA - linhaB)y*/
	unsigned indiceLinha, indiceColuna;
	long a, b, c;
	float termo1, termo2, margemErro;

	if (numeroMaximoLinhas > NUMERO_MAXIMO_LINHAS)
		return numeroLinhasInvalido;

	if (numeroMaximoColunas > NUMERO_MAXIMO_COLUNAS)
		return numeroColunasInvalido;

	if (linhaA > numeroMaximoLinhas || linhaB > numeroMaximoLinhas || linhaA < 1 || linhaB < 1)
		return pontoLinhaInvalido;

	if (colunaA > numeroMaximoColunas || colunaB > numeroMaximoColunas || colunaA < 1 || colunaB < 1)
		return pontoColunaInvalido;

	if (!monitor || !numeroMaximoLinhas || !numeroMaximoColunas || !linhaA || !colunaA || !linhaB || !colunaB)
        return argumentoInvalido;

	/* variaveis definidas para constantes da equacao da reta*/
	
	a = (long) colunaA - (long) colunaB;
	b = ((long) linhaA * (long) colunaB) - ((long) linhaB * (long) colunaA);
	c = (long) linhaA - (long) linhaB;

	if (a == 0)
	{
		for (indiceLinha = 1; indiceLinha <= numeroMaximoLinhas; indiceLinha++)
			for (indiceColuna = 1; indiceColuna <= numeroMaximoColunas; indiceColuna++)
			{
				if (monitor[indiceLinha - 1][indiceColuna - 1] == defeituoso)
					return encontradoPixelDefeituoso;
			
				if (linhaB >= linhaA)
					if (indiceColuna == colunaB && indiceLinha <= linhaB && indiceLinha >= linhaA)
						monitor[indiceLinha - 1][indiceColuna - 1] = aceso;

				if (linhaA >= linhaB)
					if (indiceColuna == colunaA && indiceLinha <= linhaA && indiceLinha >= linhaB)
						monitor[indiceLinha - 1][indiceColuna - 1] = aceso;
			}

		return ok;
	}

	if (c == 0)
	{
		for (indiceLinha = 1; indiceLinha <= numeroMaximoLinhas; indiceLinha++)
			for (indiceColuna = 1; indiceColuna <= numeroMaximoColunas; indiceColuna++)
			{
				if (monitor[indiceLinha - 1][indiceColuna - 1] == defeituoso)
					return encontradoPixelDefeituoso;
			
				if (colunaB >= colunaA)
					if (indiceLinha == linhaB && indiceColuna <= colunaB && indiceColuna >= colunaA)
						monitor[indiceLinha - 1][indiceColuna - 1] = aceso;

				if (colunaA >= colunaB)
					if (indiceLinha == linhaA && indiceColuna <= colunaA && indiceColuna >= colunaB)
						monitor[indiceLinha - 1][indiceColuna - 1] = aceso;
			}

		return ok;
	}

	if (b == 0) {
		for (indiceLinha = 1; indiceLinha <= numeroMaximoLinhas; indiceLinha++)
			for (indiceColuna = 1; indiceColuna <= numeroMaximoColunas; indiceColuna++)
			{	
				termo1 = a * indiceLinha + b;
				termo2 = c * indiceColuna;
				margemErro = 0;

				if (linhaB >= linhaA && colunaB >= colunaA) /* (1,1) (50,50) */
					if (indiceLinha >= linhaA && indiceColuna >= colunaA && indiceLinha <= linhaB && indiceColuna <= colunaB)
					{
						if (monitor[indiceLinha - 1][indiceColuna - 1] == defeituoso)
							return encontradoPixelDefeituoso;
				
						else
							if (termo2 / termo1 <= 1 + margemErro && termo2 / termo1 >= 1 - margemErro)
								monitor[indiceLinha - 1][indiceColuna - 1] = aceso;
					}
				
			
				if (linhaB <= linhaA && colunaB <= colunaA) /* (50,50) (1,1) */
				{
					if (indiceLinha >= linhaB && indiceColuna >= colunaB && indiceLinha <= linhaA && indiceColuna <= colunaA)
					{
						if (monitor [indiceLinha - 1][indiceColuna - 1] == defeituoso)
							return encontradoPixelDefeituoso;
				
						else
							if (termo2 / termo1 <= 1 + margemErro && termo2 / termo1 >= 1 - margemErro)
								monitor[indiceLinha - 1][indiceColuna - 1] = aceso;
					}
				}
			
				if (linhaB <= linhaA && colunaA <= colunaB) /* (50,1) (1,50) */
				{
					if (indiceLinha >= linhaB && indiceColuna >= colunaA && indiceLinha <= linhaA && indiceColuna <= colunaB)
					{
						if (monitor [indiceLinha - 1][indiceColuna - 1] == defeituoso)
							return encontradoPixelDefeituoso;
				
						else
							if (a * indiceLinha + b == c * indiceColuna)
								monitor [indiceLinha - 1][indiceColuna - 1] = aceso;
					}
				}
			
				if (linhaA <= linhaB && colunaB <= colunaA) /* (1,50) (50,1) */
				{
					if (indiceLinha >= linhaA && indiceColuna >= colunaB && indiceLinha <= linhaB && indiceColuna <= colunaA)
					{
						if (monitor [indiceLinha - 1][indiceColuna - 1] == defeituoso)
							return encontradoPixelDefeituoso;
				
						else
							if (a * indiceLinha + b == c * indiceColuna)
								monitor [indiceLinha - 1][indiceColuna - 1] = aceso;	
					}
				}
			}

		return ok;
	}


	for (indiceLinha = 1; indiceLinha <= numeroMaximoLinhas; indiceLinha++)
		for (indiceColuna = 1; indiceColuna <= numeroMaximoColunas; indiceColuna++)
		{	
			termo1 = a * indiceLinha + b;
			termo2 = c * indiceColuna;
			margemErro = 0.05 * termo2/termo1;

			if (linhaB >= linhaA && colunaB >= colunaA) /* (1,1) (50,50) */
				if (indiceLinha >= linhaA && indiceColuna >= colunaA && indiceLinha <= linhaB && indiceColuna <= colunaB)
				{
					if (monitor[indiceLinha - 1][indiceColuna - 1] == defeituoso)
						return encontradoPixelDefeituoso;
			
					else
						if (termo2 / termo1 <= 1 + margemErro && termo2 / termo1 >= 1 - margemErro)
							monitor[indiceLinha - 1][indiceColuna - 1] = aceso;
				}
			
		
			if (linhaB <= linhaA && colunaB <= colunaA) /* (50,50) (1,1) */
			{
				if (indiceLinha >= linhaB && indiceColuna >= colunaB && indiceLinha <= linhaA && indiceColuna <= colunaA)
				{
					if (monitor [indiceLinha - 1][indiceColuna - 1] == defeituoso)
						return encontradoPixelDefeituoso;
			
					else
						if (termo2 / termo1 <= 1 + margemErro && termo2 / termo1 >= 1 - margemErro)
							monitor[indiceLinha - 1][indiceColuna - 1] = aceso;
				}
			}
		
			if (linhaB <= linhaA && colunaA <= colunaB) /* (50,1) (1,50) */
			{
				if (indiceLinha >= linhaB && indiceColuna >= colunaA && indiceLinha <= linhaA && indiceColuna <= colunaB)
				{
					if (monitor [indiceLinha - 1][indiceColuna - 1] == defeituoso)
						return encontradoPixelDefeituoso;
			
					else
						if (a * indiceLinha + b == c * indiceColuna)
							monitor [indiceLinha - 1][indiceColuna - 1] = aceso;
				}
			}
		
			if (linhaA <= linhaB && colunaB <= colunaA) /* (1,50) (50,1) */
			{
				if (indiceLinha >= linhaA && indiceColuna >= colunaB && indiceLinha <= linhaB && indiceColuna <= colunaA)
				{
					if (monitor [indiceLinha - 1][indiceColuna - 1] == defeituoso)
						return encontradoPixelDefeituoso;
			
					else
						if (a * indiceLinha + b == c * indiceColuna)
							monitor [indiceLinha - 1][indiceColuna - 1] = aceso;
				}
			}
		}

	return ok;
}

tipoErros
DesenharPoligono (tipoPixel monitor [NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS], 
		unsigned numeroMaximoLinhas, 
		unsigned numeroMaximoColunas, 
		unsigned numeroVertices, 
		unsigned linhasVertices[NUMERO_MAXIMO_LINHAS], 
		unsigned colunasVertices[NUMERO_MAXIMO_COLUNAS])
{

	int indice;
	tipoErros codigoRetorno;

	for (indice = 0; indice < numeroVertices - 1 ; indice++)
	{
		codigoRetorno = DesenharReta(&monitor[0], numeroMaximoLinhas, numeroMaximoColunas, linhasVertices[indice],
										colunasVertices[indice], linhasVertices[indice + 1], colunasVertices[indice + 1]);
		if(codigoRetorno != ok)
			return codigoRetorno;
	}

		codigoRetorno = DesenharReta (&monitor[0], numeroMaximoLinhas, numeroMaximoColunas, linhasVertices[numeroVertices-1],
										colunasVertices[numeroVertices - 1], linhasVertices[0], colunasVertices[0]);

		if(codigoRetorno != ok)
			return codigoRetorno;
	
	return ok;
}

/* $RCSfile$ */
