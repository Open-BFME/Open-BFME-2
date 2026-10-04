// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
//
// ??1Rva0037BBED@@UAE@XZ retail 0x0037BBED 120B virtual dtor with vtable
// 0x00818828. Body clears TheGameInfo when it points at member m_24 closes
// FILE at +0x10 via fclose then destroys Rva0037BB53 member at +0x24 and two
// UnicodeStrings at +0x20/+0x14 (inlined releaseBuffer) then
// GameEngineDeletingBase base. Identity from vtable store member call to just
// landed 0x0037BB53 TheGameInfo global fclose IAT and deleting dtor caller
// 0x0037BD48.
#include "unicode_string.h"

class GameInfo;
extern GameInfo *TheGameInfo;
extern "C" __declspec(dllimport) int __cdecl fclose(void *fp);

class Rva0037BB53
{
public:
	virtual ~Rva0037BB53();
	char m_pad[0xE3C - 4];
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
	int m_pad04;
	int m_pad08;
};

class Rva0037BBED : public GameEngineDeletingBase
{
public:
	virtual ~Rva0037BBED();
private:
	int m_0c;
	void *m_10;
	UnicodeString m_14;
	int m_18;
	int m_1c;
	UnicodeString m_20;
	Rva0037BB53 m_24;
};

Rva0037BBED::~Rva0037BBED()
{
	if (TheGameInfo == (GameInfo *)&m_24)
		TheGameInfo = 0;
	if (m_10)
		fclose(m_10);
}
