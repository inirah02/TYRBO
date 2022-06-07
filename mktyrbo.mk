Tyrbo.exe:type_content.o client.o
	gcc type_content.o client.o -o Tyrbo.exe
type_content.o: type_content.c
	gcc -c type_content.c
client.o: client.c
	gcc -c client.c