/***************************************************************************
*  $MCI Módulo de implementação: TVIS Teste sequência visível
*
*  Arquivo gerado:              TESTVIS.C
*  Letras identificadoras:      TVIS
*
*  Nome da base de software:    Trabalho 2 de Programação Modular
*  Arquivo da base de software: VISIVEL/TESTVIS.C
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gss
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       gss   13/out/2013 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "CARTA.h"
#include    "LISTA.h"
#include    "VISIVEL.h"

static const char RESET_VISIVEL_CMD          [ ] = "=resetteste"      ;
static const char CRIAR_VISIVEL_CMD          [ ] = "=criarvisivel"    ;
static const char DESTRUIR_VISIVEL_CMD       [ ] = "=destruirvisivel" ;
static const char INSERIR_CARTA_CMD          [ ] = "=inserircarta"    ;
static const char REMOVER_CARTA_CMD          [ ] = "=removercarta"    ;
static const char OBTER_CARTA_POS_CMD        [ ] = "=obtercartapos"   ;
static const char OBTER_CARTA_POS_VAZIA_CMD  [ ] = "=obtervaziopos"   ;
static const char PARA_STRING_CMD            [ ] = "=parastring"      ;
static const char TERMINA_CMD                [ ] = "=termina"      ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_VISIVEL   15
#define DIM_STR_VISIVEL  VIS_DIM_STRING

VIS_tppVisivel vtVisivel[ DIM_VT_VISIVEL ] ;

LIS_tppLista cartas ;

/***** Protótipos das funções encapuladas no módulo *****/

    static int ValidarInxVisivel( int inxVisivel , int Modo ) ;

    static void DestruirCarta( void * pCarta ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TVIS &Testar Visiveis
*
*  $ED Descrição da função
*     Podem ser criadas até 10 sequências visiveis, identificadas 
*        pelos índices 0 a 9
*
*  Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de cartas. Provoca vazamento de memória
*     =criarvisivel                 inxVisivel
*     =destruirvisivel              inxVisivel
*     =inserircarta                 inxVisivel  naipe  rank  condRetEsp   modo
*     =removercarta                 inxVisivel  CondRetEsp       
*     =obtercartapos                inxVisivel  inxCarta  naipeEsp  rankEsp
*     =obtervaziopos                inxVisivel  inxCarta
*     =parastring                   inxVisivel  string  CondRetEsp
*     =termina
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxVisivel  = -1 ,
          inxCarta    = -1 ,
          numLidos    = -1 ,
          condRetEsp  = -1 ,
          modo        = -1  ;             
      int i ;

      char stringDado[ DIM_STR_VISIVEL ] ;
      char stringVisivel[ DIM_STR_VISIVEL ] ;

      CAR_tppCarta pCarta ;
      CAR_tppCarta pCartaRet ;

      CAR_tpCondRet carCondRet ;

      CAR_tpNaipe naipe ;
      
      CAR_tpRank rank ;

      VIS_tpCondRet visCondRet ;

      LIS_tpCondRet lisCondRet ;

      stringDado[ 0 ] = '\0' ;

      /* Efetuar reset de teste de visivel */

         if ( strcmp( ComandoTeste , RESET_VISIVEL_CMD ) == 0 )
         {

            cartas = LIS_CriarLista( DestruirCarta ) ;
            if( cartas == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , cartas , 
                         "Erro ao gerar lista de ponteiros para cartas." );
            } /* if */

            for( i = 0 ; i < DIM_VT_VISIVEL ; i++ )
            {
               vtVisivel[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de visível */

      /* Testar criar visivel*/

         else if ( strcmp( ComandoTeste , CRIAR_VISIVEL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxVisivel ) ;

            if ( ( numLidos != 1 )
                || ( ! ValidarInxVisivel( inxVisivel , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtVisivel[ inxVisivel ] = VIS_CriarVisivel( ) ;

            return TST_CompararPonteiroNulo( 1 , vtVisivel[ inxVisivel ] ,
                      "Erro em ponteiro para nova estrutura de visiveis."  ) ;

         } /* fim ativa: Testar criar visivel */

      /* Testar destruir visivel */

         else if ( strcmp( ComandoTeste , DESTRUIR_VISIVEL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxVisivel ) ;

            if ( ( numLidos != 1 )
                  || ( ! ValidarInxVisivel( inxVisivel , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            VIS_DestruirVisivel( vtVisivel[ inxVisivel ] ) ;
            vtVisivel[ inxVisivel ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar destruir visivel */

      /* Testar obter carta em certa posição */

         else if ( strcmp( ComandoTeste , OBTER_CARTA_POS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iiii" ,
                       &inxVisivel , &inxCarta , &naipe , &rank ) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxVisivel( inxVisivel , NAO_VAZIO )) )
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

               pCartaRet = VIS_ObterCartaPosicao( vtVisivel[ inxVisivel ] ,
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

      /* Testar obter carta em posição vazia */

         else if ( strcmp( ComandoTeste , OBTER_CARTA_POS_VAZIA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                       &inxVisivel , &inxCarta ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxVisivel( inxVisivel , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

           
            /* Checa se não havia carta */   

               pCartaRet = VIS_ObterCartaPosicao( vtVisivel[ inxVisivel ] ,
                              inxCarta ) ;
               return TST_CompararPonteiroNulo( 0 , pCartaRet ,
                            "Erro ao obter carta." ) ;

         } /* fim ativa: Testar obter carta em posição vazia */           

      /* Testar remover carta */

         else if ( strcmp( ComandoTeste , REMOVER_CARTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                       &inxVisivel , &condRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxVisivel( inxVisivel , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            visCondRet = VIS_RemoverCarta( vtVisivel[ inxVisivel ] ) ;
              
            return TST_CompararInt( condRetEsp , visCondRet ,
                     "Condicao de retorno errada ao remover carta." ) ;

         } /* fim ativa: Testar remover carta */

      /* Testar inserir carta em visivel */

         else if ( strcmp( ComandoTeste , INSERIR_CARTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iiiii" ,
                          &inxVisivel , &naipe , &rank, &condRetEsp, &modo ) ;

            if ( ( numLidos != 5 )
                  || ( ! ValidarInxVisivel( inxVisivel , NAO_VAZIO ))) 
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
            if( LIS_CondRetOK  != lisCondRet )
            {
               return TST_CompararInt( LIS_CondRetOK , lisCondRet ,
                         "Erro ao criar referencia para carta.") ;
            } /* if */

            visCondRet = VIS_InserirCarta( vtVisivel[ inxVisivel ] ,
                            pCarta, ( VIS_tpModo ) modo ) ;

            return TST_CompararInt( condRetEsp , visCondRet ,
                      "Condicao de retorno errada ao comparar naipes." ) ;

         } /* fim ativa: Testar inserir carta em visivel */
       
      /* Testar conversão para string */

         else if ( strcmp( ComandoTeste , PARA_STRING_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" , 
                          &inxVisivel , stringDado, &condRetEsp ) ;

            if ( ( numLidos != 3 )
                  || ( ! ValidarInxVisivel( inxVisivel , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            visCondRet = VIS_ConverterParaString( vtVisivel[ inxVisivel ] , 
                            stringVisivel ) ;
                  
            if( visCondRet != condRetEsp )
            {
               return TST_CompararInt( condRetEsp , visCondRet ,
                         "Erro ao gerar string das visiveis." ) ;
            } /* if */

            return TST_CompararString( stringDado , stringVisivel ,
                      "Erro ao gerar string das visiveis." ) ;

         } /* fim ativa: Testar conversão para string */

      /* Finalizar ambiente de testes */

         if ( strcmp( ComandoTeste , TERMINA_CMD ) == 0 )
         {

            LIS_DestruirLista( cartas ) ;

            for( i = 0 ; i < DIM_VT_VISIVEL ; i++ )
            {
               if( ValidarInxVisivel( i , NAO_VAZIO ))
               {
                  VIS_DestruirVisivel( vtVisivel[i] ) ;
                  vtVisivel[ i ] = NULL ;
               } /* if */
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Finalizar ambiente de testes */

         return TST_CondRetNaoConhec ;

    } /* Fim função: TCAR &Testar carta de um baralho */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TVIS -Validar indice do vetor de visiveis
*
***********************************************************************/

   int ValidarInxVisivel( int inxVisivel , int Modo )
   {

      if ( ( inxVisivel <  0 )
          || ( inxVisivel >= DIM_VT_VISIVEL ))
      {
         return FALSE ;
      } /* if */
             
      if ( Modo == VAZIO )
      {
         if ( vtVisivel[ inxVisivel ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtVisivel[ inxVisivel ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
             
      return TRUE ;

   } /* Fim função: TVIS -Validar indice do vetor de visiveis */

/***********************************************************************
*
*  $FC Função: TVIS -Destruir carta
*
***********************************************************************/

    void DestruirCarta( void * pCarta )
    {

      CAR_DestruirCarta( ( CAR_tppCarta ) pCarta ) ;

    } /* Fim função: TVIS -Destruir carta */

/********** Fim do módulo de implementação: TVIS Teste sequência visível **********/
