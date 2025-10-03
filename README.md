# 🚀 SmartGarden

![Status do Deploy](https://img.shields.io/badge/Status-Em%20Desenvolvimento-blueviolet?style=for-the-badge&logo=arduino)
![Tecnologia](https://img.shields.io/badge/Arduino-RP2040-brightgreen?style=for-the-badge&logo=arduino)

Sistema inteligente de irrigação automática baseado em Arduino RP2040. Desenvolvido como parte do curso de **Projeto de Desenvolvimento II** na **Universidade SENAC/RS**, com foco em acessibilidade, automação e cuidado eficiente com plantas em ambientes urbanos.

---

## 📜 Índice

* [Sobre o Projeto](#-sobre-o-projeto)
* [✨ Funcionalidades](#-funcionalidades)
* [🎨 Diretrizes de Estilo](#-diretrizes-de-estilo)
* [🛠️ Tecnologias Principais](#️-tecnologias-principais)
* [🚀 Começando](#-começando)

  * [Pré-requisitos](#pré-requisitos)
  * [Instalação](#instalação)
* [🤝 Como Contribuir](#-como-contribuir)
* [✒️ Autor](#️-autor)

---

## 📖 Sobre o Projeto

O **SmartGarden** é uma solução de irrigação automatizada que visa facilitar o cuidado com plantas em cenários onde a presença constante do cuidador não é possível.

Desenvolvido como um **projeto acadêmico** no curso de Análise e Desenvolvimento de Sistemas (SENAC/RS), o objetivo é criar um sistema funcional, acessível e escalável, capaz de automatizar a rega de plantas com base na umidade do solo ou por controle remoto via interface web.

> **Universidade:** SENAC/RS  
> **Disciplina:** Projeto de Desenvolvimento II  
> **Ano/Semestre:** 2025/2  
> **Professor:** Luciano Zanuz  
> **Aluno:** Armando Rial Michalski  

---

## ✨ Funcionalidades

As funcionalidades mínimas do MVP incluem:

* ✅ **Leitura contínua da umidade do solo** com sensor capacitivo.
* ✅ **Acionamento automático da bomba submersa** ao detectar solo seco.
* ✅ **Controle manual da irrigação** via botão físico ou interface web.
* ✅ **Feedback de status do sistema**: regando, solo úmido ou solo seco.
* ✅ **Registro básico** de leituras e acionamentos para análise futura.

Essas funcionalidades visam validar a viabilidade técnica do projeto e permitir futuras expansões com recursos como conectividade IoT, dashboards em nuvem e integração com assistentes virtuais.

---

## 🎨 Diretrizes de Estilo

Como se trata de um projeto com interface simples, os princípios de design focam em:

* **Clareza de status do sistema** (ex: ícones ou textos: "Regando", "Solo seco").
* **Contraste elevado** para facilitar a leitura em diversas condições.
* **Responsividade** para acessibilidade via dispositivos móveis.
* **Design limpo e funcional**, priorizando usabilidade.

---

## 🛠️ Tecnologias Principais

| Componente / Ferramenta          | Finalidade                                     |
| -------------------------------- | ---------------------------------------------- |
| **Arduino RP2040 Connect**       | Microcontrolador principal com Wi-Fi integrado |
| **Sensor de Umidade Capacitivo** | Monitoramento da umidade do solo               |
| **Bomba Submersa 5V**            | Responsável pela irrigação                     |
| **Módulo Relé 5V**               | Acionamento da bomba via sinal do Arduino      |
| **Fonte de Alimentação 5V**      | Alimentação de todos os componentes            |
| **Protoboard e Jumpers**         | Montagem do circuito físico                    |
| **Arduino IDE (C++)**            | Desenvolvimento e upload do firmware           |
| **Interface Web/App**            | Controle remoto da irrigação                   |

---

## 🚀 Começando

Siga os passos abaixo para montar e testar o projeto localmente.

### Pré-requisitos

* Placa **Arduino RP2040 Connect**
* Sensor de umidade capacitivo
* Módulo relé 5V
* Bomba submersa 5V
* Protoboard, jumpers e fonte de 5V
* Computador com **Arduino IDE** instalado

### Instalação

1. Clone este repositório ou baixe os arquivos do projeto.
2. Abra o projeto na Arduino IDE.
3. Conecte a placa e selecione a porta e modelo corretos.
4. Faça o upload do código para o RP2040.
5. Acompanhe os dados via monitor serial e/ou interface web.

---

## 🤝 Como Contribuir

Contribuições são bem-vindas! Sinta-se à vontade para abrir *issues*, enviar *pull requests* ou sugerir melhorias. Este projeto é voltado ao aprendizado e à experimentação com IoT.

---

## ✒️ Autor

* **Armando Rial Michalski** - [@armando-rial](https://github.com/armando-rial)

---
