// cl: /O1 /Og /arch:SSE /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Include
// stlport
// Native shadow map helper 0007C637..0007C8AE. WorldBuilder7EF110 embeds
// BuildCovexHull2D (sic), with point de-duplication and a stable orientation
// test after sorting the three indices. No equivalent ZH subsystem body was
// found; Vector2 subtraction, length and perp-dot source provide math semantics.
#include <vector>
#include <algorithm>
#define _OPERATOR_NEW_DEFINED_
#include "wwmath.h"
// LINK: max<unsigned> stays inline in _M_insert_overflow as in the retail
// copies; its .debug$F-only copy is suppressed with dllimport forceinline.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int const & max<unsigned int>(unsigned int const &__a, unsigned int const &__b) { return __a < __b ? __b : __a; } }
#pragma intrinsic(sqrt)
class Vector3;
struct BfmeE8 {float X,Y; BfmeE8(){} BfmeE8(float x,float y):X(x),Y(y){} BfmeE8(const Vector3 &v);};
void Rva00030830FreeAllocation(void*);
namespace _STL {template<> inline void allocator<BfmeE8>::deallocate(BfmeE8*p,size_t)const{if(p)Rva00030830FreeAllocation(p);}template<> inline void allocator<int>::deallocate(int*p,size_t)const{if(p)Rva00030830FreeAllocation(p);}}
struct BfmePod8 {int a[2];};
class ModuleData;
namespace _STL {
// Frees through retail's _free (0x00030830) like the BfmeE8 and int allocators above.
template<> inline void allocator<const ModuleData *>::deallocate(const ModuleData **p,size_t)const{if(p)Rva00030830FreeAllocation(p);}
template<> inline __declspec(noinline) void vector<BfmeE8>::push_back(const BfmeE8&v){if(_M_finish!=_M_end_of_storage._M_data){_Construct(_M_finish,v);++_M_finish;}else _M_insert_overflow(_M_finish,v,_IsPODType(),1UL,true);}
template<> inline __declspec(noinline) BfmePod8 *vector<BfmePod8>::erase(BfmePod8 *__first,BfmePod8 *__last){pointer __i=__copy_ptrs(__last,this->_M_finish,__first,_TrivialAss());_Destroy(__i,this->_M_finish);this->_M_finish=__i;return __first;}
template<> inline __declspec(noinline) void vector<const ModuleData *>::push_back(const ModuleData *const &v){if(_M_finish!=_M_end_of_storage._M_data){_Construct(_M_finish,v);++_M_finish;}else _M_insert_overflow(_M_finish,v,__true_type(),1UL,true);}
template<> int *find<int *,int>(int *,int *,const int &);
}
struct Rva0007B734Item {char m_pad[8];};
typedef bool (__cdecl *Rva0007B734Pred)(const Rva0007B734Item *,const Rva0007B734Item *);
Rva0007B734Item *Rva0007B734Find(Rva0007B734Item *,Rva0007B734Item *,Rva0007B734Pred);
bool Rva0007B701Cmp(const BfmeE8 &,const BfmeE8 &);
static inline void ClearPoints(std::vector<BfmeE8> &v) {
 std::vector<BfmePod8> &p=*(std::vector<BfmePod8> *)&v;
 p.erase(p.begin(),p.end());
}
static inline void PushIndex(std::vector<int> &v,const int &i) {
 ((std::vector<const ModuleData *> *)&v)->push_back(*(const ModuleData *const *)&i);
}
static inline float PointDistance(const BfmeE8 &a,const BfmeE8 &b) {
 float y=a.Y-b.Y,x=a.X-b.X;
 float sum=x*x+y*y;
 return WWMath::Sqrt(sum);
}
static inline BfmeE8 operator-(const BfmeE8 &a,const BfmeE8 &b) {
 return BfmeE8(a.X-b.X,a.Y-b.Y);
}
static inline float Perp_Dot_Product(const BfmeE8 &a,const BfmeE8 &b) {
 return a.X*-b.Y+a.Y*b.X;
}
// Select-any: W3DShadowMapConvexHull.cpp compiles the same body under its own flags.
__declspec(noinline) inline bool Rva0007C637(std::vector<BfmeE8> &input,std::vector<BfmeE8> &output,float epsilon)
{
 ClearPoints(output);
 std::vector<BfmeE8> points;
 {
 for(int n=0;n<input.size();++n) {
  unsigned j;
  for(j=0;j<points.size();++j)
   if(PointDistance(points[j],input[n])<epsilon) break;
  if(j==points.size()) points.push_back(input[n]);
 }
 }
 unsigned count=points.size();
 if(count<3) return false;
 std::vector<int> hull;

 PushIndex(hull,((BfmeE8 *)Rva0007B734Find((Rva0007B734Item *)points.begin(),(Rva0007B734Item *)points.end(),(Rva0007B734Pred)Rva0007B701Cmp)-points.begin()));
 for(;;) {
  int i;
  int current=hull.back();
  for(i=0;i<count;++i) {
   if(i==current) continue;
   unsigned j;
   for(j=0;j<count;++j) {
    if(j==i || j==current) continue;
    int a=current,b=i,c=j;
    bool flip=false;
    if(a>b){int t=a;a=b;b=t;flip=!flip;}
    if(b>c){int t=b;b=c;c=t;flip=!flip;}
    if(a>b){int t=a;a=b;b=t;flip=!flip;}
    BfmeE8 e1=points[b]-points[a];
    BfmeE8 e2=points[c]-points[a];
    if(flip){if(Perp_Dot_Product(e1,e2)>epsilon)break;}
    else{if(Perp_Dot_Product(e1,e2)< -epsilon)break;}
   }
   if(j==count) break;
  }
  if(std::find(hull.begin(),hull.end(),i)!=hull.end()) break;
  PushIndex(hull,(const int &)i);
 }
 ClearPoints(output);
 for(int *p=hull.begin();p!=hull.end();++p) output.push_back(points[*p]);
 return true;
}

#include "matrix3d.h"

// ?BfmeE8::BfmeE8 absent-from-retail
// Vector3::Cross_Product with its assert routed to a local stub: retail imports
// no _assert, but the (folded) check still shapes the transform loops below,
// and the header's unreferenced out-of-line copy would import __imp___assert.
static __declspec(noinline) void __cdecl CrossProductFailed(const char *, const char *, unsigned) {}
static __forceinline void CrossProduct(const Vector3 &a,const Vector3 &b,Vector3 *set_result) {
	(void)( (set_result != &a) || (CrossProductFailed("set_result != &a", __FILE__, 375), 0) );
	set_result->X = (a.Y * b.Z - a.Z * b.Y);
	set_result->Y = (a.Z * b.X - a.X * b.Z);
	set_result->Z = (a.X * b.Y - a.Y * b.X);
}
inline BfmeE8::BfmeE8(const Vector3 &v) : X(v.X), Y(v.Y) {}

// Retail's Coord3D copy constructor makes _Construct<Coord3D> the null-checked body at 0x002CA82C.
#include "Lib/Coord3DCtorView.h"
#include "Lib/Region2D.h"
// Suppress this TU's non-retail copy of ?erase@?$vector@UBfmePod8@@V?$allocator@UBfmePod8@@@_STL@@@_STL@@QAEPAUBfmePod8@@PAU3@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod8;
namespace _STL { template <> BfmePod8 * vector<BfmePod8,allocator<BfmePod8> >::erase(BfmePod8 *,BfmePod8 *); }
// The record view of stlport_vector_float4_469c61.cpp, whose member-wise copy gives retail's _Construct.
struct BfmeFloat4Record00469C61 {
	float x, y, z, w;
	BfmeFloat4Record00469C61() {}
	BfmeFloat4Record00469C61(const BfmeFloat4Record00469C61 &other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
	BfmeFloat4Record00469C61 &operator=(const BfmeFloat4Record00469C61 &other) { x=other.x; y=other.y; z=other.z; w=other.w; return *this; }
};
namespace _STL {
template<> inline void allocator<Coord3D>::deallocate(Coord3D *p, size_t) const { if (p) Rva00030830FreeAllocation(p); }
// Frees through _free (0x00030830) and stays inline-only (dllimport is never emitted): every call inlines it.
template<> __declspec(dllimport) __forceinline void allocator<BfmeFloat4Record00469C61>::deallocate(BfmeFloat4Record00469C61 *p, size_t) const { if (p) Rva00030830FreeAllocation(p); }
// The count-fill chain stays visible, so the caller's vector does not escape, and out of line as
// retail's rowed copies (0x0007C2AC, 0x000CA1D3, 0x002CA849, 0x002CA82C).
template<> inline __declspec(noinline) void _Construct<Coord3D, Coord3D>(Coord3D *__p, const Coord3D &__val) { _STLP_PLACEMENT_NEW (__p) Coord3D(__val); }
template<> inline __declspec(noinline) Coord3D *__uninitialized_fill_n<Coord3D *, unsigned int, Coord3D>(Coord3D *__first, unsigned int __n, const Coord3D &__x, const __false_type &)
{
	Coord3D *__cur = __first;
	for ( ; __n > 0; --__n, ++__cur)
		_Construct(&*__cur, __x);
	return __cur;
}
template<> inline __declspec(noinline) Coord3D *uninitialized_fill_n<Coord3D *, unsigned int, Coord3D>(Coord3D *__first, unsigned int __n, const Coord3D &__x)
{ return __uninitialized_fill_n(__first, __n, __x, __false_type()); }
template<> inline __declspec(noinline) _Vector_base<Coord3D, allocator<Coord3D> >::_Vector_base(size_t __n, const allocator<Coord3D> &__a)
	: _M_start(0), _M_finish(0), _M_end_of_storage(__a, 0)
{
	_M_start = _M_end_of_storage.allocate(__n);
	_M_finish = _M_start;
	_M_end_of_storage._M_data = _M_start + __n;
}
template<> inline __declspec(noinline) vector<Coord3D>::vector(size_t __n, const Coord3D &__val, const allocator<Coord3D> &__a)
	: _Vector_base<Coord3D, allocator<Coord3D> >(__n, __a) { this->_M_finish = uninitialized_fill_n(this->_M_start, __n, __val); }
template<> Region2D *vector<Region2D>::erase(Region2D *, Region2D *);
template<> inline __declspec(noinline) void vector<BfmeFloat4Record00469C61>::push_back(const BfmeFloat4Record00469C61 &__x) { if (this->_M_finish != this->_M_end_of_storage._M_data) { _Construct(this->_M_finish, __x); ++this->_M_finish; } else _M_insert_overflow(this->_M_finish, __x, _IsPODType(), 1UL, true); }
}

class PlaneClass
{
public:
	PlaneClass() {}
	// Inline-only (dllimport is never emitted): the link keeps the rowed copy at 0x00376D29.
	__declspec(dllimport) __forceinline PlaneClass(const Vector3 &normal, float dist) { N = normal; D = dist; }
	void Set(const Vector3 &normal, const Vector3 &point) { N = normal; D = Vector3::Dot_Product(normal, point); }
	PlaneClass(const Vector3 &point1, const Vector3 &point2, const Vector3 &point3) { Set(point1, point2, point3); }
	void Set(const Vector3 &point1, const Vector3 &point2, const Vector3 &point3);
	bool Compute_Intersection(const Vector3 &p0, const Vector3 &p1, float *set_t) const;

	Vector3 N;
	float D;
};

inline __declspec(noinline) bool PlaneClass::Compute_Intersection(const Vector3 & p0,const Vector3 & p1,float * set_t) const
{
	float num,den;
	den = Vector3::Dot_Product(N,p1-p0);
	if (den == 0.0f) {
		return false;
	}
	num = -(Vector3::Dot_Product(N,p0) - D);
	*set_t = num/den;
	if ((*set_t < 0.0f) || (*set_t > 1.0f)) {
		return false;
	}
	return true;
}

class FrustumClass
{
public:
	Matrix3D CameraTransform;
	PlaneClass Planes[6];
	Vector3 Corners[8];
};

class CameraClass
{
public:
	virtual void vf00();
	virtual void vf01();
	virtual void vf02();
	virtual void vf03();
	virtual void vf04();
	virtual void vf05();
	virtual void vf06();
	virtual void vf07();
	virtual void vf08();
	virtual void vf09();
	virtual void vf10();
	virtual void vf11();
	virtual void vf12();
	virtual void vf13();
	virtual void vf14();
	virtual void vf15();
	virtual void vf16();
	virtual void vf17();
	virtual void vf18();
	virtual void vf19();
	virtual void Validate_Transform() const;
	virtual void Set_Transform(const Matrix3D &m);

	const Matrix3D &Get_Transform() const { Validate_Transform(); return Transform; }
	const FrustumClass &Get_Frustum() const { Update_Frustum(); return Frustum; }
	void Get_Clip_Planes(float &znear, float &zfar) const;
	void Set_Clip_Planes(float znear, float zfar);
	void Set_View_Plane(const Vector2 &min, const Vector2 &max);
protected:
	void Update_Frustum() const;

public:
	char m_pad04[0x14];
	Matrix3D Transform;	// +0x18
	char m_pad48[0x100 - 0x48];
	FrustumClass Frustum;	// +0x100
	char m_pad1F0[0x3fc - 0x1f0];
	std::vector<BfmeFloat4Record00469C61> m_clipPlanes;	// +0x3FC
};

class AABoxClass
{
public:
	AABoxClass() {}
	Vector3 Center;
	Vector3 Extent;
};

class WorldHeightMap
{
public:
	int getXExtent() { return m_width; }
	int getYExtent() { return m_height; }
	char m_pad00[8];
	int m_width;
	int m_height;
};

class BaseHeightMapRenderObjClass
{
public:
	virtual void vf000();
	virtual void vf001();
	virtual void vf002();
	virtual void vf003();
	virtual void vf004();
	virtual void vf005();
	virtual void vf006();
	virtual void vf007();
	virtual void vf008();
	virtual void vf009();
	virtual void vf010();
	virtual void vf011();
	virtual void vf012();
	virtual void vf013();
	virtual void vf014();
	virtual void vf015();
	virtual void vf016();
	virtual void vf017();
	virtual void vf018();
	virtual void vf019();
	virtual void vf020();
	virtual void vf021();
	virtual void vf022();
	virtual void vf023();
	virtual void vf024();
	virtual void vf025();
	virtual void vf026();
	virtual void vf027();
	virtual void vf028();
	virtual void vf029();
	virtual void vf030();
	virtual void vf031();
	virtual void vf032();
	virtual void vf033();
	virtual void vf034();
	virtual void vf035();
	virtual void vf036();
	virtual void vf037();
	virtual void vf038();
	virtual void vf039();
	virtual void vf040();
	virtual void vf041();
	virtual void vf042();
	virtual void vf043();
	virtual void vf044();
	virtual void vf045();
	virtual void vf046();
	virtual void vf047();
	virtual void vf048();
	virtual void vf049();
	virtual void vf050();
	virtual void vf051();
	virtual void vf052();
	virtual void vf053();
	virtual void vf054();
	virtual void vf055();
	virtual void vf056();
	virtual void vf057();
	virtual void vf058();
	virtual void vf059();
	virtual void vf060();
	virtual void vf061();
	virtual void vf062();
	virtual void vf063();
	virtual void vf064();
	virtual void vf065();
	virtual void vf066();
	virtual void vf067();
	virtual void vf068();
	virtual void vf069();
	virtual void vf070();
	virtual void vf071();
	virtual void vf072();
	virtual void vf073();
	virtual void vf074();
	virtual void vf075();
	virtual void vf076();
	virtual void vf077();
	virtual void vf078();
	virtual void vf079();
	virtual void vf080();
	virtual void vf081();
	virtual void vf082();
	virtual void vf083();
	virtual void vf084();
	virtual void vf085();
	virtual void vf086();
	virtual void vf087();
	virtual void vf088();
	virtual void vf089();
	virtual void vf090();
	virtual void vf091();
	virtual void vf092();
	virtual void vf093();
	virtual void vf094();
	virtual void vf095();
	virtual void vf096();
	virtual void vf097();
	virtual void vf098();
	virtual void vf099();
	virtual void vf100();
	virtual void vf101();
	virtual void vf102();
	virtual void vf103();
	virtual void vf104();
	virtual void vf105();
	virtual void vf106();
	virtual void vf107();
	virtual void vf108();
	virtual void vf109();
	virtual void vf110();
	virtual void vf111();
	virtual void vf112();
	virtual void vf113();
	virtual void vf114();
	virtual void vf115();
	virtual void vf116();
	virtual void vf117();
	virtual void vf118();
	virtual void vf119();
	virtual void vf120();
	virtual void vf121();
	virtual void vf122();
	virtual void vf123();
	virtual void vf124();
	virtual void vf125();
	virtual void vf126();
	virtual void vf127();
	virtual void vf128();
	virtual void vf129();
	virtual void vf130();
	virtual void vf131();
	virtual void vf132();
	virtual void vf133();
	virtual void vf134();
	virtual void vf135();
	virtual void vf136();
	virtual void vf137();
	virtual void vf138();
	virtual void vf139();
	virtual void vf140();
	virtual void getShadowCameraBox(CameraClass *camera, AABoxClass *box);
	char m_pad04[0x37c0 - 4];
	WorldHeightMap *m_map;	// +0x37C0
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class GlobalData
{
public:
	char m_pad00[0x62];
	bool m_useShadowMap;	// +0x62
};
extern GlobalData *TheWritableGlobalData;

struct Db12
{
	int v0;
	float v1;
	float v2;
};
extern Db12 g_shadowMapSettings;

template <class T> inline const T &ShadowMin(const T &a, const T &b) { return b < a ? b : a; }
template <class T> inline const T &ShadowMax(const T &a, const T &b) { return a < b ? b : a; }

// The manager holds its cameras through RefCountPtr (WorldBuilder asserts name
// RefCountPtr<CameraClass>::operator->); release inlines operator-> to a member load.
template <class T> class RefCountPtr
{
public:
	T *operator->() const { return m_obj; }
	T &operator*() const { return *m_obj; }
	T *m_obj;
};

class W3DShadowMapManager
{
public:
	void UpdateShadowCamera();

private:
	RefCountPtr<CameraClass> m_camera;	// +0x00
	RefCountPtr<CameraClass> m_sceneCamera;	// +0x04
	Vector3 m_lightDirection;	// +0x08
};

typedef std::vector<Coord3D> PointList;

// UpdateShadowCamera 0x0007C8AE, WorldBuilder twin 0x7F0310; retail places it right after the hull
// helper. The Vector2 temps read through one pointer and the named translation follow WB.
void W3DShadowMapManager::UpdateShadowCamera()
{
	if (!TheWritableGlobalData->m_useShadowMap)
		return;
	if (!TheTerrainRenderObject)
		return;
	if (!_finite(m_sceneCamera->Get_Transform()[0][0]))
		return;

	Vector3 lightDir = m_lightDirection;
	lightDir.Normalize();
	Vector3 axis1;
	CrossProduct(lightDir, Vector3(1.0f, 0.0f, 0.0f), &axis1);
	if (axis1.Length2() < 0.1f)
		CrossProduct(lightDir, Vector3(0.0f, 1.0f, 0.0f), &axis1);
	axis1.Normalize();
	Vector3 axis2;
	CrossProduct(lightDir, axis1, &axis2);
	axis2.Normalize();
	Matrix3D lightTm;
	lightTm.Set(axis1, axis2, lightDir, Vector3(0.0f, 0.0f, 0.0f));
	Matrix3D lightInv;
	lightTm.Get_Orthogonal_Inverse(lightInv);

	AABoxClass box;
	TheTerrainRenderObject->getShadowCameraBox(&*m_sceneCamera, &box);
	float minZ = box.Center.Z - box.Extent.Z;
	PlaneClass ground(Vector3(0.0f, 0.0f, -1.0f), ShadowMax(minZ, g_shadowMapSettings.v2));
	PlaneClass ceiling(Vector3(0.0f, 0.0f, 1.0f), box.Center.Z + box.Extent.Z + 400.0f);

	Vector3 corners[8];
	float znear = 0.0f;
	float zfar = 0.0f;
	m_sceneCamera->Get_Clip_Planes(znear, zfar);
	m_sceneCamera->Set_Clip_Planes(znear, ShadowMin(zfar, g_shadowMapSettings.v1));
	const FrustumClass &frustum = m_sceneCamera->Get_Frustum();
	for (int i = 0; i < 4; i++) {
		corners[i] = frustum.Corners[i];
		float t = 0.0f;
		if (ground.Compute_Intersection(frustum.Corners[i], frustum.Corners[i + 4], &t))
			corners[i + 4] = (frustum.Corners[i + 4] - frustum.Corners[i]) * t + frustum.Corners[i];
		else
			corners[i + 4] = frustum.Corners[i + 4];
	}
	m_sceneCamera->Set_Clip_Planes(znear, zfar);
	lightInv.mulVector3Array(corners, 8);

	std::vector<BfmeE8> points;
	for (unsigned i = 0; i < 8; i++)
		points.push_back(BfmeE8(corners[i]));
	std::vector<BfmeE8> hull;
	Rva0007C637(points, hull, 0.0001f);

	Coord3D blank;
	PointList hullPts(hull.size(), blank);
	for (unsigned i = 0; i < hull.size(); i++)
		Matrix3D::Transform_Vector(lightTm, Vector3(hull[i].X, hull[i].Y, 0.0f), (Vector3 *)&hullPts[i]);
	PointList groundPts(hullPts.size(), blank);
	PointList ceilingPts(hullPts.size(), blank);
	for (unsigned i = 0; i < hull.size(); i++) {
		float t = 0.0f;
		ground.Compute_Intersection((const Vector3 &)hullPts[i], lightDir + (const Vector3 &)hullPts[i], &t);
		(Vector3 &)groundPts[i] = lightDir * t + (const Vector3 &)hullPts[i];
		ceiling.Compute_Intersection((const Vector3 &)hullPts[i], lightDir + (const Vector3 &)hullPts[i], &t);
		(Vector3 &)ceilingPts[i] = lightDir * t + (const Vector3 &)hullPts[i];
	}

	Vector2 vmin(&corners[0].X);
	Vector2 vmax(&corners[0].X);
	for (unsigned i = 1; i < 8; i++) {
		vmin.Update_Min(Vector2(&corners[i].X));
		vmax.Update_Max(Vector2(&corners[i].X));
	}
	corners[0].Set(vmin.X, vmin.Y, 0.0f);
	corners[1].Set(vmin.X, vmax.Y, 0.0f);
	corners[2].Set(vmax.X, vmin.Y, 0.0f);
	corners[3].Set(vmax.X, vmax.Y, 0.0f);
	lightTm.mulVector3Array(corners, 4);

	if (fabs(lightDir.Z) < 0.001) {
		if (fabs(lightDir.X) > fabs(lightDir.Y)) {
			ground.Set(Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
			ceiling.Set(Vector3(1.0f, 0.0f, 0.0f), Vector3(TheTerrainRenderObject->m_map->getXExtent() * 10.0f, 0.0f, 0.0f));
		} else {
			ground.Set(Vector3(0.0f, -1.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
			ceiling.Set(Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, TheTerrainRenderObject->m_map->getYExtent() * 10.0f, 0.0f));
		}
	}
	for (int i = 0; i < 4; i++) {
		float t = 0.0f;
		ground.Compute_Intersection(corners[i], lightDir + corners[i], &t);
		corners[i + 4] = lightDir * t + corners[i];
		ceiling.Compute_Intersection(corners[i], lightDir + corners[i], &t);
		corners[i] = lightDir * t + corners[i];
	}
	lightInv.mulVector3Array(corners, 8);

	float zmin = corners[0].Z;
	float zmax = corners[0].Z;
	for (unsigned i = 1; i < 8; i++) {
		if (corners[i].Z < zmin)
			zmin = corners[i].Z;
		if (corners[i].Z > zmax)
			zmax = corners[i].Z;
	}
	Vector2 center = (vmin + vmax) / 2.0f;
	vmax -= center;
	vmin -= center;
	Vector3 trans(center.X, center.Y, zmin);
	lightTm.Translate(trans);
	lightTm.Scale(1.0f, -1.0f, -1.0f);

	m_camera->Set_Clip_Planes(0.0f, zmax - zmin);
	m_camera->Set_View_Plane(vmin, vmax);
	m_camera->Set_Transform(lightTm);
	((std::vector<Region2D> &)m_camera->m_clipPlanes).clear();
	for (unsigned i = 0; i < ceilingPts.size(); i++) {
		PlaneClass plane((const Vector3 &)ceilingPts[i], (const Vector3 &)groundPts[i],
			(const Vector3 &)ceilingPts[(i + 1) % ceilingPts.size()]);
		m_camera->m_clipPlanes.push_back((const BfmeFloat4Record00469C61 &)plane);
	}
	m_camera->m_clipPlanes.push_back((const BfmeFloat4Record00469C61 &)ground);
	m_camera->m_clipPlanes.push_back((const BfmeFloat4Record00469C61 &)ceiling);
}
