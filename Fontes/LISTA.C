/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: clm
*           avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     5       clm   25/nov/2013 in�cio da instrumenta��o
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>


#define LISTA_OWN
   #include "LISTA.h"
#undef LISTA_OWN

#ifdef _DEBUG
   #include "GENERICO.h"
   #include "CESPDIN.H"
   #include "CONTA.h"
   #include   "..\\Tabelas\\IdTiposEspaco.def"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         #ifdef _DEBUG

         LIS_tppLista pCabeca ;
               /* Ponteiro para cabeca
               *
               * $ED Descri��o
               *    Todos os elementos da lista devem apontar para a 
               *      respectiva cabe�a.
               *    Este ponteiro corresponde a um identificador da 
               *      lista para fins de verifica��o da integridade. */

         #endif

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para elemento antecessor
               *
               *$EED Assertivas estruturais
               *   Seja o elemento em quest�o pElem e a lista � qual ele
               *     pertence pLista.
               *   Se pElem->pAnt == NULL, ent�o pLista->pOrigemLista == pElem.
               *   Se pElem->pAnt != NULL, pElem->pAnt->pProx == pElem. */

         struct tagElemLista * pProx ;
               /* Ponteiro para elemento seguinte
               *
               *$EED Assertivas estruturais
               *   Seja o elemento em quest�o pElem e a lista � qual ele
               *     pertence pLista.
               *   Se pElem->pProx == NULL, ent�o pLista->pFimLista == pElem.
               *   Se pElem->pProx != NULL, pElem->pProx->pAnt == pElem. */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe�a de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* N�mero de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a fun��o de destrui��o do valor 
                     contido em um elemento */

   } LIS_tpLista ;


/*****  Dados encapsulados no m�dulo  *****/

   #ifdef _DEBUG

      static char EspacoLixo[ 256 ] =
             "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
            /* Espa�o de dados lixo usado ao testar */

   #endif

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LIS  &Criar lista
*  ****/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {

      LIS_tpLista * pLista = NULL ;

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_CriarLista, Entrou" ) ;
      #endif

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pLista == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_CriarLista, Faltou memo'ria" ) ;
         #endif

         return NULL ;
      } /* if */
      #ifdef _DEBUG
         CED_DefinirTipoEspaco( pLista , LIS_TipoEspacoCabeca ) ;
      #endif

      LimparCabeca( pLista ) ;

      pLista->ExcluirValor = ExcluirValor ;

      return pLista ;

   } /* Fim fun��o: LIS  &Criar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Destruir lista
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {
      #ifdef _DEBUG
         CNT_CONTAR( "LIS_DestruirLista, Entrou" ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim fun��o: LIS  &Destruir lista */

/***************************************************************************
*
*  Fun��o: LIS  &Esvaziar lista
*  ****/

   void LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_EsvaziarLista, Entrou" ) ;
      #endif

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_EsvaziarLista, Loop de esvaziar" ) ;
         #endif

         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;

   } /* Fim fun��o: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_InserirElementoAntes, Entrou" ) ;
      #endif

      /* Criar elemento a inerir antes */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_InserirElementoAntes, Faltou memoria" ) ;
            #endif

            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_InserirElementoAntes, Lista vazia" ) ;
            #endif

            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "LIS_InserirElementoAntes, Entre dois elems" ) ;
               #endif

               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento ap�s
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
      
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_InserirElementoApos, Entrou" ) ;
      #endif

      /* Criar elemento a inserir ap�s */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_InserirElementoApos, Faltou memoria" ) ;
            #endif

            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento ap�s o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_InserirElementoApos, Lista vazia" ) ;
            #endif

            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "LIS_InserirElementoApos, Entre dois elems" ) ;
               #endif

               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "LIS_InserirElementoApos, Final da lista" ) ;
               #endif

               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir elemento ap�s */

/***************************************************************************
*
*  Fun��o: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_ExcluirElemento, Entrou" ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_ExcluirElemento, Lista vazia" ) ;
         #endif

         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia � esquerda */

         if ( pElem->pAnt != NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_ExcluirElemento, Desencadeia a esquerda" ) ;
            #endif

            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_ExcluirElemento, Remove origem" ) ;
            #endif

            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia � direita */

         if ( pElem->pProx != NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_ExcluirElemento, Desencadeia a direita" ) ;
            #endif

            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_ExcluirElemento, Remove final" ) ;
            #endif

            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Excluir elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*  ****/

   void * LIS_ObterValor( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_ObterValor, Entrou" ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_ObterValor, Elemento vazio" ) ;
         #endif

         return NULL ;
      } /* if */

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_ObterValor, Elemento com valor" ) ;
      #endif

      return pLista->pElemCorr->pValor ;

   } /* Fim fun��o: LIS  &Obter refer�ncia para o valor contido no elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento inicial
*  ****/

   void IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         CNT_CONTAR( "IrInicioLista, Entrou" ) ;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;

   } /* Fim fun��o: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento final
*  ****/

   void IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         CNT_CONTAR( "IrFinalLista, Entrou" ) ;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim fun��o: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Fun��o: LIS  &Avan�ar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_AvancarElementoCorrente, Entrou" ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_AvancarElementoCorrente, Lista vazia" ) ;
            #endif

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avan�ar para frente */

         if ( numElem > 0 )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_AvancarElementoCorrente, Avanco para frente" ) ;
            #endif

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "LIS_AvancarElementoCorrente, Loop para frente" ) ;
               #endif

               if ( pElem == NULL )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "LIS_AvancarElementoCorrente, Atingiu final" ) ;
                  #endif

                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "LIS_AvancarElementoCorrente, Achou para frente" ) ;
               #endif

               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            #ifdef _DEBUG
               CNT_CONTAR( "LIS_AvancarElementoCorrente, Avancou pro fim" ) ;
            #endif

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avan�ar para frente */

      /* Tratar avan�ar para tr�s */

         else if ( numElem < 0 )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_AvancarElementoCorrente, Avanco para tras" ) ;
            #endif

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "LIS_AvancarElementoCorrente, Loop para tras" ) ;
               #endif

               if ( pElem == NULL )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "LIS_AvancarElementoCorrente, Atingiu inicio" ) ;
                  #endif

                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "LIS_AvancarElementoCorrente, Achou para tras" ) ;
               #endif
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            #ifdef _DEBUG
               CNT_CONTAR( "LIS_AvancarElementoCorrente, Avancou pro comeco" ) ;
            #endif

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avan�ar para tr�s */

      /* Tratar n�o avan�ar */
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_AvancarElementoCorrente, Sem avanco" ) ;
         #endif

         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Avan�ar elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_ProcurarValor, Entrou" ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_ProcurarValor, Lista vazia" ) ;
         #endif
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_ProcurarValor, Loop de procura" ) ;
         #endif

         if ( pElem->pValor == pValor )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_ProcurarValor, Achou elemento" ) ;
            #endif
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_ProcurarValor, Nao achou elemento" ) ;
      #endif

      return LIS_CondRetNaoAchou ;

   } /* Fim fun��o: LIS  &Procurar elemento contendo valor */

/***************************************************************************
*
*  Fun��o: LIS  &Obter numero de elementos
*  ****/

   int LIS_ObterNumeroElementos( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_ObterNumeroElementos, Entrou" ) ;
      #endif

      return pLista->numElem ;

   } /* Fim fun��o: LIS  &Obter numero de elementos */

/***********************************************************************
*
*  $FC Fun��o: LIS  &LIS_VerificarLista
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarLista( LIS_tppLista pLista )
   {

      int numElem = 0 ;
      int correnteVisto = 0 ;

      tpElemLista * pElem = NULL ;
  
      CNT_CONTAR( "LIS_VerificarLista, Entrou" );
      

   /* Verifica o tipo do espa�o */

      if ( pLista == NULL )
      {
         CNT_CONTAR( "LIS_VerificarLista, Cabeca inexistente" ) ;
         TST_NotificarFalha( "Tentou verificar cabeca inexistente." ) ;
         return LIS_CondRetErroEstrutura ;
      } 
   
      if ( ! CED_VerificarEspaco( pLista , NULL ) )
      {
         CNT_CONTAR( "LIS_VerificarLista, Espaco de dados de cabeca nao integro" ) ;
         TST_NotificarFalha( "Controle do espaco acusou erro." ) ;
         return LIS_CondRetErroEstrutura ;
      }
   
      if ( TST_CompararInt( LIS_TipoEspacoCabeca ,
              CED_ObterTipoEspaco( pLista ) ,
              "Tipo do espa�o de dados nao e' cabe�a de lista." ) != TST_CondRetOK )
      {
         CNT_CONTAR( "LIS_VerificarLista, Erro no tipo de espaco de dados de cabeca" ) ;
         return LIS_CondRetErroEstrutura ;
      }

      CED_MarcarEspacoAtivo( pLista ) ;

   /* Verifica estrutura de lista vazia */

      if ( pLista->numElem == 0 )
      {
         /* Origem da lista tem que ser nula */
            if ( pLista->pOrigemLista != NULL )
            {
               CNT_CONTAR( "LIS_VerificarLista, Lista vazia com elemento origem" ) ;
               TST_NotificarFalha( "Lista vazia tem elemento origem." ) ;
               return LIS_CondRetErroEstrutura ;
            } /* if */

         /* Fim da lista tem que ser nulo */
            if ( pLista->pFimLista != NULL )
            {
               CNT_CONTAR( "LIS_VerificarLista, Lista vazia com elemento final." ) ;
               TST_NotificarFalha( "Lista vazia tem elemento final." ) ;
               return LIS_CondRetErroEstrutura ;
            } /* if */

         /* Elemento corrente tem que ser nulo */
            if ( pLista->pElemCorr != NULL )
            {
               CNT_CONTAR( "LIS_VerificarLista, Lista vazia com elemento corrente" ) ;
               TST_NotificarFalha( "Lista vazia tem elemento corrente." ) ;
               return LIS_CondRetErroEstrutura ;
            } /* if */
      } 

   /* Verifica estrutura de lista n�o vazia */

      else {

         /* Elemento origem tem que ser n�o nulo */
            if ( pLista->pOrigemLista == NULL )
            {
               CNT_CONTAR( "LIS_VerificarLista, Lista nao vazia sem elemento origem" ) ;
               TST_NotificarFalha( "Lista nao vazia sem elemento origem." ) ;
               return LIS_CondRetErroEstrutura ;
            } /* if */

         /* Elemento final tem que ser n�o nulo */
            if ( pLista->pFimLista == NULL )
            {
               CNT_CONTAR( "LIS_VerificarLista, Lista nao vazia sem elemento final" ) ;
               TST_NotificarFalha( "Lista nao vazia sem elemento final." ) ;
               return LIS_CondRetErroEstrutura ;
            } /* if */

         /* Elemento corrente tem que ser n�o nulo */
            if ( pLista->pElemCorr == NULL )
            {
               CNT_CONTAR( "LIS_VerificarLista, Lista nao vazia sem elemento corrente" ) ;
               TST_NotificarFalha( "Lista nao vazia sem elemento corrente" ) ;
               return LIS_CondRetErroEstrutura ;
            } /* if */
            
         /* Itera sobre cada elemento da lista, verificando se todos respeitam as assertivas
               estruturais da lista */
            for ( pElem = pLista->pOrigemLista ; 
                  pElem != NULL ; 
                  pElem = pElem->pProx )
            {
               CNT_CONTAR( "LIS_VerificarLista, Loop de verificacao dos elementos" ) ;
              
               numElem++;

               /* Verifica o tipo do espa�o de mem�ria do elemento da lista */

                  if ( ! CED_VerificarEspaco( pElem , NULL ) )
                  {
                     CNT_CONTAR( "LIS_VerificarLista, Espaco de dados de elemento nao integro" ) ;
                     TST_NotificarFalha( "Espaco de dados de elemento nao integro." ) ;
                     return LIS_CondRetErroEstrutura ;
                  } /* if */

                  if ( TST_CompararInt( LIS_TipoEspacoElemento ,
                          CED_ObterTipoEspaco( pElem ) ,
                          "Tipo do espaco de dados nao e' elemento da lista." ) != TST_CondRetOK )
                  {
                     CNT_CONTAR( "LIS_VerificarLista, Erro no tipo de espaco de dados de elemento" ) ;
                     return LIS_CondRetErroEstrutura ;
                  } /* if */

                  CED_MarcarEspacoAtivo( pElem ) ;

               /* Elemento tem que apontar para a cabeca da lista sendo verificada */
                  if ( pElem->pCabeca != pLista )
                  {
                     CNT_CONTAR( "LIS_VerificarLista, Elemento nao aponta para cabeca da lista" ) ;
                     TST_NotificarFalha( " Elemento nao aponta para cabeca da lista." ) ;
                     return LIS_CondRetErroEstrutura ;
                  } /* if */

               /* Verifica elemento anterior � pElem */
                  if ( pElem->pAnt != NULL )
                  {
                  /* O elemento seguinte ao anterior de pElem tem que ser pElem */
                     if ( pElem->pAnt->pProx != pElem )
                     {
                        CNT_CONTAR( "LIS_VerificarLista, Erro no encadeamento com elemento anterior" ) ;
                        TST_NotificarFalha( "Erro no encadeamento com elemento anterior." ) ;
                        return LIS_CondRetErroEstrutura ;
                     } /* if */
                  } 
                  else
                  {
                  /* Para que o anterior seja nulo, pElem tem que ser o elemento origem da lista */
                     if ( pElem != pLista->pOrigemLista )
                     {
                        CNT_CONTAR( "LIS_VerificarLista, Anterior nulo em elemento nao origem" ) ;
                        TST_NotificarFalha( "Anterior nulo em elemento nao origem." ) ;
                        return LIS_CondRetErroEstrutura ;
                     } /* if */
                  } /* if */

               /* Verifica elemento seguinte � pElem */
                  if ( pElem->pProx == NULL )
                  {
                  /* Para que o seguinte seja nulo, pElem tem que ser o elemento final da lista */
                     if ( pElem != pLista->pFimLista )
                     {
                        CNT_CONTAR( "LIS_VerificarLista, Seguinte nulo em elemento nao final" );
                        TST_NotificarFalha( "Seguinte nulo em elemento nao final." ) ;
                        return LIS_CondRetErroEstrutura ;
                     } /* if */
                  } /* if */
            
               /* Marca que o elemento corrente foi visto, caso pElem == pLista->pElemCorr */

                  if ( pElem == pLista->pElemCorr )
                  {
                     correnteVisto = 1 ;
                  } /* if */

            } /* for */
         
         /* Verifica se a quantidade de elementos encontrados na lista � a mesma armazenada na cabe�a. */
            if ( TST_CompararInt( numElem , pLista->numElem ,
                    "Quantidade de elementos diferente da especificada na lista." ) 
                 != TST_CondRetOK )
            {
               CNT_CONTAR( "LIS_VerificarLista, Quantidade de elementos diferente da esperada" );
               return LIS_CondRetErroEstrutura ;
            } /* if */

         /* Verifica que o elemento corrente de fato esta' na lista */
            if ( TST_CompararInt( correnteVisto , 1 ,
                    "Elemento corrente nao esta na lista." ) 
                 != TST_CondRetOK )
            {
               CNT_CONTAR( "LIS_VerificarLista, Elemento corrente nao esta na lista" );
               return LIS_CondRetErroEstrutura ;
            } /* if */
      } /* if */

   /* Lista com todas as assertivas v�lidas */

      return LIS_CondRetOK ;
   
   } /* Fun��o &LIS_VerificarLista */

#endif


/***********************************************************************
*
*  $FC Fun��o: LIS  &Deturpar Lista
*
***********************************************************************/

#ifdef _DEBUG

   void LIS_DeturparLista( LIS_tppLista * ppLista , 
                           LIS_tpModosDeturpacao modoDeturpacao )
   {

      LIS_tppLista  pLista = *ppLista ;
      
      tpElemLista * pElem  = NULL ;

      switch ( modoDeturpacao )
      {
         case DeturpaEliminaCorrente :
            pElem = pLista->pElemCorr ;
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               pLista->pElemCorr = pLista->pElemCorr->pAnt ;
            } 
            else
            {
               pLista->pElemCorr = pLista->pElemCorr->pProx ;
            } /* if */
            LiberarElemento( pLista , pElem ) ;
            break;
         case DeturpaPtProxNulo :
            pLista->pElemCorr->pProx = NULL ;
            break ;
         case DeturpaPtAntNulo :
            pLista->pElemCorr->pAnt = NULL ;
            break ;
         case DeturpaPtProxLixo :
            pLista->pElemCorr->pProx = ( tpElemLista * ) EspacoLixo ;
            break ;
         case DeturpaPtAntLixo :
            pLista->pElemCorr->pAnt = ( tpElemLista * ) EspacoLixo ;
            break ;
         case DeturpaRetiraCorrente :
            pElem = pLista->pElemCorr ;
            if ( pLista->pElemCorr->pProx != NULL )
            {               
               pLista->pElemCorr->pProx->pAnt = ( tpElemLista * ) EspacoLixo ;
            }
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               pLista->pElemCorr = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pProx = ( tpElemLista * ) EspacoLixo ;
            } else
            {
               pLista->pElemCorr = pLista->pElemCorr->pProx ;
            }
            break ;  
         case DeturpaCorrenteNulo :
            pLista->pElemCorr = NULL ;
            break ;
         case DeturpaOrigemNulo :
            pLista->pOrigemLista = NULL ;
            break ;
         case DeturpaCorrenteLixo :
            pLista->pElemCorr = ( tpElemLista * ) EspacoLixo ;
            break ;
         case DeturpaOrigemLixo :
            pLista->pOrigemLista = ( tpElemLista * ) EspacoLixo ;
            break ;
         case DeturpaFimNulo :
            pLista->pFimLista = NULL ;
            break ;
         case DeturpaFimLixo :
            pLista->pFimLista = ( tpElemLista * ) EspacoLixo ;
            break ;
         case DeturpaNumElem :
            (pLista->numElem) = -1;
            break ;
         case DeturpaPtCabecaNulo :
            pLista->pElemCorr->pCabeca = NULL;
            break ;
         case DeturpaPtCabecaLixo :
            pLista->pElemCorr->pCabeca = ( LIS_tppLista ) EspacoLixo ;
            break ;
         case DeturpaEspacoLista :
            CED_DefinirTipoEspaco( pLista, CED_ID_TIPO_VALOR_NULO ) ;
            break ;
         case DeturpaEspacoElemento :
            CED_DefinirTipoEspaco( pLista->pElemCorr, CED_ID_TIPO_VALOR_NULO ) ;
            break ;
         case DeturpaListaNulo :
            *ppLista = NULL ;
            break ;
         case DeturpaListaLixo :
            *ppLista = ( LIS_tppLista ) EspacoLixo ;
            break ;
         case DeturpaPtAntPtProx :
            pLista->pElemCorr->pAnt->pProx = ( tpElemLista * ) EspacoLixo ;
            break ;
         case DeturpaPtProxPtAnt :
            pLista->pElemCorr->pProx->pAnt = ( tpElemLista * ) EspacoLixo ;
            break ;

      } /* switch */

   } /* Fun��o &Deturpar Lista */    

#endif

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: LIS  -Liberar elemento da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      #ifdef _DEBUG
         CNT_CONTAR( "LiberarElemento, Entrou" ) ;
      #endif

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LiberarElemento, ExcluirValor" ) ;
         #endif
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      ( pLista->numElem )-- ;

   } /* Fim fun��o: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         CNT_CONTAR( "CriarElemento, Entrou" ) ;
      #endif

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "CriarElemento, Faltou memo'ria" ) ;
         #endif

         return NULL ;
      } /* if */

      #ifdef _DEBUG
         CED_DefinirTipoEspaco( pElem , LIS_TipoEspacoElemento ) ;
         pElem->pCabeca = pLista ;
      #endif

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      ( pLista->numElem )++ ;

      return pElem ;

   } /* Fim fun��o: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Limpar a cabe�a da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         CNT_CONTAR( "LimparCabeca, Entrou" ) ;
      #endif

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim fun��o: LIS  -Limpar a cabe�a da lista */


/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/