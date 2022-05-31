default:
	make clean
	javac -cp ".;lib/*" *.java
	java Main

clean:
	-rm */*.class *.class *.json