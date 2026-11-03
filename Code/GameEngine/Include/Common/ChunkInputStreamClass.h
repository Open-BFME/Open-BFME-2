// Target facts (code RVAs, table VAs): constructor 0x00240000 stores 0x00BEDCB4 at +0 and constructs a vector at +4, bounding the stream interface to its four-byte vptr; constructor 0x0023DB34 stores 0x00BEDAA8 at +0 and clears the concrete buffer pointers at +4/+8/+0xC.
// The four slots of 0x00BEDCB4 (0x0024002E/35/3D/45) forward through the +0x10 member to 0x00BEDAA8: read 0x00306C15, tell 0x00306C42, absoluteSeek 0x00306C49, eof 0x00306C58. Calls at 0x0030735A, 0x00306DDB and 0x00306C0C confirm slots 1/2/3; slot 0 is read, so there is no virtual destructor. Destructor 0x0023F4F0 restores the shared pure table 0x00C4EF80 at +0x10 and +0; its first four entries are __purecall (0x0003B810), rather than concrete stream methods.
// Donor facts: Zero Hour GeneralsMD Common/MapReaderWriterInfo.h names read(void*, int), unsigned tell(), bool absoluteSeek(unsigned) and bool eof(); its stateless InputStream base is flattened here. No ChunkInputStream constructor, destructor or direct method body is named in the BFME2 ledger, and no registered parent header defines InputStream.
#ifndef BFME2_COMMON_CHUNKINPUTSTREAMCLASS_H
#define BFME2_COMMON_CHUNKINPUTSTREAMCLASS_H

class ChunkInputStream
{
public:
    virtual int read(void *data, int numBytes) = 0;
    virtual unsigned int tell() = 0;
    virtual bool absoluteSeek(unsigned int pos) = 0;
    virtual bool eof() = 0;
};

#endif
