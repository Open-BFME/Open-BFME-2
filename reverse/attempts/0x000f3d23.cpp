// ?updateVolumes@W3DVolumetricShadow@@IAEXM@Z
// partial score=0.8676421876421876 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
class Vector3 {public: Vector3(){} Vector3(float x,float y,float z):X(x),Y(y),Z(z){} Vector3(const Vector3&v):X(v.X),Y(v.Y),Z(v.Z){} float X,Y,Z; Vector3&operator=(const Vector3&v){X=v.X;Y=v.Y;Z=v.Z;return *this;} Vector3& operator+=(const Vector3 &v){X+=v.X;Y+=v.Y;Z+=v.Z;return *this;}};
class Matrix3D {public: float m[3][4]; Vector3 Get_Translation()const{return Vector3(m[0][3],m[1][3],m[2][3]);}};
inline void *operator new(unsigned int,void*p)throw(){return p;}
class AABoxClass {public: AABoxClass(){} Vector3 Center,Extent; void Translate(const Vector3&v){Center+=v;}};
class SphereClass {public: SphereClass(){} Vector3 Center;float Radius;};
struct Region3D {Region3D(const Region3D&);float x,y,z,a,b,c;};
class FrustumClass;
class CollisionMath {public:enum OverlapType {OUTSIDE=1,INSIDE=2,OVERLAPPED=8};static OverlapType Overlap_Test(const FrustumClass&,const SphereClass&);static OverlapType Overlap_Test(const FrustumClass&,const AABoxClass&);};
class MeshClass;
class RenderObjClass {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual int Class_ID();
virtual void slot4();
virtual MeshClass *Get_Mesh();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
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
virtual void Validate_Transform();
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
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual const AABoxClass&Get_Bounding_Box();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual void slot82();
virtual void slot83();
virtual void slot84();
virtual void slot85();
virtual void slot86();
virtual void slot87();
virtual void slot88();
virtual void slot89();
virtual void slot90();
virtual void slot91();
virtual void slot92();
virtual void slot93();
virtual void slot94();
virtual void slot95();
virtual int Is_Really_Visible();
virtual int Is_Not_Hidden_At_All();
virtual void slot98();
virtual void slot99();
virtual void slot100();
virtual void slot101();
virtual void slot102();
virtual void slot103();
virtual void slot104();
virtual void slot105();
virtual void slot106();
virtual void slot107();
virtual void slot108();
virtual void slot109();
virtual void slot110();
virtual void slot111();
virtual void slot112();
virtual void slot113();
virtual void slot114();
virtual void slot115();
virtual void slot116();
virtual void slot117();
virtual void slot118();
virtual void slot119();
virtual void slot120();
virtual void slot121();
virtual void slot122();
virtual void slot123();
virtual void slot124();
virtual void slot125();
virtual void slot126();
virtual void slot127();
virtual void slot128();
virtual void slot129();
virtual void slot130();
virtual void slot131();
virtual void slot132();
virtual void slot133();
virtual void slot134();
virtual void slot135();
virtual void slot136();
virtual void slot137();
virtual MeshClass *Peek_Lod_Model(int,int);
Vector3 Get_Position()const;
char pad04[0x14]; Matrix3D transform;
};
class MeshClass:public RenderObjClass {public:void Get_Deformed_Vertices(Vector3*);};
class TCBSpline3DClass {public:class TCBClass;};
template<class T>class DynamicVectorClass {public:virtual bool Resize(int,const T*);Vector3 *vector;int capacity;};
extern DynamicVectorClass<TCBSpline3DClass::TCBClass> g_Va00DEBE0C;
extern FrustumClass g_Va00DEBD00;
extern const Matrix3D Rva00DDD9D0Identity;
struct MeshRecord{char pad00[8];Vector3*verts;int index;int dirty;int pad14;int count;char pad1C[0x14];bool deformed;char tail[3];};
struct W3DShadowGeometry{char pad00[0x14];MeshRecord meshes[160];int count;};
struct Geometry {char pad[0x1c];AABoxClass box;SphereClass sphere;int state;};
struct W3DRenderTask {W3DRenderTask*next;char data[8];};
struct VB{char pad[0x18];W3DRenderTask*head;};
struct VBSlot{char pad[8];VB*vb;};
class W3DVolumetricShadowManager{public:char pad[4];W3DRenderTask*head;void addDynamicShadowTask(W3DRenderTask*t){W3DRenderTask*old=head;head=t;head->next=old;}};
extern W3DVolumetricShadowManager*TheW3DVolumetricShadowManager;
class W3DVolumetricShadow {protected:
__forceinline Geometry*&volume(int j){return *(Geometry**)((unsigned int)this+0x80+4*j);}
__forceinline VBSlot*&vb(int j){return *(VBSlot**)((unsigned int)this+0x300+4*j);}
__forceinline W3DRenderTask&task(int j){return *(W3DRenderTask*)((unsigned int)this+0x800+j*12);}
void updateVolumes(float);void updateMeshVolume(int,int,const Matrix3D*,const AABoxClass&,float);
char pad[0x6c];W3DShadowGeometry*geometry;RenderObjClass*robj;char pad74[0xc];Geometry*volumes[160];VBSlot*vbs[160];char pad580[0x280];W3DRenderTask tasks[160];
};
void W3DVolumetricShadow::updateVolumes(float zoffset){
int j;RenderObjClass *hlod=robj;MeshClass*mesh;static AABoxClass aaBox;static SphereClass sphere;int meshIndex;
bool parentVis=robj->Is_Really_Visible()!=0;
int recordOffset=0;for(j=0;j<geometry->count;j++,recordOffset+=0x34){
meshIndex=((MeshRecord*)((char*)geometry+0x14+recordOffset))->index;
if(meshIndex>=0)mesh=hlod->Peek_Lod_Model(0,meshIndex);else mesh=(MeshClass*)robj;
if(mesh){if(!mesh->Is_Not_Hidden_At_All())continue;
MeshRecord *info=(MeshRecord*)((char*)geometry+0x14+recordOffset);mesh->Validate_Transform();const Matrix3D*meshXform=&mesh->transform;float extraZ=0;
if(info->deformed&&mesh->Class_ID()==0){
if(g_Va00DEBE0C.capacity<info->count)g_Va00DEBE0C.DynamicVectorClass<TCBSpline3DClass::TCBClass>::Resize(info->count,0);
mesh->Get_Mesh()->Get_Deformed_Vertices(g_Va00DEBE0C.vector);Vector3 *vertices=g_Va00DEBE0C.vector;info->dirty=0;info->verts=vertices;extraZ=100.0f;meshXform=&Rva00DDD9D0Identity;
}
int currentIndex=*(volatile int*)&j;updateMeshVolume(currentIndex,0,meshXform,mesh->Get_Bounding_Box(),robj->Get_Position().Z-(extraZ+zoffset));
if(volume(currentIndex)){
if(volume(currentIndex)->state==8){if(parentVis)volume(currentIndex)->state=2;else{
sphere=volume(currentIndex)->sphere;float tx=meshXform->m[0][3],ty=meshXform->m[1][3],tz=meshXform->m[2][3];sphere.Center.X=tx+sphere.Center.X;sphere.Center.Y=ty+sphere.Center.Y;sphere.Center.Z=tz+sphere.Center.Z;CollisionMath::OverlapType result=CollisionMath::Overlap_Test(g_Va00DEBD00,sphere);
if(result==8){new (&aaBox) Region3D(*(const Region3D*)&volume(currentIndex)->box);float tx=meshXform->m[0][3],ty=meshXform->m[1][3],tz=meshXform->m[2][3];aaBox.Center.X=tx+aaBox.Center.X;aaBox.Center.Y=ty+aaBox.Center.Y;aaBox.Center.Z=tz+aaBox.Center.Z;if(CollisionMath::Overlap_Test(g_Va00DEBD00,aaBox)!=1)volume(currentIndex)->state=2;else volume(currentIndex)->state=1;}else volume(currentIndex)->state=result;
}}
if(volume(currentIndex)->state==2){int taskIndex=*(volatile int*)&j;VBSlot*vbSlot=vb(taskIndex);if(vbSlot){W3DRenderTask*old=vbSlot->vb->head;vbSlot->vb->head=&task(taskIndex);vbSlot->vb->head->next=old;}else TheW3DVolumetricShadowManager->addDynamicShadowTask(&task(taskIndex));}
}
}}
}
