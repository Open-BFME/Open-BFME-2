// Retail 0x0005230D..0x000523A0, Ghidra 147B, thiscall RET20.
// Measured volume-state view; the original receiver and method names remain
// unresolved. The existing caller pin supplies this neutral ABI name.
class MilesAudioManager {
public:
    class GlobalVolumeData {
    public:
        void refreshAll();
    };
};

class Rva0005230D {
public:
    char reserved[0x9c];
    float scale;
    char reservedA0[0xac - 0xa0];
    float fieldAC;
    float fieldB0;
    float fieldB4;
    float fieldB8;
    float fieldBC;
    float fieldC0;
    unsigned char fieldC4;
    void rva0005230D(float a, float b, float c, float d, float e);
};

void Rva0005230D::rva0005230D(float a, float b, float c, float d, float e)
{
    const float zero = 0.0f;
    const float one = 1.0f;
    if (zero > a)
        a = zero;
    else if (a > one)
        a = one;
    fieldAC = a;
    float end = one;
    if (zero > b)
        end = zero;
    else if (!(b > one))
        end = b;
    fieldB0 = end;
    fieldB4 = c;
    fieldB8 = d;
    fieldBC = e;
    fieldC0 = zero;
    fieldC4 = 1;
    scale = a;
    reinterpret_cast<MilesAudioManager::GlobalVolumeData *>(this)->refreshAll();
}
