# Agenda de Contatos
Este é um simples programa em C para gerenciar uma agenda de contatos. Ele oferece as seguintes funcionalidades:

# Funcionalidades

1. **Cadastrar Contato**
   - Permite cadastrar novos contatos com nome, DDD e número de telefone.
2. **Consultar Contato por Nome**
   - Facilita a busca por contatos através do nome.
3. **Listar Todos os Contatos**
   - Exibe todos os contatos cadastrados na agenda.
4. **Editar Contato**
   - Permite a edição de informações de um contato existente.
5. **Excluir Contato**
   - Remove um contato da agenda.
6. **Sair**
   - Encerra o programa.

# Compilação e Execução
Para compilar o programa, utilize um compilador C padrão, por exemplo:

1. **Compilar:**
   ```bash
   gcc index.c -o agenda
   
2. **executar:**
   ```bash
   ./agenda

# Observações
- Os contatos são armazenados no arquivo contatos.txt
- Para Funcionamento correto do codigo depois de compilado voce deve ter um arquivo '**contatos.txt**' no mesmo diretorio que o programa compilado.
- O código utiliza a biblioteca windows.h para a função Sleep, o que pode ser ajustado conforme o sistema operacional.
