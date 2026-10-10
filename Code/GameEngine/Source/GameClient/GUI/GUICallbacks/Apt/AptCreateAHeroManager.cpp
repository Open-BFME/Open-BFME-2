// cl: /Ob2 /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// WB157DCE0 names Manager::PopulateHeroList; native5B6755..5B692F.
// Target prefixes and the comparator words are measured from retail.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
class GameWindow;
class Image {public:char prefix[0x24];int width;};
class ImageCollection {public:const Image *findImageByName(const AsciiString &);};
extern ImageCollection *TheMappedImageCollection;
enum NameKeyType;
class CreateAHeroData {public:unsigned rva00408109(const NameKeyType *);char prefix[8];UnicodeString name;unsigned major,minor;char gap[0x48-0x14];bool isDefault;};
class Rva0040A3F9 {public:unsigned *first,*last,*limit;bool rva0040A441(CreateAHeroData *);};
class CreateAHeroManager {public:Rva0040A3F9 *rva0021F797();const AsciiString &GetSubClassNameTag(unsigned,unsigned);};
extern CreateAHeroManager *TheCreateAHeroManager;
class GameTextInterface {public:
#define V(n) virtual void slot##n();
V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)
#undef V
virtual UnicodeString fetchLabel(const AsciiString &,bool *exists=0);
};
extern GameTextInterface *TheGameText;
void GadgetListBoxReset(GameWindow *);
void GadgetListBoxSetSelected(GameWindow *,int);
int GadgetListBoxAddEntryImage(GameWindow *,const Image *,int,int,int,int,bool,int);
int GadgetListBoxAddEntryText(GameWindow *,UnicodeString,int,int,int,bool);
void Rva00325388Send(GameWindow *,int,int,int);
class Rva005B61B3 {public:int key0,key1;bool rva005B61B3(void *,void *);};
struct Rva005B61B3Less: Rva005B61B3 {Rva005B61B3Less(int a,int b){key0=a;key1=b;}};
namespace _STL {template<class I,class C> void sort(I,I,C);}
struct HeroListScreenPrefix {char prefix[0x284];UnicodeString selectedName;};
struct Rva005B5C70Box {void Run(int);};
extern "C" void __cdecl free(void *);
struct HeroListScratch {
 unsigned *first,*last,*limit;
 __forceinline HeroListScratch(const Rva0040A3F9 &source){reinterpret_cast<_STL::vector<unsigned> *>(this)->_STL::vector<unsigned>::vector(*reinterpret_cast<const _STL::vector<unsigned> *>(&source));}
 __forceinline ~HeroListScratch(){if(first)free(first);}
};
class AptCreateAHero {public:class Manager;};
class AptCreateAHero::Manager {public:
 char word0[4];HeroListScreenPrefix *screen;GameWindow *heroWindow,*otherWindow;
 CreateAHeroData *selectedHero;int word14;Rva005B61B3Less order;
 void rva005B6755();void rva005B6A05();void rva005B5F2E();
};
void AptCreateAHero::Manager::rva005B6755() {
 if(TheCreateAHeroManager) {
  Rva0040A3F9 *list=TheCreateAHeroManager->rva0021F797();
  unsigned count=list->last-list->first;
  HeroListScratch heroes(*list);
  GadgetListBoxReset(heroWindow);
  const Image *image=TheMappedImageCollection->findImageByName(AsciiString("AptUserMapMaxConquered"));
  int imageSize=(int)(image?(float)image->width*0.8f:0.0f);
  const UnicodeString *selectedName=&screen->selectedName;
  int selectedIndex=0;
  _STL::sort(reinterpret_cast<void **>(heroes.first),reinterpret_cast<void **>(heroes.last),Rva005B61B3Less(order.key0,order.key1));
  for(unsigned i=0;i<count;++i) {
   CreateAHeroData *hero=reinterpret_cast<CreateAHeroData *>(heroes.first[i]);
   if(!hero->isDefault && image)GadgetListBoxAddEntryImage(heroWindow,image,i,0,imageSize,imageSize,true,-1);
   GadgetListBoxAddEntryText(heroWindow,hero->name,-1,i,1,true);
   unsigned minor=hero->minor,major=hero->major;
   UnicodeString label=TheGameText->fetchLabel(TheCreateAHeroManager->GetSubClassNameTag(major,minor));
   GadgetListBoxAddEntryText(heroWindow,label,-1,i,2,true);
   Rva00325388Send(heroWindow,(int)hero,i,0);
   if(selectedName->compare(hero->name)==0)selectedIndex=i;
  }
  GadgetListBoxSetSelected(heroWindow,selectedIndex);
  reinterpret_cast<Rva005B5C70Box *>(this)->Run(0);
 }
}
void AptCreateAHero::Manager::rva005B6A05() {
 if(selectedHero) {
  Rva0040A3F9 *list=TheCreateAHeroManager->rva0021F797();
  list->rva0040A441(selectedHero);
  selectedHero=0;
  rva005B6755();
 }
}

class Rva00406E53 {public:int rva00406E53();};
class Rva00406E65 {public:int rva00406E65(unsigned);};
class Rva0040BAD0 {public:int rva0040AAF8(int);};
class Rva0040AAD5;
extern Rva0040AAD5 *g_00E02F74;
struct StatRecord {char prefix[0x54];AsciiString label;};
int GadgetListBoxGetTopVisibleEntry(GameWindow *);
void GadgetListBoxSetTopVisibleEntry(GameWindow *,int);
void GadgetListBoxJustifyEntry(GameWindow *,int,int,int);
