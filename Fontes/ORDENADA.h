#if ! defined( ORDENADA_ )
#define ORDENADA_

/***************************************************************************
*
*  $MCD Módulo de definição: ORD  Sequência Ordenada
*
*  Arquivo gerado:              ORDENADA.h
*  Letras identificadoras:      ORD
*
*  Nome da base de software:    Trabalho 2 de Programação Modular
*  Arquivo da base de software: ORDENADA/ORDENADA.h
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gss
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data      Observações
*     1       gss   12/out/2013  início do desenvolvimento
*
*  $ED Descrição do módulo
*    Implementa uma instância de uma lista de cartas ordenadas. Cada lista é
*       ordenada crescentemente, começando do ás e terminando no Rei,
*       totalizando quatro listas, uma para cada naipe.    
*       Chama-se de 'topo' de uma sequência ordenada o último elemento da lista. 
*
***************************************************************************/

#if defined( ORDENADA_OWN )
   #define ORDENADA_EXT
#else
   #define ORDENADA_EXT extern
#endif

#include "CARTA.H"

#define ORD_MAX_DIM_CARTAS  13
        /* Quantidade de cartas */
#define ORD_DIM_STRING     (( ORD_MAX_DIM_CARTAS * ( CAR_DIM_STRING - 1 )) \
                            + ( ORD_MAX_DIM_CARTAS ))
        /* Tamanho da string que representa as listas ordenadas */

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista ordenada */

typedef struct ORD_tagOrdenada * ORD_tppOrdenada ;

/***********************************************************************
*
*  $TC Tipo de dados: ORD Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do módulo ORDENADA
*
***********************************************************************/

   typedef enum {

         ORD_CondRetOK ,
               /* Concluiu corretamente */

         ORD_CondRetNaoOK ,
               /* Não concluiu corretamente */

         ORD_CondRetFaltouMemoria ,
               /* Faltou memória ao tentar criar um elemento */
         
         ORD_CondRetCartaInvalida ,
               /* Operação não permitida para a carta em questão */

         ORD_CondRetErroParm 
              /* Um dos parâmetros fornecidos é inválido */


   } ORD_tpCondRet ;


/***********************************************************************
*
*  $FC Função: ORD  &Criar lista ordenada
*
*  $ED Descrição da função
*     Cria uma instância de lista ordenada para que se armazene cartas
*      de um determinado naipe em ordem crescente
*        
*
*  $FV Valor retornado
*     Se executou corretamente retorna um ponteiro para a lista ordenada.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*        a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
*  $AS Assertivas de Saída:
*		pOrdenada != NULL
*
***********************************************************************/

   ORD_tppOrdenada ORD_CriarOrdenada( ) ;


/***********************************************************************
*
*  $FC Função: ORD  &Destruir lista ordenada
*
*  $ED Descrição da função
*     Destroi a lista ordenada passada pelo usuário.
*
*  $EP Parâmetros
*     pOrdenada  - ponteiro para a lista ordenada a ser destruída. 
*
*  $AE Assertivas de Entrada:
*		pOrdenada != NULL
*  $AS Assertivas de Saída:
*		Se a função for executada corretamente, a ordenada em questão terá sido
*		 destruída.
*
***********************************************************************/

   void ORD_DestruirOrdenada( ORD_tppOrdenada pOrdenada ) ;

/***********************************************************************
*
*  $FC Função: ORD  Inserir carta em sequência ordenada
*
*  $ED Descrição da função
*     Insere uma instância de carta no final de uma instância de lista
*        ordenada. A carta precisa ser do mesmo naipe que as cartas da lista
*        e precisa sucessora da última carta inserida na lista. 
*
*  $EP Parâmetros
*     pOrdenada - ponteiro para uma lista ordenada
*     pCarta    - ponteiro para a carta que se está tentando inserir
*
*  $FV Valor retornado
*     ORD_CondRetOK            - inserção OK
*     ORD_CondRetCartaInvalida - A carta em questão não pode ser inserida
*                                nessa lista/posição
*     ORD_CondRetFaltouMemoria - memória insuficiente
*
*  $AE Assertivas de Entrada:
*		pOrdenada != NULL
*		pCarta != NULL
*
*  $AS Assertivas de Saída:
*		Se a função retorna ORD_CondRetOK, a carta em questão foi inserida
*      com sucesso no topo da sequência ordenada.
*		Caso contrário, se a função retorna ORD_CondRetCartaInvalida, 
*      ORD_CondRetParm ou ORD_CondRetFaltouMemoria, nada foi modificado.
*
***********************************************************************/

   ORD_tpCondRet ORD_InserirCarta( ORD_tppOrdenada pOrdenada ,
                                   CAR_tppCarta pCarta        ) ;

/***********************************************************************
*
*  $FC Função: ORD  &Obter Topo

*  $ED Descrição da função
*     Retorna um ponteiro para a carta no topo.
*     Se a carta não existir na lista retorna NULL.
*
*  $EP Parâmetros
*     pOrdenada - ponteiro para uma lista ordenada
*     
*
*  $FV Valor retornado
*     Ponteiro para o elemento pedido.
*     NULL se não contiver nenhuma carta
*    
*  $AE Assertivas de Entrada:
*		pOrdenada != NULL
*
*  $AS Assertivas de Saída:
*		Se a função for executada com sucesso, retornará um ponteiro para
*	 	 estrutura do tipo carta, contendo a carta do topo da ordenada.
*		Caso contrário, retornará o valor NULL.
***********************************************************************/
   
   CAR_tppCarta ORD_ObterTopo( ORD_tppOrdenada pOrdenada ) ;

/***********************************************************************
*
*  $FC Função: ORD  &Transformar a lista ordenada em uma string
*
*  $ED Descrição da função
*     Modifica o conteúdo referenciado por ordenadaString, fazendo-no 
*        ser composto pela concatenação das strings que representam
*        cada uma das cartas que ocupam a lista ordenada dada.
*     As representações das cartas encontram-se separadas uma a uma
*        por um caractere espaço (' ').
*     
*     A string recebida tem que ter no mínimo capacidade de salvar
*        ORD_DIM_STRING caracteres.        
*     A string é terminada com o caractere '\0'.
*
*  $EP Parâmetros
*     pOrdenada      - ponteiro para lista ordenada
*     ordenadaString - ponteiro para a string que representará 
*                    a lista ordenada
*
*  $FV Valor retornado
*     ORD_CondRetOK     - a string foi construída com sucesso
*     ORD_CondRetNaoOK  - a string não foi construída com sucesso
*
*  $AE Assertivas de Entrada:
*		pOrdenada != NULL
*		ordenadaString != NULL
*   dimensao(ordenadaString) == ORD_DIM_STRING
*
*  $AS Assertivas de Saída:
*		Se a condição retornada for CondRetOK, a string terá sido corretamente
*	 	 gerada, e será formada pela concatenação das strings representativas
*	 	 de cada carta, separadas por ' '.
*		Caso contrário, a string permanece vazia.
*	
*
***********************************************************************/

   ORD_tpCondRet ORD_ConverterParaString( ORD_tppOrdenada pOrdenada , 
                                          char * ordenadaString      ) ;

/***********************************************************************
*
*  $FC Função: ORD  &Obter numero de cartas
*
*  $ED Descrição da função
*     Retorna o numero de cartas na coluna de ordenadas
*
*  $EP Parâmetros
*     pOrdenada - ponteiro para a coluna de ordenadas cujo numero de 
*                   cartas deseja-se saber.
*
*  $FV Valor retornado
*    Retorna o número de cartas na coluna de ordenadas
*     
*
***********************************************************************/
   
   int ORD_ObterNumeroCartas( ORD_tppOrdenada pOrdenada );


#undef ORDENADA_EXT

/********** Fim do módulo de definição: ORD  Módulo de Sequência Ordenada **********/

#else
#endif