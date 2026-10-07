// ?d_00381458@@YAXXZ
// partial score=0.9 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD /Oy- /EHs-c- /Ireference/shims/bfme2_ascii
// Ghidra FUN_00781458, 78B, cdecl RET. Mode 0 forwards the wide string
// reference to 0x004166DB; mode 1 uses TheGameSpyInfo slot 0x100 with a
// by-value wide string, false and the window pointer, then returns true.
// ZH PeerDefs::sendChat supplies the signature, not a retail method name.
#include "unicode_string.h"

class GameWindow;
class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
    virtual void unused(char (*)[N]) = 0;
};
template <> class BfmeVirtualSlots<0> {};
class Rva00381458GameSpyDispatch : public BfmeVirtualSlots<64>
{
public:
    virtual bool slot100(UnicodeString message, bool isAction, GameWindow *window) = 0;
};

bool Rva004166DB(const UnicodeString &message, GameWindow *window);

// ?Rva00381458@@YA_NHABVUnicodeString@@PAVGameWindow@@@Z
bool Rva00381458(int mode, const UnicodeString &message, GameWindow *window)
{
    switch (mode)
    {
    case 0:
        return Rva004166DB(message, window);
    case 1:
        if (!TheGameSpyInfo)
            break;
        reinterpret_cast<Rva00381458GameSpyDispatch *>(TheGameSpyInfo)
            ->slot100(message, false, window);
        return true;
    default:
        break;
    }
    return false;
}
