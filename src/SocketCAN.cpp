#include "socketcan_cpp/SocketCAN.hpp"
namespace SocketCAN_CPP {
SocketCAN::SocketCAN(const std::string &device_name) {
  int rc = 0;
  can_socket_ = socket(PF_CAN, SOCK_RAW, CAN_RAW);

  strcpy(ifr_.ifr_name, device_name.c_str());
  rc = ioctl(can_socket_, SIOCGIFINDEX, &ifr_);
  if (rc == -1) {
    std::cerr << "[SocketCAN_CPP] Error ioctl! wrong CAN device name"
              << std::endl;
    return;
  }

  addr_.can_family = AF_CAN;
  addr_.can_ifindex = ifr_.ifr_ifindex;

  rc = bind(can_socket_, (struct sockaddr *)&addr_, sizeof(addr_));
  if (rc == -1) {
    std::cerr << "[SocketCAN_CPP] Error Couldn't bind!" << std::endl;
    return;
  }
}

SocketCAN::~SocketCAN() { close(can_socket_); }

struct can_frame SocketCAN::Read() {
  int nbytes = read(can_socket_, &frame, sizeof(struct can_frame));
  if (nbytes < 0) {
    std::cerr << "[SocketCAN_CPP] Couldn't Read from can" << std::endl;
  }
  return frame;
}

int SocketCAN::Write(const struct can_frame &frame) {
  int n_bytes = write(can_socket_, &frame, sizeof(struct can_frame));
  return n_bytes;
}
} // namespace SocketCAN_CPP