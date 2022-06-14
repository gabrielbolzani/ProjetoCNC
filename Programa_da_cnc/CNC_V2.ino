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

float accuracy = 0.188;
double step_mm_x = 10;
double step_mm_y = 10;
double step_mm_z = 10;
int x_feedRate = 100;
int y_feedRate = 100;
int z_feedRate = 100;
String cmd = "";
double coords[4];
double posicaoAtual[3];

String inputString = "";
bool stringComplete = false;

void setup() {
  inputString.reserve(200);
  Serial.begin(115200);
  pinMode(LimitXAxes, INPUT_PULLUP);
  pinMode(LimitYAxes, INPUT_PULLUP);
  pinMode(LimitZAxes, INPUT_PULLUP);
  pinMode(StepPusle_X, OUTPUT);
  pinMode(StepPusle_Y, OUTPUT);
  pinMode(StepPusle_Z, OUTPUT);
  pinMode(StepDir_X, OUTPUT);
  pinMode(StepDir_Y, OUTPUT);
  pinMode(StepDir_Z, OUTPUT);
  pinMode(StepperEn, OUTPUT);
  pinMode(Spindle, OUTPUT);
  coords[0] = 0;
  coords[1] = 0;
  coords[2] = 0;
  coords[3] = 0;
  posicaoAtual[0] = 0;
  posicaoAtual[1] = 0;
  posicaoAtual[2] = 0;
}



void loop() {
  int cont = 0;
  while (Serial.available()) {
    inputString = Serial.readString();
    stringComplete = true;
  } 
  if (stringComplete) {
    Serial.println(inputString);
    while (inputString[cont] != ' ') {
      cmd += inputString[cont];
      cont++;
    }
    switch (inputString[0]) {
      case 'G':
        //Verificar se é g0, g1 ou g28
        if (cmd == "G0") {
            cont++; //PULA O ESPAÇO ENTRE G0 E X;
            ReadCoords(inputString, cont, false);
            if(coords[0] < 0){
              directionX = false; //DETERMINA O SENTIDO DE ROTACAO DO MOTOR DE PASSO EM X
              coords[0] = coords[0] * (-1);
            }else{
                directionX = true;
            }
            if(coords[1] < 0){
              directionY = false; //DETERMINA O SENTIDO DE ROTACAO DO MOTOR DE PASSO EM Y
              coords[1] = coords[1] * (-1);
            }else{
                directionY = true;
            }
            if(coords[2] < 0){
              directionZ = false; //DETERMINA O SENTIDO DE ROTACAO DO MOTOR DE PASSO EM Z
              coords[2] = coords[2] * (-1);
            }else{
                directionZ = true;
            }
            ToImplementG0Func(coords[0], coords[1], coords[2], accuracy);
        } else if (cmd == "G1") {
            cont++; //PULA O ESPAÇO ENTRE G1 E X;
            ReadCoords(inputString, cont, true);
            if(coords[0] < 0){
              directionX = false; //DETERMINA O SENTIDO DE ROTACAO DO MOTOR DE PASSO EM X
              coords[0] = coords[0] * (-1);
            }else{
                directionX = true;
            }
            if(coords[1] < 0){
              directionY = false; //DETERMINA O SENTIDO DE ROTACAO DO MOTOR DE PASSO EM Y
              coords[1] = coords[1] * (-1);
            }else{
                directionY = true;
            }
            if(coords[2] < 0){
              directionZ = false; //DETERMINA O SENTIDO DE ROTACAO DO MOTOR DE PASSO EM Z
              coords[2] = coords[2] * (-1);
            }else{
                directionZ = true;
            }
            ToImplementG1Func(coords[0], coords[1], coords[2], accuracy);
        } else if (cmd == "G28") {
          func_G28();
        } else {
          Serial.print("O comando ");
          Serial.print(cmd);
          Serial.println(" não é suportado! ");
        }
        break;
      case '$':
        if (cmd == "$help") {
          //Chamar função de ajuda
        } else if (cmd == "$$") {
          //Chamar função Que moostra congiguração
        } else if (cmd == "G28") {
          //Chamar função que recebe configuração
        } else {
          Serial.print("O comando ");
          Serial.print(cmd);
          Serial.println(" não é suportado! ");
        }
        break;
      default:
        Serial.println("Sentença fora de padrão");
        Serial.println("Digite $help para ajuda");
        break;
    }
    inputString = "";
  }
  cmd = "";
  stringComplete = false;
}



void ReadCoords(String inputString, int cont, bool G1){
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
    coords[0] = 0;
    coords[1] = 0;
    coords[2] = 0;
    coords[3] = 0;
  //G0 X156 Y442 Z5 F1000
  while(cont < inputString.length()){
    Serial.println("coords");
    String numeroStr = "";
    if(inputString[cont] == 'X'){
      cont++;
      while(inputString[cont] != ' '){
        numeroStr += inputString[cont];
        cont++;
      }
      coords[0] = numeroStr.toInt();
    }else if(inputString[cont] == 'Y'){
      cont++;
      while(inputString[cont] != ' '){
        numeroStr += inputString[cont];
        cont++;
      }
      coords[1] = numeroStr.toInt();
    }else if(inputString[cont] == 'Z'){
      cont++;
        while(inputString[cont] != ' '){
          numeroStr += inputString[cont];
          cont++;
        }
      coords[2] = numeroStr.toInt();
    }else if(inputString[cont] == 'F'){
      cont++;
      while(cont != inputString.length()){
        numeroStr += inputString[cont];
        cont++;
      }
      coords[3] = numeroStr.toInt();
    }
    cont++;
  }
  Serial.print("Absoluta x: ");
  Serial.println(coords[0]);
  Serial.print("Absoluta y: ");
  Serial.println(coords[1]);
  Serial.print("Absoluta z: ");
  Serial.println(coords[2]);
  Serial.print("Velocidade: ");
  Serial.println(coords[3]);
  posicaoAtual[0] =posicaoAtual[0]+ coords[0];
  posicaoAtual[1] =posicaoAtual[1]+ coords[1];
  posicaoAtual[2] =posicaoAtual[2]+ coords[2];
}



void ToImplementG0Func(float x_desloc_mm, float y_desloc_mm, float z_desloc_mm, float accuracy){
  Serial.print("Final x: ");
  Serial.println(posicaoAtual[0] =+ coords[0]);
  Serial.print("Final y: ");
  Serial.println(posicaoAtual[1] =+ coords[1]);
  Serial.print("Final z: ");
  Serial.println(posicaoAtual[2] =+ coords[2]);
  Serial.print("Velocidade: ");
  Serial.println(coords[3]);
  while((x_desloc_mm>=0) || (y_desloc_mm>=0) || (z_desloc_mm>=0)){
    while(z_desloc_mm>=0){
      digitalWrite(StepPusle_Z, HIGH);
      delay(5);
      digitalWrite(StepPusle_Z, LOW);
      delay(5);
      z_desloc_mm-=accuracy;
    }
    if(x_desloc_mm>=0){
      digitalWrite(StepPusle_X, HIGH);
      delay(5);
      digitalWrite(StepPusle_X, LOW);
      delay(5);
      x_desloc_mm-=accuracy;
    }
    if(y_desloc_mm>=0){
      digitalWrite(StepPusle_Y, HIGH);
      delay(5);
      digitalWrite(StepPusle_Y, LOW);
      delay(5);
      y_desloc_mm-=accuracy;
    }
  }
}






void ToImplementG1Func(float x_desloc_mm, float y_desloc_mm, float z_desloc_mm, float accuracy){
  Serial.print("Final x: ");
  Serial.println(posicaoAtual[0]);
  Serial.print("Final y: ");
  Serial.println(posicaoAtual[1]);
  Serial.print("Final z: ");
  Serial.println(posicaoAtual[2] =+ coords[2]);
  Serial.print("Velocidade: ");
  Serial.println(coords[3]);
  float resolution;
  
  for(int zStep=1; zStep<(z_desloc_mm/accuracy); zStep++){
    digitalWrite(StepPusle_Z, HIGH);
    delay(5);
    digitalWrite(StepPusle_Z, LOW);
    delay(5);
    z_desloc_mm-=accuracy;
    delay(100);
  }
  
    delay(500);
    resolution = x_desloc_mm / y_desloc_mm;
    digitalWrite(StepPusle_X, HIGH);
    delay(5);
    digitalWrite(StepPusle_X, LOW);
    delay(5);
    x_desloc_mm-=accuracy;
    while ((x_desloc_mm>0) || (y_desloc_mm>0)){
     float resolution_w =  x_desloc_mm / y_desloc_mm;
     Serial.println(resolution_w);
     Serial.println(resolution);
      if(x_desloc_mm<0){
      //ACIONA O MOTOR EM Y;
      digitalWrite(StepPusle_Y, HIGH);
      delay(5);
      digitalWrite(StepPusle_Y, LOW);
      delay(5);
      y_desloc_mm-=accuracy;
      delay(100);
      }else if(y_desloc_mm<0){
      //ACIONA O MOTOR EM X;
      digitalWrite(StepPusle_X, HIGH);
      delay(5);
      digitalWrite(StepPusle_X, LOW);
      delay(5);
      x_desloc_mm-=accuracy;
      delay(100);
      }else if(resolution_w > resolution){
      //ACIONA O MOTOR EM X;
      digitalWrite(StepPusle_X, HIGH);
      delay(5);
      digitalWrite(StepPusle_X, LOW);
      delay(5);
      x_desloc_mm-=accuracy;
      delay(100);
      }else{
      //ACIONA O MOTOR EM Y;
      digitalWrite(StepPusle_Y, HIGH);
      delay(5);
      digitalWrite(StepPusle_Y, LOW);
      delay(5);
      y_desloc_mm-=accuracy;
      delay(100);
      
      }
    }
  }






void func_G28 () {
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
  posicaoAtual[0] = 0;
  posicaoAtual[1] = 0;
  posicaoAtual[2] = 0;
}
