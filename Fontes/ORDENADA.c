/***************************************************************************
*  $MCI Módulo de implementação: ORD  Sequência Ordenada
*
*  Arquivo gerado:              ORDENADA.c
*  Letras identificadoras:      ORD
*
*  Nome da base de software:    Trabalho 2 de Programação Modular
*  Arquivo da base de software: ORDENADA/ORDENADA.C
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gss
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       gss   12/out/2013 início do desenvolvimento
*
***************************************************************************/
#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#ifdef _DEBUG
   #include   "LISTA_INSTR.H"
#else
   #include   "LISTA.H"
#endif

#define ORDENADA_OWN
#include "ORDENADA.H"
#undef ORDENADA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ORD Descritor da cabeça de lista de cartas ordenadas
*
*
***********************************************************************/

   typedef struct ORD_tagOrdenada {

      LIS_tppLista  pLista;  /* instancia de lista */

   } ORD_tpOrdenada ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirCarta( void * pDado ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  Função: ORD  &Criar lista ordenada
*  ****/

   ORD_tppOrdenada ORD_CriarOrdenada( void )
   {

      ORD_tpOrdenada * pOrdenada = NULL ;

      pOrdenada = ( ORD_tpOrdenada * ) malloc( sizeof( ORD_tpOrdenada )) ;
      if( pOrdenada == NULL )
      {
         return NULL ;
      } /* if */

      /* Tenta criar a lista; caso não consiga retorna NULL */

         pOrdenada->pLista = LIS_CriarLista( DestruirCarta ) ;
         if( pOrdenada->pLista == NULL )
         {
            free( pOrdenada ) ;

            return NULL ;
         } /* if */

         return pOrdenada;

   } /* Fim função: ORD  &Criar lista ordenada */


/***********************************************************************
*
*  Função: ORD  &Destruir lista ordenada
*  ****/

   void ORD_DestruirOrdenada( ORD_tppOrdenada pOrdenada ) 
   {

      if( pOrdenada == NULL )
      {
         return;
      } /* if */

      LIS_DestruirLista( pOrdenada->pLista ) ;

      free( pOrdenada ) ;

   } /* Fim função: ORD  &Destruir lista ordenada */

/***********************************************************************
*
*  Função: ORD  &Inserir carta em sequência ordenada
*  ****/

   ORD_tpCondRet ORD_InserirCarta( ORD_tppOrdenada pOrdenada , 
                                   CAR_tppCarta pCarta        ) 
   {

      LIS_tpCondRet retornoInsercao = LIS_CondRetFaltouMemoria ;

      CAR_tppCarta AsAux = NULL ;
      CAR_tppCarta pCartaFinal = NULL ;

      #ifdef _DEBUG
         if( pOrdenada == NULL || pCarta == NULL )
         {
            return ORD_CondRetErroParm ;
         } /* if */
      #endif

      IrFinalLista( pOrdenada->pLista ) ;
      pCartaFinal = ( CAR_tppCarta ) LIS_ObterValor( pOrdenada->pLista ) ;
     
      /* Trata caso da primeira inserção; carta deve ser Às */

         if ( LIS_AvancarElementoCorrente( pOrdenada->pLista , 0 )
                 == LIS_CondRetListaVazia )
         {
            AsAux = CAR_CriarCarta( CAR_NaipePaus , CAR_RankAs ) ;
            if ( CAR_CompararRank( AsAux , pCarta ) == CAR_CondRetIgual )
            {
               retornoInsercao = LIS_InserirElementoApos( 
                                    pOrdenada->pLista , pCarta ) ;
               if ( retornoInsercao == LIS_CondRetFaltouMemoria )
               {
                  return ORD_CondRetFaltouMemoria ;
               } /* if */

               return ORD_CondRetOK ;
            } /* if */
         }

      /* Trata caso de inserções subsequentes */ 
        
         else 
         {
            if( CAR_CompararNaipe( pCarta , pCartaFinal ) 
                   == CAR_CondRetIgual
                && CAR_CompararRank( pCarta , pCartaFinal )  
                      == CAR_CondRetSucessor )
            {
               retornoInsercao = LIS_InserirElementoApos( 
                                    pOrdenada->pLista , pCarta ) ;
               if ( retornoInsercao == LIS_CondRetFaltouMemoria )
               {
                  return ORD_CondRetFaltouMemoria ;
               } /* if */

               return ORD_CondRetOK ;
            }
         } /* else */

         return ORD_CondRetCartaInvalida ;

   } /* Fim função: ORD  &Inserir carta em sequência ordenada */

/***************************************************************************
*
*  Função: ORD  Obter Topo
*  ****/
   CAR_tppCarta ORD_ObterTopo( ORD_tppOrdenada pOrdenada )
   {
     
      #ifdef _DEBUG
         if( pOrdenada == NULL )
         {
            return NULL;
         }
      #endif
      
      /* Tenta obter a carta desejada, retornando-a caso possível; no caso
         da movimentação inválida, retornará NULL */

         IrFinalLista( pOrdenada->pLista ) ;
         return LIS_ObterValor( pOrdenada->pLista ) ;
        
   } /* Fim função: ORD  Obter Topo */


/***********************************************************************
*
*  Função: ORD  &Transformar as sequências ordenadas em uma string
*  ****/

   ORD_tpCondRet ORD_ConverterParaString( ORD_tppOrdenada pOrdenada , 
                                          char * ordenadaString      ) 
   {

      int i ;

      char cartaString[ CAR_DIM_STRING ] = "\0" ;

      CAR_tppCarta pCarta = NULL ;

      LIS_tpCondRet retornoAvancar = LIS_CondRetOK ;
      
      #ifdef _DEBUG
         if( pOrdenada == NULL || ordenadaString == NULL )
         {
            return ORD_CondRetErroParm ;
         } /* if */
      #endif      

      ordenadaString[ 0 ] = '\0';

      IrInicioLista( pOrdenada->pLista ) ;
      pCarta = ( CAR_tppCarta ) LIS_ObterValor( pOrdenada->pLista ) ;
      for( i = 1 ; i <= ORD_MAX_DIM_CARTAS && retornoAvancar == 
                      LIS_CondRetOK ; i++ )
         {
            if( i > 1 )
            {
               strcat( ordenadaString , " " ) ;
            } /* if */

            pCarta = ( CAR_tppCarta ) LIS_ObterValor( 
                                         pOrdenada->pLista ) ;
            if( pCarta != NULL )
            {
               CAR_ConverterParaString( pCarta , cartaString ) ;
               strcat( ordenadaString , cartaString ) ;
            }
    
            retornoAvancar = LIS_AvancarElementoCorrente( 
                                 pOrdenada->pLista , 1 ) ; 
         } /* for */
         IrInicioLista( pOrdenada->pLista ) ;

         return ORD_CondRetOK ;
         
   } /* Fim função: ORD  &Transformar as sequências ordenadas em uma string */

/***************************************************************************
*
*  Função: ORD  &Obter numero de cartas
*  ****/

   int ORD_ObterNumeroCartas( ORD_tppOrdenada pOrdenada ) 
   {

      #ifdef _DEBUG
         if( pOrdenada == NULL )
         {
            return ORD_CondRetErroParm ;
         } /* if */
      #endif   

		return LIS_ObterNumeroElementos( pOrdenada->pLista ) ; 

   } /*Fim da função: ORD  &Obter numero de cartas */


/*****  Código das funções encapsuladas no módulo  *****/

   void DestruirCarta( void * pDado ) 
   {

      CAR_DestruirCarta( ( CAR_tppCarta ) ( pDado ) ) ;

   } /* Fim função: ORD  -Destruir carta */


/********** Fim do módulo de implementação: ORD  Sequência Ordenada **********/
