REM Tudo do zero! Recompila e retesta todos os modulos

if exist vsvars32.bat goto faz
rem >>> Precisa do vsvars32.bat!!!
goto sai

:faz

cls

:inicializar

Call LimpaTudo
Call CriaLib
Call GeraTudo
Call CompilaTudo
Call LimpaTudoRelease
Call TestaTudo

:carta
notepad ..\Produto\testecarta.log

:lista
notepad ..\Produto\testelista.log
notepad ..\Produto\testelistainstr.log
notepad ..\Produto\testelistadeturpa.log

:visivel
notepad ..\Produto\testevisivel.log

:ordenada
notepad ..\Produto\testeordenada.log

:extras
notepad ..\Produto\testeextras.log

:embaralhamento
notepad ..\Produto\testeembaralhamento.log

:sai
Call LimpaTudoRelease
