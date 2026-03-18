# ESP32 Air Mouse

**Author:** Bu_Thy  

A wireless mouse built using ESP32 and MPU6050.  
The system uses motion sensing and Bluetooth Low Energy (BLE) to control cursor movement and perform mouse actions.

---

## 📦 Components Required

- ESP32
- MPU6050 (Gyroscope + Accelerometer)
- Push buttons (for click and scroll)
- Jumper wires
- Battery or USB cable

---

## 🔌 Circuit Connections

### MPU6050 to ESP32 (I2C)

| MPU6050 Pin | ESP32 Pin |
|------------|----------|
| VCC        | 3.3V     |
| GND        | GND      |
| SDA        | GPIO 21  |
| SCL        | GPIO 22  |

---

### Buttons (Click / Scroll)

| Function      | ESP32 Pin |
|--------------|----------|
| Left Click   | GPIO 18  |
| Right Click  | GPIO 19  |
| Scroll Up    | GPIO 23  |
| Scroll Down  | GPIO 5   |

👉 Each button is connected between the GPIO pin and GND.

---

## Circuit Diagram

![Circuit Diagram](circuit_diagram/circuit_diagram.png)

---

## Project Images

![Project Image 1](images/photo1.png)  
![Project Image 2](images/photo2.png)  
![Project Image 3](images/photo3.png)

---

## 🚀 How to Upload Code

Using **VS Code + Arduino Extension**:

1. Install Visual Studio Code
2. Install Arduino Extension
3. Install ESP32 board (via Board Manager)
4. Install required libraries:
   - Wire
   - BLE Mouse
5. Connect ESP32 via USB
6. Select board: **ESP32 Dev Module**
7. Select correct COM port
8. Upload the code

---

## Why I VS Code Instead of Arduino IDE?

VS Code was used because the required **ESP32 BLE Mouse** library is not directly available through the Arduino IDE Library Manager.

In Arduino IDE, the library must be installed manually, which can lead to version or setup issues.

Using VS Code with the Arduino extension provides better control over library installation and project management, making the development process more reliable.

## ⚙️ How It Works

- MPU6050 detects motion (tilt and acceleration)
- ESP32 reads sensor data via I2C
- Motion is converted into cursor movement:
  - Tilt left → cursor moves left  
  - Tilt right → cursor moves right  
  - Tilt forward → cursor moves up  
  - Tilt backward → cursor moves down  

- ESP32 sends data using **Bluetooth HID (BLE)**  
- Device behaves like a wireless mouse
  
---

##  Future Improvements

- Add gesture recognition
- Improve motion smoothing
- Add sensitivity control
- Rechargeable battery integration
