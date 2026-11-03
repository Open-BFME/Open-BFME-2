// Target facts (code addresses are RVAs; table addresses are VAs):
// Ctor 0x0043AE44 calls Rva00355D66's ctor 0x00355D4E at 0x0043AE59 and stores VA 0x00C3D50C at 0x0043AE68. Dtor 0x0043A396 stores the same table at 0x0043A3AB, calls the embedded preview dtor 0x0057E3DB on +0x18 at 0x0043A549, then calls the base dtor 0x00355D66 at 0x0043A554. The class is polymorphic. The separately allocated 12-byte helper receives VA 0x00C3D490 at 0x0043AE81; that table belongs to the helper, not AptLoadScreen.
// VA 0x00C3D50C has six slots: 0x0043AE28 (deleting dtor), 0x0043A0C1 (one int), 0x0043A5F6 (init), 0x0043A0B2 (no arguments), 0x0043A15D (processProgress), 0x0050B5C6 (bool true). The next word at VA 0x00C3D524 is string data. Only the rowed AptLoadScreen members name slots; the other slots retain neutral names.
// Allocation 0x0023E009 pushes 0xD4, calls operator new at 0x0023E00E, then calls the ctor at 0x0023E02A. Ctor stores prove +0x10 (0x0043AE6E), +0x14 (0x0043AE71), +0x88 (0x0043AEA2), +0x8C (0x0043AE99/0x0043AFAA), two eight-int arrays +0x90/+0xB0 (0x0043AEB4..0x0043AEC6), and byte +0xD0 (0x0043AEA8).
// Ctor 0x0043AE94 constructs the preview at +0x18; its own ctor 0x0057CF43 writes through +0x6C at 0x0057CFAD. The next outer field is +0x88, so field18 retains the full 0x70-byte member representation without assigning its conflicting ledger lifecycle names. Init stores its GameInfo argument at +0x88 (0x0043A61B); PlayerColor passes that pointer to GameInfo::getSlot at 0x0043A1F4..0x0043A1FF. GameLoadingType switches on +0x14 at 0x0043A249. ProcessProgress passes +0x8C as invoke's owner handle at 0x0043A1AE and indexes +0xB0 at 0x0043A174.
// Ctor registration uses PlayerColor 0x0043A1C0 at 0x0043AECE and GameLoadingType 0x0043A242 at 0x0043AF29. Ctor and dtor remain declarations so callers use their rowed out-of-line bodies.
#ifndef BFME2_GAMECLIENT_APTLOADSCREEN_H
#define BFME2_GAMECLIENT_APTLOADSCREEN_H

#include "Rva00355D66.h"

class GameInfo;
class WindowLayout;

class AptLoadScreen : public Rva00355D66
{
public:
    AptLoadScreen(void *);
    virtual ~AptLoadScreen();
    virtual void vslot01(int);
    virtual void init(GameInfo *);
    virtual void vslot03();
    virtual void processProgress(int, int);
    virtual bool vslot05();

    void PlayerColor(int, char *, bool);
    void GameLoadingType(int, char *, bool);

private:
    WindowLayout *field10;
    int field14;
    unsigned char field18[0x70];
    GameInfo *field88;
    void *field8C;
    int field90[8];
    int fieldB0[8];
    bool fieldD0;
};

typedef char BfmeAptLoadScreenExtent[(sizeof(AptLoadScreen) == 0xD4) ? 1 : -1];

#endif
