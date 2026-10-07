// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva0037B7C7@Rva0037B7C7@@QAEXXZ retail 0x0037B7C7 47B.
// Fread-into-+0xE78 helper: fread 4x1 from FILE at +0x10 into int at +0xE78; on success return else set -1 and tail-jmp rowed 0x0037B3F7.
// Evidence: IAT fread plus rowed 0x0037B3F7 callee; callers 0x0037BC98 0x0037D337; neighbours Rva0037B5DFDtor and Rva0037B9D4Get same flags.
#include "unicode_string.h"

struct FILE;
extern "C" __declspec(dllimport) unsigned int __cdecl fread(void *buf, unsigned int size, unsigned int count, FILE *stream);

class Rva0037B3F7
{
public:
	void rva0037B3F7();
};

class Rva0037B7C7
{
public:
	void rva0037B7C7();
	void rva0037BC65();
private:
	char m_pad00[0x10]; // +0x00..+0x0F
	FILE *m_file10; // +0x10
	UnicodeString m_str14; // +0x14
	char m_pad18[0xE70 - 0x18]; // +0x18..+0xE6F
	unsigned char m_flagE70; // +0xE70
	char m_padE71[0xE78 - 0xE71]; // +0xE71..+0xE77
	int m_valE78; // +0xE78
};

void Rva0037B7C7::rva0037B7C7()
{
	if (fread(&m_valE78, 4, 1, m_file10) == 1)
		return;
	m_valE78 = -1;
	return ((Rva0037B3F7 *)this)->rva0037B3F7();
}

// Retail extent 0x0037BC65..0x0037BCA8, 67 bytes, thiscall RET 0.
// This uses the same +0xE70/+0xE78 state as the read-next-frame helper above.
// It clears pending commands, consumes records for the selected frame, then
// advances the file's frame value. The original method name is unknown.
// TheGameLogic's +0x40 value and all three calls are read from this body;
// /arch:SSE enables the retail conditional move when the mode byte is set.
class GameLogic;
extern GameLogic *TheGameLogic;
struct RecorderFrameView { char opaque00[0x40]; int frame40; };
class Rva0037B146 { public: void rva0037B146(); };
class Rva0037B7F6 { public: void rva0037B7F6(); };
void Rva0037B7C7::rva0037BC65()
{
    int frame = reinterpret_cast<const RecorderFrameView *>(TheGameLogic)->frame40;
    reinterpret_cast<Rva0037B146 *>(this)->rva0037B146();
    if (m_valE78 == -1) return;
    if (m_flagE70) frame = m_valE78;
    while (m_valE78 == frame) {
        reinterpret_cast<Rva0037B7F6 *>(this)->rva0037B7F6();
        rva0037B7C7();
    }
}
