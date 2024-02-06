#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/clogin.h"

#define MAX_LOGIN_TRIES 3
#define DATABASE_PATH "./usuarios.dat"

#define COR "\e[0;35m"
#define FIM_COR "\e[0m"
#define FAILURE "\e[1;91m"
#define SUCCESS "\e[1;92m"
#define WARNING "\e[4;33m"	
#define BLUE "\e[0;34"

void PressioneVoltar() {
	printf(COR"\nPressione enter para voltar\n"FIM_COR);
	scanf("%*c");
}

int main() {
	SetDatabasePath(DATABASE_PATH);
	SetDuracaoSessao(10); // Padrão: 1 semana, Nesse app: 10 segundos, apenas para testes
	Sessao sessao = SessaoFactory();

	while (1) {
		system("clear");

		if (sessao._has) {
			sessao = validarSessao(sessao, 3);
			system("clear");
			
			printf(COR"\nBem vindo, \033[0m%s\033[0;35m!\n\n"FIM_COR, sessao.username);
		}

		printf(COR"CORRUPT BANK\n"FIM_COR);

		printf("0 - Sair\n");
		printf("1 - Login\n");
		printf("2 - Cadastro\n");
		printf("3 - Verificar Captcha\n");
		printf("4 - Verificar sessão\n\n$ ");

		int option;
		scanf("%d%*c", &option);

		if (option == 0) {
			return 0;
		}

		else if (option == 1) {
			sessao = login(MAX_LOGIN_TRIES);
		}

		else if(option == 2) {
			if (cadastro()) {
				printf(SUCCESS"CADASTRO FEITO COM SUCESSO!\n"FIM_COR);
			}
			else {
				printf(FAILURE"CADASTRO FALHOU\n"FIM_COR);
			}
		}

		else if (option == 3) {
			if(captcha()) {
				printf(SUCCESS"CAPTCHA FEITO COM SUCESSO\n"FIM_COR);
			}
		}

		else if (option == 4) {
			sessao = validarSessao(sessao, MAX_LOGIN_TRIES);
			printf(WARNING"Você possui %d segundos de sessão!\n"FIM_COR, verificarDuracaoSessao(sessao));
		}

		else {
			printf(FAILURE"Opção inválida!\n"FIM_COR);
		}
		
		PressioneVoltar();
	}
}
