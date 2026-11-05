// cl: /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// W3DShrubBuffer::DoXfer; nativeE96B4..E9BAC full1272B RET4.
// Primary semantic guide: verified BF1 f98983a7 ZH W3DTreeBuffer.cpp xfer.
// WB898B00 names BFME2 DoXfer and proves version2 type-table extension.
// Retail's Coord3D is the non-POD class (Lib/Coord3DCtorView.h, which takes Coord3D.h's guard); the
// string compares call StringBase<char>::compareNoCase directly (arguments before the receiver).
// Target: short partition array5C0/2500 entries; distinct16B bounds1948;
// 2000 records of160B at1958;64 types of92B at4FB70. Unknown fields stay
// typed offset views. Copy301 and its31B Region2D callee only load/store,
// so the scratch copy-constructor view is declared nonthrowing. Its original
// construction-versus-assignment identity remains a repair concern.
#include "Lib/Coord3DCtorView.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"
#include "vector3.h"
#include "matrix3d.h"
#include "sphere.h"

// Retail's global at 0x012ED5C8 is EA's GlobalData *TheWritableGlobalData, defined
// once in Common/GlobalData.cpp. Only the field this body reads is described on a
// TU-local view; the real class is never redeclared.
class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva000E91CEData
{
	unsigned char prefix[8];
	AsciiString modelName, nameC;
	unsigned int framesToMoveOutward;
	unsigned char gap14[0x3d - 0x14];
	bool doTopple;
	unsigned char gap3e[0x48 - 0x3e];
	AsciiString name48;
	unsigned char gap4c[8];
	bool flag54;
};

struct Rva000E91CEType
{
public:
	void *mesh; // +0x00
	Vector3 offset; // +0x04
	SphereClass bounds; // +0x10
	const Rva000E91CEData *data; // +0x20
	unsigned char gap24[0x44 - 0x24]; // +0x24
	bool shadowKind; // +0x44
	unsigned char alignment45[3]; // +0x45
	AsciiString textureName; // +0x48
	AsciiString modelName; // +0x4C
	AsciiString nameC; // +0x50
	AsciiString templateName; // +0x54
	int field58; // +0x58
};

struct Rva000E91CETree
{
	Vector3 location;
	float scale;
	Matrix3D transform;
	int treeType;
	bool visible;
	bool flag45;
	bool flag46;
	unsigned char alignment47;
	SphereClass bounds;
	unsigned int drawableID;
	float pushAside;
	float pushAsideDelta;
	float pushAsideSin;
	float pushAsideCos;
	unsigned int pushAsideSource;
	unsigned int lastFrame;
	int nextInPartition;
	int swayType;
	int firstIndex;
	int bufferIndex;
	int toppleState;
	int uprightType;
	int toppledType;
	unsigned int sinkFrames;
	void *toppleObject;
	void *pushAsideObject;
	int fielda0;
};

extern float GetGameClientRandomValueReal(float, float, char *, int);
extern int GetGameClientRandomValue(int, int, char *, int);

static inline void translateBounds(Vector3 &center, const Vector3 &position)
{
	// Preserve the observed x87 load order for this alias-sensitive aggregate update.
	const volatile float &x = position.X;
	center.X += x;
	center.Y = position.Y + center.Y;
	center.Z = position.Z + center.Z;
}

struct FloatPair
{
	float x;
	float y;
};


#include <string.h>
#define __PLACEMENT_VEC_NEW_INLINE
#include <new>

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;

#include "../../../../GameEngine/Include/Common/BfmeXfer.h"
class Xfer::Version { public: unsigned char minimum,current; Version(unsigned char a,unsigned char b):minimum(a),current(b){} };
class Rva000E63DCObj;void __stdcall Rva000E63DCDo(Rva000E63DCObj *);
void Rva0030612AXfer(Xfer *,float *);
Xfer *Rva003062FEXfer(Xfer *,float *);
void XferDrawableID(Xfer *,int *);
class ThingTemplate; class ThingFactory {public:const ThingTemplate*findTemplate(const AsciiString&);};extern ThingFactory *TheThingFactory;
class ModuleData {public:
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();virtual void s04();virtual void s05();virtual void s06();virtual void s07();
 virtual void s08();virtual void s09();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();
 virtual const Rva000E91CEData *TreeDrawData()const;
};
#include "../../../../GameEngine/Include/Common/ModuleInfoClass.h"
#include "../../../../GameEngine/Include/Common/XferException.h"
class RenderObjClass {public:
 virtual void Delete_This();virtual void s01();virtual void s02();virtual int Class_ID()const;virtual void s04();virtual void *MeshView()const;
 int refs;
 void Release_Ref(){if(--refs==0)Delete_This();}
};
RenderObjClass *Create_Render_Obj(const char *);
__forceinline Coord3D shrubPosition(const Vector3 &position) { Coord3D pos; pos.x=position.X;pos.y=position.Y;pos.z=position.Z;return pos; }
class Rva000E771B {public:Rva000E771B();char body[0xA0];};
struct Rva000E73FC {Rva000E73FC(const Rva000E73FC &) throw();char body[0xA0];};

class W3DShrubBuffer
{
public:
 void DoXfer(Xfer *);
	int addTreeType(const AsciiString &, const AsciiString &, const void *, int, const AsciiString &, const AsciiString &);
	int rva000E8F9D(const AsciiString &, int, const AsciiString &);
	void addShrub(unsigned int id, Coord3D location, float scale, const Matrix3D *transform, float randomScaleAmount,
		const Rva000E91CEData *data, int shadowKind, const AsciiString &textureName, const AsciiString &nameD);
	int getPartitionBucket(const FloatPair *location);

private:
	unsigned char prefix[0x5c0];
	short areaPartition[2500];
 float bounds1948[4];
	Rva000E91CETree trees[2000];
	int numTrees;
	unsigned char gap4[2];
	bool changed;
	unsigned char gap7[0xd];
	bool initialized;
	unsigned char gap15[1];
	bool needUpdate;
	unsigned char gap17[1];
	Rva000E91CEType types[64];
	int numTypes;
};

// ZH W3DTreeBuffer::xfer supplies save/load purpose. WB898B00 names BFME2
// DoXfer; nativeE96B4..E9BAC adds type-table version2 and shadow version3.
void W3DShrubBuffer::DoXfer(Xfer *xfer)
{
 int i;
 Rva000E63DCDo(reinterpret_cast<Rva000E63DCObj *>(xfer));
 if(xfer->IsLightCRC()||xfer->IsCRC())return;
 Xfer::Version version(1,3);(*xfer == version);
 int count=numTrees;(*xfer == count);
 if(version.current>=2){
  (*xfer == numTypes);
  for(i=0;i<numTypes;++i){
   Rva000E91CEType &shrubType=types[i];
   Rva0030612AXfer(xfer,reinterpret_cast<float *>(&shrubType.offset));
   Rva0030612AXfer(xfer,reinterpret_cast<float *>(&shrubType.bounds));
   (*xfer == shrubType.bounds.Radius);
   (*xfer == *reinterpret_cast<Coord2D *>(shrubType.gap24));(*xfer == *reinterpret_cast<Coord2D *>(shrubType.gap24+8));(*xfer == *reinterpret_cast<Coord2D *>(shrubType.gap24+16));(*xfer == *reinterpret_cast<Coord2D *>(shrubType.gap24+24));
   (*xfer == shrubType.shadowKind);
   (*xfer == shrubType.textureName);(*xfer == shrubType.modelName);(*xfer == shrubType.nameC);(*xfer == shrubType.field58);(*xfer == shrubType.templateName);
   if(xfer->IsLoading()){
    shrubType.data=0;

    if(const ThingTemplate *tt=TheThingFactory->findTemplate(shrubType.templateName)){ModuleInfo *mi=reinterpret_cast<ModuleInfo *>(const_cast<char *>(reinterpret_cast<const char *>(tt))+0x2F0);const ModuleData *module=mi->getNthData(0);if(module)shrubType.data=module->TreeDrawData();}
    if(!shrubType.data)throw XferException(4,0);
    if(shrubType.mesh){reinterpret_cast<RenderObjClass *>(shrubType.mesh)->Release_Ref();shrubType.mesh=0;}
    RenderObjClass *render=Create_Render_Obj(shrubType.modelName.str());
    if(render){if(render->Class_ID()==0)shrubType.mesh=render->MeshView();else render->Release_Ref();}
   }
  }
 }
 if(xfer->IsLoading()){
  numTrees=0;for(i=0;i<2500;++i)areaPartition[i]=-1;
 }
 for(i=0;i<count;++i){
  Rva000E771B buffer;
  memset(&buffer,0,sizeof(buffer));
  Rva000E91CETree &tree=*reinterpret_cast<Rva000E91CETree *>(&buffer);
  AsciiString modelName,modelTexture;
  int treeType=-2;
  if(xfer->IsStoring()){
   new(&buffer) Rva000E73FC(*reinterpret_cast<const Rva000E73FC *>(&trees[i]));
   treeType=trees[i].treeType;
   _ReadWriteBarrier();
   if(treeType!=-2){modelName=types[treeType].data->modelName;modelTexture=types[treeType].data->nameC;}
  }
  (*xfer == modelName);(*xfer == modelTexture);
  if(xfer->IsLoading()){
   for(int j=0;j<numTypes;++j){
    if(((const StringBase<char> *)&types[j].data->modelName)->compareNoCase(*(const StringBase<char> *)&modelName)==0 &&((const StringBase<char> *)&types[j].data->nameC)->compareNoCase(*(const StringBase<char> *)&modelTexture)==0){treeType=j;break;}
   }
  }
  (*xfer == tree.location.X);(*xfer == tree.location.Y);(*xfer == tree.location.Z);(*xfer == tree.scale);
  Rva003062FEXfer(xfer,reinterpret_cast<float *>(&tree.transform));
  XferDrawableID(xfer,reinterpret_cast<int *>(&tree.drawableID));
  bool shadow=false;
  AsciiString textureName;
  if(!xfer->IsLoading()&&treeType>=0&&treeType<numTypes){shadow=types[treeType].shadowKind;textureName=types[treeType].textureName;}
  (*xfer == shadow);(*xfer == textureName);(*xfer == *reinterpret_cast<Region2D *>(bounds1948));
  if(xfer->IsLoading()&&treeType>=0&&treeType<numTypes){
   Coord3D pos;pos.x=tree.location.X;pos.y=tree.location.Y;pos.z=tree.location.Z;
   AsciiString nameD("");
   addShrub(tree.drawableID,pos,tree.scale,&tree.transform,0,types[treeType].data,shadow?1:0,textureName,nameD);
  }
 }
}
