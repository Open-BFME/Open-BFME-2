// cl: /O2 /MD /EHsc
// Native F1310 constructor and F1360 destructor share the 0x28-byte
// CEC CF8 vtable owner. The XML-node lookup at F1600 uses node +0x20
// and owner +0x24; WB1787270 corroborates the constructor purpose.
// Names remain address-derived: the layout and ABI are target facts.
// The D6360 base is 0x1c bytes and D6470 adds the flag word at +0x1c.
#include "../../../Libraries/Source/Apt/Rva006D2A60.h"
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class AptValue
{
public:
    virtual void AddRef();
    virtual void Release();
};
// Retail vtable 0x008EA228 starts with the rowed AptValue::AddRef (0x006DCAC0) and Release.
class BfmeAptValue006DCD20 : public AptValue
{
protected:
    unsigned int m_flags04;
public:
    virtual ~BfmeAptValue006DCD20();
};
class Rva006D6360 : public BfmeAptValue006DCD20 {
  char m_pad08[20];

public:
  Rva006D6360(int, int);
  virtual ~Rva006D6360();
};
class Rva006D6470Owner : public Rva006D6360 {
  unsigned int m_flags;

public:
  Rva006D6470Owner(int type, int size) : Rva006D6360(type, size) {
    *(unsigned char *)&m_flags = 0;
    m_flags &= 0xfffffcff;
  }
  virtual ~Rva006D6470Owner();
  static void operator delete(void *p, unsigned int size) {
    g_pChainBlockAllocatorF4->freeBlock(p, size);
  }
};
class Rva006F1360 : public Rva006D6470Owner {
  void *m_node;
  void *m_owner;

public:
  Rva006F1360(int, void *);
  virtual ~Rva006F1360();
};
Rva006F1360::Rva006F1360(int type, void *node)
    : Rva006D6470Owner(type, 8), m_node(node), m_owner(0) {}
Rva006F1360::~Rva006F1360() {
  m_node = 0;
  m_owner = 0;
}
