// ??0Rva002E2903Player@@QAE@PAURva002BA8F1Input@@PAX@Z
// partial score=0.87 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include <vector>
#include <set>
#include <string.h>
class Rva00330757Member { public: Rva00330757Member(); ~Rva00330757Member(); char bytes[16]; };
struct Rva002BA8F1Input { char unknown00[36]; bool flag; };
class Rva002E0A0A { public: Rva002E0A0A(); Rva002E0A0A(const Rva002E0A0A&); ~Rva002E0A0A(); char bytes[40]; };
class Rva004FB3F2 { public: Rva004FB3F2(); ~Rva004FB3F2(); char bytes[308]; };
class Rva001EAE6FHelper { public: Rva001EAE6FHelper*clear80(); };
struct ClearStorage { char bytes[128]; ClearStorage(){ ((Rva001EAE6FHelper*)this)->clear80(); } };
class RefSlot {public:RefSlot(int x):value(x){}~RefSlot();int value;};
struct Color { float x,y,z; Color(float v):x(v),y(v),z(v){} };
class Rva000D1930 { public:Rva000D1930(); ~Rva000D1930();char bytes[28]; };
class Rva004EEADE { public:Rva004EEADE(int,Rva00330757Member*);~Rva004EEADE();char bytes[252]; };
class Rva002B317CBumpCounter {public:int bump();};
extern Rva002B317CBumpCounter *TheLivingWorldLogic;
class Rva002E2903Player : public Snapshot, public Rva00330757Member {
public:
 Rva002E2903Player(); Rva002E2903Player(Rva002BA8F1Input*,void*);
 virtual ~Rva002E2903Player();
 virtual void loadPostProcess(); virtual const char*GetSnapshotName()const; virtual void xfer(Xfer*);
 int id;
 Rva002E0A0A input;
 void *p40; int kind; RefSlot zero48;
 Rva004FB3F2 ai;
 int colorIndex;Color color1,color2,color3;
 _STL::vector<int> records;RefSlot zero1B4;
 _STL::vector<void*> armies;int zero1C4;float value1C8;
 _STL::vector<int> list1CC;
 ClearStorage storage;
 Rva000D1930 member258,member274;
 int zero290,zero294,zero298;
 _STL::set<int> set29C,set2A8;
 char zero2B4[16];int zero2C4;
 Rva004EEADE member2C8;
 bool flag3C4,flag3C5;
};
Rva002E2903Player::Rva002E2903Player()
 : id(-1),p40(0),kind(0),zero48(0),colorIndex(-1),color1(1.0f),color2(1.0f),color3(1.0f),zero1B4(0),zero1C4(0),value1C8(1.0f),zero290(0),zero294(0),zero298(0),zero2C4(0),member2C8(id,this),flag3C4(false),flag3C5(false)
 {memset(&storage,0,128);memset(zero2B4,0,16);}
Rva002E2903Player::Rva002E2903Player(Rva002BA8F1Input*src,void*context)
 : id(TheLivingWorldLogic->bump()),input(*(const Rva002E0A0A*)src),p40(context),kind(src->flag?2:0),zero48(0),colorIndex(-1),color1(1.0f),color2(1.0f),color3(1.0f),zero1B4(0),zero1C4(0),value1C8(1.0f),zero290(0),zero294(0),zero298(0),zero2C4(0),member2C8(id,this),flag3C4(false),flag3C5(false)
 {memset(&storage,0,128);memset(zero2B4,0,16);}
