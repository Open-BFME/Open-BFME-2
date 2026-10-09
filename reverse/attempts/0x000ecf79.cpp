// ?rva000ECF79@W3DTreeBuffer@@QAEXIURva000ECF79Coord@@MPBVMatrix3D@@MPBURva000ECF79Data@@HABVAsciiString@@3@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/shims/stringinline
// W3DTreeBuffer::addTree, retail 0x000ECF79 (1284 bytes). Donor: Open-BFME-1
// W3DTreeBufferRva000ECF79AddTree.cpp (BFME1 0x00736B60); BFME2 layout read from
// retail: 1200 tree records of 0xE8 at +0x5C0 (count +0x44540, dirty byte
// +0x44545, initialized +0x44554, type-added flag +0x44556), 64 types of 0x5C at
// +0x44558 (count +0x45C58).
#include "StringInline.h"
#include "vector3.h"
#include "matrix3d.h"
#include "sphere.h"
struct Rva000ECF79Coord { float x,y,z; };
struct Rva000ECF79Data {
 unsigned char prefix[8]; AsciiString modelName, nameC;
 unsigned char gap10[0x38]; AsciiString name48;
 unsigned char gap4c[8]; bool flag54;
};
struct Rva000ECF79Type {
 void *mesh; Vector3 offset; SphereClass bounds; const void *data;
 unsigned char gap24[0x20]; unsigned char shadow; unsigned char alignment[3];
 AsciiString textureName,modelName,nameC,nameD; int field58;
};
struct Rva000ECF79Tree {
 Vector3 location; float scale; Matrix3D transform;
 int treeType; bool visible; unsigned char alignment45[3]; SphereClass bounds;
 unsigned int drawableID; int pushAside; int swayType, firstIndex, bufferIndex;
 float pushAsideSource; float pushAsideDelta; Vector3 vector74;
 unsigned int lastFrame; float field84; bool flag88; unsigned char gap89[3]; int field8c;
 Matrix3D matrix90; int fieldc0; bool flagc4; unsigned char gapc5[3];
 int fieldc8,typecc,fieldd0,fieldd4,fieldd8,fielddc,fielde0,fielde4;
};
extern float GetGameClientRandomValueReal(float,float,char*,int);
extern int GetGameClientRandomValue(int,int,char*,int);
static inline void translateBounds(Vector3 &center, const Vector3 &position)
{
 center.X=position.X+center.X;
 center.Y=position.Y+center.Y;
 center.Z=position.Z+center.Z;
}
class W3DTreeBuffer {
public:
 int addTreeType(const AsciiString&, const AsciiString&, const void*,int,const AsciiString&,const AsciiString&);
 int rva000ECDF5(const AsciiString&, int,const AsciiString&);
 void rva000ECF79(unsigned int,Rva000ECF79Coord,float,const Matrix3D*,float,const Rva000ECF79Data*,int,const AsciiString&,const AsciiString&);
 unsigned char prefix[0x5c0]; Rva000ECF79Tree trees[1200];
 int numTrees; unsigned char gap4[2]; bool changed; unsigned char gap7[0xd]; bool initialized; unsigned char gap15[1];
 bool needUpdate; unsigned char gap17[1]; Rva000ECF79Type types[64]; int numTypes;
};
void W3DTreeBuffer::rva000ECF79(unsigned int id,Rva000ECF79Coord location,float scale,
 const Matrix3D *transform,float randomScaleAmount,const Rva000ECF79Data *data,
 int shadowKind,const AsciiString &textureName,const AsciiString &nameD)
{
 if(numTrees>=1200) return;
 if(!initialized) return;
 int type=-2;
 for(int i=0;i<numTypes;++i) {
  if(types[i].modelName.compareNoCase(data->modelName)==0 && types[i].nameC.compareNoCase(data->nameC)==0) {type=i;break;}
 }
 if(type<0) {
  type=addTreeType(data->modelName,data->nameC,data,shadowKind,textureName,nameD);
  if(type<0) return;
  needUpdate=true;
 }
 types[type].field58=rva000ECDF5(data->name48,shadowKind,textureName);
 float randomScale=GetGameClientRandomValueReal(1.0f-randomScaleAmount,1.0f+randomScaleAmount,
  "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DTreeBuffer.cpp",0x2a7);
 trees[numTrees].transform=*transform;
 if(randomScaleAmount>0.0f) trees[numTrees].scale=scale*randomScale;
 else trees[numTrees].scale=scale;
 trees[numTrees].location=Vector3(location.x,location.y,location.z);
 trees[numTrees].treeType=type;
 trees[numTrees].typecc=type;
 trees[numTrees].fieldd0=types[type].field58;
 trees[numTrees].bounds=types[type].bounds;
 trees[numTrees].bounds.Center*=trees[numTrees].scale;
 trees[numTrees].bounds.Radius*=trees[numTrees].scale;
 translateBounds(trees[numTrees].bounds.Center,trees[numTrees].location);
 trees[numTrees].visible=false;
 trees[numTrees].drawableID=id;
 trees[numTrees].firstIndex=0;
 trees[numTrees].bufferIndex=-1;
 trees[numTrees].swayType=data->flag54?0:GetGameClientRandomValue(1,10,
  "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DTreeBuffer.cpp",0x2c3);
 trees[numTrees].pushAside=0;
 trees[numTrees].lastFrame=0;
 trees[numTrees].fieldc8=0;
 trees[numTrees].fielde0=255;
 trees[numTrees].fielde4=255;
 trees[numTrees].flagc4=false;
 trees[numTrees].fieldd8=0;
 trees[numTrees].fielddc=0;
 trees[numTrees].fieldd4=0;
 trees[numTrees].pushAsideSource=0;
 trees[numTrees].pushAsideDelta=0;
 trees[numTrees].vector74.Set(0,0,0);
 trees[numTrees].field84=0;
 trees[numTrees].flag88=false;
 trees[numTrees].field8c=0;
 trees[numTrees].matrix90.Make_Identity();
 trees[numTrees].fieldc0=0;
 ++numTrees;
 changed=true;
}

