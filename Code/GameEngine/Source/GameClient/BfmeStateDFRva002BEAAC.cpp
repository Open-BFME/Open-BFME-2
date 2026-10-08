// cl: /O1 /arch:SSE /G7
// ?rva002BEAAC@BfmeStateDF@@QAEMMMM@Z, retail 0x002BEAAC, 33 bytes.
// Evidence: unlock caller 0x002BECBA, pin callee Curve 0x00504BA9
// ?rva00504BA9@Rva00504BA9Curve@@QAEMM@Z, same BfmeStateDF curve +0x28
// and single-lerp x87 shape as BfmeStateDF::interpolate in
// LivingWorldPairInterpolate.cpp (which needs /Oy- for its EBP frame;
// this frameless 33B leaf needs no /Oy-).
class Rva00504BA9Curve
{
public:
    float rva00504BA9(float progress);
};

class BfmeStateDF
{
public:
    float rva002BEAAC(float from, float to, float progress);
private:
    unsigned char prefix28[0x28];
    Rva00504BA9Curve curve;
};

// ?rva002BEAAC@BfmeStateDF@@QAEMMMM@Z
float BfmeStateDF::rva002BEAAC(float from, float to, float progress)
{
    float factor = curve.rva00504BA9(progress);
    return (to - from) * factor + from;
}
