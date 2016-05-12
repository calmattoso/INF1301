#if ! defined( EMBARALHAR_ )
#define EMBARALHAR_

/***************************************************************************
*
*  $MCD Módulo de definição: EMB  Embaralha cartas de um baralho
*
*  Arquivo gerado:              EMBARALHARAMENTO.h
*  Letras identificadoras:      EMB
*
*  Nome da base de software:    Trabalho 2 de Programação Modular
*  Arquivo da base de software: EMBARALHAMENTO/EMBARALHAMENTO.H
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: ffa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data      Observações
*     1       ffa   11/out/2013  início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo realiza o embaralhamento de um baralho representado através
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

/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: EMB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do módulo EMBARALHAMENTO
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
            /* A lista está vazia */

      EMB_CondRetFaltouMemoria ,
            /* Faltou memória ao tentar inserir elemento na lista */

      EMB_CondRetErroParm
            /* Algum parâmetro viola uma assertiva de entrada */
        
   } EMB_tpCondRet ;

 /***********************************************************************
*
*  $FC Função: EMB  Embaralhar uma lista de cartas
*
*  $ED Descrição da função
*     Esta função recebe um baralho representado por uma instância de 
*        lista, reordenando os seus elementos de forma aleatória a fim
*        de a embaralhar.
*     É preciso que a lista passada não tenha sido instanciada com uma 
*        função que destrua os valores quando da remoção de um elemento
*        da lista.   
*
*  $EP Parâmetros
*     pLista - lista com as cartas que devem ser embaralhadas
*
*  $FV Valor retornado
*     EMB_CondRetOK              - se a lista foi embaralhada com sucesso.
*     EMB_CondRetFimLista        - se tentou avançar mais elementos
*                                  do que havia nela
*     EMB_CondRetListaVazia      - se tentou avançar ou obter valor
*                                  em uma lista vazia
*     EMB_CondRetFaltouMemoria   - se faltou memória ao se tentar 
*                                  inserir elemento
*     EMB_CondRetCartaNaoExiste  - se a lista passada tinha um elemento
*                                  sem carta
*  $AE Assertivas de entrada:
*      pLista != NULL
*      dimensao(pLista) == EMB_NUM_CARTAS
*  
*  $AS	Assertivas de saída:
*      A pLista deve ter todos ou alguns de seus elementos em posições
*         diferentes de suas posições na entrada. A pLista deve conter 
*         todos os elementos que ela tinha na entrada.
*
***********************************************************************/
 
   EMB_tpCondRet EMB_Embaralhar( LIS_tppLista pLista ) ; 


#undef EMBARALHAMENTO_EXT

/********** Fim do módulo de definição: EMB  Embaralha cartas de um baralho **********/

#else
#endif