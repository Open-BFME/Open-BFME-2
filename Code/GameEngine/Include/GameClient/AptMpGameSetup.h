// Target facts (code addresses are RVAs; table addresses are VAs): constructor 0x00441ECE calls Rva005248D0's constructor 0x002D2C34 at unchanged this (0x00441EE3), then stores 0x00C3DD7C at +0 (0x00441EF3). Destructor 0x004421E1 stores the same table (0x004421F2) and calls the base destructor 0x005248D0 (0x004422A2). This is a polymorphic class. Its three table words are 0x008428AD (deleting destructor), 0x0083FFD7 (reset), and 0x008421DA (const dword getter at +0x394); string data starts at 0x00C3DD88. slot01 and slot02 have no proven member names. The base's distinct table 0x00C02A80 is stored at 0x002D2C8C and 0x005248E1; 0x00C02A84 begins another table.
// Target facts: the base constructor calls six non-polymorphic holders at +0x04/+0x10/+0x1C/+0x34/+0x40/+0x4C (0x002D2C42..0x002D2C84); the base destructor destroys them in reverse order (0x005248E7..0x0052492D), establishing its 0x58-byte span. The panel constructor initializes owner +0x58 and reference +0x5C (0x00441EF9..0x00441F08), members +0x60/+0xD0/+0x190/+0x244 (0x00441F19..0x00441F6C), 8 four-byte wrappers at +0x2F4 (0x00441F71..0x00442000), string-vector storage +0x398 (0x00442008), and bit-vector storage +0x3C4 (0x00442026). Destructor stores of 0x00C3D954/+0xD0 and 0x00C3D95C/+0x190 (0x00442260..0x0044227B) belong to embedded objects, not the panel's primary table.
// Target facts: 0x0043EDD7 compares the dword at +0x7C with 1. Constructor stores establish +0x2B0/+0x2B4, bytes +0x2B8..+0x2C4 (except +0x2BB, written by 0x00440A68), dwords +0x2C8/+0x2CC/+0x2D0, six 8-element arrays at +0x2D4/+0x2F4/+0x314/+0x334/+0x354/+0x374, +0x394, dwords +0x3A4/+0x3A8/+0x3AC/+0x3B0, image pointers +0x3B8/+0x3BC/+0x3C0, +0x3D8 and byte +0x3DC (0x00441F8A..0x00442141). The containing constructors 0x005A5BC7 and 0x00522B0E place this panel at +0x70/+0x288 and their next members at +0x450/+0x668, bounding sizeof to 0x3E0 with four-byte alignment. Storage without a proven declaration remains opaque; methods are declarations of matched ledger bodies at 0x0043DB6E..0x00443EA8, including out-of-line constructor/destructor at 0x00441ECE/0x004421E1.
#ifndef BFME2_APTMPGAMESETUP_H
#define BFME2_APTMPGAMESETUP_H

#include "Rva005248D0.h"

class AsciiString;
class UnicodeString;
class GameInfo;
class GameSlot;
class GameWindow;
class Image;
class MpGameSetupOwner;
class Rva0043DA65;
class TreeHintOpaque0043671B;
class WinInstanceData;

class AptMpGameSetup : public Rva005248D0
{
public:
    AptMpGameSetup(MpGameSetupOwner *owner, int flags);
    virtual ~AptMpGameSetup();
    virtual void slot01();
    virtual int slot02() const;

    void rva0043DB6E();
    void rva0043DC0F();
    void rva0043DC40(int column);
    void OnSortName(const char *argument);
    void OnSortPlayers(const char *argument);
    void OnSortIcons(const char *argument);
    void OnTabSelect(const char *argument);
    bool rva0043DCFA(int value);
    int GetDisplayedPlayerTemplateIndex(int slot);
    bool SetSlotHeroData(GameSlot *slot, int hero);
    void InitGadgets();
    unsigned int rva0043DF22();
    static void PlayerTooltip(GameWindow *window, WinInstanceData *data, unsigned int flags);
    bool HandleHeroSelection(int slot);
    bool rva0043E1CC(int slot);
    void rva0043E253(int slot);
    void ChangePlayerSelection(int slot, int value);
    void rva0043E3E2(int slot, int team);
    void rva0043E49C(const UnicodeString &text);
    void OnKickPlayer(const char *argument);
    const Image *rva0043E512(int value);
    void rva0043E5C1(int slot, int kind, int value);
    bool InitGameInfoFromSaveGame(GameInfo *game);
    void InitGadgets(const char *name, void *argument, GameWindow *window);
    bool rva0043ECC1(int slot);
    void rva0043EDB4();
    void OnReadyPress(const char *argument);
    void rva0043F244(int slot, bool reset);
    void PopulatePlayerCombo(int slot);
    void UpdateHeroDisplay(int slot);
    void rva0043FA68(GameInfo *game);
    void UpdateReadyIcon(int slot);
    bool rva0043FC1F(int kind, bool reset);
    void rva0043FFCF();
    void rva0043FFD7();
    void rva00440017(const AsciiString &map);
    bool PopulateColorCombo(int slot);
    void rva004404AC(bool enabled, int slot);
    void PopulateHeroCombo(int slot);
    bool HandleClanChange();
    bool OnHostStartGame(bool value);
    bool WaitStartGame();
    void UpdateHeroToFaction(GameSlot *slot, int index, bool flag);
    void rva004415D5(const AsciiString &map);
    void rva00441685(bool flag);
    void UpdatePlayerTemplateDisplay(int slot);
    void InitAvailableColors();
    bool handlePlayerTemplateSelection(int slot);
    void UpdateSlot(int slot);
    void rva004422B4(int mode);
    void HostValidateColors();
    void PopulatePlayerTemplateCombo(int slot);
    void rva004427C5(int slot);
    void rva004427FA();
    void UpdateClans();
    void rva00442A19();
    bool rva00442A68(int slot);
    bool rva00442BCC();
    bool rva00442C9C();
    int rva00442CB3(unsigned int message, unsigned int data1, unsigned int data2);
    void ExternFunc(int query, char *result, bool skip);
    void rva0044303D();
    void rva00443538(int flags);
    void rva00443BF3();
    bool Init(GameInfo *game, int value);
    bool OnUpdate();

    MpGameSetupOwner *field58;
    Rva0043DA65 *field5c;
    unsigned int field60[0x1C / 4];
    int field7c;
    unsigned int field80[0x50 / 4];
    unsigned int fieldd0[0xC0 / 4];
    unsigned int field190[0xB4 / 4];
    unsigned int field244[0x6C / 4];
    TreeHintOpaque0043671B *field2b0;
    int field2b4;
    bool field2b8, field2b9, field2ba, field2bb, field2bc;
    bool field2bd, field2be, field2bf, field2c0, field2c1;
    bool field2c2, field2c3, field2c4;
    int field2c8, field2cc, field2d0;
    GameWindow *field2d4[8];
    unsigned int field2f4[8];
    GameWindow *field314[8];
    GameWindow *field334[8];
    GameWindow *field354[8];
    GameWindow *field374[8];
    GameWindow *field394;
    unsigned int field398[3];
    int field3a4, field3a8, field3ac, field3b0;
    unsigned char field3b4[4];
    const Image *field3b8, *field3bc, *field3c0;
    unsigned int field3c4[5];
    int field3d8;
    bool field3dc;
};

#endif
