@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .

cd ..\ferramnt

gmake  /b..\composicao  /cTesteCarta
gmake  /b..\composicao  /cTesteLista
gmake  /b..\composicao  /cTesteListaInstr
gmake  /b..\composicao  /cTesteEmbaralhamento
gmake  /b..\composicao  /cTesteExtras
gmake  /b..\composicao  /cTesteOrdenada
gmake  /b..\composicao  /cTesteVisivel
gmake  /b..\composicao  /cJogo


popd
