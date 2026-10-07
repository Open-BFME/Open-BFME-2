// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ConnectionManager::sendFile, retail 0x004D1927, 372 bytes.
//
// Reference: Zero Hour GameEngine/Source/GameNetwork/ConnectionManager.cpp
// sendFile without the Targa compression block: a missing or empty file is
// reported to the LAN lobby as a system chat line; otherwise the file is read
// whole into a file command (local slot, the caller's command ID, the path and
// the data), the buffer freed and the command sent to the player mask.
// Name: the pinned callee of Network::sendFile 0x0025E327.
// BFME 2 differences read from this body: the file comes from TheFileSystem's
// openFile(name, 0, 0) (File::size and readEntireAndClose are its +0x2C and
// +0x34 virtuals); the command is the 0x28-byte type built by 0x004D61BB with
// the path set through 0x004D6250 and the data through
// NetFileCommandMsg::setFileData 0x004D594C; LANAPI::OnChat (+0xA0) takes the
// sender's address record, here a zeroed one.

#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

class File
{
public:
	virtual ~File();
	virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18();
	virtual void slot1C(); virtual void slot20(); virtual void slot24();
	virtual void slot28();
	virtual Int size();							// +0x2C
	virtual Int position();						// +0x30
	virtual char *readEntireAndClose();			// +0x34
};

class FileSystem
{
public:
	File *openFile(const char *filename, Int access = 0, Int bufferSize = 0);
};

class NetCommandMsg
{
public:
	void detach();
	void setPlayerID(UnsignedInt playerID) { m_playerID = playerID; }
	void setID(UnsignedShort id) { m_id = id; }

protected:
	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	Int m_commandType;
	Int m_referenceCount;
};

// The file command (ZH's NetFileCommandMsg), held in the ledger under its
// constructor's address name.
class Rva004D6208 : public NetCommandMsg
{
public:
	Rva004D6208();

private:
	char m_pad1C[0x28 - 0x1c];
};

// ZH's setRealFilename(AsciiString).
class Rva004D632D
{
public:
	void rva004D6250(AsciiString filename);
};

class NetFileCommandMsg
{
public:
	void setFileData(UnsignedByte *data, UnsignedInt dataLength);
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

void operator delete[](void *p);

extern FileSystem *TheFileSystem;
extern LANAPI *TheLAN;

class ConnectionManager
{
public:
	void sendFile(AsciiString path, UnsignedByte playerMask, UnsignedShort commandID);
	void sendLocalCommand(NetCommandMsg *msg, UnsignedByte relay);

private:
	char m_pad00000[0x12028];
	Int m_localSlot;
};

void ConnectionManager::sendFile(AsciiString path, UnsignedByte playerMask, UnsignedShort commandID)
{
	File *theFile = TheFileSystem->openFile(path.str(), 0, 0);
	if (!theFile || !theFile->size())
	{
		UnicodeString log;
		log.format(L"Not sending file '%hs' to %X\n", path.str(), playerMask);
		if (TheLAN)
			TheLAN->OnChat(UnicodeString(L"sendFile"), &BfmeNetAddress(0, 0), log, LANCHAT_SYSTEM);
		return;
	}

	Int len = theFile->size();
	char *buf = theFile->readEntireAndClose();

	Rva004D6208 *fileMsg = new Rva004D6208;
	fileMsg->setPlayerID(m_localSlot);
	fileMsg->setID(commandID);
	((Rva004D632D *)fileMsg)->rva004D6250(path);
	((NetFileCommandMsg *)fileMsg)->setFileData((UnsignedByte *)buf, len);

	delete[] buf;
	buf = 0;

	sendLocalCommand(fileMsg, playerMask);

	fileMsg->detach();
}
