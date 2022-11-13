// BANCO DE DADOS
// DATA: 21/12/2021

/*
    Alterações feitas no código até o momento:
        retirei o system cls, por enquanto.
*/


#include <stdio.h>
#include <stdlib.h>
//#include <locale.h>
#include <string.h>




struct Cliente {
    char NomeCompletoDoCliente[70];
    char CPF[30];
    char telefone[30];
    int diaNascimento;
    int mesNascimento;
    int anoNascimento;
    char bairro[30]; //antes tava 20 aqui.
    char cidade[30]; //antes tava 20 aqui.

    //talvez tenha que ter um ponteiro para produtos aqui.
};

struct Produtos {
    char CPFdoComprador[30];
    char bairroComprador[20];
    char cidadeComprador[20];
    char nomeProduto[20];
    float valor;
    int DiaDaVenda; 
    int MesDaVenda; 
    int AnoDaVenda;
};



//FUNCAO
void sair();
void finish();
void pesquisarCadastros();
void consultarCliente();
void alterarDados();
void pesquisarCompras();
void menuCadastradoCliente();
void cadastrarCliente();
void cadastrarCompras();
int confirmarAcao();
void listarCliente();
void pesquisaComprasPorValor(FILE *arquivoProdutos,float DadoAserPesquisado);
/*
Essa funcao teve que ser em cima da main pq como o parametro da funcao é um float ela dava erro quando estava abaixo da main, pesquisei em alguns lugares mas não descobri algum lugar que explicava o pq isso acontecia.

Uma outra opcao para nao ter que fazer isso, seria ler o float e converter para string e passar como parametro da funcao, depois voltar para float novamente.
*/
void pesquisaComprasPorValor(FILE *arquivoProdutos,float DadoAserPesquisado){

    int MarcadorDeVirgula = 4; //numero da virgula que esta presente o conteudo de valor
    //printf("Valor a ser pesquisado: %f",DadoAserPesquisado);
    float somador = 0.0;

    int op;
    do {
        printf("Digite a forma de pesquisa: \n");
        printf("[1] - MAIOR OU IGUAL A %.2f\n",DadoAserPesquisado);
        printf("[2] - MENOR OU IGUAL A %.2f\n",DadoAserPesquisado);
        printf("[3] - IGUAL A %.2f\n",DadoAserPesquisado);
        printf("Escolha uma opcao: ");
        fflush(stdin);
        scanf("%d",&op);
    } while (op<1 || op>3);
    
    



    //converte de string para float : atof
    //sprintf(DadoASerPesquisado, "%.2f", aux); //converte de float para string

    char AnaliseDaLinhaArq[2048];
    const char virgula[2] = ",";
    int contagemDeVirgulas=0;
    char *palavraQuebrada;
    int flag = -1 ;
    int cont = 1;

    char DadosDoProduto[1000];
    
    fseek(arquivoProdutos,0,SEEK_SET);
    while(fgets(AnaliseDaLinhaArq,sizeof(AnaliseDaLinhaArq),arquivoProdutos)) {
        //printf(" Linha lida do arquivo: %s",AnaliseDaLinhaArq);
        strcpy(DadosDoProduto,AnaliseDaLinhaArq);
        
        palavraQuebrada = strtok(AnaliseDaLinhaArq, virgula);

        
        contagemDeVirgulas = 0;
        while( contagemDeVirgulas != MarcadorDeVirgula ) { //para pegar somente a 2ª virgula, por isso é 1. (0 - 1a vigula, 1 - 2a virgula,...)
            //printf( " %s\n", palavraQuebrada );
            palavraQuebrada = strtok(NULL, virgula);
            contagemDeVirgulas++;
        }
        RemoveEspacoComecoEFinal(palavraQuebrada);

        float ValorDoArquivo = atof(palavraQuebrada);
        //printf("Valor do arquivo=%f=",ValorDoArquivo);

        
        switch (op) {
        case 1:
            if(ValorDoArquivo >= DadoAserPesquisado) {
                printf("\tCompra[%d]: %s",cont,DadosDoProduto);
                //calcula a soma:
                somador += ValorDoArquivo;
                cont++;
                flag++;
            }
            break;
        case 2:
            if(ValorDoArquivo <= DadoAserPesquisado) {
                printf("\tCompra[%d]: %s",cont,DadosDoProduto);
                //calcula a soma:
                somador += ValorDoArquivo;
                cont++;
                flag++;
            }
            break;
        case 3:
            if(ValorDoArquivo == DadoAserPesquisado) {
                printf("\tCompra[%d]: %s",cont,DadosDoProduto);
                //calcula a soma:
                somador += ValorDoArquivo;
                cont++;
                flag++;
            }
            break;
        default:
            break;
        }

    }
    if(somador!=0) {
        printf("Soma dos Valores listados: %.2f",somador);
    }

    if(flag == -1) {
        printf("\n\nO Valor: %f Nao Existe no Banco de dados de Produtos.\n Voltando ao menu principal...\n\n",DadoAserPesquisado);
        return;
    }


}



int main(){

    //setlocale(LC_ALL,"");
    FILE* arquivo = fopen("BancoDeDadosCliente.txt", "a+");

    if (arquivo == NULL) {
        printf("Erro na abertura de arquivo de clientes!");
        return 0;
    } else {
        printf("O arquivo foi aberto com sucesso!");
    }
    
    
    FILE* arquivoProdutos = fopen("BancoDeDadosProdutos.txt", "a+");

    if (arquivoProdutos == NULL) {
        printf("Erro na abertura de arquivo de produtos!");
        return 0;
    } else {
        printf("O arquivo foi aberto com sucesso!");
    }
    




    menuCadastradoCliente(arquivo,arquivoProdutos);


    printf("Fechando o arquivo e salvando...");
    fclose(arquivo);
    fclose(arquivoProdutos);
    
}

void menuCadastradoCliente(FILE *arquivo,FILE *arquivoProdutos){

    

    int op;
    do{
        system("cls");
        printf("\n\n ------- CADASTRO DOS CLIENTES -------- \n\n");
        printf("[1] Criar cadastro dos clientes \n");
        printf("[2] Criar cadastros de compras dos clientes \n");
        printf("[3] Escolha como deseja pesquisar \n");
        printf("[0] Sair\n");
        printf("Escolha uma Opcao:\n");
        scanf("%d", &op);

        switch (op){
            case 1: cadastrarCliente(arquivo);
                break;
            case 2: cadastrarCompras(arquivo,arquivoProdutos);
                break;
            case 3: pesquisarCadastros(arquivo,arquivoProdutos);
                break;
            case 0:printf("\nFinalizando.....\n");
                break;
            default:printf("\nOpcao Invalida\n");
                break;
        }

    }while(op!=0);

}

int confirmarAcao(){//Confirma se a pessoa quer continuar?
    int op;
    do{
        printf("Deseja continuar?\n");
        printf("[1] Sim \n");
        printf("[0] Nao\n");
        scanf("%d", &op);
        //system("cls");
    }while(op<0  || op >1);
    return op;
}

void cadastrarCliente(FILE *arquivo){

    if(!confirmarAcao()) return;

    struct Cliente cliente;
    printf("\n** Cadastrando Cliente **\n");
    fflush(stdin);
    printf("Digite o Nome completo: ");
    fgets(cliente.NomeCompletoDoCliente, sizeof(cliente.NomeCompletoDoCliente), stdin );
    printf("Digite o CPF: ");
    fgets(cliente.CPF,sizeof(cliente.CPF),stdin);
    printf("Digite o telefone: ");
    fgets(cliente.telefone,sizeof(cliente.telefone),stdin);

    printf("**Data de nascimento**:\n Digite o Dia de nascimento: ");
    scanf("%d",&cliente.diaNascimento);
    printf("Digite o mes de nascimento: ");
    scanf("%d",&cliente.mesNascimento);
    printf("Digite o ano de nascimento: ");
    scanf("%d",&cliente.anoNascimento);

    fflush(stdin);

    printf("Digite o seu Bairro: ");
    fgets(cliente.bairro,sizeof(cliente.bairro),stdin);
    printf("Digite a cidade: ");
    fgets(cliente.cidade,sizeof(cliente.cidade),stdin);

    printf("\n\n---Dados do cliente:-----\n ");
    printf("\n Nome Completo: %s CPF: %s Telefone: %s Data de nascimento: %02d/%02d/%d \n Bairro: %s Cidade: %s \n ",cliente.NomeCompletoDoCliente,cliente.CPF,cliente.telefone,cliente.diaNascimento,cliente.mesNascimento,cliente.anoNascimento,cliente.bairro,cliente.cidade);

    int op;
    do{
        printf("\nDeseja Salvar esses dados acima do cliente no arquivo?\n");
        printf("[1] Sim \n");
        printf("[0] Nao\n");
        scanf("%d", &op);
        //system("cls");
    }while(op<0  || op >1);
    if(op == 0) {
        printf("Voltando ao menu principal...");
        return;
    } else {
        printf("Salvando dados do cliente no arquivo...");
    }

    //Remoção do \n para escrever no arquivo na forma: nome, telefone, ...
    cliente.NomeCompletoDoCliente[strcspn(cliente.NomeCompletoDoCliente, "\n")] = 0;
    /*a funcao strcspn serve para comparar valores de s1 que nao estao em s2, e devolverá o tamanho dessa string 
    nesse caso a função procurará todos os valores da string até que encontre \n, quando encontrar devolverá o 
    valor para o usuário,e como esse valor é o valor de \n, esse valor será substituído por zero. */
    cliente.CPF[strcspn(cliente.CPF,"\n")]= 0;
    cliente.telefone[strcspn(cliente.telefone,"\n")] = 0;
    cliente.bairro[strcspn(cliente.bairro,"\n")]= 0;
    cliente.cidade[strcspn(cliente.cidade,"\n")]=0;

    //Salvando os dados no arquivo:
    fseek(arquivo,0,SEEK_END);

    //salvando dados com: Nome Completo, CPF, telefone, diaNasc/mesNasc/anoNasc, bairro, cidade;
    fprintf(arquivo, "%s, %s, %s, %02d/%02d/%d, %s, %s\n",cliente.NomeCompletoDoCliente,cliente.CPF,cliente.telefone,cliente.diaNascimento,cliente.mesNascimento,cliente.anoNascimento,cliente.bairro,cliente.cidade);  
    


    

}

int erroNoArquivo(FILE *arquivo) {
    if(ferror(arquivo)!=0) {
        printf("Ocorreu um erro ao abrir o arquivo, voltando ao menu principal...\n");
        return 1;
    } else {
        return 0;
    }

    fseek(arquivo, 0, SEEK_END);

    if(ftell(arquivo)==0) {
        printf("Nao existem clientes para cadastrar produtos, voltando ao menu principal...");
        return 1;
    } else {
        return 0;
    }
}

void cadastrarCompras(FILE *arquivo, FILE *arquivoProdutos){
    if(!confirmarAcao()) return;

    

    //if(erroNoArquivo(arquivo) == 1) {
      //  return;
    //}

    if(ferror(arquivo)!=0) {
        printf("Ocorreu um erro ao abrir o arquivo, voltando ao menu principal...\n");
        return;
    }

    listarCliente(arquivo);

    fseek(arquivo, 0, SEEK_END);

    if(ftell(arquivo)==0) {
        printf("Nao existem clientes para cadastrar produtos, voltando ao menu principal...");
        return;
    } 
    printf("\n***** Cadastrando Produtos ******\n");
    char CpfAProcurar[30];
    printf("\nDigite o CPF do cliente que voce quer cadastrar o produto: "); 
    fflush(stdin);
    fgets(CpfAProcurar,sizeof(CpfAProcurar),stdin);
    //printf("CPF lido: %s ", CpfAProcurar);
    CpfAProcurar[strcspn(CpfAProcurar,"\n")]= 0;

    char AnaliseDaLinhaArq[2048];
    const char virgula[2] = ",";
    int cont=0;
    char *palavraQuebrada;
    int flag = -1 ;
    char DadosDoCliente[1000];
    
    fseek(arquivo,0,SEEK_SET);
    while(fgets(AnaliseDaLinhaArq,sizeof(AnaliseDaLinhaArq),arquivo)) {
        //printf(" Linha lida do arquivo: %s",AnaliseDaLinhaArq);

        strcpy(DadosDoCliente,AnaliseDaLinhaArq);
        
        palavraQuebrada = strtok(AnaliseDaLinhaArq, virgula);

        cont = 0;
        while( cont != 1 ) { //para pegar somente a 2ª virgula, por isso é 1. (0 - 1a vigula, 1 - 2a virgula,...)
            //printf( " %s\n", palavraQuebrada );
            palavraQuebrada = strtok(NULL, virgula);
            cont++;
        }
        
        char *CPFEncontrado;
        CPFEncontrado = strstr(palavraQuebrada, CpfAProcurar);

        if(CPFEncontrado!=NULL) {
            if(strcmp(CpfAProcurar,CPFEncontrado)==0) { //strcmp dá erro ao comparar strings com NULL
                printf("\nO CPF: %s foi encontrado! Cadastrando produtos nesse CPF...\n ",CpfAProcurar);
                flag = 0;
                printf("Dados do cliente: %s",DadosDoCliente);
                break; //no caso, para pesquisar dados de cidade (que sao valores repetidos), nao coloco um break aqui, deixo ler todos os que estao iguais.
            }
        }

    }

    if(flag != 0) {
        printf("\n\nO CPF: %s Nao Existe no Banco de dados de cliente. Cadastre dados do cliente primeiro\n Voltando ao menu principal...\n\n",CpfAProcurar);
        return;
    }

    struct Produtos produtos;

    /*
        nome nao esta sendo contabilizado em cont, pq ele é lido pela primeira vez
            valores de cont: 
            1 ---> cpf
            2 --> tel
            3 --> data
            4 --> bairro
            5 --> cidade

   */
    palavraQuebrada = strtok(DadosDoCliente, virgula);
    cont = 1; //para ignorar o valor de nome, que é 0. 
    while( cont != 6 ) { //Lê até o final da linha
    
        palavraQuebrada = strtok(NULL, virgula);

        if(cont == 4) { //bairro
            RemoveEspacoComecoEFinal(palavraQuebrada); //remove os espacos no comeco e final de bairro
            strcpy(produtos.bairroComprador,palavraQuebrada);
            //printf( " %s\n", palavraQuebrada );
        }

        if(cont == 5) { //cidade
            RemoveEspacoComecoEFinal(palavraQuebrada); //remove os espacos no comeco e final de bairro
            strcpy(produtos.cidadeComprador,palavraQuebrada);
            produtos.cidadeComprador[strcspn(produtos.cidadeComprador, "\n")] = 0; //remove o \n
            //printf( " %s\n", palavraQuebrada );
        }

      cont++;

    }
    
    printf("Digite o Nome do Produto: ");
    fgets(produtos.nomeProduto, sizeof(produtos.nomeProduto), stdin );
    fflush(stdin);
    printf("Digite o valor do Produto: ");
    scanf("%f",&produtos.valor);
    printf("**Data da Venda**:\n Digite o Dia da venda: ");
    scanf("%d",&produtos.DiaDaVenda);
    printf("Digite o mes da venda: ");
    scanf("%d",&produtos.MesDaVenda);
    printf("Digite o ano da venda ");
    scanf("%d",&produtos.AnoDaVenda);
    strcpy(produtos.CPFdoComprador,CpfAProcurar);
    fflush(stdin);
    printf("\n\n---Dados da compra:-----\n ");
    printf("\n CPF Comprador: %s\n Bairro do Comprador: %s\n Cidade Comprador: %s\n Nome do produto: %s Valor: %.2f, Data da compra: %02d/%02d/%d\n",produtos.CPFdoComprador,produtos.bairroComprador,produtos.cidadeComprador, produtos.nomeProduto,produtos.valor,produtos.DiaDaVenda,produtos.MesDaVenda,produtos.AnoDaVenda);

    int op;
    do{
        printf("\nDeseja Salvar esses dados acima do produto no arquivo?\n");
        printf("[1] Sim \n");
        printf("[0] Nao\n");
        scanf("%d", &op);
        //system("cls");
    }while(op<0  || op >1);
    if(op == 0) {
        printf("Voltando ao menu principal...");
        return;
    } else {
        printf("Salvando dados do produto no arquivo...");
    }

    produtos.nomeProduto[strcspn(produtos.nomeProduto, "\n")] = 0;

    //Salvando os dados no arquivo:

    fseek(arquivoProdutos,0,SEEK_END);
    //salvando dados com: CPF Comprador, nome produto, valor, dia/mes/ano
    fprintf(arquivoProdutos, "%s, %s, %s, %s, %.2f, %02d/%02d/%d\n",produtos.CPFdoComprador,produtos.bairroComprador,produtos.cidadeComprador,produtos.nomeProduto,produtos.valor,produtos.DiaDaVenda,produtos.MesDaVenda,produtos.AnoDaVenda); 



    printf("saindo...");

    

}

//menu de pesquisa
void pesquisarCadastros(FILE *arquivo, FILE *arquivoProdutos){
    int op;
    if(!confirmarAcao()) return;
    //system("cls");
    do{
        printf("\n ------ PESQUISAR CADASTROS ------- \n\n");
        printf("[1] Listar dados dos clientes \n");
        printf("[2] Consultar dados do Cliente \n");
        printf("[3] Alterar dados do Cliente\n");
        printf("[4] Pesquisar cadastros de produtos \n");
        printf("[0] Volta ao Menu Principal\n");
        printf("Escolha como voce deseja pesquisa:\n");
        scanf("%d", &op);

        switch(op) {
            case 1:
                listarCliente(arquivo);
                break;
            case 2: consultarCliente(arquivo);
                break;
            case 3: alterarDados(arquivo);
                break;
            case 4: pesquisarCompras(arquivoProdutos);
                break;
            case 0:printf("\nSaindo......\n");
                break;
            default:printf("\nOpcao Invalida\n");
                break;
        }
        //system("cls");
    } while(op!=0);

}

void listarCliente(FILE *arquivo) {

    //if(!confirmarAcao()) return;

    printf("Listando Clientes...\n\n");
    char linhaArquivo[2048];
    int i = 1;
    fseek(arquivo,0,SEEK_SET);
    while(fgets(linhaArquivo,sizeof(linhaArquivo),arquivo)) {
        printf(" Cliente [%d]: %s",i,linhaArquivo);
        i++;
    }


}

//consultar cliente
void consultarCliente(FILE *arquivo){
    int op;
    if(!confirmarAcao()) return;
    do{
        printf("\n ------ CONSULTAR CLIENTE ------- \n\n");
	    printf("[1] Por nome completo\n");
	    printf("[2] Por CPF\n");
	    printf("[0] Voltar ao Menu Pesquisar\n");
	    printf("Escolha de que forma deseja consultar os dados do cliente: \n");
	    scanf("%d", &op);

        switch(op){
            case 1:
                printf("nome completo\n");
                consultaNomecompleto(arquivo);
                break;
            case 2:
                printf("CPF\n");
                ConsultaCPF(arquivo);
                break;
            case 0:
                printf("Saindo......\n");
                break;
            default:printf("\nOpcao Invalida\n");
                break;
        }
        //system("cls");
	} while(op!=0);
}

void consultaNomecompleto(FILE *arquivo) {
    printf("\n**Consulta por nome do cliente**\n");

    if(erroNoArquivo(arquivo) == 1) {
        return;
    }

    char NomeAProcurar[50];
    printf("\nDigite o Nome do cliente que voce quer consultar: "); 
    fflush(stdin);
    fgets(NomeAProcurar,sizeof(NomeAProcurar),stdin);
    NomeAProcurar[strcspn(NomeAProcurar,"\n")]= 0;

    char AnaliseDaLinhaArq[2048];
    const char virgula[2] = ",";
    int contagemDeVirgulas=0;
    char *palavraQuebrada;
    int flag = -1 ;
    
    char DadosDoCliente[1000];

    fseek(arquivo,0,SEEK_SET);
    while(fgets(AnaliseDaLinhaArq,sizeof(AnaliseDaLinhaArq),arquivo)) {
        //printf(" Linha lida do arquivo: %s",AnaliseDaLinhaArq);
        
        strcpy(DadosDoCliente,AnaliseDaLinhaArq);
        
        palavraQuebrada = strtok(AnaliseDaLinhaArq, virgula);

        contagemDeVirgulas = 0;
        while( contagemDeVirgulas != 0 ) { //para pegar somente a 2ª virgula, por isso é 1. (0 - 1a vigula, 1 - 2a virgula,...)
            printf( " %s\n", palavraQuebrada );
            palavraQuebrada = strtok(NULL, virgula);
            contagemDeVirgulas++;
        }
        
        char *NomeEncontrado;
        NomeEncontrado = strstr(palavraQuebrada, NomeAProcurar);

        if(NomeEncontrado!=NULL) {
            if(strcmp(NomeAProcurar,NomeEncontrado)==0) { //strcmp dá erro ao comparar strings com NULL
                printf("\nO Nome '%s' foi encontrado!\n",NomeAProcurar);
                printf("Dados do cliente: %s \n ", DadosDoCliente);
                flag = 0;
            }
        }

    }

    if(flag != 0) {
        printf("\n\nO Nome '%s' Nao Existe no Banco de dados de cliente. Voltando ao menu principal...\n\n",NomeAProcurar);
        return;
    }

}

void ConsultaCPF(FILE *arquivo) {
    char CpfAProcurar[30];
    printf("\nDigite o CPF do cliente: "); 
    fflush(stdin);
    fgets(CpfAProcurar,sizeof(CpfAProcurar),stdin);
    //printf("CPF lido: %s ", CpfAProcurar);
    CpfAProcurar[strcspn(CpfAProcurar,"\n")]= 0;

    char AnaliseDaLinhaArq[2048];
    const char virgula[2] = ",";
    int contagemDeVirgulas=0;
    char *palavraQuebrada;
    int flag = -1 ;

    char DadosDoCliente[1000];
    
    fseek(arquivo,0,SEEK_SET);
    while(fgets(AnaliseDaLinhaArq,sizeof(AnaliseDaLinhaArq),arquivo)) {
        //printf(" Linha lida do arquivo: %s",AnaliseDaLinhaArq);
        strcpy(DadosDoCliente,AnaliseDaLinhaArq);
        
        palavraQuebrada = strtok(AnaliseDaLinhaArq, virgula);

        contagemDeVirgulas = 0;
        while( contagemDeVirgulas != 1 ) { //para pegar somente a 2ª virgula, por isso é 1. (0 - 1a vigula, 1 - 2a virgula,...)
            //printf( " %s\n", palavraQuebrada );
            palavraQuebrada = strtok(NULL, virgula);
            contagemDeVirgulas++;
        }
        
        char *CPFEncontrado;
        CPFEncontrado = strstr(palavraQuebrada, CpfAProcurar);

        if(CPFEncontrado!=NULL) {
            if(strcmp(CpfAProcurar,CPFEncontrado)==0) { //strcmp dá erro ao comparar strings com NULL
                printf("\nO CPF: %s foi encontrado!\n ",CpfAProcurar);
                printf("Dados do Cliente: %s \n",DadosDoCliente);
                flag = 0;
            }
        }

    }

    if(flag != 0) {
        printf("\n\nO CPF: %s Nao Existe no Banco de dados de cliente.\n Voltando ao menu principal...\n\n",CpfAProcurar);
        return;
    }

}

//alterar dados
void alterarDados(FILE *arquivo) {

    char CpfAProcurar[30];
    printf("\nDigite o CPF do cliente do qual quer alterar dados: "); 
    fflush(stdin);
    fgets(CpfAProcurar,sizeof(CpfAProcurar),stdin);
    //printf("CPF lido: %s ", CpfAProcurar);
    CpfAProcurar[strcspn(CpfAProcurar,"\n")]= 0;

    char AnaliseDaLinhaArq[2048];
    const char virgula[2] = ",";
    int contagemDeVirgulas=0;
    char *palavraQuebrada;
    int flag = -1 ;

    char DadosDoCliente[1000];
    
    fseek(arquivo,0,SEEK_SET);
    //fseek(arquivo,posLinhaArqCliente,SEEK_SET);
    while(fgets(AnaliseDaLinhaArq,sizeof(AnaliseDaLinhaArq),arquivo)) {
        //printf(" Linha lida do arquivo: %s",AnaliseDaLinhaArq);
        strcpy(DadosDoCliente,AnaliseDaLinhaArq);
        
        palavraQuebrada = strtok(AnaliseDaLinhaArq, virgula);

        contagemDeVirgulas = 0;
        while( contagemDeVirgulas != 1 ) { //para pegar somente a 2ª virgula, por isso é 1. (0 - 1a vigula, 1 - 2a virgula,...)
            //printf( " %s\n", palavraQuebrada );
            palavraQuebrada = strtok(NULL, virgula);
            contagemDeVirgulas++;
        }
        
        char *CPFEncontrado;
        CPFEncontrado = strstr(palavraQuebrada, CpfAProcurar);
        

        if(CPFEncontrado!=NULL) {
            if(strcmp(CpfAProcurar,CPFEncontrado)==0) { //strcmp dá erro ao comparar strings com NULL
                printf("\nO CPF: %s foi encontrado!\n ",CpfAProcurar);
                printf("Dados do Cliente: %s \n",DadosDoCliente);
                flag = 0;
                break;
            }
        }

    }

    if(flag != 0) {
        printf("\n\nO CPF: %s Nao Existe no Banco de dados de cliente.\n",CpfAProcurar);
        return;
    }

    int op;
    char DadoAlterar[30];
    do{
        printf("\n ------ QUAL DADO VOCE QUER ALTERAR DO CLIENTE? ------- \n\n");
        printf("[1] Bairro \n");
        printf("[2] Cidade \n");
        printf("[3] Telefone \n");
        printf("[0] Voltar ao Menu Pesquisar \n");
        printf("Escolha a informacao que deseja alterar: \n");
        scanf("%d", &op);
        switch(op){
            case 1:
                printf("Digite o nome do bairro para atualizar do cliente: ");
                fflush(stdin);
                fgets(DadoAlterar,sizeof(DadoAlterar),stdin);
                DadoAlterar[strcspn(DadoAlterar, "\n")] = 0;
                //valores de op: 1 - Bairro, 2- Cidade, 3 - Telefone;
                alterarDadosCliente(arquivo,DadosDoCliente,DadoAlterar,op);
                return;
                break;
            case 2:
                printf("Digite o nome da Cidade para atualizar do cliente: ");
                fflush(stdin);
                fgets(DadoAlterar,sizeof(DadoAlterar),stdin);
                DadoAlterar[strcspn(DadoAlterar, "\n")] = 0;
                //valores de op: 1 - Bairro, 2- Cidade, 3 - Telefone;
                alterarDadosCliente(arquivo,DadosDoCliente,DadoAlterar,op);
                return;
                break;
            case 3:
                printf("Digite o numero do telefone para atualizar do cliente: ");
                fflush(stdin);
                fgets(DadoAlterar,sizeof(DadoAlterar),stdin);
                DadoAlterar[strcspn(DadoAlterar, "\n")] = 0;
                //valores de op: 1 - Bairro, 2- Cidade, 3 - Telefone;
                alterarDadosCliente(arquivo,DadosDoCliente,DadoAlterar,op);
                return;
                break;
            case 0:
                printf("Saindo......\n");
                break;
            default:printf("\nOpcao Invalida\n");
                break;
        }
    } while(op!=0);

}

alterarDadosCliente(FILE *arquivo, char DadosDoCliente[30],char DadoAAlterar[30],int cod_Alteracao) {
    
    //printf("Dados Do cliente: %s",DadosDoCliente);
    //printf("Dado a Alterar: %s", DadoAAlterar);
    //printf("Codigo de alteracao: %d\n", cod_Alteracao);

    char DadosClienteAux[1000];
    strcpy(DadosClienteAux,DadosDoCliente);

    struct Cliente clienteAux;

    /*
        valores de cont: 
        1 ---> nome
        2 --> cpf
        3 --> telefone
        4 --> data
        5 --> bairro
        6 --> cidade
   */
    const char virgula[2] = ",";
    char *palavraQuebrada;
    palavraQuebrada = strtok(DadosDoCliente, virgula);
    int cont = 0;
    char DataClienteStringAux[15];
    while( cont != 7 ) { //Lê até o final da linha
        
        if(cont == 0) { //Nome
            RemoveEspacoComecoEFinal(palavraQuebrada); //remove os espacos no comeco e final de bairro
            strcpy(clienteAux.NomeCompletoDoCliente,palavraQuebrada);
            //printf( "nome: %s\n", palavraQuebrada );
        }

        if(cont == 1) { //CPF
            RemoveEspacoComecoEFinal(palavraQuebrada);
            strcpy(clienteAux.CPF,palavraQuebrada);
            //printf( "cpf: %s\n", palavraQuebrada );
        }

        if(cont == 2) { //telefone
            RemoveEspacoComecoEFinal(palavraQuebrada); //remove os espacos no comeco e final de bairro
            strcpy(clienteAux.telefone,palavraQuebrada);
            //printf( "telefone:  %s\n", palavraQuebrada );
        }
        if(cont == 3) { //data de nascimento
            RemoveEspacoComecoEFinal(palavraQuebrada);
            strcpy(DataClienteStringAux,palavraQuebrada);
            //DataClienteStringAux[strcspn(DataClienteStringAux,'\n')==0];
            //printf( "dtNasc: %s\n", palavraQuebrada );
        }
        if(cont == 4) { //bairro
            RemoveEspacoComecoEFinal(palavraQuebrada);
            strcpy(clienteAux.bairro,palavraQuebrada);
            //printf( "Bairro: %s\n", palavraQuebrada );
        }

        if(cont == 5 ) { //cidade
            RemoveEspacoComecoEFinal(palavraQuebrada);
            strcpy(clienteAux.cidade,palavraQuebrada);
            clienteAux.cidade[strcspn(clienteAux.cidade, "\n")] = 0; //remove o \n do final da linha
            //printf( "Cidade: %s\n", palavraQuebrada );
        }
        palavraQuebrada = strtok(NULL, virgula); //a cada iteracao uma parte da linha é quebrada

      cont++;

    }

    //printf("\nDados do cliente da struct:\n ");
    //printf("\n Nome Completo: %s CPF: %s Telefone: %s Data de nascimento: %s Bairro: %s Cidade: %s \n ",clienteAux.NomeCompletoDoCliente,clienteAux.CPF,clienteAux.telefone,DataClienteStringAux,clienteAux.bairro,clienteAux.cidade);

    switch (cod_Alteracao) {
        case 1: //bairro
            strcpy(clienteAux.bairro,DadoAAlterar);
            break;

        case 2: //cidade
            strcpy(clienteAux.cidade,DadoAAlterar);
            break;

        case 3: //telefone
            strcpy(clienteAux.telefone,DadoAAlterar);
            break;

    }

    //printf("Valores a serem Atuais do cliente:");
    //printf("\n Nome Completo: %s CPF: %s Telefone: %s Data de nascimento: %s \n Bairro: %s Cidade: %s \n ",clienteAux.NomeCompletoDoCliente,clienteAux.CPF,clienteAux.telefone,DataClienteStringAux,clienteAux.bairro,clienteAux.cidade);

    //salva esses dados no final do arquivo:
    fseek(arquivo,0,SEEK_END);
    erroNoArquivo(arquivo);
    fprintf(arquivo,"%s, %s, %s, %s, %s, %s\n",clienteAux.NomeCompletoDoCliente,clienteAux.CPF,clienteAux.telefone,DataClienteStringAux,clienteAux.bairro,clienteAux.cidade);

    //Salvando Dados:

    FILE* temporario = fopen("Temporario.txt", "a+");

    if (temporario == NULL) {
        printf("Erro na abertura de arquivo temporario!");
        return 0;
    } else {
        printf("O arquivo Temporario foi aberto com sucesso!");
    }

    //DadosDoCliente[strcspn(DadosDoCliente,'\n')==0];
    //printf("Dados do Cliente no salvamento: %s *******Testando se tem /n",DadosClienteAux);


    fseek(arquivo,0,SEEK_SET); //aponta para o comeco do arq original
    char linhaDoArquivo[2048];
    int flag = 0;
    while(fgets(linhaDoArquivo,sizeof(linhaDoArquivo),arquivo)){
        //linhaDoArquivo[strcspn(linhaDoArquivo,"\n")]= 0;
        if(strcmp(linhaDoArquivo,DadosClienteAux)==0){
            flag++;
            if(flag>1) {
                //se flag for maior que um, quer dizer que esse dado está repetido no arquivo, entao tem que verificar no cadastro de clientes se ja existe esse cliente no banco de dados. observar se ja existe essa funcionalidade no sistema. para que dados nao fiquem repetidos.
            }
        } else {
            fputs(linhaDoArquivo,temporario);
        }
    }
    fclose(arquivo);
    fclose(temporario);
    remove("BancoDeDadosCliente.txt");

    int ret = rename("Temporario.txt", "BancoDeDadosCliente.txt");
	
    if(ret == 0) {
      printf("Arquivo Renomeado com sucesso");
    } else {
      printf("Nao foi possivel renomear o arquivo");
    }
    remove("Temporario.txt");

    //abre novamente o arquivo para continuar no programa
    arquivo = fopen("BancoDeDadosCliente.txt", "a+");

    if (arquivo == NULL) {
        printf("Erro na abertura de arquivo de clientes!");
        return 0;
    } else {
        printf("O arquivo foi aberto com sucesso!");
    }


    printf("\n **** Alterado com sucesso! **** \n");
    listarCliente(arquivo);

}


//pesquisar compras
void pesquisarCompras(FILE *arquivoProdutos){

    char DadoASerPesquisado[20];
    int op;
    if(!confirmarAcao()) return;
    do{
        printf("\n ------ PESQUISAR COMPRAS ------- \n\n");
        printf("[1] Bairro \n");
        printf("[2] Cidade \n");
        printf("[3] Valor \n");
        printf("[0] Voltar ao Menu Pesquisar \n");
        printf("Escolha a Forma de Pesquisa: \n");
        scanf("%d", &op);

        switch(op){
            case 1:
                printf("Digite o bairro que voce quer buscar no arquivo de produtos: ");
                fflush(stdin);
                fgets(DadoASerPesquisado, sizeof(DadoASerPesquisado),stdin);
                pesquisaCompras(arquivoProdutos,DadoASerPesquisado,op);
                break;
            case 2:
                printf("Digite A cidade que voce quer buscar no arquivo de produtos: ");
                fflush(stdin);
                fgets(DadoASerPesquisado, sizeof(DadoASerPesquisado),stdin);
                pesquisaCompras(arquivoProdutos,DadoASerPesquisado,op);
                break;
            case 3:
                printf("Digite O valor  que voce quer buscar no arquivo de produtos: ");
                float valor;
                fflush(stdin); 
                scanf("%f",&valor);
                fflush(stdin);
                pesquisaComprasPorValor(arquivoProdutos,valor);
                break;
            case 0:
                printf("Voltar ao menu anterior\n");
                break;
        }

        //system("cls");
    } while(op!=0);
}

void pesquisaCompras(FILE *arquivoProdutos, char DadoASerPequisado[20],int op) {

    RemoveEspacoComecoEFinal(DadoASerPequisado);
    DadoASerPequisado[strcspn(DadoASerPequisado,"\n")] = 0;

    printf("\n\nVALOR DE CONSULTA: %s\n",DadoASerPequisado);

    int MarcadorDeVirgula = op;
    
    char AnaliseDaLinhaArq[2048];
    const char virgula[2] = ",";
    int contagemDeVirgulas=0;
    char *palavraQuebrada;
    int flag = -1 ;
    int cont = 1;

    char DadosDoProduto[1000];
    
    fseek(arquivoProdutos,0,SEEK_SET);
    while(fgets(AnaliseDaLinhaArq,sizeof(AnaliseDaLinhaArq),arquivoProdutos)) {
        //printf(" Linha lida do arquivo: %s",AnaliseDaLinhaArq);
        strcpy(DadosDoProduto,AnaliseDaLinhaArq);
        
        palavraQuebrada = strtok(AnaliseDaLinhaArq, virgula);

        
        contagemDeVirgulas = 0;
        while( contagemDeVirgulas != MarcadorDeVirgula ) { //para pegar somente a 2ª virgula, por isso é 1. (0 - 1a vigula, 1 - 2a virgula,...)
            //printf( " %s\n", palavraQuebrada );
            palavraQuebrada = strtok(NULL, virgula);
            contagemDeVirgulas++;
        }
        
        char *DadoEncontrado;
        DadoEncontrado = strstr(palavraQuebrada, DadoASerPequisado);

        if(DadoEncontrado!=NULL) {
            if(strcmp(DadoEncontrado,DadoASerPequisado)==0) { //strcmp dá erro ao comparar strings com NULL
                //printf("\nVALOR DE CONSULTA: %s !\n ",DadoASerPequisado);
                printf("\tCompra[%d]: %s",cont,DadosDoProduto);
                cont++;
                flag++;
            }
        }

    }

    if(flag == -1) {
        printf("\n\nO Dado: %s Nao Existe no Banco de dados de Produtos.\n Voltando ao menu principal...\n\n",DadoASerPequisado);
    }

} 


void removeTodosEspacos(char *str){ 
    int count=0,i;
    for(i=0;str[i];i++){
        if(str[i]!=' '){
            str[count++]=str[i];
        }
    }
    str[count]=0;
}

void RemoveEspacoComecoEFinal( char *str ) {

    int i;
    // lado esquerdo
    for( i=0; i<strlen(str) && *(str + i) == ' '; i++);

    strcpy(str, str+i);

    // lado direito
    for(i = strlen(str); *(str + i) == ' '; i-- );

    *(str + i)  = '\0';
  
    return;
}
