Tyrbo.exe: type_content.o client.o user_manage.o tc.o menu.o
	gcc menu.o tc.o client.o type_content.o user_manage.o -o Tyrbo.exe
user_manage.o: user_manage.c
	gcc -c user_manage.c
type_content.o: type_content.c
	gcc -c type_content.c
client.o: client.c
	gcc -c client.c
menu.o: menu.c
	gcc -c menu.c
tc.o: tc.c
	gcc -c tc.c