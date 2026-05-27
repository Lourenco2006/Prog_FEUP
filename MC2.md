# Workshop de Microcontroladores: Raspberry Pi Pico

### Nota Prévia

Este documento está no formato Markdown (.md). Para o leres com a formatação visual correta (títulos grandes, negritos, formatação de código), sugerimos as seguintes opções:

- No **VS Code**: Abre o ficheiro e prime `Ctrl + Shift + V` _(Windows/Linux)_ ou `Cmd + Shift + V` _(macOS)_ para abrir a janela de pré-visualização.
- No **Navegador (Online)**: Podes arrastar o ficheiro para um visualizador online gratuito como o Dillinger.io ou o StackEdit.

---

Todos os desafios encontram-se neste ficheiro, que contêm o enunciado do desafio.
Para facilitar, é fornecido um código de base a preencher. Substitui os comentários (`/* */`) por pedaços de código correto.

---

# Desafio 1: Interrupts (O Básico)

### Objetivo
Lidar com interrupções de hardware. Temos um LED principal que pisca lentamente na função `loop()`, a bloquear o processador com delays. O objetivo é usar um botão associado a um **Interrupt** para alterar o estado de um segundo LED instantaneamente e desligar o LED do loop principal.

### Cenário
1. O LED Principal (Pino 14) pisca a cada 2 segundos no `loop()`.
2. O botão (Pino 16) aciona uma interrupção (ISR).
3. A interrupção liga/desliga o LED Secundário (Pino 1)

### Código Base

```cpp
volatile bool estadoLed = false;
const int pinoBotao = 16; 
const int pinoLedI = 1; 
const int pinoLed = 14; 

// Função ISR, Interrupt Service Routine
void BotaoLED() {
   /* */
}

void setup() {
    pinMode(pinoLedI, OUTPUT);
    pinMode(pinoBotao, INPUT_PULLUP); 
    pinMode(pinoLed, OUTPUT);

    // Configura o interrupt no botão
    // Sintaxe: (Pino Traduzido, Função a chamar, Modo de disparo)
    attachInterrupt(digitalPinToInterrupt(/* */), /* */, /* */); 
}

void loop() {
    digitalWrite(pinoLed, HIGH);
    delay(2000); 
    digitalWrite(pinoLed, LOW);
    delay(2000); 
}
```

---

# Desafio 2: Timers (Alarms)

### Objetivo
Criar uma interrupção baseada em tempo (Timer), substiuindo o botão do desafio anterior. 
O objetivo é que os dois leds pisquem nos seus próprio intervalos, usando um interrupt periódico.

### Cenário
1. O LED controlado pela 'Loop', que pisca mais lentamente (pino 14).
2. O Timer de hardware chama a função  de interrupt automaticamente a cada x milissegundos.
3. A interrupção periódica altera o estado do LED Secundário (Pino 1)

### Código Base

```cpp
#include "hardware/timer.h" // Biblioteca necessária para os timers do SDK da Pico

const int pinoLedLento = 14; 
const int pinoLedRapido = 1; 
volatile bool estadoLedRapido = false;

/* */ timer; // Estrutura para guardar a info do timer (repeating_timer)

// Função que o Timer vai chamar (ISR do Timer)
bool piscaRapidoCallback(struct repeating_timer *t) {
    estadoLedRapido = !estadoLedRapido;
    digitalWrite(/* */, /* */);
    return /* */; // Deve retornar verdadeiro para repetir infinitamente
}

void setup() {
    pinMode(pinoLedLento, OUTPUT);
    pinMode(pinoLedRapido, OUTPUT);

    // Inicia um timer a cada x milissegundos
    add_repeating_timer_ms(/* */, /* */, /**/, &timer); //sintaxe: (tempo,função,retorno,endereço do timer)
}

void loop() {
    digitalWrite(pinoLedLento, HIGH);
    delay(2000); 
    digitalWrite(pinoLedLento, LOW);
    delay(2000); 
} 
```
---

# Desafio 3: Multicore (Mutexes)

### Objetivo
Programar um Mutex de forma a proteger os recursos partilhados entre ambos os Cores do CPU da Pi Pico de forma a que as instruções
de cada Núcleo ocorram de forma cordenada.
Os dois Cores vão tentar acender os mesmos LEDs com padrões diferentes, o Mutex vai garantir que isso acontece de forma cordenada.
Para testar o que acontece quando não há mutexes, a "Race Condition", comentem as linhas com a palavra "mutex" usando "//".

### Cenário
1. Core 0: Tem instruções para piscar os dois LEDs de forma simétrica (alternada) 5 vezes.
2. Core 1: Tem instruções para piscar os dois LEDs de forma síncrona 3 vezes.
3. Ambos partilham a "chave" do Mutex (mutex_t) que, para poderem alterar as mesmas variáveis, tem de estar desbloqueada. 

### Código Base

```cpp
#include "pico/mutex.h" 

const int pinoLed1 = 14; 
const int pinoLed2 = 1; 
/* */ led_mutex; // Cria a variável do mutex

void setup() {
    pinMode(pinoLed1, OUTPUT);
    pinMode(pinoLed2, OUTPUT);
    /* */(&led_mutex); // Inicializa o mutex
}

void loop() { 
    // Core 0: Padrão simétrico
    /* */(&led_mutex); // Tranca o mutex
    
    for(int i = 0; i < 5; i++) {
        digitalWrite(/* */,/* */); 
        digitalWrite(/* */,/* */); 
        delay(100);
        digitalWrite(/* */,/* */); 
        digitalWrite(/* */,/* */); 
        delay(100);
    }
    digitalWrite(pinoLed1, LOW); digitalWrite(pinoLed2, LOW); 
    
    /* */(&led_mutex); // Destrancar o mutex
    delay(500); 
}

void setup1() { 
    // Vazio - O Arduino IDE arranca este setup para o Core 1
}

void loop1() { 
    // Core 1: Padrão síncrono
    /* */(&led_mutex); // Tranca o mutex
    
    for(int i = 0; i < 3; i++) {
        digitalWrite(/* */, /* */); 
        digitalWrite(/* */, /* */); 
        delay(300);
        digitalWrite(/* */, /* */); 
        digitalWrite(/* */, /* */); 
        delay(300);
    }
    
    /* */(&led_mutex); // Destrancar o mutex
    delay(500); 
}
```
---

# Desafio : Multicore (FIFOs)

### Objetivo
Utilizar uma FIFO (First in First Out) de forma a proteger os recursos partilhados entre ambos os Cores do CPU da Pi Pico de forma a que as instruções de cada Núcleo ocorram de forma ordenada.
Implementar uma dinâmica Chefe - Trabalhador (uma espécie de "Produtor - Consumidor") entre dois Núcleos, em que um dos Núcleos lê se o botão está a ser clicado ou não e envia um valor, através da FIFO, para o outro núcleo que corresponde ao número de vezes que o LED vai piscar.

### Cenário
1. Core 0: Apenas lê o botão (pino 16) que quando pressionado, coloca um valor na FIFO (rp2040.fifo.push())
2. Core 1: Verifica, a cada iteração se a FIFO está vazia, não estando, pisca o LED um número de vezes, retirando o valor da FIFO (rp2040.fifo.pop()).

### Código Base

```cpp
const int pinoBotao = 16; 
const int pinoLed = 14; 

void setup() { 
    pinMode(/* */, /* */);
    pinMode(/* */,/* */);
}

void loop() { 
    // Core 0: Chefe, lê botões e envia ordens
    if (digitalRead(/* */) == LOW) {
        
        // Envia o número '5' para a FIFO (usando a classe do RP2040)
        /* */.push(5); 
        
        // Espera que o botão seja largado (debounce)
        while(digitalRead(pinoBotao) == LOW) {
            delay(10);
        }
        delay(50); 
    }
}

void setup1() {} // Vazio

void loop1() { 
    // Core 1: Trabalhador
    
    // Confirma se há mensagens na FIFO antes de tentar ler
    if (/* */.available() > 0) {
        
        // Retira a mensagem da FIFO e guarda na variável
        uint32_t ordem_de_piscas = /* */.pop(); 
        
        // Executa a tarefa de piscar as vezes pedidas
        for (uint32_t i = 0; i < /* */; i++) {
            digitalWrite(/* */,/* */); 
            delay(150);
            digitalWrite(/* */, /* */); 
            delay(150);
        }
    }
}
```