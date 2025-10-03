# SmartGarden
SENAC/RS - 2025/2 - Projeto de Desenvolvimento II - SmartGarden

Aluno: Armando Rial Michalski

Professor: Luciano Zanuz

Definição do problema:
A manutenção adequada de plantas exige atenção constante à irrigação, especialmente em ambientes urbanos ou para pessoas com rotinas agitadas. A falta de tempo, esquecimentos ou ausência prolongada podem comprometer a saúde das plantas, levando à subnutrição hídrica ou ao excesso de água. Esse problema afeta diretamente amantes da jardinagem, moradores de apartamentos, idosos, pessoas com mobilidade reduzida e até instituições que mantêm áreas verdes. 
A oportunidade está em automatizar esse cuidado, oferecendo uma solução acessível, eficiente e conectada que garanta a irrigação ideal das plantas sem depender da presença física do usuário.  

Proposta de solução:
A solução proposta é o desenvolvimento de um sistema inteligente de irrigação, baseado em um microcontrolador Arduino RP2040, capaz de realizar a rega de forma automática (com base na umidade do solo) ou manual remota (via aplicativo ou interface web). 

Funcionalidades do MVP (Produto Mínimo Viável): 
• Interface de controle remoto (via botão físico ou aplicativo web) para ativar a bomba manualmente. 
• Leitura contínua da umidade do solo através de um sensor capacitivo. 
• Acionamento automático da bomba submersa quando a umidade estiver abaixo do nível ideal. 
• Feedback do status do sistema: regando, solo úmido, solo seco. 
• Registro básico de leituras de umidade e acionamentos para análise futura. 
Esse MVP será suficiente para demonstrar a viabilidade técnica e funcional do sistema, podendo ser expandido 
futuramente com conectividade IoT, integração com assistentes virtuais ou dashboards na nuvem. 

Proposta de tecnologia:
A seguir, as tecnologias e ferramentas que serão utilizadas no desenvolvimento do projeto:de modo simplificado quais tecnologias e ferramentas você pretende utilizar para o desenvolvimento do projeto. 
Componente / Finalidade 
• Arduino RP2040 Connect = Microcontrolador principal com suporte a Wi-Fi 
• Sensor de Umidade do Solo = Monitoramento da umidade da terra 
• Bomba Submersa 5V = Irrigação da planta 
• Módulo Relé 5V = Controle da bomba via sinal do Arduino  
• Fonte de Alimentação 5V = Alimentação dos componentes 
• Jumpers e Protoboard = Montagem do circuito 
• Arduino IDE = Programação do microcontrolador (C++) 
• Interface Web via App = Controle remoto da irrigação 
