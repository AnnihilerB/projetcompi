SRC_PATH = 
SOURCES_Y = $(wildcard $(SRC_PATH)*.y)
SOURCES_L = $(wildcard $(SRC_PATH)*.l)

all:
	make interpp
	make tradpp2c3a
	make interpp_c3a
interpp:
	$(shell bison -d $(SOURCES_Y))
	$(shell flex $(SOURCES_L))
	gcc -g -std=c99 $(SRC_PATH)analyseur.c $(SRC_PATH)environ.c $(SRC_PATH)interpp.c $(SRC_PATH)interpreteur.c lex.yy.c *.tab.c $(SRC_PATH)tableau.c $(SRC_PATH)util.c -o $@ -lfl
tradpp2c3a:
	$(shell bison -d $(SOURCES_Y))
	$(shell flex $(SOURCES_L))
	gcc -g -std=c99 $(SRC_PATH)analyseur.c $(SRC_PATH)environ.c $(SRC_PATH)tradpp2c3a.c $(SRC_PATH)traducteurC3A.c lex.yy.c *.tab.c $(SRC_PATH)bilquad.c $(SRC_PATH)util.c -o $@ -lfl
interpp_c3a:
	$(shell bison -d $(SOURCES_Y))
	$(shell flex $(SOURCES_L))
	gcc -g -std=c99 $(SRC_PATH)tableau.c  $(SRC_PATH)analyseur.c $(SRC_PATH)environ.c $(SRC_PATH)interpp_c3a.c $(SRC_PATH)traducteurC3A.c lex.yy.c *.tab.c $(SRC_PATH)bilquad.c $(SRC_PATH)util.c $(SRC_PATH)interpreteurC3A.c -o $@ -lfl
clean:
	rm lex.yy.c *.tab.c *tab.h interpp tradpp2c3a interpp_c3a
