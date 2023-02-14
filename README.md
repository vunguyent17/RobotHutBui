# Mô phỏng Robot Hút Bụi (Robot Vacuum Cleaner Simulator)

<img src="https://github.com/vunguyent17/RobotHutBui/blob/main/Screenshot/Screenshot%20RobotHutBui2.png" width="300" alt="Chương trình" />

## Giới thiệu / Introduction

Chương trình này mô phỏng các chế độ làm việc của robot hút bụi, mục tiêu đi hết toàn bộ các khu vực trống trong phòng với sơ đồ căn phòng cho trước. Chương trình chạy và hiển thị trên màn hình console

This program simulates how a Robot Vacuum Cleaner works, and find a method so that robot can avoid obstacles and clean every empty spaces and in a room with a given map. The program runs on Windows console

### Chức năng của ứng dụng / Functionality:
- Nhập bản đồ căn phòng cho robot bằng file txt, hiển thị bản đồ và trạng thái làm việc lên console
-	Chương trình có các chế độ hút bụi: Manual, Auto
  - Chế độ chạy bằng tay (Manual): có 2 cách di chuyển
    - Live control: Người dùng nhập lệnh và robot di chuyển
    - Setup control: Người dùng nhập hướng đi và số bước cho robot di chuyển
  - Chế độ chạy tự động: Robot sẽ tự động quét hết căn phòng.
- Thông bao pin yếu / tự động ngừng khi hết pin
 <br/>

- Input room map using text file. Display map and robot status on console
- Robot has 2 modes when working: Manual, Auto
  - Manual mode: there are two ways to control robot manually:
    - Live control: Robot moves by each command from user's input
    - Setup control: User types direction and number of steps to move robot
  - Auto mode: Robot will attempt to clean every empty space in the room using data from the map.
- Notify when battery low / stop when running out of battery


### Công nghệ sử dụng / Tech stack:
- C++


### Demo
Tải file demo.zip xuống, giải nén và chạy file RobotHutBui.exe. Chỉnh sửa sơ đồ căn phòng bằng cách chỉnh sửa file input.txt (1 là vật cản trong phòng, 3 là ô trống, 4 là tường)

Download demo.zip, extract it and run RobotHutBui.exe. Modify map of the room using input.txt (1 - obstacle space, 3 - empty space, 4 - wall)


## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

## License

[MIT](https://choosealicense.com/licenses/mit/)
