// cl: /O2 /MD /EHsc
// Native F1600..F1D61 plus aligned 16-case table F1D64..F1DA3.
// Ghidra's 1887-byte boundary misses the final ret8 and table: extent1956.
// WB1787580 identifies AptXmlNode::objectMemberLookup and supplies purpose;
// native checked-cast FDD220, vtable call slots and node+20 establish layout.
// The interface names describe observed operations; original names unproven.
// The wrapper keeps the ledger's established address name and F1310 ABI.
// Return control flow matters: positive nested tests in the final child case
// place the shared undefined-return block after its allocation, as retail.
// All callees are existing providers, with the newly recovered F1570 callback.
// Whole native code, case targets and table bytes verify independently.
class Rva006D2A60 {
public:
  void *allocBlock(int);
  void freeBlock(void *, int);
};
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
#define POOL_ALLOC                                                             \
public:                                                                        \
  static void *operator new(unsigned n) {                                      \
    return g_pChainBlockAllocatorF4->allocBlock(n);                            \
  }                                                                            \
  static void operator delete(void *p, unsigned n) {                           \
    g_pChainBlockAllocatorF4->freeBlock(p, n);                                 \
  }
class EAStringC {
  void *data;

public:
  EAStringC(const char *);
  EAStringC() { clear(); }
  EAStringC &clear();
  bool rva006D3510(const char *) const;
  ~EAStringC();
  const char *rva00620090() const;
  unsigned rva006D3750() const;
};
class AptValue {
public:
  void SetString(const char *);
  void toString(EAStringC &) const;
};
class BfmeAptValue006DCD20 {
public:
  virtual void AddRef();
  int isXmlNode() const;
  int isString() const;
  unsigned flags;
  BfmeAptValue006DCD20 *rva006DD220();
  void setGCRootCount(unsigned);
  void rva006D95E0(int, BfmeAptValue006DCD20 *);
};
struct XmlAttribute {
  const char *key;
  const char *value;
};
class XmlNode {
public:
  virtual void slot0();
  virtual void slot1();
  virtual XmlAttribute firstAttribute();
  virtual XmlAttribute nextAttribute();
  virtual void slot4();
  virtual XmlNode *firstChildInList();
  virtual XmlNode *nextChildInList();
  virtual void slot7();
  virtual XmlNode *firstChild();
  virtual void slot9();
  virtual void slot10();
  virtual XmlNode *nextSibling();
  virtual XmlNode *previousSibling();
  virtual const char *name();
  virtual void setName(const char *);
  virtual int type();
  virtual const char *value();
  virtual void setValue(const char *);
  virtual XmlNode *parent();
  virtual XmlNode *lastChild();
};
class Rva006F1360 : public BfmeAptValue006DCD20 {
  char pad[24];

public:
  XmlNode *node;
  void *owner;
  Rva006F1360(int, void *);
  AptValue *rva006F1600(AptValue *, const EAStringC *) const;
  POOL_ALLOC
};
class Rva006D6500 : public BfmeAptValue006DCD20 {
  char rest[28];

public:
  Rva006D6500(int);
  POOL_ALLOC
};
class Rva00711380 : public BfmeAptValue006DCD20 {
  char rest[28];

public:
  Rva00711380(int, int);
  POOL_ALLOC
};
class AptArray : public BfmeAptValue006DCD20 {
  char rest[36];

public:
  AptArray();
  POOL_ALLOC
};
class AptString : public AptValue {
public:
  static AptString *Create();
};
class AptInteger {
public:
  static AptValue *Create(int);
};
class Rva006DBB60ShrNAndField {
public:
  bool get() const;
};
struct AptNativeHash {
  void Set(const EAStringC *const, AptValue *const);
};
struct R4Word {
  const char *name;
  int id;
};
const R4Word *Rva008D5DC0(const char *, unsigned);
EAStringC *Rva0070B4F0GetString(int);
extern AptValue *gpUndefinedValue;
int Rva006F5100Get();
void rva006F1530(BfmeAptValue006DCD20 *);
AptValue *rva006F1570(BfmeAptValue006DCD20 *);
// These six cache slots already belong to the verified shutdown provider.
// Keep its global symbol types; the native initializer establishes that each
// value stored there is a native-function wrapper.
class Rva008A48D0Item;
extern Rva008A48D0Item *g_rva008A48D0_0, *g_rva008A48D0_1, *g_rva008A48D0_2,
    *g_rva008A48D0_3, *g_rva008A48D0_4, *g_rva008A48D0_5;
#define xmlCache1 (*(Rva006D6500 **)&g_rva008A48D0_0)
#define xmlCache4 (*(Rva006D6500 **)&g_rva008A48D0_1)
#define xmlCache6 (*(Rva006D6500 **)&g_rva008A48D0_2)
#define xmlCache7 (*(Rva006D6500 **)&g_rva008A48D0_3)
#define xmlCache15 (*(Rva006D6500 **)&g_rva008A48D0_4)
#define xmlCache16 (*(Rva006D6500 **)&g_rva008A48D0_5)
#define CACHE(N, F)                                                            \
  case N:                                                                      \
    if (!xmlCache##N) {                                                        \
      xmlCache##N = new Rva006D6500((int)&F);                                  \
      xmlCache##N->setGCRootCount(1);                                          \
      xmlCache##N->AddRef();                                                   \
    }                                                                          \
    return (AptValue *)xmlCache##N;
AptValue *Rva006F1360::rva006F1600(AptValue *context,
                                   const EAStringC *name) const {
  const R4Word *word =
      context ? Rva008D5DC0(name->rva00620090(), name->rva006D3750()) : 0;
  Rva006F1360 *xml =
      (Rva006F1360 *)((BfmeAptValue006DCD20 *)this)->rva006DD220();
  if (word) {
    switch (word->id) {
      CACHE(1, Rva006F5100Get)
    case 2: {
      Rva00711380 *attributes = new Rva00711380(0x22, (int)xml->node);
      if (xml->node) {
        XmlAttribute attr = xml->node->firstAttribute();
        while (attr.key && attr.value) {
          AptString *s = AptString::Create();
          s->SetString(attr.value);
          EAStringC key(attr.key);
          ((AptNativeHash *)((char *)attributes + 8))->Set(&key, s);
          attr = xml->node->nextAttribute();
        }
      }
      if (attributes)
        return (AptValue *)attributes;
      return gpUndefinedValue;
    }
    case 3: {
      if (!xml->node)
        return gpUndefinedValue;
      AptArray *array = new AptArray();
      if (array) {
        XmlNode *child = xml->node->firstChildInList();
        int i = 0;
        while (child) {
          Rva006F1360 *v = new Rva006F1360(0x20, child);
          array->rva006D95E0(i, v);
          ++i;
          child = xml->node->nextChildInList();
        }
        return (AptValue *)array;
      }
      return 0;
    }
      CACHE(4, Rva006F5100Get)
    case 5: {
      if (!xml->node)
        return gpUndefinedValue;
      XmlNode *child = xml->node->firstChild();
      if (!child)
        return gpUndefinedValue;
      Rva006F1360 *v = new Rva006F1360(0x20, child);
      if (((Rva006DBB60ShrNAndField *)v)->get())
        return (AptValue *)v;
      break;
    }
      CACHE(6, rva006F1530)
      CACHE(7, Rva006F5100Get)
    case 8: {
      if (!xml->node)
        return gpUndefinedValue;
      XmlNode *child = xml->node->nextSibling();
      if (!child)
        return gpUndefinedValue;
      Rva006F1360 *v = new Rva006F1360(0x20, child);
      if (((Rva006DBB60ShrNAndField *)v)->get())
        return (AptValue *)v;
      break;
    }
    case 9: {
      if (!xml->node)
        return gpUndefinedValue;
      XmlNode *child = xml->node->previousSibling();
      if (!child)
        return gpUndefinedValue;
      Rva006F1360 *v = new Rva006F1360(0x20, child);
      if (((Rva006DBB60ShrNAndField *)v)->get())
        return (AptValue *)v;
      break;
    }
    case 10: {
      AptString *s = AptString::Create();
      s->SetString(Rva0070B4F0GetString(0x62)->rva00620090());
      if (xml->node) {
        const char *p = xml->node->name();
        if (p)
          s->SetString(p);
      }
      return s;
    }
    case 11:
      if (xml->node)
        return AptInteger::Create(xml->node->type());
      return gpUndefinedValue;
    case 12: {
      AptString *s = AptString::Create();
      s->SetString(Rva0070B4F0GetString(0x62)->rva00620090());
      if (xml->node) {
        const char *p = xml->node->value();
        if (p)
          s->SetString(p);
      }
      return s;
    }
    case 13: {
      AptValue *result = gpUndefinedValue;
      if (xml->node) {
        XmlNode *parent = xml->node->parent();
        if (parent) {
          Rva006F1360 *v = new Rva006F1360(0x20, parent);
          result = (AptValue *)v;
          if (((Rva006DBB60ShrNAndField *)v)->get())
            return (AptValue *)v;
        }
      }
      return result;
    }
    case 14: {
      if (xml->node) {
        XmlNode *child = xml->node->lastChild();
        if (child) {
          Rva006F1360 *v = new Rva006F1360(0x20, child);
          if (((Rva006DBB60ShrNAndField *)v)->get())
            return (AptValue *)v;
          break;
        }
      }
      return gpUndefinedValue;
    }
      CACHE(15, Rva006F5100Get)
      CACHE(16, rva006F1570)
    default:
      break;
    }
  }
  return 0;
}

// Native F1410..F1522 has stdcall ret12 and ignores incoming ECX.
// Keys NodeName/NodeValue select node slots14/17; returns true on every path.
bool __stdcall Rva006F1410(BfmeAptValue006DCD20 *target, const EAStringC *key,
                           AptValue *value) {
  if ((unsigned char)target->isXmlNode()) {
    Rva006F1360 *xml = (Rva006F1360 *)target->rva006DD220();
    if (key->rva006D3510("NodeName")) {
      if ((unsigned char)((BfmeAptValue006DCD20 *)value)->isString()) {
        EAStringC text;
        value->toString(text);
        if (xml->node)
          xml->node->setName(text.rva00620090());
      }
    } else if (key->rva006D3510("NodeValue")) {
      if ((unsigned char)((BfmeAptValue006DCD20 *)value)->isString()) {
        EAStringC text;
        value->toString(text);
        if (xml->node)
          xml->node->setValue(text.rva00620090());
      }
    }
  }
  return true;
}
