// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "../include/tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len) {
  if (len <= 0) {
    throw "len <= 0";
  }
  BitLen = len;
  MemLen = ceil(((float)len) / (sizeof(TELEM) * 8));
  // cout << BitLen << ' ' << MemLen;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; ++i) {
    pMem[i] = 0;
  }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; ++i) {
    pMem[i] = bf.pMem[i];
  }
}

TBitField::~TBitField() {
  delete[] pMem;
  MemLen = 0;
  BitLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  TELEM res = 1;
  int idBit = n % (sizeof(TELEM) * 8);
  res <<= idBit;
  return res;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0 || n >= BitLen) {
    throw "Wrong index";
  }
  pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || n >= BitLen) {
    throw "Wrong index";
  }
  pMem[GetMemIndex(n)] &= (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0 || n > GetLength()) {
    throw "Wrong index";
  }
  return (pMem[GetMemIndex(n)] & GetMemMask(n)) == 0 ? 0 : 1;
}

// битовые операции

TBitField &TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this == (&bf)) {
    return *this;
  }
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  delete[] pMem;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; ++i) {
    pMem[i] = bf.pMem[i];
  }
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (BitLen != bf.BitLen) {
    return false;
  }
  for (int i = 0; i < MemLen - 1; ++i) {
    if (pMem[i] != bf.pMem[i]) {
      return false;
    }
  }
  for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; ++i) {
    if (GetBit(i) != bf.GetBit(i)) {
      return false;
    }
  }
  return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int max_len = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
  TBitField res(max_len);

  for (int i = BitLen; i < (MemLen * sizeof(TELEM) * 8); ++i) {
    ClrBit(i);
  }

  for (int i = 0; i < MemLen; ++i) {
    res.pMem[i] = pMem[i];
  }

  for (int i = 0; i < bf.MemLen; ++i) {
    res.pMem[i] |= bf.pMem[i];
  }

  return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int max_len = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
  TBitField res(max_len);

  for (int i = BitLen; i < (MemLen * sizeof(TELEM) * 8); ++i) {
    SetBit(i);
  }

  for (int i = 0; i < MemLen; ++i) {
    res.pMem[i] = pMem[i];
  }

  for (int i = 0; i < bf.MemLen; ++i) {
    res.pMem[i] &= bf.pMem[i];
  }

  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField res(*this);

  for (int i = 0; i < MemLen - 1; ++i) {
    res.pMem[i] = ~res.pMem[i];
  }

  for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; ++i) {
    if (res.GetBit(i) == 1) {
      res.ClrBit(i);
    } else {
      res.SetBit(i);
    }
  }

  return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  char tmp;
  int i = 0;
  while (1) {
    istr >> tmp;
    if (tmp == '1') {
      bf.SetBit(i);
    } else if (tmp == '0') {
      bf.ClrBit(i);
    } else {
      break;
    }
    ++i;
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.GetLength(); ++i) {
    ostr << bf.GetBit(i);
  }
  return ostr;
}
