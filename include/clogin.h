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

char databasePath[MAX_FIELD];
bool databasePathSet = false;

typedef struct {
	char *username;
	char *password;
	char *email;
} User;

typedef struct {
    char *email;
    char *username;
    int _expira_em;
} Sessao;

bool check_character(char * str, char key) {
	return memchr(str, key, strlen(str)) != NULL;
}

void setDatabasePath(char * path) {
	strcpy(databasePath, path);

	FILE * file = fopen(databasePath, "rb");
	if (file == NULL) {
		printf("setDatabasePath falhou, caminho do arquivo não foi encontrado!\n");
		exit(EXIT_FAILURE);
	}

	fclose(file);
	databasePathSet = true;
}

bool cadastro() {

	if (!databasePathSet) {
		printf("Database path not defined! Use 'setDatabasePath' to set the path to your database\n");
		exit(EXIT_FAILURE);
	}

	FILE *file = fopen(databasePath, "ab");
	if(!file) {
        printf("Memory allocation error or file not exits");
        exit(EXIT_FAILURE);
    }
	
	User cadastrando;
	cadastrando.username = (char*) malloc(100*sizeof(char));
	if (cadastrando.username == NULL)
		return false;

	cadastrando.password = (char*) malloc(100*sizeof(char));
	if (cadastrando.password == NULL)
		return false;

	cadastrando.email = (char*) malloc(300*sizeof(char));
	if (cadastrando.email == NULL)
		return false;

	printf("\nREALIZAÇÃO DO CADASTRO\n");

	printf("DIGITE SEU USUARIO\n");
	scanf("%s%*c", cadastrando.username);

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
	
    char mensagem[MAX_BUFFER];
    sprintf(mensagem, "%s%c%s%c%s\n", 
		cadastrando.username,
		FILE_SEP,
		cadastrando.password,
		FILE_SEP,
		cadastrando.email
	);
    fwrite(mensagem, strlen(mensagem), 1, file);
	
	printf("CADASTRO REALIZADO COM SUCESSO: %s \n", cadastrando.username);

	free(cadastrando.username);
	free(cadastrando.password);
	free(cadastrando.email);	
}

Sessao login(int maxTries) {

	if (maxTries == 0) {
		printf("\nMaximum number of attempts reached, please try again later\n");
		exit(EXIT_FAILURE);
	}

	Sessao sessao;
	if (!databasePathSet) {
		printf("Database path not defined! Use 'setDatabasePath' to set the path to your database\n");
		exit(EXIT_FAILURE);
	}

	FILE * file = fopen(databasePath, "rb");
	if(!file) {
        printf("Memory allocation error");
        exit(EXIT_FAILURE);
    }

	User visitante;
	visitante.username = (char*) calloc(100, sizeof(char));
    if (visitante.username == NULL) {
        printf("Memory allocation error");
        exit(EXIT_FAILURE);
    }

	visitante.password = (char*) calloc(100, sizeof(char));
    if (visitante.password == NULL) {
        printf("Memory allocation error");
        exit(EXIT_FAILURE);
    }

	printf("Insira seu username: ");
	scanf("%s%*c", visitante.username);

	printf("Insira sua senha: ");
	scanf("%s%*c", visitante.password);

    char username[100], password[100], email[MAX_FIELD];
    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", username, password, email) != EOF) 
	{
        if (strcmp(username, visitante.username) == 0 && strcmp(password, visitante.password) == 0) 
		{
        	fclose(file);

            sessao.email = (char*) malloc(sizeof(char) * strlen(email));
            if (sessao.email == NULL) {
                printf("Memory allocation error");
                exit(EXIT_FAILURE);
            }

            sessao.username = (char*) malloc(sizeof(char) * strlen(username));
            if (sessao.username == NULL) {
                printf("Memory allocation error");
                exit(EXIT_FAILURE);
            }

            free(visitante.username);
            free(visitante.password);

            strcpy(sessao.email, email);
            strcpy(sessao.username, username);
            sessao._expira_em = time(NULL) + DURACAO_SESSAO;

            return sessao;
        }
    }

    fclose(file);
    free(visitante.username);
    free(visitante.password);

    return login(maxTries - 1);
}

char *generate_captcha() {
    char symbols[] = "!@#$%,./ABCDEFGHIJKLMNOPQRSTUVWXYZ?";
    const char numbers[] = "0123456789";
    char all_char[strlen(symbols) + strlen(numbers) + 1];

    strcpy(all_char, symbols);
    strcat(all_char, numbers);

    char* captcha = (char*)malloc((CAPTCHA_LENGTH + 1) * sizeof(char));
    if (!captcha) {
        printf("Memory allocation error");
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

Sessao validarSessao(Sessao sessao, int maxTries) {
    time_t agora = time(NULL);

    if (sessao._expira_em < agora) {
        printf("Sua sessão foi expirada, por favor faça login novamente!\n\n");
        Sessao novaSessao = login(maxTries);
        return novaSessao;
    };

    return sessao;
}

#endif 
