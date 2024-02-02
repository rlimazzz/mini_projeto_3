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
#define CAPTCHA_LENGTH 5

// main struct
typedef struct {
	char *username;
	char *password;
	char *email;
} User;

typedef struct {
    char *email;
    char *username;
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
		printf("CARACTER INVÁLIDO INSERIDO '%c'!\n", FILE_SEP);
		return false;
	}
	
	//escrevendo meus dados no file
    char mensagem[MAX_BUFFER];
    sprintf(mensagem, "%s%c%s%c%s\n", 
		cadastrando.username,
		FILE_SEP,
		cadastrando.password,
		FILE_SEP,
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

	FILE *arquivo; 
	arquivo = fopen("./include/teste.bin", "rb");
	if(!arquivo) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

	User visitante;
	visitante.username = (char*) calloc(100, sizeof(char));
    if (visitante.username == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

	visitante.password = (char*) calloc(100, sizeof(char));
    if (visitante.password == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }


	printf("Insira seu username: ");
	scanf("%s%*c", visitante.username);

	printf("Insira sua senha: ");
	scanf("%s%*c", visitante.password);

    char username[100], password[100], email[MAX_FIELD];
    while (fscanf(arquivo, "%[^,],%[^,],%[^\n]\n", username, password, email) != EOF) 
	{
        if (strcmp(username, visitante.username) == 0 && strcmp(password, visitante.password) == 0) 
		{
        	fclose(arquivo);
            printf("Achei\n");

            sessao.email = (char*) malloc(sizeof(char) * strlen(email));
            if (sessao.email == NULL) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }

            sessao.username = (char*) malloc(sizeof(char) * strlen(username));
            if (sessao.username == NULL) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }

            free(visitante.username);
            free(visitante.password);

            strcpy(sessao.email, email);
            strcpy(sessao.username, username);
            sessao.expira_em = time(NULL) + DURACAO_SESSAO;

            return sessao;
        }
    }

	printf("Não achei\n");

    fclose(arquivo);
    free(visitante.username);
    free(visitante.password);

    return login(); // <- A recursão
}

char *generate_captcha() {
    char symbols[] = "!@#$%,./ABCDEFGHIJKLMNOPQRSTUVWXYZ?";
    const char numbers[] = "0123456789";
    char all_char[strlen(symbols) + strlen(numbers) + 1];

    strcpy(all_char, symbols);
    strcat(all_char, numbers);

    char* captcha = (char*)malloc((CAPTCHA_LENGTH + 1) * sizeof(char));
    if (!captcha) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    int i;
    for (i = 0; i < CAPTCHA_LENGTH; i++) {
        captcha[i] = all_char[rand() % strlen(all_char)];
    }

    captcha[CAPTCHA_LENGTH] = '\0';
    return captcha;
}

bool captcha() {
    system("clear");

    int i, n;
    time_t t;
    n = 5;
    srand(time(0));

    for (i = 0; i < n; i++) {
        char* generated_captcha = generate_captcha();
        printf("DIGITE OS CARACTERES APRESENTADOS: %s\n", generated_captcha);

        char user_input[CAPTCHA_LENGTH + 1];
        scanf("%5s", user_input);
        int c; while((c = getchar()) != '\n' && c != EOF) {}

        if (strcmp(user_input, generated_captcha) == 0) {
            printf("CAPTCHA CORRETO!\n");
            return true;
        } else {
            printf("CAPTCHA INCORRETO, TENTE NOVAMENTE!\n");
            i--;
        }
        free(generated_captcha);

    }
    return false;
}

// Uso em funções exigem login
Sessao validarSessao(Sessao sessao) {
    time_t agora = time(NULL);

    // Caso a sessao esteja expirada, exija o login
    if (sessao.expira_em < agora) {
        printf("Sua sessão foi expirada, por favor faça login novamente!\n\n");
        Sessao novaSessao = login();
        return novaSessao;
    };

    return sessao;
}

#endif 
