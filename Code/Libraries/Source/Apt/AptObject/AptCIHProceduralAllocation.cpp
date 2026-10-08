// cl: /O2 /MD /EHsc
// Native 0x006E06A0..0x006E0915 lazily allocates twelve floats at CIH+0x44.
// Existing getter 0x006E0920 and the Colour setter call chain prove this layout.
// Translation, matrix, colour, allocation size, rounding and all constants
// are target facts. The later b44700bdab0a24a7-AptCIH.cpp is a semantic lead;
// its later accessor layout is not used. The inline normalization is the
// already-verified wrapAngle at 0x006E03F0, including its unusual half-pi fold.
// Reference stores on the first two angles reproduce native float rounding.
// factoryEnsureProperties is a descriptive binding, not an original symbol.
#include <math.h>
#include <string.h>
class Rva006DB160 { public: void *allocBlock(int); };
extern class Rva006DB270 *g_pChainBlockAllocator;
enum PropertyAllocation { propertyAllocation };
// ?operator new absent-from-retail
inline void *operator new(unsigned int size,PropertyAllocation) {return (*(Rva006DB160 **)&g_pChainBlockAllocator)->allocBlock(size);}
// ?operator delete absent-from-retail
inline void operator delete(void *,PropertyAllocation) {}
// ?PropertyArray::PropertyArray present-unmatched
struct PropertyArray {float value[12];PropertyArray(){memset(value,0,sizeof(value));}};
class AptCIH {
public:
    char pad[0xc];float a,b,c,d,tx,ty;
    float alphaMultiplier,redMultiplier,greenMultiplier,blueMultiplier;
    float alphaOffset,redOffset,greenOffset,blueOffset;
    float *properties;
    void factoryEnsureProperties();
};
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
    if(!properties) {
        properties=(float *)new(propertyAllocation) PropertyArray;
        properties[0]=tx;properties[1]=ty;
        float x=atan2f(b,a);normalizeProceduralRotationInPlace(x);
        float y=atan2f(-c,d);normalizeProceduralRotationInPlace(y);
        float rotation=y+normalizeProceduralRotation(x-y)*0.5f;
        properties[6]=rotation*57.2957763671875f;
        float cs=cosf(rotation),sn=sinf(rotation);
        if(cs > -0.0001f && cs < 0.0001f) {
            if(sn > -0.0001f && sn < 0.0001f) {properties[2]=100.f;properties[3]=100.f;}
            else {float inv=1.f/sn;properties[2]=inv*b*100.f;properties[3]=inv*c*-100.f;}
        }else{float inv=1.f/cs;properties[2]=inv*a*100.f;properties[3]=inv*d*100.f;}
        properties[7]=alphaMultiplier*100.f;
        properties[8]=redOffset*255.f;properties[9]=greenOffset*255.f;properties[10]=blueOffset*255.f;properties[11]=1.f;
    }
}
