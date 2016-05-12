/***************************************************************************
*  $MCI Módulo de implementação: VIS  Sequência Visível
*
*  Arquivo gerado:              VISIVEL.C
*  Letras identificadoras:      VIS
*
*  Nome da base de software:    Trabalho 2 de Programação Modular
*  Arquivo da base de software: VISIVEL/VISIVEL.C
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gss
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data      Observações
*     1       gss   13/out/2013  início do desenvolvimento
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

#define VISIVEL_OWN
   #include "VISIVEL.h"
#undef VISIVEL_OWN

/***********************************************************************
*
*  $TC Tipo de dados: VIS Descritor da cabeça de lista de cartas visíveis
*
*
***********************************************************************/

   typedef struct VIS_tagVisivel {

      LIS_tppLista pLista;  
            /* Instância de lista */

   } VIS_tpVisivel ;


/***** Protótipos das funções encapuladas no módulo *****/

   static VIS_tpCondRet VIS_InserirCartaSemOrdem ( VIS_tppVisivel pVisivel , 
                                                   CAR_tppCarta pCarta      ) ;

   static VIS_tpCondRet VIS_InserirCartaComOrdem ( VIS_tppVisivel pVisivel ,
                                                   CAR_tppCarta pCarta      ) ;


/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: VIS  Criar Visivel
*  ****/

   VIS_tppVisivel VIS_CriarVisivel( void )
   {

      VIS_tpVisivel * pVisivel = NULL ;

      pVisivel = ( VIS_tpVisivel * ) malloc( sizeof( VIS_tpVisivel )) ;
      if( pVisivel == NULL )
      {
         return NULL ;
      } /* if */

      /* Tenta criar a lista; caso não consiga retorna NULL */

         pVisivel->pLista = LIS_CriarLista( NULL ) ;
         if( pVisivel->pLista == NULL )
         {
            free( pVisivel ) ;

            return NULL ;
         } /* if */

         return pVisivel ;

   } /* Fim função: VIS  &Criar lista visivel */

/***************************************************************************
*
*  Função: VIS  Destruir Visivel
*  ****/

   void VIS_DestruirVisivel( VIS_tppVisivel pVisivel )
   {
      
      if( pVisivel == NULL )
      {
         return;
      }
       
      LIS_DestruirLista( pVisivel->pLista ) ;

      free( pVisivel ) ;

   } /* Fim função: VIS  Criar Visivel */

/***********************************************************************
*
*  Função: VIS  &Inserir Carta em sequência visível
*  ****/

   VIS_tpCondRet VIS_InserirCarta( VIS_tppVisivel pVisivel , 
                                   CAR_tppCarta pCarta ,
                                   VIS_tpModo modo          ) 
   {

      #ifdef _DEBUG
         if( pVisivel == NULL || pCarta == NULL )
         {
            return VIS_CondRetErroParm ;
         } /* if */
      #endif  

      switch( modo )
      {
         case VIS_ModoSemOrdem:
            return VIS_InserirCartaSemOrdem( pVisivel , pCarta ) ;
            break ;
         case VIS_ModoComOrdem:  
            return VIS_InserirCartaComOrdem( pVisivel , pCarta ) ;
            break ;
         default:
            return VIS_CondRetModoInvalido ; 
      }

   } /* Fim função: VIS  Inserir Carta em sequência visível  */

/***************************************************************************
*
*  Função: VIS  Remover Carta de sequência visível
*  ****/
   VIS_tpCondRet VIS_RemoverCarta( VIS_tppVisivel pVisivel )
   {
      
      LIS_tpCondRet retornoRemocao ;

      #ifdef _DEBUG
         if( pVisivel == NULL )
         {
            return VIS_CondRetErroParm ;
         } /* if */
      #endif

      /* Remove a carta no topo da lista; volta para o começo desta para fazer
         seu cleanup, independente do resultado da remoção */

         IrFinalLista( pVisivel->pLista ) ;
         retornoRemocao = LIS_ExcluirElemento( pVisivel->pLista ) ;
         IrInicioLista( pVisivel->pLista ) ;

         if ( retornoRemocao == LIS_CondRetListaVazia )
         {
            return VIS_CondRetListaVazia ;
         } /* if */

         return VIS_CondRetOK ;

   } /* Fim função: VIS  Remover Carta de sequência visível */

/***************************************************************************
*
*  Função: VIS  Obter Carta Posição
*  ****/
   CAR_tppCarta VIS_ObterCartaPosicao( VIS_tppVisivel pVisivel ,
                                       int posicao )
   {
     
      LIS_tpCondRet retornoObter ;
        
      #ifdef _DEBUG
         if( pVisivel == NULL || posicao < 0 )
         {
            return NULL;
         }
      #endif
      
      /* Tenta obter a carta desejada, retornando-a caso possível; no caso
         da movimentação inválida, retornará NULL */

         IrFinalLista( pVisivel->pLista ) ;
         retornoObter = LIS_AvancarElementoCorrente( 
                           pVisivel->pLista , -posicao ) ;
         if ( retornoObter == LIS_CondRetOK )
         {
            return ( CAR_tppCarta ) LIS_ObterValor( pVisivel->pLista ) ;
         } /* if */
        
         return NULL ;

   } /* Fim função: VIS  Obter Carta Posição */

/***********************************************************************
*
*  Função: VIS  &Transformar uma sequência visível em uma string
*  ****/

   VIS_tpCondRet VIS_ConverterParaString( VIS_tppVisivel pVisivel , 
                                          char * visivelString     ) 
   {

      int i ;

      char cartaString[ CAR_DIM_STRING ] = "\0" ;

      CAR_tppCarta pCarta ;

      LIS_tpCondRet retornoAvancar = LIS_CondRetOK ;

      #ifdef _DEBUG
         if( pVisivel == NULL || visivelString == NULL )
         {
            return VIS_CondRetErroParm ;
         } /* if */
      #endif  

      visivelString[ 0 ] = '\0';

      IrInicioLista( pVisivel->pLista ) ;
      pCarta = ( CAR_tppCarta ) LIS_ObterValor( pVisivel->pLista ) ;
      for( i = 1 ; i <= VIS_MAX_DIM_CARTAS && retornoAvancar == 
                      LIS_CondRetOK ; i++ )
         {
            if( i > 1 )
            {
               strcat( visivelString , " " ) ;
            } /* if */

            pCarta = ( CAR_tppCarta ) LIS_ObterValor( 
                                         pVisivel->pLista ) ;
            if( pCarta != NULL )
            {
               CAR_ConverterParaString( pCarta , cartaString ) ;
               strcat( visivelString , cartaString ) ;
            }
    
            retornoAvancar = LIS_AvancarElementoCorrente( 
                                 pVisivel->pLista , 1 ) ; 
         } /* for */
      IrInicioLista( pVisivel->pLista ) ;

      return VIS_CondRetOK ;
         
   } /* Fim função: VIS  &Transformar uma sequência visível em uma string */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: VIS  -Inserir Carta Sem Ordem
*
*  $ED Descrição da função
*     Insere uma instância de carta no final de uma instância de lista
*        visivel. A carta não precisa obedecer nenhum requisito.
*
*  $EP Parâmetros
*     pVisivel - ponteiro para uma lista visivel
*     pCarta    - ponteiro para a carta que se está tentando inserir
*
*  $FV Valor retornado
*     VIS_CondRetOK            - inserção OK
*     VIS_CondRetFaltouMemoria - memória insuficiente
*
*  $AE Assertivas de Entrada:
*     pVisivel != NULL
*     pCarta   != NULL
*
*  $AS Assertivas de Saída:
*     Se a função retorna CondRetOK, a carta em questão foi inserida com
*        sucesso no topo da visível. pvisível aponta para a nova carta inserida.
*     Caso contrário, se a função retorna ORD_CondRetErroParm ou
*        ORD_CondRetFaltouMemoria, nada foi modificado.
*
***********************************************************************/

   VIS_tpCondRet VIS_InserirCartaSemOrdem( VIS_tppVisivel pVisivel , 
                                           CAR_tppCarta pCarta      ) 
   {
      
      LIS_tpCondRet retornoInsercao = LIS_CondRetFaltouMemoria ;

      IrFinalLista( pVisivel->pLista ) ;
      retornoInsercao = LIS_InserirElementoApos( 
                           pVisivel->pLista , pCarta ) ;      
      if( retornoInsercao == LIS_CondRetFaltouMemoria )
      {
         return VIS_CondRetFaltouMemoria ;
      } /* if */

      return VIS_CondRetOK ;

   } /* Fim função: VIS  -Inserir Carta Sem Ordem */

/***********************************************************************
*
*  $FC Função: VIS  -Inserir Carta Com Ordem
*
*  $ED Descrição da função
*     Insere uma instância de carta no final de uma instância de lista
*      visivel. A carta precisa ser de cor diferente e de rank uma
*      unidade maior que a carta presente no final da lista visível.
*
*  $EP Parâmetros
*     pVisivel - ponteiro para uma lista visivel
*     pCarta    - ponteiro para a carta que se está tentando inserir
*
*  $FV Valor retornado
*     VIS_CondRetOK            - inserção OK
*     VIS_CondRetCartaInvalida - A carta em questão não pode ser inserida
*                                nessa lista/posição
*     VIS_CondRetFaltouMemoria - memória insuficiente
*
*  $AE Assertivas de Entrada:
*     pVisivel != NULL
*     pCarta   != NULL
*
*  $AS Assertivas de Saída:
*     Se a função retorna CondRetOK, a carta em questão foi inserida com
*        sucesso no topo da visível. pvisível aponta para a nova carta inserida.
*     Caso contrário, se a função retorna ORD_CondRetErroParm ou
*        ORD_CondRetFaltouMemoria, nada foi modificado.
*
*
***********************************************************************/

   VIS_tpCondRet VIS_InserirCartaComOrdem( VIS_tppVisivel pVisivel , 
                                           CAR_tppCarta pCarta      ) 
   {
      
      CAR_tppCarta pCartaFinal = NULL ;

      #ifdef _DEBUG
         if( pVisivel == NULL || pCarta == NULL )
         {
            return VIS_CondRetErroParm ;
         } /* if */
      #endif 

      IrFinalLista( pVisivel->pLista ) ;

      /* Trata o caso da lista estar vazia; simplesmente insere a carta */

         if ( LIS_AvancarElementoCorrente( pVisivel->pLista , 0 )
                 == LIS_CondRetListaVazia )
         {
            return VIS_InserirCartaSemOrdem( pVisivel , pCarta );
         }

      /* Trata o caso da lista não vazia; a carta a ser inserida deve ter
         cor diferente do que a última da lista e seu rank deve anteceder
         o da última carta da lista */

         else 
         {
            pCartaFinal = (CAR_tppCarta) LIS_ObterValor( pVisivel->pLista ) ;
            if( pCartaFinal == NULL )
            {
               return VIS_CondRetNaoOK ;
            } /* if */

            if( CAR_CompararCor( pCarta , pCartaFinal ) 
                   == CAR_CondRetDiferente
                && CAR_CompararRank( pCarta , pCartaFinal )  
                   == CAR_CondRetAntecessor )
            {
               return VIS_InserirCartaSemOrdem( pVisivel , pCarta ) ;
            }
         } /* if */

      /* A carta passada não pode ser inserida */

         return VIS_CondRetCartaInvalida ;

   } /* Fim função: VIS  -Inserir Carta Com Ordem */


 /*** Fim do módulo de implementação: VIS  Sequência Visível *****/