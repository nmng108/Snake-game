# Snake Game

## Introduction
Một project làm game **Snake** đơn giản

* Một số hình ảnh, assets, sound effects có nguồn gốc từ Internet

## Technologies
Project sử dụng IDE và các thư viện sau:

* Code::blocks 20.03 MinGW
* SDL2 image devel 2.0.5 MinGW
* SDL2 ttf devel 2.0.15 MinGW
* SDL2 devel 2.0.14 MinGW
* SDL2 mixer 2.0.4 MinGW

## Set up and lauch this game
- Trên hệ điều hành Windows, truy cập Control Panel và theo đường dẫn sau: Control Panel\System and Security\System
- Mở Advanced System Setting , chọn Environment Variable, trong ô System Variable tìm và ấn PATH rồi Edit...
- Bấm New, chọn đường dẫn là thư mục SDL2 trong thư mục chứa project này
- Tải MinGW(có sẵn nếu đã tải cùng IDE code::blocks), sau đó thêm đường dẫn tới folder bin bằng cách tương tự
 như trên và ấn Ok để hoàn tất
- Mở Snake Game.exe để vào game

### Luật chơi
* Điều khiển con rắn bằng bộ 4 phím ASDW hoặc 4 phím mũi tên để ăn quả, khi đạt được 1 số lượng quả nhất định sẽ
 chuyển màn(level) mới. Hiện tại có tất cả 5 level

* Khi đầu con rắn đâm vào tường hoặc đuôi sẽ chết, quay về chơi từ đầu

* Mỗi ăn đủ 4 quả sẽ xuất hiện 1 phần thưởng cộng thêm điểm, tồn tại trong 3s. Tất cả 
 quà và phần thưởng xuất hiện ngẫu nhiên

### Tính năng:

#### 1. Menu:
* Chọn Start để vào game
* Chọn High Score để mở bảng điểm 
* Chọn Quit để thoát

#### 2. Bảng điểm:
* Hiển thị 5 mức điểm cao nhất.
* Ấn reset để thiết lập lại bảng xếp hạng
* Ấn back để quay về
#### 3. Trong game:
* Người chơi lần lượt vượt qua từng vòng, khi đang chơi có thể ấn ESC để tạm dừng game
* Khi tạm dừng có 2 lựa chọn: Resume để tiếp tục, Replay để chơi lại từ level 1
* Số điểm cuối cùng ghi nhận sau khi thua hoặc thắng sẽ được so sánh với những số điểm trước đó. 
 Nếu nằm trong 5 điểm cao nhất sẽ được lưu lại và hiện trên bảng xếp hạng.