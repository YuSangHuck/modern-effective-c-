#include <stdio.h>

template<typename T>
void f(const T& param) {
  return;
}

int main() {
  int x = 0;
  f(x);
}