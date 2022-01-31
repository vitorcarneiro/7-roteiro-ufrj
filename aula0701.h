/* 
Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
EEL270 - Computacao II - Turma 2021/2
Prof. Marcelo Luiz Drumond Lanza
Autor: Vitor Carneiro Silva de Oliveira
Descricao: Prototipo das funcoes: MostrarMonitor e GerarDistribuicaoInicial

$Author$
$Date$
$Log$

*/

#ifndef _AULA0701_
#define _AULA0701_	"@(#)aula0701.h $Revision$"

#define NUMERO_MAXIMO_LINHAS                    250
#define NUMERO_MAXIMO_COLUNAS                   800

#define APAGADO					' '
#define ACESO					'O'
#define DEFEITUOSO				'.'

typedef enum
{
	ok,
	argumentoInvalido,
	numeroLinhasInvalido,
	numeroColunasInvalido,
    valorPercentualInvalido,
	pontoLinhaInvalido,
	pontoColunaInvalido,
	encontradoPixelDefeituoso,
} tipoErros;

typedef enum
{
	defeituoso = -1,
	apagado,
	aceso
} tipoPixel;

tipoErros
MostrarMonitor(useconds_t tempoEspera, /* E */
                tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS], /* E */
                unsigned numeroMaximoLinhas, /* E */
                unsigned numeroMaximoColunas); /* E */

tipoErros
GerarDistribuicaoInicial(tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS], /* E/S */
                            unsigned numeroMaximoLinhas, /* E */
                            unsigned numeroMaximoColunas, /* E */
                            float percentualDefeituosos, /* E */
                            float percentualApagados); /* E */

tipoErros
LimparMonitor(tipoPixel monitor[NUMERO_MAXIMO_LINHAS][NUMERO_MAXIMO_COLUNAS], /* E/S */
				unsigned numeroMaximoLinhas, /* E */
				unsigned numeroMaximoColunas);


#endif

/* $RCSfile$ */