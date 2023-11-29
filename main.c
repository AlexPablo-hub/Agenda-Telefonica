#include <stdio.h>  //stdio.h para funções de entrada e saída de dados
#include <stdlib.h> //stdlib.h para funções de alocação de memória, controle de processos e outras
#include <string.h> //string.h para funções de manipulação de strings

// importa a biblioteca windows.h para o comando Sleep
#ifdef _WIN32
#include <windows.h>
#endif

// Define a estrutura de dados para o telefone
typedef struct Telefone
{
    int dd;
    int tel;
} Telefone;

// Define a estrutura de dados para a pessoa
typedef struct Pessoa
{
    char nome[30];
    Telefone fone;
} Pessoa;

// Função para editar um contato existente, passa como parâmetro o vetor de contatos e o indice do contato a ser editado.
void editar(Pessoa *pessoa, int indice)
{
    // Solicita o novo nome
    printf("\n Novo Nome: ");
    fflush(stdin);
    gets(pessoa[indice].nome);

    // Solicita o novo DDD
    printf(" Novo DDD: ");
    scanf("%d", &pessoa[indice].fone.dd);

    // Solicita o novo numero de telefone
    printf(" Novo telefone: ");
    scanf("%d", &pessoa[indice].fone.tel);
    fflush(stdin);
}

// Função para salvar os contatos no arquivo contatos.txt, passa como parâmetro o vetor de contatos e o indice do contato a ser salvo.
void salvar_contatos(Pessoa *contatos, int indice)
{
    // Abre o arquivo para escrita
    FILE *arquivo;
    arquivo = fopen("contatos.txt", "w"); // fopen é uma função que abre um arquivo, w é uma flag que indica que o arquivo será aberto para escrita

    if (arquivo == NULL) // Verifica se o arquivo foi aberto corretamente
    {
        printf("Erro ao abrir o arquivo!"); // Se o arquivo não foi aberto corretamente, exibe uma mensagem de erro e encerra o programa
        exit(1);
    }
    for (int i = 0; i < indice; i++) // Escreve os contatos no arquivo contatos.txt, repete enquanto não chegar no final do arquivo.
    {
        // fprintf é uma função que escreve no arquivo, funciona como um printf porem a diferença é que o printf escreve no console e o fprintf escreve no arquivo.
        fprintf(arquivo, "%s %d %d\n", contatos[i].nome, contatos[i].fone.dd, contatos[i].fone.tel);
        fflush(stdin);
    }
    fclose(arquivo); // Fecha o arquivo
}

// Função para carregar os contatos do arquivo contatos.txt, passa como parâmetro o vetor de contatos e o indice do contato a ser carregado.
void carregar_contatos(Pessoa *contatos, int *indice)
{
    FILE *arquivo;                        // Abre o arquivo para leitura
    arquivo = fopen("contatos.txt", "r"); // r é uma flag que indica que o arquivo será aberto para leitura

    if (arquivo == NULL) // Verifica se o arquivo foi aberto corretamente
    {
        // Se o arquivo não foi aberto corretamente, exibe uma mensagem de erro e encerra a função
        printf("Erro ao abrir o arquivo!");
        exit(1);
    }

    // Lê os contatos do arquivo e armazena no vetor de contatos
    // Utiliza fgets para garantir a leitura correta de cada linha
    while (*indice < 100 && fgets(contatos[*indice].nome, sizeof(contatos[*indice].nome), arquivo) != NULL)
    {
        // Remove o caractere de nova linha (\n) do final da string lida pelo fgets
        contatos[*indice].nome[strcspn(contatos[*indice].nome, "\n")] = '\0';

        // Lê os dados do telefone
        fscanf(arquivo, "%d %d", &contatos[*indice].fone.dd, &contatos[*indice].fone.tel);

        (*indice)++; // Incrementa o índice para que o próximo contato seja armazenado na próxima posição do vetor de contatos.
    }

    fclose(arquivo); // Fecha o arquivo
}


// Função principal do programa.
int main()
{
    // Declaração das variáveis locais.
    Pessoa contatos[100];
    int opcao;            // Variável para armazenar a opção escolhida no menu
    int indice = 0;       // Variável para armazenar o indice do contato
    int i, encontrou = 0; // Variáveis auxiliares
    char pesq[30];        // Variável para armazenar o nome do contato a ser pesquisado
    int cod;              // Variável para armazenar o código do contato a ser editado ou excluído

    carregar_contatos(contatos, &indice); // chama a função carregar_contatos para carregar os contatos do arquivo contatos.txt.

    do
    {
        system("cls"); // Limpa a tela do console

        // Exibe o menu de opções para o usuário
        printf("\n*************\n");
        printf("      * AGENDA DE CONTATOS *\n");
        printf("*************\n");
        printf("\n       ####### MENU #######\n\n");
        printf("   ( 1 ) CADASTRAR CONTATO. \n");
        printf("   ( 2 ) CONSULTAR UM CONTATO POR NOME. \n");
        printf("   ( 3 ) LISTAR TODOS OS CONTATOS. \n");
        printf("   ( 4 ) EDITAR UM CONTATO. \n");
        printf("   ( 5 ) EXCLUIR UM CONTATO. \n");
        printf("   ( 6 ) SAIR. \n");

        printf("\n Opcao: ");
        scanf("%d", &opcao); // Lê a opção escolhida pelo usuário
        fflush(stdin);

        switch (opcao) // switch case é uma estrutura de controle que permite que uma variável seja testada em uma lista de valores.
        {
        case 1:
            system("cls");

            printf("\n--** CADASTRO DE CONTATO **--");
            printf("\n CODIGO:%i\n", indice);
            printf("\n Nome: ");
            gets(contatos[indice].nome); // gets é uma função que lê uma string do console e armazena na variável contatos[indice].nome
            printf("\n Dados do Telefone. ");
            printf("\n DDD: ");
            scanf("%d", &contatos[indice].fone.dd);
            printf(" Numero: ");
            scanf("%d", &contatos[indice].fone.tel);
            indice++; // incrementa o indice para que o proximo contato seja armazenado na proxima posição do vetor de contatos.
            fflush(stdin);

            salvar_contatos(contatos, indice); // chama a função salvar_contatos para salvar os contatos no arquivo contatos.txt.
            break;

        case 2:
            system("cls");

            printf("\n--** CONSULTAR UM CONTATO POR NOME **--");
            printf("\nPesquisar: ");
            gets(pesq); // gets é uma função que lê uma string do console e armazena na variável pesq

            for (i = 0; i < indice; i++) // Percorre o vetor de contatos para encontrar o contato pesquisado pelo usuário.
            {
                if (strcmp(pesq, contatos[i].nome) == 0) // strcmp é uma função que compara duas strings, se as strings forem iguais retorna 0.
                {
                    printf("\nCodigo: %i", i);
                    printf("\n   Nome: %s", contatos[i].nome);
                    printf("\n   Telefone: %d %d", contatos[i].fone.dd, contatos[i].fone.tel);
                    encontrou = 1; // Se o contato for encontrado, a variável encontrou recebe 1.
                    printf("\n--------------------------------------------\n");
                }
            }
            if (encontrou == 0) // Exibe mensagem caso o contato não seja encontrado.
            {
                printf("\n NENHUM REGISTRO ENCONTRADO!\n\n");
                printf("\n--------------------------------------------\n");
            }
            system("pause");
            break;

        case 3:
            printf("--** CONTATOS DA AGENDA **-- \n"); // Lista todos os contatos cadastrados
            for (i = 0; i < indice; i++)  // Percorre o vetor de contatos para exibir os contatos cadastrados.
            {
                printf("\nCodigo: %i", i);
                printf("\n   Nome: %s", contatos[i].nome);
                printf("\n   Telefone: %d %d", contatos[i].fone.dd, contatos[i].fone.tel);
                printf("\n--------------------------------------------\n");
            }
            if (indice == 0) // Exibe mensagem caso o contato não seja encontrado.
            {
                printf("\n NENHUM REGISTRO ENCONTRADO!\n\n");
                printf("\n--------------------------------------------\n");
            }
            system("pause");
            break;

        case 4:
            printf("\n--###----EDITAR CONTATO----###--\n"); // Edita um contato existente
            printf("\nInforme o Codigo: ");
            scanf("%i", &cod);

            if (cod >= 0 && cod < indice)
            {
                editar(contatos, cod);             // chama a função editar para editar o contato
                salvar_contatos(contatos, indice); // chama a função salvar_contatos para salvar os contatos no arquivo contatos.txt
            }
            else
            {
                printf("\nCodigo invalido! Por favor, informe um codigo existente.\n");
                printf("\n");
                system("pause");
            }
            break;

        case 5:
            printf("\n--###----EXCLUIR CONTATO----###--\n"); // Exclui um contato existente
            printf("\nInforme o Codigo: ");
            scanf("%i", &cod);

            if (cod >= 0 && cod < indice)
            {
                printf("\n Nome: %s", contatos[cod].nome);
                printf("\n Telefone: %d %d", contatos[cod].fone.dd, contatos[cod].fone.tel);
                printf("\nDeseja excluir o contato? Sim(1) / Nao(2): ");
                scanf("%i", &i);

                if (i == 1)
                {
                    for (i = cod; i < indice; i++) // Percorre o vetor de contatos para excluir o contato
                    {
                        strcpy(contatos[i].nome, contatos[i + 1].nome);
                        // strcpy é uma função que copia uma string para outra string, mas nesse caso está sendo usada para mover os contatos para uma posição anterior no vetor de contatos assim excluindo o contato.
                        contatos[i].fone.dd = contatos[i + 1].fone.dd;
                        contatos[i].fone.tel = contatos[i + 1].fone.tel;
                    }
                    indice--; // Decrementa o indice para que o proximo contato seja armazenado na posição anterior do vetor de contatos.

                    salvar_contatos(contatos, indice); // Salva os contatos no arquivo contatos.txt

                    printf("\nContato excluido!\n");
                    system("pause");
                }
            }
            else
            {
                printf("\nCodigo invalido! Por favor, informe um codigo existente.\n");
                printf("\n");
                system("pause");
            }
            break;

        case 6:
            printf("\n----Obrigado pela atencao---\n"); // Encerra o programa e exibe uma mensagem de agradecimento
            fflush(stdout); // fflush é uma função que limpa o buffer de saída do console
            Sleep(800); // Sleep é uma função que faz o programa dormir por um determinado tempo, nesse caso 800 milisegundos que equivale a 0,8 segundos
            exit(0); // exit é uma função que encerra o programa
            break;

        default: // Caso o usuário digite uma opção inválida, exibe uma mensagem de erro.
            printf("\nOpcao invalida! Por favor, escolha uma opcao exixtente no menu.\n");
            printf("\n---------------------------------------\n");
            system("pause");
        }
    } while (opcao != 6); // Repete enquanto a opção escolhida for diferente de 6.

    return 0; // Retorna 0 para o sistema operacional.
}