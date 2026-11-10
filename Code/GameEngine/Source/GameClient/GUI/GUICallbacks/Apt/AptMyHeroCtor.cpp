// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0AptMyHero@@QAE@PAVAptCreateAHero@@@Z, retail 0x005B12C5..0x005B1748 (1155 bytes, EH,
// ret 4). The AptMyHero constructor: it installs vftable 0x00872A80 whose
// slot 0 is the rowed scalar deleting dtor ??_GAptMyHero 0x005B1A50, and its
// extern-handler keys are the ones the rowed ~AptMyHero 0x005B190D drops
// (rva005B0A53 "Base"/"Cur"/"Max" for five slots); WorldBuilder twin
// 0x0156D5A0 pushes the same "MyHero::*" names.
//
// Its only caller, the AptCreateAHero constructor, passes itself
// (REL32 at 0x005142E9 for the hero embedded at +0x27C).
//
// Body: the CreateAHeroData base (pinned 0x00409C3D with the empty name,
// colour 0xFF707070 and -1 defaults; rowed dtor 0x00409285), the holder at
// +0x140 (the owning screen), the pending hero +0x144, flags and attribute
// points +0x148..+0x158, the location map +0x15C (vector base 0x00211E58,
// dtor 0x0007FAB3), the view range +0x168, +0x170 = 1, the two bling blocks
// +0x174 (eh vector constructor iterator with the folded closure 0x00256646
// and dtor 0x0007FAB3) and +0x18C. It blanks the name / class / type /
// attribute-point texts through the Apt window manager (rowed bfmeSetText),
// then registers its extern handlers on the holder's +0x228 adder (rowed
// 0x005245F3, delegate 0x00579E47): Base/Cur/Max attributes for slots 0-4,
// NumAppearance 0-6, MaxAttribute / MaxAwards / IsSystemHero and one
// AwardState per TheCreateAHeroManager award (+0x1D4), and finally runs
// the rowed 0x005B04B6.

#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../../../Include/GameLogic/CreateAHeroData.h"

#include "../../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

#include "../../../../../Include/GameLogic/CreateAHeroManager.h"
extern CreateAHeroManager *TheCreateAHeroManager;

const AsciiString &rva005B0A53(const char *kind, int index);

class Rva005B045D
{
public:
	void *rva005B045D();
	void rva005B04B6();
	char m_pad00[0x144];
private:
	void *m_ptr144; // +0x144
	char m_pad148[0x4];
	int m_flag14c; // +0x14C
	char m_pad150[0x8];
	int m_val158; // +0x158
};

#include "../../../../../Include/GameClient/AptMyHero.h"

// Keep the existing external destructor providers: BfmeE8 at RVA 0x0007FAB3
// and ObjectCreationList pointers in the existing STLport instantiation.
namespace _STL
{
template <> vector<BfmeE8>::~vector();
template <> vector<const ObjectCreationList *>::~vector();
}

class __single_inheritance AptDelegateTarget;
typedef void (AptDelegateTarget::*AptDelegateMethod)(void);

#include "../../../../../Include/Common/DelegateDesc.h"

template <class T, class M> __forceinline DelegateDesc MakeDelegate(T *object, M method)
{
	DelegateDesc desc(object, method);
	return desc;
}

// Link: the AptRef lineage fork. The FunctorHolder/Rva00579E47-wrapper spelling
// used here emitted a census-losing dtor copy (a jmp to an extern base dtor,
// digest e67a72158686); retail keeps the majority TU's inline-release copy
// (digest 361dbf55f6ea). Adopt the majority spelling verbatim
// (ArmyCommandPointsMovieClipConstructor.cpp): trivial base, inline release
// dtor. The EH funclets call the dtor by name for the by-value handler temps,
// so their bytes are unchanged; only the COMDAT body becomes retail's.
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);Rva00579E47(const Rva00579E47 &other);void*ptr;};
// NOTE: the base copy ctor stays DECLARED (extern, non-trivial) so the implicit
// AptRef copy ctor is non-trivial too: that preserves the by-value handler-temp
// passing convention (dynamic esp-temp) and the 0x20 frame of the rowed bodies.
// Only the base *destructor* declaration was removed (see below).
class AptExternHandler;struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
template<class T> class AptRef:public Rva00579E47 {public:AptRef(const DelegateDesc&desc):Rva00579E47(desc){}~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);
};

// The create-a-hero screen that embeds the hero at +0x27C and constructs
// it with itself (0x005142E9); its extern-handler adder sits at +0x228.
class AptCreateAHero
{
public:
	char pad000[0x228];
	AptExternHandlerAdder m_externHandlers;
};

class CommandButton;
#include "../../../../../Include/Common/CreateAHeroHero.h"
class Rva005B03B4 { public: void rva005B03B4(int, char *, int); };
class Rva005B0608
{
public:
 void rva005B0608(unsigned, char *, int);
 void rva005B0648(unsigned, char *, int);
 void rva005B068E(unsigned, char *, int);
 void rva005B06CE(unsigned, char *, bool);
};

AptMyHero::AptMyHero(AptCreateAHero *holder)
	: CreateAHeroData(0, 0, 0, UnicodeString::TheEmptyString, -1, 0xFF707070, -1),
	  field140(holder), field144(0), field148(false), field14C(0), field150(true), field151(true),
	  field154(0), field158(0), field170(1), field18C(0)
{
	g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:MyHeroName"), UnicodeString((const unsigned short *)L" "), false);
	g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:MyHeroClass"), UnicodeString((const unsigned short *)L" "), false);
	g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:MyHeroType"), UnicodeString((const unsigned short *)L" "), false);
	g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:MyHeroAttribPoints"), UnicodeString((const unsigned short *)L" "), false);

	{
		int i = 0;
		DelegateDesc baseHandler = MakeDelegate(this, &Rva005B0608::rva005B0608);
		DelegateDesc curHandler = MakeDelegate(this, &Rva005B0608::rva005B0648);
		DelegateDesc maxHandler = MakeDelegate(this, &Rva005B0608::rva005B068E);
		for (; i < 5; ++i) {
			field140->m_externHandlers.AddExternHandler(rva005B0A53("Base", i), i, AptRef<AptExternHandler>(baseHandler));
			field140->m_externHandlers.AddExternHandler(rva005B0A53("Cur", i), i, AptRef<AptExternHandler>(curHandler));
			field140->m_externHandlers.AddExternHandler(rva005B0A53("Max", i), i, AptRef<AptExternHandler>(maxHandler));
		}
	}
	{
		int i = 0;
		DelegateDesc appearanceHandler = MakeDelegate(this, &Rva005B0608::rva005B06CE);
		for (; i < 7; ++i) {
			AsciiString name;
			name.format("MyHero::NumAppearance_%d", i);
			field140->m_externHandlers.AddExternHandler(name, i, AptRef<AptExternHandler>(appearanceHandler));
		}
	}
	{
		AsciiString name("MyHero::MaxAttribute");
		field140->m_externHandlers.AddExternHandler(name, 0, AptRef<AptExternHandler>(MakeDelegate(this, &Rva005B03B4::rva005B03B4)));
	}
	{
		AsciiString name("MyHero::MaxAwards");
		field140->m_externHandlers.AddExternHandler(name, 1, AptRef<AptExternHandler>(MakeDelegate(this, &Rva005B03B4::rva005B03B4)));
	}
	{
		AsciiString name("MyHero::IsSystemHero");
		field140->m_externHandlers.AddExternHandler(name, 2, AptRef<AptExternHandler>(MakeDelegate(this, &Rva005B03B4::rva005B03B4)));
	}
	{
		unsigned int awards = TheCreateAHeroManager->field1D4;
		unsigned int i = 0;
		if (awards > 0) {
			DelegateDesc awardHandler = MakeDelegate(this, &CreateAHeroHero::rva005B0357);
			do {
				AsciiString name;
				name.format("MyHero::AwardState_%d", i);
				field140->m_externHandlers.AddExternHandler(name, i, AptRef<AptExternHandler>(awardHandler));
			} while (++i < awards);
		}
	}
	reinterpret_cast<Rva005B045D *>(this)->rva005B04B6();
}

// Retail's CreateAHeroData vftable (0x00C38D88) holds the xfer 0x00408C11 in slot 3 and 0x004083FF
// in slot 4; the rows at those addresses carry the CreateAHeroHero spelling. Bind this unit's
// placeholders to them.
