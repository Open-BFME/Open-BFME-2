// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BFME2-only conquest/map-list extension: clean BF1 MpGameSetup and ZH
// SkirmishGameOptionsMenu provide the subsystem lead but not these badges.
// WB149CF20 independently supplies all twelve image labels and the profile,
// map-rating, sorting and row-insertion semantics. Native443538..443BF3 RET4
// proves the target fields/calls below; their providers are already rowed.
// codegen otherwise instantiates the min<int> COMDAT (one byte shape
// per TU flags); a file-static overload takes those calls instead so this
// TU emits no external copy.
namespace _STL {
static inline const int &min(const int &a, const int &b)
{
    return b < a ? b : a;
}
}
// vector<MapMetaData *> storage goes to the C++-linkage free (0x00030830), as
// in MapUtilGetDefaultMap.cpp, so this TU's teardown COMDATs carry the same
// relocation as that unit's first copy in link order.
#include <stdlib.h>
namespace _STL { void __cdecl free(void *); }
// Bind before STLport imports ::free into the same namespace.
static __forceinline void releaseMapListStorage(void *storage)
{
	_STL::free(storage);
}
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <algorithm>
class MapMetaData;
namespace _STL {
template<> inline void allocator<MapMetaData *>::deallocate(MapMetaData **__p, size_type) const
{
	if (__p != 0) releaseMapListStorage((void *)__p);
}
}
#include "ascii_string.h"
#include "unicode_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> COMDAT copies, so the calls bind the kept rowed copies.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> void vector<AsciiString, allocator<AsciiString> >::push_back(const AsciiString&);
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString*, AsciiString*);
template <> void vector<AsciiString, allocator<AsciiString> >::_M_insert_overflow(AsciiString*, const AsciiString&, const __false_type&, size_t, bool);
}
class GameWindow;
class Image;
#include "../../../Include/GameClient/Image.h"
extern ImageCollection *TheMappedImageCollection;
struct ImageWidthView {char unknown[0x24];int width;};
#include "../../../Include/GameClient/MapMetaData.h"
class MapCache;
extern MapCache *TheMapCache;
void rva00302459(unsigned flags,_STL::vector<MapMetaData *> *maps);
class Rva0043FE9A {public:bool rva0043FE9A(MapMetaData *a,MapMetaData *b);protected:int key0,key1;};
struct Rva0043FE9ALess:public Rva0043FE9A {
 __forceinline Rva0043FE9ALess(int a,int b){key0=a;key1=b;}
 bool operator()(MapMetaData *const &a,MapMetaData *const &b){return rva0043FE9A(a,b);}
};
namespace _STL {template<> void sort<MapMetaData **,Rva0043FE9ALess>(MapMetaData **,MapMetaData **,Rva0043FE9ALess);}
#include "../../../Include/Common/UserPreferences.h"
// Narrow ABI view of the compiler-generated scalar deleting destructor.
// Slot0 with flags0 destroys and returns the allocation for separate free;
// native443BB5..443BC9 demonstrates both operations and the returned pointer.
struct PreferencesDeletingDtorView {virtual void *scalarDeletingDtor(unsigned flags);};
class RealTimeStatsPreferences:public UserPreferences {public:
 RealTimeStatsPreferences(const UnicodeString &profile);
 virtual ~RealTimeStatsPreferences();
};
#include "../../../Include/GameClient/SkirmishPreferencesClass.h"
typedef char CheckUserPreferences20[(sizeof(UserPreferences)==20)?1:-1];
typedef char CheckSkirmishPreferences32[(sizeof(SkirmishPreferences)==32)?1:-1];
int GadgetListBoxGetColumnWidth(GameWindow *window,int column);
int GadgetListBoxGetNumColumns(GameWindow *window);
void GadgetListBoxReset(GameWindow *window);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data, int row, int column);
int GadgetListBoxAddEntryImage(GameWindow *window,const Image *image,int row,int column,int height,int width,bool overwrite,int color);
int GadgetListBoxAddEntryText(GameWindow *window,UnicodeString text,int color,int row,int column,bool overwrite);
class AptMpGameSetup {public:void rva00443538(int flags);
 private:
 char unknown00[0x7c];int mode;
 char unknown80[0x2c2-0x80];bool refreshing;
 char unknown2C3[0x394-0x2c3];GameWindow *mapList;
 _STL::vector<AsciiString> mapNames;int lobbyFlags;
 char unknown3A8[4];int sortColumn,previousSortColumn;
};
void AptMpGameSetup::rva00443538(int flags)
{
 if(!TheMapCache || !mapList) return;
 const Image *notConquered=TheMappedImageCollection->findImageByName(AsciiString("AptDifficultyNotConquered"));
 const Image *easy=TheMappedImageCollection->findImageByName(AsciiString("AptDifficultyEasyConquered"));
 const Image *medium=TheMappedImageCollection->findImageByName(AsciiString("AptDifficultyMedConquered"));
 const Image *hard=TheMappedImageCollection->findImageByName(AsciiString("AptDifficultyHardConquered"));
 const Image *brutal=TheMappedImageCollection->findImageByName(AsciiString("AptDifficultyBrutalConquered"));
 const Image *maximum=TheMappedImageCollection->findImageByName(AsciiString("AptDifficultyMaxConquered"));
 const Image *userNotConquered=TheMappedImageCollection->findImageByName(AsciiString("AptUserMapNotConquered"));
 const Image *userEasy=TheMappedImageCollection->findImageByName(AsciiString("AptUserMapEasyConquered"));
 const Image *userMedium=TheMappedImageCollection->findImageByName(AsciiString("AptDifficultyMedConquered"));
 const Image *userHard=TheMappedImageCollection->findImageByName(AsciiString("AptUserMapHardConquered"));
 const Image *userBrutal=TheMappedImageCollection->findImageByName(AsciiString("AptUserMapBrutalConquered"));
 const Image *userMaximum=TheMappedImageCollection->findImageByName(AsciiString("AptUserMapMaxConquered"));
 UserPreferences *stats=0;
 int width=hard ? ((const ImageWidthView *)hard)->width : 10;
 int columnWidth=GadgetListBoxGetColumnWidth(mapList,0);
 width=_STL::min(width,columnWidth);
 refreshing=true;
 int numColumns=GadgetListBoxGetNumColumns(mapList);
 if(lobbyFlags&1) {
  SkirmishPreferences prefs(mode);
  stats=new RealTimeStatsPreferences(prefs.Rva0043B9F5());
 }
 if(!(flags&0x40)) {GadgetListBoxReset(mapList);mapNames.clear();}
 _STL::vector<MapMetaData *> maps;
 rva00302459(flags,&maps);
 for(_STL::vector<MapMetaData *>::iterator it=maps.begin();it!=maps.end();++it) {
  MapMetaData *map=*it;
  if(stats && map->m_isMultiplayer) {
   int wonEasy=stats->rva00537190(AsciiString(map->m_fileName.str()),2);
   int wonMedium=stats->rva00537190(AsciiString(map->m_fileName.str()),3);
   int wonHard=stats->rva00537190(AsciiString(map->m_fileName.str()),4);
   int wonBrutal=stats->rva00537190(AsciiString(map->m_fileName.str()),5);
   int wonMaximum=stats->rva00537190(AsciiString(map->m_fileName.str()),6);
   if(wonMaximum) map->fieldF4=6;
   else if(wonBrutal) map->fieldF4=5;
   else if(wonHard) map->fieldF4=4;
   else if(wonMedium) map->fieldF4=3;
   else if(wonEasy) map->fieldF4=2;
   else map->fieldF4=1;
  } else map->fieldF4=0;
  if(!map->m_isOfficial)map->fieldF4|=0x8000;
 }
 _STL::sort(maps.begin(),maps.end(),Rva0043FE9ALess(sortColumn,previousSortColumn));
 for(_STL::vector<MapMetaData *>::iterator it=maps.begin();it!=maps.end();++it) {
  MapMetaData *map=*it;
  const Image *badge=notConquered;
  switch((int)map->fieldF4) {
  case 0:case 1:badge=notConquered;break;
  case 2:badge=easy;break;case 3:badge=medium;break;
  case 4:badge=hard;break;case 5:badge=brutal;break;case 6:badge=maximum;break;
  case 0x8000:case 0x8001:badge=userNotConquered;break;
  case 0x8002:badge=userEasy;break;case 0x8003:badge=userMedium;break;
  case 0x8004:badge=userHard;break;case 0x8005:badge=userBrutal;break;
  case 0x8006:badge=userMaximum;break;
  }
  GadgetListBoxSetItemData(mapList,(void *)(map->fieldF4),-1,1);
  int row=GadgetListBoxAddEntryImage(mapList,badge,-1,0,width,width,true,-1);
  row=GadgetListBoxAddEntryText(mapList,map->bfme_getDisplayName(false),-1,row,numColumns-3,true);
  UnicodeString players;players.format(L"%d",map->m_numPlayers);
  GadgetListBoxAddEntryText(mapList,players,-1,row,numColumns-1,true);
  mapNames.push_back(map->m_fileName);
 }
 if(stats) operator delete(((PreferencesDeletingDtorView *)stats)->scalarDeletingDtor(0));
 refreshing=false;
}
