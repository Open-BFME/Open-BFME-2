// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0037B3F7@Rva0037B3F7@@QAEXXZ retail 0x0037B3F7 54B.
// Close-plus-notify: if FILE at +0x10 is set fclose and null it then clear UnicodeString at +0x14 via rowed releaseBuffer 0x36E70; if byte at +0xE70 is set return else MessageStreamSubsystem->v18(0x1D).
// Evidence: callees rowed 0x36E70 plus IAT fclose; global MessageStreamSubsystem 0x00A00950 in use; caller jmp 0x0037B7EE; neighbours Rva0037B3D1 and Rva0037B5A0 same flags.
#include "unicode_string.h"

struct FILE;
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *stream);

class GameMessage;
class MessageStream
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual GameMessage *v18(int type);
};
extern class MessageStream *TheMessageStream;

class Rva0037B3F7
{
public:
	void rva0037B3F7();
private:
	char m_pad00[0x10]; // +0x00..+0x0F
	FILE *m_file10; // +0x10
	UnicodeString m_str14; // +0x14
	char m_pad18[0xE70 - 0x18]; // +0x18..+0xE6F
	unsigned char m_flagE70; // +0xE70
};

void Rva0037B3F7::rva0037B3F7()
{
	if (m_file10 != 0) {
		fclose(m_file10);
		m_file10 = 0;
	}
	m_str14.clear();
	if (m_flagE70 != 0)
		return;
	TheMessageStream->v18(0x1D);
}
