// Target facts: addresses of code are RVAs and table addresses are VAs. Constructor 0x0054E7BA stores 0x00C6A894 at +0; its deleting destructor 0x0054E79D restores that table and conditionally deletes this without member teardown. The table has 14 entries: slot 0 is 0x0054E79D, slots 1-13 are __purecall (0x0003B810), and non-code starts at 0x00C6A8CC. These bodies and the first implementation member at +4 support a data-free polymorphic root with a primary vptr at +0, sizeof 4 and no base or virtual bases; sizeof is a structural inference. Factory 0x0054F4AF allocates 0x68 and calls implementation constructor 0x0054E8DC, whose store at 0x0054E8FE installs 0x00C6AA10. Implementation destructor 0x0054F434 installs that table at 0x0054F445, destroys members at +0x64, +0x58, +0x48, +0x3C, +0x30 and +4, then restores 0x00C6A894 at 0x0054F49F. The two tables describe implementation and interface destruction phases. The interface destructor is empty and inlined there.
// Target slots in implementation table 0x00C6AA10: 0 deleting destructor=0x0054F418 (calls 0x0054F434); 1 list getter=0x0054F3E2 (+4); 2 integer getter=0x0030F45F (+8); 3 integer getter=0x001DB0A8 (+0x0C); 4 integer getter=0x001DB09D (+0x10); 5 integer getter=0x0057E556 (+0x14); 6 list getter=0x0054F3FD (+0x48); 7 integer getter=0x002A98A7 (+0x4C); 8 integer getter=0x00225A98 (+0x50); 9 integer setter=0x003FF328 (one stack argument, writes +0x50, ret 4); 10 isPlayerVIP=0x0054E86D; 11 getManglerLocation=0x0054E7EA (int, AsciiString &, unsigned short &); 12 string getter=0x0054F3C7 (+0x64); 13 byte getter=0x005C4AE5 (+0x54). Slots 14-19 are implementation additions; they do not occur in the interface table. Slot 9 is the setter paired with slot 8, not a no-argument placeholder.
// Declaration evidence: Zero Hour GeneralsMD GameNetwork/GameSpy/GSConfig.h supplies the class-key, data-free root, empty destructor and the method names paired with the retail operations above. BFME2 removes Zero Hour's getPointsForRank slot: the ledger proves isPlayerVIP at slot 10 and getManglerLocation at slot 11. Factory spelling and by-value AsciiString argument are rowed at 0x0054F4AF. Container and string results are copied out of line by 0x0054F3E2, 0x0054F3FD and 0x0054F3C7. No constructor, copy constructor or assignment of this interface is called out of line under this name.
#pragma once

#ifndef BFME2_GAMESPYCONFIGINTERFACE_H
#define BFME2_GAMESPYCONFIGINTERFACE_H

class AsciiString;

namespace _STL {
template <class T> class allocator;
template <class T, class A> class list;
}

class GameSpyConfigInterface
{
public:
    virtual ~GameSpyConfigInterface() {}
    virtual _STL::list<AsciiString, _STL::allocator<AsciiString> > getPingServers() = 0;
    virtual int getNumPingRepetitions() = 0;
    virtual int getPingTimeoutInMs() = 0;
    virtual int getPingCutoffGood() = 0;
    virtual int getPingCutoffBad() = 0;
    virtual _STL::list<AsciiString, _STL::allocator<AsciiString> > getQMMaps() = 0;
    virtual int getQMBotID() = 0;
    virtual int getQMChannel() = 0;
    virtual void setQMChannel(int channel) = 0;
    virtual bool isPlayerVIP(int id) = 0;
    virtual bool getManglerLocation(int index, AsciiString &host, unsigned short &port) = 0;
    virtual AsciiString getLeftoverConfig() = 0;
    virtual bool restrictGamesToLobby() = 0;

    static GameSpyConfigInterface *create(AsciiString config);
};

#endif
