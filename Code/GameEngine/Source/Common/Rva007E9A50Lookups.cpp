// cl: /GS
// Transferred unchanged from Open-BFME-1 5cae4bdff game/GameEngine/Source/Common/Rva007E9A50Lookups.cpp;
// bfme1_sweep ambiguous: byte-identical bodies placed by the BFME1->BFME2 address map at 0x00656A40, 0x0065DCE0, 0x0065E9C0, 0x0065F850, 0x0065FDF0, 0x00660AC0, 0x00660E30.
// Addresses in the donor text are BFME1.
// Retail lookup bodies: independent starts after int3, each 179 bytes through
// RET 4, followed by int3 padding. Each dispatch table address is witnessed
// by the two absolute operands in that body's retail instructions.
#include <string.h>
#pragma intrinsic(strcmp)
class Rva007E8810Message {
public:
    bool getString(const char *, char *, int);
};
struct Rva007E9A50Entry {
    void *field00;
    const char *m_name;
};

// Registry records are owned by Rva007B55E0TxnNameInits.cpp.
// This prefix view reads only the target-proven name pointer at +4.
struct Rva007B55E0TxnName;
extern Rva007B55E0TxnName g_Va00E09F24;
extern Rva007B55E0TxnName g_Va00E09F0C;
extern Rva007B55E0TxnName g_Va00E09EF4;
extern Rva007B55E0TxnName g_Va00E09F30;
extern Rva007B55E0TxnName g_Va00E09F3C;
extern Rva007B55E0TxnName g_Va00E09F18;
extern Rva007B55E0TxnName g_Va00E09F90;
extern Rva007B55E0TxnName g_Va00E09EAC;
extern Rva007B55E0TxnName g_Va00E09ED0;
extern Rva007B55E0TxnName g_Va00E09F60;
extern Rva007B55E0TxnName g_Va00E09F48;
extern Rva007B55E0TxnName g_Va00E09EB8;
extern Rva007B55E0TxnName g_Va00E09F78;
extern Rva007B55E0TxnName g_Va00E09EDC;
extern Rva007B55E0TxnName g_Va00E09F54;
extern Rva007B55E0TxnName g_Va00E09EC4;
extern Rva007B55E0TxnName g_Va00E09EE8;
extern Rva007B55E0TxnName g_Va00E09F84;
extern Rva007B55E0TxnName g_Va00E09F00;
extern Rva007B55E0TxnName g_Va00E09F6C;
extern Rva007B55E0TxnName g_Va00E09FE8;
extern Rva007B55E0TxnName g_Va00E0A000;
extern Rva007B55E0TxnName g_Va00E0A00C;
extern Rva007B55E0TxnName g_Va00E0A024;
extern Rva007B55E0TxnName g_Va00E09FDC;
extern Rva007B55E0TxnName g_Va00E0A018;
extern Rva007B55E0TxnName g_Va00E0A03C;
extern Rva007B55E0TxnName g_Va00E09FF4;
extern Rva007B55E0TxnName g_Va00E0A030;
extern Rva007B55E0TxnName g_Va00E09FD0;
extern Rva007B55E0TxnName g_Va00E0A054;
extern Rva007B55E0TxnName g_Va00E0A048;
extern Rva007B55E0TxnName g_Va00E0A0CC;
extern Rva007B55E0TxnName g_Va00E0A060;
extern Rva007B55E0TxnName g_Va00E0A06C;
extern Rva007B55E0TxnName g_Va00E0A078;
extern Rva007B55E0TxnName TheRankUpdateStatsTransaction;
extern Rva007B55E0TxnName g_Va00E0A084;
extern Rva007B55E0TxnName g_Va00E0A0D8;
extern Rva007B55E0TxnName g_Va00E0A09C;
extern Rva007B55E0TxnName g_Va00E0A0C0;
extern Rva007B55E0TxnName g_Va00E0A090;
extern Rva007B55E0TxnName g_Va00E0A0B4;
extern Rva007B55E0TxnName g_Va00E0A0E4;
extern Rva007B55E0TxnName g_Va00E0A0F0;
extern Rva007B55E0TxnName g_Va00E0A0FC;
extern Rva007B55E0TxnName g_Va00E0A108;
extern Rva007B55E0TxnName g_Va00E0A120;
extern Rva007B55E0TxnName g_Va00E0A12C;
extern Rva007B55E0TxnName g_Va00E0A144;
extern Rva007B55E0TxnName g_Va00E0A138;
extern Rva007B55E0TxnName g_Va00E0A174;
extern Rva007B55E0TxnName g_Va00E0A180;
extern Rva007B55E0TxnName g_Va00E0A18C;
extern Rva007B55E0TxnName g_Va00E0A168;
extern Rva007B55E0TxnName g_Va00E0A15C;
extern Rva007B55E0TxnName g_Va00E0A150;
extern Rva007B55E0TxnName g_Va00E0A114;
extern Rva007B55E0TxnName g_Va00E0A1A4;
extern Rva007B55E0TxnName g_Va00E0A1BC;
extern Rva007B55E0TxnName g_Va00E0A198;
extern Rva007B55E0TxnName g_Va00E0A1B0;

Rva007E9A50Entry *g_Rva012C37F8[] = {
    (Rva007E9A50Entry *)&g_Va00E09F24,
    (Rva007E9A50Entry *)&g_Va00E09F0C,
    (Rva007E9A50Entry *)&g_Va00E09EF4,
    (Rva007E9A50Entry *)&g_Va00E09F30,
    (Rva007E9A50Entry *)&g_Va00E09F3C,
    (Rva007E9A50Entry *)&g_Va00E09F18,
    (Rva007E9A50Entry *)&g_Va00E09F90,
    (Rva007E9A50Entry *)&g_Va00E09EAC,
    (Rva007E9A50Entry *)&g_Va00E09ED0,
    (Rva007E9A50Entry *)&g_Va00E09F60,
    (Rva007E9A50Entry *)&g_Va00E09F48,
    (Rva007E9A50Entry *)&g_Va00E09EB8,
    (Rva007E9A50Entry *)&g_Va00E09F78,
    (Rva007E9A50Entry *)&g_Va00E09EDC,
    (Rva007E9A50Entry *)&g_Va00E09F54,
    (Rva007E9A50Entry *)&g_Va00E09EC4,
    (Rva007E9A50Entry *)&g_Va00E09EE8,
    (Rva007E9A50Entry *)&g_Va00E09F84,
    (Rva007E9A50Entry *)&g_Va00E09F00,
    (Rva007E9A50Entry *)&g_Va00E09F6C,
    0
};
class Rva007E9A50 {
public:
    Rva007E9A50Entry *lookup(Rva007E8810Message *message);
};
Rva007E9A50Entry *Rva007E9A50::lookup(Rva007E8810Message *message)
{
    char text[32];
    if (!message->getString("TXN", text, 32))
        return 0;
    for (Rva007E9A50Entry **entry = g_Rva012C37F8; *entry; ++entry) {
        if (strcmp((*entry)->m_name, text) == 0)
            return *entry;
    }
    return 0;
}

Rva007E9A50Entry *g_Rva012C3958[] = {
    (Rva007E9A50Entry *)&g_Va00E09FE8,
    (Rva007E9A50Entry *)&g_Va00E0A000,
    (Rva007E9A50Entry *)&g_Va00E0A00C,
    (Rva007E9A50Entry *)&g_Va00E0A024,
    (Rva007E9A50Entry *)&g_Va00E09FDC,
    (Rva007E9A50Entry *)&g_Va00E0A018,
    (Rva007E9A50Entry *)&g_Va00E0A03C,
    (Rva007E9A50Entry *)&g_Va00E09FF4,
    (Rva007E9A50Entry *)&g_Va00E0A030,
    (Rva007E9A50Entry *)&g_Va00E09FD0,
    0
};
class Rva007F1160 {
public:
    Rva007E9A50Entry *lookup(Rva007E8810Message *message);
};
Rva007E9A50Entry *Rva007F1160::lookup(Rva007E8810Message *message)
{
    char text[32];
    if (!message->getString("TXN", text, 32))
        return 0;
    for (Rva007E9A50Entry **entry = g_Rva012C3958; *entry; ++entry) {
        if (strcmp((*entry)->m_name, text) == 0)
            return *entry;
    }
    return 0;
}

Rva007E9A50Entry *g_Rva012C3988[] = {
    (Rva007E9A50Entry *)&g_Va00E0A054,
    (Rva007E9A50Entry *)&g_Va00E0A048,
    0
};
class Rva007F1EA0 {
public:
    Rva007E9A50Entry *lookup(Rva007E8810Message *message);
};
Rva007E9A50Entry *Rva007F1EA0::lookup(Rva007E8810Message *message)
{
    char text[32];
    if (!message->getString("TXN", text, 32))
        return 0;
    for (Rva007E9A50Entry **entry = g_Rva012C3988; *entry; ++entry) {
        if (strcmp((*entry)->m_name, text) == 0)
            return *entry;
    }
    return 0;
}

Rva007E9A50Entry *g_Rva012C3998[] = {
    (Rva007E9A50Entry *)&g_Va00E0A0CC,
    (Rva007E9A50Entry *)&g_Va00E0A060,
    (Rva007E9A50Entry *)&g_Va00E0A06C,
    (Rva007E9A50Entry *)&g_Va00E0A078,
    (Rva007E9A50Entry *)&TheRankUpdateStatsTransaction,
    (Rva007E9A50Entry *)&g_Va00E0A084,
    (Rva007E9A50Entry *)&g_Va00E0A0D8,
    (Rva007E9A50Entry *)&g_Va00E0A09C,
    (Rva007E9A50Entry *)&g_Va00E0A0C0,
    (Rva007E9A50Entry *)&g_Va00E0A090,
    (Rva007E9A50Entry *)&g_Va00E0A0B4,
    0
};
class Rva007F2D70 {
public:
    Rva007E9A50Entry *lookup(Rva007E8810Message *message);
};
Rva007E9A50Entry *Rva007F2D70::lookup(Rva007E8810Message *message)
{
    char text[32];
    if (!message->getString("TXN", text, 32))
        return 0;
    for (Rva007E9A50Entry **entry = g_Rva012C3998; *entry; ++entry) {
        if (strcmp((*entry)->m_name, text) == 0)
            return *entry;
    }
    return 0;
}

Rva007E9A50Entry *g_Rva012C39CC[] = {
    (Rva007E9A50Entry *)&g_Va00E0A0E4,
    (Rva007E9A50Entry *)&g_Va00E0A0F0,
    (Rva007E9A50Entry *)&g_Va00E0A0FC,
    (Rva007E9A50Entry *)&g_Va00E0A108,
    0
};
class Rva007F3320 {
public:
    Rva007E9A50Entry *lookup(Rva007E8810Message *message);
};
Rva007E9A50Entry *Rva007F3320::lookup(Rva007E8810Message *message)
{
    char text[32];
    if (!message->getString("TXN", text, 32))
        return 0;
    for (Rva007E9A50Entry **entry = g_Rva012C39CC; *entry; ++entry) {
        if (strcmp((*entry)->m_name, text) == 0)
            return *entry;
    }
    return 0;
}

Rva007E9A50Entry *g_Rva012C39E4[] = {
    (Rva007E9A50Entry *)&g_Va00E0A120,
    (Rva007E9A50Entry *)&g_Va00E0A12C,
    (Rva007E9A50Entry *)&g_Va00E0A144,
    (Rva007E9A50Entry *)&g_Va00E0A138,
    (Rva007E9A50Entry *)&g_Va00E0A174,
    (Rva007E9A50Entry *)&g_Va00E0A180,
    (Rva007E9A50Entry *)&g_Va00E0A18C,
    (Rva007E9A50Entry *)&g_Va00E0A168,
    (Rva007E9A50Entry *)&g_Va00E0A15C,
    (Rva007E9A50Entry *)&g_Va00E0A150,
    (Rva007E9A50Entry *)&g_Va00E0A114,
    0
};
class Rva007F4000 {
public:
    Rva007E9A50Entry *lookup(Rva007E8810Message *message);
};
Rva007E9A50Entry *Rva007F4000::lookup(Rva007E8810Message *message)
{
    char text[32];
    if (!message->getString("TXN", text, 32))
        return 0;
    for (Rva007E9A50Entry **entry = g_Rva012C39E4; *entry; ++entry) {
        if (strcmp((*entry)->m_name, text) == 0)
            return *entry;
    }
    return 0;
}

Rva007E9A50Entry *g_Rva012C3A1C[] = {
    (Rva007E9A50Entry *)&g_Va00E0A1A4,
    (Rva007E9A50Entry *)&g_Va00E0A1BC,
    (Rva007E9A50Entry *)&g_Va00E0A198,
    (Rva007E9A50Entry *)&g_Va00E0A1B0,
    0
};
class Rva007F4380 {
public:
    Rva007E9A50Entry *lookup(Rva007E8810Message *message);
};
Rva007E9A50Entry *Rva007F4380::lookup(Rva007E8810Message *message)
{
    char text[32];
    if (!message->getString("TXN", text, 32))
        return 0;
    for (Rva007E9A50Entry **entry = g_Rva012C3A1C; *entry; ++entry) {
        if (strcmp((*entry)->m_name, text) == 0)
            return *entry;
    }
    return 0;
}
