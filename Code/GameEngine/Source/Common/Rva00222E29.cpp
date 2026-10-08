// ?LoadLevel@AptPlayer@@QAE_NI@Z
// partial score=0.95 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?LoadLevel@AptPlayer@@QAE_NH@Z @0x00222E29 225 bytes.
// Target evidence: rejects indices >= 14, addresses 0x28-byte records from
// this+0xCC, requires flag bit 0 and rejects bit 1. It strips the extension,
// formats a /_level%d suffix, calls the rowed path helper and sets bit 1.
// The record owner name is unproven; this class is address-derived.

#include "ascii_string.h"

void Rva006CC600(const char *path, char *suffix);

class AptPlayer
{
public:
	bool LoadLevel(unsigned int index);

private:
	char m_unknown[0xCC];
	struct Record
	{
		AsciiString m_path;
		char m_unknown[0x20];
		unsigned char m_flags;
		char m_tail[3];
	} m_records[14];
};

bool AptPlayer::LoadLevel(unsigned int index)
{
	if (index >= 14)
		return false;

	Record *record = &m_records[index];
	if (!(record->m_flags & 1))
		return false;
	if (record->m_flags & 2)
		return false;

	AsciiString path(record->m_path);
	const char *extension = path.find('.');
	if (extension)
	{
		for (int count = (int)strlen(extension); count; --count)
			path.removeLastChar();
	}

	AsciiString suffix;
	suffix.format("/_level%d", index);
	Rva006CC600(path.str(), (char *)suffix.str());
	record->m_flags = (record->m_flags & 0xFE) | 2;
	return true;
}
