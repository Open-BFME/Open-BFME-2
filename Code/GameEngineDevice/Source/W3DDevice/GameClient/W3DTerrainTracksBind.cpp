// cl: /O1 /arch:SSE /G7 /MD /EHsc /ICode/Libraries/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Reference semantic lead: GeneralsMD W3DTerrainTracks.cpp computeTrackSpacing
// at BFME1 checkout dae380faa5f6fa536eec8d6ebbe877321d4cb51d.
// Retail 0x84B18..0x84C05 supplies the boundary and target-specific ABI:
// EDI renderer, ESI two endpoint vectors, two stack bone names, XMM0 result.
// Slot C8 resolves a bone; slot CC takes a 48-byte output and bone index,
// returning a matrix reference. The slot identities are structural inferences
// from the reference; their arguments and matrix translation offsets are retail facts.
// Keeping the caller in this TU lets MSVC derive its private convention.
// WWMath::Sqrt is the existing donor x87 implementation, matching retail FSQRT.
// The renderer and track classes are partial ABI views, not recovered names.
#include "wwmath.h"
#include "vector2.h"
#include "vector3.h"
#include "Lib/Coord3D.h"
struct TrackVector { float x,y,z;
 TrackVector(){} TrackVector(float a,float b,float c):x(a),y(b),z(c){}
 TrackVector(const TrackVector&a):x(a.x),y(a.y),z(a.z){}
 TrackVector& operator=(const TrackVector&a){x=a.x;y=a.y;z=a.z;return *this;}
};
struct TrackMatrix { float m[3][4]; };
class Rva00084B18RenderObj {
public:
 virtual void v00();
 virtual void v01();
 virtual void v02();
 virtual void v03();
 virtual void v04();
 virtual void v05();
 virtual void v06();
 virtual void v07();
 virtual void v08();
 virtual void v09();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void v20();
 virtual void v21();
 virtual void v22();
 virtual void v23();
 virtual void v24();
 virtual void v25();
 virtual void v26();
 virtual void v27();
 virtual void v28();
 virtual void v29();
 virtual void v30();
 virtual void v31();
 virtual void v32();
 virtual void v33();
 virtual void v34();
 virtual void v35();
 virtual void v36();
 virtual void v37();
 virtual void v38();
 virtual void v39();
 virtual void v40();
 virtual void v41();
 virtual void v42();
 virtual void v43();
 virtual void v44();
 virtual void v45();
 virtual void v46();
 virtual void v47();
 virtual void v48();
 virtual void v49();
 virtual int boneIndex(const char*);
 virtual const TrackMatrix &boneTransform(TrackMatrix &,int);
};
class TextureClass { public: void Release_Ref(); };
template<class T> class RefCountPtr {
public:
 T *ptr;
 const RefCountPtr &operator=(const RefCountPtr &);
};
// The one-pointer texture value returned by the established particle loader.
// A derived member names its implicit assignment through the base provider;
// W3DSnowManager::updateIniSettings independently uses this same view/shape.
class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass> {
public:
 ~BFME2ParticleTextureHandle() { if(ptr) ptr->Release_Ref(); }
};
extern BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *,int,int);

class Object { public: int rva0028B511() const; };
class Drawable { public: char prefix00[0xFC]; Object *m_object; };
class TerrainLogic {
public:
 virtual void v0() const; virtual void v1() const; virtual void v2() const;
 virtual void v3() const; virtual void v4() const; virtual void v5() const;
 virtual float getGroundHeight(float,float,Coord3D *normal=0) const;
 virtual float getLayerHeight(float,float,int,Coord3D *normal=0,unsigned char clip=true) const;
};
extern TerrainLogic *TheTerrainLogic;
class TerrainTracksRenderObjClassSystem {
public: char prefix00[0x1C];int m_maxTankTrackEdges;
};
extern TerrainTracksRenderObjClassSystem *TheTerrainTracksRenderObjClassSystem;
static inline float sqr(float value) { return value*value; }
struct TrackEdge {
 Vector3 endPointPos[2]; Vector2 endPointUV[2]; int timeAdded; float alpha;
};
class Rva00084206Track {
public:
 Rva00084206Track();
 char pad0[8]; TrackVector endpoints[2]; char pad20[0xc];
 BFME2ParticleTextureHandle texture; int activeEdgeCount, totalEdgesAdded; Drawable *owner;
 TrackEdge edges[100]; Vector3 lastAnchor;
 int bottomIndex, topIndex; bool haveAnchor, bound; char pad1312[2]; float width,length; bool airborne,haveCap; char pad131e[2];
 Rva00084206Track *next,*prev;
 void init(float,float,const char*);
 void addCapEdgeToTrack(float,float);
};
static __declspec(noinline) float computeTrackSpacing(Rva00084B18RenderObj *obj,TrackVector *ends,const char *left,const char *right) {
 float spacing=14.0f;
 int a=obj->boneIndex(left); int b=obj->boneIndex(right);
 if(a && b) {
  TrackMatrix temp; const TrackMatrix &m=obj->boneTransform(temp,a);
  ends[0]=TrackVector(m.m[0][3],m.m[1][3],m.m[2][3]);
  const TrackMatrix &n=obj->boneTransform(temp,b);
  ends[1]=TrackVector(n.m[0][3],n.m[1][3],n.m[2][3]);
  float x=ends[1].x-ends[0].x,y=ends[1].y-ends[0].y,z=ends[1].z-ends[0].z;
  float sum=z*z+y*y+x*x; spacing=WWMath::Sqrt(sum)+4.0f;
 }
 return spacing;
}
class SceneClass;
class VertexMaterialClass {
public:
 enum PresetType { PRELIT_DIFFUSE = 0 };
 static VertexMaterialClass *Get_Preset(PresetType);
};
class ShaderClass {
public:
 unsigned int bits;
 static ShaderClass _PresetAlphaShader;
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct TrackSystemGlobalView {
 char pad[0x10c]; int maxTerrainTracks;
 int maxTankTrackEdges, maxTankTrackOpaqueEdges, maxTankTrackFadeDelay;
 char pad11c[0x20]; bool makeTrackMarks;
};
class Rva00084C05System {
public:
 void *vertexBuffer, *indexBuffer;
 VertexMaterialClass *material; ShaderClass shader;
 Rva00084206Track *used,*free;
 SceneClass *scene;
 int maxTankTrackEdges, maxTankTrackOpaqueEdges, maxTankTrackFadeDelay;
 void setDetail();
 void update();
 void init(SceneClass *);
 void ReAcquireResources();
 Rva00084206Track *bind(Rva00084B18RenderObj*,float,const char*,const char*,const char*);
};
Rva00084206Track *Rva00084C05System::bind(Rva00084B18RenderObj *obj,float length,const char *texture,const char *left,const char *right) {
 Rva00084206Track *mod=free;
 if(mod) {
  if(mod->next) mod->next->prev=mod->prev;
  if(mod->prev) mod->prev->next=mod->next; else free=mod->next;
  mod->prev=0; mod->next=used;
  if(used) used->prev=mod;
  used=mod;
  mod->init(computeTrackSpacing(obj,mod->endpoints,left,right),length,texture);
  mod->bound=true;
 }
 return mod;
}

// Semantic donor: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// TerrainTracksSystemInit.cpp. Target 00084D01..00084DAC and WorldBuilder
// 008BFFE0 independently agree on scene+18, free+14/used+10, track links
// +1320/+1324, allocation size1328 and global maxTerrainTracks+10C.
// WorldBuilder names init and ReAcquireResources; the address-derived class
// views remain partial. The donor establishes the material/shader purpose.
void Rva00084C05System::init(SceneClass *newScene) {
 const int numModules = ((TrackSystemGlobalView *)TheWritableGlobalData)->maxTerrainTracks;
 scene = newScene;
 ReAcquireResources();
 material = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
 shader = ShaderClass::_PresetAlphaShader;
 if (free || used) return;
 for (int i = 0; i < numModules; ++i) {
  Rva00084206Track *mod = new Rva00084206Track;
  if (!mod) return;
  mod->prev = 0;
  mod->next = free;
  if (free) free->prev = mod;
  free = mod;
 }
}

class Rva00084024 { public: void rva00084024(); };
class Rva00083E5C { public: void rva00083E5C(); };
// Donor setDetail: TerrainTracksRenderObjClassSystem.cpp at ba7ddda7e8f.
// Complete native 00084055..00084096 and WB 008C2510 agree on the two
// cleanup calls and global+110/+114/+118 -> system+1C/+20/+24 copies.
// ReAcquireResources was the previous attempt's blocker; init now proves
// that callee independently at 00083D54. The class name stays structural.
void Rva00084C05System::setDetail() {
 ((Rva00084024 *)this)->rva00084024();
 ((Rva00083E5C *)this)->rva00083E5C();
 maxTankTrackEdges = ((TrackSystemGlobalView *)TheWritableGlobalData)->maxTankTrackEdges;
 maxTankTrackOpaqueEdges = ((TrackSystemGlobalView *)TheWritableGlobalData)->maxTankTrackOpaqueEdges;
 maxTankTrackFadeDelay = ((TrackSystemGlobalView *)TheWritableGlobalData)->maxTankTrackFadeDelay;
 ReAcquireResources();
}

class WW3D {
 static unsigned int SyncTime;
public: static unsigned int Get_Sync_Time() { return SyncTime; }
};
// Existing providers moved from TerrainTrackEdgeInfoO1.cpp so the caller
// sees their verified register usage. Their native names and bodies remain.
class Rva00083CB2
{
public:
	void rva00083CB2();
	friend void __stdcall Rva00083CD7Clear(Rva00083CB2 *p);
	friend class Rva00083CE9Host;
private:
	char _pad00[0x30];
	int m_30;
	int m_34;
	int m_38;
	char _pad3C[0x1308 - 0x3C];
	int m_1308;
	int m_130C;
	unsigned char m_1310;
	unsigned char m_1311;
	char _pad1312[0x131D - 0x1312];
	unsigned char m_131D;
};
// ?rva00083CB2@Rva00083CB2@@QAEXXZ retail 0x00083CB2 37B reset of scattered
// fields to 0 with +0x131D set to 1. Evidence: unlock lane; callers at
// 0x00083D4C 0x000840B1 0x00084213 unblock 0x00083CE9 0x00084206.
void Rva00083CB2::rva00083CB2()
{
	m_1310 = 0;
	m_131D = 1;
	m_130C = 0;
	m_1308 = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 0;
}
struct Rva00083CE9Node : public Rva00083CB2
{
public:
	Rva00083CE9Node *m_1320;
	Rva00083CE9Node *m_1324;
};

class Rva00083E87Ref;
class Rva00083CE9Host
{
public:
	void rva00083CE9(Rva00083CE9Node *p);
	void rva00084002();
	void rva00083E87();
private:
	Rva00083E87Ref *m_00;
	Rva00083E87Ref *m_04;
	Rva00083E87Ref *m_08;
	char _pad0C[4];
	Rva00083CE9Node *m_10;
	Rva00083CE9Node *m_14;
};
// ?rva00083CE9@Rva00083CE9Host@@QAEXPAURva00083CE9Node@@@Z retail 0x00083CE9
// 107B unlink node from old list then push at head of this list and reset it.
// Evidence: chain calls 0x00083CB2; callers at 0x00083EA6 0x00083FDD 0x00084016.
void Rva00083CE9Host::rva00083CE9(Rva00083CE9Node *p)
{
	if (p == 0)
		return;
	if (p->m_1320 != 0)
		p->m_1320->m_1324 = p->m_1324;
	Rva00083CE9Node *next = p->m_1324;
	if (next != 0)
		next->m_1320 = p->m_1320;
	else
		m_10 = p->m_1320;
	p->m_1324 = 0;
	p->m_1320 = m_14;
	if (m_14 != 0)
		m_14->m_1324 = p;
	m_14 = p;
	p->rva00083CB2();
}

// Semantic donor: TerrainTracksSystemUpdate.cpp at ba7ddda7e8f.
// Native 00083F0F..00084002 and WB 008C0520 confirm the 30-byte edge stride,
// time+64 / alpha+68, count+30, bottom+1308, anchor+1310 and global+13C.
// The native 00083CE9 call supplies the established releaseTrack provider.
void Rva00084C05System::update() {
 int iTime = WW3D::Get_Sync_Time();
 float iDiff;
 Rva00084206Track *mod = used, *nextMod;
 while (mod != 0) {
  nextMod = mod->next;
  if (!((TrackSystemGlobalView *)TheWritableGlobalData)->makeTrackMarks)
   mod->haveAnchor = false;
  int i, index;
  for (i = 0, index = mod->bottomIndex; i < mod->activeEdgeCount; i++, index++) {
   if (index >= maxTankTrackEdges) index = 0;
   iDiff = (float)(iTime - mod->edges[index].timeAdded);
   iDiff = 1.0f - iDiff / (float)maxTankTrackFadeDelay;
   if (iDiff < 0.0) iDiff = 0.0f;
   if (mod->edges[index].alpha > 0.0f) mod->edges[index].alpha = iDiff;
   if (iDiff == 0.0f) {
    mod->bottomIndex++;
    mod->activeEdgeCount--;
    if (mod->bottomIndex >= maxTankTrackEdges) mod->bottomIndex = 0;
   }
   if (mod->activeEdgeCount == 0 && !mod->bound)
    ((Rva00083CE9Host *)this)->rva00083CE9((Rva00083CE9Node *)mod);
  }
  mod = nextMod;
 }
}

// Native84206..84271 ret12 at8426E: reset83CB2; width/length+1314/+1318;
// cached texture loader132D89 and rowed RefCountPtr assignment424D0, followed
// by temporary Release_Ref61ED10. Layout/calls are native facts; donor track
// initialization supplies semantics. Derived one-pointer member and return
// preserve the observed assignment receiver/cursor lifetime without a cast.
void Rva00084206Track::init(float w,float l,const char *name) {
 ((Rva00083CB2 *)this)->rva00083CB2();
 width=w; length=l;
 texture=BFME2LoadParticleTexture(name,0,0);
}

// Semantic donor: BFME1 9cbfb551 TerrainTracksBfmeAddCap.cpp. The complete
// native84271..8458A ret8 body establishes cap+131D, ownerDrawable+38 and
// object+FC, TerrainLogic slots18/1C, edges48B at3C, lastAnchor12FC and
// width1314/length1318. vZ's value construction preserves target scheduling.
void Rva00084206Track::addCapEdgeToTrack(float x, float y)
{
	if (haveCap)
	{
		return;
	}

	if (activeEdgeCount == 1)
	{
		haveCap = true;
		haveAnchor = false;
		return;
	}

	Vector3 vPos;
	Vector3 vZ;
	Coord3D vZTmp;
	int objectLayer;
	float eHeight;

	if (owner && (objectLayer = owner->m_object->rva0028B511()) != 1)
	{
		eHeight = 0.25f + TheTerrainLogic->getLayerHeight(x, y, objectLayer, &vZTmp);
	}
	else
	{
		eHeight = TheTerrainLogic->getGroundHeight(x, y, &vZTmp);
	}

	vZ=Vector3(vZTmp.x,vZTmp.y,vZTmp.z);

	vPos.X = x;
	vPos.Y = y;
	vPos.Z = eHeight;

	Vector3 vDir = Vector3(x, y, eHeight) - lastAnchor;
	int maxEdgeCount = TheTerrainTracksRenderObjClassSystem->m_maxTankTrackEdges;

	if (vDir.Length2() < sqr(length))
	{
		int lastAddedEdge = topIndex - 1;
		if (lastAddedEdge < 0)
			lastAddedEdge = maxEdgeCount - 1;
		edges[lastAddedEdge].alpha = 0.0f;
		haveCap = true;
		haveAnchor = false;
		return;
	}

	if (activeEdgeCount >= maxEdgeCount)
	{
		bottomIndex++;
		activeEdgeCount--;

		if (bottomIndex >= maxEdgeCount)
			bottomIndex = 0;
	}

	if (topIndex >= maxEdgeCount)
		topIndex = 0;

	vDir.Z = 0;
	vDir.Normalize();

	Vector3 vX;
	Vector3::Cross_Product(vDir, vZ, &vX);

	TrackEdge &topEdge = edges[topIndex];

	topEdge.endPointPos[0] = vPos - (width * 0.5f * vX);
	topEdge.endPointPos[0].Z += 2.0f;

	if (totalEdgesAdded & 1)
	{
		topEdge.endPointUV[0].X = 0.0f;
		topEdge.endPointUV[0].Y = 0.0f;
	}
	else
	{
		topEdge.endPointUV[0].X = 0.0f;
		topEdge.endPointUV[0].Y = 1.0f;
	}

	topEdge.endPointPos[1] = vPos + (width * 0.5f * vX);
	topEdge.endPointPos[1].Z += 2.0f;

	if (totalEdgesAdded & 1)
	{
		topEdge.endPointUV[1].X = 1.0f;
		topEdge.endPointUV[1].Y = 0.0f;
	}
	else
	{
		topEdge.endPointUV[1].X = 1.0f;
		topEdge.endPointUV[1].Y = 1.0f;
	}

	topEdge.timeAdded = WW3D::Get_Sync_Time();
	topEdge.alpha = 0.0f;
	lastAnchor = vPos;
	activeEdgeCount++;
	totalEdgesAdded++;
	topIndex++;
	haveCap = true;
	haveAnchor = false;
}

