/* Target facts (BFME2 retail, addresses are RVAs unless marked VA):
Constructor 0x0052DB99 (11 bytes) returns this and clears only dwords +0x34/+0x38. It calls no base constructor and stores no vptr. Initializer 0x002E6BA1 writes integer input coordinates at +0/+4, so +0 is data. This is a plain class with no virtual functions, base subobjects or vtable slots; no destructor row exists.
Pool initializer 0x0052DBCD allocates 0x3C00 bytes at 0x0052DBDA, passes count 0x100, stride 0x3C and constructor VA 0x0092DB99 to the vector constructor iterator at 0x0052DBF7..0x0052DC00, then advances each buffer by 0x3C at 0x0052DC15. sizeof(MixFileInfoBuffer) is 0x3C.
The same pooled object passes through unlink 0x002E6BE2 and initializer 0x002E6BA1 at 0x002E8B83/0x002E8B92. Initializer stores dwords +0/+4/+8/+0x0C, words +0x10/+0x12, five zero dwords +0x14..+0x24, a zero dword +0x28, masked flags +0x2C and its owner argument +0x30. Caller 0x004DD9E3 accesses pointer entries at +0x14+index*4 (0x004DDA6D/0x004DDA78).
ReleaseClosedList 0x0052DE9B follows +0x34, reads a PathfindCell pointer at +0x30 and calls ReleaseInfo at 0x0052DEC4. Unlink 0x002E6BE2 and link 0x0052DBA4 prove a next pointer at +0x34 and a pointer to the preceding link at +0x38.
The ledger declares constructor 0x0052DB99, private bfmeUnlink 0x002E6BE2, private bfmeLinkInto 0x0052DBA4 and public releaseInto 0x0052DD41. Retail calls these bodies out of line; the header only declares them. Unlink has no calls and link calls only unlink, so both helpers are nonthrowing. PathfindCell calls unlink at 0x0052DA9A/0x0052DB04/0x0052DEB4 and tail-jumps to link at 0x0052DC37; pool initialization calls link at 0x0052DC10 and Rva002E8B7AInit calls unlink at 0x002E8B83. StartPathfind clears bits 0x08/0x10 at +0x2C (0x0052DAB4/0x0052DABA), proving m_flags is a flag word. The other data names are neutral offsets.
*/
#pragma once

#ifndef BFME2_MIXFILEINFOBUFFER_H
#define BFME2_MIXFILEINFOBUFFER_H

class PathfindCell;
class Rva002E6BA1;
struct In002E6BA1;

class MixFileInfoBuffer
{
public:
    MixFileInfoBuffer();
    void releaseInto(void *head);

private:
    void bfmeUnlink() throw();
    void bfmeLinkInto(MixFileInfoBuffer **head) throw();
    friend class PathfindCell;
    friend class Rva002E6BA1;
    friend void Rva0052DBCDInit();
    friend MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **, int, In002E6BA1 *);

public:
    int field00;
    int field04;
    int field08;
    int m_0C;
    unsigned short field10;
    unsigned short field12;
    void *field14[5];
    int field28;
    unsigned int m_flags;
    PathfindCell *field30;
    MixFileInfoBuffer *field34;
    MixFileInfoBuffer **field38;
};

#endif
