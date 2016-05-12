##################################################
###
### Diretivas de MAKE para o construto: Jogo
### Gerado a partir de: Jogo.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = Jogo


### Nomes de paths

Pdef                 = ..\Tabelas
Ph                   = ..\Fontes
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes
Pc                   = ..\Fontes

### Nomes de diretórios para geração

Fdef                 = ..\Tabelas
Fh                   = ..\Fontes
Fobj                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Fontes
Fc                   = ..\Fontes

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\carta.obj   $(Fobj)\lista.obj   $(Fobj)\embaralhamento.obj \
   $(Fobj)\visivel.obj   $(Fobj)\ordenada.obj   $(Fobj)\extras.obj \
   $(Fobj)\interface.obj   $(Fobj)\freecell.obj   $(Fobj)\main.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\carta.obj :  {$(Pc)}\carta.c \
    {$(Ph)}carta.h              {$(Ph)}generico.h           {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\lista.obj :  {$(Pc)}\lista.c \
    ..\\tabelas\\idtiposespaco.def {$(Ph)}cespdin.h            {$(Ph)}conta.h              \
    {$(Ph)}generico.h           {$(Ph)}lista.h              {$(Pdef)}tiposespacoslista.def \
    {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\embaralhamento.obj :  {$(Pc)}\embaralhamento.c \
    {$(Ph)}carta.h              {$(Ph)}embaralhamento.h     {$(Ph)}lista.h              \
    {$(Ph)}lista_instr.h       
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\visivel.obj :  {$(Pc)}\visivel.c \
    {$(Ph)}carta.h              {$(Ph)}lista.h              {$(Ph)}lista_instr.h        \
    {$(Ph)}visivel.h           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\ordenada.obj :  {$(Pc)}\ordenada.c \
    {$(Ph)}carta.h              {$(Ph)}lista.h              {$(Ph)}lista_instr.h        \
    {$(Ph)}ordenada.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\extras.obj :  {$(Pc)}\extras.c \
    {$(Ph)}carta.h              {$(Ph)}extras.h             {$(Ph)}lista.h              \
    {$(Ph)}lista_instr.h       
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\interface.obj :  {$(Pc)}\interface.c \
    {$(Ph)}carta.h              {$(Ph)}extras.h             {$(Ph)}interface.h          \
    {$(Ph)}lista.h              {$(Ph)}ordenada.h           {$(Ph)}visivel.h           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\freecell.obj :  {$(Pc)}\freecell.c \
    {$(Ph)}carta.h              {$(Ph)}embaralhamento.h     {$(Ph)}extras.h             \
    {$(Ph)}freecell.h           {$(Ph)}lista.h              {$(Ph)}lista_instr.h        \
    {$(Ph)}ordenada.h           {$(Ph)}visivel.h           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\main.obj :  {$(Pc)}\main.c \
    {$(Ph)}carta.h              {$(Ph)}freecell.h           {$(Ph)}interface.h          \
    {$(Ph)}lista.h              {$(Ph)}lista_instr.h       
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\carta.obj   $(Fobj)\lista.obj   $(Fobj)\embaralhamento.obj \
   $(Fobj)\visivel.obj   $(Fobj)\ordenada.obj   $(Fobj)\extras.obj \
   $(Fobj)\interface.obj   $(Fobj)\freecell.obj   $(Fobj)\main.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: Jogo
###
##################################################

