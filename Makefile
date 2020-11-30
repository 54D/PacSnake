# It is a mess, pleae forgive me :^ )
# Edward CHUI 2020

CXX = g++
CXXFLAGS = -std=c++11 -I.
OBJDIR = obj
SRCDIR = src
OBJS = Entity.o MovingEntity.o SnakeBody.o Snake.o main.o
_OBJS = $(patsubst %,$(OBJDIR)/%,$(OBJS))

ENTITYDIR = src/entities/Entity
MOVINGENTITYDIR = src/entities/MovingEntity
SNAKEBODYDIR = src/entities/snake/SnakeBody
SNAKEDIR = src/entities/snake/Snake
FRUITDIR = src/entities/fruits_and_powerUps/Fruit
POWERUPDIR = src/entities/fruits_and_powerUps/PowerUp

all : main.exe

main.exe : $(_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(_OBJS)

$(OBJDIR)/main.o : main.cpp $(ENTITYDIR).h $(MOVINGENTITYDIR).h $(SNAKEBODYDIR).h $(SNAKEDIR).h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 	entity
$(OBJDIR)/Entity.o : $(ENTITYDIR).cpp $(ENTITYDIR).h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/MovingEntity.o : $(MOVINGENTITYDIR).cpp $(MOVINGENTITYDIR).h $(ENTITYDIR).h
	$(CXX) $(CXXFLAGS) -c $< -o $@

#		snake
$(OBJDIR)/SnakeBody.o : $(SNAKEBODYDIR).cpp $(SNAKEBODYDIR).h $(MOVINGENTITYDIR).h
	$(CXX) $(CXXFLAGS) -c $< -o $@

#Snake.o : $(SNAKEDIR).cpp $(SNAKEDIR).h $(SNAKEBODYDIR).h $(POWERUPDIR).h
$(OBJDIR)/Snake.o : $(SNAKEDIR).cpp $(SNAKEDIR).h $(SNAKEBODYDIR).h
	$(CXX) $(CXXFLAGS) -c $< -o $@

#		fruits_and_powerUps
# TODO
#Fruit.o : $(FRUITDIR).h
#	$(CXX) $(CXXFLAGS) -c $< -o $@

#PowerUp.o : $(POWERUPDIR).h
#	$(CXX) $(CXXFLAGS) -c $< -o $@


# CLEAN
.PHONY : clean
clean :
	del *.o *.exe