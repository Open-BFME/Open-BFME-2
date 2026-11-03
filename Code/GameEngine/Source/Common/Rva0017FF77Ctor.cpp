// cl: /EHsc /MD
//
// ??0Rva0017FF77@@QAE@PBDHH@Z @0x0017FF77 (77B):
// Ctor with a20-byte intermediate base; name at18 and words14/1C/20.
// Native ctor17FF77 calls GenBase61ED40 and constructs the four-byte name at18.
// Its exact EH graph calls intermediate-base destructor135E35 at this+0.
// Existing intermediate ctor135E23 and scalar135F19 (BD28F0 slot9) corroborate
// that base; derived BD4F50 and loader18012A establish the catalog relationship.
// This remains a limited ABI view; no original application class name is claimed.
extern "C" char GenBase009EB7D0_vtbl;
class __declspec(novtable) GenBase009EB7D0
{
public:
	__declspec(noinline) GenBase009EB7D0();
	virtual void handle();
private:
	unsigned int m_flags;
	unsigned int m_zero08;
	unsigned int m_zero0c;
	unsigned int m_zero10;
};
// The native constructor unwind calls the existing virtual base destructor
// at 0x00135E35 with this unchanged. Its own constructor 0x00135E23 calls
// GenBase009EB7D0 and installs BD28F0; the derived BD4F50 table retains its
// inherited slots. Keep that intermediate constructor visible so its vptr
// store is superseded by the most-derived constructor, as in retail.
class __declspec(novtable) Rva00135E35 : public GenBase009EB7D0
{
public:
	// The existing135E23 provider owns the out-of-line constructor. Inline
    // this empty intermediate step only; do not emit a novtable copy of it.
    __declspec(dllimport) __forceinline Rva00135E35() {}
	virtual ~Rva00135E35();
};
#include "../../../Libraries/Source/WWVegas/WWLib/StringClassData.h"
class Rva0017FF77 : public Rva00135E35
{
public:
	Rva0017FF77(const char *name, int a, int b);
private:
	int m_14;
	StringClass m_str18;
	int m_1c;
	int m_20;
};

Rva0017FF77::Rva0017FF77(const char *name, int a, int b) : m_14(0), m_str18(name, false), m_1c(a), m_20(b)
{
}

typedef char Rva0017FF77SizeCheck[sizeof(Rva0017FF77) == 0x24 ? 1 : -1];
