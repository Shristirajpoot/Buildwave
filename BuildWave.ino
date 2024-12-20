#include <SPI.h>
#include <Ethernet.h>

#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>

#include <ArduinoJson.h>
#include <Thread.h>

byte ip[] = { 192, 168, 2, 243 };
byte gateway[] = { 192, 168, 2, 1 };
byte subnet[] = { 255, 255, 255, 0 };
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define BLACK   0x0000
//#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define PIN_SUCESSO 3
#define PIN_FALHA   10


const char FALHA   = 'f';
const char SUCESSO = 's';
const char CONSTR  = 'c';
const char INICIO  = 'i';
const char PAROU   = 'p';
const char ERRO    = 'e';

char stat    = ' ';
boolean requisitou = false;
String descricaoErro = "";

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

EthernetServer server(80);

struct DetalheFalha {
  String proj;
  String build;
  String usu;
  String desc;
};

DetalheFalha detFalha;

Thread threadConstruindo;

void setup() {
  Serial.begin(9600);
    
  Ethernet.begin(mac, ip, gateway, subnet);
  /*Escrever(2, 10, 10, RED, F("Inicializando ethernet DHCP"));
  while (!Ethernet.begin(mac)) {
    tft.print(".");  
    delay(500);
  }*/

  server.begin();

  pinMode(PIN_SUCESSO, OUTPUT);
  pinMode(PIN_FALHA, OUTPUT);
  digitalWrite(PIN_SUCESSO, LOW);
  digitalWrite(PIN_FALHA, HIGH);

  threadConstruindo.setInterval(1000);
  threadConstruindo.onRun(LedConstruindo);
  
  ConfigurarTela();
  TelaInicial();
}

void loop() {
  ProcessarRequisicao();
  ProcessarResultado();
  delay(1);
}

void ProcessarRequisicao() {
  requisitou = false;
  descricaoErro = "";

  EthernetClient client = server.available();
  if (client) {
    // para funcionaar
    tft.fillScreen(BLACK);

    boolean linhaVazia = false;

    while (client.connected()) {
      while (client.available()) {

        char c = client.read();
        delay(1);

        if (c == '\n' && linhaVazia) {

          // Se a ultima linha e branco, então aqui é o corpo
          requisitou = true;
          String corpo = "";
          
          while (client.available()) {
            char j = client.read();
            corpo = corpo + j;
            delay(1);
          }

          String resp  = "{\"result\":\"ok\"}";
          String falha = "indefinido";
          Serial.println(corpo);

          DynamicJsonBuffer jbuff;
          JsonObject& joCorpo = jbuff.parseObject(corpo);
          if (joCorpo.success()) {
            String status = joCorpo["stat"];
            char _stat = status.charAt(0);

            if ((_stat == SUCESSO) || (_stat == CONSTR) || (_stat == FALHA) || (_stat == INICIO) || (_stat == PAROU)) {
              stat = _stat;
              if (_stat = FALHA) {
                String proj    = joCorpo["proj"];
                String build   = joCorpo["build"];
                String usu     = joCorpo["usu"];
                String desc    = joCorpo["desc"];
                detFalha.proj  = proj;
                detFalha.build = build;
                detFalha.usu   = usu;
                detFalha.desc  = desc;
              }
            } else {
              stat = ERRO;
              descricaoErro = "Nao encontrado no status ou valor invalido.";
            }
          } else {
            stat = ERRO;
            descricaoErro = "Conteudo invalido";
          }

          if (stat == ERRO) {
            resp = "{\"result\":\"falha\",\"motivo\":\"" + descricaoErro + "\"}";
          }

          Serial.println(resp);

          client.println(F("HTTP/1.0 200 OK"));
          client.println(F("Content - Type: application/json"));
          client.println();
          client.println(resp);
          client.stop();

        } else if (c == '\n') {
          linhaVazia = true;
        } else if (c != '\r') {
          linhaVazia = false;
        }
      }
    }
  }
}

void ProcessarResultado() {

  if (stat == CONSTR) {
    digitalWrite(PIN_FALHA, HIGH);
    threadConstruindo.run();
  } else if (stat == SUCESSO) {
    digitalWrite(PIN_SUCESSO, HIGH);
    digitalWrite(PIN_FALHA, HIGH);
  } else if (stat == FALHA) {
    digitalWrite(PIN_FALHA, LOW);
    digitalWrite(PIN_SUCESSO, LOW);
  } else {
    digitalWrite(PIN_FALHA, HIGH);
    digitalWrite(PIN_SUCESSO, LOW);
  }

  if (requisitou) {
    if (stat == SUCESSO) {
      TelaSucesso();
    } else if (stat == CONSTR) {
      TelaConstruindo();
    } else if (stat == FALHA) {
      TelaFalha();
    } else if (stat == INICIO) {
      TelaIniciou();
    } else if (stat == PAROU) {
      TelaParou();
    } else if (stat == ERRO) {
      TelaErro();
    }
  }
}

void DesenharBorda(uint16_t cor, uint16_t fundo) {
  tft.fillScreen(cor);
  tft.fillRect(5, 5, 310, 230, fundo);
}

void DesenharBola(int pos_x, int pos_y, int raio, int bor, uint16_t cor, uint16_t cor_bor) {
  tft.fillCircle(pos_x, pos_y, raio + bor, cor_bor);
  tft.fillCircle(pos_x, pos_y, raio, cor);
}

void Escrever(int tam, int pos_x, int pos_y, uint16_t cor, String txt ) {
  tft.setTextSize(tam);
  tft.setCursor(pos_x, pos_y);
  tft.setTextColor(cor);
  tft.print(txt);
}

String IpAddrStr(const IPAddress& ip) {
  return String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
}

void ConfigurarTela() {
  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(3);
}

void TelaInicial() {
  DesenharBorda(YELLOW, BLACK);
  Escrever(2, 50, 20, CYAN, F("Monitor de Builds"));
  Escrever(2, 15, 205, CYAN, F("Oper. end.:"));
  Escrever(2, 145, 205, CYAN, IpAddrStr(Ethernet.localIP()));
  Escrever(6, 45, 73, WHITE, F("BUILD"));
  Escrever(4, 130, 120, RED, F("Guard"));
}

void TelaIniciou () {
  TelaInicial();
  Escrever(2, 100, 170, GREEN, F("(iniciou)"));
}

void TelaParou () {
  TelaInicial();
  Escrever(2, 115, 170, RED, F("(parou)"));
}

void TelaSucesso() {
  DesenharBorda(GREEN, WHITE);
  DesenharBola(155, 65, 45, 5, GREEN, BLACK);
  Escrever(5, 50, 150, BLACK, F("SUCESSO"));
}

void TelaConstruindo() {
  TelaSucesso();
  Escrever(2, 150, 200, MAGENTA, F("Construindo..."));
}

void TelaFalha() {
  DesenharBorda(RED, BLACK);
  DesenharBola(35, 35, 28, 2, RED, WHITE);
  Escrever(5, 100, 18, WHITE, F("FALHA"));
  Escrever(2, 10, 65, YELLOW, F("Projeto"));
  Escrever(2, 10, 115, YELLOW, F("Usuario"));
  Escrever(2, 240, 115, YELLOW, F("Build"));
  Escrever(2, 10, 165, YELLOW, F("Desc."));
  Escrever(3, 10, 85, WHITE, detFalha.proj);
  Escrever(3, 10, 135, WHITE, detFalha.usu);
  Escrever(5, 200, 135, WHITE, detFalha.build);
  Escrever(2, 10, 185, WHITE, detFalha.desc.substring(0, 25));
  Escrever(2, 10, 205, WHITE, detFalha.desc.substring(25, 50));
}

void TelaErro() {
  DesenharBorda(RED, BLACK);
  Escrever(4, 110, 18, RED, F("ERRO!"));
  Escrever(2, 10, 50, WHITE, descricaoErro);
}

void LedConstruindo() {
  digitalWrite(PIN_SUCESSO, HIGH);
  delay(500);
  digitalWrite(PIN_SUCESSO, LOW);
  delay(500);
}

