# Workshop de FreeRTOS

### Nota Prévia

Este documento está no formato Markdown (.md). Para o leres com a formatação visual correta (títulos grandes, negritos, formatação de código), sugerimos as seguintes opções:

- No VS Code: Abre o ficheiro e prime `Ctrl + Shift + V` _(Windows/Linux)_ ou `Cmd + Shift + V` _(macOS)_ para abrir a janela de pré-visualização.

- No Navegador (Online): Podes arrastar o ficheiro para um visualizador online gratuito como o Dillinger.io ou o StackEdit.

---

Todos os mini desafios encontram-se neste ficheiro, que contêm o enunciado do desafio e o slide onde se encontra.

Para facilitar é fornecido um código de base a preencher. Substitui os comentários (`/* */`) por pedaços de código correcto

---

# Mini Desafio 1

## **Módulo 2 · Slide 17**

### Objetivo

- **Task 1 (Blink):** Piscar o LED integrado a cada 500ms.
- **Task 2 (Serial):** Imprimir uma mensagem e o tempo atual do sistema (`xTaskGetTickCount`) a cada 2 segundos.

### Regras

1.  **Não podes usar o `void loop()`** do Arduino (deve ficar vazio).
2.  Cria ambas as tasks dentro do `void setup()`.
3.  Ambas as tarefas devem ter a **mesma prioridade** (ex: 1).

---

### Código Base

Copia o código abaixo para a tua IDE para começares o exercício:

```cpp
#include <FreeRTOS.h>

void Task1(void* params)
{
  for(;;)
  {
    /* */
    /* */
  }
}

void Task2(void* params)
{
  TickType_t xLastWakeTime  = /* */;
  for(;;)
  {
    /* */
    /* */
  }
}

void setup()
{
  Serial.begin(115200);
  while(!Serial){ delay(10); }
  pinMode(LED_BUILTIN, OUTPUT);



  // Criação da Task1
  xTaskCreate(
    /*...*/,
    /*...*/,
    /*...*/,
    /*...*/,
    /*...*/,
    /*...*/
  );

  // Criação da Task2
  xTaskCreate(
    /*...*/,
    /*...*/,
    /*...*/,
    /*...*/,
    /*...*/,
    /*...*/
  );
}

void loop() { /* Vazio*/ }
```

---

# Mini Desafio 2

## **Módulo 3 · Slide 26**

### Objetivo

Simular um sistema onde um sensor (botão) dispara um alarme, mas o ecrã/serial tem de ser partilhado de forma segura.

### Cenário

1. **`Task_Blink`**: Pisca um LED a cada 200ms e escreve `"Status OK"` a cada 1 segundo (Prioridade 1).

2. **`ISR_Botao` / `Task_Botao`**: Deteta um clique e dá um **Binary Semaphore** _(podem usar uma task que faz digitalRead( ) se não estão familiarizados com Interrupts)_

3. **`Task_Alarme`**: Espera pelo semáforo. Quando recebe, escreve `"ALARME DISPARADO"` no Serial 5 vezes (Prioridade 3).

4. **Recurso Crítico**: O Serial deve ser protegido por um Mutex

---

### Código Base

Copia o código abaixo para a tua IDE para começares o exercício:

```cpp
#include <FreeRTOS.h>

#define MODO_ISR // Comenta-me se não te sentes confortável com ISR para usar uma Task de Polling


SemaphoreHandle_t xbinarySemaphore;
SemaphoreHandle_t xSerialMutex;

void Task_Blink(void *pvParameters)
{
  int count = 0;
  TickType_t xLastWakeTime = xTaskGetTickCount();

  for(;;)
  {
    /* */

    count++;
    if (count >= 5)
    {
      if (xSemaphoreTake(/* */, /* */) == pdTRUE)
      {
        /* */
        xSemaphoreGive(/* */);
      }
      count = /* */;
    }

    vTaskDelayUntil(/* */, /* */);
  }
}

#ifdef MODO_ISR
// ISR (Interrupt Service Routine)
/*
    * O que é? Uma função chamada diretamente pelo Hardware quando o pino muda de estado.
    * Regras: Deve ser ultra rápida. Nunca uses Serial.print ou Delays aqui. Qualquer variável externa à função que é alterada dentro do interrupt deve ser volatile ex: volatile int x = 0;
*/
void ISR_Botao()
{
  /* */
  xSemaphoreGiveFromISR(/* */, /* */);
  portYIELD_FROM_ISR(/* */);
}

#else

void Task_Butao(void* p)
{
  bool prevState = false;
  for(;;)
  {
    bool currentState = !digitalRead(/* */);

    if(/* */)
    {
      /* */
    }

    prevState = /* */;

    /* */
  }
}

#endif

void Task_Alarm(void* params)
{
  for(;;)
  {
    if(xSemaphoreTake(/* */, /* */) == pdTRUE)
    {
      if(xSemaphoreTake(/* */, /* */) == pdTRUE)
      {
        /* */
        xSemaphoreGive(/* */);
      }
    }
  }
}


void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  /* INPUT_PULLUP: Ativa um resistência interna que mantém o pino em HIGH (5V/3.3V).
                     VCC
                      |
                      |
                     ---
                     ! ! Resistencia
                     ! !
                     ---
                      |
                      |
         Pinout   -------------------
                                    |
                                    |
                          Butão  -|
                                    |
                                   GND


  Quando carregas no botão, ele liga o pino ao GND (0V), passando a LOW.*/


  pinMode(/* */, INPUT_PULLUP);
  while(!Serial){delay(10);}

  xbinarySemaphore = /* */;
  xSerialMutex = /* */;

#ifdef MODO_ISR
  // ESTRUTURA DO ISR: PIN, FUNC, MODE
  // O MODE pode ser:
  // * RISING - GND -> VCC (Rising Edge)
  // * FALLING - VCC -> GND (Falling Edge)
  // * CHANGE - Quando o estado muda (now != prev)
  // * LOW - Enquanto o estado for LOW
  attachInterrupt(digitalPinToInterrupt(/* */), /* */, /* */);
#else
  xTaskCreate(Task_Butao, "Task_Butao", 256, NULL, /* */, NULL);
#endif

  xTaskCreate(Task_Blink, "Task_Blink", 256, NULL, /* */, NULL);
  xTaskCreate(Task_Alarm, "Task_Alarm", 256, NULL, /* */, NULL);
}

void loop() {}
```

---

# Mini Desafio 3

## **Módulo 3 · Slide 38**

### Objetivo

Compreender na prática a diferença de arquitetura entre tarefas concorrentes idênticas que competem por um Semáforo (Campainha Geral) versus uma tarefa que acorda por Task Notification direcionada (Chamada Direta ao Empregado VIP).

### Cenário

Um sistema de alerta de edifício com três sensores independentes e dois receivers:

1. **`Task_Cliente_Geral`**: Simula clientes aleatórios no balcão. A cada x segundos, eles tocam a campainha geral do hotel libertando um Counting Semaphore.

2. **`Task_Empregado`**: Tarefas idênticas (criadas com a mesma função) de Prioridade 2. Elas competem pelo semáforo da campainha. Quem estiver livre acorda, atende o cliente e escreve no Serial: "[Nome] atendeu a campainha geral!" e, passado de algum tempo, volta a estar operacional.

3. **`Task_Cliente_VIP`**: Um cliente especial que não usa a campainha. Ele telefona diretamente para o telemóvel do Empregado VIP através de uma Task Notification enviando um código de pedido (32-bits) a cada 4 segundos.

4. **`Task_Empregado_VIP`**: Uma tarefa de Prioridade 3 que fica bloqueada à espera de uma notificação direta. Quando acordada, lê o valor de 32-bits recebido e executa o pedido VIP remotamente.

5. **Recurso Crítico**: O Serial deve ser protegido por um Mutex.

---

### Código Base

```cpp
#include <FreeRTOS.h>

// Adiciona e remove nomes para aumentar ou diminuir o numero de empregados
const char* NOMES_EMPREGADOS[] = {"Manel", "Ezequiel", "Abel", "Micael", "Leonel"};
const int QTD_EMPREGADOS = sizeof(NOMES_EMPREGADOS) / sizeof(NOMES_EMPREGADOS[0]);

const int QTD_CLIENTES_GERAIS = 1; // Quantidade de tasks de clientes a gerar tráfego



SemaphoreHandle_t xCampainhaSem;
SemaphoreHandle_t xSerialMutex;
TaskHandle_t xHandlePaulo;


void Task_Empregado(void* pvParameters)
{
  char* nomeEmpregado = (char*) pvParameters;

  for(;;)
  {
    if(xSemaphoreTake(/* */, portMAX_DELAY) == pdTRUE)
    {
      if(xSemaphoreTake(/* */, pdMS_TO_TICKS(100)) == pdTRUE)
      {
        Serial.print("Campainha! ");
        Serial.print(/* */);
        Serial.println(" foi atender o balcão geral.\n");
        xSemaphoreGive(/* */);
      }

      vTaskDelay(pdMS_TO_TICKS(2500));

      if(xSemaphoreTake(/* */, pdMS_TO_TICKS(100)) == pdTRUE)
      {
        Serial.print(/* */);
        Serial.println(" voltou para o seu posto.\n");
        xSemaphoreGive(/* */);
      }
    }
  }
}



void Task_Empregado_VIP(void* pvParameters)
{
  uint32_t id;
  for(;;)
  {
    if(xTaskNotifyWait(0, pdTRUE, /* */, portMAX_DELAY) == pdTRUE)
    {
      if(xSemaphoreTake(/* */, pdMS_TO_TICKS(100)) == pdTRUE)
      {
        Serial.print("VIP! Paulo atendeu chamada direta. Pedido ID: ");
        Serial.println(/* */);
        xSemaphoreGive(/* */);
      }

      vTaskDelay(pdMS_TO_TICKS(200));
    }
  }
}

void Task_Clientes_Gerais(void* pvParameters)
{
  for(;;)
  {
    vTaskDelay(pdMS_TO_TICKS(random(1000, 3000)));
    xSemaphoreGive(/* */);
  }
}


void Task_Cliente_VIP(void* pvParameters)
{
  for(;;)
  {
    vTaskDelay(pdMS_TO_TICKS(4000));

    uint32_t id = /* */;

    if(/* */ != NULL)
    {
      /* */
    }
  }
}



void setup()
{
  Serial.begin(115200);
  randomSeed(analogRead(0));
  while(!Serial){delay(10);}


  // Counting Semaphore: igual ao binário, mas acumula múltiplos créditos. Give +1, Take -1.
  // uxMaxCount     (10) -> Limite da fila: máx. 10 toques acumulados em espera.
  // uxInitialCount  (0) -> Estado inicial: começa em 0 (sem clientes a aguardar).
  // NOTA: Se houver 100 empregados e a campainha tocar 10 vezes, 10 empregados acordam e trabalham ao mesmo tempo para esvaziar a fila. O "10" limita a fila, não os trabalhadores
  xCampainhaSem = xSemaphoreCreateCounting(10, 0);
  xSerialMutex  = xSemaphoreCreateMutex();

  xTaskCreate(Task_Empregado_VIP, "Paulo", 256, NULL, /* */, /* */);

  for(int i = 0; i < QTD_EMPREGADOS; i++)
  {
    xTaskCreate(/* */, NOMES_EMPREGADOS[i], 256, (void*)NOMES_EMPREGADOS[i], 2, NULL);
  }

  for(int i = 0; i < QTD_CLIENTES_GERAIS; i++)
  {
    xTaskCreate(/* */, "Cliente_Geral", 256, NULL, 1, NULL);
  }

  xTaskCreate(Task_Cliente_VIP, "Cliente_VIP", 256, NULL, 1, NULL);
}

void loop() {}
```

---

# Mini Desafio 4

## **Módulo 4 · Slide 45**

### Objetivo

Aprender a comunicar dados complexos entre múltiplas tarefas utilizando uma **Queue** (Fila) de estruturas (`struct`). O sistema deve centralizar as leituras de diferentes "sensores" numa única tarefa de processamento/exibição.

### Cenário

1.  **`Task_Sensor_A`**: Simula a leitura de um sensor (ex: Temperatura) e envia o ID e o valor para a Queue a cada 1 segundo (Prioridade 2).
2.  **`Task_Sensor_B`**: Simula a leitura de outro sensor (ex: Humidade) e envia para a **mesma Queue** a cada 3 segundos (Prioridade 2).
3.  **`Task_Display`**: Fica bloqueada à espera de dados na Queue. Quando recebe, identifica qual foi o sensor e imprime: `"Sensor [ID] enviou o valor [VALOR]"` (Prioridade 1).

### A Estrutura de Dados

Para enviar mais do que um número simples, usamos uma `struct`:

```cpp
struct DadosSensor {
  int id;
  float valor;
};
```

### Código Base

```cpp
#include <FreeRTOS.h>

QueueHandle_t xQueue;

struct DadosSensor
{
  int id;
  float valor;
};

void Task_Sensor_A(void* params)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  DadosSensor dados;
  for(;;)
  {
    /* */
  }
}


void Task_Sensor_B(void* params)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  DadosSensor dados;
  for(;;)
  {
    /* */
  }
}

void Task_Display(void* params)
{
  DadosSensor dados;
  for(;;)
  {
    /* */
  }
}

void setup()
{
  Serial.begin(115200);
  randomSeed(analogRead(0));
  while(!Serial){delay(10);}

  xQueue = /* */;

  xTaskCreate(Task_Sensor_A, "Task_Sensor_A", 256, NULL, 1, NULL);
  xTaskCreate(Task_Sensor_B, "Task_Sensor_B", 256, NULL, 1, NULL);
  xTaskCreate(Task_Display,  "Display",  256, NULL, 2, NULL);
}

void loop() {}
```
