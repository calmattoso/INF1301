/***************************************************************************
*  $MCI M�dulo de implementa��o: TORD Teste sequ�ncia ordenada
*
*  Arquivo gerado:              TESTORD.c
*  Letras identificadoras:      TORD
*
*  Nome da base de software:    Trabalho 2 de Programa��o Modular
*  Arquivo da base de software: ORDENADA/TESTORD.C
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: ffa
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       ffa   13/out/2013 in�cio desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"

#include    "ORDENADA.h"


static const char RESET_ORDENADA_CMD         [ ] = "=resetteste"       ;
static const char CRIAR_ORDENADA_CMD         [ ] = "=criarordenada"    ;
static const char DESTRUIR_ORDENADA_CMD      [ ] = "=destruirordenada" ;
static const char INSERIR_CARTA_CMD          [ ] = "=inserircarta"     ;
static const char OBTER_TOPO_CMD			       [ ] = "=obtertopo"	       ;
static const char OBTER_VAZIO_CMD            [ ] = "=obtertpvazio"     ;
static const char PARA_STRING_CMD            [ ] = "=parastring"       ;
static const char TERMINA_CMD                [ ] = "=termina"          ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_ORDENADA   10
#define DIM_STR_ORDENADA  ORD_DIM_STRING

ORD_tppOrdenada vtOrdenada[ DIM_VT_ORDENADA ] ;

LIS_tppLista cartas ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static int ValidarInxOrdenada( int inxOrdenada , int Modo ) ;

   static void DestruirCarta( void * pCarta ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TORD &Testar Ordenadas
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 sequ�ncias de ordenadas, identificadas 
*        pelos �ndices 0 a 9
*
*  Comandos dispon�veis:
*
*     =resetteste
*           - anula o vetor de ordenadas. Provoca vazamento de mem�ria
*     =criarordenada                inxOrdenada
*     =destruirordenada             inxOrdenada        
*     =inserircarta                 inxOrdenada  naipe  rank  CondRetEsp
*     =obtertopo                    inxOrdenada  naipeEsp  rankEsp
*     =obtertpvazio                 inxOrdenada
*     =parastring                   inxOrdenada  string  CondRetEsp
*     =termina
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxOrdenada   = -1 ,
          numLidos      = -1 ,
          condRetEsp    = -1 ;             
      int i ;

      char   stringDado[ DIM_STR_ORDENADA ] ;
      char   stringOrdenada[ DIM_STR_ORDENADA ] ;

      CAR_tpCondRet carCondRet ;

      CAR_tppCarta pCarta ;
	   CAR_tppCarta pCartaRet;

      CAR_tpNaipe naipe ;
      
      CAR_tpRank rank ;

      ORD_tpCondRet ordCondRet ;

      LIS_tpCondRet lisCondRet ;

      stringDado[ 0 ] = '\0' ;

      /* Efetuar reset de teste de ordenada */

         if ( strcmp( ComandoTeste , RESET_ORDENADA_CMD ) == 0 )
         {

            cartas = LIS_CriarLista( DestruirCarta ) ;
            if( cartas == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , cartas , 
                         "Erro ao gerar lista de ponteiros para cartas.");
            } /* if */
               
            for( i = 0 ; i < DIM_VT_ORDENADA ; i++ )
            {
               vtOrdenada[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de carta */

      /* Testar criar ordenada*/

         else if ( strcmp( ComandoTeste , CRIAR_ORDENADA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                          &inxOrdenada ) ;

            if ( ( numLidos != 1 )
                   || ( ! ValidarInxOrdenada( inxOrdenada , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtOrdenada[ inxOrdenada ] = ORD_CriarOrdenada( ) ;

            return TST_CompararPonteiroNulo( 1 , vtOrdenada[ inxOrdenada ] ,
                      "Erro em ponteiro para nova estrutura de ordenadas."  ) ;

         } /* fim ativa: Testar criar ordenada */

      /* Testar destruir ordenada */

         else if ( strcmp( ComandoTeste , DESTRUIR_ORDENADA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                          &inxOrdenada ) ;

            if ( ( numLidos != 1 )
                  || ( ! ValidarInxOrdenada( inxOrdenada , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            ORD_DestruirOrdenada( vtOrdenada[ inxOrdenada ] ) ;
            vtOrdenada[ inxOrdenada ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar destruir ordenada */

      /* Testar inserir carta em ordenada */

         else if ( strcmp( ComandoTeste , INSERIR_CARTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iiii" ,
                          &inxOrdenada , &naipe , &rank, &condRetEsp ) ;
            if ( ( numLidos != 4 )
                  || ( ! ValidarInxOrdenada( inxOrdenada , NAO_VAZIO ))) 
            {
               return TST_CondRetParm ;
            } /* if */

            pCarta = CAR_CriarCarta( naipe , rank ) ;           
            if( pCarta == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pCarta ,
                         "Erro em ponteiro para nova carta." ) ; ;
            } /* if */

            lisCondRet = LIS_InserirElementoApos( cartas , 
                            ( void * ) pCarta ) ;
            if( LIS_CondRetOK != lisCondRet )
            {
               return TST_CompararInt( LIS_CondRetOK , lisCondRet , 
                         "Erro ao criar referencia para carta.") ;
            } /* if */

            ordCondRet = ORD_InserirCarta( vtOrdenada[ inxOrdenada ] ,
                            pCarta ) ;

            return TST_CompararInt( condRetEsp , ordCondRet ,
                      "Condicao de retorno errada inserir carta." ) ;

         } /* fim ativa: Testar inserir carta em ordenada */

	   /* Testar obter topo de uma ordenada */
	   
         else if ( strcmp( ComandoTeste , OBTER_TOPO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxOrdenada ,
                          &naipe , &rank ) ;

            if ( ( numLidos != 3 )
                  || ( ! ValidarInxOrdenada( inxOrdenada , NAO_VAZIO ))) 
            {
               return TST_CondRetParm ;
            } /* if */

			   /* Cria uma carta auxiliar para comparar com a obtida */

		         pCarta = CAR_CriarCarta( naipe , rank ) ; 
               if( pCarta == NULL )
               {
                  return TST_CompararPonteiroNulo( 1 , pCarta , 
                            "Erro ao criar carta auxiliar." ) ;
               } /* if */

			   /* Checa se conseguiu obter a carta */

               pCartaRet = ORD_ObterTopo( vtOrdenada[ inxOrdenada ] ) ;
               if( pCartaRet == NULL )
               {
                  return TST_CompararPonteiroNulo( 1 , pCartaRet ,
                            "Erro ao obter carta." ) ;
               } /* if */

			   /* Checa se o naipe bate */

               carCondRet = CAR_CompararNaipe( pCarta , pCartaRet ) ;
               if( CAR_CondRetIgual != carCondRet )
               {
                  return TST_CompararInt( CAR_CondRetIgual , 
                            carCondRet , "Erro no naipe." ) ;
               } /* if */

            /* Checa se o rank bate */

               carCondRet = CAR_CompararRank( pCarta , pCartaRet ) ;
               if( CAR_CondRetIgual != carCondRet )
               {
                  return TST_CompararInt( CAR_CondRetIgual , 
                            carCondRet , "Erro no rank." ) ;
               } /* if */

               return TST_CondRetOK ;

         } /*fim ativa: Testar obter topo de uma ordenada */
      
      /* Testar obter topo vazio de uma ordenada */
      
         else if ( strcmp( ComandoTeste , OBTER_VAZIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxOrdenada ,
                          &naipe , &rank ) ;

            if ( ( numLidos != 1 )
                  || ( ! ValidarInxOrdenada( inxOrdenada , NAO_VAZIO ))) 
            {
               return TST_CondRetParm ;
            } /* if */

            /* Checa se topo est� vazio */

               pCartaRet = ORD_ObterTopo( vtOrdenada[ inxOrdenada ] ) ;
               return TST_CompararPonteiroNulo( 0 , pCartaRet ,
                         "Erro ao obter carta." ) ;

         } /* fim ativa: Testar obter topo vazio de uma ordenada */

      /* Testar convers�o para string */

         else if ( strcmp( ComandoTeste , PARA_STRING_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" , 
                          &inxOrdenada , stringDado, &condRetEsp ) ;

            if ( ( numLidos != 3 )
                  || ( ! ValidarInxOrdenada( inxOrdenada , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            ordCondRet = ORD_ConverterParaString( vtOrdenada[ inxOrdenada ] , 
                            stringOrdenada ) ;
                  
            if( ordCondRet != condRetEsp )
            {
               return TST_CompararInt( condRetEsp , ordCondRet ,
                         "Erro ao gerar string das ordenadas." ) ;
            } /* if */

            return TST_CompararString( stringDado , stringOrdenada ,
                      "Erro ao gerar string das ordenadas." ) ;

         } /* fim ativa: Testar convers�o para string */

      /* Finaliza o ambiente de testes */

         if ( strcmp( ComandoTeste , TERMINA_CMD ) == 0 )
         {

             

            for( i = 0 ; i < DIM_VT_ORDENADA ; i++ )
            {
               if( ValidarInxOrdenada( i , NAO_VAZIO ))
               {
                  ORD_DestruirOrdenada( vtOrdenada[ i ] );
                  vtOrdenada[ i ] = NULL ;
               } /* if */
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de carta */

         return TST_CondRetNaoConhec ;

    } /* Fim fun��o: TCAR &Sequ�ncia ordenada */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TORD -Validar indice do vetor de ordenadas
*
***********************************************************************/

   int ValidarInxOrdenada( int inxOrdenada , int Modo )
   {

      if ( ( inxOrdenada <  0 )
          || ( inxOrdenada >= DIM_VT_ORDENADA ))
      {
         return FALSE ;
      } /* if */
             
      if ( Modo == VAZIO )
      {
         if ( vtOrdenada[ inxOrdenada ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtOrdenada[ inxOrdenada ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
             
      return TRUE ;

   } /* Fim fun��o: TORD -Validar indice do vetor de ordenadas */

/***********************************************************************
*
*  $FC Fun��o: TORD -Destruir carta
*
***********************************************************************/

   void DestruirCarta( void * pCarta )
   {

      CAR_DestruirCarta( ( CAR_tppCarta ) pCarta ) ;

   } /* Fim fun��o: TORD -Destruir carta */

            

/********** Fim do m�dulo de implementa��o: TORD Teste sequ�ncia ordenada **********/

