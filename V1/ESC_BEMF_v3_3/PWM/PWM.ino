void setup() {
  // Initialiser la communication série
  Serial.begin(9600);

  // Configurer les broches 5 et 6 comme sorties (correspondant à OC0B et OC0A sur Arduino Uno)
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  // Configurer le Timer/Counter 0 en mode Fast PWM, non-inversé, sans prescaler
  TCCR0A = 0xA3;  // WGM01 = 1, WGM00 = 1 (Fast PWM), COM0A1 = 1 (non-inversé sur OC0A), COM0B1 = 1 (non-inversé sur OC0B)
  TCCR0B = 0x01;  // CS00 = 1 (pas de prescaler)

  // Initialiser OCR0A et OCR0B pour un rapport cyclique de 0%
  OCR0A = 0;
  OCR0B = 0;
}

void loop() {
  // Vérifier si des données sont disponibles sur la liaison série
  if (Serial.available() > 0) {
    // Lire les données en tant qu'entier
    int percentage = Serial.parseInt();

    // Vérifier si le pourcentage est entre 0 et 100
    if (percentage >= 0 && percentage <= 100) {
      // Calculer la valeur OCR0A et OCR0B correspondante
      int pwmValue = map(percentage, 0, 100, 0, 255);

      // Mettre à jour OCR0A et OCR0B pour ajuster le rapport cyclique
      OCR0A = pwmValue;
      OCR0B = pwmValue;
    }
  }
}
