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
class BfmeAptWindowManager;
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
 char pad[0x14C];
 Rva005B566BClassVector classes;
};
extern CreateAHeroManager *TheCreateAHeroManager;

class Rva005B566B {
public: void rva005B566B();
private:
 char pad[0x1C];
 Rva00423A68 heroes;
};
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
