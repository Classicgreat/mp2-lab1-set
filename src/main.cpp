#include "../include/tbitfield.h"
#include <iostream>

int main() {
  TBitField bf(10);
  cout << bf << endl;
  bf.SetBit(9);
  cout << bf << endl;
  return 0;
}
