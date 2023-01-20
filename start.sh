g++ -c src/main.cpp
g++ -c src/raytracer.cpp
g++ main.o raytracer.o -o sfml-app.out -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app.out