// cl: /MD /EHsc
// ??1Rva005E7C19@@UAE@XZ @0x005E7C19 61B
// Virtual dtor stores vtable 0x00877F14 then calls rowed
// ?rva005E7855@Rva005E7855@@QAEXXZ on this then releases m_1C via rowed
// fastcall ?ReleaseTreeHintRef00217D4C@@YIXPAUTargetRef00217D4C@@@Z.
// Holder at +0x1C has inline dtor if (ptr) Release(ptr) which inlines as the
// test+je+call and provides the __EH_prolog frame with and [ebp-4] 0 and
// or [ebp-4] -1. Same EH shape as ??1Rva005E7529 at 0x005E7529.
// Evidence: chain lane via just-landed 0x005E7855 plus callers 0x005E7D72
// 0x005E7EE8 plus prev/next same /O1 flags.
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
class Rva005E7855 { public: void rva005E7855(); };
struct Holder005E7C19 {
  ~Holder005E7C19() { if (ptr) ReleaseTreeHintRef00217D4C(ptr); }
  TargetRef00217D4C *ptr;
};
class Rva005E7C19 {
public:
  virtual ~Rva005E7C19();
private:
  char m_pad[0x1C - 4];
  Holder005E7C19 m_1C;
};
Rva005E7C19::~Rva005E7C19()
{
  ((Rva005E7855 *)this)->rva005E7855();
}

// Rva005E7D72: a class over Rva005E7C19 whose destructor is the 5-byte jmp 0x005E7D72 (rowed in
// Rva005E7D72Dtor.cpp). Its scalar deleting destructor 0x005E7F94 calls that stub; the
// destructor is only declared here, and the tag constructor (no retail
// counterpart) makes this TU emit the vtable and with it the deleting
// destructor.
struct EmitVtableTag;
class Rva005E7D72 : public Rva005E7C19
{
public:
	Rva005E7D72(EmitVtableTag *);
	virtual ~Rva005E7D72();
};

// ?<Rva005E7D72::Rva005E7D72> absent-from-retail
Rva005E7D72::Rva005E7D72(EmitVtableTag *)
{
}
