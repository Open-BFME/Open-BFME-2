// Target facts: constructor RVA 0x004D5593 and destructor RVA 0x004CEE78 install VA 0x00C60130 at +0; scalar deleting destructor RVA 0x004CEEA6 restores it and calls global delete RVA 0x0002FD60. Allocation RVA 0x0058E0BB pushes sizeof 0x1C before the constructor call at RVA 0x0058E0D1.
// Target facts: VA 0x00C60130 has four slots: 0 = RVA 0x004CEEA6, 1 = getSortNumber RVA 0x004CEEA1 (word +0x10), 2 = RVA 0x0047A699 (false), 3 = formatter RVA 0x004D5B4C; the next table starts at VA 0x00C60140. NetGameCommandMsg slot 2 at RVA 0x004D55FC compares dword +0x24 with 0x448. There is no memory-pool slot.
// Target facts: RVA 0x004D5593 writes timestamp +4=-1, execution frame +8=-1, player ID +0xC=0, ID word +0x10=0, command type +0x14=-1, reference count +0x18=1; formatter RVA 0x004D5B4C reads the first five fields. Attach RVA 0x004D55B8 and detach RVA 0x004D55BC change +0x18; setID RVA 0x004CEE90 writes word +0x10. Timestamp reads at RVAs 0x004D5684 and 0x004D31B4 support getTimestamp alongside Zero Hour's GetTimestamp; RVA 0x004D1E5A writes +4, RVAs 0x005941DB/0x005941DE write timing +4/+8, and RVA 0x005941EC writes a decoded integer command type at +0x14. The ledger also names getContentsAsAsciiString at RVA 0x0028F940, distinct from the table's formatter. Zero Hour NetCommandMsg.h supplies the MemoryPoolObject base and field/accessor names; its memory-pool virtual is absent from retail.
#pragma once

#ifndef BFME2_NETCOMMANDMSG_H
#define BFME2_NETCOMMANDMSG_H

#include "../Common/MemoryPoolObject.h"

class AsciiString;
enum NetCommandType;

class NetCommandMsg : public MemoryPoolObject
{
public:
    NetCommandMsg();

    unsigned int GetTimestamp() { return m_timestamp; }
    unsigned int getTimestamp() { return m_timestamp; }
    void SetTimestamp(unsigned int timestamp) { m_timestamp = timestamp; }
    void setTimestamp(unsigned int timestamp) { m_timestamp = timestamp; }
    void setTiming(unsigned int timestamp, unsigned int frame) { m_timestamp = timestamp; m_executionFrame = frame; }
    void setExecutionFrame(unsigned int frame) { m_executionFrame = frame; }
    unsigned int getExecutionFrame() { return m_executionFrame; }
    void setPlayerID(unsigned int playerID) { m_playerID = playerID; }
    unsigned int getPlayerID() { return m_playerID; }
    void setID(unsigned short id);
    unsigned short getID() { return m_id; }
    void setNetCommandType(NetCommandType type) { m_commandType = type; }
    void setNetCommandType(int type) { m_commandType = (NetCommandType)type; }
    NetCommandType getNetCommandType() { return m_commandType; }
    void attach();
    void detach();

protected:
    virtual ~NetCommandMsg();

public:
    virtual int getSortNumber();
    virtual bool vslot08() { return false; }
    virtual AsciiString getContentsAsAsciiString();

public:
    unsigned int m_timestamp;
    unsigned int m_executionFrame;
    unsigned int m_playerID;
    unsigned short m_id;
    NetCommandType m_commandType;
    int m_referenceCount;
};

#endif
