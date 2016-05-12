ECHO Cria a biblioteca a ser utilizada pelos modulos
ECHO assume o arcabouco todo construído e correto

pushd  .

cd    ..\arcabouc\objetos
del    *.obj
del    *.lib
nmake /F..\..\arcabouc\composicao\crialib.make  "PRD="
copy  ArcaboucoTeste.lib  ..\..\objetos

popd
