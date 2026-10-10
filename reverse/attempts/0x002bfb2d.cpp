// ??1Rva002BFB2D@@UAE@XZ
// partial score=0.8256823821339949 date=2026-10-10
// cl: /O1 /G7 /EHs /EHc- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include "Common/Snapshot.h"
extern "C" void __cdecl free(void*);
class Rva002BF33DListener {public:virtual void notify(void*);};
struct Rva002BF33DList {
 Rva002BF33DListener **first,**last,**capacity;unsigned index;
 void forEach(void(Rva002BF33DListener::*)(void*),void*);
 ~Rva002BF33DList(){if(first)free(first);}
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
namespace _STL {template<>BfmePod16*vector<BfmePod16>::erase(BfmePod16*,BfmePod16*);}
struct RecordVectorStorage {BfmePod16*first,*last,*capacity;~RecordVectorStorage(){if(first)free(first);}};
class Rva002BFB2D:public Rva002BF33DList,public Snapshot {
public:virtual ~Rva002BFB2D();
private:char pad14[28];RecordVectorStorage records30;char pad3c[92];Rva002BF6D6 hash98;Rva002BF75A hashac;
};
Rva002BFB2D::~Rva002BFB2D(){
 forEach(&Rva002BF33DListener::notify,this);
 if(TheLivingWorldManager)((Rva00213A85*)TheLivingWorldManager)->rva00213AB6();
 if(TheAudio&&((AudioSlots*)TheAudio)->s21()==1)((AudioSlots*)TheAudio)->s20(2);
 ((_STL::vector<BfmePod16>*)&records30)->erase(records30.first,records30.last);
}
