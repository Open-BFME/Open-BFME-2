/* Target facts: ChunkLoadClass has no virtual functions or base subobject. Its constructor (RVA 0x00614EF0) writes File = 0 at +0, Input at +4 and StackIndex = 0 at +8 without storing a vptr or calling a base constructor. Open_Chunk (0x00614F50) and Read (0x006151A0) dispatch through File at +0 (Read slot +0x24) or Input at +4 (Read slot +0x0C); these are the streams' tables, not ChunkLoadClass tables. Constructor stores prove PositionStack[256] at +0x0C, HeaderStack[256] of eight-byte records at +0x40C, InMicroChunk at +0xC0C, MicroChunkPosition at +0xC10 and the two-byte MCHeader at +0xC14. The stack object at 0x001808B0 occupies +0xC18 bytes between EBP-0xD1C and the buffer at EBP-0x104; the 0x0014D078 consumer also leaves no ChunkLoadClass destructor call. No ChunkLoadClass destructor, copy constructor or assignment is rowed.
Target methods: Open_Chunk 0x00614F50, Close_Chunk 0x00614FC0, Cur_Chunk_ID 0x00615020, Cur_Chunk_Length 0x00615030, Contains_Chunks 0x00615040, Close_Micro_Chunk 0x00615050, Cur_Micro_Chunk_ID 0x006150A0, Cur_Micro_Chunk_Length 0x006150B0, Seek 0x006150C0, Read 0x006151A0, rva00615230 0x00615230 and Open_Micro_Chunk 0x00615430 have ledger rows and remain out of line. The accessors prove the header's type/size words and byte-sized micro ID/length. ChunkHeader Set_Size 0x00614D10, Get_Size 0x00614D30, Set_Sub_Chunk_Flag 0x00614D40 and Add_Size 0x00615240, plus MicroChunkHeader Set_Type 0x00614D70, Set_Size 0x00614D90 and Add_Size 0x00615270, have rowed inline copies.
Donor facts: GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/chunkio.h supplies the field and helper names, the helper definitions and Cur_Chunk_Depth declaration. BFME2's extra Input pointer and constructor signature are target facts, not the donor's FileClass constructor. */

#pragma once

#ifndef BFME2_CHUNKLOADCLASS_H
#define BFME2_CHUNKLOADCLASS_H

class FileClass;
class BFMEChunkInput;
struct IOVector2Struct;
struct IOVector3Struct;
struct IOVector4Struct;
struct IOQuaternionStruct;

struct MicroChunkHeader
{
    MicroChunkHeader() {}
    MicroChunkHeader(unsigned char type, unsigned char size) { ChunkType = type; ChunkSize = size; }

    void Set_Type(unsigned char type) { ChunkType = type; }
    unsigned char Get_Type() { return ChunkType; }
    void Set_Size(unsigned char size) { ChunkSize = size; }
    void Add_Size(unsigned char add) { Set_Size(Get_Size() + add); }
    unsigned char Get_Size() { return ChunkSize; }

    unsigned char ChunkType;
    unsigned char ChunkSize;
};

struct ChunkHeader
{
    ChunkHeader() : ChunkType(0), ChunkSize(0) {}
    ChunkHeader(unsigned long type, unsigned long size) { ChunkType = type; ChunkSize = size; }

    void Set_Type(unsigned long type) { ChunkType = type; }
    unsigned long Get_Type() { return ChunkType; }
    void Set_Size(unsigned long size) { ChunkSize &= 0x80000000; ChunkSize |= size & 0x7FFFFFFF; }
    void Add_Size(unsigned long add) { Set_Size(Get_Size() + add); }
    unsigned long Get_Size() { return ChunkSize & 0x7FFFFFFF; }
    void Set_Sub_Chunk_Flag(bool onoff)
    {
        if (onoff) { ChunkSize |= 0x80000000; } else { ChunkSize &= 0x7FFFFFFF; }
    }
    int Get_Sub_Chunk_Flag() { return ChunkSize & 0x80000000; }

    unsigned long ChunkType;
    unsigned long ChunkSize;
};

class ChunkLoadClass
{
public:
    ChunkLoadClass(BFMEChunkInput *input);

    bool Open_Chunk();
    bool Close_Chunk();
    unsigned long Cur_Chunk_ID();
    unsigned long Cur_Chunk_Length();
    int Cur_Chunk_Depth();
    int Contains_Chunks();

    bool Open_Micro_Chunk();
    bool Close_Micro_Chunk();
    unsigned long Cur_Micro_Chunk_ID();
    unsigned long Cur_Micro_Chunk_Length();

    unsigned long Read(void *buffer, unsigned long bytes);
    unsigned long Read(IOVector2Struct *value);
    unsigned long Read(IOVector3Struct *value);
    unsigned long Read(IOVector4Struct *value);
    unsigned long Read(IOQuaternionStruct *value);
    unsigned long rva00615230(void *buffer);
    unsigned long Seek(unsigned long bytes);

private:
    enum { MAX_STACK_DEPTH = 256 };

    FileClass *File;
    BFMEChunkInput *Input;
    int StackIndex;
    unsigned long PositionStack[MAX_STACK_DEPTH];
    ChunkHeader HeaderStack[MAX_STACK_DEPTH];
    bool InMicroChunk;
    int MicroChunkPosition;
    MicroChunkHeader MCHeader;
};

#endif
