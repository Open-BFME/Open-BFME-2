// Target facts: constructor RVA 0x004CEEC3 calls NetCommandMsg RVA 0x004D5593 at +0, writes dwords +0x1C=0, +0x20=0, +0x24=-1, installs VA 0x00C60140 at +0 and writes type 3 at +0x14. Allocations at RVAs 0x004D0AB8 and 0x0058DCFB push sizeof 0x28 before constructor calls at RVAs 0x004D0AD3 and 0x0058DD10.
// Target facts: VA 0x00C60140 has four virtual slots: 0 = shared deleting destructor RVA 0x004D5B30, 1 = NetCommandMsg::getSortNumber RVA 0x004CEEA1, 2 = false RVA 0x0047A699, 3 = getContentsAsAsciiString RVA 0x004D5C2B; string data begins at VA 0x00C60150. The deleting destructor calls RVA 0x004CEE78, which restores the base table VA 0x00C60130, then conditionally calls global delete RVA 0x0002FD60. That base teardown store does not describe the live derived object.
// Target facts: sendFrameInfo RVA 0x004D0AA9 writes logic frame +0x1C at RVA 0x004D0AEC, client frame +0x20 at RVA 0x004D0AFD and command count +0x24 at RVA 0x004D0B91. Formatter RVA 0x004D5C2B reads those dwords at RVAs 0x004D5C57/0x004D5C5A/0x004D5C5D using the logicFrame/clientFrame/totalCommands string at VA 0x00C602FC; factory RVA 0x0058DCEB writes them at RVAs 0x0058DD3A/0x0058DD56/0x0058DD78. Packet writer RVAs 0x00590850/0x00590871/0x00590892 read the three dwords; Connection RVA 0x0058BC87 reads +0x1C for type 3. Zero Hour NetCommandMsg.h supplies the class, parent and command-count accessor names; its 16-bit count differs from these retail 32-bit accesses.
#pragma once

#ifndef BFME2_NETFRAMECOMMANDMSG_H
#define BFME2_NETFRAMECOMMANDMSG_H

#include "NetCommandMsg.h"

class NetFrameCommandMsg : public NetCommandMsg
{
public:
    NetFrameCommandMsg();

    unsigned int getFrame() const { return m_frame; }
    void setFrame(unsigned int frame) { m_frame = frame; }
    unsigned int getPlayerFrame() const { return m_playerFrame; }
    void setPlayerFrame(unsigned int frame) { m_playerFrame = frame; }
    unsigned int getCommandCount() const { return m_commandCount; }
    void setCommandCount(unsigned int count) { m_commandCount = count; }


    virtual AsciiString getContentsAsAsciiString();

    unsigned int m_frame;
    unsigned int m_playerFrame;
    unsigned int m_commandCount;
};

#endif
