# 🎛️ Controle de Altura com PID – ESP32

Sistema embarcado desenvolvido como projeto acadêmico em equipe durante a graduação em Análise e Desenvolvimento de Sistemas, utilizando ESP32, sensor de distância VL53L0X e controle PID.

## 📖 Sobre o projeto

O projeto teve como objetivo desenvolver um sistema capaz de controlar automaticamente a altura de uma esfera de isopor utilizando um controlador PID. Para isso, foi utilizado um ESP32 para processar os dados do sensor VL53L0X e controlar a velocidade de uma ventoinha por meio de PWM, mantendo a esfera próxima à posição desejada.

## 👩‍💻 Minha participação

Neste projeto participei principalmente do desenvolvimento do software embarcado, incluindo a programação do ESP32, integração do sensor VL53L0X, implementação e calibração do controlador PID, realização de testes e identificação e correção de problemas durante o desenvolvimento.

Também colaborei com a montagem do circuito e demais atividades da equipe.

## 🛠️ Tecnologias utilizadas

- ESP32
- Linguagem C++
- Arduino IDE
- Sensor de distância VL53L0X
- Ventoinha
- PWM
- Controle PID

## ⚙️ Funcionamento

O sensor VL53L0X mede continuamente a distância da esfera em relação ao sensor.

Essas informações são enviadas ao ESP32, que compara a posição medida com a altura desejada (setpoint).

A partir desse erro, o controlador PID calcula o ajuste necessário na velocidade da ventoinha utilizando PWM, aumentando ou reduzindo o fluxo de ar para manter a esfera próxima da posição definida.

## 🧪 Testes realizados

Durante o desenvolvimento foram realizados diversos testes para validar o funcionamento do sistema, incluindo:

- Validação das leituras do sensor VL53L0X;
- Testes de acionamento da ventoinha utilizando PWM;
- Calibração do controlador PID;
- Testes em diferentes alturas;
- Ajustes dos parâmetros do controlador para melhorar a estabilidade do sistema.

## 🚧 Desafios encontrados

Durante o desenvolvimento do projeto foram enfrentados desafios relacionados à calibração do controlador PID, estabilidade da esfera e ajuste dos parâmetros do sistema. Esses desafios foram superados por meio de testes sucessivos e ajustes realizados pela equipe.

## 🎯 Objetivos de aprendizagem

Durante o desenvolvimento deste projeto foram praticados conceitos como:

- Programação embarcada
- Controle PID
- Leitura de sensores
- Modulação PWM
- Integração entre hardware e software
- Calibração de sistemas
- Resolução de problemas
- Trabalho em equipe

## 📸 Imagens do projeto

- Foto da montagem

- Foto funcionando

- Diagrama do sistema

- Fluxograma

- Vídeo

## 🎥 Demonstração

O vídeo abaixo apresenta o funcionamento do sistema em operação, demonstrando o controle automático da altura da esfera por meio do controlador PID.

## 📄 Documentação

Os slides utilizados na apresentação final do projeto estão disponíveis na pasta `docs`.
