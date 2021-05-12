#ifndef __SOCKETCAN_CPP_H__
#define __SOCKETCAN_CPP_H__
#include <cstring>
#include <iomanip>
#include <iostream>
#include <linux/can.h>
#include <net/if.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

namespace SocketCAN_CPP {
class SocketCAN {
private:
  int can_socket_;
  struct sockaddr_can addr_;
  struct ifreq ifr_;

public:
  SocketCAN(const std::string &device_name);
  ~SocketCAN();
  struct can_frame frame;
  struct can_frame Read();
  int Write(const struct can_frame &frame);
};

} // namespace SocketCAN_CPP
#endif // __SOCKETCAN_CPP_H__