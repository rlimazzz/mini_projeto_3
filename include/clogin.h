#ifndef CLOGIN
#define CLOGIN

// the clogin project header

// including an unreasonable
// amount of libraries:
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_BUFFER 10000
#define MAX_FIELD 255
#define DURACAO_SESSAO 60 * 60 * 24 * 7 // 1 semana
#define FILE_SEP ','

// main struct
typedef struct {
	char *username;
	char *password;
	char *email;
} User;

typedef struct {
    char *email;
    char *username;
    char funcao[3]; // "adm" | "usr"
    int expira_em;
} Sessao;

bool check_character(char * str, char key) {
	return memchr(str, key, strlen(str)) != NULL;
}

// function declarations
bool cadastro(FILE *file, User cadastrando) {

	system("clear");
	
	//alocação de memoria para uso na struct
	cadastrando.username = (char*) malloc(100*sizeof(char));
	if (cadastrando.username == NULL)
		return false;

	cadastrando.password = (char*) malloc(100*sizeof(char));
	if (cadastrando.password == NULL)
		return false;

	cadastrando.email = (char*) malloc(300*sizeof(char));
	if (cadastrando.email == NULL)
		return false;

	//---------------------------------------

	printf("\nREALIZAÇÃO DO CADASTRO\n");

	printf("DIGITE SEU USUARIO\n");
	scanf("%[^\n]%*c", cadastrando.username);

	printf("DIGITE SUA SENHA\n");
	scanf("%s%*c", cadastrando.password);

	printf("DIGITE SEU EMAIL\n");
	scanf("%s%*c", cadastrando.email);

	if (
		check_character(cadastrando.username, FILE_SEP)
		|| check_character(cadastrando.password, FILE_SEP)
		|| check_character(cadastrando.email, FILE_SEP)
	) {
		printf("CARACTER INVÁLIDO INSERIDO %c!\n", FILE_SEP);
		return false;
	}
	
	//escrevendo meus dados no file
    char mensagem[MAX_BUFFER];
    sprintf(mensagem, "%s%c%s%c%s\n", 
		cadastrando.username,
		FILE_SEP,
		cadastrando.password,
		FILE_SEP
		cadastrando.email
	);
    fwrite(mensagem ,strlen(mensagem), 1, file);
	
	printf("CADASTRO REALIZADO COM SUCESSO: %s \n", cadastrando.username);

	//libero a memória alocada para uso em outras aplicações
	free(cadastrando.username);
	free(cadastrando.password);
	free(cadastrando.email);	
}

Sessao login() {
	Sessao sessao;
	return sessao;
}
void captcha();

// Uso em funções que exigem login
Sessao validarSessao(Sessao sessao) {
    time_t agora = time(NULL);

    // Caso a sessao esteja expirada, exija o login
    if (sessao.expira_em < agora) {
        printf("Sua sessão foi expirada, por favor faça login novamente!\n\n");
        Sessao novaSessao = login();
        return novaSessao;
    };

    return sessao;
};

#endif 
