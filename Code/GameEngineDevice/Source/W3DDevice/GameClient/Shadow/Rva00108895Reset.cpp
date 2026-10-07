// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /Oi
// RVA 0x00108895, 97 bytes, no-argument member called by native resource-owner
// constructor 0x0010BA2C and reinitializer 0x0010BA61. The original class and
// method names remain unknown. Measured writes establish the field offsets;
// native literal at VA 0x00BCF9B0 is -100.0f. Two arrays are reset in lockstep.
#include <string.h>

struct Rva00108895Triplet
{
    float first, second, third;
    void set(float value) { first = value; second = value; third = value; }
};

class Rva0010BA2COwner
{
public:
    void rva00108895();
private:
    char unknown00[0x68];
    unsigned int retained68[2];
    void *retained70;
    unsigned char flag74;
    char unknown75[3];
    float value78;
    float value7C;
    unsigned int word80;
    unsigned char flag84;
    unsigned char flag85;
    char unknown86[2];
    Rva00108895Triplet sentinel88;
    unsigned int array94[16];
    unsigned int arrayD4[16];
};

void Rva0010BA2COwner::rva00108895()
{
    memset(retained68, 0, sizeof(retained68));
    value78 = 0.0f;
    value7C = 0.0f;
    retained70 = 0;
    flag74 = 0;
    word80 = 0;
    flag84 = 0;
    flag85 = 0;
    sentinel88.set(-100.0f);
    for (int i = 0; i < 16; ++i) {
        array94[i] = 0;
        arrayD4[i] = 0;
    }
}
