cd ../Requirements/MinGW/bin
g++ ../../../IntegralEngineEditor/main.cpp -g -c -I./include -o ../../../IntegralEngineEditor/bin/main.o
g++ ../../../IntegralEngineEditor/bin/*.o -g -L./lib -lglfw3 -lopengl32 -lgdi32 -o ../../../IntegralEngineEditor/bin/program
cd ../../../IntegralEngineEditor/bin
program
del program.exe
cd ..