// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??1Rva005F00FB@@UAE@XZ retail 0x005F00FB 87B
// Called by the rowed scalar deleting dtor 0x005F02C4 (vtable 0x00C78A78#0)
// and the global dtor thunk 0x007B99B5. Two AsciiString arrays (+0x1C x8 and
// +0x08 x5) torn down through the vector dtor iterator with the rowed
// AsciiString dtor (VA 0x0088BA39), then the rowed base ??1Rva0022167C at +0.
// No own vptr store, as in the sibling Rva005E7529 over the same base.
#include "ascii_string.h"

class __declspec(novtable) Rva0022167C
{
public:
	~Rva0022167C();
	virtual void _pure() = 0;
private:
	char m_pad4[4];
};

class __declspec(novtable) Rva005F00FB : public Rva0022167C
{
public:
	virtual ~Rva005F00FB();
private:
	AsciiString m_names08[5]; // +0x08
	AsciiString m_names1C[8]; // +0x1C
};

Rva005F00FB::~Rva005F00FB()
{
}
