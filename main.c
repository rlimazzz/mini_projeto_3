#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct principal que vou usar para tudo
typedef struct {
	char *usuario;
	char *senha;
	char *email;
} Pessoa;

void cadastro(FILE *file) {

	system("clear");
	//declaro meu usuario a ser cadastrado
	Pessoa cadastrando;
	
	//alocação de memoria para uso na struct
	cadastrando.usuario = (char*) malloc(100*sizeof(char));
	cadastrando.senha = (char*) malloc(100*sizeof(char));
	cadastrando.email = (char*) malloc(300*sizeof(char));

	//---------------------------------------

	printf("REALIZAÇÃO DO CADASTRO\n");

	printf("DIGITE SEU USUARIO\n");

	scanf("%s", cadastrando.usuario);

	printf("DIGITE SUA SENHA\n");

	scanf("%s", cadastrando.senha);

	printf("DIGITE SEU EMAIL\n");

	scanf("%s", cadastrando.email);
	
	//escrevendo meus dados no file
	fprintf(file, "USUARIO : %s , SENHA : %s, EMAIL : %s\n", cadastrando.usuario, cadastrando.senha, cadastrando.email);
	
	printf("BOAS VINDAS AO CORRUPT BANK CARO SR OU SRA %s \n", cadastrando.usuario);
	//libero a memória alocada para uso em outras aplicações
	free(cadastrando.usuario);
	free(cadastrando.senha);
	free(cadastrando.email);
	
}

int main() {

	/* inicialização do arquivo no qual estou escrevendo o cadastro dos meus usúarios */
	FILE *file;
	//aqui eu abro a file na opção de append para nunca sobreescrever meu arquivo
	file = fopen("teste.bin", "a");

	//interface basica só pra ter um esqueleto
	printf("CORRUPT BANK\n");

	printf("1 - Login\n");

	printf("2 - Cadastro\n");

	printf("3 - Verificar Captcha\n$");

	int option;
	scanf("%d", &option);

	if(option == 1) 
	{
		printf("Ola\n");
	}
	else if(option == 2) 
	{
		cadastro(file);
	}

	fclose(file);
	return 0;
}
