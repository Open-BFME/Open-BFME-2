// ?getDefaultMap@@YA?AVAsciiString@@_N@Z @ 0x0030582D 204B
// Retail sorts filtered metadata pointers and returns the selected filename.
// The 0x00302459 collector is recovered in this translation unit.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport46
#define free bfmeUnusedCRTFree
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <cstdlib>
#undef free
void free(void *);
#include <vector>
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <algorithm>
#include "ascii_string.h"
#include "unicode_string.h"

class MapMetaData
{
public:
	char unknown00[0x24];
	bool official;
	char unknown25[0x50 - 0x25];
	UnicodeString rva00300D0E();
	AsciiString m_fileName;
	char unknown54[0x100 - 0x54];
};

class MapCache : public _STL::map<AsciiString, MapMetaData>
{
public:
	void updateCache();
};

extern MapCache *TheMapCache;

struct Rva00300021Argument
{
	char unknown00[0x24];
	bool byte24, byte25, byte26;
};

class Rva00300021Flags
{
public:
	unsigned int flags;
	bool test(const Rva00300021Argument *) const;
};

#pragma optimize("s", on)

// Retail expands these cleanup operations in both callers. Keep their real
// STLport semantics inline-only, as in AIWall, so this unit does not emit
// unused cleanup COMDATs that conflict with other template instantiations.
namespace _STL {
template<> __declspec(dllimport) __forceinline void allocator<MapMetaData *>::deallocate(MapMetaData **p,size_t n) {if(p) ::free(p);}
template<> __declspec(dllimport) __forceinline void vector<MapMetaData *,allocator<MapMetaData *> >::_M_clear(){_Destroy(_M_start,_M_finish);_M_end_of_storage.deallocate(_M_start,_M_end_of_storage._M_data-_M_start);}
}

namespace _STL {
template<> __declspec(dllimport) __forceinline _Vector_base<MapMetaData *,allocator<MapMetaData *> >::~_Vector_base(){if(_M_start != 0) _M_end_of_storage.deallocate(_M_start,_M_end_of_storage._M_data-_M_start);}
}
void rva00302459(unsigned int flags, _STL::vector<MapMetaData *> *out)
{
	if (!(flags & 0x40))
		out->clear();
	MapCache::const_iterator last = TheMapCache->end();
	MapCache::const_iterator it = TheMapCache->begin();
	Rva00300021Flags predicate = { flags };
	if (it != last)
	{
		do
		{
			if (predicate.test(reinterpret_cast<const Rva00300021Argument *>(&it->second)))
			{
				MapMetaData *md = const_cast<MapMetaData *>(&it->second);
				out->push_back(md);
			}
			++it;
		} while (it != TheMapCache->end());
	}
}
#pragma optimize("", on)

struct Rva0030145CCmp
{
	bool operator()(MapMetaData *, MapMetaData *) const;
};

#pragma optimize("t", off)
#pragma optimize("s", on)
AsciiString getDefaultMap(bool isMultiplayer)
{
	if (!TheMapCache)
		return AsciiString::TheEmptyString;
	TheMapCache->updateCache();
	unsigned int flags = (isMultiplayer ? 8 : 4) | 1;
	_STL::vector<MapMetaData *> maps;
	rva00302459(flags, &maps);
	_STL::sort(maps.begin(), maps.end(), Rva0030145CCmp());
	if (maps.size() != 0)
		return maps.front()->m_fileName;
	return AsciiString::TheEmptyString;
}
#pragma optimize("", on)

// Retail 0x00304744..0x00304BA9 (1125B), the BFME2 map-list population
// counterpart of ZH/BFME1 populateMapListboxNoReset. The BFME1 source at
// 23b143233b5a8664a3bdf8572df6d905c310a5a1 supplies the semantic guide;
// BFME2 uses a flags argument and profile-specific RealTimeStatsPreferences.
// Native accesses establish MapMetaData's official byte +0x24, filename
// +0x50 and 0x100-byte stride. The RVA name retains identity uncertainty.
// Keep the real collector above this caller: its visibility separates the
// selection-count constant from the scrolling minimum and reproduces retail.
class GameWindow;
class Image
{
public:
	char gap[0x24];
	int width;
	int getImageWidth() const { return width; }
};
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &);
};
extern ImageCollection *TheMappedImageCollection;

class UserPreferences
{
public:
	virtual ~UserPreferences();
	int rva00537190(AsciiString, int);
	char storage[16];
};
class SkirmishPreferences : public UserPreferences
{
public:
	SkirmishPreferences(int);
	virtual ~SkirmishPreferences();
	UnicodeString Rva0043B9F5();
private:
	int profileIndex;
	void *names;
	AsciiString currentName;
};
class RealTimeStatsPreferences : public UserPreferences
{
public:
	RealTimeStatsPreferences(const UnicodeString &);
	virtual ~RealTimeStatsPreferences();
};
int GadgetListBoxGetNumColumns(GameWindow*);
int GadgetListBoxGetColumnWidth(GameWindow*,int);
void GadgetListBoxSetListLength(GameWindow*,int);
void GadgetListBoxReset(GameWindow*);
int GadgetListBoxAddEntryImage(GameWindow*,const Image*,int,int,int,int,bool,int);
int GadgetListBoxAddEntryText(GameWindow*,UnicodeString,int,int,int,bool);
void GadgetListBoxSetItemData(GameWindow*,void*,int,int);
void GadgetListBoxSetSelected(GameWindow*,const int*,int);
int GadgetListBoxGetTopVisibleEntry(GameWindow*);
int Rva00324807(GameWindow*);
void GadgetListBoxSetTopVisibleEntry(GameWindow*,int);
void rva00302459(unsigned,_STL::vector<MapMetaData*>*);
struct Rva003014D6Cmp { bool operator()(MapMetaData*,MapMetaData*)const; };
template<class T>inline const T &minValue(const T&a,const T&b){return a<b?a:b;}
template<class T>inline const T &maxValue(const T&a,const T&b){return a>b?a:b;}

int Rva00304744Populate(GameWindow *listbox, unsigned flags, const AsciiString &mapToSelect)
{
	if (!TheMapCache) return -1;
	if (!listbox) return -1;
	GadgetListBoxSetListLength(listbox, 1000);
	const Image *easy = 0, *medium = 0, *brutal = 0, *maximum = 0;
	RealTimeStatsPreferences *honors = 0;
	int w = 10, h = 10;
	int numColumns = GadgetListBoxGetNumColumns(listbox);
	if (numColumns > 1) {
		SkirmishPreferences preferences(0);
		honors = ::new RealTimeStatsPreferences(preferences.Rva0043B9F5());
		easy = TheMappedImageCollection->findImageByName("Star-Bronze");
		medium = TheMappedImageCollection->findImageByName("Star-Silver");
		brutal = TheMappedImageCollection->findImageByName("Star-Gold");
		maximum = TheMappedImageCollection->findImageByName("Star-Gold");
		w = maximum ? maximum->getImageWidth() : 10;
		int columnWidth = GadgetListBoxGetColumnWidth(listbox, 0);
		w = minValue(columnWidth, w);
		h = w;
	}
	if (!(flags & 0x40)) GadgetListBoxReset(listbox);
	_STL::vector<MapMetaData *> maps;
	rva00302459(flags, &maps);
	_STL::vector<MapMetaData *>::iterator first = maps.begin();
	_STL::sort(first, maps.end(), Rva003014D6Cmp());
	int selectionIndex = -1;
	_STL::vector<MapMetaData *>::iterator it = first;
	if (it != maps.end()) {
		do {
			MapMetaData *md = *it;
			int index = -1;
			const int defaultIndex = index;
			int imageData = defaultIndex;
			if (numColumns > 1 && md->official) {
				int numEasy = honors->rva00537190(AsciiString(md->m_fileName.str()), 2);
				int numMedium = honors->rva00537190(AsciiString(md->m_fileName.str()), 3);
				int numBrutal = honors->rva00537190(AsciiString(md->m_fileName.str()), 4);
				int numMaximum = honors->rva00537190(AsciiString(md->m_fileName.str()), 5);
				if (numMaximum) {
					imageData = 3;
					index = GadgetListBoxAddEntryImage(listbox, maximum, -1, 0, w, h, true, -1);
				} else if (numBrutal) {
					imageData = 2;
					index = GadgetListBoxAddEntryImage(listbox, brutal, -1, 0, w, h, true, -1);
				} else if (numMedium) {
					imageData = 2;
					index = GadgetListBoxAddEntryImage(listbox, medium, -1, 0, w, h, true, -1);
				} else if (numEasy) {
					imageData = 1;
					index = GadgetListBoxAddEntryImage(listbox, easy, -1, 0, w, h, true, -1);
				} else {
					imageData = 0;
					index = GadgetListBoxAddEntryImage(listbox, 0, -1, 0, w, h, true, -1);
				}
			}
			index = GadgetListBoxAddEntryText(listbox, md->rva00300D0E(), -1, index, numColumns - 1, true);
			if (((const StringBase<char> *)&md->m_fileName)->compare(*(const StringBase<char> *)&mapToSelect) == 0)
				selectionIndex = index;
			GadgetListBoxSetItemData(listbox, (void *)md->m_fileName.str(), index, 0);
			if (numColumns > 1) GadgetListBoxSetItemData(listbox, (void *)imageData, index, 1);
			++it;
		} while (it != maps.end());
	}
	GadgetListBoxSetSelected(listbox, &selectionIndex, 1);
	if (selectionIndex >= 0) {
		int top = GadgetListBoxGetTopVisibleEntry(listbox), bottom = Rva00324807(listbox);
		int rows = bottom - top;
		if (selectionIndex >= bottom) {
			int newTop = maxValue(0, selectionIndex - maxValue(1, rows / 2));
			GadgetListBoxSetTopVisibleEntry(listbox, newTop);
		}
	}
	if (honors) ::delete honors;
	return selectionIndex;
}

// Native23B flag helper, moved from Rva003000F6Get.cpp so the genuine
// callee remains visible to the34B bool-argument map-list wrapper below.
// WB C5E9B0/C5EA40 and both native call displacements establish this pair.
int Rva003000F6Get(bool systemMaps,bool multiplayer)
{
 int v=(systemMaps==0);
 ++v;
 if(multiplayer) v|=8; else v|=4;
 return v;
}
// Native 304BA9..304BCD (36B, cdecl): the same bool-argument map-list wrapper
// as Rva00304BCDPopulate below with flag 0x40 added to the helper's filter
// flags. Identity unproven; RVA-qualified name.
int Rva00304BA9Populate(GameWindow *listbox,bool systemMaps,bool multiplayer,
                       const AsciiString &mapToSelect)
{
 return Rva00304744Populate(listbox,Rva003000F6Get(systemMaps,multiplayer)|0x40,mapToSelect);
}
// WB does not preserve the outer wrapper name; retain the RVA-qualified
// identity. BF1 MapUtil's populateMapListbox is a semantic lead, but differs
// in reset work and string passing. Retail passes a const reference here.
// Keeping the real helper visible reproduces ADD ESP,8 after its call;
// a declaration-only helper instead compiles two POP ECX instructions.
int Rva00304BCDPopulate(GameWindow *listbox,bool systemMaps,bool multiplayer,
                       const AsciiString &mapToSelect)
{
 return Rva00304744Populate(listbox,Rva003000F6Get(systemMaps,multiplayer),mapToSelect);
}
