/***************************************************************************
*  $MCI Módulo de implementação: FRC  Free Cell
*
*  Arquivo gerado:              FREECELL.c
*  Letras identificadoras:      FRC
*
*  Nome da base de software:    Trabalho 4 de Programação Modular
*  Arquivo da base de software: FREECELL/FREECELL.C
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gss
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       gss   25/nov/2013 início do desenvolvimento
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

#include "ORDENADA.h"
#include "VISIVEL.h"
#include "CARTA.h"
#include "EMBARALHAMENTO.h"
#include "EXTRAS.h"

#define FREECELL_OWN
#include "FREECELL.h"
#undef FREECELL_OWN

#define FALSE 0
#define TRUE 1
#define FRC_NUM_COLS 13


/***** Protótipos das funções encapuladas no módulo *****/

   static LIS_tppLista FRC_CriarBaralho() ;


/*****  Código das funções exportadas pelo módulo  *****/   

/******************************************************************************
*
*  Função: FRC  &Mover Carta
*  ****/


   FRC_tpCondRet FRC_MoverCarta( LIS_tppLista pMesa , char * origem , 
                    int CodOrigem , char * destino , int CodDestino  )
   {
      CAR_tppCarta pAuxCar = NULL;

      int naipeParaPos[ 4 ] = { 0 , 1 , 2 , 3 } ;
         /* Determina em qual coluna de ordenadas a carta deve ser inserida */

      #ifdef _DEBUG
         if( pMesa == NULL || origem == NULL || destino == NULL
            || CodOrigem < 0 || CodOrigem > 9 || CodDestino < 0
            || CodDestino > 9 )
         {
            return FRC_CondRetErroParm ;
         }
      #endif

      IrInicioLista( pMesa ) ;
      
      /* Obtem-se a carta que deseja-se mover */
         if( strcmp( origem , "vis" ) == 0 )
         {
            LIS_AvancarElementoCorrente( pMesa , 4 + CodOrigem ) ;
            pAuxCar = VIS_ObterCartaPosicao( (VIS_tppVisivel) LIS_ObterValor(pMesa) , 0 ) ;
         }

         else if( strcmp( origem , "ext" ) == 0 )
         {
            LIS_AvancarElementoCorrente( pMesa , 4 ) ;
            pAuxCar = EXT_ObterCartaPosicao( (EXT_tppExtras) LIS_ObterValor(pMesa) ,
                                     CodOrigem ) ;
         } /* if */

      /* Nenhuma carta obtida indica que a lista estava vazia */
         if( pAuxCar == NULL )
            return FRC_CondRetListaVazia ;
      
      /* Tenta-se inserir a carta na coluna de destino */
         IrInicioLista( pMesa ) ;
         if( strcmp( destino , "ord" ) == 0 )
         {
            LIS_AvancarElementoCorrente( pMesa , 
               naipeParaPos[ CAR_ObterNaipe( pAuxCar ) ] ) ;
            if( ORD_InserirCarta( ( ORD_tppOrdenada ) LIS_ObterValor( pMesa ) , 
                  pAuxCar) != ORD_CondRetOK )
            {
               return FRC_CondRetInsInvalida ;
            } /* if */
         } 
         else if( strcmp( destino , "vis" ) == 0 )
         {
            LIS_AvancarElementoCorrente(pMesa, 4 + CodDestino);
            if( VIS_InserirCarta( ( VIS_tppVisivel ) LIS_ObterValor( pMesa ) , 
                  pAuxCar , VIS_ModoComOrdem ) != VIS_CondRetOK )
            {
               return FRC_CondRetInsInvalida ;
            } /* if */
         }
         else if( strcmp( destino , "ext" ) == 0 ){
            LIS_AvancarElementoCorrente( pMesa , 4 ) ;
            if( EXT_InserirCartaPosicao( ( EXT_tppExtras ) LIS_ObterValor(pMesa) ,
                     pAuxCar , CodDestino ) != EXT_CondRetOK )
            {
               return FRC_CondRetInsInvalida ;
            } /* if */
         } /* if */


      /* Caso tenha sido possível inserir a carta, remove da origem */
         IrInicioLista( pMesa ) ;
         if( strcmp( origem , "vis" ) == 0 )
         {
            LIS_AvancarElementoCorrente(pMesa, 4 + CodOrigem ) ;
            if( VIS_RemoverCarta( ( VIS_tppVisivel ) LIS_ObterValor( pMesa ) ) != VIS_CondRetOK )
            {
               return FRC_CondRetRemInvalida;
            } /* if */
         } /* if */

         else if( strcmp( origem , "ext" ) == 0 ){
            LIS_AvancarElementoCorrente(pMesa, 4);
            if(EXT_RemoverCartaPosicao(( EXT_tppExtras ) LIS_ObterValor( pMesa ) , 
                  CodOrigem ) != EXT_CondRetOK )
            {
               return FRC_CondRetRemInvalida;
            } /* if */
         } /* if */
      
      return FRC_CondRetOK;


   }

/******************************************************************************
*
*  Função: FRC  &Começar Jogo
*  ****/


   LIS_tppLista FRC_ComecarJogo( )
   {
      int i, j;

      EXT_tppExtras   pAuxExt;
      VIS_tppVisivel  pAuxVis;
      ORD_tppOrdenada pAuxOrd;

      LIS_tppLista pBaralho;
      LIS_tppLista pMesa = LIS_CriarLista( NULL ) ;

      /* Não foi possível criar a lista de listas */
         if( pMesa == NULL ){
            return NULL;
         } /* if */

      /* Cria um baralho com 52 cartas e as embaralha */
         pBaralho = FRC_CriarBaralho();
         if(pBaralho == NULL){
            return NULL ;
         } /* if */

         EMB_Embaralhar( pBaralho ) ;

      /* Primeiro, cria cada uma das colunas que ira compor o jogo, na ordem:
            4 ordenadas , 1 de extras , 8 de visiveis */
         for( i = 0 ;
              i < FRC_NUM_COLS ; 
              i++ )
         {
            if( i > 4 )
            {
               pAuxVis = VIS_CriarVisivel( ) ;
               LIS_InserirElementoApos( pMesa , ( void *) pAuxVis ) ;
            }

            else if( i < 4 )
            {
               pAuxOrd = ORD_CriarOrdenada( ) ;
               LIS_InserirElementoApos( pMesa , ( void *) pAuxOrd ) ;
            }
            
            else 
            {
               pAuxExt = EXT_CriarExtras( ) ;
               LIS_InserirElementoApos( pMesa , ( void *) pAuxExt ) ;  
            } /* if */ 
         }

      /* Agora, insere as cartas nas colunas visiveis */ 
         
         IrInicioLista( pBaralho ) ;

         IrInicioLista( pMesa ) ;   
         LIS_AvancarElementoCorrente( pMesa , 5 ) ;
         
         for( j = 0 ;
              j < 8 ;
              j++ )
         {
         /* Primeiras 4 colunas, que recebem 7 cartas cada */

            if( j < 4 )
            {
               for( i = 0 ;
                    i < 7 ;
                    i++ )
               {
                  VIS_InserirCarta( ( VIS_tppVisivel ) ( LIS_ObterValor( pMesa ) )  , 
                                    ( CAR_tppCarta ) ( LIS_ObterValor( pBaralho ) ) ,
                                    VIS_ModoSemOrdem ) ;

                  LIS_AvancarElementoCorrente( pBaralho , 1 ) ;
               } /* for */
            }

         /* Últimas 4 colunas, que recebem 6 cartas cada */
            else
            {
               for( i = 0 ;
                    i < 6 ;
                    i++ )
               {
                  VIS_InserirCarta( ( VIS_tppVisivel ) LIS_ObterValor( pMesa )  ,
                                    ( CAR_tppCarta ) LIS_ObterValor( pBaralho ) ,
                                    VIS_ModoSemOrdem ) ;

                  LIS_AvancarElementoCorrente( pBaralho , 1 ) ;
               } /* for */
            } /* if */

            LIS_AvancarElementoCorrente( pMesa , 1 ) ;
         } /* for */

         LIS_DestruirLista( pBaralho );
      
      return pMesa;
   }

/******************************************************************************
*
*  Função: FRC  &verificarVitoria
*  ****/

   int FRC_VerificarVitoria( LIS_tppLista pMesa )
   {
      int i ;

      #ifdef _DEBUG
         if( pMesa == NULL )
         {
            return FRC_CondRetErroParm ;
         } /* if */
      #endif

      IrInicioLista( pMesa ) ;
      for( i = 0 ;
           i < 4 ;
           i++ , 
           LIS_AvancarElementoCorrente( pMesa , 1 ) )
      {
         if( LIS_ObterNumeroElementos( ( LIS_tppLista ) LIS_ObterValor( pMesa ) )!=14)
            return FALSE;
      } /* for */

      return TRUE;
   }

/******************************************************************************
*
*  Função: FRC  &Salvar Score
*  ****/

   FRC_tpCondRet FRC_SalvarScore( int status )
   {
      FILE * f;

      int vitoria = 0 ;
      int derrota = 0 ;

      #ifdef _DEBUG
         if(status != 1 && status != 0)
         {
            return FRC_CondRetErroParm;
         } /* if */
      #endif

      f = fopen( "score.txt" , "r" ) ;
      if(f == NULL){
         if(status == TRUE)
         {
            vitoria = 1;
         }
         else
         {
            derrota = 1;
         } /* if */
      }
      else
      {
         fscanf(f,"v:%d d:%d", &vitoria, &derrota);
         if(status == TRUE)
            vitoria++;
         else
            derrota++ ;
         fclose(f);
      } /* if */

      f = fopen( "score.txt" , "w" ) ;
      fprintf( f , "v:%d d:%d", vitoria , derrota ) ;

      return FRC_CondRetOK;
   }

/******************************************************************************
*
*  Função: FRC  &Finalizar Jogo
*  ****/

   FRC_tpCondRet FRC_FinalizarJogo( LIS_tppLista pMesa )
   {
    
      int i = 0 ;
      int j = 0 ;
    
      ORD_tppOrdenada pAuxOrdenada ;
      EXT_tppExtras   pAuxExtras ;
      VIS_tppVisivel  pAuxVisivel ;
      CAR_tppCarta    pAuxCarta ;
    
      IrInicioLista( pMesa ) ;
    
      for( i = 0 ; i < FRC_NUM_COLS ; i++ )
      {
         /* Ordenadas */
        
            if( i < 4 )
            {
              pAuxOrdenada = ( ORD_tppOrdenada ) LIS_ObterValor( pMesa ) ;
    
              ORD_DestruirOrdenada( pAuxOrdenada ) ;
            }
         /* Extras */
    
            else if( i == 4 )
            {
               pAuxExtras = ( EXT_tppExtras ) LIS_ObterValor( pMesa ) ;
    
               for( j = 1 ; j <= EXT_DIM_EXTRAS ; j++ )
               {
                  pAuxCarta = EXT_ObterCartaPosicao( pAuxExtras , j ) ;
                  if( pAuxCarta != NULL )
                  {
                     CAR_DestruirCarta( pAuxCarta ) ;
                  } /* if */
               } /* for */
    
               EXT_DestruirExtras( pAuxExtras ) ;
            }
         /* Visiveis */
    
            else
            {
               pAuxVisivel = ( VIS_tppVisivel ) LIS_ObterValor( pMesa ) ;
    
               for( pAuxCarta = VIS_ObterCartaPosicao( pAuxVisivel , 0 ) ;
                    pAuxCarta != NULL ;
                    pAuxCarta = VIS_ObterCartaPosicao( pAuxVisivel , 0 ) )
               {
                  CAR_DestruirCarta( pAuxCarta ) ;
    
                  VIS_RemoverCarta( pAuxVisivel ) ;
               } /* if */
    
               VIS_DestruirVisivel( pAuxVisivel ) ;
            } /* if */
    
         /* Avança para a próxima coluna */
    
            LIS_AvancarElementoCorrente( pMesa , 1 ) ;
    
      } /* for */

      return FRC_CondRetOK;

   } /* Fim ativa: &FRC_FinalizarJogo */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: FRC  -CriarpBaralho
*
*  $ED Descrição da função
*     Cria uma lista contendo as 56 cartas (14 de cada naipe) existentes
*     em um pBaralho.
*
*  $EP Parâmetros
*     
*
*  $FV Valor retornado
*     Retorna um ponteiro para o pBaralho criado, ou NULL.
*     
***********************************************************************/

   LIS_tppLista FRC_CriarBaralho( )
   {

      int np ;
      int rk ;

      CAR_tppCarta pAuxCar;

      LIS_tppLista pNovo = LIS_CriarLista( NULL );
      if( pNovo == NULL)
      {
         return NULL ;
      } /* if */

      for( np  = CAR_NaipePaus  ; 
           np <= CAR_NaipeOuros ;
           np++ )
      {
         for( rk  = CAR_RankAs  ;
              rk <= CAR_RankRei ;
              rk++ )
         {
            pAuxCar = CAR_CriarCarta( ( CAR_tpNaipe ) ( np ) , 
                         ( CAR_tpRank ) ( rk ) );

            LIS_InserirElementoApos( pNovo , ( void *) pAuxCar ) ;        
         } /* for */
      } /* if */

      IrInicioLista( pNovo ) ;

      return pNovo;

   }




/********** Fim do módulo de implementação: FRC  Controla um jogo de FreeCell **********/