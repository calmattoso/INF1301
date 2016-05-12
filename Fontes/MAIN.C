#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#include "INTERFACE.h"
#include "freecell.h"


int main( )
{
	
	char idOrigem[4] , idDestino[4]; 
	
	int codOrig = -1;
	int codDest = -1;
	int retorno = (int) FRC_CondRetOK;
	int game_over = FALSE ;

	/* Inicializa Partida */
	LIS_tppLista pMesa = FRC_ComecarJogo();

	INT_ExibirMensagem( INT_MensagemEntrada );
	Sleep( 1500	) ;

	while( ! game_over )
	{
		INT_ExibirMesa( pMesa );

		INT_ExibirMensagem( INT_MensagemEntrarComando );

		retorno = (INT_tpCondRet) INT_ObterComando( idOrigem , &codOrig , idDestino , &codDest );
		//printf("%s %d %s %d",idOrigem, codOrig, idDestino, codDest);

		if( retorno != INT_CondRetOK ){
			INT_ExibirMensagem(INT_MensagemComandoInvalido);
			retorno = (FRC_tpCondRet) FRC_CondRetOK;
			continue;
		}
		else if( codOrig == INT_COD_SAIR )
		{
			game_over = TRUE ;
			continue ;
		}

		retorno = (FRC_tpCondRet) FRC_MoverCarta( pMesa , idOrigem , 
									 codOrig , idDestino , codDest  ) ;

		if( retorno == FRC_CondRetOK ) 
		{
			INT_ExibirMensagem( INT_MensagemOK ) ;
		}
		else
		{
			INT_ExibirMensagem( INT_MensagemMovimentoInvalido ) ;
		} /* if */


		if( FRC_VerificarVitoria( pMesa ) == TRUE  )
		{
			game_over = TRUE ;
		} /* if */
	}
	
	if(codOrig == INT_COD_SAIR){
		INT_ExibirMensagem(INT_MensagemFimJogoDerrota);
		FRC_SalvarScore(FALSE);
	}

	else{
		INT_ExibirMensagem(INT_MensagemFimJogoVitoria);
		FRC_SalvarScore(TRUE);
	}

	FRC_FinalizarJogo(pMesa);


	return 0;
}