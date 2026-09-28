// --- Konfigurasi Pin Sensor ---
int kiri = 2;
int tengah = 3;
int kanan = 4;

// --- Konfigurasi Pin Motor ---
int ENA = 5; int ENB = 6;  
int IN1 = 8; int IN2 = 9;
int IN3 = 10; int IN4 = 11;

// --- TUNING PERFECT (Haluskan Belok) ---
float Kp = 35;      
float Kd = 62;      
int speedBase = 85; 
float lastError = 0;

void setup() {
  // Aktifkan Serial Monitor
  Serial.begin(9600);
  Serial.println("Robot Line Follower PID Ready!");

  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(kiri, INPUT); pinMode(tengah, INPUT); pinMode(kanan, INPUT);
}

void loop() {
  int k = digitalRead(kiri);
  int t = digitalRead(tengah);
  int ka = digitalRead(kanan);

  float error = 0;

  // Logika Error (Hitam = 1, Putih = 0)
  if (k == 0 && t == 1 && ka == 0) error = 0;   
  else if (k == 1 && t == 1 && ka == 0) error = -1; 
  else if (k == 1 && t == 0 && ka == 0) error = -2; 
  else if (k == 0 && t == 1 && ka == 1) error = 1;  
  else if (k == 0 && t == 0 && ka == 1) error = 2;  
  else if (k == 0 && t == 0 && ka == 0) {           
    if (lastError > 0) error = 3; 
    else error = -3;
  }

  // --- Rumus PID (PD Control) ---
  float motorSpeed = (Kp * error) + (Kd * (error - lastError));
  
  // OUTPUT KE SERIAL MONITOR
  Serial.print("S:"); Serial.print(k); Serial.print(t); Serial.print(ka);
  Serial.print(" | Err:"); Serial.print(error);
  Serial.print(" | MSpeed:"); Serial.println(motorSpeed);

  lastError = error;

  int speedA = speedBase + motorSpeed; 
  int speedB = speedBase - motorSpeed; 

  // EKSEKUSI GERAK
  if (error <= -2.5) {
    gerakPivot(speedA, speedB, "KIRI");
  } 
  else if (error >= 2.5) {
    gerakPivot(speedA, speedB, "KANAN");
  } 
  else {
    gerakMaju(speedA, speedB);
  }
  
  // Delay kecil agar serial monitor tidak terlalu cepat dan berat
  delay(10); 
}

void gerakMaju(int spdA, int spdB) {
  analogWrite(ENA, constrain(abs(spdA), 0, 170));
  analogWrite(ENB, constrain(abs(spdB), 0, 170));
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void gerakPivot(int spdA, int spdB, String arah) {
  analogWrite(ENA, constrain(abs(spdA), 30, 130));
  analogWrite(ENB, constrain(abs(spdB), 30, 130));
  
  if (arah == "KIRI") {
    digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); 
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  
  } else {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  
    digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); 
  }
}

void stopRobot() {
  analogWrite(ENA, 0); analogWrite(ENB, 0);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}