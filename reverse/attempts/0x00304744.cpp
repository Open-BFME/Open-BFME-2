// ?Rva00304744Populate@@YAHPAVGameWindow@@IABVAsciiString@@@Z
// partial score=0.9792062414818727 date=2026-10-10
// ?Rva00304744Populate@@YAHPAVGameWindow@@IABVAsciiString@@@Z
// partial score=0.994 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// Primary ZH/BF1 MapUtil::populateMapListboxNoReset. BF2 combines filters into flags,
// sorts borrowed metadata pointers and uses current-profile RealTimeStats preferences.
#define free unusedCRTFree
#include <cstdlib>
#undef free
void free(void*);
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
class GameWindow;
class Image {public: char gap[0x24];int width;int getImageWidth()const{return width;}};
class ImageCollection {public: const Image *findImageByName(const AsciiString&);};
extern ImageCollection *TheMappedImageCollection;
class MapCache;extern MapCache *TheMapCache;
class UserPreferences {public: virtual ~UserPreferences();int rva00537190(AsciiString,int);char storage[16];};
class SkirmishPreferences:public UserPreferences {public:SkirmishPreferences(int);virtual ~SkirmishPreferences();UnicodeString Rva0043B9F5();private:int profileIndex;void*names;AsciiString currentName;};
class RealTimeStatsPreferences:public UserPreferences {public:RealTimeStatsPreferences(const UnicodeString&);virtual ~RealTimeStatsPreferences();};
class MapMetaData {public:char gap[0x24];bool official;char gap25[0x50-0x25];AsciiString fileName;char gap54[0x100-0x54];UnicodeString rva00300D0E();};
int GadgetListBoxGetNumColumns(GameWindow*);
int GadgetListBoxGetColumnWidth(GameWindow*,int);
void GadgetListBoxSetListLength(GameWindow*,int);
void GadgetListBoxReset(GameWindow*);
int GadgetListBoxAddEntryImage(GameWindow*,const Image*,int,int,int,int,bool,int);
int GadgetListBoxAddEntryText(GameWindow*,UnicodeString,int,int,int,bool);
void Rva00325388Send(GameWindow*,int,int,int);
void GadgetListBoxSetSelected(GameWindow*,const int*,int);
int GadgetListBoxGetTopVisibleEntry(GameWindow*);
int Rva00324807(GameWindow*);
void GadgetListBoxSetTopVisibleEntry(GameWindow*,int);
void rva00302459(unsigned,_STL::vector<MapMetaData*>*);
struct Rva003014D6Cmp { bool operator()(MapMetaData*,MapMetaData*)const; };
namespace _STL {template<class I,class C>void sort(I,I,C);template<>void sort<MapMetaData**,Rva003014D6Cmp>(MapMetaData**,MapMetaData**,Rva003014D6Cmp);}
template<class T>inline const T &minValue(const T&a,const T&b){return a<b?a:b;}
template<class T>inline const T &maxValue(const T&a,const T&b){return a>b?a:b;}
static __forceinline int iconWidth(const Image*image,const int &fallback){if(image)return image->width;return fallback;}
int Rva00304744Populate(GameWindow *listbox,unsigned flags,const AsciiString &mapToSelect)
{
 if(!TheMapCache)return -1;
 if(!listbox)return -1;
 GadgetListBoxSetListLength(listbox,1000);
 const Image *easy=0,*medium=0,*brutal=0,*maximum=0;
 RealTimeStatsPreferences *honors=0;
 int w=10,h=10;
 int numColumns=GadgetListBoxGetNumColumns(listbox);
 if(numColumns>1){
  SkirmishPreferences preferences(0);
  honors=::new RealTimeStatsPreferences(preferences.Rva0043B9F5());
  easy=TheMappedImageCollection->findImageByName("Star-Bronze");
  medium=TheMappedImageCollection->findImageByName("Star-Silver");
  brutal=TheMappedImageCollection->findImageByName("Star-Gold");
  maximum=TheMappedImageCollection->findImageByName("Star-Gold");
  w=maximum?maximum->getImageWidth():10;
  int columnWidth=GadgetListBoxGetColumnWidth(listbox,0);w=minValue(columnWidth,w);h=w;
 }
 if(!(flags&0x40))GadgetListBoxReset(listbox);
 _STL::vector<MapMetaData*> maps;
 rva00302459(flags,&maps);
 _STL::vector<MapMetaData*>::iterator first=maps.begin();
 _STL::sort(first,maps.end(),Rva003014D6Cmp());
 int selectionIndex=-1;
 _STL::vector<MapMetaData*>::iterator it=first;
 if(it!=maps.end()){do {
  MapMetaData *md=*it;
  int index=-1;const int defaultIndex=index;int imageData=defaultIndex;
  if(numColumns>1 && md->official){
   int numEasy=honors->rva00537190(AsciiString(md->fileName.str()),2);
   int numMedium=honors->rva00537190(AsciiString(md->fileName.str()),3);
   int numBrutal=honors->rva00537190(AsciiString(md->fileName.str()),4);
   int numMaximum=honors->rva00537190(AsciiString(md->fileName.str()),5);
   if(numMaximum){imageData=3;index=GadgetListBoxAddEntryImage(listbox,maximum,-1,0,w,h,true,-1);}
   else if(numBrutal){imageData=2;index=GadgetListBoxAddEntryImage(listbox,brutal,-1,0,w,h,true,-1);}
   else if(numMedium){imageData=2;index=GadgetListBoxAddEntryImage(listbox,medium,-1,0,w,h,true,-1);}
   else if(numEasy){imageData=1;index=GadgetListBoxAddEntryImage(listbox,easy,-1,0,w,h,true,-1);}
   else {imageData=0;index=GadgetListBoxAddEntryImage(listbox,0,-1,0,w,h,true,-1);}
  }
  index=GadgetListBoxAddEntryText(listbox,md->rva00300D0E(),-1,index,numColumns-1,true);
  if(((const StringBase<char>*)&md->fileName)->compare(*(const StringBase<char>*)&mapToSelect)==0)selectionIndex=index;
  Rva00325388Send(listbox,(int)md->fileName.str(),index,0);
  if(numColumns>1)Rva00325388Send(listbox,imageData,index,1);
 ++it; }while(it!=maps.end());}
 GadgetListBoxSetSelected(listbox,&selectionIndex,1);
 if(selectionIndex>=0){
  int top=GadgetListBoxGetTopVisibleEntry(listbox),bottom=Rva00324807(listbox);
  int rows=bottom-top;
  if(selectionIndex>=bottom){int newTop=maxValue(0,selectionIndex-maxValue(1,rows/2));GadgetListBoxSetTopVisibleEntry(listbox,newTop);}
 }
 if(honors)::delete honors;
 return selectionIndex;
}
