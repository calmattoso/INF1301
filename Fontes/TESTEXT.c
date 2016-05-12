/***************************************************************************
*  $MCI Módulo de implementação: TEXT Teste espaços extras
*
*  Arquivo gerado:              TESTEXT.c
*  Letras identificadoras:      TEXT
*
*  Nome da base de software:    Trabalho 2 de Programação Modular
*  Arquivo da base de software: C:\Users\Carlos\Skydrive\PUC\INF1301
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: clm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       clm   12/out/2013 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "CARTA.h"
#include    "EXTRAS.h"
#include    "LISTA.h"


static const char RESET_EXTRAS_CMD        [ ] = "=resetteste"     ;
static const char CRIAR_EXTRAS_CMD        [ ] = "=criarextras"    ;
static const char DESTRUIR_EXTRAS_CMD     [ ] = "=destruirextras" ;
static const char OBTER_NUM_OCUP_CMD      [ ] = "=obternumocup"   ;
static const char INSERIR_CARTA_POS_CMD   [ ] = "=insercartapos"  ;
static const char REMOVER_CARTA_POS_CMD   [ ] = "=removcartapos"  ;
static const char OBTER_CARTA_POS_CMD     [ ] = "=obtercartapos"  ;
static const char OBTER_VAZIA_POS_CMD     [ ] = "=obtervaziapos"  ;
static const char PARA_STRING_CMD         [ ] = "=parastring"     ;
static const char TERMINA_CMD             [ ] = "=termina"        ;



#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_EXTRAS   10
#define DIM_STR_EXTRAS  EXT_DIM_STRING

EXT_tppExtras   vtExtras[ DIM_VT_EXTRAS ] ;

LIS_tppLista    cartas ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarInxExtras( int inxExtras , int Modo ) ;
   static void DestruirCarta( void * pCarta ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TEXT &Testar espaços extras
*
*  $ED Descrição da função
*     Podem ser criadas até 10 estruturas de espaços extras, 
*        identificadas pelos índices 0 a 9.
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de extras. Provoca vazamento de memória
*     =criarextras                  inxExtras  
*     =destruirextras               inxExtras 
*     =obternumocup                 inxExtras  numOcupEsp
*     =insercartapos                inxExtras  inxCarta naipe  rank  CondRetEsp
*     =removcartapos                inxExtras  inxCarta  CondRetEsp
*     =obtercartapos                inxExtras  inxCarta  naipeEsp rankEsp
*     =obtervaziapos                inxExtras  inxCarta
*     =parastring                   inxExtras  stringEsp  CondRetEsp
*     =termina
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxExtras   = -1 ,
          inxCarta    = -1 ,
          numLidos    = -1 ,
          condRetEsp  = -1 ,
          numOcupEsp  = -1  ;
      int i ;

      char   stringDado[ DIM_STR_EXTRAS ] ;
      char   stringExtras[ DIM_STR_EXTRAS ] ;

      CAR_tppCarta pCarta ;
      CAR_tppCarta pCartaRet ;

      CAR_tpNaipe naipe ;

      CAR_tpRank rank ;

      CAR_tpCondRet carCondRet ;

      EXT_tpCondRet extCondRet ;

      LIS_tpCondRet lisCondRet ;


      stringDado[ 0 ] = '\0' ;

      /* Efetuar reset de teste de extras */

         if ( strcmp( ComandoTeste , RESET_EXTRAS_CMD ) == 0 )
         {

            cartas = LIS_CriarLista( DestruirCarta ) ;
            if( cartas == NULL )
            {
              return TST_CompararPonteiroNulo( 1 , cartas , 
                        "Erro ao gerar lista de ponteiros para cartas.");
            } /* if */

            for( i = 0 ; i < DIM_VT_EXTRAS ; i++ )
            {
               vtExtras[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de extras */

      /* Testar criar extras */

         else if ( strcmp( ComandoTeste , CRIAR_EXTRAS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxExtras ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxExtras( inxExtras , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtExtras[ inxExtras ] = EXT_CriarExtras( ) ;

            return TST_CompararPonteiroNulo( 1 , vtExtras[ inxExtras ] ,
               "Erro em ponteiro para nova estrutura de extras."  ) ;

         } /* fim ativa: Testar criar extras */

      /* Testar destruir estrutura de extras */

         else if ( strcmp( ComandoTeste , DESTRUIR_EXTRAS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxExtras ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxExtras( inxExtras , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            EXT_DestruirExtras( vtExtras[ inxExtras ] ) ;
            vtExtras[ inxExtras ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar destruir estrutura de extras */

      /* Testar obter número de espaços extras ocupados  */

         else if ( strcmp( ComandoTeste , OBTER_NUM_OCUP_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                          &inxExtras , &numOcupEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxExtras( inxExtras , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            return TST_CompararInt( numOcupEsp , 
                      EXT_ObterNumeroEspacosOcupados( 
                         vtExtras[ inxExtras ] ) ,
                      "Erro no numero de extras ocupados." ) ;

         } /* fim ativa: Testar obter número de espaços extras ocupados */

      /* Testar inserir carta em certa posição */

         else if ( strcmp( ComandoTeste , INSERIR_CARTA_POS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iiiii" ,
                          &inxExtras , &inxCarta , &naipe , &rank , 
                          &condRetEsp ) ;

            if ( ( numLidos != 5 )
              || ( ! ValidarInxExtras( inxExtras , NAO_VAZIO ))) 
            {
               return TST_CondRetParm ;
            } /* if */

            pCarta = CAR_CriarCarta( naipe , rank ) ;
            if( pCarta == NULL )
            {
              return TST_CompararPonteiroNulo( 1 , pCarta ,
                        "Erro em ponteiro para nova carta." ) ;
            } /* if */

            lisCondRet = LIS_InserirElementoApos( cartas , 
                            ( void * ) pCarta ) ;
            if( LIS_CondRetOK  != lisCondRet )
            {
               return TST_CompararInt( LIS_CondRetOK , lisCondRet ,
                         "Erro ao criar referencia para carta.") ;
            } /* if */

            extCondRet = EXT_InserirCartaPosicao( vtExtras[ inxExtras ] ,
                            pCarta , inxCarta ) ;

            return TST_CompararInt( condRetEsp , extCondRet ,
                     "Condicao de retorno errada ao inserir carta." ) ;

         } /* fim ativa: Testar inserir carta em certa posição */

      /* Testar remover carta em certa posição */

         else if ( strcmp( ComandoTeste , REMOVER_CARTA_POS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxExtras , &inxCarta , &condRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxExtras( inxExtras , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            extCondRet = EXT_RemoverCartaPosicao( vtExtras[ inxExtras ] ,
                            inxCarta ) ;
              
            return TST_CompararInt( condRetEsp , extCondRet ,
                     "Condicao de retorno errada ao remover carta." ) ;

         } /* fim ativa: Testar remover carta em certa posição */

      /* Testar obter carta em certa posição */

         else if ( strcmp( ComandoTeste , OBTER_CARTA_POS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iiii" ,
                       &inxExtras , &inxCarta , &naipe , &rank ) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxExtras( inxExtras , NAO_VAZIO )) )
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

               pCartaRet = EXT_ObterCartaPosicao( vtExtras[ inxExtras ] ,
                              inxCarta ) ;
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

         } /* fim ativa: Testar obter carta em certa posição */

      /* Testar posição vazia */

         else if ( strcmp( ComandoTeste , OBTER_VAZIA_POS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                          &inxExtras , &inxCarta ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxExtras( inxExtras , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            /* Checa se o espaço está vazio */

               pCartaRet = EXT_ObterCartaPosicao( vtExtras[ inxExtras ] ,
                              inxCarta ) ;
               
               return TST_CompararPonteiroNulo( 0 , pCartaRet ,
                            "Erro em posicao vazia." ) ;

         } /* fim ativa: Testar posição vazia */

      /* Testar conversão para string */

         else if ( strcmp( ComandoTeste , PARA_STRING_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" , 
                          &inxExtras , stringDado , &condRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxExtras( inxExtras , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            extCondRet = EXT_ConverterParaString( vtExtras[ inxExtras ] , 
                            stringExtras ) ;
  
            if( condRetEsp != extCondRet )
            {
               return TST_CompararInt( condRetEsp , extCondRet ,
                         "Erro ao gerar string dos espacos extras." ) ;
            } /* if */

            return TST_CompararString( stringDado , stringExtras , 
                      "Erro: string gerada diferente da esperada." ) ;

         } /* fim ativa: Testar conversão para string */

      /* Finalizar ambiente de testes */

         else if ( strcmp( ComandoTeste , TERMINA_CMD ) == 0 )
         {

            LIS_DestruirLista( cartas ) ;

            for( i = 0 ; i < DIM_VT_EXTRAS ; i++ )
            {
               if( ValidarInxExtras( i , NAO_VAZIO ))
               {
                  EXT_DestruirExtras( vtExtras[ i ] ) ;
                  vtExtras[ i ] = NULL ;
               } /* if */
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Finalizar ambiente de testes */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TEXT &Testar espaços extras */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TEXT -Validar indice do vetor de espaços extras
*
***********************************************************************/

   int ValidarInxExtras( int inxExtras , int Modo )
   {

      if ( ( inxExtras <  0 )
        || ( inxExtras >= DIM_VT_EXTRAS ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtExtras[ inxExtras ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtExtras[ inxExtras ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TEXT -Validar indice do vetor de espaços extras */

/***********************************************************************
*
*  $FC Função: TEXT -Destruir carta
*
***********************************************************************/

   void DestruirCarta( void * pCarta )
   {

      CAR_DestruirCarta( ( CAR_tppCarta ) pCarta ) ;

   } /* Fim função: TEXT -Destruir carta */

/********** Fim do módulo de implementação: TEXT Teste espaços extras **********/

