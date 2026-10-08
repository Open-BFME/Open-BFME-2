// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva00511F73Run@@YAXXZ @0x00511F73 141B evidence: calls Save 0x00511730 StringBase ctor releaseBuffer rva00224455 rva002244CA Get 0x00381452 erase 0x002B7250; strings AptMessenger OnMessengerBttn IsOpen; global TheRva00222A8BTarget; g_00E048C4
// Free function saving gadget then AptMessenger lookups via AsciiString locals then erase via Get.
#include "ascii_string.h"
void __cdecl Rva00511730(int unused);
class Rva00224455
{
public:
	int rva00224455(const AsciiString *key);
};
class Rva002244CA
{
public:
	int rva002244CA(const AsciiString *key);
};
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};
int __cdecl Rva00381452Get();
class CreateAHeroData { char m_pad[0x140]; };
// 0x00A048C4: one retail global, defined (as g_Va00E048C4) by Rva007B6880Thunks.cpp,
// whose dtor thunk and Rva007ABBB3CtorInits.cpp's initializer address the same object.
extern unsigned int g_Va00E048C4;
void __cdecl Rva00511F73Run()
{
	Rva00511730(0);
	{
		AsciiString s1("AptMessenger::OnMessengerBttn");
		((Rva00224455 *)TheRva00222A8BTarget)->rva00224455(&s1);
	}
	{
		AsciiString s2("AptMessenger::IsOpen");
		((Rva002244CA *)TheRva00222A8BTarget)->rva002244CA(&s2);
	}
	((Rva002B7250 *)Rva00381452Get())->rva002B7250((CreateAHeroData *)&g_Va00E048C4);
}
