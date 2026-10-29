// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
//
// Destructors of container elements whose only non-scalar member is an
// AsciiString at +0. Each compiles to the 5-byte tail jump that releases
// that string, which retail folds into ??1?$StringBase@D@@AAE@XZ at
// 0x0048BA39; the element units call them by these names.
#include "ascii_string.h"

// RvaPair00207E26 (Rva00207E26VectorDtor.cpp): AsciiString key plus int value.
struct RvaPair00207E26
{
	AsciiString m_key;
	int m_value;
	~RvaPair00207E26();
};

RvaPair00207E26::~RvaPair00207E26()
{
}

// List elements of the STLport clear 0x00239D49 and erase 0x000BC67A; retail
// destroys each through the same fold, so the string is at +0.
struct Rva00239D49Element
{
	AsciiString m_00;
	~Rva00239D49Element();
};

Rva00239D49Element::~Rva00239D49Element()
{
}

struct Rva000BC67AElement
{
	AsciiString m_00;
	~Rva000BC67AElement();
};

Rva000BC67AElement::~Rva000BC67AElement()
{
}

// SiegeEngineContainModuleData's +0x194 pair (SiegeEngineContainModuleDataCtor.cpp):
// the ctor 0x0047C927's unwind state 2 destroys it through the same fold.
struct SiegeStringIntPair
{
	AsciiString m_string;
	int m_int198;
	~SiegeStringIntPair();
};

SiegeStringIntPair::~SiegeStringIntPair()
{
}

// UnitRevivalTracker.cpp's static strings (RevivalStaticAsciiString) release
// through this out-of-line destructor of a four-byte string view; retail
// calls the same fold for them.
class Rva0048BA39StringElement
{
	AsciiString m_00;
public:
	~Rva0048BA39StringElement();
};

Rva0048BA39StringElement::~Rva0048BA39StringElement()
{
}
