REM Tudo do zero! Recompila e retesta todos os modulos

if exist vsvars32.bat goto faz
rem >>> Precisa do vsvars32.bat!!!
goto sai

:faz

cls

:inicializar

Call vsvars32
Call LimpaTudo
Call CriaLib
Call GeraTudo
Call CompilaTudo
Call TestaTudo

:carta
notepad ..\Produto\testecarta.log

:lista
notepad ..\Produto\testelista.log
notepad ..\Produto\testelistainstr.log
notepad ..\Produto\testelistadeturpa.log

:embaralhamento
notepad ..\Produto\testeembaralhamento.log

:extras
notepad ..\Produto\testeextras.log

:ordenada
notepad ..\Produto\testeordenada.log

:visivel
notepad ..\Produto\testevisivel.log


Call LimpaTudo
