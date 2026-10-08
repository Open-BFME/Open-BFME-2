// cl: /O1 /MD /DNDEBUG
// SimpleStreakLineClass::Set_Points, game.dat 0x00168605..0x00168690.
// Identity and two copy loops: WorldBuilder 0x00A1A980, simplestreak.cpp.
// Retail puts points/widths at C4/D4 and clears bounding-volume flag bit 1.
// Delete_All semantics follow BFME1 simplevec.h at dae380faa5f6;
// append and folded Shrink calls use the existing BFME2 providers.
class Vector3 { public: float X, Y, Z; };

// BfmePod4 is the existing owner spelling for the type-independent Shrink body.
// Casting only its storage view avoids undefined duplicate folded providers.
struct BfmePod4;
template<class T> class SimpleDynVecClass {
    template<class U> friend class SimpleDynVecClass;
public:
    virtual ~SimpleDynVecClass();
    bool Add(const T &, int);
    void Delete_All() { ActiveCount = 0; ((SimpleDynVecClass<BfmePod4> *)this)->Shrink(); }
protected:
    bool Shrink();
    T *Vector;
    int VectorMax;
    int ActiveCount;
};

class SimpleStreakLineClass {
public:
    void Set_Points(unsigned int count, const Vector3 *points, const float *widths);
private:
    char prefix[0x12];
    unsigned char flags;
    char beforePoints[0xC4 - 0x13];
    SimpleDynVecClass<Vector3> points;
    SimpleDynVecClass<float> widths;
};

void SimpleStreakLineClass::Set_Points(unsigned int count,
    const Vector3 *newPoints, const float *newWidths)
{
    if (count < 2 || !newPoints || !newWidths) return;
    points.Delete_All();
    for (unsigned int i = 0; i < count; ++i) points.Add(newPoints[i], count);
    widths.Delete_All();
    for (unsigned int j = 0; j < count; ++j) widths.Add(newWidths[j], count);
    flags &= ~2;
}
