#define YanginInput A0 // yangin sensor girdi portu
#define YanginOutput 22 // buzzer alarm için çıktı portu

#define HareketInput A1 // hareket sensor için girdi portu
#define HareketOutput 23 // hareket sensor için çıktı portu


#define SicaklikInput A2 // hareket sensor için girdi portu


#include <Keypad.h>
int SifreYesilLed=37;      // sifre yeşil led pin
int SifreKirmiziLed=38;    // sifre kırmızı led pin
const byte satir = 4;      // keypad satir adeti
const byte sutun = 3;      // keypad sutun adeti

char Sifre[4]={'1', '2', '3', '4'};; // sifre tanimlamlari icin
char SifreGirdi[4];
int GirdiSayac=0;

char keys[satir][sutun] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'#','0','*'}
}; // keypad tuslari degerleri tanimlandi

byte satirPin[satir] = { 33, 34, 35, 36 }; // keypad satir sutun pinleri
byte sutunPin[sutun] = { 30, 31 , 32 };
Keypad keypad = Keypad( makeKeymap(keys), satirPin, sutunPin, satir, sutun);

#include<LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int PinDeger;

void setup() {

  lcd.begin(16, 2);
  
  pinMode(YanginInput, INPUT_PULLUP); // yangin pinleri out-in ayarlanmasi
  pinMode(YanginOutput, OUTPUT);
  
  pinMode(HareketInput, INPUT_PULLUP); // hareket pinleri out-in ayarlanmasi
  pinMode(HareketOutput, OUTPUT);

  pinMode(SifreYesilLed, OUTPUT); // sifre pinleri ayarlanmasi
  pinMode(SifreKirmiziLed, OUTPUT);
  digitalWrite(SifreKirmiziLed,LOW);
  digitalWrite(SifreYesilLed,LOW);

  pinMode(SicaklikInput, INPUT); // Sicaklik pin ayarlanmasi
  
}

void loop() {

// Sicakli sensor kodlamasi start
lcd.begin(0,0);
PinDeger = analogRead(SicaklikInput);
float fPinDeger=PinDeger;
float Sicaklik;
Sicaklik=(fPinDeger/1024.0)*5000.0;
Sicaklik=Sicaklik/10.0;
if(Sicaklik<20.0){
  lcd.print("Sicaklik Dustu");
}
else if(Sicaklik>30.0){
  lcd.print("Sicaklik Yukseldi");
}
else{
  lcd.print("Sicaklik Normal");
}

// Sicakli sensor kodlamasi start


// Yangin sensoru kodlamasi start
int YanginKontrol = digitalRead(YanginInput);
if(YanginKontrol==HIGH)
{
  digitalWrite(YanginOutput, HIGH);
}
else
{
  digitalWrite(YanginOutput, LOW); 
}
// Yangin sensoru kodlamasi bitis


// Hareket sensoru kodlamasi start
int HareketKontrol = digitalRead(HareketInput);
if(HareketKontrol==HIGH)
{
  digitalWrite(HareketOutput, HIGH);
}
else
{
 digitalWrite(HareketOutput, LOW); 
}
// Hareket sensoru kodlamasi bitis


// Sifre kodlamasi start
char key = keypad.getKey();
if(key){
    SifreGirdi[GirdiSayac++]=key;
    delay(100);
  }
  if(GirdiSayac==4){
    if ((strncmp(SifreGirdi, Sifre, 4) == 0)){
      digitalWrite(SifreKirmiziLed,LOW);
      digitalWrite(SifreYesilLed,HIGH);
      delay(2000);
      digitalWrite(SifreYesilLed,LOW);
      GirdiSayac=0;
    }
    else{
      digitalWrite(SifreKirmiziLed,HIGH);
      digitalWrite(SifreYesilLed,LOW);
      delay(2000);
      digitalWrite(SifreKirmiziLed,LOW);
      GirdiSayac=0;
    }
  }
// Sifre kodlamasi bitis


}
