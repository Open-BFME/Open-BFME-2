// cl: /O2 /MD /EHsc
// Native F1310 constructor and F1360 destructor share the 0x28-byte
// CEC CF8 vtable owner. The XML-node lookup at F1600 uses node +0x20
// and owner +0x24; WB1787270 corroborates the constructor purpose.
// Names remain address-derived: the layout and ABI are target facts.
// The D6360 base is 0x1c bytes and D6470 adds the flag word at +0x1c.
class Rva006D2A60 {
public:
  void freeBlock(void *, int);
};
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class Rva006D6360 {
  char m_pad04[24];

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
