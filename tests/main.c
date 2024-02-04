#include "../include/clogin.h"
#include <unistd.h>
#define DATABASE_TEST_PATH "./tests/teste.dat" // Executado a partir da raiz

void assert(bool expression, char * msg);
void removeLastLine();

int main() {
    SetDatabasePath(DATABASE_TEST_PATH);

    bool primeiroCadastroSucedido = false;
    bool segundoCadastroComMesmaCredencialFalha = false;
    bool usuarioNaBaseDeDadosAposCadastro = false;
    bool retornaFalsoAoInserirCredenciaisComCaracterInvalido = false;
    bool duracaoSessaoInvalidaNegativa = false;
    bool duracaoSessaoValidaPositiva = false;

    // Duração de sessao
    SetDuracaoSessao(-10);
    duracaoSessaoInvalidaNegativa = DURACAO_SESSAO != -10;
    SetDuracaoSessao(10);
    duracaoSessaoValidaPositiva = DURACAO_SESSAO == 10;

    // Cadastros
    primeiroCadastroSucedido = cadastro();
    User * usuarioTeste = _ProcurarUsuario("usernameTeste", "senhaTeste", true);
    if (usuarioTeste != NULL)
        usuarioNaBaseDeDadosAposCadastro = true;
    
    segundoCadastroComMesmaCredencialFalha = !cadastro();
    retornaFalsoAoInserirCredenciaisComCaracterInvalido = !cadastro();

    // Login e sessão
    Sessao sessao = login(1);
    int offset_sessao = sessao._expira_em - time(NULL);
    int test_offset_sessao = verificarDuracaoSessao(sessao);


    removeLastLine();

    fflush(stdout);
    system("clear");

    printf("\n--------- Iniciando testes ---------\n");

    assert(usuarioNaBaseDeDadosAposCadastro, "Função procurar usuário encontrou credenciais de teste");
    assert(primeiroCadastroSucedido, "Cadastro retornou true para tentativa válida de cadastro");
    assert(segundoCadastroComMesmaCredencialFalha, "Cadastro falha para mesmo tentativa de cadastro duplicado");
    assert(retornaFalsoAoInserirCredenciaisComCaracterInvalido, "Cadastro falha ao informar em algum campo caracter de separação da base de dados");

    assert(sessao._has, "Parâmetro de sessao ativa muda para true");
    assert(strcmp(sessao.email, "teste@teste.com") == 0, "Email correto ao retornar sessao");
    assert(strcmp(sessao.username, "usernameTeste") == 0, "Nome de usuário correto ao retornar sessao");
    assert(test_offset_sessao >= 0 && test_offset_sessao <= offset_sessao, "Contagem de segundos correta na sessao");
    assert(offset_sessao >= 0 && offset_sessao <= DURACAO_SESSAO, "Duração de sessão correta ao retornar sessao");

    assert(strlen(generate_captcha()) == CAPTCHA_LENGTH, "Captcha é gerado com tamanho correto");
    assert(strcmp(DATABASE_TEST_PATH, databasePath) == 0, "Caminho da base de dados correto");
    assert(duracaoSessaoInvalidaNegativa, "SetDuracao impede alteracao para duração de sessao negativa");
    assert(duracaoSessaoValidaPositiva, "SetDuracao altera corretamente a duração de sessão");

    printf("\n\n--------- Testes finalizados ---------\n\n");
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
        printf("\n\033[1;32mSucesso - %s\033[0m", msg);
        return;
    }
    printf("\n\033[1;31mFalha - %s\033[0m", msg);
}
