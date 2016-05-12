/***************************************************************************
*  $MCI M�dulo de implementa��o: EMB  Embaralha cartas de um baralho
*
*  Arquivo gerado:              EMBARALHAMENTO.c
*  Letras identificadoras:      EMB
*
*  Nome da base de software:    Trabalho 2 de Programa��o Modular
*  Arquivo da base de software: EMBARALHAMENTO/EMBARALHAMENTO.C
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: ffa
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data      Observa��es
*     1       ffa   11/out/2013  princ�pio do desenvolvimento
*
***************************************************************************/


#include   <stdlib.h>
#include   <time.h>

#include   "CARTA.H"

#ifdef _DEBUG
   #include   "LISTA_INSTR.H"
#else
   #include   "LISTA.H"
#endif

#define EMBARALHAMENTO_OWN
#include "EMBARALHAMENTO.h"
#undef EMBARALHAMENTO_OWN


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static EMB_tpCondRet CopiaBaralho( LIS_tppLista pLista    , 
                                      LIS_tppLista pListaNova ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/******************************************************************************
*
*  Fun��o: EMB  &Embaralhar cartas
*  ****/

   EMB_tpCondRet EMB_Embaralhar( LIS_tppLista pLista ) 
   {
      int i = 0 ; 
      int randomPos = 0 ;

      int sorteado[ EMB_NUM_CARTAS ] ; 
         /*  Informa se a carta na i-�sima posi��o de pLista 
            j� foi sorteada */

      CAR_tppCarta pCarta = NULL ;
      
      LIS_tppLista pListaNova = NULL ; 
               /* Lista que vai guardar as cartas embaralhadas */

      LIS_tpCondRet retornoInsercao = LIS_CondRetFaltouMemoria ;
      LIS_tpCondRet retornoAvancar  = LIS_CondRetFimLista ;

      #ifdef _DEBUG
         if( pLista == NULL)
         {
            return EMB_CondRetErroParm ;
         } /* if */
      #endif 

      pListaNova = LIS_CriarLista( NULL ) ;
      if( pListaNova == NULL )
      {
         return EMB_CondRetFaltouMemoria ;
      } /* if */

      srand(( unsigned ) time( NULL )) ;

      /* Marca todas as cartas do baralho como n�o sorteadas */

         for( i = 0 ; i < EMB_NUM_CARTAS ; i++ )
         {
            sorteado[ i ] = EMB_NAO_SORTEADA ;
         }

      /* Gera um novo baralho com as cartas embaralhadas */   

         IrInicioLista( pLista ); 
         for( i = 0 ; i < EMB_NUM_CARTAS ; i++ )
         {        
            /* Gera um numero aleatorio entre 0 e 51, que indica a
               posi��o em pLista da carta a ser inserida no novo
               baralho */
            
               randomPos = ( rand() % EMB_NUM_CARTAS ) ;

            /* Caso j� n�o tenha sido sorteada, obt�m a carta do 
               baralho original e a coloca no novo baralho */
               if( sorteado[ randomPos ] == EMB_NAO_SORTEADA )
               {
                  sorteado[ randomPos ] = EMB_SORTEADA ;
                  
                  retornoAvancar = LIS_AvancarElementoCorrente( pLista    , 
                                                                randomPos  ) ; 
                  if( retornoAvancar == LIS_CondRetFimLista )
                  {
                     LIS_DestruirLista( pListaNova ) ;

                     return EMB_CondRetFimLista ;
                  }
                  else if( retornoAvancar == LIS_CondRetListaVazia )
                  {
                     LIS_DestruirLista( pListaNova ) ;

                     return EMB_CondRetListaVazia ;
                  } /* if */

                  pCarta = ( CAR_tppCarta ) LIS_ObterValor( pLista ) ;          
                  if( pCarta == NULL )
                  {
                     LIS_DestruirLista( pListaNova ) ;

                     return EMB_CondRetCartaNaoExiste ;
                  } /* if */

                  retornoInsercao = LIS_InserirElementoApos( pListaNova     , 
                                                            (void *) pCarta  ) ; 
                  if( retornoInsercao == LIS_CondRetFaltouMemoria )
                  {
                     LIS_DestruirLista( pListaNova ) ;

                     return EMB_CondRetFaltouMemoria ;
                  } /* if */

                  IrInicioLista( pLista ) ; 
               }

            /* Se a carta j� fora sorteada, ignora esta itera��o para
               tentar escolher outra carta  */

               else
               {                  
                  i-- ;
               }
         }

      /* Copia o novo baralho pro baralho original */

         return CopiaBaralho( pLista , pListaNova ) ;

   } /* Fim fun��o: EMB  &Embaralhar cartas */

 /* Fim fun��o: EMB  &Embaralhar cartas */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: EMB  -CopiaBaralho
*
*  $ED Descri��o da fun��o
*     Recebe duas listas de cartas, esvazia a primeira,
*        copia a segunda para a primeira e destroi a segunda
*
*  $EP Par�metros
*    pLista     - Lista que deve ser substituida
*    pListaNova - Lista que ser� copiada para pLista e depois detru�da
*
*  $FV Valor retornado
*     EMB_CondRetOK             - se a lista foi embaralhada com sucesso.
*     EMB_CondRetFimLista       - se tentou avan�ar mais elementos que 
*                                 haviam na lista.
*     EMB_CondRetListaVazia     - tentou avan�ar ou obter valor em uma 
*                                 lista vazia
*     EMB_CondRetFaltouMemoria  - faltou mem�ria ao se tentar inserir
*                                 uma carta em uma lista
*     EMB_CondRetCartaNaoExiste - se por algum motivo a lista tinha um
*                                  elemento sem carta 
*     
***********************************************************************/

   EMB_tpCondRet CopiaBaralho( LIS_tppLista pLista    , 
                               LIS_tppLista pListaNova )
   {
      
      LIS_tpCondRet retornoInsercao = LIS_CondRetFaltouMemoria ;
      LIS_tpCondRet retornoAvancar  = LIS_CondRetFimLista ;

      CAR_tppCarta pCarta = NULL ;

      int i = EMB_NUM_CARTAS ;

      LIS_EsvaziarLista( pLista ) ;      
      IrInicioLista( pListaNova ) ;

      for( i = 0 ; i < EMB_NUM_CARTAS ; i++ )
      {
         pCarta = ( CAR_tppCarta ) LIS_ObterValor( pListaNova ) ;
         if( pCarta == NULL )
         {
            return EMB_CondRetCartaNaoExiste ;
         }

         retornoInsercao = LIS_InserirElementoApos( pLista          , 
                                                   ( void * ) pCarta ) ;
         if( retornoInsercao == LIS_CondRetFaltouMemoria )
         {
            LIS_DestruirLista( pListaNova ) ;
            return EMB_CondRetFaltouMemoria ;
         } /* if */
         
         retornoAvancar = LIS_AvancarElementoCorrente( pListaNova , 1 ) ;
         if( i < ( EMB_NUM_CARTAS - 1 ) &&
             retornoAvancar == LIS_CondRetFimLista )
         {
            LIS_DestruirLista( pListaNova ) ;           
            return EMB_CondRetFimLista ;
         }
         else if( retornoAvancar == LIS_CondRetListaVazia )
         {
            LIS_DestruirLista( pListaNova ) ;
            return EMB_CondRetListaVazia ;
         } /* if */
      } /* for */

      LIS_DestruirLista( pListaNova ) ; 
      
      return EMB_CondRetOK ;

   } /* Fim fun��o: EMB -CopiaBaralho  */

/*** Fim do m�dulo de implementa��o: EMB Embaralha cartas de um baralho *****/
