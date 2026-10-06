// cl: /MD
// ??1Rva003ABA36@@UAE@XZ @0x003ABA36 22B
// Dtor restoring second vtable 0x00BBB554 at +0x18 via null-guarded
// neg/lea/sbb/and idiom then tail-jmp to rowed base ??1Rva003AF50D@@UAE@XZ
// at 0x003A983C. Evidence: retail mov/neg/lea/sbb/and plus BBB554 store
// plus jmp, unlocks 0x003AE8D5, prev is landed 0x003AB9FF.
// Precedent: ParticleModuleInfoDtor.cpp Rva003AF50D +0x14 store plus tail-jmp.
extern "C" const void *const vtbl_00BBB554[];  // folded, 23 classes; via ??_7BfmeBaseVUQ@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBB554=??_7BfmeBaseVUQ@@6B@")

class Rva003AF50D {
public: virtual ~Rva003AF50D();
private: char m_pad[0x18 - 4];
};

class __declspec(novtable) Rva003ABA36 : public Rva003AF50D {
public: virtual ~Rva003ABA36();
private: void *m_v18;
};

Rva003ABA36::~Rva003ABA36()
{
	unsigned char *b18 = this ? (unsigned char *)this + 0x18 : 0;
	*(volatile unsigned int *)b18 = ((unsigned int)vtbl_00BBB554);
}
