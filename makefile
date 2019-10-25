NAME = physicsProjectileCalculator
OBJECTS = physicsProjectileCalculator.cpp

program: $(OBJECTS)
	g++ -std=c++0x $(OBJECTS) -o $(NAME) -Wall

run prorgam:
	./$(NAME)
	rm $(NAME)
