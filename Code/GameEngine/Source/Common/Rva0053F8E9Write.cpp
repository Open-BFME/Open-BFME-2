// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0053F8E9@Rva0053FB33@@UAEXPAVDataChunkOutput@@@Z @ 0x0053F8E9 44B: slot 5.
// Write AsciiString at +0x18 via rowed writeAsciiString 0x00307033 then floats
// at +0x1C/+0x20 via rowed writeReal 0x00306CFF. Evidence: vtable 0x008694DC
// slot 5 plus rowed DataChunkOutput writers.
class AsciiString;

class DataChunkOutput
{
public:
	void writeAsciiString(const AsciiString &s);
	void writeInt(int value);
};

#include "ascii_string.h"


class Rva0053FB33
{
public:
	virtual ~Rva0053FB33();
	virtual void rva0053F8E9(DataChunkOutput *out);

private:
	char m_pad04[0x18 - 0x04];
	StringBase<char> m_str18;
	int m_1C;
	int m_20;
};

void Rva0053FB33::rva0053F8E9(DataChunkOutput *out)
{
	out->writeAsciiString(*(const AsciiString *)&m_str18);
	out->writeInt(m_1C);
	out->writeInt(m_20);
}
