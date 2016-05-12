REM   Limpa tudo que sera' regerado, menos os exe ( versao para producao )


if exist TestaTudo.bat goto faz
rem >>> esta' no diretorio ilegal
goto sai

:faz

pushd .

cd ..\Batches
del *.bak

cd ..\Composicao
del *.bak
del *.list

cd ..\Fontes
del *.bak
del *.err
del *.o

cd ..\Objetos
del *.bak
del *.obj
del *.lib

cd ..\Produto
del *.bak
del *.log
del *.err
del *.txt


cd ..\Projeto
del *.bak

cd ..\Tabelas
del *.bak

cd ..\Scripts
del *.bak

cd ..\Ferramnt
del *.bak
del *.err
del *.obj


popd

:sai
