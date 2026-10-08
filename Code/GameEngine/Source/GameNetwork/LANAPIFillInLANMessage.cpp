// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?fillInLANMessage@LANAPI@@QAEXPAVLANMessage@@@Z @0x0044A966 128B slot 57.
// Retail copies m_name via wcsncpy(10) to message+4 then nulls +0x18, copies
// m_userName/m_hostName via strncpy(1) to +0x1a/+0x1c then nulls +0x1b/+0x1d.
// String data uses +8-or-default (Unicode 0xBBB5C4 Ascii 0xBBAC1C). Evidence:
// vslot lane slot 57 of 0x0083E680; class/offsets copied from
// LANAPICompleteDestructor TU; str pattern from LANAPIRequestAccept TU.
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef unsigned char UnsignedByte;
typedef bool Bool;

extern "C" __declspec(dllimport) WideChar *__cdecl wcsncpy(WideChar *, const WideChar *, unsigned int);
extern "C" __declspec(dllimport) char *__cdecl strncpy(char *destination, const char *source, unsigned int count);

template <typename T> class StringBase;
class UnicodeStringData
{
public:
	UnsignedByte m_prefix[8];
	WideChar m_data[1];
};

class AsciiStringData
{
public:
	UnsignedByte m_prefix[8];
	char m_data[1];
};

#include "ascii_string.h"

#include "unicode_string.h"

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface(void);

private:
	UnsignedByte m_baseFields[8];
};

class LANAPIInterface : public SubsystemInterface
{
public:
	virtual ~LANAPIInterface(void) {}
};

#include "../../Include/GameNetwork/Transport.h"

struct BfmeNetAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

struct LANMessage
{
	UnsignedInt type;
	UnsignedByte payload[0x1D8 - sizeof(UnsignedInt)];
};

class LANGameInfo;
class LANPlayer;

class LANAPI : public LANAPIInterface
{
public:
	virtual ~LANAPI(void);
	virtual void reset(void);

	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot41(void) = 0;
	virtual void slot42(void) = 0;
	virtual void slot43(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot45(void) = 0;
	virtual void slot46(void) = 0;
	virtual void slot47(void) = 0;
	virtual void slot48(void) = 0;
	virtual void slot49(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot51(void) = 0;
	virtual void slot52(void) = 0;
	virtual void slot53(void) = 0;
	virtual void slot54(void) = 0;
	virtual void slot55(void) = 0;
	virtual void slot56(void) = 0;
	virtual void fillInLANMessage(LANMessage *message);

protected:
	LANPlayer *m_lobbyPlayers;
	LANGameInfo *m_games;
	UnicodeString m_name;
	AsciiString m_userName;
	AsciiString m_hostName;
};

void LANAPI::fillInLANMessage(LANMessage *message)
{
	if (!message)
		return;
	wcsncpy((WideChar *)(message->payload + 0), m_name.str(), 10);
	*(WideChar *)(message->payload + 0x14) = 0;
	strncpy((char *)(message->payload + 0x16), m_userName.str(), 1);
	message->payload[0x17] = 0;
	strncpy((char *)(message->payload + 0x18), m_hostName.str(), 1);
	message->payload[0x19] = 0;
}
