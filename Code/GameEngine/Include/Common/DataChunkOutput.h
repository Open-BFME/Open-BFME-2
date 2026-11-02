// Target facts (code addresses are RVAs):
// DataChunkOutput has no virtual functions or base classes. Constructor 0x00306FA5 stores its OutputStream argument at +0 (0x00306FB7), initializes contents at +8 (0x00306FBE..0x00306FCB), stores the _wfopen result at +4 (0x00307013), and clears the chunk stack at +0x18 (0x00307016). Neither it nor destructor 0x00307680 stores a vftable.
// Contents constructor 0x00306D48 initializes list +0, count +4, next ID +8 and flag +0xC, exactly as the output constructor does at +8. The contents occupies 0x10 bytes; the stack pointer at +0x18 completes the 0x1C-byte layout shared by the complete matched views and Zero Hour's declaration.
// Destructor 0x00307680 passes this+8 to contents.write at 0x003076A5, reads the stream from +0 at 0x0030771A and invokes that stream's slot 0 at 0x0030772C, then calls the contents destructor 0x00306D5C at 0x00307768. These indirect calls belong to member objects, not to DataChunkOutput; there are no competing constructor/destructor tables or inherited slots.
// openDataChunk 0x00307C76 passes this+8 to allocateID at 0x00307C9E, stores table 0x00C07E80 into a newly allocated OutputChunk at 0x00307CBE, and links that node through this+0x18 at 0x00307CC6..0x00307CD5. closeDataChunk 0x00306C88 reads and updates this+0x18 at 0x00306CDC..0x00306CE5, then invokes the node's destructor at 0x00306CF3. That table belongs to OutputChunk, not DataChunkOutput.
// Out-of-line rows: constructor 0x00306FA5, destructor 0x00307680, openDataChunk 0x00307C76, closeDataChunk 0x00306C88, writeInt/writeReal 0x00306CFF (ICF), writeByte 0x00306D17, writeArrayOfBytes 0x00306D2F, writeAsciiString 0x00307033, writeUnicodeString 0x0030708E, writeNameKey 0x00307D29, writeDict 0x00307D85. Their ledger manglings prove the declared signatures. writeInt/writeByte/writeArrayOfBytes pass the file at +4 to fwrite; writeUnicodeString destroys its by-value argument at 0x003070E6.
// writeAsciiString has an ordinary public declaration: SidesList sets temporary cleanup states at 0x0032A7F0, 0x0032A813 and 0x0032A8B5 before calling it at 0x0032A7F4, 0x0032A817 and 0x0032A8B9; PostFX sets a temporary cleanup state at 0x000AFE59 before its call at 0x000AFE67. writeDict's call at 0x00307E5E has no separate temporary cleanup state, consistent with its provider unit's local throw() definition. Zero Hour GeneralsMD Common/DataChunk.h supplies the member names and DataChunkVersionType; its header is not included.
#ifndef BFME2_COMMON_DATACHUNKOUTPUT_H
#define BFME2_COMMON_DATACHUNKOUTPUT_H

#include "DataChunk.h"

struct _iobuf;
class OutputChunk;

class DataChunkOutput
{
public:
    DataChunkOutput(OutputStream *stream);
    ~DataChunkOutput();

    void openDataChunk(char *name, DataChunkVersionType version);
    void closeDataChunk();
    void writeReal(float value);
    void writeInt(int value);
    void writeByte(unsigned char value);
    void writeAsciiString(const AsciiString &text);
    void writeUnicodeString(UnicodeString text);
    void writeArrayOfBytes(char *buffer, int length);
    void writeDict(const Dict &dict);
    void writeNameKey(NameKeyType key);

protected:
    OutputStream *m_pOut;
    _iobuf *m_tmp_file;
    DataChunkTableOfContents m_contents;
    OutputChunk *m_chunkStack;
};

#endif
