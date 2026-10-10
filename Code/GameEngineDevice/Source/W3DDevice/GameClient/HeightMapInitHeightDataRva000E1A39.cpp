// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Target nativeE1A39..E1C1A is481B RET16, with four borrowed arguments.
// ZH HeightMapRenderObjClass::initHeightData/freeIndexVertexBuffers are the
// primary allocation/lifetime guide; target uses background tile objects
// rather than per-buffer pointers and captures map identity before base init.
// Original target API spelling is unproven; retain existing E15D1 receiver.
// Native stores/calls and matched134B E15D1 establish map37C0, backup3884,
// tile array3888/count388C/cols3890/rows3894 and refresh byte3930. TileD4
// stride is independently present in the owned vector-deleting helperE1072;
// its owned187B element destructor112291 supplies the established neutral
// Rva00112291TerrainOwner view. Constructor callback112DBE initializes its
// measured prefix; its original name/complete layout remain uncertain.
// Native reuse refreshes the tile quartet then retains map; allocation
// initializes each tile with map and16-cell coordinates then refreshes it.
// Function-wide i/j retain the native shared stack homes across branches.
// CleanupE14C4..E153A is118B. A scoped DX8 lock reproduces its cleanup state
// and guarantees release during tile-array destruction; explicit reset order
// is cols/rows/count. The emitted nonvirtual78B vector-deleting helper is a
// complete byte-and-relocation twin of the existing address-derived owner.
void* __cdecl operator new[](unsigned int);
void __cdecl operator delete[](void*);
void __cdecl operator delete(void*);
class Rva000AD9AB{public:void rva000AD9FE();char pad[8];int width,height;};
class Rva0006D6D9{public:int rva0006D6D9(int,int,Rva000AD9AB*,void*);};
class Rva00112291TerrainOwner{public:Rva00112291TerrainOwner();~Rva00112291TerrainOwner();char bytes[0xd4];};
class Rva0011216CSlotQuartet{public:void rva00112197();};
class Rva00113110Holder{public:void rva00113110(void*);};
class RvaRef;
class Rva00111F0E{public:void rva00111F6F(RvaRef*,int,int,int);};
class Rva000E15D1{public:int rva000E1A39(int,int,Rva000AD9AB*,void*);void rva000E14C4();void rva000E153A();
char pad0[0x37c0];Rva000AD9AB*map;char pad1[0x3884-0x37c4];void**backup;Rva00112291TerrainOwner*tiles;int count,cols,rows;char pad2[0x3930-0x3898];bool flag;};
int Rva000E15D1::rva000E1A39(int x,int y,Rva000AD9AB*pMap,void*lights){
int i,j;
bool same=pMap==map;
((Rva0006D6D9*)this)->rva0006D6D9(x,y,pMap,lights);
int numX=(pMap->width+14)/16;
int numY=(pMap->height+14)/16;
int num=numX*numY;
pMap->rva000AD9FE();
if(same && tiles && cols==numX && rows==numY){
 for(i=0;i<cols;++i)for(j=0;j<rows;++j){Rva00112291TerrainOwner*tile=tiles+j*cols+i;((Rva0011216CSlotQuartet*)tile)->rva00112197();((Rva00113110Holder*)tile)->rva00113110(pMap);}
}else{
 rva000E14C4();tiles=new Rva00112291TerrainOwner[num];count=num;cols=numX;rows=numY;
 for(i=0;i<cols;++i)for(j=0;j<rows;++j){Rva00112291TerrainOwner*tile=tiles+j*cols+i;((Rva00111F0E*)tile)->rva00111F6F((RvaRef*)pMap,i*16,j*16,16);((Rva00113110Holder*)tile)->rva00113110(pMap);}
 backup=new void*[num*2];
}
flag=false;rva000E153A();return 0;
}

void BFME_DX8_Thread_Lock();bool BFME_DX8_Thread_Assert();
class HeightBufferLock{public:HeightBufferLock(){BFME_DX8_Thread_Lock();}~HeightBufferLock(){BFME_DX8_Thread_Assert();}};
void Rva000E15D1::rva000E14C4(){
 if(tiles){HeightBufferLock lock;delete[]tiles;tiles=0;}
 cols=0;rows=0;count=0;
 if(backup){delete[]backup;backup=0;}
}
