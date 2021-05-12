# Socket CAN C++  

Minimal working C++ code to read raw CAN frames using Socket CAN.  

```c++
#include "socketcan_cpp/SocketCAN.hpp"
int main(int argc, char const *argv[]) {
  SocketCAN_CPP::SocketCAN sCAN("vcan0");
  while (1) {
    sCAN.Read();
    std::cout << "ID: " << std::hex << std::uppercase << std::setw(3)
              << std::setfill('0') << sCAN.frame.can_id;

    std::cout << " Data: " << std::hex << std::uppercase;
    for (size_t i = 0; i < 8; i++) {
      std::cout << (0xff & (unsigned int)sCAN.frame.data[i]);
    }
    std::cout << std::endl;
    sCAN.Write(sCAN.frame);
    sleep(1);
  }

  return 0;
}

```
