// stlport
// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_MODULE_NO_MPO /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/gamewindow /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// ?GadgetTextEntrySetValidationFlags@@YAXPAVGameWindow@@H@Z @0x0032060D 25B.
// ORs mask into gadget user data +0xC. Null window or null user data returns.
// Callers pass 8 and 0x21. winGetUserData 0x005C4ACD rowed.
// Use the existing GameWindow header for its genuine nonvirtual declaration.
#include "GameClient/GameWindow.h"

struct Rva0032060DData
{
    char m_pad[0xC];
    int m_flags;
};

void __cdecl GadgetTextEntrySetValidationFlags(GameWindow *window, int value)
{
    Rva0032060DData *data;
    if (window == NULL)
        return;
    data = (Rva0032060DData *)window->winGetUserData();
    if (data == NULL)
        return;
    data->m_flags |= value;
}

// Clean reference guides: Open-BFME-1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d
// Common/Rva007903E0Get.cpp and Common/Rva004B5A10Get.cpp, retained O2/SSE/G6
// donor sweep. Target compilation uses this home's retail region defaults.
// Native A2112..A211D and A211D..A2128 are independently complete RET0 bodies.
// Each loads receiver word0, calls actual GameWindow::winGetUserData@5C4ACD,
// then returns the raw 32-bit payload word at +4 or +8. No null guard exists.
// Original wrapper/record identities and field meanings remain unknown; the
// separate address-owned views describe only each observed accessed prefix.
struct Rva000A2112Data
{
    unsigned int unknown00;
    unsigned int word04;
};
struct Rva000A211DData
{
    unsigned int unknown00[2];
    unsigned int word08;
};
struct Rva000A2112
{
    GameWindow *window;
    unsigned int get() const;
};
struct Rva000A211D
{
    GameWindow *window;
    unsigned int get() const;
};
unsigned int Rva000A2112::get() const
{
    return static_cast<Rva000A2112Data *>(window->winGetUserData())->word04;
}
unsigned int Rva000A211D::get() const
{
    return static_cast<Rva000A211DData *>(window->winGetUserData())->word08;
}

// Clean BF1 f989 Rva00548CE0Set.cpp is a guide for the window-data store.
// Native 56DCA4..56DCB2 follows RET4 and ends its own RET0. The stack4
// GameWindow argument calls actual winGetUserData@5C4ACD, then writes byte
// +0x12 to 1 without a null guard. Payload identity and flag meaning unknown.
struct Rva0056DCA4Data
{
    unsigned char unknown00[0x12];
    unsigned char byte12;
};
void __cdecl rva0056dca4(GameWindow *window)
{
    static_cast<Rva0056DCA4Data *>(window->winGetUserData())->byte12 = 1;
}
