// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /I. /Ireference/shims/bfme2_bannerui /Ireference/shims/bfmealloc
// stlport
// Retail RVA 0x00216670, 75 bytes.
// ?SetBannerSlotXOffset@BannerUI@@QAEXIM@Z chain from just-landed 0x00216517: banner offset guard.
// __thiscall Banner setter with (index float): if new float equals slot at +0x3c return; if flag at +0x20 fire SetBannerXOffset via 0x00216517 then store.
// Evidence: callee 0x00216517 rowed int-return firer; callers 0x0052A2F4 0x0052A52B 0x0052AB56; literal SetBannerXOffset; global TheRva00222A8BTarget 0x009FE4CC.
#include <vector>
#include <hash_map>
#include "ascii_string.h"
class Rva00222A8BTarget;

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
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

// Retail reaches the 29-byte forwarder 0x002161A5, whose tag travels by const reference.
namespace _STL {
template <> BfmePod28 *__copy_ptrs<BfmePod28 *, BfmePod28 *>(BfmePod28 *first, BfmePod28 *last, BfmePod28 *result, const __false_type &tag);
}

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

BfmePod28 *Rva0021618AFind(BfmePod28 *first,BfmePod28 *last,int key);

int __cdecl Rva00216517Fire(Rva00222A8BTarget *target, void *owner, const char *name, const unsigned int *pInt, const float *pFloat);
int __cdecl Rva002162CFInvoke(Rva00222A8BTarget *target, void *owner, const char *name, const unsigned int &arg);

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

void BannerUI::SetBannerSlotXOffset(unsigned int index, float value)
{
	float *slot = &m_bannerXOffsets[index];
	if (value == *slot)
		return;
	if (m_aptMovieInitialized)
		Rva00216517Fire((Rva00222A8BTarget *)g_bfmeAptWindowManager, (void *)m_windowIndex, "SetBannerXOffset", &index, &value);
	*slot = value;
}

// The target's literal at 0x00BE58A0 is "DeleteBanner". It uses the same
// owner field at +0x24 and adjacent container view at +0x28 as SetBannerSlotXOffset.
// WB B6E700 calls this RemoveBanner and asserts that the handle exists.
// Native216621..216670 searches28-byte records by the by-value integer
// handle, fires DeleteBanner, and erases the matching iterator. The former
// fill/count/reference ABI was refuted by the same WB/native search chain.
void BannerUI::RemoveBanner(int value)
{
	BfmePod28 *end = m_banners.end();
	// Retail pushes the first word straight from memory (ff 37); begin() would load a register first.
	BfmePod28 *newEnd = Rva0021618AFind(*reinterpret_cast<BfmePod28 **>(&m_banners),end,value);
	bool alreadyAtEnd = newEnd == end;
	BfmePod28 * volatile savedEnd = newEnd;
	if (!alreadyAtEnd) {
		Rva002162CFInvoke((Rva00222A8BTarget *)g_bfmeAptWindowManager,
			(void *)m_windowIndex, "DeleteBanner", *(const unsigned int *)&value);
		m_banners.erase((BfmePod28 *)savedEnd);
	}
}
