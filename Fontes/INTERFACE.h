#if ! defined( INTERFACE_ )
#define INTERFACE_

/***************************************************************************
*
*  $MCD M�dulo de defini��o: INT Interface
*
*  Arquivo gerado:              INTERFACE.h
*  Letras identificadoras:      INT
*
*  Nome da base de software:    Trabalho 4 de Programa��o Modular
*  Arquivo da base de software: INTERFACE/INTERFACE.h
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: ffa
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data      Observa��es
*     1       ffa   25/nov/2013  in�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*	 Faz a comunica��o entre o jogador e o jogo, exibindo a mesa,
*	recebendo comandos e exibindo mensagens.
***************************************************************************/

#if defined( INTERFACE_OWN )
   #define INTERFACE_EXT
#else
   #define INTERFACE_EXT extern
#endif

#include "LISTA.h"
#include "CARTA.h"

#define INT_DIM_STRING  16
#define INT_COD_SAIR   -1


/***** Declara��es exportadas pelo m�dulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: VIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do m�dulo VISIVEL
*
***********************************************************************/

   typedef enum {

		INT_CondRetOK ,
            /* Concluiu corretamente */

      INT_CondRetComandoInvalido ,
            /* O comando sugerido n�o existe */

      INT_CondRetDestinoInvalido ,
            /* O movimento n�o foi efetuado pois o destino � inv�lido */

      INT_CondRetOrigemInvalida ,
		      /* O movimento n�o foi efetuado pois a origem � inv�lida */

      INT_CondRetProibido ,
            /* Movimento proibido pelas regras do jogo */

      INT_CondRetErroAoImprimir ,
            /* A fun��o n�o conseguiu exibir a mesa*/

      INT_CondRetErroParm 
            /* Algum par�metro n�o atende uma assertiva de entrada */

   } INT_tpCondRet ;


   typedef enum {

		INT_MensagemOK ,
            /* Mensagem Indicando que est� Ok */

      INT_MensagemEntrada ,
            /* Mensagem que explica como jogar */

      INT_MensagemComandoInvalido ,
            /* Mensagem indicando comando inv�lido */

      INT_MensagemMovimentoInvalido ,
            /* Mensagem indicando movimento inv�lido */

      INT_MensagemEntrarComando ,
            /* Mensagem indicando que o jogo espera um comando */
                  
		INT_MensagemFimJogoVitoria ,
			   /* Mensagem indicando que o jogo acabou em vitoria */

      INT_MensagemFimJogoDerrota
            /* Mensagem indicando que o jogo acabou em derrota */

   } INT_tpMensagem ;

/***********************************************************************
*
*  $FC Fun��o: INT  &Exibir mesa
*
*  $ED Descri��o da fun��o
*     Mostra na tela a disposi��o da mesa.
*    
*  $EP Par�metros
*     pMesa - ponteiro para uma lista
*     
*
*  $FV Valor retornado
*     Se executou corretamente retorna CondRetOk.
*
*     Se ocorreu algum erro a fun��o retornar� 
*	  INT_CondRetErroAoImprimir.
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*  $AE Assertivas de Entrada
*		pMesa != NULL
*
*	$AS Assertivas de Saida
*		se a fun��o retornar INT_CondRetErroAoImprimir ela n�o
*		executou corretamente a mesa n�o foi impressa.
*		
*		se a fun��o retornar INT_CondRetOK ela executou corretamente
*		e a mesa ser� impressa na tela.
*
***********************************************************************/

   INT_tpCondRet INT_ExibirMesa( LIS_tppLista pMesa ) ;

   
/***********************************************************************
*
*  $FC Fun��o: INT  &Obter comando
*
*  $ED Descri��o da fun��o
*     Obtem um comando e avalia se ele � v�lido ou n�o
*
*  $EP Par�metros
*    comando - comando efetuado
*
*  $FV Valor retornado
*     Se executou corretamente retorna CondRetOk.
*	  Se o comando n�o existe retorna:
*	  CondRetComandoInvalido.
*
*	  Se o destino � inv�lido retorna:
*	  CondRetDestinoInvalido.
*
*     Se a origem � inv�lida retorna:
*	  CondRetOrigemInvalida. 
*
*	  Se o comando quebra as regras do jogo retorna:
*	  CondRetProibido
*
*     Se ocorreu algum erro a fun��o retornar� 
*	  INT_CondRetErroAoImprimir
*
*
***********************************************************************/

   INT_tpCondRet INT_ObterComando( char * idOrigem  , int * codOrig ,  
                                   char * idDestino , int * codDest  ) ;  
                                   

/***********************************************************************
*
*  $FC Fun��o: INT  &Exibir Mensagem
*
*  $ED Descri��o da fun��o
*     Exibe uma mensagem na tela
*    
*  $EP Par�metros
*    tpMensagem - C�digo da mensagem � ser impressa
*     
*
*  $FV Valor retornado
*     Se executou corretamente retorna CondRetOk.
*
*
***********************************************************************/

   INT_tpCondRet INT_ExibirMensagem( INT_tpMensagem mensagem ) ;

#undef INTERFACE_EXT

/********** Fim do m�dulo de defini��o: INT  Interface **********/

#else
#endif