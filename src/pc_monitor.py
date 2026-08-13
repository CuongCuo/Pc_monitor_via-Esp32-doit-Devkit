import time
import psutil # các thư viện quan trọng đọc dữ liệu máy 
import serial
# kết nối-> đọc dữ liệu(nhớ set lại bẩute và cổng COM)
try:
    ser = serial.Serial('COM5',115200)
    time.sleep(2) # chờ kết nối serial ổn định 

    while True: 
        cpu = int(psutil.cpu_percent(interval = None))
        ram = int(psutil.virtual_memory().percent)

        data_string = f"{cpu},{ram}\n" # tạo str xuống dòng

        # gửi thông tin qua Serial
        ser.write(data_string.encode('utf-8')) # utf 8 là...?
        print("đã gửi dữ liệu")
        time.sleep(0.5) # nghỉ mỗi 0.5 giây

except serial.SerialException:
    print("Không thể kết nối với cổng Serial! Hãy kiểm tra lại cổng COM.")
except KeyboardInterrupt:
    print("\nĐã dừng chương trình.")    


