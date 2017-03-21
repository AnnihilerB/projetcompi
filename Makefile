SOURCES_Y = $(wildcard *.y)
SOURCES_L = $(wildcard *.l)

ppascal:
	$(shell bison -d $(SOURCES_Y))
	$(shell flex $(SOURCES_L))
	gcc -std=c99 *.h *.c -o  $@ -lfl
clean:
	rm lex.yy.c *.tab.c *tab.h ppascal
