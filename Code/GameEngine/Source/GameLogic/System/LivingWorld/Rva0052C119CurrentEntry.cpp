// cl: /O1 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// Native 0x0052C119..0x0052C161, RET0. Existing caller 0x003B8D06
// passes a campaign entry through this receiver and then reads its name.
// Native stride B8 and begin/end at C/10 establish the vector view.
// Original identities and unused fields remain unknown.
#include <vector>
class Rva00564DF2NameView
{
private:
    char unknown[0xB8];
};
class Rva0052BFE1
{
public:
    Rva00564DF2NameView *rva0052C119();
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
