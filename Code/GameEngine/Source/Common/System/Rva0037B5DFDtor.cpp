// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1Rva0037B5DF@@QAE@XZ retail 0x0037B5DF 105B.
// Non-virtual dtor destroying five StringBase<unsigned short> at +0x58 +0x48 +0x44 +0x30 +0x28
// and one StringBase<char> at +0x20 via rowed releaseBuffer 0x00036E70 and 0x00036410
// in reverse order with __EH_prolog frame 0x00629188 and states 4-3-2-1-0 then -1.
// Evidence: callees rowed 0x00036E70 0x00036410; callers 0x0037D1C2 0x0037D3A5 0x00436DC4;
// neighbours RecorderIsMultiplayer 0x0037B18C and GetLastReplayDisplayName 0x0037BA62 same flags.
#include "ascii_string.h"

#include "unicode_string.h"

class Rva0037B5DF
{
public:
	~Rva0037B5DF();
private:
	char m_pad00[0x20];
	AsciiString m_20; // +0x20
	char m_pad24[0x28 - 0x24];
	UnicodeString m_28; // +0x28
	char m_pad2C[0x30 - 0x2C];
	UnicodeString m_30; // +0x30
	char m_pad34[0x44 - 0x34];
	UnicodeString m_44; // +0x44
	UnicodeString m_48; // +0x48
	char m_pad4C[0x58 - 0x4C];
	UnicodeString m_58; // +0x58
};

Rva0037B5DF::~Rva0037B5DF()
{
}
