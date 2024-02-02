<div align="center">
  <img src=docs/out.gif width=500px>

<div align="center"><p>
    <a href="https://github.com/rlimazzz/mini_projeto_3/pulse">
      <img alt="Last commit" src="https://img.shields.io/github/last-commit/rlimazzz/mini_projeto_3?style=for-the-badge&logo=starship&color=89ff57&logoColor=D9E0EE&labelColor=2c2c33"/>
    </a>
    <a href="https://github.com/rlimazzz/mini_projeto_3/stargazers">
      <img alt="Stars" src="https://img.shields.io/github/stars/rlimazzz/mini_projeto_3?style=for-the-badge&logo=starship&color=fcff57&logoColor=D9E0EE&labelColor=2c2c33" />
    </a>
    <a href="https://github.com/rlimazzz/mini_projeto_3/issues">
      <img alt="Issues" src="https://img.shields.io/github/issues/rlimazzz/mini_projeto_3?style=for-the-badge&logo=bilibili&color=ff5757&logoColor=D9E0EE&labelColor=2c2c33" />
    </a>
    <a href="https://github.com/rlimazzz/mini_projeto_3">
      <img alt="Repo Size" src="https://img.shields.io/github/repo-size/rlimazzz/mini_projeto_3?color=57b6ff&label=SIZE&logo=codesandbox&style=for-the-badge&logoColor=D9E0EE&labelColor=2c2c33" />
    </a>
  </div>
  <h2 style="font-size:30vw">Miniprojeto 3 referente a matéria de Introdução a Programação - UFG.</h2>
</div>

## Tópicos Rápidos
- [Features](#features)
- [Instalação](#instalação)
- [Estrutura do Projeto](#layout-do-projeto)
- [Documentação](#documentação)
- [Autores](#autores)

CLOGIN é uma biblioteca que visa facilitar o processo de autenticação de logins em aplicações.

## Features:
--------
- Command Line Interface;
- Acesso nas linguagens C/C++;
- Suporte de arquivos binários;
- Verificação CAPTCHA;
- Testes.


## Instalação:
-------------------
No terminal, siga os comandos:
### Linux
```bash
git clone 'https://github.com/rlimazzz/mini_projeto_3.git'
cd mini_projeto_3
gcc use_example.c
```
## Layout do projeto:
--------------
```bash
mini_projeto_3/                 # Pasta principal do projeto
|-- docs/                       # Pasta contendo arquivos gráficos
|   |-- (arquivos gráficos aqui)
|-- include/                    # Pasta do arquivo fonte da biblioteca
|   |-- (arquivos da biblioteca aqui)
|   |-- teste.bin               # Arquivo binário do banco de dados
|-- tests/                      # Diretório responsável pelos testes do projeto
|   |-- (arquivos da biblioteca aqui)
|-- README.md                   # Arquivo de documentação do projeto
|-- start                       # Arquivo de inicialização
|-- use_example.c               # Um exemplo de uso da biblioteca
```

## Documentação:
--------------
CLogin - Sistema de Login em C
O CLogin é um sistema de login simples em linguagem C que permite o cadastro de usuários, autenticação e geração de sessões de usuário.
### Structs
1. User:
- A estrutura User representa as informações de um usuário, contendo campos como username (nome de usuário), password (senha) e email.
  ```c
  typedef struct {
      char *username;
      char *password;
      char *email;
  } User;
  ```
2. Sessao:
- A estrutura Sessao representa uma sessão de usuário, contendo informações como email, username, funcao (tipo de usuário: "adm" | "usr") e expira_em (tempo de expiração da sessão).
  ```c
  typedef struct {
    char *email;
    char *username;
    char funcao[3]; // "adm" | "usr"
    int expira_em;
  } Sessao;
  ```
-------------
### Funções

1. ```c
   bool cadastro(FILE *file, User cadastrando);
   ```
   Realiza o cadastro de um novo usuário, solicitando e armazenando o username, password e email. Retorna true se o cadastro for bem-sucedido e false caso contrário.
   - Exemplo de uso:
   ```c
   FILE *arquivo = fopen("usuarios.txt", "a");
   User novoUsuario;
   cadastro(arquivo, novoUsuario);
   fclose(arquivo);
   ```
   -------------
  
2. ```c
   Sessao login();
   ```
   Realiza o login de um usuário, verificando as credenciais em um arquivo binário. Retorna uma estrutura Sessao válida se o login for bem-sucedido.
   - Exemplo de uso:
   ```c
   Sessao sessaoUsuario = login();
   ```
   
   -------------

3. ```c
   char *generate_captcha();
   ```
   Gera e retorna um código CAPTCHA composto por caracteres alfanuméricos e especiais.
   - Exemplo de uso:
   ```c
   char *captchaCode = generate_captcha();
   ```
   
   -------------
   
4. ```c
   bool captcha();
   ```
   Apresenta um desafio CAPTCHA ao usuário, solicitando a entrada dos caracteres apresentados. Retorna true se o CAPTCHA for correto e false caso contrário.
   - Exemplo de uso:
   ```c
   bool captchaValido = captcha();
   ```
   
   -------------

5. ```c
   Sessao validarSessao(Sessao sessao);
   ```
   Verifica se uma sessão de usuário está expirada. Se expirada, exige um novo login. Retorna uma nova sessão válida.
   - Exemplo de uso:
   ```c
   sessaoUsuario = validarSessao(sessaoUsuario);
   ```
-------------
### Definições e Constantes
  1. ```MAX_BUFFER, MAX_FIELD```
    Define o tamanho máximo de buffer e de campo, respectivamente.

  2. ```DURACAO_SESSAO```
    Define a duração padrão de uma sessão em segundos (1 semana).

  3. ```FILE_SEP```
    Define o separador utilizado no arquivo para armazenar informações do usuário.

  4. ```CAPTCHA_LENGTH```
    Define o comprimento do código CAPTCHA gerado.

  -------------
    
### Observações
  Todas as funções exigem a inclusão do cabeçalho ```#include "clogin.h"``` no código fonte.
    Este é um projeto simples e educacional. Recomenda-se aprimorar a segurança e robustez do sistema para uso em ambientes de produção.

## Autores:
1. Acsa Mendes
2. Caio Farias
3. Jhoy Kallebe
4. Ryan Gabryel
5. Tiago Pio

<div align="center">
  <a align="center" href="https://github.com/rlimazzz/mini_projeto_3/contributors">
  <img src="https://contrib.rocks/image?repo=rlimazzz/mini_projeto_3" />
  </a>
</div>
