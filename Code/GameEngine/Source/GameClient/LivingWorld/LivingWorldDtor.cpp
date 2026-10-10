// ??1Rva002BFB2D@@UAE@XZ
// cl: /O1 /G7 /EHs /EHc- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// Native2BFB2D..2BFBF0 and scalar wrapper2BFD53 prove the lifetime body.
// Constructor2C0120 proves list-first/Snapshot-second declaration order and
// member28 (ctor2BF807): two words then a16-byte-element vector at+8.
// Native cleanup order independently proves hash98/AC and member-buffer
// lifetimes. Keep the established address-derived owner; the relationship
// to LivingWorld is supported by the constructor/vtable, while element and
// original hash types remain uncertain. Nested real vector clear avoids the
// retained alias and extra saved register of the earlier flat storage view.
#include <vector>
#include "Common/Snapshot.h"
void Rva00030830GameFree(void*);
class Rva002BF33DListener {public:virtual void notify(void*);};
struct Rva002BF33DList {
 Rva002BF33DListener **first,**last,**capacity;unsigned index;
 void forEach(void(Rva002BF33DListener::*)(void*),void*);
 ~Rva002BF33DList(){if(first)Rva00030830GameFree(first);}
};
class Rva00213A85 {public:void rva00213AB6();};
class LivingWorldManager;extern LivingWorldManager*TheLivingWorldManager;
class AudioManager;extern AudioManager*TheAudio;
class AudioSlots {public:
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();virtual void s04();virtual void s05();virtual void s06();virtual void s07();virtual void s08();virtual void s09();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();virtual void s20(int);virtual int s21();
};
struct Rva002BF6D6 {~Rva002BF6D6();char data[20];};
struct Rva002BF75A {~Rva002BF75A();char data[20];};
struct BfmePod16 {int a[4];};

namespace _STL {template<>BfmePod16*vector<BfmePod16>::erase(BfmePod16*,BfmePod16*); }
struct Rva002BF807 {unsigned words[2];_STL::vector<BfmePod16> records;char other[24];};
class Rva002BFB2D:public Rva002BF33DList,public Snapshot {
public:virtual ~Rva002BFB2D();
private:char pad14[20];Rva002BF807 member28;char pad54[68];Rva002BF6D6 hash98;Rva002BF75A hashac;
};
Rva002BFB2D::~Rva002BFB2D(){
 forEach(&Rva002BF33DListener::notify,this);
 if(TheLivingWorldManager)((Rva00213A85*)TheLivingWorldManager)->rva00213AB6();
 if(TheAudio&&((AudioSlots*)TheAudio)->s21()==1)((AudioSlots*)TheAudio)->s20(2);
 member28.records.clear();
}
