// cl: /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1Rva004CE36@@UAE@XZ, retail 0x0004CE36..0x0004CE85 (79 bytes, EH): the
// destructor the rowed scalar deleting destructor ??_GRva004CE36 (0x0004CF47)
// and its -0xC thunk reach. It installs its own tables (0x00BC4C70 at +0,
// 0x00BC4C5C at +0xC), destroys its two sort-list vectors at +0xAC through
// the EH vector destructor iterator, and runs the base destructor 0x001F9D98.
// The render passes at 0x0004CF9A and 0x0004D47D use these same vectors with
// the existing particle handle push and erase operations.

class Rva001F9D98Primary
{
public:
	virtual ~Rva001F9D98Primary();
private:
	int m_04;
	int m_08;
};

class Rva001F9D98Secondary
{
public:
	virtual ~Rva001F9D98Secondary();
protected:
	unsigned char m_pad04[0x5C - 0x0C - 4];
	int m_5C;	// +0x5C
	unsigned char m_pad60[0xA8 - 0x60];
	bool m_A8;	// +0xA8
	unsigned char m_padA9[3];
};

class Rva001F9D98 : public Rva001F9D98Primary, public Rva001F9D98Secondary
{
public:
	Rva001F9D98();
	virtual ~Rva001F9D98();
};

#include <vector>
#include "../../Include/Common/RvaSmartPtr12.h"

namespace _STL {
template <> void _Destroy<RvaSmartPtr12 *>(RvaSmartPtr12 *, RvaSmartPtr12 *) throw();
}

class Rva004CE36 : public Rva001F9D98
{
public:
	Rva004CE36();
	virtual ~Rva004CE36();
private:
	_STL::vector<RvaSmartPtr12> m_sortLists[2];	// +0xAC
};

Rva004CE36::~Rva004CE36()
{
}

// ??0Rva004CE36@@QAE@XZ, retail 0x0004CDCD..0x0004CE28 (91 bytes, EH): the
// matching constructor. It runs the rowed base constructor 0x001FA69F
// and installs the two derived tables. The compiler passes the default
// vector constructor and destructor to the EH array iterator at the
// retail addresses 0x00256646 and 0x0004CDAF.
Rva004CE36::Rva004CE36()
{
	m_5C = 0;
	m_A8 = false;
}
