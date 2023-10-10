set PATH=%cd%\..\Requirements\MinGW\bin
g++ main.cpp -g -c -I/include -o bin/main.o
g++ bin/*.o -g -L./lib -lglfw3 -lopengl32 -lgdi32 -o bin/program
cd bin
program
del program.exe
cd ..
