// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00214ADC@@QAE@XZ retail 0x00214ADC 8 bytes.
// Tail-forwards the vector<AsciiString> member at +8 to its rowed dtor at
// 0x0002CC70 (add ecx,8; jmp). Empty dtor over a single STL member under a
// novtable holder, so no vptr store remains; 5 call/jmp sites in unclaimed
// 28B/25B bodies plus 2 EH unwind thunks. Neighbours Rva002147D1Get and
// Rva00214D59Pack share /O1.
#include <vector>

#include "ascii_string.h"

class __declspec(novtable) Rva00214ADC
{
public:
	~Rva00214ADC();

private:
	char m_pad00[8];
	_STL::vector<AsciiString> m_vec08;
};

Rva00214ADC::~Rva00214ADC()
{
}
