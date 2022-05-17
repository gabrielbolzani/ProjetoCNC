//----------------------------------
//Pinouts

//Interface
#define Abort 14
#define FeedHold 15
#define Abort 16
#define ColantE 17
#define Coolant 18
#define Probe 19

//Controles
#define StepPusle_X 2
#define StepPusle_Y 3
#define StepPusle_Z 4
#define StepDir_X 5
#define StepDir_Y 6
#define StepDir_Z 7
#define StepperEn 8
#define Spindle 11

// Limites
#define LimitXAxes 9
#define LimitYAxes 10
#define LimitZAxes 12

//----------------------------------
bool directionX = true;
bool directionY = true;
bool directionZ = true;

//Altere essas váriaveis para inverter o sentido de um eixo
//----------------------------------

double step_mm_x = 10;
double step_mm_y = 10;
double step_mm_z = 10;
int x_feedRate = 100;
int y_feedRate = 100;
int z_feedRate = 100;
String CMD = "";
double posicaoAtual[3];
posicaoAtual[0]=0;
posicaoAtual[1]=0;
posicaoAtual[2]=0;

void setup() {
  Serial.begin(115200);
  pinMode(LimitXAxes; INPUT_PULLUP);
  pinMode(LimitYAxes; INPUT_PULLUP);
  pinMode(LimitZAxes; INPUT_PULLUP);
  pinMode(StepPusle_X; OUTPUT);
  pinMode(StepPusle_Y; OUTPUT);
  pinMode(StepPusle_Z; OUTPUT);
  pinMode(StepDir_X; OUTPUT);
  pinMode(StepDir_Y; OUTPUT);
  pinMode(StepDir_Z; OUTPUT);
  pinMode(StepperEn; OUTPUT);
  pinMode(Spindle; OUTPUT);
}

leitura_serial() {
}

void loop() {
  leitura_serial();
  switch (cmd) {
    case "G28"://Comando de Homming
      digitalWrite(StepperEn, HIGH);
      if (directionZ) {
        digitalWrite(StepDir_Z, HIGH);
      } else {
        digitalWrite(StepDir_Z, LOW);
      }
      if (directionX) {
        digitalWrite(StepDir_X, HIGH);
      } else {
        digitalWrite(StepDir_X, LOW);
      }
      if (directionY) {
        digitalWrite(StepDir_Y, HIGH);
      } else {
        digitalWrite(StepDir_Y, LOW);
      }
      while (digitalRead(LimitZAxes) != LOW) {
        digitalWrite(StepPusle_Z, HIGH);
        delay(5);
        digitalWrite(StepPusle_Z, LOW);
        delay(5);
      }
      while ((digitalRead(LimitXAxes) != LOW) || (digitalRead(LimitYAxes) != LOW)) {
        if (digitalRead(LimitXAxes) != LOW) {
          digitalWrite(StepPusle_X, HIGH);
          delay(5);
          digitalWrite(StepPusle_X, LOW);
          delay(5);
        }
        if (digitalRead(LimitYAxes) != LOW) {
          digitalWrite(StepPusle_Y, HIGH);
          delay(5);
          digitalWrite(StepPusle_Y, LOW);
          delay(5);
        }
      }
      Serial.print("Movimento concluido\n");
      posicaoAtual[0]=0;
      posicaoAtual[1]=0;
      posicaoAtual[2]=0;
      break;
    case "G0":

      break;
    case "G1":

      break;
    default:
      Serial.print("Comando não reconhecido\n");
      break;
  }
}
