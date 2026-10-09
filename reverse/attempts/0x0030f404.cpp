// ??0Rva0030F42E@@QAE@H@Z
// partial score=1.0 date=2026-10-09
// Exact42B code only; NOT ready to land. Native C09834 owns dtor30F443,
// setter30F3BF and unprovided virtual30F2CB; current dtor TU emits only
// its slot0 table and the setter remains a different neutral class/QAE.
// Reconcile all providers and consumers before a constructor row.
// The non-polymorphic16B base is a source/ABI inference supported by
// target call-before-vtable order. Constructor arg stays opaque32-bit.
// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ??0Rva0030F42E@@QAE@H@Z retail 0x0030F404 42 bytes.
// Ctor of Rva0030F42E whose dtor 0x0030F42E frees +0x04 and uses vtable
// 0x00809834. Calls rowed Rva00330757Member 0x00330757 for +0x04 member
// sized 0x10 to place int arg at +0x14 float 0 at +0x18 byte 0 at +0x1C.
// Current body is exact 42B 13 insns with correct push prolog SSE xorps-movss
// and ret 4. Remaining diff is vtable scheduling only: retail is lea call
// mov-eax xorps mov-14 vtable movss byte; this body is lea vtable call
// mov-eax xorps mov-14 movss byte. Base-inlined variant forces vtable last
// but costs push-edi and 46B. Novtable explicit store may place vtable
// middle.

class Rva00330757Member
{
	char m_pad[0x10];
public:
	Rva00330757Member();
};

class Rva0030F42E:public Rva00330757Member
{
public:
 virtual ~Rva0030F42E();
 virtual void rva0030F3BF(float);
 int m_14;float m_18;bool m_1C;
 Rva0030F42E(int arg);
};
Rva0030F42E::Rva0030F42E(int arg):Rva00330757Member(),m_14(arg),m_18(0),m_1C(false){}
