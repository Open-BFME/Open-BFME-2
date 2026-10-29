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
 void setColor(int);
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
 AsciiString m_shadowTextureName;
 unsigned char unknown94[0x4e8-0x94];
 float sizeX,sizeY,offsetX,offsetY;
 unsigned char unknown4F8[8];
 float projectionX,projectionY;
 unsigned char unknown508[0x5e2-0x508];
 unsigned short m_shadowType;
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

class Rva000B3A80Animation
{
public:
 virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
 virtual int Get_Num_Frames();
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
 virtual void slot56();
 virtual void rva000B3A80();
 bool getRamp(BridgeInfo *, AsciiString, PolygonTrigger **, RenderObjClass **, bool);
 PolygonTrigger *getPolygon(RenderObjClass *mesh, float *out);
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
 char unknown5C[0x110-0x5c];
 Rva000B3A80Animation *animation110;
 float lastFrame114;
 float previousLastFrame118;
 char unknown11C[0x260-0x11c];
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

// Retail 0x000B3A80 (43 bytes), primary-table slot 57 after rva000B5FD5: with an animation
// at +0x110, keep the previous last-frame value (+0x114 -> +0x118) and store the animation's
// frame count minus one. Its original name is not recovered.
void W3DScriptedModelDraw::rva000B3A80()
{
 if (animation110)
 {
  previousLastFrame118 = lastFrame114;
  lastFrame114 = (float)(animation110->Get_Num_Frames() - 1);
 }
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
 AsciiString m_rampMesh2;
};

class Rva000BBFD6DrawInterface
{
public:
 bool rva000BBFD6(BridgeInfo *, PolygonTrigger **, RenderObjClass **, bool);
private:
 char unknown00[0x25C];
 AsciiString m_rampMesh2Override;
};

bool Rva000BBFD6DrawInterface::rva000BBFD6(BridgeInfo *info,
 PolygonTrigger **polygon, RenderObjClass **mesh, bool useObjectTransform)
{
 AsciiString name;
 if (!m_rampMesh2Override.isEmpty())
  name = m_rampMesh2Override;
 else
  name = (*reinterpret_cast<const Rva000BBFD6ModuleDataView *const *>(reinterpret_cast<const char *>(this) - 8))->m_rampMesh2;
 return reinterpret_cast<W3DScriptedModelDraw *>(reinterpret_cast<char *>(this) - 0xC)
  ->getRamp(info, name, polygon, mesh, useObjectTransform);
}

// NativeBBF55..BBFD6 RET16, the slot before BBFD6 in the same secondary
// table (complete-object+0C): the same query over the override string at
// complete-object264 with the module-data string at114 as fallback.
struct Rva000BBF55ModuleDataView
{
 char unknown00[0x114];
 AsciiString m_rampMesh1;
};

class Rva000BBF55DrawInterface
{
public:
 bool rva000BBF55(BridgeInfo *, PolygonTrigger **, RenderObjClass **, bool);
private:
 char unknown00[0x258];
 AsciiString m_rampMesh1Override;
};

bool Rva000BBF55DrawInterface::rva000BBF55(BridgeInfo *info,
 PolygonTrigger **polygon, RenderObjClass **mesh, bool useObjectTransform)
{
 AsciiString name;
 if (!m_rampMesh1Override.isEmpty())
  name = m_rampMesh1Override;
 else
  name = (*reinterpret_cast<const Rva000BBF55ModuleDataView *const *>(reinterpret_cast<const char *>(this) - 8))->m_rampMesh1;
 return reinterpret_cast<W3DScriptedModelDraw *>(reinterpret_cast<char *>(this) - 0xC)
  ->getRamp(info, name, polygon, mesh, useObjectTransform);
}

// NativeBAC53/BAD2B/BADE7/BAEBF (216/188/216/188 B, RET 4): four more slots
// of the same secondary table (complete-object+0C), the polygon twins of the
// ramp queries above. Each zeroes the output value, asks the render object
// (primary slot +0xC4) for the sub-object named by the override string at
// complete-object260 (falling back to the module-data string at10C) or
// directly by the module-data string at110, keeps that sub-object's mesh
// (its slot +0x14; a sub-object without one is released) and hands it to
// getPolygon (rowed B8440) or to the rowed B89E9 query.
class Rva000BAC53SubObject
{
public:
 virtual void Delete_This();
 virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
 virtual RenderObjClass *rva000BAC53Mesh();	// +0x14
 void Release_Ref() { if (--refs == 0) Delete_This(); }
 int refs;
};
template<int N> class Rva000BAC53Slots : public Rva000BAC53Slots<N-1> {
public: virtual void gap(char (*)[N]) = 0;
};
template<> class Rva000BAC53Slots<0> {};
class Rva000BAC53RenderView : public Rva000BAC53Slots<32> {
public: virtual Rva000BAC53SubObject *getSubObjectByName(const char *name, int flags) = 0;	// +0x80
};
class Rva000BAC53DrawView : public Rva000BAC53Slots<49> {
public: virtual Rva000BAC53RenderView *rva000BAC53Render() = 0;	// +0xC4
};
class PolygonTrigger;
class Rva000B8F5AOuter { public: int rva000B89E9(int mesh, float *out); };
struct Rva000BAC53ModuleDataView
{
 char unknown00[0x10C];
 AsciiString m_wallBoundsMesh;
 AsciiString m_raisedWallMesh;
};

class Rva000BAC53DrawInterface
{
public:
 PolygonTrigger *rva000BAC53(float *out);
 PolygonTrigger *rva000BAD2B(float *out);
 int rva000BADE7(float *out);
 int rva000BAEBF(float *out);
private:
 char unknown00[0x254];
 AsciiString m_wallBoundsMeshOverride;
};

#define BAC53_DRAW() reinterpret_cast<W3DScriptedModelDraw *>(reinterpret_cast<char *>(this) - 0xC)
#define BAC53_DATA() (*reinterpret_cast<const Rva000BAC53ModuleDataView *const *>(reinterpret_cast<const char *>(this) - 8))

PolygonTrigger *Rva000BAC53DrawInterface::rva000BAC53(float *out)
{
 W3DScriptedModelDraw *draw = BAC53_DRAW();
 Rva000BAC53RenderView *render = reinterpret_cast<Rva000BAC53DrawView *>(draw)->rva000BAC53Render();
 RenderObjClass *mesh = 0;
 *out = 0.0f;
 if (!render)
  return 0;
 {
  AsciiString name;
  if (!m_wallBoundsMeshOverride.isEmpty())
   name = m_wallBoundsMeshOverride;
  else
   name = BAC53_DATA()->m_wallBoundsMesh;
  Rva000BAC53SubObject *sub = render->getSubObjectByName(name.str(), 0);
  if (sub) {
   mesh = sub->rva000BAC53Mesh();
   if (!mesh)
    sub->Release_Ref();
  }
 }
 if (mesh)
  return draw->getPolygon(mesh, out);
 return 0;
}

PolygonTrigger *Rva000BAC53DrawInterface::rva000BAD2B(float *out)
{
 W3DScriptedModelDraw *draw = BAC53_DRAW();
 Rva000BAC53RenderView *render = reinterpret_cast<Rva000BAC53DrawView *>(draw)->rva000BAC53Render();
 RenderObjClass *mesh = 0;
 *out = 0.0f;
 if (!render)
  return 0;
 {
  AsciiString name;
  const Rva000BAC53ModuleDataView *data = BAC53_DATA();
  name = data->m_raisedWallMesh;
  Rva000BAC53SubObject *sub = render->getSubObjectByName(name.str(), 0);
  if (sub) {
   mesh = sub->rva000BAC53Mesh();
   if (!mesh)
    sub->Release_Ref();
  }
 }
 if (mesh)
  return draw->getPolygon(mesh, out);
 return 0;
}

int Rva000BAC53DrawInterface::rva000BADE7(float *out)
{
 W3DScriptedModelDraw *draw = BAC53_DRAW();
 Rva000BAC53RenderView *render = reinterpret_cast<Rva000BAC53DrawView *>(draw)->rva000BAC53Render();
 RenderObjClass *mesh = 0;
 *out = 0.0f;
 if (!render)
  return 0;
 {
  AsciiString name;
  if (!m_wallBoundsMeshOverride.isEmpty())
   name = m_wallBoundsMeshOverride;
  else
   name = BAC53_DATA()->m_wallBoundsMesh;
  Rva000BAC53SubObject *sub = render->getSubObjectByName(name.str(), 0);
  if (sub) {
   mesh = sub->rva000BAC53Mesh();
   if (!mesh)
    sub->Release_Ref();
  }
 }
 if (mesh)
  return reinterpret_cast<Rva000B8F5AOuter *>(draw)->rva000B89E9((int)mesh, out);
 return 0;
}

int Rva000BAC53DrawInterface::rva000BAEBF(float *out)
{
 W3DScriptedModelDraw *draw = BAC53_DRAW();
 Rva000BAC53RenderView *render = reinterpret_cast<Rva000BAC53DrawView *>(draw)->rva000BAC53Render();
 RenderObjClass *mesh = 0;
 *out = 0.0f;
 if (!render)
  return 0;
 {
  AsciiString name;
  const Rva000BAC53ModuleDataView *data = BAC53_DATA();
  name = data->m_raisedWallMesh;
  Rva000BAC53SubObject *sub = render->getSubObjectByName(name.str(), 0);
  if (sub) {
   mesh = sub->rva000BAC53Mesh();
   if (!mesh)
    sub->Release_Ref();
  }
 }
 if (mesh)
  return reinterpret_cast<Rva000B8F5AOuter *>(draw)->rva000B89E9((int)mesh, out);
 return 0;
}
#undef BAC53_DRAW
#undef BAC53_DATA

void W3DScriptedModelDraw::allocateShadows()
{
 const Rva000B9B4ATemplatePrefix *thingTemplate=drawable8->thing4;
 if(!shadow58 && render50 && TheW3DShadowManager && thingTemplate->m_shadowType) {
  Shadow::ShadowTypeInfo info;
  reinterpret_cast<StringBase<char> *>(&info.first)->set(*reinterpret_cast<const StringBase<char> *>(&thingTemplate->m_shadowTextureName));
  info.flags[1]=0;
  info.flags[2]=1;
  info.type=thingTemplate->m_shadowType;
  info.sizeX=thingTemplate->sizeX;
  info.sizeY=thingTemplate->sizeY;
  info.offsetX=thingTemplate->offsetX;
  info.offsetY=thingTemplate->offsetY;
  info.projectionX=thingTemplate->projectionX;
  info.projectionY=thingTemplate->projectionY;
  info.flags[0]=thingTemplate->flag5ED;
  shadow58=TheW3DShadowManager->addShadow(render50,&info,0);
  if(shadow58) {
   shadow58->shadowFlag30=thingTemplate->flag5EF;
   if(thingTemplate->color5EE) shadow58->setColor(reinterpret_cast<int>(colors28.rva000B4653(0)));
   shadow58->enableShadowInvisible(fullyObscured49);
   if(reinterpret_cast<Rva000B9B4ARenderView *>(render50)->Is_Hidden() || !shadowEnabled4A)
    shadow58->enableShadowRender(false);
  }
 }
}
