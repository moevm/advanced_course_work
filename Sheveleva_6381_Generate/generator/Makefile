
all: generate clean

generate: generate.o GenerateOption.o GenerateParagraph.o GeneratePunctuation.o GeneratePunctuationMarks.o GenerateSentence.o GenerateWord.o
	gcc generate.o GenerateOption.o GenerateParagraph.o GeneratePunctuation.o GeneratePunctuationMarks.o GenerateSentence.o GenerateWord.o -o generate

generate.o: generate.c
	gcc -c generate.c

GenerateOption.o: GenerateOption.c
	gcc -c GenerateOption.c

GenerateParagraph.o: GenerateParagraph.c
	gcc -c GenerateParagraph.c

GeneratePunctuation.o: GeneratePunctuation.c
	gcc -c GeneratePunctuation.c

GeneratePunctuationMarks.o: GeneratePunctuationMarks.c
	gcc -c GeneratePunctuationMarks.c	

GenerateSentence.o: GenerateSentence.c
	gcc -c GenerateSentence.c

GenerateWord.o: GenerateWord.c
	gcc -c GenerateWord.c
	
clean:
	rm -rf *.o
