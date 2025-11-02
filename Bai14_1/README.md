🧠 Bài: Sử dụng Event Group trong FreeRTOS điều khiển LED (STM32F103)
📘 Mục tiêu

Chương trình minh họa cách sử dụng Event Group trong FreeRTOS để đồng bộ hóa hoạt động giữa nhiều task.
Ba task điều khiển 3 LED khác nhau trên GPIOA, với điều kiện kích hoạt dựa vào các bit sự kiện (event bits).

⚙️ Cấu trúc chương trình
Tên Task	Mô tả	LED điều khiển	Bit sự kiện
TaskMain	Gửi tín hiệu (set bit) kích hoạt các task khác	—	BIT_TASK1, BIT_TASK2
Task1	Chờ bit BIT_TASK1 → bật/tắt LED1	PA0	BIT_TASK1
Task2	Chờ bit BIT_TASK2 → bật/tắt LED2	PA1	BIT_TASK2
Task3	Chờ đồng thời hai bit BIT_TASK1 và BIT_TASK2 → bật LED3	PA4	`BIT_TASK1
🧩 Hoạt động chương trình

TaskMain luân phiên gửi sự kiện:

Set BIT_TASK1 → Task1 hoạt động (LED1 sáng 0.5s)

Sau 2s → Set BIT_TASK2 → Task2 hoạt động (LED2 sáng 0.5s)

Sau 2s → Set cả hai bit BIT_TASK1 | BIT_TASK2 → Task3 hoạt động (LED3 sáng 1s)

Chu kỳ lặp lại liên tục.

Task1 và Task2:

Mỗi task chỉ thực thi khi bit tương ứng được set.

Sử dụng xEventGroupWaitBits() với pdTRUE để xóa bit sau khi xử lý, tránh lặp vô hạn.

Task3:

Chỉ hoạt động khi cả hai bit đều được set.

Dùng pdTRUE ở cả hai tham số clearOnExit và waitForAllBits để đảm bảo chờ đủ 2 bit rồi xóa sau khi xử lý.

🧠 Giải thích Event Group

Event Group là một nhóm các cờ sự kiện (bits) được chia sẻ giữa các task, dùng để:

Đồng bộ hóa nhiều task cùng lúc.

Thay thế cho Semaphore hoặc Queue trong một số trường hợp đơn giản.

Ví dụ:

xEventGroupWaitBits(xEventGroup, BIT_TASK1, pdTRUE, pdFALSE, portMAX_DELAY);


→ Task này sẽ chờ bit 0 được set, sau đó xóa bit rồi chạy tiếp.

🔌 Kết nối phần cứng
LED	Chân STM32	Mô tả
LED1	PA0	Điều khiển bởi Task1
LED2	PA1	Điều khiển bởi Task2
LED3	PA4	Điều khiển bởi Task3
