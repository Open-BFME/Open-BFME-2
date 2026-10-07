// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Reference source: Open-BFME-1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/GameEngine/Source/GameClient/System/FXParticleSystem/RenderObjectDrawModuleSelectModelName005F6B60.cpp.
// Donor semantics: weighted model-name choices, numbered suffix and .w3d extension,
// with particle-system name fallback. Original target class/method remain unknown.
// Target facts: pointers to this body occur at retail RVAs 0x81C458,
// 0x81CD28 and 0x81D508, beside the rowed xfer RVA 0x562945 and virtual
// body 0x562DDB. Accesses prove receiver +4 fallback source, flag +0x24,
// three 16-byte choices at +0x28 and selected dword +0x58; returned source
// name is at +0x10. Layout names follow the donor's model-selection semantics.
// Native fallback callee is the existing Make001FCBD7 provider. Its result
// is viewed through ParticleSystemZA's established +0x10 string ABI; no new
// alias pins or claim about the original target owner/method is introduced.
#include "ascii_string.h"
#include "wwmath.h"
#include <stdio.h>
#include <string.h>
#pragma intrinsic(strlen)


template<> inline void StringBase<char>::concat(const char *str)
{
    concat(str, str ? strlen(str) : 0);
}

class ParticleSystemZA
{
public:
    const AsciiString &nameAt10() const { return name; }
private:
    unsigned char prefix[0x10];
    AsciiString name;
};
class ParticleSystem;
ParticleSystem *Make001FCBD7();

struct Rva00562BF7Choice
{
    AsciiString name;
    int count;
    float threshold;
    int field0C;
};

class Rva00562BF7Owner
{
public:
    AsciiString rva00562BF7();
    void *vtable;
    ParticleSystemZA *system;
    unsigned char padding08[0x1c];
    bool field24;
    unsigned char padding25[3];
    Rva00562BF7Choice choices[3];
    int field58;
};

AsciiString Rva00562BF7Owner::rva00562BF7()
{
    if (field24) {
        float chance = WWMath::Random_Float() * 100.0f;
        if (chance <= choices[0].threshold) {
            field58 = choices[0].field0C;
            AsciiString name(choices[0].name);
            for (int i = 0; i < 6; ++i)
                name.removeLastChar();
            float variantCount = (float)choices[0].count;
            char suffix[4];
            sprintf(suffix, "%02d", (int)(WWMath::Random_Float() * (variantCount - 1.0f) + 1.5f));
            name.concat(suffix);
            name.concat(".w3d");
            return name;
        } else if (chance <= choices[1].threshold) {
            field58 = choices[1].field0C;
            AsciiString name(choices[1].name);
            for (int i = 0; i < 6; ++i)
                name.removeLastChar();
            float variantCount = (float)choices[1].count;
            char suffix[4];
            sprintf(suffix, "%02d", (int)(WWMath::Random_Float() * (variantCount - 1.0f) + 1.5f));
            name.concat(suffix);
            name.concat(".w3d");
            return name;
        } else {
            field58 = choices[2].field0C;
            AsciiString name(choices[2].name);
            for (int i = 0; i < 6; ++i)
                name.removeLastChar();
            float variantCount = (float)choices[2].count;
            char suffix[4];
            sprintf(suffix, "%02d", (int)(WWMath::Random_Float() * (variantCount - 1.0f) + 1.5f));
            name.concat(suffix);
            name.concat(".w3d");
            return name;
        }
    }
    return (!system ? reinterpret_cast<ParticleSystemZA *>(Make001FCBD7()) : system)->nameAt10();
}
