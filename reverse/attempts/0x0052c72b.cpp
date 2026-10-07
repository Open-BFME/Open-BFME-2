// ?contains@Rva0052BFE1@@QAE_NABVAsciiString@@@Z
// partial score=0.98 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// Native 0x0052C119..0x0052C161, RET0. Existing caller 0x003B8D06
// passes a campaign entry through this receiver and then reads its name.
// Native stride B8 and begin/end at C/10 establish the vector view.
// Original identities and unused fields remain unknown.
#include <vector>
#include "ascii_string.h"
class Rva00564DF2NameView
{
public:
    AsciiString rva00564DF2() const;
private:
    char unknown[0xB8];
};
class Rva0052BFE1
{
public:
    Rva00564DF2NameView *rva0052C119();
    bool contains(const AsciiString &key);
    Rva00564DF2NameView *rva0052C7A2(const AsciiString &key);
private:
    char unknown00[8];
    int index;
    _STL::vector<Rva00564DF2NameView> entries;
};

Rva00564DF2NameView *Rva0052BFE1::rva0052C119()
{
    int current = index;
    if (current >= 0 && (unsigned int)current < entries.size())
        return &entries[current];
    return &entries[entries.size() - 1];
}

bool Rva0052BFE1::contains(const AsciiString &key)
{
    for (unsigned int i=0; i<entries.size(); ++i)
        if (entries[i].rva00564DF2().compare(key)==0)
            return true;
    return false;
}
Rva00564DF2NameView *Rva0052BFE1::rva0052C7A2(const AsciiString &key)
{
    for (unsigned int i=0; i<entries.size(); ++i)
        if (entries[i].rva00564DF2().compare(key)==0)
            return &entries[i];
    return 0;
}
