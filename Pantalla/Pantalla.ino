// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  //int valorADC = analogRead(A0);
  //float voltaje = (5.0 / 1023.0) * valorADC;

  //Serial.println(voltaje); // Envía el mensaje
  //delay(1000); // Espera 1 segundo

  if (Serial.available() > 0) { // Si hay datos disponibles para leer
    float voltaje = Serial.parseFloat();
    lcd.setCursor(0, 0);// set the cursor to column 0, line 1
  lcd.print("Voltaje: "); // Imprime el texto que indica que el valor mostrado es el voltaje
lcd.print(voltaje); // Imprime el valor de voltaje
lcd.print(" V"); // Imprime " V" para indicar que la unidad es voltios
  }
  
}