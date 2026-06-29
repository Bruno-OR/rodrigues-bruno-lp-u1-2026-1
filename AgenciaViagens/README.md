# Simulador de Agência de Viagens — Controle de Trânsito

Simulador de gerenciamento de transporte desenvolvido em **C++** para a disciplina de Linguagem de Programação. O sistema controla a alocação de veículos, rotas, cadastro de passageiros e o avanço do tempo da simulação através de orientação a objetos e gerenciamento dinâmico de ponteiros.

---

## Compilação e Execução

O projeto é modularizado em múltiplos arquivos de cabeçalho e um arquivo principal.

## Demonstração

Simulador de Agência de Viagens em C++ | Projeto LP1: (https://youtu.be/Tp3QCHGKiiU)

### Compilar

```bash
g++ agencia.cpp -o agencia
```

### Executar manualmente pelo CMD

```bash
agencia
```

### Executar com arquivo de entrada

```bash
agencia < Arquivo.txt
```

---

## Persistência de Dados

O sistema salva automaticamente o estado ao encerrar em um arquivo estado.txt. Na próxima execução, se o arquivo existir, os dados são restaurados automaticamente. Transportes e passageiros que estavam em trânsito no momento do encerramento não são recuperados.


## Menu Interativo

Ao executar o programa pelo terminal, um menu é exibido com as opções disponíveis:

```
=======================================================
           SISTEMA INTEGRADO DE TRÂNSITO
=======================================================
  [1] Cadastrar Cidade
  [2] Cadastrar Trajeto
  [3] Cadastrar Transporte
  [4] Cadastrar Passageiro
  [5] Iniciar Viagem (Direta ou com Escalas)
  [6] Avançar Relógio (Simulação de Horas)
  [7] Relatar Estado Geral da Agência
  [8] Encerrar Programa (FIM)
-------------------------------------------------------
```

---

## Comandos

### 1. CADASTRAR_CIDADE

Adiciona uma nova cidade. Cidades duplicadas são rejeitadas.

**Exemplo:**
```
[Nome da Cidade: Natal]
```

---

### 2. CADASTRAR_TRAJETO

Cria uma rota de ligação direta entre duas cidades já existentes. O tipo deve ser obrigatoriamente `T` para terrestre ou `A` para aquático e a distância deve ser maior que zero.

**Exemplo:**
```
[Cidade de Origem: Natal]
[Cidade de Destino: Mossoró]
[Tipo: T]
[Distância (em km): 280.0]
```

---

### 3. CADASTRAR_TRANSPORTE

Insere um veículo na frota da agência. O tipo deve ser obrigatoriamente `T` ou `A`.

**Exemplo:**
```
[Nome do Veículo: Ônibus 01]
[Tipo: 'T'] 
[Capacidade: 50] 
[Velocidade em km/h: 80] 
[Distância para Descanso (em km): 100] 
[Tempo de Descanso (em horas): 1]
[Nome da Cidade Inicial: Natal]
```

---

### 4. CADASTRAR_PASSAGEIRO

Registra um passageiro no sistema e o associa a uma cidade de origem.

**Exemplo:**
```
[Nome do Passageiro: José]
[Nome da Cidade: Natal]
```

---

### 5. CADASTRAR_VIAGEM

Inicia o despacho de um transporte com passageiros entre duas cidades.


**Funcionamento com Escalas (Conexões):** O sistema valida se o veículo e os passageiros estão na cidade de origem. Se houver um trajeto direto, a viagem inicia-se imediatamente. Caso contrário, o sistema realiza uma busca por todas as cidades encontradas para achar o menor caminho possível, podendo encadear quantas conexões forem necessárias. Cada trecho é representado como uma viagem separada conectada por ponteiros (`proxima`), e os passageiros e transporte só são movidos para o destino final quando o último trecho é concluído.

**Exemplo:**
```
[Nome do Transporte: Ônibus 01]
[Cidade de Origem: Natal]
[Cidade de destino final: Mossoró]
[Quantidade de Passageiros: 1]
[Nome do Passageiro: José]
```

---

### 6. CADASTRAR_HORAS

Avança o relógio da simulação hora a hora, movimentando os veículos em trânsito e gerenciando a fadiga dos motoristas. A quantidade de horas deve ser maior que zero.

> **Funcionamento:** O tempo avança de hora em hora. A cada ciclo, o sistema verifica se o veículo atingiu o limite de quilômetros para condução (Distância para Descanso). Se atingido, o transporte entra em estado de repouso obrigatório pelo Tempo de Descanso determinado, pausando seu avanço na estrada enquanto o relógio geral continua correndo. Ao atingir o destino, os quilômetros acumulados são zerados.

**Exemplo:**
```
[Quantidade de Horas (número inteiro): 2]
```

---

### 7. RELATAR_ESTADO

Imprime um relatório completo do estado atual da simulação, contendo:

- **Cidades cadastradas**
- **Status da frota:** veículos estacionados ou em viagem, com indicação de descanso
- **Localização dos passageiros:** cidade atual ou, se em trânsito, origem, destino e transporte utilizado
- **Viagens em andamento:** trecho atual, horas em trânsito
- **Cidades mais visitadas:** ordenadas por número de chegadas registradas

---

### 8. FIM

Salva o estado atual em `estado.txt`, libera a memória alocada dinamicamente e encerra a execução do simulador.