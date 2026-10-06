// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva0057FA1C@AptMpClans@@QAEXVUnicodeString@@@Z @0x0057FA1C 148B: clan setter with toUpper trim length check via Ascii conversion plus prefs write.
// Evidence: chain from just-landed clan add 0x005CAE04; prefs at +0x58 clan at +0xAC same TU; wide toUpper 0x375E0 trim 0x37F70 AsciiFromUnicode 0x38250 write vslot 3 clan text 0x57F7AC pin; callers 0x57FCD8 0x57FD34.
#include "unicode_string.h"
#include "ascii_string.h"

class GameWindow;

class GameSpyLoginPreferences
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual bool write();

	bool rva005CAE04(const AsciiString &clan, const AsciiString &member);
};

class AptMpClans
{
public:
	void rva0057F7AC(const UnicodeString &name);
	void rva0057FA1C(UnicodeString name);

private:
	unsigned char m_pad000[0x58];
	GameSpyLoginPreferences m_prefs;
	unsigned char m_pad05c[0xA0 - 0x5C];
	GameWindow *m_clanName;
	GameWindow *m_clanPlayers;
	unsigned char m_pad0a8[0xAC - 0xA8];
	AsciiString m_clan;
};

void AptMpClans::rva0057FA1C(UnicodeString name)
{
	struct WideHeader
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
	};
	name.toUpper();
	name.trim();
	void *m_data = *(void **)&name;
	if (m_data && ((const WideHeader *)m_data)->length)
	{
		AsciiString ascii(name);
		if (m_prefs.rva005CAE04(m_clan, ascii))
			m_prefs.write();
	}
	rva0057F7AC(name);
}
