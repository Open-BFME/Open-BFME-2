// cl: /O2 /DNDEBUG /MD /EHsc
// Native ED060..ED145 constructor and ED150 destructor share CECB90.
// Target accesses establish id+4, pointers+C/10, flag14, word18, bits1C,
// word20, display-list24, word28 and ownership2C. Full size is0x30.
// A0x18-byte base is a structural inference consistent with its CEC9CC
// destructor; the field offsets and constructor stores are target facts.
// WB1780DE0 corroborates construction order. Display-list and native-hash
// types now use their existing verified providers instead of opaque names.
// A named flag temporary retains native order across the zero stores.
// The constructor assigns the registry value's prototype to hash__proto__,
// retaining the measured AddRef/Release order. No original owner name claimed.
class Rva006DB160 {
public:
  void *allocBlock(int);
};
class Rva006DB270 {
public:
  void freeBlock(void *, int);
};
extern Rva006DB270 *g_pChainBlockAllocator;
class AptValue {
public:
  virtual void AddRef();
  virtual void Release();
};
class AptNativeHash {
public:
  int count;
  void *items;
  AptValue *proto, *prototype;
  unsigned events;
  AptNativeHash(int);
  ~AptNativeHash();
  static void *operator new(unsigned n) {
    return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(n);
  }
  static void operator delete(void *p, unsigned n) {
    g_pChainBlockAllocator->freeBlock(p, n);
  }
  void Set__Proto__(AptValue *value) {
    if (value)
      value->AddRef();
    if (proto)
      proto->Release();
    proto = value;
  }
};
class AptDisplayList {
  void *list;

public:
  AptDisplayList();
  ~AptDisplayList();
};
class Rva006ED150Base {
public:
  Rva006ED150Base() {
    m_flag14 = 0;
    m_id = -1;
    m_0C = 0;
    m_10 = 0;
  }
  virtual ~Rva006ED150Base();

protected:
  int m_id, m_unknown08;
  void *m_0C;
  AptNativeHash *m_10;
  unsigned char m_flag14;
};
// ??1Rva006ED150Base@@UAE@XZ present-unmatched
inline Rva006ED150Base::~Rva006ED150Base() {
  AptNativeHash *p = m_10;
  if (p) {
    p->~AptNativeHash();
    g_pChainBlockAllocator->freeBlock(p, 0x14);
  }
}
class Rva006ED150 : public Rva006ED150Base {
public:
  Rva006ED150();
  virtual ~Rva006ED150();

private:
  int m_18;
  unsigned m_bits;
  int m_20;
  AptDisplayList m_24;
  int m_28, m_2C;
};
Rva006ED150::~Rva006ED150() {
  if (m_2C == 1)
    g_pChainBlockAllocator->freeBlock(m_0C, 0x40);
}
class EAStringC {
  void *data;
};
extern EAStringC g_00E18650;
EAStringC *Rva0070B4F0GetString(int);
class BfmeN1034 {
public:
  virtual void slot0();
  virtual void slot1();
  virtual void slot2();
  virtual AptNativeHash *slot3();
};
class Rva0070A5C0 {
public:
  BfmeN1034 *rva0070A5C0(int);
};
Rva006ED150::Rva006ED150() {
  unsigned bits = (m_bits & 0xf2000000) | 0x02000000;
  m_20 = 0;
  m_28 = 0;
  m_bits = bits;
  m_10 = new AptNativeHash(8);
  m_18 = -1;
  m_2C = 0;
  EAStringC *key = Rva0070B4F0GetString(0x5e);
  BfmeN1034 *object =
      ((Rva0070A5C0 *)*(void **)&g_00E18650)->rva0070A5C0((int)key);
  m_10->Set__Proto__(object->slot3()->prototype);
}
