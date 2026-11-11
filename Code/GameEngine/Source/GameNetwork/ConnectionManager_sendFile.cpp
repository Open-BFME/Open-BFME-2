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

#include "../../Include/Common/File.h"

#include "../../Include/Common/FileSystem.h"

#include "../../Include/GameNetwork/NetCommandMsg.h"

inline void NetCommandMsg::setID(unsigned short id)
{
	m_id = id;
}

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
#include "../../Include/GameNetwork/Rva004D632D.h"

class NetFileCommandMsg
{
public:
	void setFileData(UnsignedByte *data, UnsignedInt dataLength);
};

#include "../../Include/GameNetwork/BfmeNetAddress.h"
#include "../../Include/GameNetwork/LANAPI.h"

// The canonical BfmeNetAddress has no constructor; retail zeroes the
// record OnChat receives in place, as a temporary built between the pushes.
struct ZeroNetAddress : public BfmeNetAddress
{
	ZeroNetAddress() { ip = 0; port = 0; }
};

#include <new>

extern FileSystem *TheFileSystem;
extern LANAPI *TheLAN;

#include "../../Include/GameNetwork/ConnectionManager.h"

void ConnectionManager::sendFile(AsciiString path, UnsignedByte playerMask, UnsignedShort commandID)
{
	File *theFile = TheFileSystem->openFile(path.str(), 0, 0);
	if (!theFile || !theFile->size())
	{
		UnicodeString log;
		log.format(L"Not sending file '%hs' to %X\n", path.str(), playerMask);
		if (TheLAN)
			TheLAN->OnChat(UnicodeString(L"sendFile"), &ZeroNetAddress(), log, LANAPI::LANCHAT_SYSTEM);
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
