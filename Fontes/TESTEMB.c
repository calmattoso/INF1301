/***************************************************************************
*  $MCI Módulo de implementação: TEMB Teste embaralhamento
*
*  Arquivo gerado:              TESTEMB.c
*  Letras identificadoras:      TEMB
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
*     1       clm   13/out/2013 início do desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"
#include    "Generico.h"
#include    "LerParm.h"

#include    "Carta.h"
#include    "Lista.h"

#include    "EMBARALHAMENTO.h"

static const char RESET_EMB_CMD           [ ] = "=resetteste"      ;
static const char CRIAR_BARALHO_CMD       [ ] = "=criarbaralho"    ;
static const char DESTRUIR_BARALHO_CMD    [ ] = "=destruirbaralho" ;
static const char EMBARALHAR_CMD          [ ] = "=embaralhar"      ;
static const char INSERIR_CARTA_CMD       [ ] = "=inserircarta"    ;
static const char COPIAR_BARALHO_CMD      [ ] = "=copiarbaralho"   ;
static const char CHECAR_IGUAL_CMD        [ ] = "=checarigual"     ;
static const char TERMINA_CMD             [ ] = "=termina"        ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_BARALHOS 10

LIS_tppLista vtBaralhos[ DIM_VT_BARALHOS ] ;
      /* Vetor dos baralhos */
LIS_tppLista cartas ;
      /* Referências para as cartas criadas */

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarInxBaralhos( int inxBaralho , int Modo ) ;


   static LIS_tpCondRet CopiarBaralho( LIS_tppLista baralhoDst ,
                                       LIS_tppLista baralhoOrg  ) ;

   static int ChecarIgual( LIS_tppLista baralhoA ,
                           LIS_tppLista baralhoB  ) ;
   
   static void DestruirCarta( void * pCarta ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TCAR &Testar baralho de um baralho
*
*  $ED Descrição da função
*     Podem ser criadas até 10 baralhos, identificadas pelos índices 0 a 9
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de baralhos. Provoca vazamento de memória
*     =embaralhar                   inxBaralho  CondRetEsp
*           - teste da função implementada no módulo
*     =criarbaralho                 inxBaralho 
*     =destruirbaralho              inxBaralho 
*     =inserircarta                 inxBaralho  naipe  rank
*     =copiarbaralho                inxBaralho  inxBaralho2
*     =checarigual                  inxBaralho  inxBaralho2 CondRetEsp
*           - verifica se dois baralhos são iguais; CondRetEsp deve ser
*             TRUE ou FALSE
*     =termina
*
***********************************************************************/

    TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
    {

         int inxBaralho   = -1 ,
             inxBaralho2  = -1 ,
             numLidos     = -1 ,
             condRetEsp   = -1  ;
         int i ;

         CAR_tppCarta pCarta ;

         CAR_tpNaipe naipe ;

         CAR_tpRank rank ;

         LIS_tpCondRet lisCondRet ;

         /* Efetuar reset de teste de baralho */

            if ( strcmp( ComandoTeste , RESET_EMB_CMD ) == 0 )
            {

               cartas = LIS_CriarLista( DestruirCarta ) ;
               if( cartas == NULL )
               {
                  return TST_CompararPonteiroNulo( 1 , cartas , 
                            "Erro ao gerar lista de ponteiros para cartas.");
               } /* if */

               for( i = 0 ; i < DIM_VT_BARALHOS ; i++ )
               {
                  vtBaralhos[ i ] = NULL ;
               } /* for */

               return TST_CondRetOK ;

            } /* fim ativa: Efetuar reset de teste de baralho */

         /* Testar Embaralhar */

            else if ( strcmp( ComandoTeste , EMBARALHAR_CMD ) == 0 )
            {

               numLidos = LER_LerParametros( "ii" , &inxBaralho ,
                             &condRetEsp ) ;
               if ( ( numLidos != 2 )
                    || ( ! ValidarInxBaralhos( inxBaralho , NAO_VAZIO )))
               {
                  return TST_CondRetParm ;
               } /* if */

               return TST_CompararInt( condRetEsp , EMB_Embaralhar(
                         vtBaralhos[ inxBaralho ] ) ,
                         "Erro ao embaralhar."  ) ;

            } /* fim ativa: Testar Embaralhar */

         /* Criar baralho */

            else if ( strcmp( ComandoTeste , CRIAR_BARALHO_CMD ) == 0 )
            {

               numLidos = LER_LerParametros( "i" , &inxBaralho ) ;

               if ( ( numLidos != 1 )
                     || ( ! ValidarInxBaralhos( inxBaralho , VAZIO )))
               {
                  return TST_CondRetParm ;
               } /* if */

               vtBaralhos[ inxBaralho ] = LIS_CriarLista( NULL ) ;

               return TST_CompararPonteiroNulo( 1 , vtBaralhos[ inxBaralho ] ,
                         "Erro em ponteiro de novo baralho."  ) ;

            } /* fim ativa: Criar baralho */

         /* Destruir baralho */

            else if ( strcmp( ComandoTeste , DESTRUIR_BARALHO_CMD ) == 0 )
            {

               numLidos = LER_LerParametros( "i" , &inxBaralho ) ;

               if ( ( numLidos != 1 )
                     || ( ! ValidarInxBaralhos( inxBaralho , NAO_VAZIO )))
               {
                  return TST_CondRetParm ;
               } /* if */

               LIS_DestruirLista( vtBaralhos[ inxBaralho ] ) ;
               vtBaralhos[ inxBaralho ] = NULL ;

               return TST_CondRetOK ;

            } /* fim ativa: Destruir baralho */

         /* Inserir carta em um baralho */

            else if ( strcmp( ComandoTeste , INSERIR_CARTA_CMD ) == 0 )
            {

               numLidos = LER_LerParametros( "iii" ,
                             &inxBaralho , &naipe , &rank ) ;

               if ( ( numLidos != 3 )
                   || ( ! ValidarInxBaralhos( inxBaralho , NAO_VAZIO )) )
               {
                  return TST_CondRetParm ;
               } /* if */

               pCarta = CAR_CriarCarta( naipe, rank ) ;
               if( pCarta == NULL )
               {
                  return TST_CompararPonteiroNulo( 1 , pCarta , 
                            "Erro ao criar ponteiro de carta.") ;
               } /* if */

               lisCondRet = LIS_InserirElementoApos( cartas , 
                               ( void * ) pCarta ) ;
               if( LIS_CondRetOK != lisCondRet )
               {
                  return TST_CompararInt( LIS_CondRetOK , lisCondRet , 
                            "Erro ao criar referencia para carta.") ;
               } /* if */

               return TST_CompararInt( LIS_CondRetOK , 
                         LIS_InserirElementoApos( vtBaralhos[ inxBaralho ] ,
                            pCarta ) , 
                         "Erro ao inserir carta em baralho." ) ;

            } /* fim ativa: Inserir carta em um baralho */

         /* Copiar baralho */

            else if ( strcmp( ComandoTeste , COPIAR_BARALHO_CMD ) == 0 )
            {

               numLidos = LER_LerParametros( "ii" ,
                             &inxBaralho , &inxBaralho2 ) ;

               if ( ( numLidos != 2 )
                     || ( ! ValidarInxBaralhos( inxBaralho , NAO_VAZIO )) 
                     || ( ! ValidarInxBaralhos( inxBaralho2 , NAO_VAZIO )))
               {
                  return TST_CondRetParm ;
               } /* if */

               return TST_CompararInt( LIS_CondRetOK , CopiarBaralho( 
                         vtBaralhos[ inxBaralho ] , vtBaralhos[ inxBaralho2 ] ) ,
                         "Condicao de retorno errada ao copiar baralhos." ) ;

            } /* fim ativa: Testar copiar baralho */

         /* Comparar baralhos */

            else if ( strcmp( ComandoTeste , CHECAR_IGUAL_CMD ) == 0 )
            {

               numLidos = LER_LerParametros( "iii" , &inxBaralho ,
                             &inxBaralho2 , &condRetEsp ) ;

               if ( ( numLidos != 3 )
                     || ( ! ValidarInxBaralhos( inxBaralho , NAO_VAZIO )) 
                     || ( ! ValidarInxBaralhos( inxBaralho2 , NAO_VAZIO )))
               {
                  return TST_CondRetParm ;
               } /* if */

               return TST_CompararInt( condRetEsp , ChecarIgual( 
                         vtBaralhos[ inxBaralho ] , vtBaralhos[ inxBaralho2 ] ) ,
                         "Retorno errado ao checar igualdade de baralhos." ) ;

            } /* fim ativa: Comparar baralhos */

         /* Executa término do teste */

            else if ( strcmp( ComandoTeste , TERMINA_CMD ) == 0 )
            {

               LIS_DestruirLista( cartas ) ;

               for( i = 0 ; i < DIM_VT_BARALHOS ; i++ )
               {
                  if( ValidarInxBaralhos( i , NAO_VAZIO ))
                  {
                     LIS_DestruirLista( vtBaralhos[ i ] ) ;
                     vtBaralhos[ i ] = NULL ;
                  } /* if */
               } /* for */

               return TST_CondRetOK ;

            } /* fim ativa: Executa término do teste */
        
         return TST_CondRetNaoConhec ;

    } /* Fim função: TCAR &Testar baralho de um baralho */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TEMB -Validar indice do vetor de baralhos
*
***********************************************************************/

   int ValidarInxBaralhos( int inxBaralho , int Modo )
   {

      if ( ( inxBaralho <  0 )
        || ( inxBaralho >= DIM_VT_BARALHOS ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtBaralhos[ inxBaralho ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtBaralhos[ inxBaralho ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TEMB -Validar indice do vetor de baralhos */

/***********************************************************************
*
*  $FC Função: TEMB -Copiar baralho
*
***********************************************************************/

   LIS_tpCondRet CopiarBaralho( LIS_tppLista baralhoDst , 
                                LIS_tppLista baralhoOrg  )
   {
         
      LIS_tpCondRet retornoAvanco = LIS_CondRetOK ;

      CAR_tppCarta pCarta = NULL ;
         
      LIS_EsvaziarLista( baralhoDst ) ;

      IrInicioLista( baralhoDst ) ;
      IrInicioLista( baralhoOrg ) ;

      while( retornoAvanco == LIS_CondRetOK )
      {
         pCarta = ( CAR_tppCarta ) LIS_ObterValor( baralhoOrg ) ;
         if( pCarta == NULL )
         {
            return LIS_CondRetNaoAchou ;
         } /* if */

         if( LIS_InserirElementoApos( baralhoDst , pCarta ) !=
             LIS_CondRetOK )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

         retornoAvanco = LIS_AvancarElementoCorrente( baralhoOrg , 1 ) ;
      } /* while */

      return LIS_CondRetOK ;

   } /* Fim função: TEMB -Copiar baralho */

/***********************************************************************
*
*  $FC Função: TEMB -Checar igualdade de baralhos
*
***********************************************************************/

   int ChecarIgual( LIS_tppLista baralhoA , LIS_tppLista baralhoB  )
   {
         
      LIS_tpCondRet retornoAvancoA = LIS_CondRetOK ;
      LIS_tpCondRet retornoAvancoB = LIS_CondRetOK ;

      CAR_tppCarta pCartaA = NULL ;
      CAR_tppCarta pCartaB = NULL ;

      IrInicioLista( baralhoA ) ;
      IrInicioLista( baralhoB ) ;

      while( retornoAvancoA == LIS_CondRetOK &&
             retornoAvancoB == LIS_CondRetOK )
      {
         pCartaA = ( CAR_tppCarta ) LIS_ObterValor( baralhoA ) ;
         pCartaB = ( CAR_tppCarta ) LIS_ObterValor( baralhoB ) ;
         if( pCartaA != pCartaB )
         {
            return FALSE ;
         } /* if */

         retornoAvancoA = LIS_AvancarElementoCorrente( baralhoA , 1 ) ;
         retornoAvancoB = LIS_AvancarElementoCorrente( baralhoB , 1 ) ;
      } /* while */

      if( retornoAvancoA != retornoAvancoB )
      {
         return FALSE ;
      } /* if */

      return TRUE ;

   } /* Fim função: TEMB -Checar igualdade de baralhos */

/***********************************************************************
*
*  $FC Função: TEMB -Destruir carta
*
***********************************************************************/

   void DestruirCarta( void * pCarta )
   {
         
      CAR_DestruirCarta( ( CAR_tppCarta ) pCarta ) ;

   } /* Fim função: TEMB -Destuir carta  */

/********** Fim do módulo de implementação: TEMB Teste embaralhamento **********/

