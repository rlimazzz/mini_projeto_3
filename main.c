#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/clogin.h"

int main() {	
	// Struct user vinda da clogin.h
	User new_user;
	/* inicialização do arquivo no qual estou escrevendo o cadastro dos meus usúarios */
	FILE *file;
	//aqui eu abro a file na opção de append para nunca sobreescrever meu arquivo
	file = fopen("teste.bin", "ab");

	//interface basica só pra ter um esqueleto
	printf("CORRUPT BANK\n");

	printf("1 - Login\n");

	printf("2 - Cadastro\n");

	printf("3 - Verificar Captcha\n$");

	int option;
	scanf("%d", &option);

	if(option == 1) 
	{
		// funcão login da clogin.h
		login();
	}
	else if(option == 2) 
	{
		// função cadastro da clogin.h
		cadastro(file, new_user);
	} else if (option == 3) {
		// função captcha da clogin.h
		//captcha();
	}

	fclose(file);
	return 0;
}
