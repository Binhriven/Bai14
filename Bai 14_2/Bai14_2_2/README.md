🌙 Bài tập 2 – Nháy LED và đưa STM32 vào chế độ Sleep (WFI)
🧠 Mục tiêu

Viết chương trình đưa STM32F103C8T6 vào chế độ tiết kiệm năng lượng (Sleep) và đánh thức bằng nút nhấn PA0.
Sau đó đo dòng tiêu thụ để so sánh với chương trình dùng Delay (CPU hoạt động liên tục).

⚙️ Cấu hình phần cứng
Thành phần	Chân STM32	Mô tả
LED	PC13	LED tích hợp trên board Blue Pill
Nút nhấn (Wakeup)	PA0	Kéo lên (pull-up), nhấn tạo mức thấp
Nguồn	3.3V	Cấp nguồn cho board
GND	GND	Chung mạch
Dụng cụ đo	Ampe kế	Đặt nối tiếp với đường 3.3V để đo dòng tiêu thụ

⚠️ Trên Blue Pill, LED nối ngược:
GPIO_SetBits(GPIOC, GPIO_Pin_13) → LED tắt
GPIO_ResetBits(GPIOC, GPIO_Pin_13) → LED sáng

🔍 Giải thích hoạt động
1. Nháy LED cảnh báo

LED PC13 nháy 5 lần (mỗi lần 300ms) để báo hiệu trước khi MCU đi vào trạng thái ngủ.

2. Cấu hình GPIO và ngắt

Tắt clock cho GPIOC sau khi LED tắt → tiết kiệm năng lượng.

PA0 được cấu hình làm nguồn ngắt ngoài (EXTI0), kích hoạt theo cạnh xuống (Falling Edge).

3. Chế độ Sleep

__WFI() (Wait For Interrupt): CPU dừng hoạt động, chờ đến khi có ngắt.

Khi nhấn nút PA0 → EXTI0 kích hoạt → CPU tỉnh dậy.

Sau khi thức dậy, chương trình tiếp tục vòng while(1).

⚡ So sánh dòng tiêu thụ
Chế độ	Hoạt động của CPU	Dòng tiêu thụ trung bình	Ghi chú
Delay	CPU chạy liên tục	~10–20 mA	LED nháy liên tục
Sleep (WFI)	CPU tạm dừng, chỉ ngoại vi hoạt động	~1–2 mA	CPU chỉ tỉnh khi có ngắt

Kết quả thực tế phụ thuộc vào mạch, điện trở LED và tần số hệ thống.
Khi Sleep, bạn sẽ thấy dòng giảm rõ rệt (trên đồng hồ đo dòng).
