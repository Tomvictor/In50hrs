/*
  Character analysis operators

 Examples using the character analysis operators.
 Send any byte and the sketch will tell you about it.

 created 29 Nov 2010
 modified 2 Apr 2012
 by Tom Igoe

 This example code is in the public domain.
 */

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // send an intro:
  Serial.println("Type something");
  Serial.println();
}

void loop() {
  // get any incoming bytes:
  if (Serial.available() > 0) {
    int thisChar = Serial.read();
    Serial.write(thisChar);
    // say what was sent:
    /*
    Serial.print("You sent me: \'");
    Serial.write(thisChar);
    Serial.print("\'  ASCII Value: ");
    Serial.println(thisChar);
*/

    // analyze what was sent:
    /*
    if (isAlphaNumeric(thisChar)) {
      Serial.println("it's alphanumeric");
    }
    */

  

    // add some space and ask for another byte:
    Serial.println();
    Serial.println("Give me another byte:");
    Serial.println();
  }
}
