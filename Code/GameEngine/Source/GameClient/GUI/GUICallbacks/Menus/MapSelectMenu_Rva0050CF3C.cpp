// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva0050CF3CStartHeadlessLanGame@@YAXXZ, retail 0x0050CF3C..0x0050D099
// (349 bytes). MapSelectMenu.cpp's local LAN game host: its sole caller is
// doGameStart (0x0050D099, call at 0x0050D0D0) when the headless client
// count at 0x00E045C8 is non-zero. It creates or resets TheLAN, binds it to
// 127.0.0.1, stores the pending map in the LAN preferences and writes them,
// trims the preferred user name to ten characters, sets it, requests the
// locations and an unnamed game, then starts that many headless clients.
//
// Donor: Open-BFME-1 GameEngine/Source/Common/BfmeAltAAV.cpp (bfmeAltAAV,
// same sequence; BFME 1 trims to twelve characters and sets the map key by
// subscript). Target facts: LANAPI is 0x60 bytes with its ctor pinned at
// 0x00449AB8; vslots reset 9 / init 1 / SetLocalIP 52 / RequestSetName 29 /
// RequestLocations 15 / RequestGameCreate 27 come from the call sites; the
// map setter 0x0044DD83 / write 0x0044D50D / user name 0x0044D330 and the
// LANPreferences ctor 0x0044D2F5 are rowed in GameModePreferences.cpp; the
// pending map is the AsciiString at TheWritableGlobalData+0xAC0.

#include "ascii_string.h"
#include "unicode_string.h"

typedef bool Bool;
typedef int Int;

AsciiString AsciiStringToQuotedPrintable(AsciiString original);

class LANAPI
{
public:
	LANAPI();
	virtual void v00();
	virtual void init(void); // slot 1
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void reset(void); // slot 9
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void RequestLocations(void); // slot 15
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void RequestGameCreate(UnicodeString gameName, Bool isDirectConnect); // slot 27
	virtual void v28();
	virtual void RequestSetName(UnicodeString newName); // slot 29
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void SetLocalIP(AsciiString localIP); // slot 52

	unsigned char m_unreconstructed[0x60 - 4];
};

extern LANAPI *TheLAN;

class GameModePreferences
{
public:
	virtual ~GameModePreferences();
	virtual Bool write(void);

	UnicodeString rva0044D330(void);
	void rva0044DD83(AsciiString val);

	unsigned char m_pad04[0x1C - 0x04];
};

class LANPreferences : public GameModePreferences
{
public:
	LANPreferences(Int mode);
	virtual ~LANPreferences();
};

class GlobalData
{
public:
	unsigned char m_pad000[0xAC0];
	AsciiString m_pendingFile; // +0xAC0
};

extern GlobalData *TheWritableGlobalData;

class GameEngine
{
public:
	void startHeadlessClients(Int numClients);
};

extern GameEngine *TheGameEngine;

// MapSelectMenu's headless client count (zero-filled .bss at 0x00E045C8).
extern Int g_Va00E045C8;

void Rva0050CF3CStartHeadlessLanGame(void)
{
	if (TheLAN == 0)
		TheLAN = new LANAPI;
	else
		TheLAN->reset();

	TheLAN->init();
	TheLAN->SetLocalIP(AsciiString("127.0.0.1"));

	LANPreferences pref(0);
	pref.rva0044DD83(AsciiStringToQuotedPrintable(TheWritableGlobalData->m_pendingFile));
	pref.write();

	UnicodeString userName = pref.rva0044D330();
	while (userName.getLength() > 10)
		userName.removeLastChar();

	TheLAN->RequestSetName(userName);
	TheLAN->RequestLocations();
	TheLAN->RequestGameCreate(UnicodeString(L""), false);
	TheGameEngine->startHeadlessClients(g_Va00E045C8);
}
