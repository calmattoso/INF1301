rem Testa todos os scripts do modulo visivel

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat


:carta
..\produto\TRAB4-1       /s..\scripts\testecarta             /l..\produto\testecarta              /a..\scripts\estatisticas
if errorlevel 4 goto sai

:lista
..\produto\TRAB4-2       /s..\scripts\testelista             /l..\produto\testelista              /a..\scripts\estatisticas
if errorlevel 4 goto sai

:lista_instr
..\produto\TRAB4-3       /s..\scripts\testelistadebug             /l..\produto\testelistainstr              /a..\scripts\estatisticas
if errorlevel 4 goto sai
..\produto\TRAB4-3       /s..\scripts\testelistadeturpa            /l..\produto\testelistadeturpa              /a..\scripts\estatisticas
if errorlevel 4 goto sai

:embaralhamento
..\produto\TRAB4-4       /s..\scripts\testeembaralhamento             /l..\produto\testeembaralhamento              /a..\scripts\estatisticas
if errorlevel 4 goto sai

:extras
..\produto\TRAB4-5        /s..\scripts\testeextras             /l..\produto\testeextras              /a..\scripts\estatisticas
if errorlevel 4 goto sai

:ordenada
..\produto\TRAB4-6        /s..\scripts\testeordenada             /l..\produto\testeordenada              /a..\scripts\estatisticas
if errorlevel 4 goto sai

:visivel
..\produto\TRAB4-7        /s..\scripts\testevisivel             /l..\produto\testevisivel              /a..\scripts\estatisticas
if errorlevel 4 goto sai


..\ferramnt\exbestat /e..\scripts\estatisticas

:sai

