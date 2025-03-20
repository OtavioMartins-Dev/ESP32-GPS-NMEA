# Leitura de Coordenadas GPS Direto das Sentenças NMEA com ESP32 e FreeRTOS

![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32-orange?logo=platformio)
![FreeRTOS](https://img.shields.io/badge/FreeRTOS-Supported-blue?logo=freertos)
![License](https://img.shields.io/badge/License-MIT-green)

## 📌 O que o projeto faz

Este projeto demonstra como extrair coordenadas GPS diretamente das sentenças NMEA fornecidas por um módulo GPS conectado a um **ESP32**.  
Utilizando **FreeRTOS**, uma tarefa dedicada lê continuamente os dados do GPS, processa as sentenças **NMEA**, e atualiza uma estrutura de dados com:

✅ Latitude e Longitude  
✅ Altitude  
✅ Número de satélites visíveis  
✅ Precisão dos dados  

## 💡 Por que este projeto é útil?

Ao processar diretamente as sentenças NMEA, o projeto permite:

🔹 **Maior controle**: Evita bibliotecas externas, dando mais flexibilidade ao desenvolvedor  
🔹 **Eficiência**: Código otimizado para rodar em multitarefas com **FreeRTOS**  
🔹 **Educação**: Ensina a trabalhar com **NMEA** e gerenciamento de tarefas no **ESP32**  

## 🚀 Como começar

### 🔧 Requisitos de Hardware

- ✅ ESP32  
- ✅ Módulo GPS (exemplo: NEO-6M, u-blox)  
- ✅ Jumpers para conexão  

### ⚙️ Configuração do Ambiente

1️⃣ Instale o **[PlatformIO](https://platformio.org/)** no Visual Studio Code (ou use a [Arduino IDE](https://www.arduino.cc/en/software))  
2️⃣ Clone este repositório:  

   ```bash
   git clone https://github.com/OtavioMartins-Dev/ESP32-GPS-NMEA.git
   cd ESP32-GPS-NMEA
   ```

3️⃣ Conecte o **módulo GPS** ao **ESP32**:  

   | Módulo GPS | ESP32  |
   |------------|--------|
   | TX        | GPIO16 (RX2) |
   | RX        | GPIO17 (TX2) |
   | VCC       | 3.3V ou 5V  |
   | GND       | GND  |

4️⃣ Compile e faça o **upload do código** para o ESP32  
5️⃣ Abra o **Monitor Serial** (`115200 baud`) para ver os dados GPS sendo atualizados  

## ❓ Onde obter ajuda?

📚 **Documentação Oficial**  
- [ESP32 Docs](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)  
- [FreeRTOS Reference](https://www.freertos.org/)  

🌍 **Comunidades**  
- [Fórum do ESP32](https://www.esp32.com/)  
- [Stack Overflow](https://stackoverflow.com/) (`esp32`, `freertos`, `nmea`)  

💬 **Suporte no GitHub**  
- Abra uma **issue** neste repositório detalhando seu problema  

## 👨‍💻 Manutenção e Contribuições

Este projeto é mantido por [**OtávioMartins-Dev**](https://github.com/OtavioMartins-Dev).  
Contribuições são bem-vindas! Faça um **fork**, implemente melhorias e envie um **pull request**.  

🔹 **Dúvidas ou sugestões?** Abra uma **issue** ou entre em contato.  

---

📌 *Feito com ❤️ e código limpo para a comunidade ESP32!*
