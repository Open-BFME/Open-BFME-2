// Target facts (code addresses are RVAs; table addresses are VAs): constructor 0x0043D686 calls _bfme_AptGameWindow at 0x0043D69E, then stores 0x00C3D7F8 at +0 (0x0043D6B2) and 0x00C3D7F4 at +0x218 (0x0043D6B8). Destructor 0x0043D1C9 stores the same pair at 0x0043D1DC/0x0043D1E2. The secondary table holds the -0x218 deleting-destructor thunk 0x0043D34F to 0x0043D3BE, which calls the destructor at 0x0043D3C1. This class is polymorphic. The different pair 0x00C659E8/0x00C659E4 belongs to the base: its constructor 0x0051268C and destructor 0x005126F5 store it during base lifetime, before derived construction or after derived teardown.
// The primary table has fourteen entries, slots 0..13 targeting 0x0043D3BE/0x0043D41E/0x0051274F/0x000A12F8/0x00444680/0x000910FB/0x00313913/0x00510D87/0x0031393A/0x0008FF78/0x0050B5C6/0x0050B5C6/0x000B3FD0/0x000B3FD0. The bytes at 0x00C3D830 are the string "dds", not a fifteenth slot. The input declaration preserves the included base's slot-1 spelling; it does not assert an original name for 0x0043D41E.
// Factory 0x0043DA1B pushes 0x35C at 0x0043DA26 and calls the constructor at 0x0043DA42. The base factory 0x002D1E55 pushes 0x27C at 0x002D1E60; base constructor stores at 0x005126C6/0x005126CD/0x005126D4 place the string/dword/byte at +0x270/+0x274/+0x278. The derived constructor calls vector-base 0x00211E58 on +0x27C (0x0043D6C2) and holder constructor 0x0043D16F on +0x288 (0x0043D6CD). Destruction calls 0x0043D193 on +0x288 at 0x0043D31B and frees the +0x27C vector storage at 0x0043D330. field27C and field288 preserve these 12-byte and 24-byte spans without asserting their unresolved element or holder identities. Constructor stores 0x0043D6E6..0x0043D702 prove bytes +0x2A0..+0x2A3 and dword +0x2A4. The iterator call at 0x0043D708 uses +0x2A8, count 20, stride 8 and folded constructor 0x0007E81F; destructor 0x0043D211..0x0043D25B reads each first word with that stride and count. Stores 0x0043D710..0x0043D72F prove dwords +0x348/+0x34C/+0x350/+0x354 and bytes +0x358/+0x359. Method declarations follow matched ledger rows 0x0043C78A/0x0043C85D/0x0043C883/0x0043C8A3/0x0043C9E5/0x0043D5F5/0x0043C9FD/0x0043CD3C/0x0043C8E4; constructor and destructor remain out of line.
#ifndef BFME2_GAMECLIENT_APTSPELLSTORE_H
#define BFME2_GAMECLIENT_APTSPELLSTORE_H

#include "BfmeAptGameWindow.h"

class AptSpellStore : public _bfme_AptGameWindow
{
public:
    AptSpellStore(void *context);
    virtual ~AptSpellStore();
    virtual WindowMsgHandledType input(unsigned int, unsigned int, unsigned int);

    void OnInitialized(const char *);
    void OnRollOverBttnSpell(const char *);
    void OnRollOutBttnSpell(const char *);
    void InputEnabled(int, char *, bool);
    void OnClosed(const char *);
    void OnBttnSpell(const char *);
    void rva0043C9FD();
    void rva0043CD3C();
    void rva0043C8E4(int, int);

private:
    unsigned int field27C[3];
    unsigned int field288[6];
    bool field2A0;
    bool field2A1;
    bool field2A2;
    bool field2A3;
    int field2A4;
    unsigned int field2A8[20][2];
    int field348;
    int field34C;
    int field350;
    int field354;
    bool field358;
    bool field359;
};

typedef char BfmeAptSpellStoreExtent[(sizeof(AptSpellStore) == 0x35C) ? 1 : -1];

#endif
