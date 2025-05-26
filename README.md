## 👩‍💻 Autoras

- **Ana Carolina Reis Santana** - RM556219  
- **Letícia Zago de Souza** - RM558464  
- **Celina Alcântara do Carmo** - RM558090

  
# 🚗 Pátio Vision IoT

Sistema de monitoramento de veículos em pátios utilizando **ESP32**, **protocolo MQTT** e **Node-RED**. O projeto simula a leitura de dados via BLE (Bluetooth Low Energy), envia essas informações via Wi-Fi para um broker MQTT e exibe os dados em tempo real em um painel web interativo.

---

## 📦 Estrutura do Repositório

```
patio-vision-iot/
│
├── firmware/            # Código para o ESP32 (main.cpp)
├── node-red/            # Flows para importar no Node-RED (flows.json)
├── README.md            # Este arquivo
└── LICENSE              # Licença MIT
```

---

## 🧾 Pré-requisitos

- ESP32 com suporte ao Arduino
- IDE Arduino instalada
- Node.js instalado (versão LTS recomendada)
- Node-RED instalado
- Broker MQTT (ex: Mosquitto)
- Conexão Wi-Fi local

---

## ⚙️ Instalação e Configuração

### 1. 📲 Firmware ESP32

1. Abra o arquivo `main.cpp` na **IDE Arduino**.
2. Edite as configurações de rede:
   ```cpp
   const char* ssid = "SEU_WIFI";
   const char* password = "SUA_SENHA";
   const char* mqtt_server = "IP_DO_SEU_BROKER";
   ```
3. Conecte o ESP32 ao computador.
4. Carregue o código no dispositivo.
5. O ESP32 iniciará a conexão com a rede Wi-Fi e enviará dados via MQTT para o tópico `monitoramento/veiculos`.

---

### 2. 🌐 Node-RED

1. Instale o Node-RED:
   ```bash
   npm install -g --unsafe-perm node-red
   ```
2. Inicie o Node-RED:
   ```bash
   node-red
   ```
3. No navegador, acesse:
   ```
   http://<SEU_IP>:1880
   ```
4. Clique no menu (☰) > *Import* > *Arquivo* > selecione `flows.json` (pasta `node-red/`).
5. Edite o nó do **broker MQTT** para apontar para o mesmo IP configurado no ESP32.
6. Acesse o dashboard em:
   ```
   http://<SEU_IP>:1880/ui
   ```

---

## 📊 Funcionalidades

- Simulação de um veículo BLE com dados como:
  - Identificador
  - Tipo de veículo
  - Zona de localização
  - Movimento
  - Intensidade de sinal (RSSI)
  - Distância aproximada via RSSI
- Envio periódico de dados via MQTT
- Visualização em tempo real no painel do Node-RED

---

## 📄 Licença

Distribuído sob a Licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais informações.

---

## 🤝 Contribuindo

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests.
