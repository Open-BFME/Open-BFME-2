// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0037B287@Rva0037B287@@QAEXVUnicodeString@@H@Z retail 0x0037B287 159B.
// File-flag helper: if FILE at +0x10 is null release by-value wide arg and return;
// else if int arg in [0,8) ftell then fseek to arg+29 SEEK_SET then fwrite one 0x01 byte
// then fseek back to ftell pos; always release by-value arg via rowed releaseBuffer 0x36E70.
// Evidence: callees rowed 0x36E70 plus IAT ftell fseek fwrite; caller 0x004D422C;
// neighbours RecorderIsMultiplayer 0x0037B18C and Rva0037B5DF dtor 0x0037B5DF same flags.
typedef unsigned short WideChar;

#include "unicode_string.h"


struct FILE;
extern "C" __declspec(dllimport) long __cdecl ftell(FILE *stream);
extern "C" __declspec(dllimport) int __cdecl fseek(FILE *stream, long offset, int origin);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *buf, unsigned int size, unsigned int count, FILE *stream);

class Rva0037B287
{
public:
	void rva0037B287(UnicodeString arg, int slot);
private:
	char m_pad00[0x10];
	FILE *m_file10; // +0x10
};

void Rva0037B287::rva0037B287(UnicodeString arg, int slot)
{
	if (m_file10 == 0)
		return;
	if (slot < 0 || slot >= 8)
		return;
	long pos = ftell(m_file10);
	if (fseek(m_file10, (long)(slot + 0x1D), 0) == 0) {
		unsigned char one = 1;
		fwrite(&one, 1, 1, m_file10);
	}
	fseek(m_file10, pos, 0);
}
