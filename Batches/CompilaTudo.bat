ECHO Compila todos os modulos do programa
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio Microsoft
cls

del ..\produto\*.err
del ..\objetos\*.obj

:carta
REM compila modulo CARTA para producao sem otimizacoes
pushd .
nmake /F..\Composicao\testecarta.make 
popd

:lista
REM compila modulo lista para producao sem otimizacoes
del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testelista.make 

:lista_instr
REM compila modulo lista para debug sem otimizacoes
del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testelistainstr.make 

:embaralhamento
REM compila modulo embaralhamento para producao sem otimizacoes
del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testeembaralhamento.make 

:extras
REM compila modulo EXTRAS para producao sem otimizacoes
del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testeextras.make 

:ordenada
REM compila modulo ORDENADA para producao sem otimizacoes
del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testeordenada.make 

:visivel
REM compila modulo VISIVEL para producao sem otimizacoes
del ..\objetos\*.obj
pushd .
nmake /F..\Composicao\testevisivel.make 
popd

:jogo
REM compila o JOGO para producao sem otimizacoes
del ..\objetos\*.obj
pushd .
nmake /F..\Composicao\jogo.make 
popd

del ..\objetos\*.obj

popd

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err

