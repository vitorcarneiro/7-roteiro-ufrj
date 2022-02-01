/* 
Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
EEL270 - Computacao II - Turma 2021/2
Prof. Marcelo Luiz Drumond Lanza
Autor: Vitor Carneiro Silva de Oliveira
Descricao: Programa de testes para funcoes MostrarMonitor, GerarDistribuicaoInicial, LimparMonitor e DesenharReta

$Author$
$Date$
$Log$

*/

#ifdef __linux__
#define _XOPEN_SOURCE 600
#include <unistd.h>
#undef _XOPEN_SOURCE
#endif

#ifdef __FreeBSD__
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include "aula0701.h"

#define OK						            0
#define ARGUMENTO_INVALIDO				    1
#define NUMERO_ARGUMENTOS_INVALIDO			2
#define FUNCAO_RETORNOU_ERRO				3

#define NUMERO_ARGUMENTOS				    10
#define EOS						            '\0'

int
main (int argc, char *argv[])
{
	unsigned numeroMaximoLinhas, numeroMaximoColunas, indice, linhaA, colunaA, linhaB, colunaB;
    float percentualDefeituosos, percentualApagados;
	char *verificacao;
	tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS];
	useconds_t tempoEspera;
	tipoErros codigoRetorno;

/* TRATAMENTO DE ERROS ---------------------------------------------------------------------------- */

	/* Erro se quantidade de argumentos nao for correta */
	if (argc != NUMERO_ARGUMENTOS)
	{
		printf ("Uso: %s <inteiro-nao-negativo> <inteiro-nao-negativo> <inteiro-nao-negativo> <ponto-flutuante-não-negativo> <ponto-flutuante-não-negativo> <inteiro-nao-negativo> <inteiro-nao-negativo>\n", argv[0]);
		printf ("Uso: %s <tempo-congelamento> <numero-linhas> <numero-colunas> <percentual-defeituosos> <percentual-apagados> <linha-ponto-1> <coluna-ponto-1> <linha-ponto-2> <coluna-ponto-2>\n", argv[0]);
		exit (NUMERO_ARGUMENTOS_INVALIDO);
	}

	/* Erro se primeiro caractere for hifen de algum argumento */
	for (indice = 1; indice < NUMERO_ARGUMENTOS; indice++)
		if (argv[indice][0] == '-')
		{
			printf ("Caractere invalido: '-'\n");
			printf ("Todos valores devem ser positivos.\n");
		    printf ("Uso: %s <tempo-congelamento> <numero-linhas> <numero-colunas> <percentual-defeituosos> <percentual-apagados> <linha-ponto-1> <coluna-ponto-1> <linha-ponto-2> <coluna-ponto-2>\n", argv[0]);
			exit (ARGUMENTO_INVALIDO);	
		}

	/* Cada variavel recebe a valor tipo long typecasted para seu respectivo tipo */
    tempoEspera = strtoul(argv[1], &verificacao, 10);
	if (*verificacao != EOS)
	{
		printf ("Argumento 1 <tempo-congelamento> contem caractere invalido. \n");
		printf ("Primeiro caractere invalido \'%c\'.\n", *verificacao);
		exit (ARGUMENTO_INVALIDO);
	}
	tempoEspera = (useconds_t) tempoEspera;

	numeroMaximoLinhas = strtoul(argv[2], &verificacao, 10);
	if (*verificacao != EOS)
	{
		printf ("Argumento 2 <numero-linhas> contem caractere invalido. \n");
		printf ("Primeiro caractere invalido \'%c\'.\n", *verificacao);
		exit (ARGUMENTO_INVALIDO);
	}
	numeroMaximoLinhas = (unsigned) numeroMaximoLinhas;

	numeroMaximoColunas =  strtoul(argv[3], &verificacao, 10);
	if (*verificacao != EOS)
	{
		printf ("Argumento 3 <numero-colunas> contem caractere invalido. \n");
		printf ("Primeiro caractere invalido \'%c\'.\n", *verificacao);
		exit (ARGUMENTO_INVALIDO);
	}
	numeroMaximoColunas = (unsigned) numeroMaximoColunas;

    percentualDefeituosos =  strtof(argv[4], &verificacao);
	if (*verificacao != EOS)
	{
		printf ("Argumento 4 <percentual-defeituosos> contem caractere invalido. \n");
		printf ("Primeiro caractere invalido \'%c\'.\n", *verificacao);
		exit (ARGUMENTO_INVALIDO);
	}
	
    percentualApagados =  strtof(argv[5], &verificacao);
	if (*verificacao != EOS)
	{
		printf ("Argumento 5 <percentual-apagados> contem caractere invalido. \n");
		printf ("Primeiro caractere invalido \'%c\'.\n", *verificacao);
		exit (ARGUMENTO_INVALIDO);
	}

    linhaA =  strtoul(argv[6], &verificacao, 10);
	if (*verificacao != EOS)
	{
		printf ("Argumento 6 <numero-colunas> contem caractere invalido. \n");
		printf ("Primeiro caractere invalido \'%c\'.\n", *verificacao);
		exit (ARGUMENTO_INVALIDO);
	}
	linhaA = (unsigned) linhaA;

    colunaA =  strtoul(argv[7], &verificacao, 10);
	if (*verificacao != EOS)
	{
		printf ("Argumento 7 <numero-colunas> contem caractere invalido. \n");
		printf ("Primeiro caractere invalido \'%c\'.\n", *verificacao);
		exit (ARGUMENTO_INVALIDO);
	}
	colunaA = (unsigned) colunaA;

    linhaB =  strtoul(argv[8], &verificacao, 10);
	if (*verificacao != EOS)
	{
		printf ("Argumento 8 <numero-colunas> contem caractere invalido. \n");
		printf ("Primeiro caractere invalido \'%c\'.\n", *verificacao);
		exit (ARGUMENTO_INVALIDO);
	}
	linhaB = (unsigned) linhaB;

    colunaB =  strtoul(argv[9], &verificacao, 10);
	if (*verificacao != EOS)
	{
		printf ("Argumento 9 <numero-colunas> contem caractere invalido. \n");
		printf ("Primeiro caractere invalido \'%c\'.\n", *verificacao);
		exit (ARGUMENTO_INVALIDO);
	}
	colunaB = (unsigned) colunaB;

	/* Chamada funcao para preencher o monitor com pixels */
    codigoRetorno = GerarDistribuicaoInicial(&monitor[0], numeroMaximoLinhas, numeroMaximoColunas, percentualDefeituosos, percentualApagados);
    
    /* Verifica retorno da funcao */	
    if (codigoRetorno == numeroLinhasInvalido)
	{
		printf ("Argumento 2 <numero-linhas> nao deve ser maior que %u\n", NUMERO_MAXIMO_LINHAS);
		exit (ARGUMENTO_INVALIDO);
	}

    if (codigoRetorno == numeroColunasInvalido)
	{
		printf ("Argumento 3 <numero-colunas> nao deve ser maior que %u\n", NUMERO_MAXIMO_COLUNAS);
		exit (ARGUMENTO_INVALIDO);
	}
	
    if (codigoRetorno == argumentoInvalido)
	{
		printf ("Funcao GerarDistribuicaoInicial retornou erro: %i (argumento-invalido)\n", codigoRetorno);
		printf ("Verique os argumentos de entrada.\n");
		exit (ARGUMENTO_INVALIDO);	
	}
	
	/* codigoRetorno recebe o retorno da chamada da funcao MostrarMonitor para tratamento de Erros*/
	codigoRetorno = MostrarMonitor(tempoEspera, &monitor[0], numeroMaximoLinhas, numeroMaximoColunas);

	codigoRetorno = LimparMonitor(&monitor[0], numeroMaximoLinhas, numeroMaximoColunas);

	codigoRetorno = MostrarMonitor(tempoEspera, &monitor[0], numeroMaximoLinhas, numeroMaximoColunas);
	
    codigoRetorno = DesenharReta(&monitor[0], numeroMaximoLinhas, numeroMaximoColunas, linhaA, colunaA, linhaB, colunaB);
    
    if (codigoRetorno == encontradoPixelDefeituoso)
	{
		printf ("Foi encontrado um pixel-defeituoso na geracao da reta.\n");
		exit (FUNCAO_RETORNOU_ERRO);
	}

    if (codigoRetorno == pontoLinhaInvalido)
	{
		printf ("O valor referente a linha de qualquer ponto deve estrar entre 0 e %u.\n", numeroMaximoLinhas);
		exit (FUNCAO_RETORNOU_ERRO);
	}

    if (codigoRetorno == pontoColunaInvalido)
	{
		printf ("O valor referente a coluna de qualquer ponto deve estrar entre 0 e %u.\n", numeroColunasInvalido);
		exit (FUNCAO_RETORNOU_ERRO);
	}
    
    codigoRetorno = MostrarMonitor(tempoEspera, &monitor[0], numeroMaximoLinhas, numeroMaximoColunas);

    /* Verifica retorno da funcao */	
    if (codigoRetorno == encontradoPixelDefeituoso)
	{
		printf ("Foi encontrado um pixel-defeituoso na geracao da reta.\n");
		exit (FUNCAO_RETORNOU_ERRO);
	}

    if (codigoRetorno == numeroColunasInvalido)
	{
		printf ("Argumento 3 <numero-colunas> nao deve ser maior que %u\n", NUMERO_MAXIMO_COLUNAS);
		exit (ARGUMENTO_INVALIDO);
	}
	
    if (codigoRetorno == argumentoInvalido)
	{
		printf ("Funcao MostrarMonitor retornou erro: %i\n", codigoRetorno);
		printf ("Verique os argumentos de entrada.\n");
		exit (ARGUMENTO_INVALIDO);	
	}

	return OK;
}	

/* $RCSfile$ */
