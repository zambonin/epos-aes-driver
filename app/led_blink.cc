#include <gpio.h>

using namespace EPOS;

int main() {
  GPIO g('C', 3, GPIO::OUT);

  unsigned int i = 0;
  while (i++ < 8) {
    g.set(i % 2);
    for (volatile int t = 0; t < 0xfffff; t++);
  }

  return 0;
}
