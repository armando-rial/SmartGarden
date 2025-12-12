/* ------------- PARÂMETROS DE CONFIGURAÇÃO ------------- */

constexpr int BUTTON_PIN = 4;    						// Entrada digital para botão
constexpr int LED_PIN    = 5;    						// Saída digital para LED do botão
constexpr int RELAY_PIN  = 6;    						// Saída digital para relé
constexpr int MOIST_PIN  = A0;   						// Entrada analógica para sensor de umidade

int raw_moisture = 0;            						// Valor bruto do sensor
int moisture = 0;                						// Percentual de umidade

// Constantes simbólicas para limites de umidade (otimizar)
constexpr int MOISTURE_WET = 40; 						// Acima de 40% = solo úmido
constexpr int MOISTURE_DRY = 10; 						// Abaixo de 10% = solo muito seco

// Configuração dos tempos de piscar
int blinkSlow = 1000; 									// período em ms (devagar)
int blinkFast = 500;  									// período em ms (rápido)

/* ------------- BIBLIOTECAS E VARIÁVEIS ------------- */

#include "thingProperties.h"    						// Conexão com Arduino IoT Cloud
#include <Bounce2.h>             						// Controle de botão com debounce

Bounce b;                        						// Instância do botão com debounce
unsigned long startedWatering;   						// Marca o início da rega

/* ------------- CONFIGURAÇÃO INICIAL ------------- */

void setup() {
  Serial.begin(9600);               					// Inicia a comunicação serial com o computador a 9600 bps
  delay(1500);                      					// Aguarda 1,5 segundos para estabilização do sistema

  b.attach(BUTTON_PIN, INPUT_PULLUP); 					// Configura o botão com resistor pull-up interno usando a biblioteca Bounce2
  b.interval(25);                   					// Define intervalo de debounce de 25 ms para evitar leituras falsas do botão
  pinMode(LED_PIN, OUTPUT);        						// Define o pino do LED como saída
  pinMode(RELAY_PIN, OUTPUT);      						// Define o pino do relé como saída
	
  stopWatering();                  						// Garante que a bomba esteja desligada ao iniciar o sistema

  initProperties();                						// Inicializa as propriedades vinculadas à Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection); 	// Inicia a conexão com a nuvem usando a configuração preferida
  setDebugMessageLevel(4);         						// Define o nível de detalhamento das mensagens de debug (4 = detalhado)
  ArduinoCloud.printDebugInfo();   						// Imprime informações de debug da conexão com a nuvem

  // Pisca o LED 5 vezes para indicar que o sistema está rodando corretamente
  for (int i = 0; i <= 4; i++) {
    digitalWrite(LED_PIN, HIGH);   						// Acende o LED
    delay(200);                    						// Aguarda 200 ms
    digitalWrite(LED_PIN, LOW);    						// Apaga o LED
    delay(200);                    						// Aguarda 200 ms
  }
}

/* ------------- LOOP PRINCIPAL ------------- */

void loop() {
  ArduinoCloud.update(); 				// Atualiza a conexão com a Arduino IoT Cloud e sincroniza variáveis

  // Lê o sensor de umidade e converte o valor bruto para percentual (0% seco, 100% úmido)
  raw_moisture = analogRead(MOIST_PIN); 		// Lê o valor analógico do sensor de umidade
  moisture = map(raw_moisture, 610, 90, 0, 100); 	// Converte o valor para escala percentual invertida
  moisture = constrain(moisture, 0, 100); 		// Garante que o valor fique entre 0% e 100%

  // Exibe os dados no monitor serial com marcação de tempo
  Serial.print("Umidade: "); 				// Imprime o texto "Umidade: "
  Serial.print(moisture); 				// Imprime o valor percentual da umidade
  Serial.print("% - Tempo: "); 				// Imprime o texto "% - Tempo: "
  Serial.println(millis()); 				// Imprime o tempo atual em milissegundos desde que o Arduino foi ligado

  // Atualiza LED conforme status
  updateLED(watering, moisture);

  // Verifica se o tempo de rega já passou e interrompe se necessário		// Se variável 'watering' for verdadeira (rega ativa),
  if (watering && (millis() - startedWatering) >= waterTime * 1000) {		// E o tempo atual menos o tempo de início da rega, for maior ou igual ao tempo de rega configurado (em milissegundos),
    stopWatering(); 								// Encerra-se a rega após o tempo configurado
  }

  // Atualiza o estado do BOTÃO FÍSICO com debounce					// Verifica se houve mudança no botão HIGH → LOW (pressionado) ou LOW → HIGH (solto),
  b.update(); 														// Como botão INPUT_PULLUP, o estado normal (não pressionado) é HIGH,
  if (b.changed() && b.read() == false) { 							// Se o botão foi pressionado e nível lógico LOW,
    if (watering) {													// Se já estiver regando
      stopWatering(); 												// Interrompe a rega
    } else {														// Senão verifica
      if (moisture < 30) {											// Se umidade estiver abaixo de 30%
        startWatering(); 											// Inicia a rega
      } else {														// Senão supõe-se que umidade está acima de 30%
        Serial.println("Solo úmido — rega local não iniciada."); 	// E informa usuário que solo esta úmido, e ignora comando
      }
    }
  }
}

/* ------------- FUNÇÃO DE CONTROLE DO LED ------------- */
// milis() = Retorna o tempo em milissegundos desde que o Arduino foi ligado
// % blinkSlow  = Calcula o resto da divisão do tempo atual pelo período de piscar (ex: 1000 ms)
// < (blinkSlow / 2) = Compara se esse tempo está na primeira metade do ciclo

void updateLED(bool watering, int moisture) {
  if (watering) {
    digitalWrite(LED_PIN, HIGH); 					// LED acesso
  } else if (moisture > MOISTURE_WET) {				// Umidade < 40%
    digitalWrite(LED_PIN, LOW);  					// LED apagado
  } else if (moisture > MOISTURE_DRY) {				// Umidade < 10%
    digitalWrite(LED_PIN, (millis() % blinkSlow) < (blinkSlow / 2)); 	// Pisca devagar = 1000ms = 1s
  } else {
    digitalWrite(LED_PIN, (millis() % blinkFast) < (blinkFast / 2)); 	// Pisca rápido = 500ms = 0,5s
  }
}

/* ------------- FUNÇÕES DE EVENTO DA NUVEM ------------- */

// Evento de mudança na variável watering
void onWateringChange() {					// Função de rega via app
  if (watering) {						// Verifica se a variável 'watering' foi definida como TRUE (pedido para iniciar a rega)
    if (moisture < 30) {					// Se umidade estiver abaixo de 30%
      startWatering(); 						// Inicia a rega
    } else {							// Senão
      Serial.println("Solo úmido — rega remota ignorada."); 	// Informa usuário que o solo está úmido, e ignora o comando
      watering = false; 					// Corrige o estado da variável na nuvem para refletir que a rega não foi iniciada
    }
  } else {							// Senão supõe-se que 'watering' é FALSE,
    stopWatering(); 						// E interrompe a rega
  }
}

// Evento de mudança na variável waterTime
void onWaterTimeChange() {
  Serial.print("Novo tempo de rega configurado: "); 		// Imprime uma mensagem indicando que o tempo de rega foi alterado
  Serial.print(waterTime);                          		// Imprime o novo valor da variável 'waterTime' (em segundos)
  Serial.println(" segundos.");                     		// Finaliza a linha com a unidade de tempo e quebra de linha
}

/* ------------- FUNÇÕES DE CONTROLE DE REGA ------------- */

void startWatering() {
  watering = true;                      		// Define a variável de controle como verdadeira (rega ativa)
  startedWatering = millis();          			// Registra o momento em que a rega começou (em milissegundos)
  digitalWrite(RELAY_PIN, HIGH);       			// Liga o relé, ativando a bomba de água
  Serial.println("Rega iniciada.");    			// Exibe mensagem no monitor serial indicando início da rega
}

void stopWatering() {
  watering = false;                    			// Define a variável de controle como falsa (rega encerrada)
  digitalWrite(RELAY_PIN, LOW);        			// Desliga o relé, interrompendo a bomba de água
  Serial.println("Rega encerrada.");   			// Exibe mensagem no monitor serial indicando fim da rega
}