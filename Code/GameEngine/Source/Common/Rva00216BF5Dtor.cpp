// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /I. /Ireference/shims/bfme2_bannerui /Ireference/shims/bfmealloc
// stlport
// ??1Rva00216BF5@@UAE@XZ, retail 0x00216BF5..0x00216D2D (312 bytes, EH):
// by its literals AptBannerUI's destructor (a SubsystemInterface; opaque pin
// of its scalar deleting destructor 0x00216DA0, table 0x00BE59E4). With an
// Apt player it removes the over-button handlers of both banner locations'
// available and waiting buttons and background, and drops the
// "AptBannerUI::OnInitialized" and "AptBannerUI::OnBttnBanner" callbacks
// (rowed 0x00224455). Then the +0x28 buffer goes to GameFree (unwind copy
// 0x0007FAB3), the +0xC bucket table dies (rowed 0x00216B80; its wrapper's
// unwind copy is the 5-byte thunk 0x00216BF0) and SubsystemInterface last.
#include <hash_map>
#include "ascii_string.h"

void __cdecl Rva00030830GameFree(void *);

class AptCommandMap;

class AptOverButtonHandler;

template <class T> class AptRef;

class AptPlayer
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);
	void AddOverButtonHandler(const AsciiString &name, AptRef<AptOverButtonHandler> handler);
	bool HideLevel(int);
	bool ShowLevel(int index);
	void RemoveOverButtonHandler(const AsciiString &name);
};

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00224455
{
public:
	int RemoveCommandMap(const AsciiString *name);
};

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

struct Rva002171F2Element { char bytes[1]; bool operator<(const Rva002171F2Element&)const; bool operator==(const Rva002171F2Element&)const; };
namespace _STL {template<> struct hash<Rva002171F2Element> { unsigned operator()(const Rva002171F2Element&) const; };}
typedef _STL::hash_map<int, Rva002171F2Element> Rva002171F2Table;
class Rva00056F61;
// Native ctor217211 constructs this20B table at+C through the shared
// constructor2171F2 and FuncInfo913FFC state1 destroys it through216BF0.
// Preserve lookup/constructor ABI names on the storage view while using
// the existing destructor owner for this wrapper; original type unknown.
// Native 00216B80: rowed 00216AF6 clear, then free the bucket vector.
class Rva00216AF6 : public Rva002171F2Table
{
public:
	~Rva00216AF6();
};
// Its inline teardown is the 5-byte tail jump 0x00216BF0 in unwind funclets.
class Rva00216BF0 : public Rva00216AF6
{
public:
	Rva00216BF0() {}
	~Rva00216BF0() {}
	// The lookups 0x00056F61 and 0x0041534B are rowed on the Rva00056F61 view of these 20 bytes.
	Rva00056F61 &lookup() { return *reinterpret_cast<Rva00056F61 *>(this); }
};
typedef char BannerTableHas20Bytes[sizeof(Rva00216BF0)==20 ? 1 : -1];
struct Gen_uw_0007fab3
{
	~Gen_uw_0007fab3() { if (m_begin) Rva00030830GameFree(m_begin); }
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class Rva00216BF5 : public SubsystemInterface
{
public:
	virtual ~Rva00216BF5();
private:
	Rva00216BF0 m_types;			// +0x0C
	bool m_aptMovieInitialized;		// +0x20
	unsigned char m_pad21[3];
	int m_windowIndex;				// +0x24
	Gen_uw_0007fab3 m_28;			// +0x28
};

Rva00216BF5::~Rva00216BF5()
{
	if (((AptPlayer *)g_bfmeAptWindowManager))
	{
		for (unsigned int i = 0; i < 2; ++i)
		{
			AsciiString path;
			path.format("BannerUI/~Location%d/Banner/AvailableBttn/", i);
			((AptPlayer *)g_bfmeAptWindowManager)->RemoveOverButtonHandler(path);
			path.format("BannerUI/~Location%d/Banner/WaitingBttn/", i);
			((AptPlayer *)g_bfmeAptWindowManager)->RemoveOverButtonHandler(path);
			path.format("BannerUI/~Location%d/Banner/Background", i);
			((AptPlayer *)g_bfmeAptWindowManager)->RemoveOverButtonHandler(path);
		}
		{
			AsciiString name("AptBannerUI::OnInitialized");
			((Rva00224455 *)((AptPlayer *)g_bfmeAptWindowManager))->RemoveCommandMap(&name);
		}
		{
			AsciiString name("AptBannerUI::OnBttnBanner");
			((Rva00224455 *)((AptPlayer *)g_bfmeAptWindowManager))->RemoveCommandMap(&name);
		}
	}
}
