Leitura de Coordenadas GPS Direto das Sentenças NMEA com ESP32 e FreeRTOS
O que o projeto faz
Este projeto demonstra como extrair coordenadas GPS diretamente das sentenças NMEA fornecidas por um módulo GPS conectado a um ESP32. Utilizando uma tarefa do FreeRTOS, o código lê continuamente os dados do GPS, processa as sentenças NMEA e atualiza uma estrutura de dados com as informações de latitude, longitude, altitude, número de satélites, entre outros.

Por que o projeto é útil
Ao ler e processar diretamente as sentenças NMEA, este projeto oferece uma compreensão aprofundada de como os dados GPS são transmitidos e interpretados. Isso permite aos desenvolvedores:

Personalização: Adaptar o processamento de dados GPS conforme as necessidades específicas de suas aplicações.
Eficiência: Evitar o uso de bibliotecas externas, permitindo um controle mais direto e potencialmente reduzindo o uso de recursos.
Educação: Aprender sobre o protocolo NMEA e como implementar multitarefas com FreeRTOS no ESP32.
Como os usuários podem começar a usar o projeto
Para iniciar com este projeto:

Hardware Necessário:

ESP32, 
Módulo GPS compatível que transmita sentenças NMEA e 
Cabos de conexão 

Configuração do Ambiente de Desenvolvimento:

Instale o PlatformIO como extensão do Visual Studio Code ou utilize a Arduino IDE configurada para o ESP32.
Conexões de Hardware:

Conecte o pino TX do módulo GPS ao pino RX2 (GPIO16) do ESP32.
Conecte o pino RX do módulo GPS ao pino TX2 (GPIO17) do ESP32.
Alimente o módulo GPS com 3.3V ou 5V, conforme especificado pelo fabricante, e conecte os GNDs em comum.
Código Fonte:

Clone este repositório: git clone https://github.com/seu_usuario/seu_repositorio.git
Abra o projeto no PlatformIO ou Arduino IDE.
Compile e faça o upload do código para o ESP32.
Execução:

Abra o monitor serial configurado para 115200 baud.
Observe as informações GPS sendo atualizadas continuamente no terminal.
Onde os usuários podem obter ajuda com o projeto
Se você encontrar dificuldades ou tiver dúvidas sobre este projeto:

Documentação Oficial:

Documentação do ESP32
Referência do FreeRTOS
Comunidades e Fóruns:

Fórum do ESP32
Stack Overflow (utilize tags como esp32, freertos, nmea)
Contato Direto:

Abra uma issue neste repositório detalhando o problema encontrado.
Quem mantém e contribui com o projeto
Este projeto é mantido por Otávio Martins. Contribuições são bem-vindas! Sinta-se à vontade para forkear o repositório e enviar pull requests. Para questões ou sugestões, abra uma issue ou entre em contato diretamente.
