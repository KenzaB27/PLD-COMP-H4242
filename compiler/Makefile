OUTPUT=output
SOURCE=code
GENERATED=$(SOURCE)/antlr4-generated
GRAMMAR=ifcc.g4

#override with your local installation
ANTLR4_INCDIR=/usr/local/include/antlr4-runtime 
ANTLR4_LIBDIR=/usr/local/lib

ifeq ($(ENV), mac)
	DENV=-DMACOS
	ANTLR4=java -jar /usr/local/lib/antlr-4.8-complete.jar 
else
	ANTLR4=/usr/bin/antlr4
endif

CC=clang++
CCARGS=-g -c -I $(ANTLR4_INCDIR) -I $(GENERATED) -std=c++11 -Wno-defaulted-function-deleted -Wno-unknown-warning-option $(DENV) $(D)
LDARGS=-g

CODESOURCE_CPP=$(shell find $(SOURCE) -type f -name '*.cpp')
CODESOURCE_H=$(shell find $(SOURCE) -type f -name '*.h')
OBJECTS=$(CODESOURCE_CPP:.cpp=.o)
OBJECTS_IN_OUTPUT_DIRECTORY=$(patsubst %.o,$(OUTPUT)/%.o,$(OBJECTS))

all: ifcc

%.o: %.cpp
	mkdir -p $(OUTPUT)/$(dir $@)
	$(CC) $(CCARGS) $< -o $(OUTPUT)/$@
	
ifcc: dirs antlr $(OBJECTS)
	$(CC) $(LDARGS) $(OBJECTS_IN_OUTPUT_DIRECTORY) $(ANTLR4_LIBDIR)/libantlr4-runtime.a -o ifcc

antlr: $(GRAMMAR)
	$(ANTLR4) -visitor -no-listener -Dlanguage=Cpp -o $(GENERATED) $(GRAMMAR)

dirs:
	mkdir -p $(OUTPUT) 
	mkdir -p $(GENERATED)

clean:
	rm -rf $(OUTPUT)
	rm -rf $(GENERATED)

test:
	cd ../tests/ && ./test_if.sh
