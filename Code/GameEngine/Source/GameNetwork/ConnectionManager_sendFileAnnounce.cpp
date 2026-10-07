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

class File
{
public:
	virtual ~File();
	virtual void slot04();
	virtual void close();						// +0x08
	virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18();
	virtual void slot1C(); virtual void slot20(); virtual void slot24();
	virtual void slot28();
	virtual Int size();							// +0x2C
};

class FileSystem
{
public:
	File *openFile(const char *filename, Int access = 0, Int bufferSize = 0);
};

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

class NetCommandMsg
{
public:
	void detach();
	void setPlayerID(UnsignedInt playerID) { m_playerID = playerID; }
	void setID(UnsignedShort id) { m_id = id; }
	NetCommandType getNetCommandType() const { return m_commandType; }

protected:
	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	Int m_referenceCount;
};

// ZH's setRealFilename(AsciiString).
class Rva004D632D
{
public:
	void rva004D6250(AsciiString filename);
};

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

struct BfmeNetAddress
{
	BfmeNetAddress(UnsignedInt ip, UnsignedShort port) : m_ip(ip), m_port(port) {}

	UnsignedInt m_ip;
	UnsignedShort m_port;
};

enum ChatType
{
	LANCHAT_NORMAL = 0,
	LANCHAT_EMOTE,
	LANCHAT_SYSTEM = 3
};

#define LAN_SLOT(n) virtual void slot##n();

class LANAPI
{
public:
	LAN_SLOT(00) LAN_SLOT(01) LAN_SLOT(02) LAN_SLOT(03) LAN_SLOT(04)
	LAN_SLOT(05) LAN_SLOT(06) LAN_SLOT(07) LAN_SLOT(08) LAN_SLOT(09)
	LAN_SLOT(10) LAN_SLOT(11) LAN_SLOT(12) LAN_SLOT(13) LAN_SLOT(14)
	LAN_SLOT(15) LAN_SLOT(16) LAN_SLOT(17) LAN_SLOT(18) LAN_SLOT(19)
	LAN_SLOT(20) LAN_SLOT(21) LAN_SLOT(22) LAN_SLOT(23) LAN_SLOT(24)
	LAN_SLOT(25) LAN_SLOT(26) LAN_SLOT(27) LAN_SLOT(28) LAN_SLOT(29)
	LAN_SLOT(30) LAN_SLOT(31) LAN_SLOT(32) LAN_SLOT(33) LAN_SLOT(34)
	LAN_SLOT(35) LAN_SLOT(36) LAN_SLOT(37) LAN_SLOT(38) LAN_SLOT(39)
	virtual void OnChat(const UnicodeString &player, const BfmeNetAddress *ip,
		const UnicodeString &message, ChatType format);	// +0xA0
};

#undef LAN_SLOT

extern FileSystem *TheFileSystem;
extern LANAPI *TheLAN;

Bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

class ConnectionManager
{
public:
	UnsignedShort sendFileAnnounce(AsciiString path, UnsignedByte playerMask);
	void sendLocalCommand(NetCommandMsg *msg, UnsignedByte relay);

private:
	void processFileAnnounce(NetFileAnnounceCommandMsg *msg);

	char m_pad00000[0x12028];
	Int m_localSlot;
};

UnsignedShort ConnectionManager::sendFileAnnounce(AsciiString path, UnsignedByte playerMask)
{
	File *theFile = TheFileSystem->openFile(path.str(), 0, 0);
	if (!theFile || !theFile->size())
	{
		UnicodeString log;
		log.format(L"Not sending file '%hs' to %X\n", path.str(), playerMask);
		if (TheLAN)
			TheLAN->OnChat(UnicodeString(L"sendFile"), &BfmeNetAddress(0, 0), log, LANCHAT_SYSTEM);
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
