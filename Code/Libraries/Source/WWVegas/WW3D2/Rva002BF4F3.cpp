// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Geometry helper home: native2BF935 passes its unchanged receiver to ray helper2BF4F3.
// WB D270A0 proves prefix1C plus dot plus argument-name54; its ReleaseRef label
// comes from an inlined refcount assertion and does not establish the owner name.
// Target facts: manager268 config; assets4; factory VT80; refcount4; delete VT0.
// The 12/16-byte nodes use verified RegistryAsciiPath and Rva005F17C6Build ABIs.
// Address-derived base views retain unknown expression and receiver identities.
// Canonical AsciiString owns cleanup. Native2BF935..2BFA12 RET12; full221/EH exact.
// ?rva002BF4F3@Rva002BF4F3@@QAE_NPAVRenderObjClass@@PBVVector3@@PAV3@H_N@Z @0x002BF4F3 189B unlock: AABox early-out then down-cast via rowed 0x002BF198; callers 0x002BF5B0 0x002BF935; box getter slot 0x108; float -1.0f via g_00BBB9AC


#include "ascii_string.h"
class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class AABoxClass
{
public:
	Vector3 Center;
	Vector3 Extent;
};

class RenderObjClass
{
public:
	int m_refs;
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual int v28(); virtual void v29();
	virtual RenderObjClass *v30(int); virtual void v31(); virtual RenderObjClass *v32(const char *,int); virtual void v33(); virtual void v34();
	virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
	virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
	virtual void v65();
	virtual const AABoxClass *GetBoundingBox();
 virtual void v67();
 virtual void v68();
 virtual void v69();
 virtual void v70();
 virtual void v71();
 virtual void v72();
 virtual void v73();
 virtual void v74();
 virtual void v75();
 virtual void v76();
 virtual void v77();
 virtual void v78();
 virtual void v79();
 virtual void v80();
 virtual void v81();
 virtual void v82();
 virtual void v83();
 virtual void v84();
 virtual void v85();
 virtual void v86();
 virtual void v87();
 virtual void v88();
 virtual void v89();
 virtual void v90();
 virtual void v91();
 virtual void v92();
 virtual void v93();
 virtual void v94();
 virtual void v95();
 virtual void v96();
 virtual void v97();
 virtual void v98();
 virtual void v99();
 virtual void v100();
 virtual void v101(int);
};

extern float g_00BBB9AC;

class Rva00DFEF18Host
{
public:
	bool Cast(RenderObjClass *obj, const Vector3 &start, const Vector3 &dir, Vector3 *out, int collisionType, bool checkHidden);
};

class Rva002BF4F3
{
public:
	bool rva002BF4F3(RenderObjClass *obj, const Vector3 *pt, Vector3 *out, int collisionType, bool checkHidden);
 void rva002BEA10(RenderObjClass *,bool);
 void rva002BEF4B(RenderObjClass *);
 bool rva002BF935(void *arg, const Vector3 *pt, Vector3 *out);
};

bool Rva002BF4F3::rva002BF4F3(RenderObjClass *obj, const Vector3 *pt, Vector3 *out, int collisionType, bool checkHidden)
{
	const AABoxClass *box = obj->GetBoundingBox();
	if (box->Center.X - box->Extent.X > pt->X)
		return false;
	if (pt->X > box->Center.X + box->Extent.X)
		return false;
	if (box->Center.Y - box->Extent.Y > pt->Y)
		return false;
	if (pt->Y > box->Center.Y + box->Extent.Y)
		return false;
	Vector3 start;
	Vector3 dir;
	start.X = pt->X;
	start.Y = pt->Y;
	start.Z = box->Center.Z + box->Extent.Z;
	dir.X = 0.0f;
	dir.Y = 0.0f;
	dir.Z = g_00BBB9AC;
	return ((Rva00DFEF18Host *)this)->Cast(obj, start, dir, out, collisionType, checkHidden);
}

struct Rva005F17C6S12 { int m0,m1,m2; };
struct AsciiStringPlusText : Rva005F17C6S12 {};
AsciiStringPlusText operator+(const AsciiString &,const char *);
struct Rva0020F58E { int storage[4]; operator AsciiString(); };
struct Rva005F17C6S16 : Rva0020F58E {};
Rva005F17C6S16 Rva005F17C6Build(const Rva005F17C6S12 &,int);
class Rva002BF935AssetManager { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual RenderObjClass *create(const char *,int);
};
struct Rva002BF935Config { int pad0; Rva002BF935AssetManager *assets; char pad8[0x14]; AsciiString prefix; };
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
struct Rva002BF935ManagerView { char pad[0x268]; Rva002BF935Config *config; };
bool Rva002BF4F3::rva002BF935(void *arg,const Vector3 *pt,Vector3 *out) {
 Rva002BF935Config *config=reinterpret_cast<Rva002BF935ManagerView *>(TheLivingWorldManager)->config;
 AsciiString name=Rva005F17C6Build(static_cast<const Rva005F17C6S12 &>(config->prefix + "."),reinterpret_cast<int>((char *)arg+0x54));
 config=reinterpret_cast<Rva002BF935ManagerView *>(TheLivingWorldManager)->config;
 Rva002BF935AssetManager *assets=config->assets;
 RenderObjClass *obj=assets->create(name.str(),0);
 bool result=false;
 if(obj) { result=rva002BF4F3(obj,pt,out,1,true); if(--obj->m_refs==0)obj->v00(); }
 return result;
}

// Native2BEA10..2BEA63 RET8: child count70/get78 and virtual194(!flag).
// WB D26AC0 confirms this is unused and each child is released via refcount4/VT0.
void Rva002BF4F3::rva002BEA10(RenderObjClass *obj,bool flag) {
 for(int i=0;i<obj->v28();++i) {
  RenderObjClass *child=obj->v30(i);
  if(child) { child->v101(!flag); if(--child->m_refs==0)child->v00(); }
 }
}

// WB D26CB0 and native2BEF4B..2BEFE5 RET4 prove LM_%02d child lookup.
// Manager count18; named AsciiString::format; render slots80/194 and refs4/VT0.
// The method name remains unknown; its original receiver is preserved but unused.
struct Rva002BEF4BManagerView { char pad[0x18]; int count; };
void Rva002BF4F3::rva002BEF4B(RenderObjClass *obj) {
 int i=0;
 int *count=&reinterpret_cast<Rva002BEF4BManagerView *>(TheLivingWorldManager)->count;
 for(;i<*count;++i) {
  AsciiString name;
  name.format("LM_%02d",i+1);
  RenderObjClass *child=obj->v32(name.str(),0);
  if(child) { child->v101(0); if(--child->m_refs==0)child->v00(); }
 }
}
