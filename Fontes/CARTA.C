/***************************************************************************
*  $MCI Módulo de implementação: CAR  Carta de um baralho
*
*  Arquivo gerado:              CARTA.c
*  Letras identificadoras:      CAR
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
*     1       clm   11/out/2013  início do desenvolvimento
*
***************************************************************************/

#include   <string.h>
#include   <malloc.h>

#define CARTA_OWN
#include "CARTA.h"
#undef CARTA_OWN

#ifdef _DEBUG
   #include "GENERICO.h"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: CAR Descritor de uma carta
*
*
***********************************************************************/

   typedef struct CAR_tagCarta {

         CAR_tpNaipe naipe ;
               /* Naipe da carta */

         CAR_tpRank rank ;
               /* Rank da carta */

         CAR_tpCor cor;
               /* Cor da carta */

   } CAR_tpCarta ;

/***** Dados encapsulados no módulo *****/

   static char naipeParaChar[ 4 ] = { 'P' , 'E' , 'C' , 'O' } ;    
         /* Tabela de conversão de Naipe para Carectere representativo */
   static char corParaChar[ 2 ] = { 'V' , 'P' } ;
         /* Tabela de conversão de Cor para Carectere representativo */
   static char rankParaChar[ 13 ] = { 'A' , '2' , '3' , '4' , '5' ,
                                      '6' , '7' , '8' , '9' , 'T' ,
                                      'J' , 'Q' , 'K' } ;
         /* Tabela de conversão de Rank para Carectere representativo */

/***** Protótipos das funções encapsuladas no módulo *****/

   static CAR_tpCor ObterCor( CAR_tpNaipe naipe ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: CAR  &Criar carta
*  ****/

   CAR_tppCarta CAR_CriarCarta( CAR_tpNaipe naipe , CAR_tpRank rank ) 
   {

      CAR_tpCarta * pCarta = NULL;

      pCarta = ( CAR_tpCarta * ) malloc( sizeof( CAR_tpCarta ));
      if(pCarta == NULL)
      {
         return NULL;
      } /* if */

      pCarta->naipe = naipe;
      pCarta->rank  = rank;
      pCarta->cor   = ObterCor(naipe);

      return pCarta ;

   } /* Fim função: CAR  &Criar carta */

/***************************************************************************
*
*  Função: CAR  &Destruir carta
*  ****/

   void CAR_DestruirCarta( CAR_tppCarta pCarta ) 
   {
      
      free( pCarta ) ;

   } /* Fim função: CAR  &Destruir carta */

/***********************************************************************
*
*  Função: CAR  &Obter naipe da carta
*  ****/

   CAR_tpNaipe CAR_ObterNaipe( CAR_tppCarta pCarta ) 
   {
      
      #ifdef _DEBUG
         if( pCarta == NULL )
         {
            return CAR_PARM_INVALIDO ;
         } /* if */
      #endif

      return ( pCarta->naipe ) ;

   } /* Fim função: CAR  &Obter naipe da carta */

/***************************************************************************
*
*  Função: CAR  &Comparar naipes de duas cartas
*  ****/

   CAR_tpCondRet CAR_CompararNaipe( CAR_tppCarta pCartaA, 
                                   CAR_tppCarta pCartaB ) 
   {
           
      #ifdef _DEBUG
         if( pCartaA == NULL || pCartaB == NULL )
         {
            return CAR_CondRetErroParm ;
         } /* if */
      #endif

      if( pCartaA->naipe == pCartaB->naipe )
      {
         return CAR_CondRetIgual ;
      }
      
      return CAR_CondRetDiferente ;

   } /* Fim função: CAR  &Comparar naipes de duas cartas */

/***************************************************************************
*
*  Função: CAR  &Comparar ranks de duas cartas
*  ****/

   CAR_tpCondRet CAR_CompararRank( CAR_tppCarta pCartaA , 
                                   CAR_tppCarta pCartaB  ) 
   {
     
      CAR_tpRank rankA ;
      CAR_tpRank rankB ;

      #ifdef _DEBUG
         if( pCartaA == NULL || pCartaB == NULL )
         {
            return CAR_CondRetErroParm ;
         } /* if */
      #endif

      rankA = pCartaA->rank ;
      rankB = pCartaB->rank ;

      /* Trata caso menor */

         if( rankA < rankB )
         {
            if( rankA == ( rankB - 1 ))
            {
               return CAR_CondRetAntecessor ;
            }
            else
            {
               return CAR_CondRetMenor ;
            }
         }

      /* Trata caso maior */

         if( rankA > rankB )
         {
            if( rankA == ( rankB + 1 ))
            {
               return CAR_CondRetSucessor ;
            }
            else
            {
               return CAR_CondRetMaior ;
            }
         }

      /* Trata caso igual */

         return CAR_CondRetIgual ;
      
   } /* Fim função: &CAR  Comparar ranks de duas cartas */

/***************************************************************************
*
*  Função: CAR  &Comparar cores de duas cartas
*  ****/

   CAR_tpCondRet CAR_CompararCor( CAR_tppCarta pCartaA , 
                                  CAR_tppCarta pCartaB  )      
   {
      
      #ifdef _DEBUG
         if( pCartaA == NULL || pCartaB == NULL )
         {
            return CAR_CondRetErroParm ;
         } /* if */
      #endif

      if( pCartaA->cor == pCartaB->cor )
      {
         return CAR_CondRetIgual ;
      }
      
      return CAR_CondRetDiferente ;

   } /* Fim função: CAR  &Comparar cores de duas cartas */

/***************************************************************************
*
*  Função: CAR  &Transformar a carta em uma string
*  ****/

   CAR_tpCondRet CAR_ConverterParaString( CAR_tppCarta pCarta , 
                                          char * cartaString   ) 
   {

      #ifdef _DEBUG
         if( pCarta == NULL || cartaString == NULL )
         {
            return CAR_CondRetErroParm ;
         } /* if */
      #endif
           
      /* Gera a string no formato <cor><naipe><rank>'\0' */

         cartaString[ 0 ] = corParaChar[ pCarta->cor ] ;
         cartaString[ 1 ] = naipeParaChar[ pCarta->naipe ] ;
         cartaString[ 2 ] = rankParaChar[ pCarta->rank ] ;
         cartaString[ 3 ] = '\0';

         return CAR_CondRetOK ;

   } /* Fim função: CAR  &Transformar a carta em uma string */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: CAR  -Obter cor associada a um naipe
*
*  $ED Descrição da função
*     Retorna a cor associada ao naipe.
*
***********************************************************************/

   CAR_tpCor ObterCor( CAR_tpNaipe naipe )
   {

      #ifdef _DEBUG
         if( naipe < CAR_NaipePaus || naipe > CAR_NaipeOuros )
         {
            return CAR_PARM_INVALIDO ;
         } /* if */
      #endif


      if ( naipe == CAR_NaipePaus || naipe == CAR_NaipeEspadas )
      {
         return CAR_CorPreta ;
      } 
      else if (naipe == CAR_NaipeCopas || naipe == CAR_NaipeOuros )
      {
            return CAR_CorVermelha ;
      }
      /* if */

      return CAR_CorVermelha ;

   } /* Fim função: CAR  -Obter cor associada a um naipe */



/********** Fim do módulo de implementação: CAR  Carta de um baralho **********/

