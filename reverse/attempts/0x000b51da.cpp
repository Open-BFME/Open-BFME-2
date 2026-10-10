// ?rva000B51DA@W3DModelDraw@@UAEXI@Z
// partial score=0.9430134237806334 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /Oy- /MD /DNDEBUG /I.
// Complete nativeB51DA..B52CD RET4,243B. Method name remains unknown.
// Class identity independently established by Draw interface table7CBB78:
// slot21 at7CBBCC points4B51DA; sibling slot4 is the owned1145B
// W3DModelDraw::getCurrentBonePositions. Same slot in7CBF08/7CC598.
// Secondary receiver is primary+0C; moduleData-8, drawable-4, flags+1C,
// animation override words+8/+C. ZH W3DModelDraw state/animation replacement
// is a semantic lead; BF2 compact16B state and hero preview extension are
// target facts. Neither original flags class name nor key type is asserted.
// Existing72B Rva78AE3 copy proves bit fields0..2/3..29/30 and words4/8/C;
// bit31 is preserved. Both direct helper names are already byte owned.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class CreateAHeroManager;extern CreateAHeroManager *TheCreateAHeroManager;
struct ModelHeroView {char head[0x184];bool flag184;};
class Rva000B4653 {public:void *rva000B4653(int);};
class Rva00078AE3 {public:
 unsigned count:3;unsigned middle:27;unsigned flag30:1;unsigned reserved31:1;
 unsigned word4,word8,wordC;
 Rva00078AE3 &rva00078AE3(const Rva00078AE3*);
 __forceinline bool same(const Rva00078AE3 &b)const {
  if(count!=b.count)return false;
  void *volatile a=((Rva000B4653*)this)->rva000B4653(0);
  void *right=((Rva000B4653*)&b)->rva000B4653(0);
  void *left=a;_ReadWriteBarrier();
  if(left!=right)return false;
  if(bool(flag30)!=bool(b.flag30))return false;return true;
 }

 __forceinline Rva00078AE3(unsigned key) {
  count=0;middle=0;flag30=0;word4=0;word8=0;wordC=0;
  if(key&0xFFFFFF) {count=1;middle=0;flag30=0;word4=key;word8=0;wordC=0;}
 }
};
struct ModelModuleView {char head[0x68];bool flag68;};
struct ModelTemplateView {char head[0x11C];unsigned flags11C;};
struct ModelObjectView {char head[4];ModelTemplateView *what;};
struct ModelDrawableView {char head[0xFC];ModelObjectView *object;};
class ModelPrimaryView {public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void s19();
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual void s31();
 virtual void s32();
 virtual void s33();
 virtual void s34();
 virtual void s35();
 virtual void s36();
 virtual void s37();
 virtual void s38();
 virtual void s39();
 virtual void s40();
 virtual void s41();
 virtual void s42();
 virtual void s43();
 virtual void s44();
 virtual void s45();
 virtual void s46();
 virtual void s47();
 virtual void s48();
 virtual int s49();
 virtual void s50();
 virtual void s51();
 virtual void s52();
 virtual void s53();
 virtual void s54();
 virtual void s55();
 virtual void s56();
 virtual void s57();
 virtual void s58();
 virtual void s59();
 virtual void s60();
 virtual void s61();
 virtual void s62();
 virtual void s63();
 virtual void s64(unsigned,unsigned,unsigned);
 ModelModuleView *data;ModelDrawableView *drawable;
};
class ModelDrawIface {public:
virtual void gap0();virtual void gap1();virtual void gap2();virtual void gap3();virtual void gap4();virtual void gap5();virtual void gap6();virtual void gap7();virtual void gap8();virtual void gap9();virtual void gap10();virtual void gap11();virtual void gap12();virtual void gap13();virtual void gap14();virtual void gap15();virtual void gap16();virtual void gap17();virtual void gap18();virtual void gap19();virtual void gap20();virtual void rva000B51DA(unsigned)=0;};
class W3DModelDraw:public ModelPrimaryView,public ModelDrawIface {public:
 unsigned unknown10,word14,word18,unknown1C[3];Rva00078AE3 state28;
 virtual void rva000B51DA(unsigned);
};
void W3DModelDraw::rva000B51DA(unsigned key) {
 if(!data->flag68)return;
 Rva00078AE3 next(key);
 ModelDrawableView *draw=drawable;
 ModelObjectView *object=draw?draw->object:0;
 if(object&&(object->what->flags11C&0x40000000)&&((ModelHeroView*)TheCreateAHeroManager)->flag184)next.flag30=1;
 Rva00078AE3 *current=&state28;
 if(current->same(next))return;
 current->rva00078AE3(&next);
 ModelPrimaryView *primary=this;
 if(primary->s49()) {
  unsigned first=word14,last=word18;
  word14=0;
  primary->s64(first,0,last);
 }
}
