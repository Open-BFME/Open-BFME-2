// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /I. /Ireference/shims/bfme2_bannerui /Ireference/shims/bfmealloc
// stlport
// ?Hide@BannerUI@@QAEX_N@Z, retail 0x00216B3F, 65 bytes.
// Guards on TheRva00222A8BTarget null then branches on bool param: true calls
// pinned rva0022277D with +0x24 and erases pod28 range at +0x28 clearing +0x20,
// false calls rowed ShowLevel with +0x24 as int. Evidence: global 0x009FE4CC
// extern name in use; callees rowed 0x005842F7 0x002224FE pinned 0x0022277D;
// callers at 0x00216D32 0x00402A62 0x00402AD3; prev/next STLport pod28 TUs.
#include <vector>
#include <hash_map>
#include "ascii_string.h"

#include "../../subsystem/SubsystemInterface.h"
class INI;

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
struct BfmePod28
{
	unsigned int slot;			// +0x00
	int bannerID;				// +0x04
	const void *typeEntry;		// +0x08, the type table's key/info pair
	int state;					// +0x0C
	int progress;				// +0x10
	int timer;					// +0x14
	bool pendingDelete;			// +0x18
	// The default less<> of __lower_bound 0x005413B0: signed, on the first word.
	__forceinline bool operator<(const BfmePod28 &o) const { return (int)slot < (int)o.slot; }
};

class BannerUI : public SubsystemInterface
{
public:
	BannerUI();
	static void ParseBannerTypeInfo(INI *ini);
 void init();
 const AsciiString &GetBannerIconImageName(const AsciiString &key);
 int CreateBanner(int bannerID);
 void OnAptMovieInitialized(const char *path);
 void OnBannerButton(int slot);
 void rva00216735(const char *path);
 void SetBannerSlotXOffset(unsigned int index, float value);
 void RemoveBanner(int value);
 void Hide(bool on);
 void reset();
 void update();

	static __forceinline int bannerStateFor(int armyState)
	{
		switch (armyState) {
		case 0:
			return 0;
		case 2:
			return 1;
		case 3:
			return 2;
		default:
			return 3;
		}
	}

private:
 Rva00216BF0 m_types;
 bool m_aptMovieInitialized;	// +0x20, WB's assert names it
 unsigned char m_pad21[3];
 int m_windowIndex;
 _STL::vector<BfmePod28, _STL::allocator<BfmePod28> > m_banners;	// +0x28
 bool m_movieGone;	// +0x34
 unsigned char m_pad35[3];
 unsigned int m_summaryIndex;	// +0x38
 float m_bannerXOffsets[2];	// +0x3C, SetBannerSlotXOffset's per-slot offsets; native21725B..21726F initializes3C..44 only
};

// bfme link decl-only BfmePod28
namespace _STL { template <> BfmePod28 * vector<BfmePod28, allocator<BfmePod28> >::erase(BfmePod28 *, BfmePod28 *); }

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

class BfmeAptWindowManager;

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

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

void BannerUI::Hide(bool on)
{
	if ((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager) == 0)
		return;
	m_movieGone = on;
	if (on)
	{
		reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->HideLevel(m_windowIndex);
		_STL::vector<BfmePod28> &vr = m_banners;
		vr.erase(vr.begin(), vr.end());
		m_aptMovieInitialized = false;
	}
	else
	{
		((AptPlayer *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->ShowLevel(m_windowIndex);
	}
}

// ?reset@BannerUI@@QAEXXZ, retail 0x00216D2D (47B, reached from a retail
// table): hide, empty the +0x28 records and zero the two +0x3C floats.
void BannerUI::reset()
{
	Hide(true);
	_STL::vector<BfmePod28> &vr = m_banners;
	vr.erase(vr.begin(), vr.end());
	for (float *p = m_bannerXOffsets; p != m_bannerXOffsets + 2; ++p)
		*p = 0.0f;
}
