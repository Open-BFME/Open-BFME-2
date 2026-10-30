// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
//
// ??1Rva0037BBED@@UAE@XZ retail 0x0037BBED 120B virtual dtor with vtable
// 0x00818828. Body clears TheGameInfo when it points at member m_24 closes
// FILE at +0x10 via fclose then destroys Rva0037BB53 member at +0x24 and two
// UnicodeStrings at +0x20/+0x14 (inlined releaseBuffer) then
// SubsystemInterface base. Identity from vtable store member call to just
// landed 0x0037BB53 TheGameInfo global fclose IAT and deleting dtor caller
// 0x0037BD48.
#include "unicode_string.h"

class GameInfo;
extern GameInfo *TheGameInfo;
struct _iobuf;
typedef struct _iobuf FILE;
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *fp);

class Rva0037BB53
{
public:
	virtual ~Rva0037BB53();
	char m_pad[0xE3C - 4];
};

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class AsciiString;
class Rva0037B5DF;
class Rva0037D097CRCView;
class Rva0037BBED : public SubsystemInterface
{
public:
	Rva0037BBED();
	UnicodeString rva0037BCA8();
	AsciiString rva0037B70A();
	bool rva0037CBB6(Rva0037B5DF &header);
	bool rva0037D0EF(UnicodeString filename);
	void rva0037D0A7(unsigned int crc, int player, bool fromPlayback, unsigned int frame);
	virtual ~Rva0037BBED();
	virtual void init();
	Rva0037D097CRCView *m_0c; // +0x0C
	FILE *m_file; // +0x10
	UnicodeString m_14; // +0x14
	int m_18; // +0x18
	int m_1c; // +0x1C
	UnicodeString m_20; // +0x20
	Rva0037BB53 m_gameInfo; // +0x24
	int m_crcInterval; // +0xE60
	int m_mode; // +0xE64
	int m_numPlayers; // +0xE68
	int m_localIndex; // +0xE6C
	unsigned char m_e70; // +0xE70
	char m_padE71[0x3];
	int m_e74; // +0xE74
	int m_frameE78; // +0xE78
};

Rva0037BBED::~Rva0037BBED()
{
	if (TheGameInfo == (GameInfo *)&m_gameInfo)
		TheGameInfo = 0;
	if (m_file)
		fclose(m_file);
}
