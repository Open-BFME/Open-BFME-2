// cl: /O2 /MD /EHsc
// Native 0x006E06A0..0x006E0915 lazily allocates twelve floats at CIH+0x44.
// Existing getter 0x006E0920 and the Colour setter call chain prove this layout.
// Translation, matrix, colour, allocation size, rounding and all constants
// are target facts. The later b44700bdab0a24a7-AptCIH.cpp is a semantic lead;
// its later accessor layout is not used. The inline normalization is the
// already-verified wrapAngle at 0x006E03F0, including its unusual half-pi fold.
// Reference stores on the first two angles reproduce native float rounding.
// factoryEnsureProperties is a descriptive binding, not an original symbol.
// Retail keeps the CRT float wrappers from other units: import them here so
// this unit inlines them without emitting its own competing out-of-line copies.
#pragma push_macro("inline")
#define inline __declspec(dllimport) __forceinline
#include <math.h>
#pragma pop_macro("inline")
#include <math.h>
#include <string.h>
#include "../../../../GameEngine/Include/Common/Rva006DB160.h"
extern class Rva006DB270 *g_pChainBlockAllocator;
enum PropertyAllocation { propertyAllocation };
// ?operator new absent-from-retail
inline void *operator new(unsigned int size,PropertyAllocation) {return (*(Rva006DB160 **)&g_pChainBlockAllocator)->allocBlock(size);}
// ?operator delete absent-from-retail
inline void operator delete(void *,PropertyAllocation) {}
// ?PropertyArray::PropertyArray present-unmatched
struct PropertyArray {float value[12];PropertyArray(){memset(value,0,sizeof(value));}};
#include "../AptCIHClass.h"
// Canonical fields: matrix a,b,c,d = field0C..field18, translation field1C/field20,
// colour multipliers field24..field30, offsets field34..field40, property array field44.
// ?normalizeProceduralRotation absent-from-retail
static inline float normalizeProceduralRotation(float angle) {
    angle=(float)fmod(angle,3.14159274f);
    if(angle>=1.57079637f)angle-=3.14159274f;
    if(angle < -1.57079637f) {
        if(angle > -3.14159274f)return angle;
        angle+=3.14159274f;
    } else return angle;
    return angle;
}
// ?normalizeProceduralRotationInPlace absent-from-retail
static __forceinline void normalizeProceduralRotationInPlace(float &angle) {
    angle=(float)fmod(angle,3.14159274f);
    if(angle>=1.57079637f)angle-=3.14159274f;
    if(angle < -1.57079637f) {
        if(angle > -3.14159274f)return;
        angle+=3.14159274f;
    } else return;
}
void AptCIH::factoryEnsureProperties() {
    if(!field44) {
        field44=(float *)new(propertyAllocation) PropertyArray;
        field44[0]=field1C;field44[1]=field20;
        float x=atan2f(field10,field0C);normalizeProceduralRotationInPlace(x);
        float y=atan2f(-field14,field18);normalizeProceduralRotationInPlace(y);
        float rotation=y+normalizeProceduralRotation(x-y)*0.5f;
        field44[6]=rotation*57.2957763671875f;
        float cs=cosf(rotation),sn=sinf(rotation);
        if(cs > -0.0001f && cs < 0.0001f) {
            if(sn > -0.0001f && sn < 0.0001f) {field44[2]=100.f;field44[3]=100.f;}
            else {float inv=1.f/sn;field44[2]=inv*field10*100.f;field44[3]=inv*field14*-100.f;}
        }else{float inv=1.f/cs;field44[2]=inv*field0C*100.f;field44[3]=inv*field18*100.f;}
        field44[7]=field24*100.f;
        field44[8]=field38*255.f;field44[9]=field3C*255.f;field44[10]=field40*255.f;field44[11]=1.f;
    }
}
