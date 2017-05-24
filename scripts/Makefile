CXX = g++
CXXFLAGS = -g -Wall -MMD
OBJECTS = main.o boostattack.o controller.o dragon.o elf.o goblin.o human.o orc.o poisonhealth.o stairs.o view.o boostdefence.o default.o drow.o enemy.o gold.o merchant.o playable.o potion.o troll.o woundattack.o character.o display.o dwarf.o floor.o halfling.o moveableenemy.o player.o restorehealth.o vampire.o wounddefence.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}
