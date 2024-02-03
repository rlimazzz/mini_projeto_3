#include "../include/clogin.h"
#include <unistd.h>
#define DATABASE_TEST_PATH "./teste.bin"

void assert(bool expression, char * msg);
void removeLastLine();

int main() {
    setDatabasePath(DATABASE_TEST_PATH);

    cadastro();
    Sessao sessao = login(3);

    removeLastLine();

    assert(strcmp(sessao.email, "teste@teste.com") == 0, "Email correto ao retornar sessao");
    assert(strcmp(sessao.username, "usernameTeste") == 0, "Nome de usuário correto ao retornar sessao");

    int offset_sessao = sessao._expira_em - time(NULL);
    assert(offset_sessao >= 0 && offset_sessao <= DURACAO_SESSAO, "Duração de sessão correta ao retornar sessao");
}

void removeLastLine() {
    FILE * file = fopen(DATABASE_TEST_PATH, "rb+");
    if (file == NULL) {
        printf("Erro ao ler o arquivo (removeLastLine)\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);

    if (size > 0) {
        for (long i = size - 2; i >= 0; i--) {
            fseek(file, i, SEEK_SET);
            if (fgetc(file) == '\n') {
                ftruncate(fileno(file), i + 1);
                break;
            } else if (i == 0) {
                ftruncate(fileno(file), 0);
            }
        }
    }

    fclose(file);
}

void assert(bool expression, char * msg) {
    if (expression) {
        printf("\n\033[1;32mSucesso - %s\033[0m\n", msg);
        return;
    }
    printf("\n\033[1;31mFalha - %s\033[0m\n", msg);
}
