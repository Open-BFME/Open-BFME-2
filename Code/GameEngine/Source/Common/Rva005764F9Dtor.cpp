// cl: /O1 /arch:SSE /G7 /MD /EHsc
// ??1Rva005764F9@@UAE@XZ @0x005764F9 87B evidence: vtable 0x00C6E78C; calls rowed get 0x00574AA5 and rowed 0x005CC20D 0x005CD5FA and base dtor 0x005D0D85; caller deleting dtor 0x005767A7
class Rva00574AA5AddDwordField
{
public:
  int get() const;
};
class Rva005CC20D
{
public:
  void rva005CC20D(unsigned char value);
};
class Rva005CD5FA
{
public:
  void rva005CD5FA(unsigned char value);
};
#include "../../Include/Common/Rva00328A83PtrChaseField.h"
class Rva00574AACAddDwordField
{
public:
  int get() const;
};
class Rva005D0D85
{
public:
  Rva005D0D85(int a, int b, int c);
  virtual ~Rva005D0D85();
};
struct Rva005764F9Mid
{
  char m_pad[4];
  Rva00574AA5AddDwordField *m_04;
};
struct Rva005764F9Holder
{
  char m_pad[16];
  Rva005764F9Mid *m_10;
  char m_pad2[28];
  Rva005CD5FA m_30;
};
// The constructor (0x0057647E) reads its base arguments off the holder's
// field once and evaluates the 0x00328A83 read before the 0x00574AAC one, as
// two inline argument-forwarding layers do.
class Rva005764F9Args : public Rva005D0D85
{
public:
  __forceinline Rva005764F9Args(int chase, Rva00574AA5AddDwordField *field, int c)
    : Rva005D0D85(chase, ((Rva00574AACAddDwordField *)field)->get(), c) {}
};
class Rva005764F9Base : public Rva005764F9Args
{
public:
  __forceinline Rva005764F9Base(Rva00574AA5AddDwordField *field, int c)
    : Rva005764F9Args(((Rva00328A83PtrChaseField *)field)->get(), field, c) {}
};
class Rva005764F9 : public Rva005764F9Base
{
public:
  Rva005764F9(Rva005764F9Holder *holder, int c);
  virtual ~Rva005764F9();
  char m_pad[4];
  Rva005764F9Holder *m_08;
};
Rva005764F9::~Rva005764F9()
{
  ((Rva005CC20D *)m_08->m_10->m_04->get())->rva005CC20D(1);
  m_08->m_30.rva005CD5FA(1);
}
// ??0Rva005764F9@@QAE@PAURva005764F9Holder@@H@Z @0x0057647E 123B (RET 8):
// base 0x005D0D2D with the holder field's two values and the extra word, then
// the mirror of the destructor: 0x005CD5FA and 0x005CC20D told 0.
Rva005764F9::Rva005764F9(Rva005764F9Holder *holder, int c)
  : Rva005764F9Base(holder->m_10->m_04, c)
{
  m_08 = holder;
  m_08->m_30.rva005CD5FA(0);
  ((Rva005CC20D *)m_08->m_10->m_04->get())->rva005CC20D(0);
}
