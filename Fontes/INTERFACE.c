/***************************************************************************
*
*  $MCD Módulo de definição: INT Interface
*
*  Arquivo gerado:              INTERFACE.C
*  Letras identificadoras:      INT
*
*  Nome da base de software:    Trabalho 4 de Programação Modular
*  Arquivo da base de software: INTERFACE/INTERFACE.C
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: ffa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data      Observações
*     2       clm   27/nov/2013  modificações na função de leitura
*     1       ffa   25/nov/2013  início do desenvolvimento
*
*  $ED Descrição do módulo
*   Faz a comunicação entre o jogador e o jogo, exibindo a mesa,
*  recebendo comandos e exibindo mensagens.
***************************************************************************/


#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>

#include   "LISTA.h"
#include   "VISIVEL.h"
#include   "ORDENADA.h"
#include   "EXTRAS.h"

#define INTERFACE_OWN
#include "INTERFACE.H"
#undef INTERFACE_OWN

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarColuna( char * coluna ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: INT  &Exibir mesa
*  ****/

   INT_tpCondRet INT_ExibirMesa( LIS_tppLista pMesa ) 
   {
      
      int i ;

      char ordenadaString [ ORD_DIM_STRING ] ;
      char extrasString   [ EXT_DIM_STRING ] ;
      char visivelString  [ VIS_DIM_STRING ] ;

      ORD_tpCondRet CondRetOrd ;
      EXT_tpCondRet CondRetExt ;
      VIS_tpCondRet CondRetVis ;
      LIS_tpCondRet CondRetLis ;

      ORD_tppOrdenada pOrdAux ;
      EXT_tppExtras   pExtAux ;
      VIS_tppVisivel  pVisAux ;

      IrInicioLista( pMesa ) ;

      /* 4 ordenadas, 1 extra, 8 visíveis */
      for( i = 0 ; i < 13 ; i++ )
      { 
         /* Exibe os títulos das colunas */
            if( i == 0 )
            {
               printf( "ORDENADAS\n" ) ;
            }
            else if ( i == 5 )
            {
               printf( "\nVISIVEIS\n" ) ;
            } /* if */

         /* Exibe as 4 colunas de ordenadas */

            if( i < 4 )
            {
               pOrdAux = ( ORD_tppOrdenada ) LIS_ObterValor( pMesa ) ;

               CondRetOrd = ORD_ConverterParaString( pOrdAux ,
                               ordenadaString ) ;
               if( CondRetOrd != ORD_CondRetOK )
               {
                  return INT_CondRetErroAoImprimir ;
               } /* if */

               printf( "\t[ %d ] %s\n" , i + 1 , ordenadaString) ; 
            } 

         /* Exibe a única coluna de extras */
           
            else if( i == 4 ) {
               printf( "\nEXTRAS\n" ) ;
               pExtAux = ( EXT_tppExtras ) LIS_ObterValor( pMesa ) ;
                  
               CondRetExt = EXT_ConverterParaString( pExtAux ,
                               extrasString ) ;
                  
               if( CondRetExt != EXT_CondRetOK )
               {
                  return INT_CondRetErroAoImprimir ;
               } /* if */

               printf( "\t%s\n" , extrasString ) ;
            }

         /* Exibe as 8 colunas de visiveis */
            
            else {
               pVisAux = ( VIS_tppVisivel ) LIS_ObterValor( pMesa ) ;

               CondRetVis = VIS_ConverterParaString( pVisAux , 
                               visivelString ) ;
               
               if( CondRetVis != VIS_CondRetOK )
               {
                  return INT_CondRetErroAoImprimir ;
               } /* if */

               printf( "\t[ %d ] %s\n" , i - 4 , visivelString ) ;
            } /* if */

         /* Avança para a próxima coluna do jogo */

            CondRetLis = LIS_AvancarElementoCorrente( pMesa , 1 ) ;
            if( CondRetLis != LIS_CondRetOK )
            {
               return INT_CondRetErroAoImprimir ;
            } /* if */ 
      }

      return INT_CondRetOK ;

   } /* Fim função: INT  &Exibir mesa */

/***************************************************************************
*
*  Função: INT  &Obter comando
*  ****/

   INT_tpCondRet INT_ObterComando( char * idOrigem  , int * codOrig ,  
                                   char * idDestino , int * codDest  )  
   {

      char comando       [ INT_DIM_STRING ] ;
      char colunaOrigem  [ INT_DIM_STRING ] ;
      char colunaDestino [ INT_DIM_STRING ] ;

      scanf( " %s" , comando ) ;

   /* Usuário quer sair do jogo */

      if( strcmp( comando , "quit" ) == 0 )
      {
         *codDest = INT_COD_SAIR ;
         *codOrig = INT_COD_SAIR ;
      }

   /* Usuário quer mover uma carta */

      else if( strcmp( comando , "mov" ) == 0 )
      {
         scanf( " %s %s" , colunaOrigem , colunaDestino ) ;

      /* Verifica se a coluna origem e a destino atendem
            o formato da linguagem especificada (lembrando):
         - origem não pode ser ord
         - não sendo 'ord', origem tem que ter um único dígito
              numérico em sua 4 posição
         - destino, caso não seja ord, tem q ser: 'vis' ou 'ext',
              sufixadas por um único dígito numérico
       */
         
         if(  !ValidarColuna( colunaOrigem )
           || ( strstr( colunaDestino , "ord" ) == colunaDestino 
               && strlen( colunaDestino ) > 3 )
           || !ValidarColuna( colunaDestino ) )
         {
            return INT_CondRetComandoInvalido ;
         } /* if */

      /* Extrai as informações de movimentação */
         sscanf( colunaOrigem , " %[^0-9]" , idOrigem ) ;
         sscanf( colunaDestino , " %[^0-9]", idDestino ) ;

         *codOrig = colunaOrigem[ 3 ] - '0' ;

         if( strcmp( colunaDestino , "ord" ) == 0 )
         {
            *codDest = -1 ;
         }
         else
         {
            *codDest = colunaDestino[ 3 ] - '0' ;
         }
      } 

   /* Usuário entrou comando inválido */

      else 
      {
         return INT_CondRetComandoInvalido ;
      } /* if */
      

      return INT_CondRetOK;

   } /* Fim função: INT  &Obter Comando */




/***************************************************************************
*
*  Função: INT  &Exibir Mensagem
*  ****/
   INT_tpCondRet INT_ExibirMensagem( INT_tpMensagem mensagem ) 
   {
      
      switch( mensagem ) {
         case INT_MensagemOK :
            printf( "Movimento efetuado com sucesso!" ) ;
            break ;
         case INT_MensagemEntrada :
            printf( "MODO DE JOGAR  ____________________________________\n"
                    "Para jogar utilize os seguintes comandos:\n"
                    " quit : para sair"
                    " mov col num col num : para mover entre colunas\n"
                    "  col tem que ser:"
                    "       vis (para coluna visivel )\n"
                    "       ext (para espaco extra   )\n"
                    "       ord (para ordenadas      )\n"
                    "  'vis' e 'ext' devem sempre ser imediatamente\n"
                    "    seguidas de digito numerico, que indica: \n"
                    "     -> 'vis': id da coluna origem/destino\n"
                    "     -> 'ext': codigo do espaco extra\n"
                    "   'ord' so' pode aparecer como destino.\n"
                    "   ex: mov vis2 vis4\n"
                    "       mov vis4 ord\n"
                    "       mov vis5 ext2\n") ;
            break ;
         case INT_MensagemComandoInvalido :
            printf( "O comando efetuado nao existe.\n" ) ;
            break ;
         case INT_MensagemMovimentoInvalido :
            printf( "Movimento nao pode ser feito!\n" ) ;
            break ;
         case INT_MensagemEntrarComando :
            printf( "Entre comando: ") ;
            break ;
         case INT_MensagemFimJogoVitoria :
            printf( "Voce venceu! :D\n" ) ;
            break ;
         case INT_MensagemFimJogoDerrota :
            printf( "Voce perdeu! Fim de Jogo. :( \n" ) ;
            break ;
         default :
            return INT_CondRetErroParm ;
      } /* switch */

      return INT_CondRetOK ;

   } /* Fim função: INT  &Exibir mensagem */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: INT  -Validar coluna
*
*  $ED Descrição da função
*     Verifica se uma coluna de entrada do tipo 'vis' ou 'ext' está no
*        formato correto.
*
***********************************************************************/


   int ValidarColuna( char * coluna )
   {

      if (  strlen( coluna )  == 4
         && (   ( strstr( coluna , "vis" ) == coluna 
                 && coluna[ 3 ] >= '1' 
                 && coluna[ 3 ] <= '8' )
             || ( strstr( coluna , "ext" ) == coluna
                 && coluna[ 3 ] >= '1' 
                 && coluna[ 3 ] <= '4' )))
      {
         return 1 ;
      } 

      return 0 ;

   } /* Fim função: LIS  -Validar coluna */

/********** Fim do módulo de implementação: INT  Interface **********/