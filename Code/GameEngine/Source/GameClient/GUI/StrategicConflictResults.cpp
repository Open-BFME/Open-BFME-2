// cl: /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Native5EB955..5EB9D6, RET12: initialize the output, look up an int-keyed
// participant identifier, split it into side/player indices, and format the
// participant's opaque RGB colour. WB ExternPlayerColor supplies a name lead;
// the receiver's complete identity/layout remains unresolved.
// Target accesses prove battle+C, map+38, identifier divisor10000 and RGB+184.
// Existing matched providers supply all three non-library call identities.
#include <map>

extern "C" char *__cdecl _mbscpy(char *, const char *);

struct RGBColor { int getAsInt() const; float red, green, blue; };
class LivingWorldBattle { public: int rva003F459A(); };
class Rva003F468D { public: int rva003F468D(int, int); };

class Rva005EB955 {
public:
    void rva005EB955(int index, char *result, bool disabled);
private:
    char unknown00[0xC];
    LivingWorldBattle *battle;
    char unknown10[0x28];
    _STL::map<int, int> participants;
};

void Rva005EB955::rva005EB955(int index, char *result, bool disabled)
{
    _mbscpy(result, "0");
    if (!disabled && battle && index < battle->rva003F459A()) {
        _STL::map<int, int>::iterator found = participants.find(index);
        if (found != participants.end()) {
            int id = found->second;
            int player = reinterpret_cast<Rva003F468D *>(battle)->rva003F468D(id / 10000, id % 10000);
            int color = reinterpret_cast<RGBColor *>(player + 0x184)->getAsInt() | 0xFF000000;
            _snprintf(result, 0xFF, "%d", color);
        }
    }
}
