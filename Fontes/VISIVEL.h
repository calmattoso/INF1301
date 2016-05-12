#if ! defined( VISIVEL_ )
#define VISIVEL_

/***************************************************************************
*
*  $MCD Módulo de definição: VIS  Sequência Visível
*
*  Arquivo gerado:              VISIVEL.h
*  Letras identificadoras:      VIS
*
*  Nome da base de software:    Trabalho 2 de Programação Modular
*  Arquivo da base de software: VISIVEL/VISIVEL.h
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gss
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data      Observações
*     1       gss   13/out/2013  início do desenvolvimento
*
*  $ED Descrição do módulo
*    Implementa uma instância de uma sequencia visível. Cada lista é inicializada
*       com 7 ou 8 cartas, embaralhadas. Após o início do jogo, as cartas só podem ser
*       removidas da lista se puderem ser inseridas em outra instância de sequência
*       visível, numa instância de sequência ordenada, ou num espaço extra. Uma carta
*       apenas pode ser inserida no topo de uma sequência visível. A condição para que
*       isso seja possível é que a carta seja de cor diferente e valor uma unidade maior
*       que a carta presente no topo da sequência.    
*		Chama-se de 'topo' de uma sequência visível o último elemento da lista. 
*
***************************************************************************/

#if defined( VISIVEL_OWN )
    #define VISIVEL_EXT
#else
    #define VISIVEL_EXT extern
#endif

#include "CARTA.h"

#define VIS_MAX_DIM_CARTAS  19
            /* Quantidade de cartas */
#define VIS_DIM_STRING     (( VIS_MAX_DIM_CARTAS * ( CAR_DIM_STRING - 1 )) \
                              + ( VIS_MAX_DIM_CARTAS )) 
            /* Tamanho máximo da string que representa uma sequência visível */


/***** Declarações exportadas pelo módulo *****/


/* Tipo referência para uma sequência visível */

typedef struct VIS_tagVisivel * VIS_tppVisivel ;

/***********************************************************************
*
*  $TC Tipo de dados: VIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do módulo VISIVEL
*
***********************************************************************/

   typedef enum {

      VIS_CondRetOK ,
            /* Concluiu corretamente */

      VIS_CondRetNaoOK ,
            /* Não concluiu corretamente */

      VIS_CondRetFaltouMemoria ,
            /* Faltou memória ao tentar criar um elemento */
             
      VIS_CondRetCartaInvalida ,
            /* Operação não permitida para a carta em questão */

      VIS_CondRetModoInvalido ,
            /* Modo selecionado é inválido */

      VIS_CondRetListaVazia ,
            /* A lista referenciada está vazia */

      VIS_CondRetErroParm 
            /* Um dos parâmetros fornecidos é inválido */

    } VIS_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: VIS Modos de inserção
*
*
*  $ED Descrição do tipo
*     Modos para inserção em lista visível
*
***********************************************************************/

   typedef enum {

      VIS_ModoComOrdem ,
            /* Insere respeitando as regras de inserção */

      VIS_ModoSemOrdem
            /* Insere sem critérios */

    } VIS_tpModo ;   

/***********************************************************************
*
*  $FC Função: VIS  Criar Visivel
*
*  $ED Descrição da função
*     Cria uma lista visível vazia e retorna um ponteiro para ela.
*
*  $FV Valor retornado
*     Um ponteiro para lista visivel.
*     NULL se houve falha na alocação.
*
*  $AS Assertivas de Saída:
*     pOrdenada != NULL
*
***********************************************************************/
      
   VIS_tppVisivel VIS_CriarVisivel( void ) ;

/***********************************************************************
*
*  $FC Função: VIS  &Destruir Visivel
*
*  $ED Descrição da função
*     Destroi a sequência visível passada pelo usuário.
*
*  $EP Parâmetros
*     pVisivel - ponteiro para lista visivel
*
*  $AE Assertivas de Entrada:
*     pVisivel != NULL
*  $AS Assertivas de Saída:
*     Se a função for executada corretamente, a lista visivel em questão terá sido
*      destruída.
*
***********************************************************************/
      
   void VIS_DestruirVisivel( VIS_tppVisivel pVisivel ) ;

/***********************************************************************
*
*  $FC Função: VIS  &Inserir Carta em sequência visível
*
*  $ED Descrição da função
*     Recebe um ponteiro para lista visível, um ponteiro para carta e
*     um modo de inserção. Então, chama a função de inserção específica
*     para o modo escolhido.
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
*
*  $AE Assertivas de Entrada:
*     pVisivel != NULL
*     pCarta   != NULL
*     modo deve estar dentre os tipos especificados por VIS_tpModo
*
*  $AS Assertivas de Saída:
*     Se a função retorna CondRetOK, a carta em questão foi inserida com
*      sucesso no topo da visível. pvisível aponta para a nova carta inserida.
*     Caso contrário, se a função retorna ORD_CondRetParm ou ORD_CondRetFaltouMemoria,
*      nada foi modificado.
***********************************************************************/

   VIS_tpCondRet VIS_InserirCarta( VIS_tppVisivel pVisivel , 
                                   CAR_tppCarta pCarta ,
                                   VIS_tpModo modo          ) ;

/***********************************************************************
*
*  $FC Função: VIS  &Remover Carta de sequência visivel
*
*  $ED Descrição da função
*     Retira a carta do topo da lista. Não faz nada se a lista for vazia.
*
*  $EP Parâmetros
*     pVisivel - ponteiro para uma lista visivel
*
*  $FV Valor retornado
*     VIS_CondRetOK - Removeu corretamente
*     VIS_CondRetListaVazia - A lista estava vazia.
*     
*  $AE Assertivas de Entrada:
*     pVisivel != NULL
* 
*  $AS Assertivas de Saída:
*     Se a função retorna CondRetOK, o elemento presente no fim da lista
*      visível terá sido removido, e pVisível apontará pro elemento anterior.
*     Caso contrário, a lista não é modificada.
*
***********************************************************************/
   
   VIS_tpCondRet VIS_RemoverCarta( VIS_tppVisivel pVisivel ) ;

/***********************************************************************
*
*  $FC Função: VIS  &Obter Carta Posicao 

*  $ED Descrição da função
*     Retorna um ponteiro para a carta a uma determinada distância do topo.
*     Se a posição não existir na lista retorna NULL.
*
*  $EP Parâmetros
*     pVisivel - ponteiro para uma lista visivel
*     posicao - posição do elemento
*
*  $FV Valor retornado
*     Ponteiro para o elemento pedido.
*     NULL se na posição não contiver nenhuma carta
*  
*  $AE Assertivas de Entrada:
*     pVisivel != NULL
*     posicao >= 0 
*     
*  $AS Assertivas de Saída:
*     Se a função for executada com sucesso, retornará um ponteiro para
*      estrutura do tipo carta, contendo a carta presente na posição especificada.
*     Caso contrário, retornará o valor NULL.
*
***********************************************************************/
   
   CAR_tppCarta VIS_ObterCartaPosicao( VIS_tppVisivel pVisivel ,
                                       int posicao              ) ;


/***********************************************************************
*
*  $FC Função: VIS  &Transformar UMA lista visivel em uma string
*
*  $ED Descrição da função
*     Modifica o conteúdo referenciado por visivelString, fazendo-no 
*        ser composto pela concatenação das strings que representam
*        cada uma das cartas que ocupam a lista visivel dada.
*     As representações das cartas encontram-se separadas uma a uma
*        por um caractere espaço (' ').
*     
*     A string recebida tem que ter no mínimo capacidade de salvar
*        VIS_DIM_STRING caracteres.        
*     A string é terminada com o caractere '\0'.
*
*  $EP Parâmetros
*     pVisivel      - ponteiro para lista Visivel
*     visivelString - ponteiro para a string que representará 
*                     a lista Visivel
*
*  $FV Valor retornado
*     VIS_CondRetOK     - a string foi construída com sucesso
*     VIS_CondRetNaoOK  - a string não foi construída com sucesso
*
*  $AE Assertivas de Entrada:
*     pVisivel != NULL
*     visivelString != NULL
*     dimensao(visivelString) == VIS_DIM_STRING
*
*  $AS Assertivas de Saída:
*    Se a condição retornada for CondRetOK, a string terá sido corretamente
*    gerada, e será formada pela concatenação das strings representativas
*    de cada carta, separadas por ' '.
*   Caso contrário, a string permanece vazia.
* 
*
***********************************************************************/

   VIS_tpCondRet VIS_ConverterParaString( VIS_tppVisivel pVisivel , 
                                          char * visivelString     ) ; 

#undef VISIVEL_EXT

/*** Fim do módulo de definição: VIS  Sequência Visível *****/

#else
#endif
