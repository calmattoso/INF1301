#if ! defined( EMBARALHAR_ )
#define EMBARALHAR_

/***************************************************************************
*
*  $MCD M�dulo de defini��o: EMB  Embaralha cartas de um baralho
*
*  Arquivo gerado:              EMBARALHARAMENTO.h
*  Letras identificadoras:      EMB
*
*  Nome da base de software:    Trabalho 2 de Programa��o Modular
*  Arquivo da base de software: EMBARALHAMENTO/EMBARALHAMENTO.H
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: ffa
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data      Observa��es
*     1       ffa   11/out/2013  in�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo realiza o embaralhamento de um baralho representado atrav�s
*        de uma lista, a qual deve ter EMB_NUM_CARTAS cartas.          
*     
*
***************************************************************************/

#if defined( EMBARALHAMENTO_OWN )
   #define EMBARALHAMENTO_EXT
#else
   #define EMBARALHAMENTO_EXT extern
#endif

#ifdef _DEBUG
   #include   "LISTA_INSTR.H"
#else
   #include   "LISTA.H"
#endif

#define EMB_SORTEADA       1
#define EMB_NAO_SORTEADA   0
#define EMB_NUM_CARTAS     52

/***** Declara��es exportadas pelo m�dulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: EMB Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do m�dulo EMBARALHAMENTO
*
***********************************************************************/

   typedef enum {

      EMB_CondRetOK ,
            /* Concluiu corretamente */

      EMB_CondRetCartaNaoExiste ,
            /* Se a lista passada tem um elemento sem uma carta */

      EMB_CondRetFimLista ,
            /* Chegou ao fim da lista*/

      EMB_CondRetListaVazia ,
            /* A lista est� vazia */

      EMB_CondRetFaltouMemoria ,
            /* Faltou mem�ria ao tentar inserir elemento na lista */

      EMB_CondRetErroParm
            /* Algum par�metro viola uma assertiva de entrada */
        
   } EMB_tpCondRet ;

 /***********************************************************************
*
*  $FC Fun��o: EMB  Embaralhar uma lista de cartas
*
*  $ED Descri��o da fun��o
*     Esta fun��o recebe um baralho representado por uma inst�ncia de 
*        lista, reordenando os seus elementos de forma aleat�ria a fim
*        de a embaralhar.
*     � preciso que a lista passada n�o tenha sido instanciada com uma 
*        fun��o que destrua os valores quando da remo��o de um elemento
*        da lista.   
*
*  $EP Par�metros
*     pLista - lista com as cartas que devem ser embaralhadas
*
*  $FV Valor retornado
*     EMB_CondRetOK              - se a lista foi embaralhada com sucesso.
*     EMB_CondRetFimLista        - se tentou avan�ar mais elementos
*                                  do que havia nela
*     EMB_CondRetListaVazia      - se tentou avan�ar ou obter valor
*                                  em uma lista vazia
*     EMB_CondRetFaltouMemoria   - se faltou mem�ria ao se tentar 
*                                  inserir elemento
*     EMB_CondRetCartaNaoExiste  - se a lista passada tinha um elemento
*                                  sem carta
*  $AE Assertivas de entrada:
*      pLista != NULL
*      dimensao(pLista) == EMB_NUM_CARTAS
*  
*  $AS	Assertivas de sa�da:
*      A pLista deve ter todos ou alguns de seus elementos em posi��es
*         diferentes de suas posi��es na entrada. A pLista deve conter 
*         todos os elementos que ela tinha na entrada.
*
***********************************************************************/
 
   EMB_tpCondRet EMB_Embaralhar( LIS_tppLista pLista ) ; 


#undef EMBARALHAMENTO_EXT

/********** Fim do m�dulo de defini��o: EMB  Embaralha cartas de um baralho **********/

#else
#endif