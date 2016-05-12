#if ! defined( LISTA_INSTR )
#define LISTA_INSTR
/***************************************************************************
*
*  $MCD Módulo de definição: LIS_INSTR  Lista duplamente encadeada instrumentado
*
*  Arquivo gerado:              LISTA_INSTR.h
*  Letras identificadoras:      LIS_INSTR
*
*  Nome da base de software:    Trabalho 4 de Programação Modular
*  Arquivo da base de software: .../LISTA/FONTES
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gss
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data      Observações
*     1       gss   12/nov/2013  início da instrumentação
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_INSTR_OWN )
   #define LISTA_INSTR_EXT
#else
   #define LISTA_INSTR_EXT extern
#endif

#include "LISTA.h"

/***** Declarações exportadas pelo módulo *****/


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   LIS_tppLista LIS_CriarListaInstr(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   void LIS_DestruirListaInstr( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

   void LIS_EsvaziarListaInstr( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntesInstr( LIS_tppLista pLista ,
                                                void * pValor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAposInstr( LIS_tppLista pLista ,
                                               void * pValor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElementoInstr( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     não NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

   void * LIS_ObterValorInstr( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void IrInicioListaInstr( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void IrFinalListaInstr( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrenteInstr( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara ponteiro e não conteúdo apontado.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValorInstr( LIS_tppLista pLista ,
                                         void * pValor        ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Obter numero elementos
*
*  $ED Descrição da função
*     Retorna o numero de elementos na lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista onde se quer descobrir o numero
*           de elementos
*
*  $FV Valor retornado
*    Retorna o número de elementos na lista
*     
*
***********************************************************************/
   
   int LIS_ObterNumeroElementosInstr( LIS_tppLista pLista );

#ifdef _DEBUG

/***********************************************************************
*
*  $FC Função: LIS  &Verificar Lista
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica primeiramente a integridade da cabeça da lista. 
*     Posteriormente, itera sobre os elementos da lista verificando
*        não apenas sua integridade, mas também se respeitam às assertivas
*        estruturais da lista duplamente encadeada.
*
*  $EP Parâmetros
*     pLista  - Ponteiro para a lista à ser verificada
*
*  $FV Valor retornado
*     LIS_CondRetOK              - Lista está íntegra e obedece a todas
*                                     assertivas estruturais.
*     LIS_CondRetErroEstrutura  -  Lista apresenta algum erro de integridade
*                                     ou desobedece alguma assertiva estrutural 
*  
***********************************************************************/

   LIS_tpCondRet LIS_VerificarListaInstr( LIS_tppLista pLista );

#endif

#ifdef _DEBUG

/***********************************************************************
*
*  $FC Função: LIS  &Deturpar Lista
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Corrompe elementos específicos da estrutura da lista.
*     Essa função destina-se a preparar os cenários de teste dos
*     casos de teste utilizados ao testar os verificadores estruturais
*     da lista.
*     Esta função não tem proteção contra erros de uso, consequentemente
*     poderá levar o programa a ser cancelado pelo sistema operacional.
*
*  $EP Parâmetros
*     pLista         - lista à ser deturpada
*     modoDeturpacao - identifica como deve ser feita a deturpação
*                         LIS_tpModosDeturpacao identifica os modos de
*                         deturpação conhecidos
*
*  $FV Valor retornado
*     TST_CondRetOK   - Deturpação realizada com sucesso
*     TST_CondRetParm - Modo de deturpação desconhecido
*  
***********************************************************************/


   void LIS_DeturparListaInstr( LIS_tppLista * pLista      , 
                                LIS_tpModosDeturpacao modoDeturpacao );

#endif

#if !defined( LISTA_INSTR_OWN )
   #define  LIS_CriarLista               LIS_CriarListaInstr
   #define  LIS_DestruirLista            LIS_DestruirListaInstr
   #define  LIS_EsvaziarLista            LIS_EsvaziarListaInstr
   #define  LIS_InserirElementoAntes     LIS_InserirElementoAntesInstr
   #define  LIS_InserirElementoApos      LIS_InserirElementoAposInstr
   #define  LIS_ExcluirElemento          LIS_ExcluirElementoInstr
   #define  LIS_ObterValor               LIS_ObterValorInstr
   #define  IrInicioLista                IrInicioListaInstr
   #define  IrFinalLista                 IrFinalListaInstr
   #define  LIS_AvancarElementoCorrente  LIS_AvancarElementoCorrenteInstr
   #define  LIS_ProcurarValor            LIS_ProcurarValorInstr
   #define  LIS_ObterNumeroElementos     LIS_ObterNumeroElementosInstr
   #define  LIS_VerificarLista           LIS_VerificarListaInstr
   #define  LIS_DeturparLista            LIS_DeturparListaInstr
#endif   

#undef LISTA_INSTR_EXT

/********** Fim do módulo de definição: LIS_INSTR  Lista duplamente encadeada instrumentado **********/

#else
#endif
