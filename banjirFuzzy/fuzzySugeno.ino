/* dekalarsi variabel untuk: */
/* set nilai keanggotaan ketinggian air */
float normal[2] = {25,50}; /* kurva turun {a,b}  */
float siaga[3] = {25, 50, 75}; /* kurva segitiga {a,b,c}*/
float bahaya[2] = {50, 75}; /* kurva naik {a,b}*/
/* set nilai keanggotaan curah hujan */
float gerimis[2] = {40,60}; /* kurva turun {a,b}  */
float sedang[3] = {40,60,80}; /* kurva segitiga {a,b,c}*/
float deras[2] = {60,80}; /* kurva naik {a,b}*/
/* set nilai keanggotaan output*/
float Aman = 30;
float Waspada = 60;
float Bahaya = 90;

/* fungsi/class untuk menghitung rumus kurva turun */
float kurvaTurun(float input, float batasA, float batasB) { /* input=nilai dari sensor, batasA=nilai a di kurva, batasB=nilai b di kurva */
  float hasil; /* variabel untuk menyimpan nilai perhitungan rumus */
  float batas[2] = {batasA, batasB}; /* variabel untuk menaruh nilai a dan b kurva */
  if(input <= batas[0]) hasil =1; /* jika batas[0]=(nilai a kurva) hasilnya=1 */
  else if (input >= batas[0] && input <= batas[1]) hasil=(batas[1]-input)/(batas[1]-batas[0]); 
  else if (input >= batas[1]) hasil=0; /* jika batas[1]=(nilai b kurva) hasilnya=0 */
  return hasil;
}
/* fungsi/class untuk menghitung rumus kurva segitiga */
float kurvaSegitiga(float input, float batasA, float batasB, float batasC) {
  float hasil;
  float batas[3] = {batasA, batasB, batasC};
  if(input <= batas[0]) hasil=0; 
  else if (input >= batas[0] && input <=batas[1]) hasil=(input-batas[0])/(batas[1]-batas[0]);
  else if (input >= batas[1] && input <=batas[2]) hasil=(batas[2]-input)/(batas[2]-batas[1]);
  else if (input >= batas[2]) hasil=0;
  return hasil;
}
/* fungsi/class untuk menghitung rumus kurva naik */
float kurvaNaik(float input, float batasA, float batasB){
  float hasil;
  float batas[2] = {batasA, batasB};
  if(input <= batas[0]) hasil=0; 
  else if (input >= batas[0] && input <= batas[1]) hasil=(input-batas[0])/(batas[1]-batas[0]);
  else if (input >= batas[1]) hasil=1;
  return hasil;
}

/* hitung fuzzy */
float fuzzy(float ketinggianAir, float curahHujan){
  /* 1. tahap fuzzyfikasi */
  /* dekalarasi variabel */
  float KAnormal, KAsiaga, KAbahaya, /* deklarasikan variabel untuk menghitung keanggotaan Ketinggian Air (KA) */
        CHgerimis, CHsedang, CHderas; /* deklarasikan variabel untuk menghitung keanggotaan Curah Hujan (CH) */
  /* proses fuzzyfikasi */
  /* keanggotaan Ketinggian Air (KA) */
  KAnormal = kurvaTurun(ketinggianAir, normal[0], normal[1]); /* menggunakan kurva turun */
  KAsiaga = kurvaSegitiga(ketinggianAir, siaga[0], siaga[1], siaga[2]); /* menggunakan kurva segitiga */
  KAbahaya = kurvaNaik(ketinggianAir, bahaya[0], bahaya[1]); /* menggunakan kurva naik */
  /* keangotaan Curah Hujan (CH) */
  CHgerimis = kurvaTurun(curahHujan, gerimis[0], gerimis[1]);
  CHsedang = kurvaSegitiga(curahHujan, sedang[0], sedang[1], sedang[2]);
  CHderas = kurvaNaik(curahHujan, deras[0], deras[1]);

  /* 2. tahap inferensi */
  float rules[9]; /* deklarasikan variabel untuk menyimpan nilai setiap aturan */
  /* proses inferensi (9 rules)*/
  rules[0] = min(KAnormal, CHgerimis);
  rules[1] = min(KAnormal, CHsedang);
  rules[2] = min(KAnormal, CHderas);

  rules[3] = min(KAsiaga, CHgerimis);
  rules[4] = min(KAsiaga, CHsedang);
  rules[5] = min(KAsiaga, CHderas);

  rules[6] = min(KAbahaya, CHgerimis);
  rules[7] = min(KAbahaya, CHsedang);
  rules[8] = min(KAbahaya, CHderas);

  /* 3. tahap defuzzyfikasi */
  float Z, nilai1, nilai2;
  nilai1 = ((rules[0]*Aman)+(rules[1]*Aman)+(rules[2]*Waspada)+
      (rules[3]*Aman)+(rules[4]*Waspada)+(rules[5]*Bahaya)+
      (rules[6]*Waspada)+(rules[7]*Bahaya)+(rules[8]*Bahaya));
  nilai2 = (rules[0]+rules[1]+rules[2]+rules[3]+rules[4]+rules[5]+rules[6]+rules[7]+rules[8]);

  Z = nilai1/nilai2;

  return Z;
}