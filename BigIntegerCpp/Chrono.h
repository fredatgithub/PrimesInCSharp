#pragma once
#include <chrono>
#include <iostream>

class Chrono {
public:
  Chrono(const std::string& name)
    : m_name(name), m_start(std::chrono::steady_clock::now()) {
  }

  ~Chrono() {
    auto stop = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - m_start);
    std::cout << m_name << " : " << ms.count() << " ms\n";
  }

private:
  std::string m_name;
  std::chrono::steady_clock::time_point m_start;
};


