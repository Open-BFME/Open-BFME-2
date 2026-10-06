// cl: /DNDEBUG /MD
// ?rva006D4190@EAStringC@@QAEXH@Z @0x006D4190 (225B). EAStringC single-codepoint
// UTF-8 encode worker: writes the 1/2/3/4-byte UTF-8 form of the int code
// point into the reserved internal buffer (+8), terminates, installs size via
// rowed SetSize 0x006D3BC0 and clears the hash word (+6). Donor is open-bfme-1
// Code/Libraries/Source/EA/Apt/AptString/Rva0089DDC0Utf8Encode.cpp
// (encodeUtf8Rva0089DDC0, same 0x80/0x800/0x10000 thresholds and byte
// patterns); retail adds terminator plus SetSize plus hash-zero stores.
// Caller at 0x006D6223 (Assign codepoint: FreeData then ChangeBuffer then
// this) plus length worker utf8EncodedLength 0x006D3DB0 rowed in the prior
// commit; neighbours SetSize 0x006D3BC0 and ChangeBuffer 0x006D4AA0 share
// the /O2 /DNDEBUG /MD flags. Honest address name; class from StringDataC
// layout plus SetSize row, void(int) from ret-4 plus int arg.
class EAStringC
{
public:
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
	};

private:
	StringDataC *m_pData;

	char *GetInternalBuffer() const
	{
		return reinterpret_cast<char *>(m_pData) + sizeof(StringDataC);
	}

public:
	void SetSize(int size);

	void rva006D4190(int c);
};

void EAStringC::rva006D4190(int c)
{
	char *dst = GetInternalBuffer();
	if (c < 0x80) {
		dst[0] = (char)c;
		dst[1] = 0;
		SetSize(1);
		m_pData->m_uHash = 0;
		return;
	}
	if (c < 0x800) {
		dst[0] = (char)(0xC0 | (c >> 6));
		dst[1] = (char)(0x80 | (c & 0x3F));
		dst[2] = 0;
		SetSize(2);
		m_pData->m_uHash = 0;
		return;
	}
	if (c < 0x10000) {
		dst[0] = (char)(0xE0 | (c >> 12));
		dst[1] = (char)(0x80 | ((c >> 6) & 0x3F));
		dst[2] = (char)(0x80 | (c & 0x3F));
		dst[3] = 0;
		SetSize(3);
		m_pData->m_uHash = 0;
		return;
	}
	dst[0] = (char)(0xF0 | (c >> 18));
	dst[1] = (char)(0x80 | ((c >> 12) & 0x3F));
	dst[2] = (char)(0x80 | ((c >> 6) & 0x3F));
	dst[3] = (char)(0x80 | (c & 0x3F));
	dst[4] = 0;
	SetSize(4);
	m_pData->m_uHash = 0;
}
