// cl: /O1 /G7 /arch:SSE /MD
// Native 003F99DC..003F9A2B, 79B, RET0. Receiver fields1C/20 hold
// the two render hosts; pair24/28 is copied from5C/60. The view singleton
// has source coordinates8C and virtual slot38 returning a stack Vec3.
// Callee3F962F is a complete941B same-receiver RET0 body: its entry
// saves ECX and reads fields24/28/2C; its epilogue ends at3F99DC.
// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f supplies the
// LivingWorldEyeTower::processFrame identity in LivingWorldEyeTowerProcessFrame.cpp.
// BFME2 rowed updateState3F9BED independently tail-calls this body; its
// helper3F936E now has the matching member ABI and owner. Field names and
// exact original field qualifiers remain unknown. Both native pair-helper calls
// explicitly reload ECX=this even though the helper at3F936E does not read it.
struct Rva003F99DCVec3 { float x, y, z; };
struct Rva003F99DCPair { float x, y; };
class Rva003F99DCView
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13();
    virtual void sample(const Rva003F99DCVec3 *, Rva003F99DCVec3 *);
    char prefix04[0x8C - 4];
    Rva003F99DCVec3 position;
};
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;
class Rva003F936EHost;
class LivingWorldEyeTower
{
private:
    void processFrame();
    void rva003F962F();
    void rva003F936E(Rva003F936EHost *, float *);
    char prefix00[0x1C];
    Rva003F936EHost *first, *second;
    float currentX, currentY;
    char prefix2C[0x5C - 0x2C];
    Rva003F99DCPair start;
};

// ?processFrame@LivingWorldEyeTower@@AAEXXZ
void LivingWorldEyeTower::processFrame()
{
    Rva003F99DCVec3 temporary;
    Rva003F99DCView *view = reinterpret_cast<Rva003F99DCView *>(g_00DFEF18);
    view->sample(&view->position, &temporary);
    // Retail copies the two words as raw float representations, preserving
    // NaNs and signed zeros. The separate destination fields reproduce its
    // receiver-relative Y store while the X address remains live for both calls.
    *reinterpret_cast<unsigned int *>(&currentX) =
        *reinterpret_cast<const unsigned int *>(&start.x);
    *reinterpret_cast<unsigned int *>(&currentY) =
        *reinterpret_cast<const unsigned int *>(&start.y);
    rva003F962F();
    rva003F936E(first, &currentX);
    rva003F936E(second, &currentX);
}
