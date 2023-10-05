set PATH=C:\Users\Hiago Fernando\Desktop\Coisas Importantes\IntegralEngine\Requirements\MinGW\bin
g++ main.cpp -g -c -I/include -o bin/main.o
g++ bin/*.o -g -L./lib -lglfw3 -lopengl32 -lgdi32 -o bin/program
cd bin
program
del program.exe
cd ..
