// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ConnectionManager::sendFileAnnounce, retail 0x004D2D6A, 410 bytes.
//
// Reference: Zero Hour GameEngine/Source/GameNetwork/ConnectionManager.cpp
// sendFileAnnounce: a missing or empty file is reported to the LAN lobby as a
// system chat line and yields file ID 0; otherwise the file is closed and a
// file announce command (local slot, a command ID when its type needs one, the
// path, the recipient mask and a fresh file ID) is set up locally through
// processFileAnnounce 0x004D2C8E and sent to every other player; the file ID is
// returned.
// BFME 2 differences read from this body: the file comes from TheFileSystem's
// openFile(name, 0, 0) (File::close and size are its +0x08 and +0x2C
// virtuals); the command is the 0x24-byte type built by 0x004D62A9, its path
// set through 0x004D6250, the file ID word at +0x20 through 0x004D5978 and the
// mask byte at +0x22 through 0x004D5984; LANAPI::OnChat (+0xA0) takes the
// sender's address record, here a zeroed one, as in sendFile 0x004D1927.

#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#include "../../Include/Common/File.h"

#include "../../Include/Common/FileSystem.h"

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

#include "../../Include/GameNetwork/NetCommandMsg.h"

inline void NetCommandMsg::setID(unsigned short id)
{
	m_id = id;
}

// ZH's setRealFilename(AsciiString).
#include "../../Include/GameNetwork/Rva004D632D.h"

// Ledger names of the folded field setters.
class Rva004D5978WordSlot
{
public:
	void set(UnsignedShort value);		// word at +0x20
};

class Rva004D5984ByteSlot
{
public:
	void set(UnsignedByte value);		// byte at +0x22
};

class NetFileAnnounceCommandMsg : public NetCommandMsg
{
public:
	void setFileID(UnsignedShort fileID) { ((Rva004D5978WordSlot *)this)->set(fileID); }
	void setPlayerMask(UnsignedByte playerMask) { ((Rva004D5984ByteSlot *)this)->set(playerMask); }

private:
	char m_pad1C[0x24 - 0x1c];
};

// Its constructor, held in the ledger under its address name.
class Rva004D62A9 : public NetFileAnnounceCommandMsg
{
public:
	Rva004D62A9();
};

#include "../../Include/GameNetwork/BfmeNetAddress.h"
#include "../../Include/GameNetwork/LANAPI.h"

// The canonical BfmeNetAddress has no constructor; retail zeroes the
// record OnChat receives in place, as a temporary built between the pushes.
struct ZeroNetAddress : public BfmeNetAddress
{
	ZeroNetAddress() { ip = 0; port = 0; }
};

extern FileSystem *TheFileSystem;
extern LANAPI *TheLAN;

Bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

#include "../../Include/GameNetwork/ConnectionManager.h"

UnsignedShort ConnectionManager::sendFileAnnounce(AsciiString path, UnsignedByte playerMask)
{
	File *theFile = TheFileSystem->openFile(path.str(), 0, 0);
	if (!theFile || !theFile->size())
	{
		UnicodeString log;
		log.format(L"Not sending file '%hs' to %X\n", path.str(), playerMask);
		if (TheLAN)
			TheLAN->OnChat(UnicodeString(L"sendFile"), &ZeroNetAddress(), log, LANAPI::LANCHAT_SYSTEM);
		return 0;
	}

	theFile->close();

	Int announceMask = 0xff ^ (1 << m_localSlot);
	NetFileAnnounceCommandMsg *announceMsg = new Rva004D62A9;
	announceMsg->setPlayerID(m_localSlot);
	if (DoesCommandRequireACommandID(announceMsg->getNetCommandType()) == true)
	{
		announceMsg->setID(GenerateNextCommandID());
	}
	((Rva004D632D *)announceMsg)->rva004D6250(path);
	announceMsg->setPlayerMask(playerMask);
	UnsignedShort fileID = GenerateNextCommandID();
	announceMsg->setFileID(fileID);

	processFileAnnounce(announceMsg);

	sendLocalCommand(announceMsg, announceMask);
	announceMsg->detach();

	return fileID;
}
