// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva0039215F@Rva0039205C@@QAEXIABVAsciiString@@@Z 55B @0x0039215F: AsciiString setter stride 0x1C at +0x14 via StringBase set. Layout from Rva0039205CArray rows plus string at +0x14. Evidence: init pin at 0x00392092 plus GlobalData count plus callers at 0x00393486 0x00393CE7.
#include "ascii_string.h"

extern class GlobalData *TheWritableGlobalData;

class GlobalData
{
public:
	char m_pad[0xA94];
	unsigned int m_count;
};

class Rva00392092Target
{
public:
	void rva00392092();
};

class Rva004D9A3C
{
public:
	char m_pad00[0x0C];
	float m_float0C;
	unsigned char m_byte10;
	char m_pad11[0x03];
	AsciiString m_str14;
	int m_int18;
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *value);
};

extern class Rva002D06CA *g_009FF000;

class Rva0039205C
{
public:
	void rva0039215F(unsigned int index, const AsciiString &value);
	void *rva00392CC5(unsigned int index);
private:
	int m_count00;
	int m_pad04;
	Rva004D9A3C *m_array08;
};

void Rva0039205C::rva0039215F(unsigned int index, const AsciiString &value)
{
	if (m_array08 == 0)
		((Rva00392092Target *)this)->rva00392092();
	if (index >= TheWritableGlobalData->m_count)
		return;
	((StringBase<char> *)&m_array08[index].m_str14)->set(*(const StringBase<char> *)&value);
}

void *Rva0039205C::rva00392CC5(unsigned int index)
{
	if (m_array08 == 0)
		((Rva00392092Target *)this)->rva00392092();
	if (index < (unsigned int)m_count00)
		return g_009FF000->rva002D06CA(&m_array08[index].m_str14);
	return 0;
}
