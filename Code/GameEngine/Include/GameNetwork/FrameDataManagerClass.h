// Target facts (addresses are retail RVAs): ctor 0x0058B567 and dtor 0x0058B623 store table 0x00870A0C at +0. Its only slot is scalar deleting dtor 0x0058B86E; the next word at 0x00870A10 is string data. The destructor is virtual and out of line.
// Ctor stores m_frameData at +4 (0x0058B5C1), m_isLocal at +8 (0x0058B578), m_isQuitting at +9 (0x0058B5C5), and m_quitFrame at +0xC (0x0058B5BA). Allocation sites 0x004D1699 and 0x004D1760 in parseUserList allocate 0x10 bytes; the element iterator at 0x0058B5B5 uses 0x14-byte FrameData entries and ctor/dtor 0x005DA4C8/0x005DA4DC.
// Out-of-line rows: reset 0x0058B666, addNetCommandMsg 0x0058B6AB (returns NetCommandRef*), allCommandsReady 0x0058B6D1, getFrameCommandList 0x0058B6F5, resetFrame 0x0058B715, getCommandCount 0x0058B74B, setFrameCommandCount 0x0058B76B, getFrameCommandCount 0x0058B78F, zeroFrames 0x0058B7AF, destroyGameMessages 0x0058B7ED, setQuitFrame 0x0058B818, getIsQuitting 0x0058B826, rva00670890 0x0058B82A, getAckCommandCount 0x0058B84E, getQuitFrame 0x001DB0A8. Zero Hour FrameDataManager.h supplies the MemoryPoolObject base and field names; the registered base has only the destructor slot.
#pragma once

#ifndef BFME2_FRAMEDATAMANAGERCLASS_H
#define BFME2_FRAMEDATAMANAGERCLASS_H

#include "../Common/MemoryPoolObject.h"

class FrameData;
class NetCommandList;
class NetCommandMsg;
class NetCommandRef;
enum FrameDataReturnType;

class FrameDataManager : public MemoryPoolObject
{
public:
    FrameDataManager(bool isLocal);
    virtual ~FrameDataManager();

    void reset();
    NetCommandRef *addNetCommandMsg(NetCommandMsg *msg);
    FrameDataReturnType allCommandsReady(unsigned int frame, bool debugSpewage);
    NetCommandList *getFrameCommandList(unsigned int frame);
    void resetFrame(unsigned int frame, bool isAdvancing = true);
    unsigned int getCommandCount(unsigned int frame);
    void setFrameCommandCount(unsigned int frame, unsigned int commandCount);
    unsigned int getFrameCommandCount(unsigned int frame);
    void zeroFrames(unsigned int startingFrame, unsigned int numFrames);
    void destroyGameMessages();
    void setQuitFrame(unsigned int frame);
    bool getIsQuitting();
    int rva00670890(unsigned int frame, int mark);
    unsigned int getAckCommandCount(unsigned int frame);
    unsigned int getQuitFrame();

protected:
    FrameData *m_frameData;
    bool m_isLocal;
    bool m_isQuitting;
    unsigned int m_quitFrame;
};

#endif
