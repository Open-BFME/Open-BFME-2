// cl: /DNDEBUG /MD /EHsc
//
// One body carried from Open-BFME-1's game/Libraries/Source/Apt/string/
// EAString.cpp (BFME 1 RVA 0x0089EFE0), whose bytes reappear in game.dat at
// 0x006D5580 once relocation slots are set aside. Only this body is carried.

// Address-derived emission view. Original class and member identities unknown.
// Native wrapper: entry ECX, one stack byte, RET4; forwards callee EAX.
class Rva0089EFE0
{
public:
    int method(char value);
    // Native body at BFME 1 RVA 0x0089E2B0 (game.dat 0x006D47F0): ECX
    // receiver, two C strings, RET8, and an integral count in EAX.
    int rva0089E2B0(const char *first, const char *second);
};

int Rva0089EFE0::method(char value)
{
    char text[2] = "*";
    text[0] = value;
    return rva0089E2B0(text, "");
}
