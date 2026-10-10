// ?queueDualDecal@W3DProjectedShadowManager@@QAEXPAVW3DDualProjectedShadow@@@Z
// partial score=0.6302067432599086 date=2026-10-10
// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// Caller queueDualDecal @10A736..10B9B54737 RET4: named WB8CEAC0
//17990B analogue; ZH queueDecal at BF1 575ba2b04 semantic guide.
// Native two textures and size/position/offset fields plus manager254..270
// and RAII buffer locks; true emits4805 versus native4737; no Code port.
// The older helper provenance below applies to the local algorithms.
// BFME 1 W3DProjectedShadowDecalHelpers.cpp, donor revision
// 1399ad37d42ea52a63829e417c46a1ba9ed2cd20, compiled with BFME 2 flags above.
// These file-static algorithms come from ZH queueDecal: flatten/normalise the
// transform axes, and find the extrema of four projected corner coordinates.
// Their original private names are unknown, so names retain target addresses.
// Native axes body 0x108E7A..0x108FBD (323B), Ghidra FUN_00508e7a. Calls at
// 0x10ACAB / 0x10ACBF / 0x10CB9C pass Matrix3D in ESI and two Vector3 outputs
// in ECX/EDX. X/Y basis elements are +0/+0x10 and +4/+0x14; output Z is zero.
// Native extrema body 0x108E33..0x108E7A (71B), immediately after the thunk
// at 0x108E28. Inputs use XMM1/2/3 and one stack float; hidden Vector2 output
// is EAX. The projected-range body at 0x108FBD inlines the same extrema logic.
// A compiler-visible caller preserves both private conventions, as MSVC 7.1
// derives them from same-unit calls. It is an emission pattern, not a retail
// caller recovery. All body bytes and compiler float literals are verified.
#include "wwmath.h"
#include "vector3.h"
#include "matrix3d.h"
#include <math.h>
#define __max(a,b) (((a)>(b))?(a):(b))
#define __min(a,b) (((a)<(b))?(a):(b))

// Scoped storage views use the evidenced 12B vector, 8B pair, and 3x4 matrix
// representations without defining copies of the public math-library methods.
class Rva00108E7AVector
{
public:
    float X, Y, Z;
    WWINLINE Rva00108E7AVector() {}
    WWINLINE Rva00108E7AVector(float x, float y, float z) { X=x; Y=y; Z=z; }
    WWINLINE Rva00108E7AVector &operator=(const Rva00108E7AVector &v)
    { X=v.X; Y=v.Y; Z=v.Z; return *this; }
    WWINLINE Rva00108E7AVector &operator*=(float k)
    { X=X*k; Y=Y*k; Z=Z*k; return *this; }
    WWINLINE void Set(float x, float y, float z) { X=x; Y=y; Z=z; }
    WWINLINE float Length() const { return WWMath::Sqrt(X*X+Y*Y+Z*Z); }
};
class Rva00108E33Pair
{
public:
    float X, Y;
    WWINLINE Rva00108E33Pair(float x, float y) { X=x; Y=y; }

};
class Rva00108E7AMatrix
{
public:
    float Row[3][4];
    WWINLINE Rva00108E7AVector Get_X_Vector() const
    { return Rva00108E7AVector(Row[0][0],Row[1][0],Row[2][0]); }
    WWINLINE Rva00108E7AVector Get_Y_Vector() const
    { return Rva00108E7AVector(Row[0][1],Row[1][1],Row[2][1]); }
};

static void decalAxesRva00108E7A(const Rva00108E7AMatrix &objXform, Rva00108E7AVector &uVector, Rva00108E7AVector &vVector)
{
	uVector = objXform.Get_X_Vector();
	uVector.Z = 0.0f;
	float vecLength = uVector.Length();
	if (vecLength != 0.0f) {
		uVector *= 1.0f / vecLength;
		vVector.Set(uVector.Y, -uVector.X, 0.0f);
	} else {
		vVector = objXform.Get_Y_Vector();
		vVector.Z = 0.0f;
		vecLength = vVector.Length();
		if (vecLength != 0.0f)
			vVector *= 1.0f / vecLength;
		else
			vVector.Set(0.0f, -1.0f, 0.0f);
		uVector.Set(-vVector.Y, vVector.X, 0.0f);
	}
}

static Rva00108E33Pair minMax4Rva00108E33(float a, float b, float c, float d)
{
	float lo, hi;
	if (a < b) {
		lo = a;
		hi = b;
	} else {
		lo = b;
		hi = a;
	}
	if (c < d) {
		if (c < lo)
			lo = c;
		if (d > hi)
			hi = d;
	} else {
		if (d < lo)
			lo = d;
		if (c > hi)
			hi = c;
	}
	return Rva00108E33Pair(lo, hi);
}

static WWINLINE Rva00108E7AVector operator*(float k,const Rva00108E7AVector&a){return Rva00108E7AVector(a.X*k,a.Y*k,a.Z*k);}
static WWINLINE Rva00108E7AVector operator+(const Rva00108E7AVector&a,const Rva00108E7AVector&b){return Rva00108E7AVector(a.X+b.X,a.Y+b.Y,a.Z+b.Z);}
static void projectRangesRva00108FBD(const Rva00108E7AVector &axisA, const Rva00108E7AVector &axisB, float sizeA, float sizeB,
	float offA, float offB, Rva00108E33Pair &xr, Rva00108E33Pair &yr)
{
	Rva00108E7AVector a0 = -((offA + 0.5f) * sizeA) * axisA;
	Rva00108E7AVector a1 = (0.5f - offA) * sizeA * axisA;
	Rva00108E7AVector b0 = -((offB + 0.5f) * sizeB) * axisB;
	Rva00108E7AVector b1 = (0.5f - offB) * sizeB * axisB;
	Rva00108E7AVector c0 = b0 + a0;
	Rva00108E7AVector c1 = b0 + a1;
	Rva00108E7AVector c2 = b1 + a1;
	Rva00108E7AVector c3 = b1 + a0;
	xr = minMax4Rva00108E33(c0.X, c1.X, c2.X, c3.X);
	yr = minMax4Rva00108E33(c0.Y, c1.Y, c2.Y, c3.Y);
}


class Object {public:int rva0028B511()const;};
class Drawable {public:char pad[0xfc];Object*object;};
struct DrawableInfo {void*unknown;Drawable*drawable;};
class RenderObjClass{public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
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
virtual void slot66();
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
virtual DrawableInfo*Get_User_Data();
Vector3 Get_Position()const;
char pad04[0x14];Matrix3D transform;
};
class TerrainLogic {public:
virtual void pad0();
virtual void pad1();
virtual void pad2();
virtual void pad3();
virtual void pad4();
virtual void pad5();
virtual void pad6();
virtual float getLayerHeight(float,float,int,Rva00108E7AVector*,bool);
};extern TerrainLogic*TheTerrainLogic;
static float layerHeightRva001086EC(RenderObjClass*robj,const Rva00108E7AVector&pos,Rva00108E7AVector&normal){
 if(robj&&robj->Get_User_Data()){
 Drawable*draw=robj->Get_User_Data()->drawable;char*drawBytes=(char*)draw;Object*object=*(Object**)(drawBytes+0xfc);
 if(object){int layer=object->rva0028B511();if(layer!=1&&TheTerrainLogic){Rva00108E7AVector n;float height=TheTerrainLogic->getLayerHeight(pos.X,pos.Y,layer,&n,true);normal=n;return height+1.5f;}}
 }
 normal.Set(0,0,1);return 0;
}

class W3DShadowTexture;
struct DecalCenter{float X,Y,Z;};
struct DecalChildView{DecalCenter getPosition()const{return center;} char pad[8];DecalCenter center;char pad14[0xc];float angle;char pad24[0x34];float sizeX,sizeY;char pad60[8];W3DShadowTexture*texture;float offsetU,offsetV;};
class W3DDualProjectedShadow {public:DecalCenter getPosition()const{return pos;} W3DShadowTexture*getTexture(int i)const{DecalChildView*c=child[i];return c?c->texture:0;} void getSize(int i,float*x,float*y)const{DecalChildView*c=child[i];*x=c->sizeX;*y=c->sizeY;} char pad[8];DecalCenter pos;char pad14[0xc];float angle;int pad24;unsigned diffuse;char pad2c[8];int type;char pad38[0x20];DecalChildView*child[2];RenderObjClass*robj;};
class Rva001089EA {public:void rva001089EA(int,float*,float*);};
struct DecalVertex {float x,y,z;unsigned diffuse;float u0,v0,u1,v1;};
class VertexBufferClass {public:class AppendLockClass{public:AppendLockClass(VertexBufferClass*,unsigned,unsigned,int);~AppendLockClass();VertexBufferClass*buffer;DecalVertex*vertices;char lock[4];};};
class IndexBufferClass {public:class AppendLockClass{public:AppendLockClass(IndexBufferClass*,unsigned,unsigned,int);~AppendLockClass();IndexBufferClass*buffer;unsigned short*indices;char lock[4];};};
class BoundedShortGrid {public:short rva00062A58(int,int);};
class WorldHeightMap {public:char pad[0x10];int border;};
class Gen_0074B410 {public:bool bfmeBitA(int,int)const;};
class BaseHeightMapRenderObjClass {public:char pad[0x37c0];WorldHeightMap*map;};
extern BaseHeightMapRenderObjClass*TheTerrainRenderObject;
extern int g_Va00DEC2E4,g_Va00DEC2E8,g_Va00DEC2DC,g_Va00DEC2E0;
enum ShadowType {SHADOW_NONE=0};
class W3DProjectedShadowManager {public:
 void queueDualDecal(W3DDualProjectedShadow*);
 void flushDecals(ShadowType,W3DShadowTexture*,W3DShadowTexture*,int);
 char pad[0x254];VertexBufferClass*vertexBuffer;IndexBufferClass*indexBuffer;int vertsInBuffer,startVertex,indicesInBuffer,startIndex,polysInBatch,vertsInBatch;
};
void W3DProjectedShadowManager::queueDualDecal(W3DDualProjectedShadow*shadow){
 W3DShadowTexture *texture0=shadow->getTexture(0);
 W3DShadowTexture *texture1=shadow->getTexture(1);
 if(!texture0||!texture1)return;
 float sx0,sy0,sx1,sy1;shadow->getSize(0,&sx0,&sy0);shadow->getSize(1,&sx1,&sy1);
 if((sx0==0||sy0==0)&&(sx1==0||sy1==0))return;
 Matrix3D objXform(true);Vector3 objPos(0,0,0);Rva00108E7AVector normal;
 float layerHeight=0;RenderObjClass*robj=shadow->robj;
 if(robj){objPos=robj->Get_Position();objPos.Z=0;robj->Validate_Transform();objXform=robj->transform;layerHeight=layerHeightRva001086EC(robj,*(Rva00108E7AVector*)&objPos,normal);}
 else {DecalCenter p=shadow->getPosition();objPos.Set(p.X,p.Y,p.Z);objPos.Z=0;objXform.Rotate_Z(shadow->angle);}
 Matrix3D rotations[2];rotations[0].Make_Identity();rotations[1].Make_Identity();
 rotations[0].Rotate_Z(shadow->angle+shadow->child[0]->angle);rotations[1].Rotate_Z(shadow->child[1]->angle+shadow->angle);
 Rva00108E7AVector u[2],v[2];
 decalAxesRva00108E7A(*(Rva00108E7AMatrix*)&rotations[0],u[0],v[0]);decalAxesRva00108E7A(*(Rva00108E7AMatrix*)&rotations[1],u[1],v[1]);
 DecalCenter childPos0=shadow->child[0]->getPosition(),childPos1=shadow->child[1]->getPosition();childPos0.Z=0;childPos1.Z=0;
 Vector3 centers[2];Matrix3D::Transform_Vector(objXform,*(Vector3*)&childPos0,&centers[0]);Matrix3D::Transform_Vector(objXform,*(Vector3*)&childPos1,&centers[1]);
 float ou0=0,ov0=0,ou1=0,ov1=0;
 if(shadow->child[0]){ou0=shadow->child[0]->offsetU;ov0=shadow->child[0]->offsetV;}
 ((Rva001089EA*)shadow)->rva001089EA(1,&ou1,&ov1);
 Rva00108E33Pair xr[2]={Rva00108E33Pair(0,0),Rva00108E33Pair(0,0)},yr[2]={Rva00108E33Pair(0,0),Rva00108E33Pair(0,0)};
 projectRangesRva00108FBD(u[0],v[0],sx0,sy0,ou0,ov0,xr[0],yr[0]);projectRangesRva00108FBD(u[1],v[1],sx1,sy1,ou1,ov1,xr[1],yr[1]);
 centers[0].X+=objPos.X;centers[0].Y+=objPos.Y;centers[1].X+=objPos.X;centers[1].Y+=objPos.Y;
 float maxX=__max(centers[0].X+xr[0].Y,centers[1].X+xr[1].Y);
 float minX=__min(centers[0].X+xr[0].X,centers[1].X+xr[1].X);
 float maxY=__max(centers[0].Y+yr[0].Y,centers[1].Y+yr[1].Y);
 float minY=__min(centers[0].Y+yr[0].X,centers[1].Y+yr[1].X);
 if(sx0!=0)u[0]*=1.0f/sx0;else u[0].Set(0,0,0);if(sx1!=0)u[1]*=1.0f/sx1;else u[1].Set(0,0,0);
 if(sy0!=0)v[0]*=1.0f/sy0;else v[0].Set(0,0,0);if(sy1!=0)v[1]*=1.0f/sy1;else v[1].Set(0,0,0);
 WorldHeightMap*hmap=TheTerrainRenderObject->map;int borderSize=hmap->border;
 ou0+=0.5f;ou1+=0.5f;ov0+=0.5f;ov1+=0.5f;
 int startX=(int)(float)floor(minX*0.1f)+borderSize,endX=(int)(float)ceil(maxX*0.1f)+borderSize;
 int startY=(int)(float)floor(minY*0.1f)+borderSize,endY=(int)(float)ceil(maxY*0.1f)+borderSize;
 startX=__max(startX,g_Va00DEC2E4);startX=__min(startX,g_Va00DEC2DC);startY=__max(startY,g_Va00DEC2E8);startY=__min(startY,g_Va00DEC2E0);
 endX=__max(endX,g_Va00DEC2E4);endX=__min(endX,g_Va00DEC2DC);endY=__max(endY,g_Va00DEC2E8);endY=__min(endY,g_Va00DEC2E0);
 int numExtraX=endX-startX+1-104;if(numExtraX>0){int a=(int)(float)floor(numExtraX*0.5f);startX+=a;endX-=numExtraX-a;}
 int numExtraY=endY-startY+1-104;if(numExtraY>0){int a=(int)(float)floor(numExtraY*0.5f);startY+=a;endY-=numExtraY-a;}
 int vertsPerRow=endX-startX+1,vertsPerColumn=endY-startY+1;if(vertsPerRow<=1||vertsPerColumn<=1)return;
 int numVerts=vertsPerRow*vertsPerColumn,numCells=(endX-startX)*(endY-startY),numIndex=numCells*6;
 bool flushed=false;if(vertsInBuffer+numVerts>32768||indicesInBuffer+numIndex>65536){flushDecals((ShadowType)shadow->type,texture0,texture1,0);startVertex=startIndex=polysInBatch=vertsInBatch=vertsInBuffer=indicesInBuffer=0;flushed=true;}
 int flags=flushed?0x2000:0x1000;
 {
 VertexBufferClass::AppendLockClass vl(vertexBuffer,vertsInBuffer,numVerts,flags);DecalVertex*pvVertices=vl.vertices;if(!pvVertices)return;
 IndexBufferClass::AppendLockClass il(indexBuffer,indicesInBuffer,numIndex,flags);unsigned short*pvIndices=il.indices;if(!pvIndices)return;
 Vector3 hmapVertex;unsigned diffuse=shadow->diffuse;int i,j,k;
 if(layerHeight){for(j=startY;j<=endY;j++){hmapVertex.Y=(j-borderSize)*10.0f;for(i=startX;i<=endX;i++){hmapVertex.X=(i-borderSize)*10.0f;hmapVertex.Z=__max((float)(unsigned short)((BoundedShortGrid*)hmap)->rva00062A58(i,j)*0.0390625f,layerHeight);
 pvVertices->x=hmapVertex.X;pvVertices->y=hmapVertex.Y;pvVertices->z=hmapVertex.Z;pvVertices->diffuse=diffuse;
 pvVertices->u0=Vector3::Dot_Product(*(Vector3*)&u[0],hmapVertex-centers[0])+ou0;pvVertices->v0=Vector3::Dot_Product(*(Vector3*)&v[0],hmapVertex-centers[0])+ov0;
 pvVertices->u1=Vector3::Dot_Product(*(Vector3*)&u[1],hmapVertex-centers[1])+ou1;pvVertices->v1=Vector3::Dot_Product(*(Vector3*)&v[1],hmapVertex-centers[1])+ov1;pvVertices++;
 }}}
 else{for(j=startY;j<=endY;j++){hmapVertex.Y=(j-borderSize)*10.0f;for(i=startX;i<=endX;i++){hmapVertex.X=(i-borderSize)*10.0f;hmapVertex.Z=(float)(unsigned short)((BoundedShortGrid*)hmap)->rva00062A58(i,j)*0.0390625f+0.01f*10.0f;
 pvVertices->x=hmapVertex.X;pvVertices->y=hmapVertex.Y;pvVertices->z=hmapVertex.Z;pvVertices->diffuse=diffuse;
 pvVertices->u0=Vector3::Dot_Product(*(Vector3*)&u[0],hmapVertex-centers[0])+ou0;pvVertices->v0=Vector3::Dot_Product(*(Vector3*)&v[0],hmapVertex-centers[0])+ov0;
 pvVertices->u1=Vector3::Dot_Product(*(Vector3*)&u[1],hmapVertex-centers[1])+ou1;pvVertices->v1=Vector3::Dot_Product(*(Vector3*)&v[1],hmapVertex-centers[1])+ov1;pvVertices++;
 }}}
 int rowStart;for(j=startY,rowStart=0;j<endY;j++,rowStart+=vertsPerRow){for(i=rowStart,k=startX;k<endX;i++,k++){
 if(((Gen_0074B410*)hmap)->bfmeBitA(k,j)){
 pvIndices[0]=i+1+vertsInBatch;pvIndices[1]=i+vertsPerRow+vertsInBatch;pvIndices[2]=i+vertsInBatch;pvIndices[3]=i+1+vertsInBatch;pvIndices[4]=i+1+vertsPerRow+vertsInBatch;pvIndices[5]=i+vertsPerRow+vertsInBatch;
 }else{pvIndices[0]=i+vertsInBatch;pvIndices[1]=i+1+vertsPerRow+vertsInBatch;pvIndices[2]=i+vertsPerRow+vertsInBatch;pvIndices[3]=i+vertsInBatch;pvIndices[4]=i+1+vertsInBatch;pvIndices[5]=i+1+vertsPerRow+vertsInBatch;}
 pvIndices+=6;
 }}
 }
 polysInBatch+=numCells*2;vertsInBuffer+=numVerts;vertsInBatch+=numVerts;indicesInBuffer+=numIndex;
}
