// Target facts: constructor RVA 0x004D59D1 (rowed as Rva004D59D1) calls NetCommandMsg RVA 0x004D5593 at +0, writes dword +0x1C=0 and +0x20=-1, installs VA 0x00C60274 at +0 and writes command type 8 at +0x14. NetPacket factory RVA 0x0058E367 pushes sizeof 0x24 at RVA 0x0058E376, calls that constructor at RVA 0x0058E38C, then calls setLeavingPlayerID and setLeaveFrame at RVAs 0x0058E3BA/0x0058E3DF.
// Target facts: VA 0x00C60274 has four virtual slots: 0 = deleting destructor RVA 0x004D5B30, 1 = NetCommandMsg::getSortNumber RVA 0x004CEEA1, 2 = false RVA 0x0047A699, 3 = getContentsAsAsciiString RVA 0x004D634E (rowed as Rva004D59D1). The next message table begins at VA 0x00C60284. The shared deleting destructor calls RVA 0x004CEE78, which restores the base table VA 0x00C60130, then conditionally calls global delete RVA 0x0002FD60; that teardown table does not describe the live derived object.
// Target facts: setLeaveInfo RVA 0x004D59EE writes frame +0x1C and player ID +0x20; setLeaveFrame RVA 0x004D59FF writes type 8 at +0x14 and frame +0x1C; setLeavingPlayerID RVA 0x00317B9B writes player ID +0x20. Receiver RVA 0x004CFD06 calls the folded +0x1C/+0x20 getters at RVAs 0x004CFD23/0x004CFD2F; formatter RVA 0x004D634E reads those fields and uses the leavePlayer/playerLeaveFrame format at VA 0x00C604A4. These are BFME-specific fields; Zero Hour NetCommandMsg.h supplies the parent declaration, not this class's name.
#pragma once

#ifndef BFME2_NETINFORMPLAYERLEAVEFRAMECOMMANDMSG_H
#define BFME2_NETINFORMPLAYERLEAVEFRAMECOMMANDMSG_H

#include "NetCommandMsg.h"

class BFMENetInformPlayerLeaveFrameCommandMsg : public NetCommandMsg
{
public:
    BFMENetInformPlayerLeaveFrameCommandMsg();

    void setLeaveInfo(int playerID, unsigned int frame);
    void setLeaveFrame(unsigned int frame);
    void setLeavingPlayerID(int playerID);

protected:
    virtual ~BFMENetInformPlayerLeaveFrameCommandMsg();

public:
    virtual AsciiString getContentsAsAsciiString();

    unsigned int m_leaveFrame;
    int m_leavingPlayerID;
};

#endif
