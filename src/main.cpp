#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 21
#define OLED_SCL 22
// KHỞI TẠO MÀN OLED 
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1);

void setup(){
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    for(;;); // Lỗi không tìm thấy OLED -> Dừng
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(15, 25);
  display.print("Waiting PC...");
  display.display();
}
void loop(){
  // kiểm tra có dữ liệu gửi qua serial-> tách chuỗi nếu có-> clear màn cũ
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Đọc đến ký tự xuống dòng
    int commaIndex = input.indexOf(',');
    // nếu xuất hiện input cpu \n ram  {0,1}
    if(commaIndex >0){ // chuyển sang int
      int cpuVal = input.substring(0,commaIndex).toInt();
      int ramVal = input.substring(commaIndex+1).toInt();
      display.clearDisplay();

      // --- HÀNG TIÊU ĐỀ ---
      display.setTextSize(1);
      display.setCursor(30, 0);
      display.print("PC SYSTEM");
      display.drawLine(0, 10, 127, 10, SSD1306_WHITE); // Kẻ đường phân cách

      // --- HIỂN THỊ CPU (Cỡ chữ 2) ---
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print("CPU: ");
      display.print(cpuVal);
      display.print("%");

      // --- HIỂN THỊ RAM (Cỡ chữ 2) ---
      display.setCursor(0, 44);
      display.print("RAM: ");
      display.print(ramVal);
      display.print("%");

      // Cập nhật lên màn hình OLED
      display.display();
      }
    }
}