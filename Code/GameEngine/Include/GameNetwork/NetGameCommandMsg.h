// Target facts: constructors RVAs 0x004D55D6 and 0x004D5CBE call NetCommandMsg RVA 0x004D5593 at +0 and install VA 0x00C601E4; both write command type 4 at +0x14 and five dwords at +0x1C/+0x20/+0x24/+0x28/+0x2C. Allocations at RVAs 0x004D0E13 and 0x00591EB6 push sizeof 0x30 before constructor calls at 0x004D0E2E and 0x00591ECB. The base allocation at RVA 0x0058E0BB is 0x1C bytes.
// Target facts: VA 0x00C601E4 has four slots, followed by the next table at VA 0x00C601F4: 0 = deleting destructor RVA 0x004D5A5E, 1 = inherited getSortNumber RVA 0x004CEEA1, 2 = vslot08 RVA 0x004D55FC (dword +0x24 == 0x448), 3 = getContentsAsAsciiString RVA 0x004D5D55. Destructor RVA 0x004D5609 first stores VA 0x00C601E4 at +0, unlinks the +0x28 list through each node's +4 link, then stores the parent's VA 0x00C60130 at RVA 0x004D564D; the later table belongs to base teardown. There is no memory-pool slot.
// Target facts: RVA 0x004D5CBE copies GameMessage's dword +0x10 to +0x24 and calls addArgument RVA 0x004D5A7A, which links +0x28/+0x2C and receives a 16-byte argument union; formatter RVA 0x004D5D55 reads +0x24 and inherited +4/+8/+0xC/word +0x10. constructGameMessage is rowed at RVA 0x004D68C6. Zero Hour GeneralsMD NetCommandMsg.h supplies the class, method and member names; its memory-pool glue is absent from retail.
#pragma once

#ifndef BFME2_NETGAMECOMMANDMSG_H
#define BFME2_NETGAMECOMMANDMSG_H

#include "NetCommandMsg.h"

class GameMessage;
class GameMessageArgument;
enum GameMessageArgumentDataType;
union GameMessageArgumentType;

class NetGameCommandMsg : public NetCommandMsg
{
public:
    NetGameCommandMsg();
    NetGameCommandMsg(GameMessage *msg);
    virtual ~NetGameCommandMsg();

    GameMessage *constructGameMessage();
    void addArgument(GameMessageArgumentDataType type, GameMessageArgumentType arg);
    virtual bool vslot08();
    virtual AsciiString getContentsAsAsciiString();

public:
    int m_numArgs;
    int m_argSize;
    int m_type;
    GameMessageArgument *m_argList;
    GameMessageArgument *m_argTail;
};

#endif
