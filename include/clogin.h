#ifndef CLOGIN
#define CLOGIN

// the clogin project header

// including an unreasonable
// amount of libraries:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// main struct
typedef struct {
	char *username;
	char *password;
	char *email;
} User;

// function declarations
void cadastro(FILE *file, User cadastrando) {

	system("clear");
	//declaro meu usuario a ser cadastrado
	
	//alocação de memoria para uso na struct
	cadastrando.username = (char*) malloc(100*sizeof(char));
	cadastrando.password = (char*) malloc(100*sizeof(char));
	cadastrando.email = (char*) malloc(300*sizeof(char));

	//---------------------------------------

	printf("REALIZAÇÃO DO CADASTRO\n");

	printf("DIGITE SEU USUARIO\n");

	scanf("%s", cadastrando.username);

	printf("DIGITE SUA SENHA\n");

	scanf("%s", cadastrando.password);

	printf("DIGITE SEU EMAIL\n");

	scanf("%s", cadastrando.email);
	
	//escrevendo meus dados no file
    char mensagem[100000];
    int t=10;
    sprintf(mensagem, "USUARIO : %s , SENHA : %s, EMAIL : %s\n", cadastrando.username, cadastrando.password, cadastrando.email);

    fwrite(mensagem , strlen(mensagem), 1, file);
	
	printf("CADASTRO REALIZADO COM SUCESSO: %s \n", cadastrando.username);
	//libero a memória alocada para uso em outras aplicações
	free(cadastrando.username);
	free(cadastrando.password);
	free(cadastrando.email);	
}

void login();
void captcha();

#endif 
