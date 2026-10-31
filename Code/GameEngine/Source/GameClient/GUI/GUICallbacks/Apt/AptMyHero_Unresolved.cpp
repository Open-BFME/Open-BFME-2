// cl: /O1 /G7 /MD /EHsc /arch:SSE2 /Ireference/shims/bfme2_ascii
// Split from AptMyHero.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Identity: WB AptMyHero.cpp names SwitchToPendingHero (assert line816),
// calls the same assignment/view/bling chain, and uses this+144/+148.
// Native005B1E71..005B1EE2 is the full113-byte standard-thiscall body.
// CreateAHeroData assignment and the 8-byte GetObjectInfo record are existing
// providers. The native self guard, flag handling and virtual slot14 are
// target facts. Unknown helper semantics and virtual names stay address views;
// their call declarations model witnessed noarg/one-dword ABIs only.
// No constructor, destructor or vtable layout beyond the used slots is claimed.
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
class Image;
class ImageCollection {public: const Image *findImageByName(const AsciiString &);};
extern ImageCollection *TheMappedImageCollection;
class BfmeAptWindowManager {public: void bfmeSetText(const AsciiString &,const UnicodeString &,bool);};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class GameTextInterface {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();virtual void slot14();
 virtual void slot18();virtual void slot1C();virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2C();
 virtual void slot30();virtual void slot34();
 virtual UnicodeString fetch(const AsciiString &label,bool *exists=0);
};
extern GameTextInterface *TheGameText;
// CreateAHeroData's bling value get/set pair, rowed under this owner.
class Rva00407E28 {public: int rva00407E28(int id);bool rva00407E53(int id);bool rva00407DE0(int id,int value);};
class CreateAHeroHero {public: void ConstructHeroBlingList();const class CommandButton *GetButtonForLevel(int);};
// A bling binder (20 bytes): its name key, the game-text label, and the
// slot and category it fills.
struct BlingBinder {int key;AsciiString label;int pad08;unsigned int slot;int category;};
struct BlingBinderList {unsigned int size() const {return last-first;}BlingBinder *first,*last,*capacity;};
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva0043DB23(Rva00222A8BTarget *,void *,const char *);
class AptPlayer {public: const Image *FindRenderImage(const char *,const char *);};
class Rva002239B2 {public: void rva002239E2(const AsciiString &,const Image *);};
// AptMyHero's base: vtable 0x00C38D88's five slots, the rowed assignment
// and destructor, and the fields the screen reads.
class CreateAHeroData {
public:
 virtual ~CreateAHeroData();
protected:
 virtual void loadPostProcess();
public:
 virtual const char *GetSnapshotName() const;
 virtual void DoXfer(class Xfer &);
 virtual bool Update(int);
 CreateAHeroData &operator=(const CreateAHeroData &);
protected:
 char pad04[4];
 UnicodeString heroName08;
 int field0C,field10;
 char pad14[0x138-0x14];
 const Image *image138;
 char pad13C[4];
};
// Native vector cleanup uses the game CRT allocator at00030830.
extern "C" void __cdecl free(void *) throw(...);
struct BfmePod8 {int a;float b;};
// The rowed by-value resize 0x005FF96A is spelled on this vector view.
class BfmePod8Vector {public: ~BfmePod8Vector(){if(first)free(first);}void resize(unsigned int,BfmePod8);unsigned int size() const {return last-first;}BfmePod8 *first,*last,*capacity;};
class Rva00406E47 {public: bool rva00406E47(int);};
struct Rva005B0473View {char opaque[0x60];float field60;int field64,field68;};
struct CreateAHeroClassRecord {char opaque[0x20];};
struct CreateAHeroClassList {unsigned int size() const {return last-first;}CreateAHeroClassRecord *first,*last,*capacity;};
class Rva002195E6;
class CreateAHeroManager {public: const Rva002195E6 *GetViewInfo(unsigned int,unsigned int);const AsciiString &GetClassNameTag(unsigned int);const AsciiString &GetSubClassNameTag(unsigned int,unsigned int);const AsciiString &GetBlingNameTag(int,const CreateAHeroHero *,unsigned int);int GetSubClassSpendableAttributePoints(unsigned int,unsigned int);void *GetBlingBinder(unsigned int);int GetBlingCount(int,const CreateAHeroHero *) const;int GetSubClassDefaultBlingId(int,unsigned int,unsigned int) const;int GetSubClassAttributeMinValue(unsigned int,unsigned int,unsigned int);int GetSubClassAttributeMaxValue(unsigned int,unsigned int,unsigned int);int GetSubClassAttributeDefaultValue(unsigned int,unsigned int,unsigned int);unsigned int GetClassCount() const {return classes14C.size();}char pad000[0x14C];CreateAHeroClassList classes14C;char pad158[0x168-0x158];BlingBinderList binders168;char pad174[0x1E8-0x174];AsciiString field1E8,field1EC;};
class Object;
class Drawable {public: char pad000[0xFC];Object *object;char pad100[4];Drawable *next;};
class GameClient {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();virtual void slot14();
 virtual void slot18();virtual void slot1C();virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2C();
 virtual void slot30();virtual void slot34();virtual void slot38();virtual void slot3C();virtual void slot40();
 virtual Drawable *firstDrawable();
};
extern GameClient *TheGameClient;
class Display {public: char pad000[0x141];bool field141;};
extern Display *TheDisplay;
class GameWindowTransitionsHandler {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();
 virtual void slot14();virtual void slot18();virtual void slot1C();virtual void slot20();virtual void slot24();
 bool isFinished();
 void reverse(AsciiString);
 void setGroup(AsciiString groupName,bool immediate);
};
extern GameWindowTransitionsHandler *TheTransitionHandler;
class Rva001DBB82OneSetter {public: void enable();};
class GameWindowManager {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();
 virtual void slot14();virtual void slot18();virtual void slot1C();virtual void slot20();virtual void slot24();virtual void slot28();
};
extern GameWindowManager *TheWindowManager;
extern CreateAHeroManager *TheCreateAHeroManager;
struct MyHeroBlingRecord {int field00,field04,minimum,maximum,field10;};
struct MyHeroBlingBlock {~MyHeroBlingBlock();MyHeroBlingRecord *first,*last,*capacity;};
int GetGameClientRandomValue(int,int,char *,int);
extern "C" __declspec(dllimport) char *__cdecl strstr(const char *,const char *);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *);
// The Object fields the location map reads; offsets are retail's.
class Object {public: char pad00[0x44];float field44;char pad48[0x74-0x48];int field74;char pad78[0x88-0x78];AsciiString name88;};
class CommandButton;
void __cdecl Rva005B24CDHeroPowerText(void *,const char *,int);
bool __cdecl rva005B2295(const CommandButton *button,const char *prefix,int index,int page);
class Rva00223A94 {public: int rva00223A94(const AsciiString *);};
class Rva005241DF {public: void rva005241DF(const StringBase<char> &);};
class Rva005B1830 {public: void rva005B1830();};
class Rva005B1A07 {public: void rva005B1B26(unsigned int);};
// Sun-direction helper views (retail 0x005B0A95): the WWMath Vector3/Vector4/
// Matrix3D inlines are carried from ZH's vector3.h/vector4.h/matrix3d.h shapes
// (axis-angle Set with cosf/sinf locals, mul via submul); Rotate_Vector is the
// out-of-line 0x00712030 row. View slots 0x78/0x100/0x108 and Display slot
// 0xB8 are the retail vtable offsets the body calls; GlobalData +0x920 is
// m_terrainLightPos[0].
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
inline float cosf(float _X){return ((float)cos((double)_X));}
inline float sinf(float _X){return ((float)sin((double)_X));}
class Vector3 {
public:
 float X,Y,Z;
 __forceinline Vector3(){}
 __forceinline Vector3(float x,float y,float z){X=x;Y=y;Z=z;}
 __forceinline Vector3(const Vector3 &vec){X=vec.X;Y=vec.Y;Z=vec.Z;}
 __forceinline Vector3 &operator=(const Vector3 &vec){X=vec.X;Y=vec.Y;Z=vec.Z;return *this;}
 __forceinline float &operator[](int i){return (&X)[i];}
 __forceinline const float &operator[](int i) const{return (&X)[i];}
 __forceinline Vector3 &operator*=(float k){X*=k;Y*=k;Z*=k;return *this;}
};
__forceinline Vector3 operator-(const Vector3 &a){return Vector3(-a.X,-a.Y,-a.Z);}
#include "../../../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"
__forceinline float submul(const Vector4 &row,float tmp1,float tmp2,float tmp3){return row.X*tmp1+row.Y*tmp2+row.Z*tmp3;}
class Matrix3D {
public:
 __forceinline Matrix3D(){}
 __forceinline Matrix3D(const Vector3 &axis,float angle){Set(axis,angle);}
 __forceinline void Set(const Vector3 &axis,float angle){float c=cosf(angle);float s=sinf(angle);Set(axis,s,c);}
 void Set(const Vector3 &axis,float s,float c);
 void mul(const Matrix3D &A,const Matrix3D &B);
 Vector3 Rotate_Vector(const Vector3 &vect) const;
 Vector4 Row[3];
};
__forceinline void Matrix3D::Set(const Vector3 &axis,float s,float c){
 Row[0].Set((float)(axis[0]*axis[0]+c*(1.0f-axis[0]*axis[0])),(float)(axis[0]*axis[1]*(1.0f-c)-axis[2]*s),(float)(axis[2]*axis[0]*(1.0f-c)+axis[1]*s),0.0f);
 Row[1].Set((float)(axis[0]*axis[1]*(1.0f-c)+axis[2]*s),(float)(axis[1]*axis[1]+c*(1.0f-axis[1]*axis[1])),(float)(axis[1]*axis[2]*(1.0f-c)-axis[0]*s),0.0f);
 Row[2].Set((float)(axis[2]*axis[0]*(1.0f-c)-axis[1]*s),(float)(axis[1]*axis[2]*(1.0f-c)+axis[0]*s),(float)(axis[2]*axis[2]+c*(1-axis[2]*axis[2])),0.0f);
}
__forceinline void Matrix3D::mul(const Matrix3D &matrix3D,const Matrix3D &B){
 float tmp1,tmp2,tmp3;
 tmp1=B.Row[0].X;tmp2=B.Row[1].X;tmp3=B.Row[2].X;
 Row[0].X=submul(matrix3D.Row[0],tmp1,tmp2,tmp3);Row[1].X=submul(matrix3D.Row[1],tmp1,tmp2,tmp3);Row[2].X=submul(matrix3D.Row[2],tmp1,tmp2,tmp3);
 tmp1=B.Row[0].Y;tmp2=B.Row[1].Y;tmp3=B.Row[2].Y;
 Row[0].Y=submul(matrix3D.Row[0],tmp1,tmp2,tmp3);Row[1].Y=submul(matrix3D.Row[1],tmp1,tmp2,tmp3);Row[2].Y=submul(matrix3D.Row[2],tmp1,tmp2,tmp3);
 tmp1=B.Row[0].Z;tmp2=B.Row[1].Z;tmp3=B.Row[2].Z;
 Row[0].Z=submul(matrix3D.Row[0],tmp1,tmp2,tmp3);Row[1].Z=submul(matrix3D.Row[1],tmp1,tmp2,tmp3);Row[2].Z=submul(matrix3D.Row[2],tmp1,tmp2,tmp3);
 tmp1=B.Row[0].W;tmp2=B.Row[1].W;tmp3=B.Row[2].W;
 Row[0].W=submul(matrix3D.Row[0],tmp1,tmp2,tmp3)+matrix3D.Row[0].W;Row[1].W=submul(matrix3D.Row[1],tmp1,tmp2,tmp3)+matrix3D.Row[1].W;Row[2].W=submul(matrix3D.Row[2],tmp1,tmp2,tmp3)+matrix3D.Row[2].W;
}
class View {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1C();
 virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2C();virtual void slot30();virtual void slot34();virtual void slot38();virtual void slot3C();
 virtual void slot40();virtual void slot44();virtual void slot48();virtual void slot4C();virtual void slot50();virtual void slot54();virtual void slot58();virtual void slot5C();
 virtual void slot60();virtual void slot64();virtual void slot68();virtual void slot6C();virtual void slot70();virtual void slot74();
 virtual bool slot78();
 virtual void slot7C();
 virtual void slot80();virtual void slot84();virtual void slot88();virtual void slot8C();virtual void slot90();virtual void slot94();virtual void slot98();virtual void slot9C();
 virtual void slotA0();virtual void slotA4();virtual void slotA8();virtual void slotAC();virtual void slotB0();virtual void slotB4();virtual void slotB8();virtual void slotBC();
 virtual void slotC0();virtual void slotC4();virtual void slotC8();virtual void slotCC();virtual void slotD0();virtual void slotD4();virtual void slotD8();virtual void slotDC();
 virtual void slotE0();virtual void slotE4();virtual void slotE8();virtual void slotEC();virtual void slotF0();virtual void slotF4();virtual void slotF8();
 virtual void setAngle(float);
 virtual float getAngle();
 virtual void setPitch(float);
 virtual float getPitch();
};
extern View *TheTacticalView;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct GlobalDataLightView {char pad000[0x920];Coord3D terrainLightPos0;};
// Coord3D::set is out of line in the canonical header; retail inlines the three stores.
__forceinline void SetLightPos(Coord3D *pos,float x,float y,float z){pos->x=x;pos->y=y;pos->z=z;}
class DisplayLightView {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1C();
 virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2C();virtual void slot30();virtual void slot34();virtual void slot38();virtual void slot3C();
 virtual void slot40();virtual void slot44();virtual void slot48();virtual void slot4C();virtual void slot50();virtual void slot54();virtual void slot58();virtual void slot5C();
 virtual void slot60();virtual void slot64();virtual void slot68();virtual void slot6C();virtual void slot70();virtual void slot74();virtual void slot78();virtual void slot7C();
 virtual void slot80();virtual void slot84();virtual void slot88();virtual void slot8C();virtual void slot90();virtual void slot94();virtual void slot98();virtual void slot9C();
 virtual void slotA0();virtual void slotA4();virtual void slotA8();virtual void slotAC();virtual void slotB0();virtual void slotB4();
 virtual void setLightDirection(const Vector3 *dir);
};
class W3DShadowManager;
extern W3DShadowManager *TheW3DShadowManager;
class W3DGameClientShadowShim {public:void setLightPosition(int,float,float,float);};
const AsciiString &rva005B0A53(const char *kind,int index);
class AptMyHero : public CreateAHeroData {
public:
 BfmePod8 *GetObjectInfo(int);
 virtual ~AptMyHero();
 virtual void slot14();
 void SwitchToPendingHero();
 void FrameUpdate();
 void rva005B21DA(CreateAHeroData *hero,bool flag,int mode);
 void rva005B0416(int);int rva005B0E60(const Object *);void rva005B1A6C();void rva005B0446();
 bool rva005B0725();
 void rva005B0923(int);void SetBling(int,int,int);void AdjustBling(int,int,int);
 Rva005B0473View *rva005B0473();
 void BuildBlingData();
 void rva005B0487();void rva005B1019();void rva005B1288();void rva005B097F(int);void rva005B0FCD(int);
 int rva005B0A95(int,int);
private:
 void *holder140;
 CreateAHeroData *pending144;
 bool flag148;
 char pad149[3];
 int field14C;
 bool flag150,flag151;char pad152[2];
 int availAttribPoints154;	// WorldBuilder: m_availAttribPoints
 int maxAttribPoints158;
 BfmePod8Vector mapObjectInfo15C;
 float field168,field16C;
 char pad170[4];
 MyHeroBlingBlock blocks174[2];
 int field18C;
};














const AsciiString &rva005B0A53(const char *kind,int index);


// AptMyHero::~AptMyHero, retail 0x005B190D..0x005B1A07 (250 bytes): drops
// the Base/Cur/Max attribute keys of five slots from the +0x140 holder's
// +0x228 registry, clears the Cah::Portrait image key, runs 0x005B1830,
// then the members (two bling vectors at +0x174, the location map at
// +0x15C) and the CreateAHeroData base are destroyed.
AptMyHero::~AptMyHero(){
 for(int i=0;i<5;++i){
  reinterpret_cast<Rva005241DF *>((char *)holder140+0x228)->rva005241DF(*(const StringBase<char> *)&rva005B0A53("Base",i));
  reinterpret_cast<Rva005241DF *>((char *)holder140+0x228)->rva005241DF(*(const StringBase<char> *)&rva005B0A53("Cur",i));
  reinterpret_cast<Rva005241DF *>((char *)holder140+0x228)->rva005241DF(*(const StringBase<char> *)&rva005B0A53("Max",i));
 }
 {
  AsciiString key("Cah::Portrait");
  reinterpret_cast<Rva00223A94 *>(g_bfmeAptWindowManager)->rva00223A94(&key);
 }
 reinterpret_cast<Rva005B1830 *>(this)->rva005B1830();
}

// FrameUpdate: WB AptMyHero::FrameUpdate names the transition polling, the
// DIK arrow-key handlers and the MyHeroName/Class/Type text refresh. Helper
// names below stay address views. The transition guard's ctor is defined in
// the class (retail still calls the rowed 0x0023C565 copy); its dtor inlines.
class Keyboard {public:bool rva00232643(unsigned char);};
extern Keyboard *TheKeyboard;
extern int BfmeLogicFramesPerSecond;
class Rva005B02B5 {public:void rva005B0249();void rva005B027F();void rva005B02B5();void rva005B02FD();};
// Same lock/unlock view as Rva0023C565Lock.cpp, so this unit's select-any ctor copy is retail's.
class Rva001DBAA4 {public:void lock();void unlock();};
class Rva0023C565 {
public: Rva0023C565(){if(TheTransitionHandler)reinterpret_cast<Rva001DBAA4 *>(TheTransitionHandler)->lock();}
 __forceinline ~Rva0023C565(){if(TheTransitionHandler)reinterpret_cast<Rva001DBAA4 *>(TheTransitionHandler)->unlock();}
};
void AptMyHero::FrameUpdate() {
 bool changed=false;
 switch(field14C) {
 case 1:
  if(TheTransitionHandler->isFinished()) {
   if(!field18C)SwitchToPendingHero();
   else if((unsigned)field18C >= (unsigned)(BfmeLogicFramesPerSecond+2)) {
    Rva0023C565 guard;
    const AsciiString &group=TheCreateAHeroManager->field1EC;
    if(!reinterpret_cast<const StringBase<char> &>(group).isEmpty()) {
     TheTransitionHandler->reverse(group);
     reinterpret_cast<Rva001DBB82OneSetter *>(TheTransitionHandler)->enable();
     TheWindowManager->slot28();
    }
    field14C=2;
   }
   ++field18C;
  }
  break;
 case 2:
  if(TheTransitionHandler->isFinished()) {
   TheTransitionHandler->slot24();TheWindowManager->slot28();field14C=0;TheDisplay->field141=false;
  }
  break;
 }
 if(TheKeyboard->rva00232643(0xCB)){reinterpret_cast<Rva005B02B5 *>(this)->rva005B0249();changed=true;}
 if(TheKeyboard->rva00232643(0xCD)){reinterpret_cast<Rva005B02B5 *>(this)->rva005B027F();changed=true;}
 if(TheKeyboard->rva00232643(0xC8)){reinterpret_cast<Rva005B02B5 *>(this)->rva005B02B5();changed=true;}
 if(TheKeyboard->rva00232643(0xD0)){reinterpret_cast<Rva005B02B5 *>(this)->rva005B02FD();changed=true;}
 if(changed)rva005B1019();
 if(flag150) {
  rva005B0446();
  if(!TheCreateAHeroManager)return;
  unsigned classIndex=field0C;unsigned subclassIndex=field10;
  {AsciiString key("APT:MyHeroName");g_bfmeAptWindowManager->bfmeSetText(key,heroName08,true);}
  {AsciiString key("APT:MyHeroClass");g_bfmeAptWindowManager->bfmeSetText(key,TheGameText->fetch(TheCreateAHeroManager->GetClassNameTag(classIndex)),true);}
  {AsciiString key("APT:MyHeroType");g_bfmeAptWindowManager->bfmeSetText(key,TheGameText->fetch(TheCreateAHeroManager->GetSubClassNameTag(classIndex,subclassIndex)),true);}

  flag150=false;flag151=true;
 }
 flag151=true;
 flag151=!rva005B0725();
}

// ~MyHeroBlingBlock: the call site in this unit's rows reads 0x0007FAB3 from retail, where the
// folded vector<int> destructor row lives. DoXfer and Update are slots 3 and 4 of retail's
// CreateAHeroData vftable (0x00C38D88: 0x00408C11 and 0x004083FF, spelled CreateAHeroHero in the
// ledger).
#pragma comment(linker, "/alternatename:??1MyHeroBlingBlock@@QAE@XZ=??1?$vector@HV?$allocator@H@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?DoXfer@CreateAHeroData@@UAEXAAVXfer@@@Z=?DoXfer@CreateAHeroHero@@QAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:?Update@CreateAHeroData@@UAE_NH@Z=?Update@CreateAHeroHero@@QAE_NH@Z")
