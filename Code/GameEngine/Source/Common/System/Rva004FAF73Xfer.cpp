// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva004FAF73@Rva004FAF73@@QAEXPAVXfer@@@Z @0x004FAF73 67B evidence: chain via just-landed Rva004FACD0Xfer 0x004FACD0; callees rowed rva004CE6E4 0x004CE6E4 plus Rva004FACD0Xfer plus Xfer slots 0x28 version and 0x7c; vector Science at +0x20 member at +0x2c.
// Honest Rva thiscall taking Xfer returning void ret-4.
#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum ScienceType
{
	SCIENCE_0 = 0
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

#include "XferVectorTypes.h"
#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/Rva004CE6E4.h"

typedef _STL::vector<ScienceType> ScienceTypeVector;

extern Xfer * __cdecl Rva004FACD0Xfer(Xfer *xfer, ScienceTypeVector *vec);

class Rva004FAF73
{
public:
	void rva004FAF73(Xfer *xfer);
	char m_pad[0x20];
	ScienceTypeVector m_vec;
	int m_2c;
};

void Rva004FAF73::rva004FAF73(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	*xfer == reinterpret_cast<Xfer::Version &>(version);

	((Rva004CE6E4 *)this)->rva004CE6E4(xfer);

	*xfer == m_2c;

	Rva004FACD0Xfer(xfer, &m_vec);
}
