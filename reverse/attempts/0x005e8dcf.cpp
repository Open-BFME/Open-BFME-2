// ??0Rva005E8DCF@@QAE@PAXPAURva005E8DCFIn@@@Z
// partial score=0.985 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /Ob2 /DNDEBUG /EHsc /MD
#include "ascii_string.h"
class Image;
class Rva005E1158 {
public:
 void rva005E1158(const Image*);
 virtual ~Rva005E1158();
private:
 int m_04; void *m_08;
};
class Rva005E12D1 {
public:
 Rva005E12D1(void*, const AsciiString&, void*);
 virtual ~Rva005E12D1();
private:
 char m_pad[0x10];
};
struct Ui149Base {
 Ui149Base(): m_04(0) {}
 virtual ~Ui149Base() {}
 int m_04;
};
class Rva005E16B9 {
public: const Image *rva005E16B9();
};
class Rva005E8DB5 {
public: void *rva005E8DB5();
};
struct Rva005E8DCFIn { void* m_00; void* m_04; };
struct Ui149Fields {
 Ui149Fields(Rva005E8DCFIn *p): m_1C(p->m_00), m_20(p->m_04) {}
 void *m_1C, *m_20;
};
class Rva005E8DCF : public Ui149Base, public Rva005E12D1, public Ui149Fields {
public:
 Rva005E8DCF(void*, Rva005E8DCFIn*);
 virtual ~Rva005E8DCF();
};
Rva005E8DCF::Rva005E8DCF(void* a, Rva005E8DCFIn* p)
 : Ui149Base(), Rva005E12D1(a, AsciiString("button"), p->m_00), Ui149Fields(p)
{
 const Image *image=((Rva005E16B9*)((Rva005E8DB5*)this)->rva005E8DB5())->rva005E16B9();
 ((Rva005E1158*)(Rva005E12D1*)this)->rva005E1158(image);
}
