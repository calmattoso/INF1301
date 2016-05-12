/***************************************************************************
*  $MCI Módulo de implementação: EXT  Espaços extras do jogo
*
*  Arquivo gerado:              EXTRAS.c
*  Letras identificadoras:      EXT
*
*  Nome da base de software:    Trabalho 2 de Programação Modular
*  Arquivo da base de software: C:\Users\Carlos\Skydrive\PUC\INF1301
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: clm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data      Observações
*     1       clm   12/out/2013  início do desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>

#ifdef _DEBUG
   #include   "LISTA_INSTR.H"
#else
   #include   "LISTA.H"
#endif

#define EXTRAS_OWN
#include "EXTRAS.h"
#undef EXTRAS_OWN


/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: EXT Descritor de uma sequência de espaços extras
*
*
***********************************************************************/

   typedef struct EXT_tagExtras {

         LIS_tppLista pLista ;
               /* Lista que representa os espaços extras */

         int numeroCartas ;
               /* Quantidade de cartas salvas nos espaços extras */

   } EXT_tpExtras ;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  Função: EXT  &Criar extras
*  ****/

   EXT_tppExtras EXT_CriarExtras( void ) 
   {

      EXT_tpExtras * pExtras = NULL ;

      int i ;

      pExtras = ( EXT_tpExtras * ) malloc( sizeof( EXT_tpExtras )) ;
      if( pExtras == NULL )
      {
         return NULL ;
      } /* if */

      /* Tenta criar a lista; caso não consiga destroi pExtras e
         retorna NULL */

         pExtras->pLista = LIS_CriarLista( NULL ) ;
         if( pExtras->pLista == NULL )
         {
            free( pExtras ) ;

            return NULL ;
         } /* if */

      /* Preenche os espaços com NULL, indicando que ali não há
         cartas; facilita adicionar depois. Cria um nó cabeça para
         facilitar operações de remoção de cartas */

         for( i = 0 ; i <= EXT_DIM_EXTRAS ; i++ )
         {
            if( LIS_InserirElementoApos( pExtras->pLista , NULL ) ==
                LIS_CondRetFaltouMemoria )
            {
               EXT_DestruirExtras( pExtras ) ;

               return NULL ;
            } /* if */
         } /* for */

      /* Inicialmente os espaços extras estão todos livres */

         pExtras->numeroCartas = 0 ;

         return pExtras ;

   } /* Fim função: EXT  &Criar extras */


/***********************************************************************
*
*  Função: EXT  &Destruir espaços extras
*  ****/

   void EXT_DestruirExtras( EXT_tppExtras pExtras ) 
   {

      #ifdef _DEBUG
         if( pExtras == NULL )
         {
            return;
         } /* if */
      #endif
      
      LIS_DestruirLista( pExtras->pLista ) ;

      free( pExtras ) ;

   } /* Fim função: EXT  &Destruir espaços extras */

/***********************************************************************
*
*  Função: EXT  &Obter número de espaços ocupados
*  ****/

   int EXT_ObterNumeroEspacosOcupados( EXT_tppExtras pExtras ) 
   {

      #ifdef _DEBUG
         if( pExtras == NULL )
         {
            return EXT_ERRO_PARM ;
         } /* if */
      #endif

      return pExtras->numeroCartas ;

   } /* Fim função: EXT  &Obter numero de espaços ocupados */

/***********************************************************************
*
*  Função: EXT  &Inserir Carta Posição
*  ****/

   EXT_tpCondRet EXT_InserirCartaPosicao( EXT_tppExtras pExtras , 
                                          CAR_tppCarta pCarta ,
                                          int posicao            ) 
   {

      LIS_tpCondRet retornoAvancar ;

      CAR_tppCarta pCartaRet = NULL ;

      #ifdef _DEBUG
         if( pExtras == NULL || pCarta == NULL || posicao < 1 || 
             posicao > EXT_DIM_EXTRAS )
         {
            return EXT_CondRetErroParm ;
         } /* if */
      #endif
      
      if( pExtras->numeroCartas == EXT_DIM_EXTRAS )
      {
         return EXT_CondRetExtrasLotados ;
      }

      /* Caminha até a posição onde se deseja inserir a carta. */
         
         IrInicioLista( pExtras->pLista ) ;
         retornoAvancar = LIS_AvancarElementoCorrente( 
                             pExtras->pLista , posicao ) ;
         if( retornoAvancar == LIS_CondRetFimLista )
         {
            return EXT_CondRetFimExtras ;
         }
         else if( retornoAvancar == LIS_CondRetListaVazia ) 
         {
            return EXT_CondRetExtrasVazios ;
         } /* if */

      /* Checa se tal posição já está ocupada: se estiver retorna
         indicando tal fato; caso contrário, tenta inserir a carta,
         removendo o valor NULL auxiliar (que indicava posicao vazia)
         que antes fora colocado ali */

         pCartaRet = ( CAR_tppCarta ) LIS_ObterValor( pExtras->pLista ) ;
         if( pCartaRet != NULL )
         {
            IrInicioLista( pExtras->pLista ) ;
            return EXT_CondRetPosicaoInvalida ;
         }

         if( LIS_InserirElementoAntes( pExtras->pLista , pCarta ) ==
             LIS_CondRetFaltouMemoria )
         {
            IrInicioLista( pExtras->pLista ) ;
            return EXT_CondRetFaltouMemoria ;
         } 
         ( pExtras->numeroCartas )++ ;

         LIS_AvancarElementoCorrente( pExtras->pLista , 1 ) ;
         LIS_ExcluirElemento( pExtras->pLista ) ;
         IrInicioLista( pExtras->pLista ) ;
         
         return EXT_CondRetOK ;

   } /* Fim função: EXT  &Inserir carta */

/***********************************************************************
*
*  Função: EXT  &Remover carta em certa posição
*  ****/

   EXT_tpCondRet EXT_RemoverCartaPosicao( EXT_tppExtras pExtras , 
                                          int posicao            )
   {

      LIS_tpCondRet retornoAvancar = LIS_CondRetListaVazia ;

      #ifdef _DEBUG
         if( pExtras == NULL || posicao < 1 || 
             posicao > EXT_DIM_EXTRAS )
         {
            return EXT_CondRetErroParm ;
         } /* if */
      #endif

      if( pExtras->numeroCartas == 0 )
      {
         return EXT_CondRetExtrasVazios ;
      } /* if */

      /* Move o ponteiro corrente da lista até a carta que se deseja 
         remover, removendo-a caso possível. */

         IrInicioLista( pExtras->pLista ) ;
         retornoAvancar = LIS_AvancarElementoCorrente( 
                              pExtras->pLista , posicao ) ;

         if( retornoAvancar == LIS_CondRetFimLista )
         {
            return EXT_CondRetFimExtras ;
         }
         else if( retornoAvancar == LIS_CondRetListaVazia ) 
         {
            return EXT_CondRetExtrasVazios ;
         } /* if */

      /* Verifica se a posição está ocupada */

         if( LIS_ObterValor( pExtras->pLista ) == NULL )
         {
            return EXT_CondRetPosicaoInvalida ;
         } /* if */
       
      /* Exclui a carta na posição desejada */

         if( LIS_ExcluirElemento( pExtras->pLista ) == 
             LIS_CondRetListaVazia )
         {
            return EXT_CondRetExtrasVazios ;
         } /* if */
         ( pExtras->numeroCartas )-- ;

      /* Coloca um nó vazio naquela posição */

         if( LIS_InserirElementoApos( pExtras->pLista , NULL ) ==
             LIS_CondRetFaltouMemoria )
         {
            IrInicioLista( pExtras->pLista ) ;
            return EXT_CondRetFaltouMemoria ;
         } /* if */

         IrInicioLista( pExtras->pLista ) ;
         return EXT_CondRetOK ;

   } /* Fim função: EXT  &Remover carta em certa posição */

/***********************************************************************
*
*  Função: EXT  &Obter carta em certa posição
*  ****/

   CAR_tppCarta EXT_ObterCartaPosicao( EXT_tppExtras pExtras , 
                                       int posicao            )
   {

      CAR_tppCarta pCarta = NULL ;

      LIS_tpCondRet retornoAvancar = LIS_CondRetListaVazia ;

      #ifdef _DEBUG
         if( pExtras == NULL || posicao < 1 || 
             posicao > EXT_DIM_EXTRAS )
         {
            return NULL ;
         } /* if */
      #endif

      if( pExtras->numeroCartas == 0 )
      {
         return NULL ;
      } /* if */

      /* Move o ponteiro corrente da lista até a carta que se deseja 
         obter, retornando-a caso possível. O +1 pula o nó cabeça 
         auxiliar. */

         IrInicioLista( pExtras->pLista ) ;
         retornoAvancar =  LIS_AvancarElementoCorrente( 
                              pExtras->pLista , posicao ) ;

         if( retornoAvancar == LIS_CondRetFimLista || 
             retornoAvancar == LIS_CondRetListaVazia ) 
         {
            return NULL ;
         } /* if */
                  
         pCarta = ( CAR_tppCarta ) LIS_ObterValor( pExtras->pLista ) ;

         IrInicioLista( pExtras->pLista ) ;

         return pCarta ;

   } /* Fim função: EXT  &Obter carta em certa posição */


/***********************************************************************
*
*  Função: EXT  &Transformar os espaços extras em uma string
*  ****/

   EXT_tpCondRet EXT_ConverterParaString( EXT_tppExtras pExtras , 
                                          char * extrasString    ) 
   {

      int i ;

      char cartaString[ CAR_DIM_STRING ] = "\0" ;
      char vazioString[ CAR_DIM_STRING ] = "\0" ;
            /* String que representa um espaço extra vazio */

      CAR_tppCarta pCarta = NULL ;

      LIS_tpCondRet retornoAvancar = LIS_CondRetOK ;

      #ifdef _DEBUG
         if( pExtras == NULL || extrasString == NULL )
         {
            return EXT_CondRetErroParm ;
         } /* if */
      #endif

      extrasString[ 0 ] = '\0' ;

      for( i = 0 ; i < ( CAR_DIM_STRING - 1 ) ; i++ )
      {
         vazioString[ i ] = EXT_POS_VAZIA ;
      } /* for */
      vazioString[ i ] = '\0' ;

      /* Para cada espaço extra ocupado, gera a string da carta que 
         o ocupa e concatena com a string total dos espaços extras.
         Primeiramente, pula o nó cabeça auxiliar */

         IrInicioLista( pExtras->pLista ) ;
         retornoAvancar = LIS_AvancarElementoCorrente( 
                             pExtras->pLista , 1 ) ;
         for( i = 1 ; i <= EXT_DIM_EXTRAS && retornoAvancar == 
                      LIS_CondRetOK ; i++ )
         {
            if( i > 1 )
            {
               strcat( extrasString , " " ) ;
            } /* if */

            pCarta = ( CAR_tppCarta ) LIS_ObterValor( 
                                         pExtras->pLista ) ;
            if( pCarta != NULL )
            {
               CAR_ConverterParaString( pCarta , cartaString ) ;
               strcat( extrasString , cartaString ) ;
            }
            else 
            {
               strcat( extrasString , vazioString ) ;
            } /* if */
    
            retornoAvancar = LIS_AvancarElementoCorrente( 
                                 pExtras->pLista , 1 ) ; 
         } /* for */
         IrInicioLista( pExtras->pLista ) ;

         return EXT_CondRetOK ;

   } /* Fim função: EXT  &Transformar os espaços extras em uma string */


/********** Fim do módulo de implementação: EXT  Espaços extras do jogo **********/
