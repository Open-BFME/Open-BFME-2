// cl: /MD
// ??1Rva005E7ED7@@UAE@XZ @0x005E7ED7 22B
// MI dtor: stores secondary vtable 0x007C6F20 at this+0x24 via null-safe
// neg/sbb/and then tail-jmps to rowed ??1Rva005E7C19@@UAE@XZ which stores
// primary vtable 0x00877F14 and does the Holder release. Primary size 0x24
// places secondary at +0x24. Novtable suppresses derived primary store.
// Same shape as empty MI dtors over rowed bases. Evidence: chain lane via
// just-landed 0x005E7C19 plus caller 0x005E7EBB deleting shape plus
// prev/next same /O1 flags.
class Rva005E7C19 {
public:
  virtual ~Rva005E7C19();
private:
  char m_pad[0x20];
};
class Secondary005E7ED7 {
public:
  virtual ~Secondary005E7ED7() {}
};
class __declspec(novtable) Rva005E7ED7 : public Rva005E7C19, public Secondary005E7ED7 {
public:
  virtual ~Rva005E7ED7();
};
Rva005E7ED7::~Rva005E7ED7() {}
