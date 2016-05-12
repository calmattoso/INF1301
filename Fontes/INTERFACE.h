#if ! defined( INTERFACE_ )
#define INTERFACE_

/***************************************************************************
*
*  $MCD Módulo de definição: INT Interface
*
*  Arquivo gerado:              INTERFACE.h
*  Letras identificadoras:      INT
*
*  Nome da base de software:    Trabalho 4 de Programação Modular
*  Arquivo da base de software: INTERFACE/INTERFACE.h
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: ffa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data      Observações
*     1       ffa   25/nov/2013  início do desenvolvimento
*
*  $ED Descrição do módulo
*	 Faz a comunicação entre o jogador e o jogo, exibindo a mesa,
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


/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: VIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do módulo VISIVEL
*
***********************************************************************/

   typedef enum {

		INT_CondRetOK ,
            /* Concluiu corretamente */

      INT_CondRetComandoInvalido ,
            /* O comando sugerido não existe */

      INT_CondRetDestinoInvalido ,
            /* O movimento não foi efetuado pois o destino é inválido */

      INT_CondRetOrigemInvalida ,
		      /* O movimento não foi efetuado pois a origem é inválida */

      INT_CondRetProibido ,
            /* Movimento proibido pelas regras do jogo */

      INT_CondRetErroAoImprimir ,
            /* A função não conseguiu exibir a mesa*/

      INT_CondRetErroParm 
            /* Algum parâmetro não atende uma assertiva de entrada */

   } INT_tpCondRet ;


   typedef enum {

		INT_MensagemOK ,
            /* Mensagem Indicando que está Ok */

      INT_MensagemEntrada ,
            /* Mensagem que explica como jogar */

      INT_MensagemComandoInvalido ,
            /* Mensagem indicando comando inválido */

      INT_MensagemMovimentoInvalido ,
            /* Mensagem indicando movimento inválido */

      INT_MensagemEntrarComando ,
            /* Mensagem indicando que o jogo espera um comando */
                  
		INT_MensagemFimJogoVitoria ,
			   /* Mensagem indicando que o jogo acabou em vitoria */

      INT_MensagemFimJogoDerrota
            /* Mensagem indicando que o jogo acabou em derrota */

   } INT_tpMensagem ;

/***********************************************************************
*
*  $FC Função: INT  &Exibir mesa
*
*  $ED Descrição da função
*     Mostra na tela a disposição da mesa.
*    
*  $EP Parâmetros
*     pMesa - ponteiro para uma lista
*     
*
*  $FV Valor retornado
*     Se executou corretamente retorna CondRetOk.
*
*     Se ocorreu algum erro a função retornará 
*	  INT_CondRetErroAoImprimir.
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
*  $AE Assertivas de Entrada
*		pMesa != NULL
*
*	$AS Assertivas de Saida
*		se a função retornar INT_CondRetErroAoImprimir ela não
*		executou corretamente a mesa não foi impressa.
*		
*		se a função retornar INT_CondRetOK ela executou corretamente
*		e a mesa será impressa na tela.
*
***********************************************************************/

   INT_tpCondRet INT_ExibirMesa( LIS_tppLista pMesa ) ;

   
/***********************************************************************
*
*  $FC Função: INT  &Obter comando
*
*  $ED Descrição da função
*     Obtem um comando e avalia se ele é válido ou não
*
*  $EP Parâmetros
*    comando - comando efetuado
*
*  $FV Valor retornado
*     Se executou corretamente retorna CondRetOk.
*	  Se o comando não existe retorna:
*	  CondRetComandoInvalido.
*
*	  Se o destino é inválido retorna:
*	  CondRetDestinoInvalido.
*
*     Se a origem é inválida retorna:
*	  CondRetOrigemInvalida. 
*
*	  Se o comando quebra as regras do jogo retorna:
*	  CondRetProibido
*
*     Se ocorreu algum erro a função retornará 
*	  INT_CondRetErroAoImprimir
*
*
***********************************************************************/

   INT_tpCondRet INT_ObterComando( char * idOrigem  , int * codOrig ,  
                                   char * idDestino , int * codDest  ) ;  
                                   

/***********************************************************************
*
*  $FC Função: INT  &Exibir Mensagem
*
*  $ED Descrição da função
*     Exibe uma mensagem na tela
*    
*  $EP Parâmetros
*    tpMensagem - Código da mensagem à ser impressa
*     
*
*  $FV Valor retornado
*     Se executou corretamente retorna CondRetOk.
*
*
***********************************************************************/

   INT_tpCondRet INT_ExibirMensagem( INT_tpMensagem mensagem ) ;

#undef INTERFACE_EXT

/********** Fim do módulo de definição: INT  Interface **********/

#else
#endif