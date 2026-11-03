// Target facts: constructor RVA 0x004D5844 calls ??0NetCommandMsg (RVA 0x004D5593) at +0, zeroes dwords +0x1C..+0x30 and word +0x34, installs VA 0x00C60254 at +0 and writes command type 18 at +0x14. Allocations at RVA 0x0058E0F2 (readWrapperMessage, constructor call RVA 0x0058E108) and RVA 0x0059474B (ConstructBigCommandPacketList, constructor call RVA 0x00594762) push sizeof 0x38.
// Target facts: VA 0x00C60254 has four slots: 0 = ??_G RVA 0x004D5AF8, 1 = getSortNumber RVA 0x004CEEA1, 2 = RVA 0x0047A699, 3 = RVA 0x004D5B4C; slots 1-3 are NetCommandMsg's (VA 0x00C60130) and the next table starts at VA 0x00C60264. Only the destructor is overridden. Destructor RVA 0x004D5871 installs VA 0x00C60254, frees +0x1C through global delete RVA 0x0002FD60, then installs the base table VA 0x00C60130 (the inline empty base destructor); ??_G RVA 0x004D5AF8 calls it and frees through RVA 0x0002FD60.
// Target facts: getData RVA 0x0030F2C7 (+0x1C), getDataLength RVA 0x0030D377 (+0x20), getDataOffset RVA 0x00091A56 (+0x24), getTotalDataLength RVA 0x005C4AE1 and setTotalDataLength RVA 0x0033F8CA (+0x28), getNumChunks RVA 0x003F3FE8 (+0x30), get/setWrappedCommandID RVAs 0x004D58CD/0x004D58D2 (word +0x34); setData RVA 0x004D5894 frees +0x1C, allocates, copies and writes +0x1C/+0x20. readWrapperMessage RVA 0x0058E0E2 calls setChunkNumber, setNumChunks and setDataOffset at the folded setters RVA 0x002B2210 (+0x2C), 0x00210C87 (+0x30) and 0x005739F6 (+0x24); copyChunkData RVA 0x0058C047 calls getChunkNumber at the folded getter RVA 0x005C4ACD (+0x2C). Zero Hour NetCommandMsg.h supplies the member and accessor names; its memory-pool glue is absent from retail.
#pragma once

#ifndef BFME2_NETWRAPPERCOMMANDMSG_H
#define BFME2_NETWRAPPERCOMMANDMSG_H

#include "NetCommandMsg.h"

class NetWrapperCommandMsg : public NetCommandMsg
{
public:
    NetWrapperCommandMsg();

    unsigned char *getData();
    void setData(unsigned char *data, unsigned int dataLength);
    unsigned int getChunkNumber();
    void setChunkNumber(unsigned int chunkNumber);
    unsigned int getNumChunks();
    void setNumChunks(unsigned int numChunks);
    unsigned int getDataLength();
    unsigned int getTotalDataLength();
    void setTotalDataLength(unsigned int totalDataLength);
    unsigned int getDataOffset();
    void setDataOffset(unsigned int offset);
    unsigned short getWrappedCommandID();
    void setWrappedCommandID(unsigned short wrappedCommandID);

protected:
    virtual ~NetWrapperCommandMsg();

public:
    unsigned char *m_data;
    unsigned int m_dataLength;
    unsigned int m_dataOffset;
    unsigned int m_totalDataLength;
    unsigned int m_chunkNumber;
    unsigned int m_numChunks;
    unsigned short m_wrappedCommandID;
};

#endif
