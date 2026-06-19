# Simulador de Agência de Viagens — Controle de Trânsito

Simulador de gerenciamento de transporte desenvolvido em **C++** para a disciplina de Linguagem de Programação. O sistema controla a alocação de veículos, rotas, cadastro de passageiros e o avanço do tempo da simulação através de orientação a objetos e gerenciamento dinâmico de ponteiros.

---

## Compilação e Execução

O projeto é modularizado em múltiplos arquivos de cabeçalho e um arquivo principal.

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

## Comandos

### 1. `CADASTRAR_CIDADE`

Adiciona uma nova cidade.

```
CADASTRAR_CIDADE
[Nome da Cidade]
```

**Exemplo:**
```
CADASTRAR_CIDADE
Natal
```

---

### 2. `CADASTRAR_TRAJETO`

Cria uma rota de ligação direta entre duas cidades já existentes.

```
CADASTRAR_TRAJETO
[Cidade de Origem]
[Cidade de Destino]
[Tipo: 'T' para Terrestre ou 'A' para Aquático]
[Distância em km]
```

**Exemplo:**
```
CADASTRAR_TRAJETO
Natal
Mossoró
T
280.0
```

---

### 3. `CADASTRAR_TRANSPORTE`

Insere um veículo na frota da agência.

```
CADASTRAR_TRANSPORTE
[Nome do Veículo]
[Tipo: 'T' ou 'A'] [Capacidade] [Velocidade em km/h] [Distância para Descanso] [Tempo de Descanso]
[Nome da Cidade Inicial]
```

---

### 4. `CADASTRAR_PASSAGEIRO`

Registra um passageiro no sistema e o associa a uma cidade de origem.

```
CADASTRAR_PASSAGEIRO
[Nome do Passageiro]
[Nome da Cidade]
```

**Exemplo:**
```
CADASTRAR_PASSAGEIRO
Jose
Natal
```

---

### 5. `CADASTRAR_VIAGEM`

Inicia o despacho de um transporte com passageiros entre duas cidades.

```
CADASTRAR_VIAGEM
[Nome do Transporte]
[Cidade de Origem]
[Cidade de Destino]
[Quantidade de Passageiros]
[Nome do Passageiro 1]
[Nome do Passageiro 2]
...
```

**Funcionamento com Escalas (Conexões):** O sistema valida se o veículo e os passageiros estão na cidade de origem. Se houver um trajeto direto, a viagem inicia-se imediatamente. Caso contrário, o sistema busca uma cidade de conexão viável e gera uma estrutura encadeada de viagens utilizando ponteiros (proxima), mantendo o transporte e passageiros em trânsito até a conclusão total da viagem.

**Exemplo:**
```
CADASTRAR_VIAGEM
Onibus
Natal
Fortaleza
1
Maria
```

---

### 6. `CADASTRAR_HORAS`

Avança o relógio da simulação hora a hora, movimentando os veículos em trânsito e gerenciando a fadiga dos motoristas.

```
CADASTRAR_HORAS
[Quantidade de Horas (número inteiro)]
```
> **Funcionamento:** O tempo avança de hora em hora. A cada ciclo, o sistema verifica se o veículo atingiu o limite de quilômetros para condução (Distância para Descanso). Se atingido, o transporte entra em estado de repouso obrigatório pelo Tempo de Descanso determinado, pausando seu avanço na estrada enquanto o relógio geral continua correndo. Ao atingir o destino, o estado de fadiga é reiniciado.

**Exemplo:**
```
CADASTRAR_HORAS
2
```

---

### 7. `RELATAR_ESTADO`

Imprime um relatório completo do estado atual da simulação: cidades existentes, veículos estacionados ou em viagem, e localização de cada passageiro.

```
RELATAR_ESTADO
```

---

### 8. `FIM`

Realiza a liberação da memória alocada dinamicamente e encerra a execução do simulador.

```
FIM
```
