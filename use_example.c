#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/clogin.h"

#define MAX_LOGIN_TRIES 3
#define DATABASE_PATH "./usuarios.dat"

void PressioneVoltar() {
	printf("\nPressione enter para voltar\n");
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
			
			printf("\nBem vindo, %s!\n\n", sessao.username);
		}

		printf("CORRUPT BANK\n");

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
				printf("CADASTRO FEITO COM SUCESSO!\n");
			}
			else {
				printf("CADASTRO FALHOU\n");
			}
		}

		else if (option == 3) {
			if(captcha()) {
				printf("CAPTCHA FEITO COM SUCESSO\n");
			}
		}

		else if (option == 4) {
			sessao = validarSessao(sessao, MAX_LOGIN_TRIES);
			printf("Você possui \033[1;32m%d\033[0m segundos de sessão!\n", verificarDuracaoSessao(sessao));
		}

		else {
			printf("Opção inválida!\n");
		}
		
		PressioneVoltar();
	}
}
