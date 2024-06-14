JC = javac
JFLAGS = -classpath .
JD = javadoc
JDFLAGS = -protected -splitindex -use -author -version -d ./javadoc
RM = rm
JR = java
input_file = input.txt
add_file = add_100.txt

CLASSES = \
		AVLTree.java \
		Main.java \
		Stock.java \
		StockDataManager.java \
		InputFileGenerator.java \
		
all : Main.class InputFileGenerator.class

run : 
	$(JR) -Xint Main $(input_file) $(add_file)

classes : $(CLASSES:.java=.class)

%.class : %.java
	$(JC) $(JFLAGS) $<

doc:
	$(JD) $(JDFLAGS) *.java 

clean:
	$(RM) *.class 

cleandoc:
	$(RM) -r ./javadoc