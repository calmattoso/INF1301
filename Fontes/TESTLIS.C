/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include  "LISTA.h"

#ifdef _DEBUG
  #include  "CESPDIN.h"
  #include  "..\\tabelas\\IdTiposEspaco.def"
#endif


static const char RESET_LISTA_CMD         [ ] = "=resetteste"       ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"       ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"    ;
static const char ESVAZIAR_LISTA_CMD      [ ] = "=esvaziarlista"    ;
static const char INS_ELEM_ANTES_CMD      [ ] = "=inselemantes"     ;
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"      ;
static const char PROCURAR_VALOR_CMD      [ ] = "=procurarvalor"    ;
static const char OBTER_NUM_ELEM_CMD      [ ] = "=obternumelems"    ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem"   ;
static const char EXC_ELEM_CMD            [ ] = "=excluirelem"      ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"         ;
static const char IR_FIM_CMD              [ ] = "=irfinal"          ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"      ;
static const char VERIFICAR_LISTA_CMD     [ ] = "=verificarlista"   ;
static const char DETURPAR_LISTA_CMD      [ ] = "=deturparlista"    ;
static const char LIMPAR_MEMORIA_CMD      [ ] = "=limparmemoria" ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   30
#define DIM_VT_VALOR  100
#define DIM_VALOR     100

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;

int vtValores[ DIM_VT_VALOR ] ;
int ultIdxValores = 0 ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarlista                   inxLista
*     =destruirlista                inxLista
*     =esvaziarlista                inxLista
*     =inselemantes                 inxLista  int      CondRetEsp
*     =inselemapos                  inxLista  int      CondRetEsp
*     =procurarvalor                inxLista  inxValor CondRetEsp
*     =obternumelems                inxLista  numElem
*     =obtervalorelem               inxLista  int      CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =avancarelem                  inxLista  numElem CondRetEsp
*     =verificarlista               inxLista    
*     =deturparlista                inxLista  modoDeturpacao
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista   = -1 ,
          inxValor   = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      LIS_tpCondRet lisCondRet ;

      int dado ;
      int * pDado ;

      int ValEsp = -1 ;
      int i ;
      int numElem = -1 ;
      
      #ifdef _DEBUG
        int  modoDeturpacao   = -1 ;
      #endif

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {
            /* Anula todo o velor de listas */

               for( i = 0 ; i < DIM_VT_LISTA ; i++ )
               {
                  vtListas[ i ] = NULL ;
               } /* for */

            /* Anula todo o vetor de valores */
               for( i = 0 ; i < DIM_VT_VALOR ; i++ )
               {
                  vtValores[ i ] = 0 ;
               } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */

         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                       &inxLista , &ValEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtListas[ inxLista ] =
                 LIS_CriarLista( DestruirValor ) ;

            return TST_CompararPonteiroNulo( ValEsp , vtListas[ inxLista ] ,
               "Erro em ponteiro de nova lista."  ) ;

         } /* fim ativa: Testar CriarLista */

      /* Testar Esvaziar lista  */

         else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_EsvaziarLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Esvaziar lista lista */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir lista */

      /* Testar inserir elemento antes */

         else if ( strcmp( ComandoTeste , INS_ELEM_ANTES_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxLista , &dado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista )) )
            {
               return TST_CondRetParm ;
            } /* if */

            vtValores[ ultIdxValores ] = dado ;
            ultIdxValores++ ;

            lisCondRet = LIS_InserirElementoAntes( vtListas[ inxLista ] ,
                            &vtValores[ ultIdxValores - 1 ] ) ;
            if( lisCondRet == LIS_CondRetFaltouMemoria )
            {
               ultIdxValores-- ;
            } /* if */

            return TST_CompararInt( CondRetEsp , lisCondRet ,
                     "Condicao de retorno errada ao inserir antes." ) ;

         } /* fim ativa: Testar inserir elemento antes */

      /* Testar inserir elemento apos */

         else if ( strcmp( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                          &inxLista , &dado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista )) )
            {
               return TST_CondRetParm ;
            } /* if */

            vtValores[ ultIdxValores ] = dado ;
            ultIdxValores++ ;

            lisCondRet = LIS_InserirElementoApos( vtListas[ inxLista ] , 
                            &vtValores[ ultIdxValores - 1 ] ) ;
            if( lisCondRet == LIS_CondRetFaltouMemoria )
            {
               ultIdxValores-- ;
            } /* if */

            return TST_CompararInt( CondRetEsp , lisCondRet ,
                     "Condicao de retorno errada ao inserir apos." ) ;

         } /* fim ativa: Testar inserir elemento apos */

      /* Testar procurar valor */

         else if ( strcmp( ComandoTeste , PROCURAR_VALOR_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "iii" , &inxLista , &inxValor ,
                          &CondRetEsp ) ;            

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista ))
              || ( ! ( inxValor >= 0 && inxValor < DIM_VT_VALOR )))
            {
               return TST_CondRetParm ;
            } /* if */
                  
            lisCondRet = LIS_ProcurarValor( vtListas[ inxLista ] , 
                            &vtValores[ inxValor ] ) ;

            return TST_CompararInt( CondRetEsp , lisCondRet ,
                     "Erro ao procurar valor." ) ;
         } /* fim ativa: Testar procurar valor */

      /* Testar obter numero de elementos */

         else if ( strcmp( ComandoTeste , OBTER_NUM_ELEM_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "ii" , &inxLista , 
                           &ValEsp ) ;            

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista )))
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( ValEsp , 
                      LIS_ObterNumeroElementos( vtListas[ inxLista ] ) ,
                     "Numero de elementos errado." ) ;
         } /* fim ativa: Testar obter numero de elementos */

      /* Testar excluir simbolo */

         else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_ExcluirElemento( vtListas[ inxLista ] ) ,
                     "Condição de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir simbolo */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxLista , &dado , &ValEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( int * ) LIS_ObterValor( vtListas[ inxLista ] ) ;

            if ( ValEsp == 0 )
            {
               return TST_CompararPonteiroNulo( 0 , pDado ,
                         "Valor não deveria existir." ) ;
            } /* if */

            if ( pDado == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pDado ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */

            return TST_CompararInt( dado , *pDado ,
                         "Valor do elemento errado." ) ;

         } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar ir para o elemento inicial */

         else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista )) )
            {
               return TST_CondRetParm ;
            } /* if */

            IrInicioLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ir para o elemento inicial */

      /* LIS  &Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista )) )
            {
               return TST_CondRetParm ;
            } /* if */

            IrFinalLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: LIS  &Ir para o elemento final */

      /* LIS  &Avançar elemento */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxLista , &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_AvancarElementoCorrente( vtListas[ inxLista ] , numElem ) ,
                      "Condicao de retorno errada ao avancar" ) ;

         } /* fim ativa: LIS  &Avançar elemento */

      /* Testar verificador de lista */
      #ifdef _DEBUG      

         else if ( strcmp( ComandoTeste , VERIFICAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista,
                          &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp , 
                      LIS_VerificarLista( vtListas[ inxLista ] ) ,
                      "Numero de falhas diferente do esperado."   ) ;

         } /* fim ativa: Testar verificador de lista */

      #endif

      /* Deturpar uma lista */     
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , DETURPAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista,
                          &modoDeturpacao ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista ) ))
            {
               return TST_CondRetParm ;
            } /* if */
                       
            LIS_DeturparLista( &vtListas[ inxLista ] ,
               ( LIS_tpModosDeturpacao ) modoDeturpacao ) ;

            return TST_CondRetOK;

         } /* fim ativa: Deturpar uma lista */

      #endif

      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , LIMPAR_MEMORIA_CMD ) == 0 )
         {

            CED_InicializarIteradorEspacos( ) ;

            while ( CED_ExisteEspacoCorrente( ) ) 
            {
              CED_ExcluirEspacoCorrente( ) ;
            } /* if */

            CED_TerminarIteradorEspacos( ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Verificar vazamento de memória */
      #endif

      return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      pValor = NULL ;
      return ;

   } /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
                
      return TRUE ;

   } /* Fim função: TLIS -Validar indice de lista */

/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

