// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ConnectionManager's handler for command type 20, retail 0x004CF1AD,
// 328 bytes including its catch-all funclet 0x004CF2CA.
//
// No reference source: the command type is new in BFME 2 (Zero Hour and
// BFME 1 go from FILE 19 straight to FILEANNOUNCE 20). What the body does is
// read from these bytes. The dispatcher 0x004D2F04 routes type 20 here. If
// the command's +0x1C dword matches TheGameInfo's +0x88 value, and the slot
// named by its +0x20 word is occupied with a nonzero +0x50, the data block
// (+0x24 pointer, +0x28 length) is opened as a memory file. Inside a
// catch-all, an Xfer reader over it loads a fresh CreateAHeroData from
// TheHeroManager, the slot copies it in, and the temporary is freed. The
// catch path frees the temporary if one exists, then closes the reader and
// the file and returns.
// Callees by ledger name: the reader is the Xfer-family object built by
// 0x0060C5FA, opened by 0x0060C3C3, closed by 0x0060C45E and destroyed by
// Xfer's destructor 0x000053E7. The hero data is allocated by 0x00219251
// with the CreateAHeroData constructor's default arguments, and released by
// 0x0021929D. The slot setter is 0x0037AD8D.
//
// The sender, retail 0x004D01D5, 289 bytes including its catch-all funclet
// 0x004D02F0, reached from Network's vtable 0x00BF6040 slot 34 through the
// tail jump at 0x0025DC59. It builds the type-20 command (operator new 0x2C,
// constructor 0x004D58DE), stamps the local slot and a command id as Zero
// Hour's senders do, and stores the seed and slot. The hero data is written
// by XferSave (0x0060D1F7, opened by 0x0060D10A inside a catch-all that only
// returns) into the memory stream 0x006023C1 names "heroString"; its buffer
// (0x006021A4) becomes the command's data block (0x004D5925) and is freed. The
// command is handed to the receiver above first, then sent with the relay
// mask (1 << local slot) ^ the caller's mask and detached.

#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#define TRUE 1

// Declared so delete[] calls the array form 0x0002FD80, as retail does; MSVC
// 7.1 otherwise lowers it to the scalar operator delete.
void operator delete[](void *p);

class Xfer
{
public:
	virtual ~Xfer();
};

// The stream interface XferLoad::Open reads through.
struct Rva0060C3C3Stream;

// The reader: an Xfer with its own vtable, built from three null pointers.
class Rva0060C5FA : public Xfer
{
public:
	Rva0060C5FA(void *a1, void *a2, void *a3);

private:
	char m_pad04[0x20 - 4];
};

class XferLoad
{
public:
	bool Open(Rva0060C3C3Stream *stream, Int *version);
};

class Rva0060C45E
{
public:
	void clear();
};

class File
{
public:
	virtual ~File();
	virtual Bool open(const char *filename, Int access);
	virtual void close();
};

File *createMemoryReadFile(char *data, Int size);

class CreateAHeroData
{
public:
	virtual ~CreateAHeroData();
	virtual void crc(Xfer *xfer);
	virtual const char *typeName() const;
	virtual void xfer(Xfer *xfer);
};

class GameSlot
{
public:
	Bool isOccupied() const;
	Int getHeroKind() const { return m_heroKind; }
	void rva0037AD8D(const CreateAHeroData &data);

private:
	char m_pad00[0x50];
	Int m_heroKind;
};

class GameInfo
{
public:
	GameSlot *getSlot(Int slotNum);
	Int getSeed() const { return m_seed; }

private:
	char m_pad00[0x88];
	Int m_seed;
};

// TheHeroManager, held in the ledger under its allocator's address name.
class Rva00219251
{
public:
	CreateAHeroData *rva00219251(Int a = 0, Int b = 0, Int c = 0,
		const UnicodeString &name = UnicodeString::TheEmptyString,
		Int d = -1, Int color = 0xFF707070, Int e = -1);
	void rva0021929D(CreateAHeroData **data);
};

extern GameInfo *TheGameInfo;
extern Rva00219251 *TheHeroManager;

enum NetCommandType
{
};

class NetCommandMsg
{
public:
	void setPlayerID(UnsignedInt playerID) { m_playerID = playerID; }
	void setID(UnsignedShort id) { m_id = id; }
	NetCommandType getNetCommandType() { return (NetCommandType)m_commandType; }
	void detach();

protected:
	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	Int m_commandType;
	Int m_referenceCount;
};

// The type-20 command's payload.
class Rva004D58DE : public NetCommandMsg
{
public:
	Rva004D58DE();
	Int getSeed() const { return m_seed; }
	void setSeed(Int seed) { m_seed = seed; }
	UnsignedShort getSlot() const { return m_slot; }
	void setSlot(UnsignedShort slot) { m_slot = slot; }
	char *getData() { return m_data; }
	Int getDataLength() const { return m_dataLength; }
	void rva004D5925(unsigned char *data, unsigned int length);

private:
	Int m_seed;
	UnsignedShort m_slot;
	char *m_data;
	Int m_dataLength;
};

// The memory stream 0x006023C1 builds; 0x006021A4 hands back its buffer.
class BfmeThingEC
{
public:
	int bfmeTakeEC(int *size);
};

class BfmeMade_009CB5F0;
BfmeMade_009CB5F0 *bfmeMake_009CB5F0(void *text);

class XferSave
{
public:
	XferSave(void);
	virtual ~XferSave(void);
	unsigned char Open(Xfer *file, int mode, bool flag);
	void close(void);

private:
	char m_body[0x3c];
};

Bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

class ConnectionManager
{
public:
	void rva004CF1AD(NetCommandMsg *command);
	void rva004D01D5(CreateAHeroData *hero, Int seed, UnsignedShort slot,
		UnsignedByte playerMask);
	void sendLocalCommand(NetCommandMsg *msg, UnsignedByte relay);

private:
	char m_pad00[0x12028];
	Int m_localSlot;
};

void ConnectionManager::rva004CF1AD(NetCommandMsg *command)
{
	Rva004D58DE *msg = (Rva004D58DE *)command;
	if (msg == 0 || TheGameInfo == 0)
		return;
	if (msg->getSeed() != TheGameInfo->getSeed())
		return;
	GameSlot *slot = TheGameInfo->getSlot(msg->getSlot());
	if (!slot->isOccupied() || slot->getHeroKind() == 0)
		return;
	if (msg->getDataLength() == 0)
		return;
	File *file = createMemoryReadFile(msg->getData(), msg->getDataLength());
	if (file == 0)
		return;

	Rva0060C5FA xfer(0, 0, 0);
	CreateAHeroData *hero = 0;
	try
	{
		Int version;
		if (((XferLoad *)&xfer)->Open((Rva0060C3C3Stream *)file, &version))
		{
			hero = TheHeroManager->rva00219251();
			hero->xfer(&xfer);
			slot->rva0037AD8D(*hero);
			TheHeroManager->rva0021929D(&hero);
		}
	}
	catch (...)
	{
		if (hero != 0)
			TheHeroManager->rva0021929D(&hero);
		((Rva0060C45E *)&xfer)->clear();
		file->close();
		return;
	}
	((Rva0060C45E *)&xfer)->clear();
	file->close();
}

void ConnectionManager::rva004D01D5(CreateAHeroData *hero, Int seed,
	UnsignedShort slot, UnsignedByte playerMask)
{
	if (hero == 0)
		return;
	Int relay = (1 << m_localSlot) ^ playerMask;
	Rva004D58DE *msg = new Rva004D58DE;
	msg->setPlayerID(m_localSlot);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()) == TRUE)
		msg->setID(GenerateNextCommandID());
	msg->setSeed(seed);
	msg->setSlot(slot);

	BfmeThingEC *stream = (BfmeThingEC *)bfmeMake_009CB5F0((void *)"heroString");
	XferSave xfer;
	try
	{
		xfer.Open((Xfer *)stream, 1, false);
	}
	catch (...)
	{
		return;
	}
	hero->xfer((Xfer *)&xfer);
	xfer.close();
	int size;
	unsigned char *data = (unsigned char *)stream->bfmeTakeEC(&size);
	msg->rva004D5925(data, size);
	delete[] data;
	rva004CF1AD(msg);
	sendLocalCommand(msg, relay);
	msg->detach();
}
