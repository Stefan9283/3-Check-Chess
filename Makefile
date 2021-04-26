build:
	g++ -IInclude -o 3_Check_Chess Source/*.cpp
clean:
	rm -rf 3_Check_Chess
run:
	./3_Check_Chess
pack:
	zip -r Etapa2.zip Include Source Makefile README.md
