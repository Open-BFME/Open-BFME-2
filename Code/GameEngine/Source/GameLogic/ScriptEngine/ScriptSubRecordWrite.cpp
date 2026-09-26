// cl: /O1 /G7 /DNDEBUG /MD
//
// ?WriteScriptSubRecord_Rva003B24F2@@YAXAAVDataChunkOutput@@PBUScriptSubRecord@@@Z,
// retail 0x003B24F2, 66 bytes. Dedicated TU.
//
// Mid-record writer for the script chunk (called from WriteScriptDataChunk
// 0x3B5994 with the writer and &script+0x10): two flag bytes, an int slot,
// a third flag byte, then the trailing AsciiString at +0x0C. All three
// callees are matched rows (writeByte 0x306D17, writeInt folded with
// writeReal at 0x306CFF, writeAsciiString 0x307033), so no pins are needed.
// Identity beyond the address is unproven, hence the Rva name
// (ReadEmailList_Rva005CAEA3 precedent).

typedef int Int;
typedef unsigned char Byte;

// Minimal 4-byte AsciiString view (member use needs a complete type; this TU
// never constructs, copies or destroys one, so no ctor/dtor is declared).
class AsciiString
{
public:
	void *m_data;
};

class DataChunkOutput
{
public:
	void writeByte(Byte value);
	void writeInt(Int value);
	void writeAsciiString(const AsciiString &str);
};

struct ScriptSubRecord
{
	Byte m_flagA; // +0x00
	Byte m_flagB; // +0x01
	Int m_value; // +0x04
	Byte m_flagC; // +0x08
	AsciiString m_name; // +0x0C
};

// ?WriteScriptSubRecord_Rva003B24F2@@YAXAAVDataChunkOutput@@PBUScriptSubRecord@@@Z
void WriteScriptSubRecord_Rva003B24F2(DataChunkOutput &chunkWriter, const ScriptSubRecord *record)
{
	chunkWriter.writeByte(record->m_flagA);
	chunkWriter.writeByte(record->m_flagB);
	chunkWriter.writeInt(record->m_value);
	chunkWriter.writeByte(record->m_flagC);
	chunkWriter.writeAsciiString(record->m_name);
}
