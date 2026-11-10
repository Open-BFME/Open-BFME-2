// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "ascii_string.h"
#include "unicode_string.h"
//
// ??1OnlineHome@AptOnline@@UAE@XZ @0x005B922F 221B
// AptOnlineHome's destructor: WorldBuilder names it (AptOnlineHome.cpp:180
// s_instance assert) and retail closes the screen through the same
// "AptOnlineHome::InitGadgets" literal.
// Dtor with Apt conditional: stores vtable 0x873B70, if this == g_Va00E06480
// closes two screens via rva00223A94 plus AptOnlineHome InitGadgets via
// _bfme_closeAptScreen, clears global, destroys wide member +0x64, base
// Rva005248D0. Evidence: vtables 0x873B70/0x86DB78, globals g_Va00E06480,
// g_00DD3BC0/C4, TheRva00222A8BTarget, literal AptOnlineHome::InitGadgets,
// callees rowed StringBase PBD 0x37BA0 releaseBuffer D/G plus pin close and
// base dtor, caller deleting dtor 0x005B94E5.
//

void _bfme_closeAptScreen(const AsciiString &);

#include "../../Include/Common/Rva00223A94.h"

#include "../../Include/Common/Rva00222A8BTarget.h"

class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern int g_Va00E06480;
const char * g_00DD3BC0 = "OnlineHome/Gadgets/Image";	// retail RVA 0x009D3BC0 (.data), defined here
const char * g_00DD3BC4 = "OnlineHome/Gadgets/ImageLevelIconMain";	// retail RVA 0x009D3BC4 (.data), defined here

#include "../../Include/GameClient/Rva005248D0.h"

class Rva0056DC6B : public Rva005248D0
{
public:
	virtual ~Rva0056DC6B();
};

inline Rva0056DC6B::~Rva0056DC6B()
{
}

// WorldBuilder spells the class AptOnlineHome (assert names
// AptOnlineHome::AptOnlineHome / ::~AptOnlineHome); the tree's rowed
// constructor 0x005B9BBC (AptOnlineHomeConstructor.cpp) and Apt callbacks
// spell it AptOnline::OnlineHome, after the "AptOnline::OnlineHome::..."
// command strings. The destructor takes the constructor's spelling so that
// unit's virtual destructor reference resolves to this body.
class AptOnline
{
public:
	class OnlineHome;
};

class AptOnline::OnlineHome : public Rva0056DC6B
{
public:
	virtual ~OnlineHome();

private:
	char m_pad[0x64 - 0x58];
	UnicodeString m_64;
};

AptOnline::OnlineHome::~OnlineHome()
{
	if ((int)this == g_Va00E06480) {
		{
			AsciiString s(g_00DD3BC0);
			((Rva00223A94 *)g_bfmeAptWindowManager)->rva00223A94(&s);
		}
		{
			AsciiString s(g_00DD3BC4);
			((Rva00223A94 *)g_bfmeAptWindowManager)->rva00223A94(&s);
		}
		{
			AsciiString s("AptOnlineHome::InitGadgets");
			_bfme_closeAptScreen(s);
		}
		g_Va00E06480 = 0;
	}
}
