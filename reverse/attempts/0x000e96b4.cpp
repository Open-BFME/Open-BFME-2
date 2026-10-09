// ?DoXfer@W3DShrubBuffer@@QAEXPAVXfer@@@Z
// partial score=0.8 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Banked DoXfer reconstruction; nativeE96B4..E9BAC full1272B RET4.
// Primary semantic guide: verified BF1 f98983a7 ZH W3DTreeBuffer.cpp xfer.
// WB898B00 names BFME2 DoXfer and proves version2 type-table extension.
// Target: short partition array5C0/2500 entries; distinct16B bounds1948;
// 2000 records of160B at1958;64 types of92B at4FB70. Unknown fields stay
// typed offset views. Copy301 and its31B Region2D callee only load/store,
// so the scratch copy-constructor view is declared nonthrowing. Its original
// construction-versus-assignment identity remains a repair concern.
#include "ascii_string.h"
#include "vector3.h"
#include "matrix3d.h"
#include "sphere.h"

#include "../../Code/Libraries/Include/Lib/Coord3D.h"

// Retail's global at 0x012ED5C8 is EA's GlobalData *TheWritableGlobalData, defined
// once in Common/GlobalData.cpp. Only the field this body reads is described on a
// TU-local view; the real class is never redeclared.
class GlobalData;
struct Rva000E91CEGlobalData
{
	unsigned char m_pad00[0x1c];
	bool m_flag1c;
};

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
	void *mesh;
	Vector3 offset;
	SphereClass bounds;
	const Rva000E91CEData *data;
	unsigned char gap24[0x44 - 0x24];
 bool shadowKind; unsigned char alignment45[3];
 AsciiString textureName,modelName,nameC,templateName;
	int field58;
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

struct ShrubVersion { unsigned char minimum,current; ShrubVersion(unsigned char a,unsigned char b):minimum(a),current(b){} };
class Xfer { public:
 virtual ~Xfer();
 virtual bool IsLoading()const; virtual bool IsStoring()const; virtual bool IsCRC()const; virtual bool IsLightCRC()const;
 virtual void s05();virtual void s06();virtual void s07();virtual void s08();virtual void s09();
 virtual void Version(ShrubVersion *);
 virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();
 virtual void Bounds(float *);virtual void s19();virtual void RawPair(void *);
 virtual void s21();virtual void s22();virtual void s23();virtual void s24();virtual void s25();virtual void s26();
 virtual void String(AsciiString *);virtual void Real(float *);virtual void s29();virtual void s30();virtual void Int(int *);
 virtual void s32();virtual void s33();virtual void s34();virtual void s35();virtual void Bool(bool *);
};
class Rva000E63DCObj;void __stdcall Rva000E63DCDo(Rva000E63DCObj *);
void Rva0030612AXfer(Xfer *,float *);
void Rva003062FEXfer(Xfer *,float *);
void XferDrawableID(Xfer *,int *);
class Rva002D06CA {public:void *rva002D06CA(const AsciiString *);};
class ThingFactory;extern ThingFactory *TheThingFactory;
class ModuleData {public:
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();virtual void s04();virtual void s05();virtual void s06();virtual void s07();
 virtual void s08();virtual void s09();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();
 virtual const Rva000E91CEData *TreeDrawData()const;
};
class ModuleInfo {public:const ModuleData *getNthData(int)const;};
class XferException {public:XferException(int,const char *,...);XferException(const XferException &);~XferException();char *text;int tag;};
class RenderObjClass {public:
 virtual void Delete_This();virtual void s01();virtual void s02();virtual int Class_ID()const;virtual void s04();virtual void *MeshView()const;
 int refs;
 void Release_Ref(){if(--refs==0)Delete_This();}
};
RenderObjClass *Create_Render_Obj(const char *);
__forceinline Coord3D shrubPosition(const Vector3 &p) { Coord3D r; r.x=p.X;r.y=p.Y;r.z=p.Z;return r; }
class Rva000E771B {public:Rva000E771B();char body[0xA0];};
struct Rva000E73FC {Rva000E73FC(const Rva000E73FC &) throw();char body[0xA0];};

class W3DShrubBuffer
{
public:
 void DoXfer(Xfer *);
	int addTreeType(const AsciiString &, const AsciiString &, const void *, int, const AsciiString &, const AsciiString &);
	int rva000E8F9D(const AsciiString &, int, const AsciiString &);
	void rva000E91CE(unsigned int id, Coord3D location, float scale, const Matrix3D *transform, float randomScaleAmount,
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
 Rva000E63DCDo(reinterpret_cast<Rva000E63DCObj *>(xfer));
 if(xfer->IsLightCRC()||xfer->IsCRC())return;
 ShrubVersion version(1,3);xfer->Version(&version);
 int count=numTrees;xfer->Int(&count);
 if(version.current>=2){
  xfer->Int(&numTypes);
  for(int i=0;i<numTypes;++i){
   Rva000E91CEType &t=types[i];
   Rva0030612AXfer(xfer,reinterpret_cast<float *>(&t.offset));
   Rva0030612AXfer(xfer,reinterpret_cast<float *>(&t.bounds));
   xfer->Real(&t.bounds.Radius);
   xfer->RawPair(t.gap24);xfer->RawPair(t.gap24+8);xfer->RawPair(t.gap24+16);xfer->RawPair(t.gap24+24);
   xfer->Bool(&t.shadowKind);
   xfer->String(&t.textureName);xfer->String(&t.modelName);xfer->String(&t.nameC);xfer->Int(&t.field58);xfer->String(&t.templateName);
   if(xfer->IsLoading()){
    t.data=0;
    void *tmpl=reinterpret_cast<Rva002D06CA *>(TheThingFactory)->rva002D06CA(&t.templateName);
    if(tmpl){const ModuleData *module=reinterpret_cast<ModuleInfo *>(static_cast<char *>(tmpl)+0x2F0)->getNthData(0);if(module)t.data=module->TreeDrawData();}
    if(!t.data)throw XferException(4,0);
    if(t.mesh){reinterpret_cast<RenderObjClass *>(t.mesh)->Release_Ref();t.mesh=0;}
    RenderObjClass *render=Create_Render_Obj(t.modelName.str());
    if(render){if(render->Class_ID()==0)t.mesh=render->MeshView();else render->Release_Ref();}
   }
  }
 }
 if(xfer->IsLoading()){
  numTrees=0;for(int i=0;i<2500;++i)areaPartition[i]=-1;
 }
 for(int i=0;i<count;++i){
  Rva000E771B buffer;
  memset(&buffer,0,sizeof(buffer));
  Rva000E91CETree &tree=*reinterpret_cast<Rva000E91CETree *>(&buffer);
  AsciiString modelName,modelTexture;
  int treeType=-2;
  if(xfer->IsStoring()){
   new(&buffer) Rva000E73FC(*reinterpret_cast<const Rva000E73FC *>(&trees[i]));
   treeType=tree.treeType;
   if(treeType!=-2){modelName=types[treeType].data->modelName;modelTexture=types[treeType].data->nameC;}
  }
  xfer->String(&modelName);xfer->String(&modelTexture);
  if(xfer->IsLoading()){
   for(int j=0;j<numTypes;++j){
    if(types[j].data->modelName.compareNoCase(modelName)==0 &&types[j].data->nameC.compareNoCase(modelTexture)==0){treeType=j;break;}
   }
  }
  xfer->Real(&tree.location.X);xfer->Real(&tree.location.Y);xfer->Real(&tree.location.Z);xfer->Real(&tree.scale);
  Rva003062FEXfer(xfer,reinterpret_cast<float *>(&tree.transform));
  XferDrawableID(xfer,reinterpret_cast<int *>(&tree.drawableID));
  AsciiString textureName;
  bool shadow=false;
  if(!xfer->IsLoading()&&treeType>=0&&treeType<numTypes){shadow=types[treeType].shadowKind;textureName=types[treeType].textureName;}
  xfer->Bool(&shadow);xfer->String(&textureName);xfer->Bounds(bounds1948);
  if(xfer->IsLoading()&&treeType>=0&&treeType<numTypes){
   Coord3D pos;pos.x=tree.location.X;pos.y=tree.location.Y;pos.z=tree.location.Z;
   AsciiString nameD("");
   rva000E91CE(tree.drawableID,shrubPosition(tree.location),tree.scale,&tree.transform,0,types[treeType].data,shadow?1:0,textureName,nameD);
  }
 }
}
