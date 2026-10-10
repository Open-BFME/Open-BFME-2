// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// The byte-proven constructor C0DD8 installs primary table7CA090 and
// constructs a string at260 followed by two strings at264. Slots54/55
// point to B5FBE/B5FD5. This is the primary object, without an adjustment.
// WB948160 names SetRampMeshOverload and indexes the264 array. Its old
// vtable pairing to B5FD5 contradicts RET8 versus RET0: nativeB5FBE is
// the indexed setter. The query's original name and return spelling stay
// unknown; retain an address name and the observed full EAX integer ABI.
#include "ascii_string.h"
template<> void StringBase<char>::set(const char *);
template<> bool StringBase<char>::isEmpty() const;

class BridgeInfo;
class PolygonTrigger;
class RenderObjClass;


// allocateShadows: native B9B4A..B9C8C, complete322B RET0/EH.
// Identity/behavior: WB9292C0 names W3DScriptedModelDraw::allocateShadows;
// verified BF1 donor575 W3DModelDraw::allocateShadows supplies the shadow
// allocation flow. Target differs in its two-string40B ShadowTypeInfo,
// six float fields, optional color and two additional flags. Target native
// accesses establish every offset below; the padding and full class extents
// remain unknown. These receiver-prefix views never allocate those owners.
// The existing draw view is extended in place; all original siblings remain.
// Shadow ctor79514/dtor793FA and manager9A8D3 are now genuinely recovered
// under their correct names (the old AudioEventRTS names were refuted).
// Use the data-ledger canonical TheW3DShadowManager at VADE5DFC; the
// old g_shadowManager spelling is a separate datum. No pin or alias added.
class Shadow {
public:
 struct ShadowTypeInfo {
  ShadowTypeInfo(); ~ShadowTypeInfo();
  AsciiString first,second;
  int type;
  float sizeX,sizeY,offsetX,offsetY,projectionX,projectionY;
  unsigned char flags[4];
 };
 void rva00330995(int);
 __forceinline void enableShadowRender(bool value) { enabled=value; }
 __forceinline void enableShadowInvisible(bool value) { invisible=value; }
 unsigned int vptr00;
 bool enabled,invisible;
 unsigned char unknown06[0x30-6];
 unsigned char shadowFlag30;
};
class Drawable;
class W3DShadowManager {
public: Shadow *addShadow(RenderObjClass *,Shadow::ShadowTypeInfo *,Drawable *);
};
extern W3DShadowManager *TheW3DShadowManager;
struct Rva000B9B4ATemplatePrefix {
 unsigned char unknown00[0x90];
 AsciiString name90;
 unsigned char unknown94[0x4e8-0x94];
 float sizeX,sizeY,offsetX,offsetY;
 unsigned char unknown4F8[8];
 float projectionX,projectionY;
 unsigned char unknown508[0x5e2-0x508];
 unsigned short type5E2;
 unsigned char unknown5E4[9];
 unsigned char flag5ED,color5EE,flag5EF;
};
struct Rva000B9B4ADrawablePrefix {
 unsigned int vptr00;
 const Rva000B9B4ATemplatePrefix *thing4;
};
class Rva000B4653 {
public: void *rva000B4653(int);
 unsigned int count;
};
template<int N> struct Rva000B9B4ASlotTag;
template<int N> class Rva000B9B4ASlots : public Rva000B9B4ASlots<N-1> {
public: virtual void unused(Rva000B9B4ASlotTag<N> *);
};
template<> class Rva000B9B4ASlots<0> {};
class Rva000B9B4ARenderView : public Rva000B9B4ASlots<100> {
public: virtual int Is_Hidden() const;
};

class W3DScriptedModelDraw
{
public:
#define SLOT(N) virtual void slot##N();
 SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
 SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
 virtual void allocateShadows();
 SLOT(15)
 SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
 SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
 SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
 SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
 SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53)
#undef SLOT
 virtual void SetRampMeshOverload(const char *name, int index);
 virtual int rva000B5FD5();
 bool getRamp(BridgeInfo *, AsciiString, PolygonTrigger **, RenderObjClass **, bool);
private:
 char unknown04[4];
 Rva000B9B4ADrawablePrefix *drawable8;
 char unknown0C[0x28-0x0c];
 Rva000B4653 colors28;
 char unknown2C[0x49-0x2c];
 bool fullyObscured49,shadowEnabled4A;
 char unknown4B[0x50-0x4b];
 RenderObjClass *render50;
 char unknown54[4];
 Shadow *shadow58;
 char unknown5C[0x260-0x5c];
 StringBase<char> string260;
 StringBase<char> rampNames[2];
};

void W3DScriptedModelDraw::SetRampMeshOverload(const char *name, int index)
{
 rampNames[index].set(name);
}

int W3DScriptedModelDraw::rva000B5FD5()
{
 return !string260.isEmpty();
}

// NativeBBFD6..BC057 RET16. Secondary-table7CC588 slot43 is shared by
// ScriptedModelDraw/Truck/Tank interfaces; this is complete-object+0C.
// The recovered getRamp B9EC2 proves the forwarded pointer/output/flag ABI.
// ConstructorC0DD8 proves the override string at complete-object268. The
// fallback module-data string at118 is observed here; its original name
// and this callback's original name remain unresolved.
struct Rva000BBFD6ModuleDataView
{
 char unknown00[0x118];
 AsciiString string118;
};

class Rva000BBFD6DrawInterface
{
public:
 bool rva000BBFD6(BridgeInfo *, PolygonTrigger **, RenderObjClass **, bool);
private:
 char unknown00[0x25C];
 AsciiString string25C;
};

bool Rva000BBFD6DrawInterface::rva000BBFD6(BridgeInfo *info,
 PolygonTrigger **polygon, RenderObjClass **mesh, bool useObjectTransform)
{
 AsciiString name;
 if (!string25C.isEmpty())
  name = string25C;
 else
  name = (*reinterpret_cast<const Rva000BBFD6ModuleDataView *const *>(reinterpret_cast<const char *>(this) - 8))->string118;
 return reinterpret_cast<W3DScriptedModelDraw *>(reinterpret_cast<char *>(this) - 0xC)
  ->getRamp(info, name, polygon, mesh, useObjectTransform);
}

void W3DScriptedModelDraw::allocateShadows()
{
 const Rva000B9B4ATemplatePrefix *t=drawable8->thing4;
 if(!shadow58 && render50 && TheW3DShadowManager && t->type5E2) {
  Shadow::ShadowTypeInfo info;
  reinterpret_cast<StringBase<char> *>(&info.first)->set(*reinterpret_cast<const StringBase<char> *>(&t->name90));
  info.flags[1]=0;
  info.flags[2]=1;
  info.type=t->type5E2;
  info.sizeX=t->sizeX;
  info.sizeY=t->sizeY;
  info.offsetX=t->offsetX;
  info.offsetY=t->offsetY;
  info.projectionX=t->projectionX;
  info.projectionY=t->projectionY;
  info.flags[0]=t->flag5ED;
  shadow58=TheW3DShadowManager->addShadow(render50,&info,0);
  if(shadow58) {
   shadow58->shadowFlag30=t->flag5EF;
   if(t->color5EE) shadow58->rva00330995(reinterpret_cast<int>(colors28.rva000B4653(0)));
   shadow58->enableShadowInvisible(fullyObscured49);
   if(reinterpret_cast<Rva000B9B4ARenderView *>(render50)->Is_Hidden() || !shadowEnabled4A)
    shadow58->enableShadowRender(false);
  }
 }
}
