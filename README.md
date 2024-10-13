# Projeto CNC - Firmware
## Visão Geral
Este projeto foi desenvolvido como parte de um trabalho de faculdade, no qual fomos desafiados a criar uma CNC (Controle Numérico Computadorizado) e implementar um firmware personalizado para controlar seus eixos e funções principais. 
O desenvolvimento do firmware foi uma exigência do professor, que nos orientou a criar uma solução que aceitasse comandos G-Code. Embora o firmware tenha sido elaborado, a CNC foi posteriormente testada com o firmware GRBL, que comprovou a funcionalidade do hardware.

Histórico
O professor especificou que deveríamos desenvolver um firmware do zero para a CNC. O objetivo era garantir que a máquina fosse capaz de interpretar comandos G-Code para realizar movimentações básicas dos eixos X, Y e Z, bem como controlar funções adicionais, como o spindle e a refrigeração.

Porém, como o foco do projeto também era validar o hardware, testamos a CNC utilizando o GRBL, um firmware amplamente reconhecido para controle de CNCs. Sabemos que o GRBL funcionou corretamente com o nosso hardware, mas não lembro se validamos 100% do nosso firmware desenvolvido, já que isso ocorreu há dois anos.

# Funcionalidades Implementadas no Firmware
- Movimentação dos Eixos (X, Y, Z):

  - Controle básico dos motores de passo para movimentar os eixos.
  - Ajustes de direção e taxa de avanço (feed rate) para os três eixos.
  - Suporte para os comandos de G-Code G0, G1 e G28.

- Limites e Segurança:
  - Implementação de sensores de limite para proteger os eixos da CNC.
  - Função de "homing" (G28), que move a CNC até os limites físicos para definir a posição inicial.

- Comandos de G-Code:
  - Suporte para comandos G0 (movimento rápido), G1 (movimento controlado) e G28 (homing).
  - Interpretação e resposta aos comandos enviados via interface serial.

- Controles Adicionais:
  - Controle do spindle e refrigeração via pinos dedicados.
  - Opção de abortar ou pausar o movimento através de botões dedicados.

# Testes com o GRBL
Após o desenvolvimento do firmware solicitado, decidimos testar a CNC com o GRBL para validar o hardware, uma vez que o GRBL é uma solução de código aberto amplamente utilizada para o controle de CNCs. O teste com o GRBL nos permitiu confirmar que o hardware desenvolvido estava funcionando conforme o esperado.
