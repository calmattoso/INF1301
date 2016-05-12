/***************************************************************************
*  $MCI Módulo de implementação: TCAR Teste carta de um baralho
*
*  Arquivo gerado:              TESTCAR.c
*  Letras identificadoras:      TCAR
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
*     1       clm   11/out/2013 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "CARTA.h"

static const char RESET_CARTA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_CARTA_CMD         [ ] = "=criarcarta"     ;
static const char DESTRUIR_CARTA_CMD      [ ] = "=destruircarta"  ;
static const char OBTER_NAIPE_CMD         [ ] = "=obternaipe"     ;
static const char COMPARAR_NAIPE_CMD      [ ] = "=compararnaipe"  ;
static const char COMPARAR_RANK_CMD       [ ] = "=compararrank"   ;
static const char COMPARAR_COR_CMD        [ ] = "=compararcor"    ;
static const char PARA_STRING_CMD         [ ] = "=parastring"     ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_CARTA   10
#define DIM_STR_CARTA  CAR_DIM_STRING

CAR_tppCarta   vtCartas[ DIM_VT_CARTA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarInxCarta( int inxCarta , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TCAR &Testar carta de um baralho
*
*  $ED Descrição da função
*     Podem ser criadas até 10 cartas, identificadas pelos índices 0 a 9
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de cartas. Provoca vazamento de memória
*     =criarcarta                   inxCarta  Naipe  Rank
*     =destruircarta                inxCarta
*     =obternaipe                   inxCarta  NaipeEsp
*     =compararnaipe                inxCarta  inxCarta2  CondRetEsp
*     =compararrank                 inxCarta  inxCarta2  CondRetEsp
*     =compararcor                  inxCarta  inxCarta2  CondRetEsp
*     =parastring                   inxCarta  string  CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxCarta   = -1 ,
          inxCarta2  = -1 ,
          numLidos   = -1 ,
          condRetEsp = -1  ;
      int i ;

      char   stringDado[ DIM_STR_CARTA ] ;
      char   stringCarta[ DIM_STR_CARTA ] ;

      CAR_tpNaipe naipe ;

      CAR_tpRank rank ;

      CAR_tpCondRet carCondRet ;


      stringDado[ 0 ] = '\0' ;

      /* Efetuar reset de teste de carta */

         if ( strcmp( ComandoTeste , RESET_CARTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_CARTA ; i++ )
            {
               vtCartas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de carta */

      /* Testar criar carta */

         else if ( strcmp( ComandoTeste , CRIAR_CARTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxCarta, &naipe, &rank ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxCarta( inxCarta , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtCartas[ inxCarta ] = CAR_CriarCarta( naipe , rank ) ;

            return TST_CompararPonteiroNulo( 1 , vtCartas[ inxCarta ] ,
                      "Erro em ponteiro de nova carta."  ) ;

         } /* fim ativa: Testar criar carta */

      /* Testar destruir carta */

         else if ( strcmp( ComandoTeste , DESTRUIR_CARTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                          &inxCarta ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxCarta( inxCarta , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CAR_DestruirCarta( vtCartas[ inxCarta ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar destruir carta */

      /* Testar obter naipe de carta */

         else if ( strcmp( ComandoTeste , OBTER_NAIPE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                          &inxCarta , &naipe ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxCarta( inxCarta , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            return TST_CompararInt( naipe , 
                      CAR_ObterNaipe( vtCartas[ inxCarta ] ) ,
                      "Naipe diferente do esperado." ) ;

         } /* fim ativa: Testar obter naipe de carta */

      /* Testar comparar naipes de duas cartas */

         else if ( strcmp( ComandoTeste , COMPARAR_NAIPE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxCarta , &inxCarta2 , &condRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxCarta( inxCarta , NAO_VAZIO )) 
              || ( ! ValidarInxCarta( inxCarta2 , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            carCondRet = CAR_CompararNaipe( vtCartas[ inxCarta ] ,
                              vtCartas[ inxCarta2 ] ) ;

            return TST_CompararInt( condRetEsp , carCondRet ,
                     "Condicao de retorno errada ao comparar naipes." ) ;

         } /* fim ativa: Testar comparar naipes de duas cartas */

      /* Testar comparar ranks de duas cartas */

         else if ( strcmp( ComandoTeste , COMPARAR_RANK_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxCarta , &inxCarta2 , &condRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxCarta( inxCarta , NAO_VAZIO )) 
              || ( ! ValidarInxCarta( inxCarta2 , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            carCondRet = CAR_CompararRank( vtCartas[ inxCarta ] ,
                              vtCartas[ inxCarta2 ] ) ;

            return TST_CompararInt( condRetEsp , carCondRet ,
                     "Condicao de retorno errada ao comparar ranks." ) ;

         } /* fim ativa: Testar comparar ranks de duas cartas */

      /* Testar comparar cores de duas cartas */

         else if ( strcmp( ComandoTeste , COMPARAR_COR_CMD ) == 0 )
         {

           numLidos = LER_LerParametros( "iii" ,
                       &inxCarta , &inxCarta2 , &condRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxCarta( inxCarta , NAO_VAZIO )) 
              || ( ! ValidarInxCarta( inxCarta2 , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            carCondRet = CAR_CompararCor( vtCartas[ inxCarta ] ,
                              vtCartas[ inxCarta2 ] ) ;

            return TST_CompararInt( condRetEsp , carCondRet ,
                     "Condicao de retorno errada ao comparar ranks." ) ;

         } /* fim ativa: Testar comparar cores de duas cartas */

      /* Testar conversão para string */

         else if ( strcmp( ComandoTeste , PARA_STRING_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" , 
                          &inxCarta , stringDado , &condRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxCarta( inxCarta , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            carCondRet = CAR_ConverterParaString( vtCartas[ inxCarta ] , 
                            stringCarta ) ;
            if( condRetEsp != carCondRet )
            {
               return TST_CompararInt( condRetEsp , carCondRet ,
                         "Erro ao gerar string da carta." ) ;
            } /* if */

            return TST_CompararString( stringDado , stringCarta , 
                      "Erro: string gerada diferente da esperada." ) ;

         } /* fim ativa: Testar conversão para string */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TCAR &Testar carta de um baralho */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TCAR -Validar indice do vetor de cartas
*
***********************************************************************/

   int ValidarInxCarta( int inxCarta , int Modo )
   {

      if ( ( inxCarta <  0 )
        || ( inxCarta >= DIM_VT_CARTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtCartas[ inxCarta ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtCartas[ inxCarta ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TCAR -Validar indice do vetor de cartas */

/********** Fim do módulo de implementação: TCAR Teste carta de um baralho **********/

