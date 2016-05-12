#if ! defined( EXTRAS_ )
#define EXTRAS_

/***************************************************************************
*
*  $MCD Módulo de definição: EXT  Espaços extras do jogo
*
*  Arquivo gerado:              EXTRAS.h
*  Letras identificadoras:      EXT
*
*  Nome da base de software:    Trabalho 2 de Programação Modular
*  Arquivo da base de software: C:\Users\Carlos\Skydrive\PUC\INF1301
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: clm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data      Observações
*     1       clm   12/out/2013  início do desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa a sequência de 4 (EXT_DIM_EXTRAS) espaços extras do jogo,
*        nos quais pode-se armazenar uma carta em cada um.
*     Embora no contexto do Freecell exista apenas uma sequência de espaços
*        extras, este módulo permite a criação de n sequências.
*     
*     A quantidade de espaços extras livres interfere no número de cartas
*        que podem ser movidas de uma só vez. Portanto, a quantidade de 
*        espaços ocupados é externada.
*
***************************************************************************/

#if defined( EXTRAS_OWN )
   #define EXTRAS_EXT
#else
   #define EXTRAS_EXT extern
#endif

#include "CARTA.h"

#define EXT_DIM_EXTRAS  4
        /* Quantidade de espaços extras */
#define EXT_DIM_STRING  (( EXT_DIM_EXTRAS * ( CAR_DIM_STRING - 1 )) \
                         + ( EXT_DIM_EXTRAS ))
        /* Tamanho da string que representa os espaços extras */
#define EXT_POS_VAZIA  '-'
        /* Usado para construir a representação de uma posição vazia */

#ifdef _DEBUG
  #define EXT_ERRO_PARM  -1
        /* Valor retornado por EXT_ObterNumeroEspacosOcupados caso o 
           parâmetro esteja incorreto */
#endif


/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma sequência de espaços extras */

typedef struct EXT_tagExtras * EXT_tppExtras ;

/***********************************************************************
*
*  $TC Tipo de dados: EXT Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do módulo EXTRAS
*
***********************************************************************/

   typedef enum {

         EXT_CondRetOK ,
               /* Concluiu corretamente */

         EXT_CondRetFaltouMemoria ,
               /* Faltou memória ao tentar inserir uma carta */

         EXT_CondRetPosicaoInvalida ,
               /* Posição inválida para certa operação */

         EXT_CondRetExtrasLotados ,
               /* Todos os espaços extras estão ocupados */

         EXT_CondRetExtrasVazios ,
              /* Todos os espaços extras estão vazios */

         EXT_CondRetFimExtras ,
             /* Atingiu o fim dos espaços extras antes do desejado */

         EXT_CondRetErroParm 
              /* Algum parâmetro não atende uma assertiva de entrada */

   } EXT_tpCondRet ;

/***********************************************************************
*
*  $FC Função: EXT  &Criar espaços extras
*
*  $ED Descrição da função
*     Retorna um ponteiro para os quatro espaços extras criados.
*
*  $FV Valor retornado
*     Se executou corretamente retorna um ponteiro para 
*     os espaços extras.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
*  $AE Assertivas de entrada:
*
*  $AS Assertivas de saida:
*		  Se executada corretamente, EXT_tppExtras é um ponteiro para os 
*		  espaços extras.
*	
***********************************************************************/

   EXT_tppExtras EXT_CriarExtras( void ) ;


/***********************************************************************
*
*  $FC Função: EXT  &Destruir espaços extras
*
*  $ED Descrição da função
*     Destroi os espaços extras
*
*  $EP Parâmetros
*     pExtras  - ponteiro para os espaços extras
*                Não pode ser NULL. 
*	
*  $AE Assertivas de entrada:
*		pExtras != NULL
*
*
***********************************************************************/

   void EXT_DestruirExtras( EXT_tppExtras pExtras ) ;

/***********************************************************************
*
*  $FC Função: EXT  &Obter numero de espaços ocupados
*
*  $ED Descrição da função
*     Retorna o número de espaços extras ocupados
*
*  $EP Parâmetros
*     pExtras    - ponteiro para os espaços extras.
*                  Não pode ser NULL.
*
*  $FV Valor retornado
*          inteiro         - se pExtras não for NULL, é o número de 
*                            espaços extras ocupados. 
*                            Este valor é maior ou igual a 0 e menor ou
*                            igual a EXT_DIM_EXTRAS.
*          EXT_ERRO_PARM   - se pExtras for NULL
* 
*  $AE Assertivas de entrada:
*		pExtras != NULL
*
*  $AS Assertivas de saída:
*		O inteiro retornado corresponde ao número de espaços extras ocupados.
*		0 <= inteiro <= EXT_DIM_EXTRAS
*
***********************************************************************/

   int EXT_ObterNumeroEspacosOcupados( EXT_tppExtras pExtras ) ;

/***********************************************************************
*
*  $FC Função: EXT  &Inserir carta
*
*  $ED Descrição da função
*     Insere a carta passada em um dos espaços extras livres, caso
*        haja algum. 
*
*  $EP Parâmetros
*     pExtras - ponteiro para os espaços extras.
*               Não pode ser NULL
*     pCarta  - ponteiro para a carta a ser inserida.
*               Não pode ser NULL
*     posicao - posição onde a carta deve ser inserida na sequência
*               de espaços extras.
*
*  $FV Valor retornado
*     EXT_CondRetOK              - se foi possível inserir a carta
*     EXT_CondRetExtrasLotados   - se não foi possível inserir a carta,
*                                  porque não há espaços extras livres
*     EXT_CondRetFaltouMemória   - se não foi possível inserir a carta,
*                                  por erros de alocação de memória
*     EXT_CondRetPosicaoInvalida - se o espaço extra associado à posição
*                                  passada já está ocupado
*     EXT_CondRetErroParm        - se algum parâmetro não atende uma 
*                                  assertiva de entrada 
*	
*  $AE Assertivas de Entrada:
*		pExtras != NULL
*		pCarta	!= NULL
*		1 <= posicao <= EXT_DIM_EXTRAS
*
*  $AS Assertivas de Saída:
*		Se EXT_tpCondRet == EXT_CondRetOK então a carta foi inserida 
*		corretamente no espaço extra.
*
*
***********************************************************************/

   EXT_tpCondRet EXT_InserirCartaPosicao( EXT_tppExtras pExtras , 
                                          CAR_tppCarta pCarta ,
                                          int posicao            ) ;

/***********************************************************************
*
*  $FC Função: EXT  &Remover carta em certa posição
*
*  $ED Descrição da função
*     Remove a carta que se encontra na posição especificada, caso tal
*        posição seja válida.
*    
*
*  $EP Parâmetros
*     pExtras   - ponteiro para os espaços extras.
*                 Não pode ser NULL.
*     posicao   - posição da carta na sequência de extras.
*                 Varia de 1 até EXT_DIM_EXTRAS (ambos inclusos).
*
*  $FV Valor retornado
*     EXT_CondRetOK              - se removeu com sucesso o elemento
*     EXT_CondRetFimExtras       - se atingiu o fim dos espaços extras 
*                                  antes de chegar na posição desejada
*     EXT_CondRetExtrasVazios    - se não há nenhuma carta nos espaços
*                                  extras  
*     EXT_CondRetPosicaoInvalida - se o espaço extra associado à posição
*                                  passada está vazio
*     EXT_CondRetErroParm        - se algum parâmetro não atende uma 
*                                  assertiva de entrada 
*
*  $AE Assertivas de Entrada:
*		pExtras != NULL
*		1 <= posicao <= EXT_DIM_EXTRAS
*
*  $AS Assertivas de Saída:
*		Se EXT_tpCondRet == EXT_CondRetOK o elemento foi removido
*		do espaço extra apontado.
***********************************************************************/

   EXT_tpCondRet EXT_RemoverCartaPosicao( EXT_tppExtras pExtras , 
                                         int posicao            ) ;

/***********************************************************************
*
*  $FC Função: EXT  &Obter carta em certa posição
*
*  $ED Descrição da função
*     Retorna a carta que se encontra na posição especificada, caso tal
*        posição seja válida.
*     Não será dada mais informação quanto ao problema ocorrido.
*    
*
*  $EP Parâmetros
*     pExtras   - ponteiro para os espaços extras
*                 Não pode ser NULL.
*     posicao   - posição da carta na sequência de extras.
*                 Varia de 1 até EXT_DIM_EXTRAS (ambos inclusos)
*
*  $FV Valor retornado
*     não NULL  - se a carta foi encontrada e retornada
*     NULL      - se não há carta na posicao passada, ou algum outro
*                 erro ocorreu.
*
*  $AE Assertivas de Entrada:
*		pExtras != NULL
*		1 <= posicao <= EXT_DIM_EXTRAS
*
*  $AS Assertivas de Saída:
*		CAR_tppCarta != NULL
***********************************************************************/

   CAR_tppCarta EXT_ObterCartaPosicao( EXT_tppExtras pExtras , 
                                       int posicao            ) ;

/***********************************************************************
*
*  $FC Função: EXT  &Transformar os espaços extras em uma string
*
*  $ED Descrição da função
*     Modifica o conteúdo referenciado por extrasString, fazendo-no 
*        ser composto pela concatenação das strings que representam
*        cada uma das cartas que ocupam os espaços extras.
*     As representações das cartas encontram-se separadas uma a uma
*        por um caractere espaço (' ').
*     
*     A string recebida tem que ter no mínimo capacidade de salvar
*        EXT_DIM_STRING caracteres. Este é o número de caracteres
*        necessários para a representação dos espaços extras quando
*        todos estão ocupados.        
*     A string é terminada com o caractere '\0'.
*
*  $EP Parâmetros
*     pExtras      - ponteiro para os espaços extras.
*                    Não pode ser NULL.
*     extrasString - ponteiro para a string que representará 
*                    os espaços extras.
*                    Recomenda-se usar EXT_DIM_STRING, o tamanho
*                    máximo que esta string pode ter ( caso em que
*                    os espaços extras estão lotados ).
*
*  $FV Valor retornado
*     EXT_CondRetOK        - a string foi construída com sucesso
*     EXT_CondRetNaoOK     - a string não foi construída com sucesso
*     EXT_CondRetErroParm  - se algum parâmetro não atende uma 
*                            assertiva de entrada (não verifica caso
*                            da string não ter o tamanho adequado).
*
*  $AE Assertivas de Entrada:
*		  pExtras != NULL
*		  extrasString != NULL
*     dimensao( extrasString ) == EXT_DIM_STRING
*
*	$AS Assertivas de Saída:
*		  Se o retorno foi EXT_CondRetOK a string foi construída com sucesso.
*
***********************************************************************/

   EXT_tpCondRet EXT_ConverterParaString( EXT_tppExtras pExtras , 
                                          char * extrasString    ) ; 


#undef EXTRAS_EXT

/********** Fim do módulo de definição: EXT  Espaços extras do jogo **********/

#else
#endif