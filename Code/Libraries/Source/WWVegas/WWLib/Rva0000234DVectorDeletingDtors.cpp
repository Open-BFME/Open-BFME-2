// cl: /O1 /DNDEBUG /MD /EHsc
//
// Two vector deleting destructors (??_E) of non-polymorphic elements that sit
// between the VectorClass<int> scalar deleting destructor (0x0000232B) and
// its destructor (0x000023E3). Neither is referenced in retail.
//
//   ??_E        element dtor  size
//   0x0000234D  0x00001DAC    0x24
//   0x00002398  0x00001E13    0x08
//
// Evidence (retail bytes): each tests flag bit 1 and runs the eh vector
// destructor iterator (0x00629110) over [this-4] elements of the given size
// with the given destructor, freeing through operator delete[] (0x0002FD80);
// the scalar path calls the same destructor out of line and frees through
// operator delete (0x0002FD60). 0x00001DAC is the 0x24-byte element
// destructor the VectorClassWide constructor at 0x00154CD0 hands its array
// iterator; 0x00001E13 is the rowed 8-byte wrapper destructor Rva00001E13
// (member destructor at +4). The element names are address-derived: no
// identity beyond size and destructor is claimed. The anchor exists only to
// make this unit emit the two destructors through delete[]; it is not a
// retail function.

#include <new>

#include "../../../../GameEngine/Include/Common/W3DRadarResetSurface.h"

// Rva00001E13Dtor.cpp's wrapper: int at +0, the member destructor at +4.
class Rva00001E13
{
public:
	~Rva00001E13();
private:
	int m_00;
	W3DRadarResetSurface m_04;
};

// 0x24-byte element whose destructor is the out-of-line body at 0x00001DAC.
class Rva0000234DElem
{
public:
	~Rva0000234DElem();
private:
	int m_words[9];
};

// ?bfmeVectorDeleteAnchor0000234D@@YAXPAVRva0000234DElem@@PAVRva00001E13@@@Z present-unmatched
void bfmeVectorDeleteAnchor0000234D(Rva0000234DElem *a, Rva00001E13 *b)
{
	delete[] a;
	delete[] b;
}

// The retail call in this body reads 0x00001DAC, an address the ledger already
// carries as ??1RenderSentenceGeometryView@@QAE@XZ. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??1Rva0000234DElem@@QAE@XZ=??1RenderSentenceGeometryView@@QAE@XZ")
