#if ! defined( FREECELL_ )
#define FREECELL_

/***************************************************************************
*
*  $MCD Módulo de definição: FRC  Controla um jogo de FreeCell
*
*  Arquivo gerado:              FREECELL.h
*  Letras identificadoras:      FRC
*
*  Nome da base de software:    Trabalho 4 de Programação Modular
*  Arquivo da base de software: FREECELL/FREECELL.H
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gss
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data      Observações
*     1       gss   25/nov/2013  início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo controla o início e a finalização de uma partida do jogo
*		FreeCell, além de exportar as funções necessárias para toda a movimentação
*		das cartas.        
*     
*
***************************************************************************/

#if defined( FREECELL_OWN )
   #define FREECELL_EXT
#else
   #define FREECELL_EXT extern
#endif

#ifdef _DEBUG
   #include   "LISTA_INSTR.H"
#else
   #include   "LISTA.H"
#endif


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

      FRC_CondRetOK ,
            /* Concluiu corretamente */

      FRC_CondRetFaltouMemoria ,
            /* Faltou memória ao tentar criar um elemento */
             
      FRC_CondRetRemInvalida ,
            /* Operação não permitida para a carta em questão */

      FRC_CondRetErroParm ,
            /* Um dos parâmetros fornecidos é inválido */

      FRC_CondRetListaVazia,
      		/* Tenta-se obter carta de uma lista vazia */

      FRC_CondRetInsInvalida
      		/* Operação não permitida para a carta em questão */

    } FRC_tpCondRet ;


/***********************************************************************
*
*  $FC Função: FRC  MoverCarta
*
*  $ED Descrição da função
*     Verifica se a movimentação é possível, removendo do local de origem
*		e inserindo no local de destino.
*
*  $EP Parâmetros
*		
*		A COMPLETAR
*
*  $FV Valor retornado
*		A COMPLETAR
*     
***********************************************************************/

FRC_tpCondRet FRC_MoverCarta( LIS_tppLista pMesa , char * origem , 
                 int CodOrigem , char * destino , int CodDestino );


/***********************************************************************
*
*  $FC Função: FRC  ComecarJogo
*
*  $ED Descrição da função
*     Cria a lista de listas que representa a mesa de jogo e insere
*		7 cartas nas 4 primeiras sequências visíveis, e 6 nas 4 últimas.
*
*  $FV Valor retornado
*		Retorna um ponteiro para a mesa criada, ou NULL;
*     
***********************************************************************/

LIS_tppLista FRC_ComecarJogo( ) ;

/***********************************************************************
*
*  $FC Função: FRC  VerificarVitoria
*
*  $ED Descrição da função
*		Checa se as 4 sequências ordenadas estão completas.
*
*  $EP Parâmetros
*		LIS_tppLista mesa - ponteiro para a mesa
*
*  $FV Valor retornado
*		TRUE caso seja confirmada a vitória
*		FALSE caso não seja confirmada a vitória
*     
***********************************************************************/

int FRC_VerificarVitoria( LIS_tppLista pMesa );

/***********************************************************************
*
*  $FC Função: FRC  SalvarScore
*
*  $ED Descrição da função
*		Salva o saldo de vitórias e derrotas até o momento.
*
*  $EP Parâmetros
*		int status - booleano que indica se houve vitória ou não
*
*  $FV Valor retornado
*		FRC_CondRetOK - Caso seja executada corretamente
*		FRC_CondRetErroParm - Caso o status passado seja inválido
*     
***********************************************************************/

FRC_tpCondRet FRC_SalvarScore( int status );

/***********************************************************************
*
*  $FC Função: FRC  Finalizar Jogo
*
*  $ED Descrição da função
*		Destroi cartas e listas.
*
*  $EP Parâmetros
*		LIS_tppLista mesa - a mesa de jogo
*
*  $FV Valor retornado
*		FRC_CondRetOK - Caso seja executada corretamente
*
*     
***********************************************************************/

FRC_tpCondRet FRC_FinalizarJogo( LIS_tppLista pMesa );

#undef FREECELL_EXT

/********** Fim do módulo de definição: FRC  Controla um jogo de FreeCell **********/

#else
#endif