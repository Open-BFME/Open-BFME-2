// ?rva005EB77D@Rva005EB77D@@QAEXHPAD_N@Z
// partial score=0.96 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /Oy- /MD
// Native Ghidra 5EB77D..5EB7CD RET12. The original callback name is
// unresolved. Existing battle-side helper and target accesses establish the
// inner pointer at +C and the side index at inner+38; native format is "%d".
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *, unsigned int, const char *, ...);
class Rva003F468D {
public:
    int rva003F459A();
    int rva003F4DAE(int);
    char unknown[0x38];
    int side;
};
class Rva005EB77D {
public:
    void rva005EB77D(int, char *, bool);
private:
    char unknown[0xc];
    Rva003F468D *inner;
};
void Rva005EB77D::rva005EB77D(int selector, char *out, bool blocked)
{
    if (inner) {
        switch (selector) {
        case 1:
            if (!blocked)
                _snprintf(out, 0xff, "%d", inner->rva003F459A());
            break;
        case 0:
            if (!blocked)
                _snprintf(out, 0xff, "%d", inner->rva003F4DAE(inner->side));
            break;
        }
    }
}
