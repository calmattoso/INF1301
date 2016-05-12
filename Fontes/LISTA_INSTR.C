/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: clm
*           avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     5       clm   25/nov/2013 início da instrumentação
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>


#define LISTA_INSTR_OWN
#include "LISTA_INSTR.h"
#undef LISTA_INSTR_OWN

#ifdef _DEBUG
   #include "GENERICO.h"
   #include "CESPDIN.H"
   #include "CONTA.h"
#endif

#include "LISTA.h"

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

   LIS_tppLista LIS_CriarListaInstr(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {

      return LIS_CriarLista( ExcluirValor ) ;

   } /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

   void LIS_DestruirListaInstr( LIS_tppLista pLista )
   {

      /* Assertivas de entrada */
         
         if( pLista == NULL )
         {
            TST_NotificarFalha( "LIS_DestruirListaInstr, Lista nao existe" ) ;
            return;
         } /* if */

      LIS_DestruirLista( pLista ) ;

   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

   void LIS_EsvaziarListaInstr( LIS_tppLista pLista )
   {

      /* Assertivas de entrada */
         
         if( pLista == NULL )
         {
            TST_NotificarFalha( "LIS_EsvaziarListaInstr, Lista nao existe" ) ;
            return;
         } /* if */

      LIS_DestruirLista( pLista ) ;

   } /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntesInstr( LIS_tppLista pLista ,
                                                void * pValor        )
   {
      
      int numErros = 0 ;

      /* Assertivas de entrada */
         
         if( pLista == NULL )
         {
            TST_NotificarFalha( "LIS_InserirElementoAntesInstr, Lista nao existe" ) ;
            numErros++ ;
         } /* if */

         if( pValor == NULL )
         {
            TST_NotificarFalha( "LIS_InserirElementoAntesInstr, Valor nulo" ) ;
            numErros++ ;
         } /* if */

         if( numErros > 0 )
         {
            return LIS_CondRetErroParm ;
         } /* if */


      return LIS_InserirElementoAntes( pLista , pValor ) ;

   } /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoAposInstr( LIS_tppLista pLista ,
                                               void * pValor        )
      
   {

      int numErros = 0 ;

      /* Assertivas de entrada */
         
         if( pLista == NULL )
         {
            TST_NotificarFalha( "LIS_InserirElementoAposInstr, Lista nao existe" ) ;
            numErros++ ;
         } /* if */

         if( pValor == NULL )
         {
            TST_NotificarFalha( "LIS_InserirElementoAposInstr, Valor nulo" ) ;
            numErros++ ;
         } /* if */

         if( numErros > 0 )
         {
            return LIS_CondRetErroParm ;
         } /* if */


      return LIS_InserirElementoApos( pLista , pValor ) ;

   } /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElementoInstr( LIS_tppLista pLista )
   {

      /* Assertivas de entrada */
         
         if( pLista == NULL )
         {
            TST_NotificarFalha( "LIS_ExcluirElementoInstr, Lista nao existe" ) ;
            return LIS_CondRetErroParm ;
         } /* if */


      return LIS_ExcluirElemento( pLista ) ;

   } /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

   void * LIS_ObterValorInstr( LIS_tppLista pLista )
   {

      /* Assertivas de entrada */
         
         if( pLista == NULL )
         {
            TST_NotificarFalha( "LIS_ObterValorInstr, Lista nao existe" ) ;
            return NULL ;
         } /* if */


      return LIS_ObterValor( pLista ) ;

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

   void IrInicioListaInstr( LIS_tppLista pLista )
   {

      /* Assertivas de entrada */
         
         if( pLista == NULL )
         {
            TST_NotificarFalha( "IrInicioListaInstr, Lista nao existe" ) ;
            return;
         } /* if */


      IrInicioLista( pLista ) ;

   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

   void IrFinalListaInstr( LIS_tppLista pLista )
   {

      /* Assertivas de entrada */
         
         if( pLista == NULL )
         {
            TST_NotificarFalha( "LIS_IrFinalListaInstr, Lista nao existe" ) ;
            return;
         } /* if */


      IrFinalLista( pLista ) ;

   } /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrenteInstr( LIS_tppLista pLista ,
                                                   int numElem          )
   {

      /* Assertivas de entrada */
         
         if( pLista == NULL )
         {
            TST_NotificarFalha( "LIS_AvancarElementoCorrenteInstr, Lista nao existe" ) ;
            return LIS_CondRetErroParm ;
         } /* if */


      return LIS_AvancarElementoCorrente( pLista , numElem ) ;

   } /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValorInstr( LIS_tppLista pLista ,
                                         void * pValor        )
   {

      int numErros = 0 ;

      /* Assertivas de entrada */
         
         if( pLista == NULL )
         {
            TST_NotificarFalha( "LIS_ProcurarValorInstr, Lista nao existe" ) ;
            numErros++ ;
         } /* if */

         if( pValor == NULL )
         {
            TST_NotificarFalha( "LIS_ProcurarValorInstr, Valor nulo" ) ;
            numErros++ ;
         } /* if */

         if( numErros > 0 )
         {
            return LIS_CondRetErroParm ;
         } /* if */

      return LIS_ProcurarValor( pLista , pValor ) ;

   } /* Fim função: LIS  &Procurar elemento contendo valor */

/***************************************************************************
*
*  Função: LIS  &Obter numero de elementos
*  ****/

   int LIS_ObterNumeroElementosInstr( LIS_tppLista pLista )
   {

      /* Assertivas de entrada */
         
         if( pLista == NULL )
         {
            TST_NotificarFalha( "LIS_ObterNumeroElementosInstr, Lista nao existe" ) ;
            return 0 ;
         } /* if */

      return LIS_ObterNumeroElementosInstr( pLista ) ;

   } /* Fim função: LIS  &Obter numero de elementos */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: LIS  &LIS_VerificarLista
*
***********************************************************************/

   LIS_tpCondRet LIS_VerificarListaInstr( LIS_tppLista pLista )
   {

      return LIS_VerificarLista( pLista ) ;
   
   } /* Função &LIS_VerificarLista */

/***********************************************************************
*
*  $FC Função: LIS  &Deturpar Lista
*
***********************************************************************/

   void LIS_DeturparListaInstr( LIS_tppLista * ppLista              , 
                                LIS_tpModosDeturpacao modoDeturpacao )
   {

      int numErros = 0 ;

      /* Assertivas de entrada */
         
         if( ppLista == NULL )
         {
            TST_NotificarFalha( "LIS_DeturparListaInstr, PP p/ lista nao existe" ) ;
            numErros++ ;
         } /* if */

         if( ( *ppLista ) == NULL )
         {
            TST_NotificarFalha( "LIS_DeturparListaInstr, Lista nao existe" ) ;
            numErros++ ;
         } /* if */

         if( numErros > 0 )
         {
            return;
         } /* if */

      LIS_DeturparLista( ppLista , modoDeturpacao ) ;  

   } /* Função &Deturpar Lista */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/