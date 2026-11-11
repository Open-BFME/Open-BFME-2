// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE
// ??1Rva00527827@@UAE@XZ, retail 0x00527CCE (176 bytes, EH).
//
// Target evidence: destructor of the class Rva00527827Constructor.cpp
// constructs. When TheAptPlayer exists it asks 0x00527B03 for the movie name
// and removes "<movie>_Content" from its custom renders (0x002246B1, the call
// AptCreateAHeroScreenDestructor.cpp makes on the same receiver), then drops
// the +0x1C reference holder and the +0x08 name; the empty polymorphic base
// is restored last. The constructor TU holds the full class view; this unit
// keeps the destructor-only view under the opaque pin name.
#include "ascii_string.h"

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

#include "../../../Include/GameClient/Rva002246B1.h"
// One native manager datum at VA DFE4CC; cast to this unit's receiver view.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

#include "../../../Include/Common/Rva000B3F84Pair.h"
#include "../../../Include/Common/AsciiStringRef.h"
#include "../../../Include/Common/AsciiStringPlusText.h"
AsciiStringPlusText operator+(const AsciiString &left, const char *right);

class Rva00527827Base
{
public:
	virtual ~Rva00527827Base() {}
};

class Rva004F6966
{
public:
	Rva004F6966() : m_ptr(0) {}
	~Rva004F6966()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
private:
	void *m_ptr;
};

class Rva00527827 : public Rva00527827Base
{
public:
	virtual ~Rva00527827();
	AsciiString rva00527B03();
private:
	int m_04;
	AsciiString m_name; // +0x08
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	Rva004F6966 m_1C;
};

static __forceinline void removeCustomRender(const AsciiString &key)
{
	reinterpret_cast<Rva002246B1 *>(g_bfmeAptWindowManager)->RemoveCustomRender(&key);
}

Rva00527827::~Rva00527827()
{
	if (reinterpret_cast<Rva002246B1 *>(g_bfmeAptWindowManager))
	{
		AsciiString movie = rva00527B03();
		removeCustomRender(movie + "_Content");
	}
}
