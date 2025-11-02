🧩 Bài tập 3 – Chế độ Standby & RTC Wakeup trên STM32F103
🎯 Mục tiêu

Cấu hình vi điều khiển STM32F103 vào chế độ tiết kiệm năng lượng sâu nhất (Standby Mode).

Sử dụng RTC (Real-Time Clock) để đánh thức MCU sau 5 giây.

Gửi chuỗi ký tự qua UART trước khi ngủ để xác nhận hoạt động.

⚙️ 1. Chức năng chương trình

MCU khởi động và cấu hình UART1 để truyền dữ liệu.

Cấu hình RTC dùng thạch anh LSE (32.768 kHz) làm nguồn clock.

Đặt báo thức RTC (RTC Alarm) để đánh thức MCU sau 5 giây.

Gửi chuỗi "Wake up and send data...\r\n" qua UART1.

Sau khi gửi xong, MCU vào chế độ Standby (toàn bộ hệ thống tắt, chỉ RTC còn hoạt động).

Khi hết thời gian 5 giây, RTC Alarm kích hoạt MCU khởi động lại từ đầu.

🔌 2. Kết nối phần cứng
Thành phần	Chân STM32	Ghi chú
UART1 TX	PA9	Truyền dữ liệu sang máy tính qua USB-UART
UART1 RX	PA10	(Không bắt buộc)
Thạch anh LSE	OSC32_IN / OSC32_OUT	32.768 kHz, dùng cho RTC
Nguồn	3.3V	MCU hoạt động và đo dòng tiêu thụ
🧠 3. Giải thích từng phần
🔹 UART1_Init()

Cấu hình USART1 tốc độ 9600 baud.

PA9 làm TX, PA10 làm RX.

Dùng để gửi thông báo trước khi MCU vào Standby.

🔹 RTC_Config()

Cho phép truy cập vùng Backup domain (PWR, BKP).

Bật LSE làm nguồn RTC.

Chia tần số về 1 Hz → đếm giây.

Đặt Alarm sau 5 giây kể từ thời điểm hiện tại.

Cho phép ngắt RTC để đánh thức MCU.

🔹 Enter_Standby_Mode()

Xóa cờ Wake-up (PWR_FLAG_WU).

Gọi PWR_EnterSTANDBYMode() để MCU ngắt toàn bộ hệ thống (RAM mất, chỉ RTC còn).

⏱ 4. Chu trình hoạt động
Thời điểm	Trạng thái MCU	Ghi chú
0s	Chạy, gửi UART	"Wake up and send data..."
1–5s	Standby	Dòng tiêu thụ vài µA
5s	RTC Alarm kích hoạt	MCU reset lại từ đầu
6s	Gửi UART lần nữa	Lặp lại chu kỳ
