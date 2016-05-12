LEIAME -- T4 Freecell
=====================

ÍNDICE
------
   1 - Apresentação
   2 - Estrutura de Diretórios
   3 - Modo de uso
   4 - Como Jogar
   5 - Identificadores

1   APRESENTAÇÃO
----------------
   Este documento descreve breviamente o conteúdo deste projeto, extraído de
   INF1301-Trab04-CLMFFAGSS.ZIP. Este projeto contém todos os módulos fontes, 
   utilitários e documentação necessários.   
   ATENÇÃO: Todos os arquivos .exe tiveram suas extensões alteradas para .exe.txt.
   Antes de utilizá-los, corrija suas extensões para .exe .
   Os integrantes deste grupo são:
      NOME                        | SIGLA | MATRÍCULA
      ---------------------------   -----   ---------
      Carlos Augusto Lima Mattoso |  clm  | 1210553
      Felipe Filgueiras Argento   |  ffa  | 1211625
      Gabriel da Silva Siqueira   |  gss  | 1210689  

2   ESTRUTURA DE DIRETÓRIOS
---------------------------
   Este projeto apresenta-se organizado nos seguintes módulos, cujos arquivos
   fonte compartilham a pasta Fontes:

   /**** Módulos ****/
   - carta:
      Contém as partes integrantes necessárias para compilar o módulo Carta.
      >> Código para executáveis:  1

   - lista:
      Contém as partes integrantes necessárias para compilar o módulo Lista.
      >> Código para executáveis:  2 ( sem instrumentação ), 
                                   3 ( com instrumentação )

   - embaralhamento:
      Contém as partes integrantes necessárias para compilar
      o módulo Embaralhamento.
      >> Código para executáveis:  4

   - extras:
      Contém as partes integrantes necessárias para compilar
      o módulo Extras.
      >> Código para executáveis:  5

   - ordenada:
      Contém as partes integrantes necessárias para compilar o módulo Ordenada.
      >> Código para executáveis:  6

   - visivel:
      Contém as partes integrantes necessárias para compilar o módulo Visivel.
      >> Código para executáveis:  7

   - jogo:
      Contém as partes integrantes necessárias para compilar o Jogo. Depende dos
      módulos FreeCell e Interface que também são providos em anexo. Estes módulos
      dependem intrinsicamente de interação do jogador ou de aleatoriedade (na hora 
      de se gerar o baralho). Portanto, não foram testados.
      >> Código para executáveis:  8

   /**** Outros ****/

   - documentos
      Contém arquivos que exibem a arquitetura do sistema, um modelo físico da 
      mesma, um relatório geral sobre o projeto e os relatórios de 
      desenvolvimento.

   - batches
      Arquivos batches que auxiliam a geração e teste das versões Release de 
      TODOS os módulos.

   Internamente, os arquivos dos módulos foram organizados com base no exemplo
   /instrum do arcabouço. 

3   MODO DE USO
---------------
   !!! OBS !!! Caso deseje-se compilar os trabalhos novamente, deve-se 
   primeiramente adicionar as pastas /ferramnt e /arcabouc do arcabouço na
   pasta raiz do trabalho (pasta em que se encontram as pastas de cada módulo),
   assim como o batch vsvars32.bat do Visual Studio na subpasta Batches da pasta
   raiz do trabalho. 

 Recompilar e Testar Tudo
 ------------------------
   Caso deseje-se recompilar e testar todos os módulos de uma só vez, basta 
   fazer no terminal, a partir da pasta raiz do trabalho (após executar os 
   passos descritos na observação) :

      cd batches
      TudoRelease.bat

   Isto irá exibir no notepad, durante a execução, os resultados de compilação
   e de testes de cada módulo, além de gerar e manter apenas os logs e 
   estatísticas de teste.

 Testar Tudo
 -----------
   Caso queira apenas testar todos os módulos do projeto, basta fazer no
   terminal a partir da pasta raiz do trabalho:

      cd batches
      TestaTudoRelease.bat

   Neste caso, serão apenas gerados os arquivos de log dos testes nas 
   pastas Produto de cada módulo.

 Teste Individual de Módulo
 --------------------------
   Para executar os testes, basta no terminal fazer, a partir da pasta 
   raiz do módulo a ser testado:

      cd Batches
      TestaTudo.bat
  
   Uma coisa opção é fazer, também a partir da raiz:

      cd Produto
      TRAB4-<codigo> /s..\Scripts\<nome_do_script>.script /l<nome_do_log>

   Onde <codigo> é um dos valores numéricos que foram listados na seção 2 
   deste documento, com relação aos módulos.
   Caso seja feito /l<nome_do_log> (parte opcional) será criado um arquivo
   chamado <nome_do_log>.log, contendo os resultados dos testes.

 Compilação e Teste Individual
 -----------------------------
   Tendo-se feito os passos da observação inicial e executado antes no terminal
   o batch vsvars32.bat, basta fazer a partir da pasta raiz do trabalho:

      cd <nome_da_pasta_do_módulo>\Batches
      TudoRelease.bat

   Pode ainda utilizar-se o Tudo.bat, que não irá remover arquivos extras.

4   Como Jogar
---------------

   O jogo de FreeCell que implementamos é simples de controlar e jogar. Assim 
   que executado, mostra uma mensagem explicando ao jogador os comandos básicos
   para interagir com o jogo. Logo em seguida, a mesa de cartas é mostrada, começando
   pelas sequêcias ordenadas, seguidas pelos espaços extras e as sequências visíveis.
   Pede-se então um comando do usuário.

   Há duas opções de comando: 
      - o comando    mov , que movimenta uma carta;
      - e o comando quit , que abandona a partida. 
        Caso o jogador abandone a partida, será acrescentada uma derrota
        a sua contagem.

   Sintaxe do comando mov:
      mov idOrigemNum idDestino[Num] 

   Por exemplo:

   mov vis1 ext1 
      moveria a carta do topo da primeira sequência visível para o 
      primeiro espaço extra (caso possível)

   mov ext1 ord
      moveria a carta do espaço extra 1 para a sequência ordenada 
      correspondente a seu naipe (caso possível)

   A cada movimento feito, é exibida uma visão atualizada da mesa.	

