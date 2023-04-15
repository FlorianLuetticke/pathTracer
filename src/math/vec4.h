#include <array>

class TVec4 {

  std::array<double, 4> _data;

private:
  TVec4() { _data.fill(0.); }
  TVec4(const std::array<double, 4> &l) : _data(l) {}
  TVec4(const std::array<double, 3> &l) {
    _data[0] = l[0];
    _data[1] = l[1];
    _data[2] = l[2];
    _data[3] = 0;
  }
};