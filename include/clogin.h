#ifndef CLOGIN
#define CLOGIN

// the clogin project header

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "clogin_memanager.h"

#define FILE_SEP ','
#define CAPTCHA_LENGTH 5

int DURACAO_SESSAO = 60 * 60 * 24 * 7;
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
    bool _has;
} Sessao;

bool CheckCharacter(char * str, char key) {
	return memchr(str, key, strlen(str)) != NULL;
}

Sessao SessaoFactory() {
    Sessao sessao;
    sessao._has = false;
    return sessao;
}

void SetDatabasePath(char * path) {
	strcpy(databasePath, path);

	FILE * file = fopen(databasePath, "rb");
	if (file == NULL) {
		printf("SetDatabasePath falhou, caminho do arquivo não foi encontrado!\n");
		exit(EXIT_FAILURE);
	}

	fclose(file);
	databasePathSet = true;
}

void SetDuracaoSessao(int novaDuracao) {
    if (novaDuracao < 0) {
        printf("Duração de sessão inválida: %d\n", novaDuracao);
        return;
    }
    DURACAO_SESSAO = novaDuracao;
}

User * _ProcurarUsuario(char * username, char * password, bool verificarSenha) {

    FILE * file = fopen(databasePath, "rb");
	if(file == NULL) {
        printf("Memory allocation error");
        return NULL;
    }

    char Fusername[MAX_FIELD], Fpassword[MAX_FIELD], Femail[MAX_FIELD];
    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", Fusername, Fpassword, Femail) != EOF) {
        if (strcmp(Fusername, username) == 0 && (!verificarSenha || strcmp(Fpassword, password) == 0)) {
            
            fclose(file);

            User *user = (User*) malloc(sizeof(User));
            if (user == NULL) {
                printf("Memory alloc error (_ProcurarUsuario)\n");
                return NULL;
            }

            Cleaner userCleaner = CleanerFactory(3);

            FileCharAlloc(&user->email, &userCleaner, file);
            FileCharAlloc(&user->username, &userCleaner, file);
            
            strcpy(user->email, Femail);
            strcpy(user->username, Fusername);
            user->password = NULL;

            return user;
        }
    }

    return NULL;
}

bool cadastro() {

	if (!databasePathSet) {
		printf("Database path not defined! Use 'SetDatabasePath' to set the path to your database\n");
		exit(EXIT_FAILURE);
	}

	FILE *file = fopen(databasePath, "ab");
	if(!file) {
        printf("Memory allocation error or file not exits");
        exit(EXIT_FAILURE);
    }

    Cleaner cleaner = CleanerFactory(3);
	User cadastrando;

    FileCharAlloc(&cadastrando.username, &cleaner, file);
    FileCharAlloc(&cadastrando.password, &cleaner, file);
    FileCharAlloc(&cadastrando.email, &cleaner, file);

	printf("\nREALIZAÇÃO DO CADASTRO\n");

	printf("DIGITE SEU USUARIO\n");
	scanf("%s%*c", cadastrando.username);

	printf("DIGITE SUA SENHA\n");
	scanf("%s%*c", cadastrando.password);

	printf("DIGITE SEU EMAIL\n");
	scanf("%s%*c", cadastrando.email);

	if (
		CheckCharacter(cadastrando.username, FILE_SEP)
		|| CheckCharacter(cadastrando.password, FILE_SEP)
		|| CheckCharacter(cadastrando.email, FILE_SEP)
	) {
		printf("CARACTER INVÁLIDO INSERIDO '%c'!\n", FILE_SEP);
        FileClean(&cleaner, file);
		return false;
	}

    User * searchDuplicate = _ProcurarUsuario(cadastrando.username, cadastrando.password, false);
    if (searchDuplicate != NULL) {
        printf("USUÁRIO JÁ CADASTRADO!\n");
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

    FileClean(&cleaner, file);
    return true;
}

Sessao login(int maxTries) {

	if (maxTries == 0) {
		printf("Número máximo de tentativas atingidas, por favor, tente novamente mais tarde\n");
		exit(EXIT_FAILURE);
	}

	if (!databasePathSet) {
		printf("Database path not defined! Use 'SetDatabasePath' to set the path to your database\n");
		exit(EXIT_FAILURE);
	}

    Cleaner visitanteCleaner = CleanerFactory(2);
	User visitante;

    CharAlloc(&visitante.username, &visitanteCleaner);
    CharAlloc(&visitante.password, &visitanteCleaner);

	printf("Insira seu username: ");
	scanf("%s%*c", visitante.username);

	printf("Insira sua senha: ");
	scanf("%s%*c", visitante.password);

    User * databaseUser = _ProcurarUsuario(visitante.username, visitante.password, true);
    if (databaseUser == NULL) {
        Clean(&visitanteCleaner);
        printf("\033[1;31mCredenciais inválidas.\033[0m\n\n");
        return login(maxTries - 1);
    }

    Sessao sessao = SessaoFactory();
    Cleaner sessaoCleaner = CleanerFactory(2);

    CharAlloc(&sessao.email, &sessaoCleaner);
    CharAlloc(&sessao.username, &sessaoCleaner);

    Clean(&visitanteCleaner);

    strcpy(sessao.email, databaseUser->email);
    strcpy(sessao.username, databaseUser->username);

    sessao._expira_em = time(NULL) + DURACAO_SESSAO;
    sessao._has = true;

    return sessao;
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
    int i, n;
    n = 5;
    srand(time(0));

    for (i = 0; i < n; i++) {
        char* generated_captcha = generate_captcha();
        printf("DIGITE OS CARACTERES APRESENTADOS: \033[1;35m%s\033[0m\n", generated_captcha);

        char user_input[CAPTCHA_LENGTH + 1];
        scanf("%5s", user_input);
        int c; while((c = getchar()) != '\n' && c != EOF) {}

        if (strcmp(user_input, generated_captcha) == 0) {
            return true;
        } else {
            printf("CAPTCHA INCORRETO, TENTE NOVAMENTE!\n");
            i--;
        }
        free(generated_captcha);

    }
    return false;
}

bool sessaoExpirou(Sessao sessao) {
    time_t agora = time(NULL);
    return sessao._expira_em < agora;
}

Sessao validarSessao(Sessao sessao, int maxTries) {

    if (!sessao._has || sessaoExpirou(sessao)) {
        printf("Sua sessão é inválida ou foi expirada, por favor faça login novamente!\n\n");
        Sessao novaSessao = login(maxTries);
        return novaSessao;
    };

    return sessao;
}

int verificarDuracaoSessao(Sessao sessao) {
    if (!sessao._has) {
        printf("Verificação de duração de sessão falhou!\n");
        return 0;
    }
    else if (sessaoExpirou(sessao)) {
        printf("Sessão expirada!\n");
        return 0;
    }
    
    return sessao._expira_em - time(NULL);
}

#endif 
