#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox;

// =========================
// PINOS
const int PWM_PIN = 18;   // fio azul da ventoinha

// =========================
// CONFIGURAÇÕES DO SISTEMA
const float H = 44.0;   // altura total do tubo (cm)

// =========================
// SETPOINTS DAS 3 ETAPAS
const float SP_BAIXO = 2.0;    // esfera perto da base
const float SP_MEIO  = 20.0;   // metade do tubo
const float SP_CIMA  = 38.0;   // perto do topo

// tempo de cada etapa
const unsigned long TEMPO_ETAPA = 30000;   // 30 segundos

// =========================
// PWM BASE E LIMITES
const int PWM_BASE = 105;   // valor de equilíbrio aproximado
const int PWM_MIN  = 95;
const int PWM_MAX  = 120;

// =========================
// GANHOS PID
// Ajustados de forma conservadora para evitar agressividade
float Kp = 1.8;
float Ki = 0.08;
float Kd = 0.8;

// =========================
// VARIÁVEIS PID
float erro = 0;
float erroAnterior = 0;
float integral = 0;
float derivada = 0;
float saidaPID = 0;

// tempo de amostragem do controle
const float Ts = 0.10;   // 100 ms

unsigned long tempoAnterior = 0;
unsigned long tempoInicio = 0;

// setpoint atual
float setpointAtual = SP_BAIXO;

// =========================
// FUNÇÃO PARA ESCOLHER SETPOINT
void atualizarSetpoint() {
  unsigned long tempoDecorrido = millis() - tempoInicio;

  // ciclo total = 90 s
  if (tempoDecorrido < 30000) {
    setpointAtual = SP_BAIXO;
  }
  else if (tempoDecorrido < 60000) {
    setpointAtual = SP_MEIO;
  }
  else if (tempoDecorrido < 90000) {
    setpointAtual = SP_CIMA;
  }
  else {
    // reinicia o ciclo
    tempoInicio = millis();
    setpointAtual = SP_BAIXO;

    // opcional: zera a integral ao reiniciar o ciclo
    integral = 0;
  }
}

void setup() {
  Serial.begin(115200);
  delay(1500);

  // I2C do sensor
  Wire.begin(21, 22);

  // PWM da ventoinha
  ledcAttach(PWM_PIN, 25000, 8);

  Serial.println("======================================");
  Serial.println(" PID COM 3 SETPOINTS AUTOMATICOS ");
  Serial.println("======================================");

  // Inicializa sensor
  if (!lox.begin()) {
    Serial.println("ERRO: VL53L0X nao encontrado!");
    while (1) {
      delay(1000);
    }
  }

  Serial.println("Sensor VL53L0X OK");
  Serial.println("Ventoinha PWM OK");
  Serial.println("Sistema iniciado");
  Serial.println();

  Serial.println("Etapas:");
  Serial.println("0-30 s  -> BAIXO");
  Serial.println("30-60 s -> MEIO");
  Serial.println("60-90 s -> CIMA");
  Serial.println();

  Serial.println("Formato:");
  Serial.println("altura,setpoint,pwm,erro");
  Serial.println();

  tempoInicio = millis();
}

void loop() {
  // controla a taxa de amostragem do PID
  unsigned long agora = millis();
  if (agora - tempoAnterior < (Ts * 1000)) {
    return;
  }
  tempoAnterior = agora;

  // atualiza setpoint conforme o tempo
  atualizarSetpoint();

  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  // =========================
  // LEITURA VÁLIDA DO SENSOR
  if (measure.RangeStatus != 4 && measure.RangeMilliMeter != 65535) {

    // distância do sensor até a esfera
    float distanciaCM = measure.RangeMilliMeter / 10.0;

    // altura da esfera em relação à base
    float altura = H - distanciaCM;

    // limita altura
    if (altura < 0) altura = 0;
    if (altura > H) altura = H;

    // =========================
    // PID
    erro = setpointAtual - altura;

    // integral
    integral += erro * Ts;

    // anti-windup
    if (integral > 40) integral = 40;
    if (integral < -40) integral = -40;

    // derivada
    derivada = (erro - erroAnterior) / Ts;

    // saída do PID
    saidaPID = (Kp * erro) + (Ki * integral) + (Kd * derivada);

    // PWM final
    int pwm = PWM_BASE + (int)saidaPID;

    // limita PWM
    if (pwm > PWM_MAX) pwm = PWM_MAX;
    if (pwm < PWM_MIN) pwm = PWM_MIN;

    // aplica na ventoinha
    ledcWrite(PWM_PIN, pwm);

    // guarda erro anterior
    erroAnterior = erro;

    // =========================
    // SERIAL

    Serial.print("Altura:");
    Serial.print(altura, 2);
    Serial.print(", ");
    Serial.print("Setpoint Atual:");
    Serial.print(setpointAtual, 2);
    Serial.print(", ");
    Serial.print("PWM:");
    Serial.print(pwm);
    Serial.print(", ");
    Serial.print("Erro:");
    Serial.println(erro, 2);
  }

  else {
    // se perder leitura, mantém PWM base
    ledcWrite(PWM_PIN, PWM_BASE);

    Serial.print("0,");
    Serial.print(setpointAtual, 2);
    Serial.print(",");
    Serial.print(PWM_BASE);
    Serial.print(",");
    Serial.println("0");
  }
}
