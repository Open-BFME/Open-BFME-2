// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native375B7A..375BFF RET8. Terrain slot6 and the local polygon-height
// query are combined; AI's +18 object provides the optional +B0 floor.
// Exact roles beyond these measured heights and slots remain unidentified.
#include <float.h>
class TerrainLogic {
public:
 virtual void slot0();virtual void slot1();virtual void slot2();
 virtual void slot3();virtual void slot4();virtual void slot5();
 virtual float heightAt(float x,float y,void *normal);
};
extern TerrainLogic *TheTerrainLogic;
class AI;
extern AI *TheAI;
struct Rva00375B7ACap { char unknown00[0xB0]; float height; };
struct Rva00375B7AAI { char unknown00[0x18]; Rva00375B7ACap *cap; };
class Rva00375AF7HeightQuery {
public:
 float rva00375AF7(float x,volatile float y);
 float rva00375B7A(float x,float y);
};
float Rva00375AF7HeightQuery::rva00375B7A(float x,float y)
{
 float height=TheTerrainLogic->heightAt(x,y,0);
 float local=rva00375AF7(x,y);
 if(local>height) height=local;
 float limit=reinterpret_cast<Rva00375B7AAI *>(TheAI)->cap->height;
 if(limit!=FLT_MAX && limit>height) height=limit;
 return height;
}
