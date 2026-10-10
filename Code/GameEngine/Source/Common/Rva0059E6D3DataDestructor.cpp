// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1Rva0059E6D3Data@@UAE@XZ, retail 0x0059E5AE..0x0059E647 (153 bytes, EH);
// pinned until now as the opaque ??1Rva0059E5AE@@UAE@XZ. The data object of
// the Rva0059E6D3 window (vtable 0x00C71094): two file-pointer vectors at +4
// and +0x10 are walked through the rowed range releaser 0x0059E2DC (a by-value
// box with a cleared flag) before the members go: the name vector at +0x1C
// and the string at +0x28 (and the two buffers). Class name address-derived;
// the two pointer vectors are 4-byte POD stand-ins.
#include <stdlib.h>
// Retail releases container buffers through the throwing allocation releaser,
// which preserves the native unwind states (as in AptCreateAHeroPowers.cpp).
void Rva00030830FreeAllocation(void *);
#define free Rva00030830FreeAllocation
#include <vector>
#undef free
#include "ascii_string.h"

enum ObjectID { INVALID_ID = 0 };

class FileClass;

struct Rva0059E2DCBox
{
	bool flag;
};

bool __cdecl rva0059E2DC(FileClass **first, FileClass **last, Rva0059E2DCBox box);

class Rva0059E6D3Data
{
public:
	virtual ~Rva0059E6D3Data();
private:
	_STL::vector<ObjectID> m_vec04;
	_STL::vector<ObjectID> m_vec10;
	_STL::vector<AsciiString> m_names1C;
	AsciiString m_str28;
};

Rva0059E6D3Data::~Rva0059E6D3Data()
{
	{
		Rva0059E2DCBox box = Rva0059E2DCBox();
		rva0059E2DC((FileClass **)&*m_vec04.begin(), (FileClass **)&*m_vec04.end(), box);
	}
	{
		Rva0059E2DCBox box = Rva0059E2DCBox();
		rva0059E2DC((FileClass **)&*m_vec10.begin(), (FileClass **)&*m_vec10.end(), box);
	}
}
