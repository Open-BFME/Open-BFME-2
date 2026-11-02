// Target facts: constructor RVA 0x0058B06A and scalar deleting destructor RVA 0x0058B50F store VA 0x00C70A08 at +0. Its sole slot is RVA 0x0058B50F; VA 0x00C70A0C starts FrameDataManager's table (RVA 0x0058B86E), installed by its constructor at RVA 0x0058B57B. The destructor calls reset RVA 0x0058B283 and global delete RVA 0x0002FD60 when flag bit 0 is set; its row's MAE spelling requires protected virtual destruction. There are no other virtual slots or base-constructor calls.
// Target facts: FrameData::init pushes sizeof 0x10 at RVA 0x005DA50D and calls the constructor at 0x005DA522; ConnectionManager::reset repeats this at 0x004D06FA/0x004D070E and 0x004D073A/0x004D0752. Constructor stores clear dwords +4/+8/+0xC. removeMessage RVA 0x0058B07E and addMessage RVA 0x0058B2C6 prove head +4, tail +8 and last-inserted +0xC; Connection::isQueueEmpty RVA 0x0058B9A9 reads the head at 0x0058B9AC. Zero Hour NetCommandList.h supplies the field names and getFirstMessage; BFME2 uses global allocation and deletion without pool glue.
// Target facts: ledger rows name length RVA 0x0058B0CA, findMessage(id,player,timestamp) 0x0058B0D7, findMessage(id,player,type,frame) 0x0058B121, isEqualCommandMsg 0x0058B174 (bool), reset 0x0058B283, addMessage 0x0058B2C6, findMessage(msg) 0x0058B4E2 and appendList 0x0058B531. The init pin names reset's body; calls at 0x004D0722/0x004D072D and 0x005DA534/0x005DA53C reach it. Virtual destruction at RVAs 0x004D33BF (ConnectionManager), 0x0058BF55 (Connection) and 0x005DA4EA (FrameData) supports their destructor access. Constructor and destructor remain out of line.
#pragma once

#ifndef BFME2_NETCOMMANDLISTCLASS_H
#define BFME2_NETCOMMANDLISTCLASS_H

class NetCommandRef;
class NetCommandMsg;
enum NetCommandType;

class NetCommandList
{
    friend class ConnectionManager;
    friend class Connection;
    friend class FrameData;

public:
    NetCommandList();

    void init();
    void reset();
    NetCommandRef *addMessage(NetCommandMsg *msg);
    bool isEqualCommandMsg(NetCommandMsg *msg1, NetCommandMsg *msg2);
    NetCommandRef *getFirstMessage() { return m_first; }
    NetCommandRef *findMessage(NetCommandMsg *msg);
    NetCommandRef *findMessage(unsigned short id, unsigned char player, unsigned int timestamp);
    NetCommandRef *findMessage(unsigned short id, unsigned char player, NetCommandType type, unsigned int frame);
    void removeMessage(NetCommandRef *msg);
    void appendList(NetCommandList *list);
    int length();

protected:
    virtual ~NetCommandList();

public:
    NetCommandRef *m_first;
    NetCommandRef *m_last;
    NetCommandRef *m_lastMessageInserted;
};

#endif
