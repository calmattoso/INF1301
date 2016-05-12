#if ! defined( CARTA_ )
#define CARTA_

/***************************************************************************
*
*  $MCD Módulo de definição: CAR  Carta de um baralho
*
*  Arquivo gerado:              CARTA.h
*  Letras identificadoras:      CAR
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
*     1       clm   11/out/2013  início do desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa uma carta de um baralho. 
*     Podem existir quantas cartas forem necessárias, embora
*        um baralho tenha apenas 52 ao total.
*     As cartas apresentam uma representação em string, sendo os cada 
*        componente dela (cor, naipe e rank) representada por um caractere.
*        Os caracteres que representam cada possível valor destas 
*        componentes encontram-se em seus respectivos enums.
*
***************************************************************************/

#if defined( CARTA_OWN )
   #define CARTA_EXT
#else
   #define CARTA_EXT extern
#endif

#define CAR_DIM_STRING  4

#ifdef _DEBUG
   #define CAR_PARM_INVALIDO  -1
         /* Usado para indicar parâmetro inválido no caso de
            retorno de algum tipo enum */
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma carta */

typedef struct CAR_tagCarta * CAR_tppCarta ;

/***********************************************************************
*
*  $TC Tipo de dados: CAR Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do módulo CARTA
*
***********************************************************************/

   typedef enum {

         CAR_CondRetOK ,
               /* Concluiu corretamente */

         CAR_CondRetIgual ,
               /* Os dois artefatos comparados são iguais */

         CAR_CondRetDiferente ,
               /* Os dois artefatos comparados são diferentes */

         CAR_CondRetMaior ,
               /* O primeiro artefato é maior que o segundo */

         CAR_CondRetSucessor ,
               /* O primeiro artefato vem imediatamente após
                  o segundo, em sua ordenação crescente natural */

         CAR_CondRetMenor ,
               /* O primeiro artefato é menor que o segundo */

         CAR_CondRetAntecessor ,
               /* O primeiro artefato vem imediatamente antes
                  do segundo, em sua ordenação crescente natural */
          
          CAR_CondRetErroParm 
              /* Algum parâmetro não atende uma assertiva de entrada */

   } CAR_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: CAR Naipes das cartas
*
*
*  $ED Descrição do tipo
*     Os possíveis naipes de uma carta, que dizem à qual partição do
*        baralho ela pertence assim como sua cor.
*
***********************************************************************/

   typedef enum {

         CAR_NaipePaus ,
               /* O naipe chamado paus. Char: P */

         CAR_NaipeEspadas ,
               /* O naipe chamado espadas. Char: E */

         CAR_NaipeCopas ,
               /* O naipe chamado copas. Char: C */

         CAR_NaipeOuros 
               /* O naipe chamado ouros. Char: O */

   } CAR_tpNaipe ;

/***********************************************************************
*
*  $TC Tipo de dados: CAR Cores das cartas
*
*
*  $ED Descrição do tipo
*     Cores associadas à uma carta segundo seu naipe. Assim, temos que:
*      - Se a carta for de Paus  ou Espadas, sua cor é Preta
*      - Se a carta for de Copas ou Ouros  , sua cor é Vermelha
*
***********************************************************************/

   typedef enum {

         CAR_CorVermelha ,
               /* Carta vermelha. Char: V */

         CAR_CorPreta 
               /* Carta preta. Char: P */

   } CAR_tpCor ;


/***********************************************************************
*
*  $TC Tipo de dados: CAR Rank das cartas
*
*
*  $ED Descrição do tipo
*     Os possíveis valores associados a uma carta. Estes valores são:
*        { 2, 3, 4, 5, 6, 7, 8, 9, 10, Valete, Rei, Rainha, Às }
*
*      Os valores apresentam um peso associado a eles, estando acima
*         exibidos em ordenação crescente. Assim, Às é o de maior
*         peso, enquanto 2 é o de menor.
*
*      O valor "Valete" é comumente representado por 'J', o valor 
*         "Rei" por 'K', o valor "Rainha" por 'Q' e o valor "Às" por
*         'A'.
*
***********************************************************************/

   typedef enum {

         CAR_RankAs ,
               /* O rank das cartas é Às. Char: A */

         CAR_RankDois ,
               /* O rank da carta é 2. Char: 2 */

         CAR_RankTres ,
               /* O rank das cartas é 3. Char: 3 */

         CAR_RankQuatro ,
               /* O rank das cartas é 4. Char: 4 */

         CAR_RankCinco ,
               /* O rank das cartas é 5. Char: 5 */

         CAR_RankSeis ,
               /* O rank das cartas é 6. Char: 6 */

         CAR_RankSete ,
               /* O rank das cartas é 7. Char: 7 */

         CAR_RankOito ,
               /* O rank das cartas é 8. Char: 8 */

         CAR_RankNove ,
               /* O rank das cartas é 9. Char: 9 */

         CAR_RankDez ,
               /* O rank das cartas é 10. Char: T */

         CAR_RankValete ,
               /* O rank das cartas é Valete. Char: J */

         CAR_RankRainha , 
               /* O rank das cartas é Rainha. Char: Q */

         CAR_RankRei 
               /* O rank das cartas é Rei. Char: K */

   } CAR_tpRank ;

/***********************************************************************
*
*  $FC Função: CAR  &Criar carta
*
*  $ED Descrição da função
*     Cria uma carta com o naipe e rank especificados pelo usuário.
*
*  $EP Parâmetros
*     naipe - valor do naipe da carta
*     rank  - valor do rank da carta
*
*  $FV Valor retornado
*     Se executou corretamente retorna um ponteiro para a carta.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*	
*  $AE Assertivas de Entrada:
*		naipe != NULL
*		rank  != NULL
*
*  $AS Assertivas de Saída:
*		Se a execução foi bem CAR_CondRetOK o retorno é um endereço de
*		memória de uma carta válida.
*
***********************************************************************/

   CAR_tppCarta CAR_CriarCarta( CAR_tpNaipe naipe , CAR_tpRank rank ) ;


/***********************************************************************
*
*  $FC Função: CAR  &Destruir carta
*
*  $ED Descrição da função
*     Destroi a carta passada pelo usuário.
*
*  $EP Parâmetros
*     pCarta  - ponteiro para a carta a ser destruída.
*
*  $AE Assertivas de Entrada:
*		pCarta != NULL	
*
*  $AS Assertivas de Saída:
*		Se a execução foi bem sucedida o conteúdo apontado por pCarta
*     terá sido limpo destruído.
*
***********************************************************************/

   void CAR_DestruirCarta( CAR_tppCarta pCarta ) ;

/***********************************************************************
*
*  $FC Função: CAR  &Obter naipe da carta
*
*  $ED Descrição da função
*     Retorna o naipe da carta.
*
*  $EP Parâmetros
*     pCarta   - ponteiro para a carta.
*                Não pode ser NULL.
*
*  $FV Valor retornado
*     CAR_NaipeEspadas
*     CAR_NaipePaus
*     CAR_NaipeCopas
*     CAR_NaipeOuros
*
*  $AE Assertivas de Entrada:
*		pCarta != NULL
*
*  $AS Assertivas de Saída:
*		Se a execução for bem sucedida e o retorno corresponde ao naipe
*		da pCarta.
*
***********************************************************************/

   CAR_tpNaipe CAR_ObterNaipe( CAR_tppCarta pCarta ) ;

/***********************************************************************
*
*  $FC Função: CAR  &Comparar naipes de duas cartas
*
*  $ED Descrição da função
*     Compara os naipes das duas cartas fornecidas pelo usuário, 
*        retornando se eles são iguais ou diferentes.
*
*  $EP Parâmetros
*     pCartaA   - ponteiro para a primeira carta.
*                 Não pode ser NULL.
*     pCartaB   - ponteiro para a segunda carta 
*                 Não pode ser NULL.
*
*  $FV Valor retornado
*     CAR_CondRetIgual      - se o naipe de pCartaA for igual ao naipe
*                             de pCartaB
*     CAR_CondRetDiferente  - se o naipe de pCartaA for diferente do
*                             naipe de pCartaB
*     CAR_CondRetErroParm   - se algum parâmetro não atende uma 
*                             assertiva de entrada 
*  $AE Assertivas de Entrada:
*		pCartaA != NULL
*		pCartaB != NULL
*
*  $AS Assertivas de Saída:
*		Se a execução for bem sucedida:
*		retornará CAR_CondRetIgual quando o 
*		naipe da pCartaA == naipe da pCartaB.
*		Retornará CAR_CondRetDiferente quando o 
*		naipe da pCartaA != naipe da pCartaB.
*
***********************************************************************/

   CAR_tpCondRet CAR_CompararNaipe( CAR_tppCarta pCartaA , 
                                    CAR_tppCarta pCartaB  ) ;

/***********************************************************************
*
*  $FC Função: CAR  &Comparar ranks de duas cartas
*
*  $ED Descrição da função
*     Compara os ranks das duas cartas fornecidas pelo usuário, 
*        retornando se o rank da primeira é maior, sucessor, igual,
*        antecessor ou igual ao rank da segunda.
*
*     O rank sucessor a um rank R, é aquele que vem imediatamente 
*       após de R na ordenação crescente dos ranks.
*     O rank antecessor a um rank R, é aquele que vem imediatamente 
*        antes de R na ordenação crescente dos ranks.
*     
*     A ordenação crescente dos ranks foi especificada previamente
*        na declaração do tipo CAR_tpRank.
*
*
*  $EP Parâmetros
*     pCartaA - ponteiro para a primeira carta.
*               Não pode ser NULL.
*     pCartaB - ponteiro para a segunda carta
*               Não pode ser NULL.
*
*  $FV Valor retornado
*     CAR_CondRetMaior       - se o rank de pCartaA for maior que
*                              o rank de pCartaB
*     CAR_CondRetSucessor    - se o rank de pCartaA for o sucessor do
*                              rank da pCartaB, com relação à ordenação
*                              crescente dos ranks
*     CAR_CondRetIgual       - se o rank de pCartaA for igual ao
*                              rank de pCartaB
*     CAR_CondRetAntecessor  - se o rank de pCartaA for o antecessor do
*                              rank da pCartaB, com relação à ordenação
*                              crescente dos ranks
*     CAR_CondRetMenor       - se o rank de pCartaA for menor que
*                              o rank de pCartaB
*     CAR_CondRetErroParm    - se algum parâmetro não atende uma 
*                              assertiva de entrada 
*
*  $AE Assertivas de Entrada:
*		pCartaA != NULL
*		pCartaB != NULL
*
*  $AS Assertivas de Saída:
*		Se a execução for bem sucedida:
*		Retornará CAR_CondRetIgual quando o rank da pCartaA == rank da pCartaB.
*		
*		Retornará CAR_CondRetSucessor se o rank de pCartaA for sucessor 
*     do rank da pCartaB.
*		
*		Retornará CAR_CondRetAntecessor se o rank de pCartaA for antecessor
*     do rank de pCartaB.
*		
*		Retornará CAR_CondRetMenor ser o rank da pCartaA for menor que o rank
*		da pCartaB.
*
*		Retornará CAR_CondRetMaior se o rank da pCartaA for maior que o rank
*		da pCartaB.
***********************************************************************/

   CAR_tpCondRet CAR_CompararRank( CAR_tppCarta pCartaA , 
                                   CAR_tppCarta pCartaB  ) ;

/***********************************************************************
*
*  $FC Função: CAR  &Comparar cores de duas cartas
*
*  $ED Descrição da função
*     Compara as cores das duas cartas fornecidas pelo usuário, 
*        retornando se ambas são iguais ou diferentes.
*     
*     A associação de cores à cartas foi especificada previamente na
*        declaração do tipo CAR_tpCor.
*
*
*  $EP Parâmetros
*     pCartaA - ponteiro para a primeira carta.
*               Não pode ser NULL.
*     pCartaB - ponteiro para a segunda carta 
*               Não pode ser NULL.
*
*  $FV Valor retornado
*     CAR_CondRetIgual      - se a cor de pCartaA for igual ao naipe
*                             de pCartaB
*     CAR_CondRetDiferente  - se a cor de pCartaA for diferente do
*                             naipe de pCartaB
*     CAR_CondRetErroParm   - se algum parâmetro não atende uma 
*                             assertiva de entrada 
*  $AE Assertivas de Entrada:
*		pCartaA != NULL
*		pCartaB != NULL
*
*  $AS Assertivas de Saída:
*		Se a execução for bem sucedida:
*		retornará CAR_CondRetIgual quando a 
*		cor da pCartaA == cor da pCartaB.
*		Retornará CAR_CondRetDiferente quando a 
*		cor da pCartaA != cor da pCartaB.
*
*
***********************************************************************/

   CAR_tpCondRet CAR_CompararCor( CAR_tppCarta pCartaA , 
                                  CAR_tppCarta pCartaB  ) ;

/***********************************************************************
*
*  $FC Função: CAR  &Transformar a carta em uma string
*
*  $ED Descrição da função
*     Modifica o conteúdo referenciado por cartaString, informando
*        carta, naipe e rank da carta, no formato: 
*          <cor><naipe><rank>'\0'
*        onde cor, naipe e rank são os caracteres que representam 
*        cada um
*
*     O valor <cor> pode ser de dois tipos: 'P', indicando a cor preta;
*        e 'V', indicando a cor vermelha.
*
*     Por exemplo, para um Valete de Paus, o retorno seria: "PPJ". 
*        Para um Rei de Espadas, o retorno seria: "VES".
*
*     A string recebida tem que ter no mínimo capacidade de salvar
*       CAR_DIM_STRING caracteres.        
*
*     A associação de naipes à cores foi especificada previamente na
*        declaração do tipo CAR_tpNaipe.
*
*
*  $EP Parâmetros
*     pCarta      - ponteiro para a carta.
*                   Não pode ser NULL.
*     cartaString - ponteiro para a string que representará a carta
*                   Não pode ser NULL e recomenda-se que seu tamanho
*                   seja pelo menos CAR_DIM_STRING (tamanho suficiente).
*
*  $FV Valor retornado
*     CAR_CondRetOK        - conseguiu construir a string 
*     CAR_CondRetNaoOK     - não conseguiu construir a string
*     CAR_CondRetErroParm  - se algum parâmetro não atende uma 
*                            assertiva de entrada (não verifica ) 
*
*	$AE Assertivas de Entrada:
*		pCarta != NULL
*		cartaString != NULL
*
*	$AS Assertivas de Saída:
*		Se CAR_tpCondRet == CAR_CondRetOK, a função foi bem sucedida e
*		a string referente à pCarta foi construida e coloca em cartaString
*
***********************************************************************/

   CAR_tpCondRet CAR_ConverterParaString( CAR_tppCarta pCarta , 
                                          char * cartaString ) ;


#undef CARTA_EXT

/********** Fim do módulo de definição: CAR  Carta de um baralho **********/

#else
#endif