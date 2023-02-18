float KetinggianAir, CurahHujan, Fuzzy;

void setup() {
  Serial.begin(9600);
}

void loop() {
  KetinggianAir = 29;
  CurahHujan = 62;
  Fuzzy = fuzzy(KetinggianAir, CurahHujan);

  Serial.print("KA: "); Serial.print(KetinggianAir); Serial.print(" CH: "); Serial.println(CurahHujan);
  Serial.print("fuzzy: "); Serial.println(Fuzzy);
  
  delay(2000); 
}
