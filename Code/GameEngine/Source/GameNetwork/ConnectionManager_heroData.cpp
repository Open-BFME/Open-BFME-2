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

#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

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

class NetCommandMsg
{
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
class Rva004CF1ADCommandMsg : public NetCommandMsg
{
public:
	Int getSeed() const { return m_seed; }
	UnsignedShort getSlot() const { return m_slot; }
	char *getData() { return m_data; }
	Int getDataLength() const { return m_dataLength; }

private:
	Int m_seed;
	UnsignedShort m_slot;
	char *m_data;
	Int m_dataLength;
};

class ConnectionManager
{
public:
	void rva004CF1AD(NetCommandMsg *command);
};

void ConnectionManager::rva004CF1AD(NetCommandMsg *command)
{
	Rva004CF1ADCommandMsg *msg = (Rva004CF1ADCommandMsg *)command;
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
