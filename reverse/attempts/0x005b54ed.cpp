// ?rva005B54ED@Rva005B566B@@QAEXII_N@Z
// partial score=0.8481675392670157 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /O1 /G7 /arch:SSE
// WB157C640 names Class::CreateDefaultHeroes; native5B566B..5B576B
// independently establishes the behavior and offsets. Retain a neutral
// target method spelling while the weak WB string association is unresolved.
#include "ascii_string.h"
#include "unicode_string.h"

class CreateAHeroData;
class Rva00219251 { public:
 CreateAHeroData *rva00219251(int,int,int,const UnicodeString &,int,int,int);
};
class Rva00407020 { public: bool rva00407020(); };
class ModuleData;
class Rva00423A68 { public: void rva00423A68(const ModuleData *); };
class Rva00222A8BTarget { public:
 void rva002239FA(const AsciiString &,const AsciiString &);
};
class BfmeAptWindowManager {public:void bfmeSetText(const AsciiString &,const UnicodeString &,bool);};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

struct Rva005B566BClassEntry { char bytes[32]; };
struct Rva005B566BClassVector {
 Rva005B566BClassEntry *start,*finish,*end;
 __forceinline unsigned int size() const { return finish-start; }
};
class CreateAHeroManager {
public:
 int rva00219D52(unsigned int);
 const AsciiString &GetClassImageName(unsigned int);
 const AsciiString &GetButtonImageName(unsigned,unsigned);
 const AsciiString &GetClassDescTag(unsigned);
 const AsciiString &GetSubClassDescTag(unsigned,unsigned);
 char pad[0x14C];
 Rva005B566BClassVector classes;
};
extern CreateAHeroManager *TheCreateAHeroManager;

class GameTextInterface {public:
#define V(n) virtual void slot##n();
V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)
#undef V
virtual UnicodeString fetchLabel(const AsciiString &,bool *exists=0);
};
extern GameTextInterface *TheGameText;
class AptMyHero {public:void rva005B21DA(CreateAHeroData *,bool,int);};
class Rva0040A3D2 {public:CreateAHeroData *rva0040A3D2(int,int);};
struct ClassScreenPrefix {char prefix[0x27C];AptMyHero hero;};

class Rva005B566B {
public: void rva005B566B();void rva005B54ED(unsigned,unsigned,bool);
private:
 char pad[4];ClassScreenPrefix *screen;char gap[0x1C-8];
 Rva00423A68 heroes;
};
void Rva005B566B::rva005B54ED(unsigned major,unsigned minor,bool animate)
{
 CreateAHeroData *hero=reinterpret_cast<Rva0040A3D2 *>(&heroes)->rva0040A3D2(major,minor);
 if(!hero)return;
 screen->hero.rva005B21DA(hero,true,animate?1:0);
 unsigned count=TheCreateAHeroManager->rva00219D52(major);
 for(unsigned i=0;i<count;++i) {
  const AsciiString &image=TheCreateAHeroManager->GetButtonImageName(major,i);
  AsciiString key;
  key.format("Cah::TypeIcon%d",i);
  reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager)->rva002239FA(key,image);
 }
 {
  AsciiString key("APT:CahClassDescription");
  g_bfmeAptWindowManager->bfmeSetText(key,TheGameText->fetchLabel(TheCreateAHeroManager->GetClassDescTag(major)),true);
 }
 {
  AsciiString key("APT:CahTypeDescription");
  const UnicodeString &text=TheGameText->fetchLabel(TheCreateAHeroManager->GetSubClassDescTag(major,minor));
  g_bfmeAptWindowManager->bfmeSetText(key,text,true);
 }
}
void Rva005B566B::rva005B566B()
{
 if (!TheCreateAHeroManager) return;
 unsigned int count=TheCreateAHeroManager->classes.size();
 for (unsigned int i=0;i<count;++i) {
  unsigned int subCount=TheCreateAHeroManager->rva00219D52(i);
  for (unsigned int j=0;j<subCount;++j) {
   CreateAHeroData *hero=reinterpret_cast<Rva00219251 *>(TheCreateAHeroManager)->rva00219251(
     0,i,j,UnicodeString::TheEmptyString,-1,0xFF707070,-1);
   reinterpret_cast<Rva00407020 *>(hero)->rva00407020();
   heroes.rva00423A68(reinterpret_cast<const ModuleData *>(hero));
  }
  AsciiString image(TheCreateAHeroManager->GetClassImageName(i));
  AsciiString key;
  key.format("Cah::ClassIcon%d",i);
  reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager)->rva002239FA(key,image);
 }
}
