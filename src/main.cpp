#include "../include/tbitfield.h"
#include <iostream>

int main() {
  const int size = 4;
  TBitField bf1(size), bf2(size), expBf(size);
  // bf1 = 0011
  bf1.SetBit(2);
  bf1.SetBit(3);
  // bf2 = 0101
  bf2.SetBit(1);
  bf2.SetBit(3);

  // expBf = 0111
  expBf.SetBit(1);
  expBf.SetBit(2);
  expBf.SetBit(3);
  TBitField bf3 = bf1 | bf2;
  cout << bf1 << endl << bf2 << endl << expBf << endl << bf3;
  return 0;
}
