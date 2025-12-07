# Código Base - Sistema de Gestão de Treinos

Este é o código base (esqueleto) para o trabalho de implementação do Sistema de Gestão de Treinos. O código está incompleto e contém TODOs indicando onde você deve implementar a lógica.

## O que já está implementado

- Estrutura completa de classes (headers)
- Classe base Exercicio completamente implementada
- Menu principal e submenus (main.cpp)
- Funções utilitárias (Utils.h)
- Makefile configurado

## O que você precisa implementar

### Classes Derivadas (Cardio.cpp e Forca.cpp)
- Construtores (novo cadastro e leitura de arquivo)
- Método exibirDetalhes()
- Método calcularTempoEstimado()
- Método calcularCaloriasGastas()
- Método getTipo()
- Getters específicos

### Classe Ficha (Ficha.cpp)
- Inicialização da variável estática proximoId
- Construtores
- Destrutor (importante: não deletar exercícios!)
- Método adicionarExercicio()
- Método exibirFicha()
- Métodos calcularTempoTotal() e calcularCaloriasTotais()
- Getters
- Método atualizarProximoId()

### Classe Historico (Historico.cpp)
- Método adicionarRegistro()
- Método exibirHistorico()
- Método getRegistros()
- Método carregarDeArquivo()
- Método salvarEmArquivo()

### Classe Sistema (Sistema.cpp)
- Destrutor (deletar ponteiros)
- Método carregarDados() (exercícios e fichas)
- Método salvarDados() (exercícios e fichas)
- Método buscarExercicioPorId()
- Método buscarFichaPorId()
- Método cadastrarExercicio()
- Método listarExercicios()
- Método excluirExercicio()
- Método criarFicha()
- Método adicionarExercicioFicha()
- Método listarFichas()
- Método registrarTreino()
- Método exibirHistorico()

## Compilação

O código compila mesmo incompleto (com warnings esperados):

```bash
make clean
make
```

Os warnings sobre parâmetros não usados são normais e desaparecerão conforme você implementa os métodos.

## Formato dos Arquivos

### exercicios.txt
- Cardio: TIPO;ID;NOME;DURACAO;CALORIAS_POR_MIN;STATUS
- Força: TIPO;ID;NOME;CARGA;SERIES;REPETICOES;DESCANSO;STATUS
- TIPO: 1 = Cardio, 2 = Força
- STATUS: 1 = Ativo, 0 = Inativo

### fichas.txt
- Formato: ID_FICHA;NOME_FICHA;TOTAL_EXERCICIOS;ID_EX_1;ID_EX_2;...

### historico.txt
- Formato: DATA;ID_FICHA;NOME_FICHA;TEMPO_TOTAL;CALORIAS_TOTAL

## Dicas

1. Leia os TODOs: Cada método tem comentários TODO explicando o que fazer
2. Siga a ordem: Comece pelas classes derivadas (Cardio/Forca), depois Ficha, depois Historico, por último Sistema
3. Teste incrementalmente: Implemente um método e teste antes de passar para o próximo
4. Polimorfismo: Use dynamic_cast quando precisar converter Exercicio* para Cardio* ou Forca*
5. Memory Management: Lembre-se de deletar os ponteiros no destrutor do Sistema
6. Arquivos: Use std::ifstream para ler e std::ofstream para escrever
7. Parsing: Use std::stringstream com getline(ss, token, ';') para separar campos

## Objetivos de Aprendizado

- Herança e polimorfismo
- Classes abstratas e métodos virtuais
- Gerenciamento de memória com ponteiros
- Manipulação de arquivos de texto
- Estruturas de dados (vector)
- Variáveis estáticas

## Importante

- NÃO delete os exercícios no destrutor de Ficha: Eles pertencem ao Sistema
- Use construtores de inicialização: : Exercicio(nome) para chamar a classe base
- Atualize proximoId: Quando carregar do arquivo, atualize o contador estático
- Validação: Verifique se ponteiros não são nullptr antes de usar
- Formatação: Use std::fixed e std::setprecision(2) para números decimais

## Estrutura do Projeto

```
codigo_base/
├── Exercicio.h          Completo
├── Exercicio.cpp        Completo
├── Cardio.h             Completo
├── Cardio.cpp           TODO
├── Forca.h              Completo
├── Forca.cpp            TODO
├── Ficha.h              Completo
├── Ficha.cpp            TODO
├── Historico.h          Completo
├── Historico.cpp        TODO
├── Sistema.h            Completo
├── Sistema.cpp           TODO
├── main.cpp             Completo
├── Utils.h              Completo
└── Makefile             Completo
```

## Começando

1. Leia este README completamente
2. Compile o projeto: make
3. Comece implementando Cardio.cpp e Forca.cpp
4. Depois implemente Ficha.cpp
5. Em seguida Historico.cpp
6. Por último Sistema.cpp (mais complexo)
7. Teste cada funcionalidade conforme implementa
