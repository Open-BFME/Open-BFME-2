// ?mark@Rva00069C5F@@QAEXMMMM@Z
// partial score=0.889 date=2026-10-10
// cl: /O1 /G7 /MD /arch:SSE /EHsc
static __forceinline float scorchSqrt(float val){float retval;__asm {fld val
fsqrt
fstp retval}
return retval;}
struct TerrainScorchVector {float X,Y,Z;TerrainScorchVector(float x,float y,float z):X(x),Y(y),Z(z){} __forceinline float Length()const{return scorchSqrt(Z*Z+Y*Y+X*X);}};
struct TerrainScorchEntry {float opaque;TerrainScorchVector pos;float radius;int kind;bool active;char pad[3];};
class Rva00069C5F {public:void mark(float x,float y,float z,float radius);private:char pad[0xE0];TerrainScorchEntry entries[500];int count,cached;};
void Rva00069C5F::mark(float x,float y,float z,float radius){for(int i=0;i<count;++i){TerrainScorchEntry &e=entries[i];TerrainScorchVector delta(x-e.pos.X,y-e.pos.Y,z-e.pos.Z);float distance=delta.Length();if(e.radius+radius>distance)e.active=true;}cached=0;}
