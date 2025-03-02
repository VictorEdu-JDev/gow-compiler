# GOW Language - God of War Inspired Programming Language

GOW é uma linguagem esotérica inspirada no jogo *God of War*. Os comandos são baseados em falas, eventos e referências do jogo. Este documento explica a sintaxe, os comandos, as estruturas de controle e como interpretar/executar um programa em GOW.

## Índice

1. [Introdução](#introdução)
2. [Declaração de Variáveis](#declaração-de-variáveis)
3. [Comandos](#comandos)
    1. [Comandos de Entrada e Saída](#comandos-de-entrada-e-saída)
4. [Estruturas de Controle](#estruturas-de-controle)
    1. [Condicionais](#condicionais)
    2. [Laços de Repetição](#laços-de-repetição)
5. [Funções](#funções)
6. [Compilando e Executando um Programa em GOW](#compilando-e-executando-um-programa-em-gow)
    1. [Escreva o Código GOW](#escreva-o-código-gow)
    2. [Use o Tradutor GOW-C](#use-o-tradutor-gow-c)
    3. [Execute o Tradutor](#execute-o-tradutor)
7. [Adicionais](#adicionais)
    1. [Avisos sobre a Linguagem](#avisos-sobre-a-linguagem)
    2. [Possíveis Erros](#possíveis-erros)
    3. [Repositório com Exemplos](#repositório-com-exemplos)

## 1 Introdução

GOW é uma linguagem esotérica criada para divertir os amantes de *God of War*. Seus comandos utilizam referências do jogo para definir funções, estruturas e operações.

## 2. Declaração de Variáveis

Em GOW, os tipos de variáveis são inferidos automaticamente. Portanto, o programador precisa apenas declarar o nome que deseja para a variável e o valor que será atribuído a ela. A sintaxe é:
i am the nome_da_variavel of valor;

### Exemplo em GoW
```
i am the number of 10;
````
### Exemplo em C

```
int number = 10;
```
# 3 Comandos
Os comandos em GOW são referências ao jogo:
- **runic**: representa a definição de funções;
- **trial**: representa o comando `if`;
- **fate**: representa o comando `else`;
- **fate else**: representa o comando `else if`;
- **cyclone of chaos**: representa o comando `for`.

## 3.1 Comandos para entrada e saída dos dados
`face me` e `read the words` representam os comandos `printf()` e `input()`, respectivamente. Em GOW, eles são funções criadas a partir da `runic` e devem ser chamadas quando forem ser usadas com a palavra reservada `revenge`.

### Exemplo:
```
runic face me - message {
    i am the endline of "\n";
    revenge show yourself message together endline;
}

revenge face me "hello world!";
```
# 4 Estruturas de controle

## 4.1 Condicionais
```gow
trial condicao {
    // comando;
} fate {
    // comando;
}
```
### Exemplo
```
i am the nota of 10;

trial nota blade of chaos 7 {
    revenge face me "aluno reprovado :(";
} fate {
    revenge face me "aluno reprovado!";
}
```
Nesse exemplo, para imprimir a mensagem na tela chamamos a função face me usando revenge.

### Em C:
```c
int nota = 10;

if (nota < 7) {
    printf("aluno reprovado :(");
} else {
    printf("aluno aprovado!");
}
```
## 4.2 Laços de repetição
### Laço for
cyclone of chaos valor, criterio_de_parada, incremento {
    // comando;
}
### Exemplo
```
i am the valor of 1;

cyclone of chaos valor, valor blade of chaos 5, valor power up {
    revenge face me valor;
}
```
Nesse exemplo, para imprimir a mensagem na tela chamamos a função face me usando revenge.

### Em C:
```
for (int i = 1; i <= 5; i++) {
    printf("%d\n", i);
}
```
# 5 Funções
```
runic nome_da_funcao - variavel {
    // Instruções;
}
```
### Exemplo
```
runic mensagem {
    revenge face me "God of War";
}

runic omega {
    revenge mensagem;
}
```
Nesse exemplo, para imprimir a mensagem na tela chamamos a função face me usando revenge.

## Em C:
```
void mensagem() {
    printf("God of War\n");
}

int main() {
    mensagem();
}
```
# 6 Compilando e executando um programa em GOW
## 6.1 Escreva o Código GOW
- Certifique-se que o CMake ou GCC está instalado e está nas variáveis de ambiente
do seu sistema;
5
- Faça um fork ou clone do repositório para sua máquina do tradutor GoWC que esta
na última seção da documentação;
- Crie um código fonte GoW com a extensão ".gow";
- Execute o tradutor gerado pela compilação do CMake a partir do terminal usando
./gowc teste.gow.

# 7 Executando um código em GoW
### 99 garrafas de cerveja em GOW:

### Em C:
```
#include <stdio.h>

int main() {
    for (int i = 99; i > 0; i--) {
        printf("%d bottles of beer on the wall, %d bottles of beer.\n", i, i);
        printf("Take one down, pass it around, %d bottles of beer on the wall.\n", i - 1);
    }
    return 0;
}
```
### Em GoW
```
runic omega {
    cyclone of chaos i am the bottles of 99, bottles rage of sparta 0, bottles power down {
        revenge face me bottles together " garrafas de cerveja na parede, " together bottles together " garrafas de cerveja";
        revenge face me "Pegue uma e passe adiante, " together bottles fall 1 together " garrafas de cerveja na parede";
}

    revenge face me "Nenhuma garrafa de cerveja na parede, nenhuma garrafa de cerveja";
    revenge face me "Va ate a loja e compre mais 99 garrafas de cerveja na parede";
}
```
# 8 Adicionais
## 8.1 Avisos sobre a linguagem
GOW é uma linguagem criada para amantes do jogo God of War, feita com o objetivo de divertir quem está programando nela, e desafiar a fazer tarefas e funções usando referências ao jogo.

## 8.2 Possíveis erros
Devido à natureza experimental da linguagem GOW, ela está suscetível a alguns erros durante a tradução e execução dos programas. Esses erros podem incluir problemas com a sintaxe e formatação de saída. Em suma, é recomendado verificar o código gerado e o ambiente de execução para garantir que o comportamento do programa esteja conforme esperado. Divirta-se!

## 8.3 Repositório com exemplos
Para obter o tradutor GOW e outros exemplos com o código, visite o repositório do GitHub:

[GoW Language - Interpretador](https://github.com/VictorEdu-JDev/gow-interpreter)


