// NetworkInterface: BFME2's abstract network interface over SubsystemInterface.
// Target facts: RVAs 0x0025DB34/0x0025DB46 install VA 0x00BF5F30 and call SubsystemInterface's 0x001B4E63/0x001B4E74; its fields are byte +4 and AsciiString +8, so the interface is 0x0C bytes with no added data (also Zero Hour's declaration). Network's ctor 0x0025DB6D installs 0x00BF6040; its dtor 0x0025E4CD restores 0x00BF5F30 at 0x0025E504 before the base dtor. These are derived and abstract-base tables, not conflicting class tables. Both have 67 slots (0..66): the abstract table ends at the zero word 0x00BF603C, the concrete one at non-code 0x00BF614C. Slots 0..13 are SubsystemInterface's; 14..66 are pure in 0x00BF5F30 except 61 (0x005DAA6C, returns 0 and pops one word). CreateTheNetwork 0x0025E46D deletes through slot 0, allocates 0x40 bytes for Network at 0x0025E492, and calls init through slot 1 at 0x0025E4BE. Network's data starts with its manager at +0x0C (0x0025DCCB) and state at +0x10 (0x0025E01F); those fields belong to Network. Named concrete slots: 14 startNewSession 0x0025DFA1, 17 ParseUserList 0x0025DBCD, 18 SetLocalAddr 0x0025DBDC, 19/20 InitTransport(int)/InitTransport() 0x0025DC08/0x0025DBFB, 26 sendChat 0x0025E29D, 27 sendDisconnectChat 0x0025E2E3, 28 sendFile 0x0025E327, 29 sendFileAnnounce 0x0025E370, 37 quitGame 0x0025E233. The ledger spells 0x0025E014, 0x0025E163 and 0x0025DCCB as non-virtual NetworkInterface methods, although the table calls them through slots 21, 22 and 43; neutral slots preserve those out-of-line declarations. ProcessDestroyPlayerCommand is the row at 0x0025E539. Other slot signatures follow their rowed concrete bodies; unproved names stay neutral.
// Donor facts: GeneralsMD/GameEngine/Include/GameNetwork/NetworkInterface.h names the interface and its SubsystemInterface base; BFME2's slot order and added methods come from the target, not the donor order.

#pragma once
#ifndef CANONICAL_NETWORKINTERFACECLASS_H
#define CANONICAL_NETWORKINTERFACECLASS_H

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class UnicodeString;
class NetWrapperCommandMsg;
struct NetLocalAddress;

class NetworkInterface : public SubsystemInterface
{
public:
    virtual ~NetworkInterface();
    virtual void init() = 0;
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
    virtual void reset() = 0;
    virtual void update() = 0;
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);

    virtual void startNewSession() = 0; // 14
    virtual void slot15(int) = 0;
    virtual void slot16(int) = 0;
    virtual void ParseUserList(int) = 0;
    virtual void SetLocalAddr(const NetLocalAddress &) = 0;
    virtual void InitTransport() = 0; // MSVC places overloads in reverse order.
    virtual void InitTransport(int) = 0;
    virtual int slot21() = 0;
    virtual int slot22() = 0;
    virtual int slot23() = 0;
    virtual bool slot24() = 0;
    virtual void slot25() = 0;
    virtual void sendChat(UnicodeString, int) = 0;
    virtual void sendDisconnectChat(UnicodeString) = 0;
    virtual void sendFile(AsciiString, unsigned char, unsigned short) = 0;
    virtual unsigned short sendFileAnnounce(AsciiString, unsigned char) = 0;
    virtual int slot30(int, AsciiString) = 0;
    virtual void slot31() = 0;
    virtual void slot32() = 0;
    virtual void slot33() = 0;
    virtual void slot34(int, int, int, int) = 0;
    virtual void slot35(int) = 0;
    virtual void slot36() = 0;
    virtual void quitGame() = 0;
    virtual void slot38(int) = 0;
    virtual void slot39(int) = 0;
    virtual int slot40() = 0;
    virtual int slot41() = 0;
    virtual int slot42() = 0;
    virtual bool slot43() = 0;
    virtual int slot44() = 0;
    virtual int slot45() = 0;
    virtual int slot46() = 0;
    virtual UnicodeString slot47(int) = 0;
    virtual unsigned char slot48() = 0;
    virtual void slot49() = 0;
    virtual void slot50() = 0;
    virtual bool slot51(int) = 0;
    virtual int slot52() = 0;
    virtual float slot53() const = 0;
    virtual float slot54() const = 0;
    virtual float slot55() const = 0;
    virtual float slot56() const = 0;
    virtual float slot57() const = 0;
    virtual float slot58() const = 0;
    virtual int slot59() = 0;
    virtual int slot60() = 0;
    virtual int slot61(int);
    virtual int slot62(int) = 0;
    virtual bool slot63() = 0;
    virtual bool slot64(int) = 0;
    virtual unsigned char slot65(int) = 0;
    virtual void slot66(int, int, int) = 0;

    int getFrameAdvanceCount();
    int getFramePacingStatus();
    int isPacketRouter();
    void ProcessDestroyPlayerCommand(NetWrapperCommandMsg *);
};

#endif
