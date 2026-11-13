// ?rva004D0E93@Rva004D0E93@@QAEXHHABVUnicodeString@@@Z, retail
// 0x004D0E93 (148B RET0xC). Unnamed (no WB name, no direct caller: reached
// through a pointer); all callees are rowed and the field writes are native.
// Builds a 0x28-byte type-30 net command message (rowed ctor 0x004D674D),
// stores the int args at +0x1C/+0x20, copies the UnicodeString argument
// through Rva004D05D7::rva004D05D7 (0x004D05D7, StringBase<wchar_t> copy
// ctor 0x00037050), copies the owner's +0x12028 word to +0xC, conditionally
// stamps the generated command id at +0x10 (DoesCommandRequireACommandID
// 0x005811B5, GenerateNextCommandID 0x005811A8), sends it via
// ConnectionManager::sendLocalCommand (0x004CFF21, 0xFF) and detaches
// (NetCommandMsg::detach 0x004D55BC). Address-derived identity.
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Native 0x004D0E93..0x004D0F26 (148B, RET0xC). Builds a type-30 net command
// message (rowed ctor 0x004D674D), stores the two int args at +0x1C/+0x20,
// copies the UnicodeString arg in (rowed StringBase<wchar_t> copy ctor
// 0x00037050) through Rva004D05D7::rva004D05D7 (0x004D05D7), copies the
// owner's +0x12028 word to +0xC, conditionally stamps the generated command id
// at +0x10 (DoesCommandRequireACommandID 0x005811B5, GenerateNextCommandID
// 0x005811A8), sends it (ConnectionManager::sendLocalCommand 0x004CFF21,
// 0xFF) and detaches (NetCommandMsg::detach 0x004D55BC).
#include "unicode_string.h"

#include "../../Include/Common/Rva004D67D0.h"

class Rva004D05D7
{
public:
	void rva004D05D7(UnicodeString s);
};

#include "../../Include/GameNetwork/NetCommandMsg.h"

enum NetCommandType { NETCOMMAND_TYPE_DUMMY };
bool DoesCommandRequireACommandID(NetCommandType type);
unsigned short GenerateNextCommandID();

#include "../../Include/GameNetwork/ConnectionManager.h"

class Rva004D0E93
{
public:
	void rva004D0E93(int a, int b, const UnicodeString &s);
private:
	char m_pad[0x12028];
	int m_12028;
};

void Rva004D0E93::rva004D0E93(int a, int b, const UnicodeString &unicodeString)
{
	NetCommandMsg *msg = (NetCommandMsg *)new Rva004D67D0();
	*(int *)((char *)msg + 0x1C) = a;
	*(int *)((char *)msg + 0x20) = b;
	((Rva004D05D7 *)msg)->rva004D05D7(unicodeString);
	*(int *)((char *)msg + 0xC) = m_12028;
	if (DoesCommandRequireACommandID((NetCommandType)*(int *)((char *)msg + 0x14)))
		*(unsigned short *)((char *)msg + 0x10) = GenerateNextCommandID();
	((ConnectionManager *)this)->sendLocalCommand(msg, 0xFF);
	msg->detach();
}
