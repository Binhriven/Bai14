🧠 Mục tiêu

Viết chương trình điều khiển LED trên STM32F103C8T6 bằng cách dùng hàm Delay (CPU bận liên tục trong thời gian trễ).
Sau đó dùng đồng hồ đo để so sánh dòng tiêu thụ với chương trình sử dụng chế độ Sleep (WFI).

⚙️ Cấu hình phần cứng
Thành phần	Chân STM32	Ghi chú
LED	PC13	LED tích hợp sẵn trên board Blue Pill
Nguồn	3.3V	Cấp nguồn cho chip
GND	GND	Chung mạch
Thiết bị đo	Ampe kế	Đặt nối tiếp với đường cấp 3.3V để đo dòng tiêu thụ

⚠️ Lưu ý: Trên board Blue Pill, LED nối ngược logic →
GPIO_SetBits(GPIOC, GPIO_Pin_13) → LED tắt,
GPIO_ResetBits(GPIOC, GPIO_Pin_13) → LED sáng.
