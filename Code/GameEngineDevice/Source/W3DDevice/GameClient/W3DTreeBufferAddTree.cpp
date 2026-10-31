// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/stringinline /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
// W3DTreeBuffer::addTree, retail 0x000ECF79 (1284 bytes). Donor: Open-BFME-1
// W3DTreeBufferRva000ECF79AddTree.cpp (BFME1 0x00736B60); BFME2 layout read from
// retail: 1200 tree records of 0xE8 at +0x5C0 (count +0x44540, dirty byte
// +0x44546, initialized +0x44554, type-added flag +0x44556), 64 types of 0x5C at
// +0x44558 (count +0x45C58).
// +0x44545, initialized +0x44554, type-added flag +0x44556), 64 types of 0x5C at
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "vector3.h"
#include "matrix3d.h"
#include "sphere.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "W3DTreeRecord.h"
#include "W3DTreeTypeRecord.h"

class Rva000E6AC0Base
{
public:
	Rva000E6AC0Base() {}
	virtual ~Rva000E6AC0Base() {}
};

class Rva0052413E
{
public:
	Rva0052413E() throw();
	~Rva0052413E();
private:
	unsigned char m_storage[12];
};

class TextureClass;

template <class T> class RefCountPtr;

template <> class RefCountPtr<TextureClass>
{
public:
	RefCountPtr const &operator=(RefCountPtr const &other);
	TextureClass *Ptr;
};

class Rva000E6AC0 : public Rva000E6AC0Base
{
public:
	Rva000E6AC0();
	void rva000E65B1();
	virtual ~Rva000E6AC0();
private:
	unsigned char m_storage[0x38 - 4]; // +0x04
protected:
	RefCountPtr<TextureClass> texture38, texture3c; // +0x38
	char list40[0x28], list68[0x28]; // +0x40
private:
	unsigned char m_pad90[0x5BC - 0x90];
protected:
	float m_sinkScale; // +0x5BC
};

struct TTree;

class Xfer;
struct Rva000EAFA4Coord3;
struct Rva000EAFA4Coord2;
struct Rva000ECF79Coord;
struct Rva000ECF79Data;

class W3DTreeBuffer : public Rva000E6AC0
{
	friend class Rva000EC9C6;
protected:
	void updateTexture();
	void updateTopplingTree(TTree *tree);
	virtual void xfer(Xfer *xfer);
public:
	W3DTreeBuffer();
public:
	void rva000EA24D();
private:
	Rva000EDA94Record m_records[1200];
private:
	int m_count;
private:
	unsigned char m_anythingChanged;
private:
	unsigned char m_44545; // +0x44545
private:
	unsigned char m_changed;
private:
	unsigned char m_44547;
private:
	Rva0052413E m_objects;
private:
	unsigned char m_initialized;
private:
	unsigned char m_44555;
private:
	unsigned char m_needUpdate;
private:
	unsigned char m_44557;
private:
	Rva000EC67F m_types[64]; // +0x44558
private:
	int m_typeCount;
private:
	int m_45c5c; // +0x45C5C
private:
	int m_45c60;
private:
	unsigned char m_45c64;
public:
	bool rva000EA48D(void *key, const Coord3D *direction, float height);
	bool rva000EA644(void *key);
	void rva000EA2C0(void *key);
	bool rva000EA6A7(void *key);
	void rva000EB2EF(int index);
	void rva000EB0E6(int index);
	bool rva000ECF2A(unsigned key, int mode);
	void startMorph(int index, int mode);
	int addTreeType(const AsciiString &modelName, const AsciiString &nameC, const void *data, int shadowKind,
		const AsciiString &textureName, const AsciiString &templateName);
	int rva000ECDF5(const AsciiString &templateName, int shadowKind, const AsciiString &textureName);
	char rva000EA327(void *key, Vector3 position, const Matrix3D *transform);
	bool rva000EAFA4(int index, Rva000EAFA4Coord3 *position, float *radius, Rva000EAFA4Coord2 *primary,
		Rva000EAFA4Coord2 *secondary);
	void addTree(unsigned int id, Rva000ECF79Coord location, float scale, const Matrix3D *transform,
		float randomScaleAmount, const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName,
		const AsciiString &templateName);
};
// addTree's position, taken by value and converted from the caller's Coord3D.
struct Rva000ECF79Coord
{
	Rva000ECF79Coord(const Coord3D &c) : x(c.x), y(c.y), z(c.z) {}
	float x, y, z;
};
struct Rva000ECF79Data {
 unsigned char prefix[8]; AsciiString modelName, nameC;
 unsigned char gap10[0x38]; AsciiString name48;
 unsigned char gap4c[8]; bool flag54;
};
struct Rva000ECF79Type {
 void *mesh; Vector3 offset; SphereClass bounds; const void *data;
 unsigned char gap24[0x20]; unsigned char shadow; unsigned char alignment[3];
 AsciiString textureName,modelName,nameC,nameD; int m_morphTreeType;
};
struct Rva000ECF79Tree {
 Vector3 location; float scale; Matrix3D transform;
 int treeType; bool visible; unsigned char alignment45[3]; SphereClass bounds;
 unsigned int drawableID; int pushAside; int swayType, firstIndex, bufferIndex;
 float pushAsideSource; float pushAsideDelta; Vector3 vector74;
 unsigned int lastFrame; float m_angularAccumulation; bool flag88; unsigned char gap89[3]; int m_options;
 Matrix3D matrix90; int m_sinkFramesLeft; bool flagc4; unsigned char gapc5[3];
 int m_morphState,typecc,fieldd0,m_morphFramesLeft,fieldd8,fielddc,m_alpha,m_targetAlpha;
};
extern float GetGameClientRandomValueReal(float,float,char*,int);
extern int GetGameClientRandomValue(int,int,char*,int);
// The x component reads through a volatile alias: it keeps retail's load order
// (position first, then the center) for the first lane, as in the BFME1 shrub twin.
static inline void translateBounds(Vector3 &center, const Vector3 &position)
{
 const volatile float &x=position.X;
 center.X+=x;
 center.Y=position.Y+center.Y;
 center.Z=position.Z+center.Z;
}
// The donor's component operations, without an out-of-line Vector3 operator.
static inline void scaleBounds(Vector3 &center, float scale)
{
 center.X=center.X*scale;
 center.Y=center.Y*scale;
 center.Z=center.Z*scale;
}
// This method's native record and type views over the canonical tree records.
struct Rva000ECF79BufferView {
 unsigned char prefix[0x5c0]; Rva000ECF79Tree trees[1200];
 unsigned char gap44540[0x44558-0x44540]; Rva000ECF79Type types[64];
};
void W3DTreeBuffer::addTree(unsigned int id,Rva000ECF79Coord location,float scale,
 const Matrix3D *transform,float randomScaleAmount,const Rva000ECF79Data *data,
 int shadowKind,const AsciiString &textureName,const AsciiString &nameD)
{
 if(m_count>=1200) return;
 if(!m_initialized) return;
 int type=-2;
 for(int i=0;i<m_typeCount;++i) {
  // Both retail calls use the StringBase<char> provider at 0x00006A00.
  if(((const StringBase<char> *)&((Rva000ECF79BufferView *)this)->types[i].modelName)->compareNoCase(*(const StringBase<char> *)&data->modelName)==0 &&
     ((const StringBase<char> *)&((Rva000ECF79BufferView *)this)->types[i].nameC)->compareNoCase(*(const StringBase<char> *)&data->nameC)==0) {type=i;break;}
 }
 if(type<0) {
  type=addTreeType(data->modelName,data->nameC,data,shadowKind,textureName,nameD);
  if(type<0) return;
  m_needUpdate=true;
 }
 ((Rva000ECF79BufferView *)this)->types[type].m_morphTreeType=rva000ECDF5(data->name48,shadowKind,textureName);
 float randomScale=GetGameClientRandomValueReal(1.0f-randomScaleAmount,1.0f+randomScaleAmount,
  "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DTreeBuffer.cpp",0x2a7);
 ((Rva000ECF79BufferView *)this)->trees[m_count].transform=*transform;
 if(randomScaleAmount>0.0f) ((Rva000ECF79BufferView *)this)->trees[m_count].scale=scale*randomScale;
 else ((Rva000ECF79BufferView *)this)->trees[m_count].scale=scale;
 ((Rva000ECF79BufferView *)this)->trees[m_count].location=Vector3(location.x,location.y,location.z);
 ((Rva000ECF79BufferView *)this)->trees[m_count].treeType=type;
 ((Rva000ECF79BufferView *)this)->trees[m_count].typecc=type;
 ((Rva000ECF79BufferView *)this)->trees[m_count].fieldd0=((Rva000ECF79BufferView *)this)->types[type].m_morphTreeType;
 ((Rva000ECF79BufferView *)this)->trees[m_count].bounds=((Rva000ECF79BufferView *)this)->types[type].bounds;
 scaleBounds(((Rva000ECF79BufferView *)this)->trees[m_count].bounds.Center,((Rva000ECF79BufferView *)this)->trees[m_count].scale);
 ((Rva000ECF79BufferView *)this)->trees[m_count].bounds.Radius*=((Rva000ECF79BufferView *)this)->trees[m_count].scale;
 translateBounds(((Rva000ECF79BufferView *)this)->trees[m_count].bounds.Center,((Rva000ECF79BufferView *)this)->trees[m_count].location);
 ((Rva000ECF79BufferView *)this)->trees[m_count].visible=false;
 ((Rva000ECF79BufferView *)this)->trees[m_count].drawableID=id;
 ((Rva000ECF79BufferView *)this)->trees[m_count].firstIndex=0;
 ((Rva000ECF79BufferView *)this)->trees[m_count].bufferIndex=-1;
 ((Rva000ECF79BufferView *)this)->trees[m_count].swayType=data->flag54?0:GetGameClientRandomValue(1,10,
  "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DTreeBuffer.cpp",0x2c3);
 ((Rva000ECF79BufferView *)this)->trees[m_count].pushAside=0;
 ((Rva000ECF79BufferView *)this)->trees[m_count].lastFrame=0;
 ((Rva000ECF79BufferView *)this)->trees[m_count].m_morphState=0;
 ((Rva000ECF79BufferView *)this)->trees[m_count].m_alpha=255;
 ((Rva000ECF79BufferView *)this)->trees[m_count].m_targetAlpha=255;
 ((Rva000ECF79BufferView *)this)->trees[m_count].flagc4=false;
 ((Rva000ECF79BufferView *)this)->trees[m_count].fieldd8=0;
 ((Rva000ECF79BufferView *)this)->trees[m_count].fielddc=0;
 ((Rva000ECF79BufferView *)this)->trees[m_count].m_morphFramesLeft=0;
 ((Rva000ECF79BufferView *)this)->trees[m_count].pushAsideSource=0;
 ((Rva000ECF79BufferView *)this)->trees[m_count].pushAsideDelta=0;
 ((Rva000ECF79BufferView *)this)->trees[m_count].vector74.Set(0,0,0);
 ((Rva000ECF79BufferView *)this)->trees[m_count].m_angularAccumulation=0;
 ((Rva000ECF79BufferView *)this)->trees[m_count].flag88=false;
 ((Rva000ECF79BufferView *)this)->trees[m_count].m_options=0;
 ((Rva000ECF79BufferView *)this)->trees[m_count].matrix90.Make_Identity();
 ((Rva000ECF79BufferView *)this)->trees[m_count].m_sinkFramesLeft=0;
 ++m_count;
 m_changed=true;
}
