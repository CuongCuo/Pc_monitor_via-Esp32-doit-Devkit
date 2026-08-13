# Bài 11: PC System Monitor (Màn Hình Giám Sát Hệ Thống PC)

## 📋 Mô Tả Dự Án
Dự án này xây dựng một hệ thống giám sát hiệu suất PC theo thời gian thực. Thông tin CPU và RAM từ máy tính sẽ được gửi đến ESP32 qua kết nối Serial và hiển thị trên màn hình OLED.

## 🎯 Chức Năng Chính
- **Đọc dữ liệu hệ thống PC**: Sử dụng Python để lấy thông tin CPU và RAM
- **Truyền dữ liệu qua Serial**: Gửi dữ liệu từ PC đến ESP32 với bộ đếm thời gian 0.5 giây
- **Hiển thị trên OLED**: Màn hình 128x64 hiển thị CPU% và RAM% một cách rõ ràng
- **Giao diện thân thiện**: Thiết kế giao diện với tiêu đề "PC SYSTEM" và đường phân cách

## 🔧 Phần Cứng Cần Thiết
- **Microcontroller**: ESP32 DOIT DevKit v1
- **Màn hình**: OLED SSD1306 (128x64)
- **Kết nối I2C**:
  - SDA: GPIO 21
  - SCL: GPIO 22
  - Địa chỉ I2C: 0x3D
- **Cáp USB**: Để kết nối giữa PC và ESP32

## 📦 Thư Viện Yêu Cầu
###ESP32 (C++)
- `Adafruit_GFX.h` - Thư viện đồ họa
- `Adafruit_SSD1306.h` - Điều khiển màn hình OLED
- `Wire.h` - Giao thức I2C

### Phía PC (Python)
```
psutil - Đọc thông tin hệ thống (CPU, RAM)
pyserial - Giao tiếp Serial
```

## 💻 Cài Đặt

### 1. Chuẩn Bị Phần Cứng
- Kết nối OLED với ESP32 qua I2C (SDA: GPIO 21, SCL: GPIO 22)
- Kết nối ESP32 với PC qua cáp USB

### 2. Lập Trình ESP32
```bash
# Sử dụng PlatformIO
pio run -t upload
```

### 3. Cài Đặt Dependencies Python
```bash
pip install psutil pyserial
```

### 4. Chạy Chương Trình PC
```bash
python src/pc_monitor.py
```

## ⚙️ Cấu Hình

### Cấu Hình Serial (trong pc_monitor.py)
```python
ser = serial.Serial('COM5', 115200)  # Thay 'COM5' bằng cổng COM của bạn
```

**Cách tìm cổng COM:**
- Windows: Device Manager → Ports (COM & LPT)
- Tìm thiết bị "USB-SERIAL CH340" hoặc tương tự

### Bộ Đếm Thời Gian
- Khoảng thời gian gửi dữ liệu: **0.5 giây** (có thể thay đổi trong `time.sleep(0.5)`)

## 📊 Dòng Dữ Liệu
```
PC (Python) → Serial (COM) → ESP32 → OLED Display
     ↓
  psutil đọc CPU% và RAM%
     ↓
  Định dạng: "CPU_VALUE,RAM_VALUE\n"
  VD: "35,62\n" (CPU 35%, RAM 62%)
```

## 🖥️ Giao Diện Hiển Thị
```
┌────────────────────────────┐
│        PC SYSTEM           │
├────────────────────────────┤
│                            │
│ CPU: 45%                   │
│                            │
│ RAM: 72%                   │
│                            │
└────────────────────────────┘
```

## 🔍 Khắc Phục Sự Cố

### OLED không hiển thị
- Kiểm tra kết nối I2C (SDA/SCL)
- Kiểm tra địa chỉ I2C: 0x3D
- Kiểm tra điện áp (3.3V cho ESP32)

### Python không kết nối được
```python
# Kiểm tra cổng COM
import serial.tools.list_ports
ports = serial.tools.list_ports.comports()
for p in ports:
    print(p)
```

### Dữ liệu không cập nhật
- Kiểm tra baud rate: 115200
- Kiểm tra cáp USB
- Thử reset ESP32

## 📝 Cấu Trúc Tệp
```
Bai11_pcmonitor/
├── platformio.ini          # Cấu hình PlatformIO
├── README.md               # Tài liệu này
├── src/
│   ├── main.cpp            # Mã chương trình ESP32
│   └── pc_monitor.py       # Mã chương trình Python (PC)
├── include/
└── lib/
```

## 🎓 Kiến Thức Học Được
- ✅ Giao tiếp Serial giữa PC và Microcontroller
- ✅ Đọc dữ liệu hệ thống sử dụng Python (psutil)
- ✅ Điều khiển màn hình OLED với I2C
- ✅ Xử lý chuỗi dữ liệu (parsing) trong C++
- ✅ Xử lý lỗi kết nối Serial

## 📌 Ghi Chú
- Hãy đảm bảo ESP32 được cấp nguồn đủ khi chạy
- Nếu cổng COM thay đổi, hãy cập nhật trong `pc_monitor.py`
- OLED sẽ hiển thị "Waiting PC..." khi chưa nhận dữ liệu

## 🔗 Tài Liệu Tham Khảo
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [psutil Documentation](https://psutil.readthedocs.io/)
- [PySerial](https://pyserial.readthedocs.io/)
- [ESP32 I2C Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/i2c.html)

---
**Tác giả**: CuongCuo  
**Ngày cập nhật**: 2026-08-13
