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

struct BfmeStateDFVector3
{
    float x, y, z;
};

class BfmeStateDF
{
public:
    float rva002BEAAC(float from, float to, float progress);
    void rva002BEACD(BfmeStateDFVector3 *from, BfmeStateDFVector3 *to,
                    BfmeStateDFVector3 *result, float progress);
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

// Retail 0x002BEACD..0x002BEB6F: RET 0x10 follows the third float store.
// Caller 0x002BECBA shares this receiver with the scalar helper above and
// the matched two-component interpolate at 0x002BEB6F. The target calls the
// same curve at receiver+0x28 three times, returning ST0 each time, and writes
// floats at result+0/4/8. A three-component vector is a structural inference;
// the target method's original name remains unknown.
void BfmeStateDF::rva002BEACD(BfmeStateDFVector3 *from, BfmeStateDFVector3 *to,
                             BfmeStateDFVector3 *result, float progress)
{
    float factor;
    Rva00504BA9Curve *c = &curve;
    factor = c->rva00504BA9(progress);
    float start = from->x;
    result->x = (to->x - start) * factor + start;
    float secondFactor = c->rva00504BA9(progress);
    start = from->y;
    result->y = (to->y - start) * secondFactor + start;
    progress = c->rva00504BA9(progress);
    start = from->z;
    result->z = (to->z - start) * progress + start;
}
