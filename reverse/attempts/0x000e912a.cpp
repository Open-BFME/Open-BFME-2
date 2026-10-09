// ?rva000E912A@W3DShrubBuffer@@QAEXPBUCoord3D@@MH@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// W3DShrubBuffer::removeTreeAtIndex, retail 0x000E75F5 (195 bytes, ret 4). Open-BFME-1 twin:
// W3DShrubBuffer_removeTreeAtIndex.cpp (0x0071D020), here in plain form: a tree in the toppling state snaps to its
// upright type (or the toppled type while a push-aside model exists), drops its topple and push-aside models (a
// shrub with none resets the rows that share its key) and leaves the toppling state. BFME2 layout: 2000 records
// of 0xA0 at +0x1958, count +0x4FB58, changed byte +0x4FB5C.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Coord2D.h"
typedef int Int;


class Rva000E75F5RenderObjClass
{
public:
	virtual void Delete_This(void);
	virtual void slot04(void); virtual void slot08(void); virtual void slot0c(void);
	virtual void slot10(void); virtual void slot14(void); virtual void slot18(void); virtual void slot1c(void);
	virtual void slot20(void); virtual void slot24(void); virtual void slot28(void); virtual void slot2c(void);
	virtual void slot30(void); virtual void slot34(void); virtual void slot38(void); virtual void slot3c(void);
	virtual void Remove(void);

	void Release_Ref(void)
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}

	Int m_refCount;
};

struct Rva000E75F5Tree
{
	Coord3D m_position; float m_scale;
	unsigned char m_pad10[0x40 - 0x10];
	Int m_treeType;
	bool m_enabled; unsigned char m_pad45[0x58 - 0x45];
	Int m_key;
	unsigned char m_pad5c[0x84 - 0x5c];
	Int m_state;
	Int m_uprightType;
	Int m_toppledType;
	unsigned char m_pad90[0x94 - 0x90];
	Rva000E75F5RenderObjClass *m_topple;
	Rva000E75F5RenderObjClass *m_pushAside;
	unsigned char m_pad9c[0xa0 - 0x9c];
};

struct Rva000E7546TypeRecord {
 void *m_valid; char at04[0x2C-4];
 Coord2D m_shadowA; char at34[0x3C-0x34];
 Coord2D m_shadowB; bool m_ready; char at45[0x5C-0x45];
};
class W3DShrubBuffer
{
public:
	void rva000E75F5(Int index);
 bool rva000E7546(Int index, float *outPos, float *outScale, Coord2D *outShadowA, Coord2D *outShadowB);
	void rva000E70D9(Int key);
	void rva000E912A(const Coord3D *center, float radius, Int mode);
	bool rva000E90DB(unsigned int key, Int mode);

private:
	unsigned char m_pad0000[0x1958];
	Rva000E75F5Tree m_trees[2000];
	Int m_numTrees;
	unsigned char m_anythingChanged;
 char at4FB5D[0x4FB70-0x4FB5D];
 Rva000E7546TypeRecord m_treeTypes[64];
};

void W3DShrubBuffer::rva000E75F5(Int index)
{
	if (index >= m_numTrees)
		return;
	if (m_trees[index].m_treeType < 0)
		return;
	if (m_trees[index].m_state == 1) {
		if (m_trees[index].m_pushAside != 0)
			m_trees[index].m_treeType = m_trees[index].m_toppledType;
	} else {
		m_trees[index].m_treeType = m_trees[index].m_uprightType;
	}
	if (m_trees[index].m_topple != 0) {
		m_trees[index].m_topple->Remove();
		if (m_trees[index].m_topple != 0) {
			m_trees[index].m_topple->Release_Ref();
			m_trees[index].m_topple = 0;
		}
	}
	if (m_trees[index].m_pushAside != 0) {
		m_trees[index].m_pushAside->Remove();
		if (m_trees[index].m_pushAside != 0) {
			m_trees[index].m_pushAside->Release_Ref();
			m_trees[index].m_pushAside = 0;
		}
	} else {
		rva000E70D9(m_trees[index].m_key);
	}
	m_trees[index].m_state = 0;
	m_anythingChanged = true;
}

static inline void copyShrubPosition(float *out, const Coord3D *position)
{
 out[0] = position->x; out[1] = position->y; out[2] = position->z;
}
// BF1 f98983a7 W3DShrubBufferRva0071CF40 is the semantic guide.
// BFME2's existing removeTreeAtIndex independently proves160B entries,
// not the donor164B stride; native175 proves all four copied outputs.
bool W3DShrubBuffer::rva000E7546(Int index, float *outPos, float *outScale, Coord2D *outShadowA, Coord2D *outShadowB)
{
 if (index < m_numTrees) {
  Int type = m_trees[index].m_treeType;
  if (type >= 0 && m_trees[index].m_enabled && m_treeTypes[type].m_valid && m_treeTypes[type].m_ready) {
   copyShrubPosition(outPos, &m_trees[index].m_position);
   *outScale = m_trees[index].m_scale * 10.0f;
   *outShadowA = m_treeTypes[type].m_shadowA;
   *outShadowB = m_treeTypes[type].m_shadowB;
   return true;
  }
 }
 return false;
}

// Reference shrub/tree unitMoved supplies the vector distance test. Native
// 164B proves a strict radius comparison and keyed removal with caller mode.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
struct ShrubRadiusDelta : Coord3D
{
 ShrubRadiusDelta(float a,float b,float c) {x=a; y=b; z=c;}
 void sub(const Coord3D *v) {
  float a=x,b=y,c=z; float vx=v->x,vy=v->y,vz=v->z;
  _ReadWriteBarrier();
  x=a-vx; y=b-vy; z=c-vz;
 }
 float lengthSqr() const {return x*x+y*y+z*z;}
};
void W3DShrubBuffer::rva000E912A(const Coord3D *center,float radius,Int mode)
{
 for(Int i=0;i<m_numTrees;++i) {
  if(m_trees[i].m_treeType>=0) {
   ShrubRadiusDelta delta(m_trees[i].m_position.x,m_trees[i].m_position.y,m_trees[i].m_position.z);
   delta.sub(center);
   if(radius*radius>delta.lengthSqr()) rva000E90DB(m_trees[i].m_key,mode);
  }
 }
}
