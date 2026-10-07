// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ConnectionManager's file-transfer handlers:
//   processFileProgress, retail 0x004D2852, 116 bytes
//   processWrapper,      retail 0x004D29C7, 335 bytes
//   processFile,         retail 0x004D2B16, 376 bytes
//
// Reference: Zero Hour GameEngine/Source/GameNetwork/ConnectionManager.cpp,
// the three functions of the same names (record a peer's progress as the
// larger of old and new; hand a wrapper chunk to the wrapper list and report
// this machine's new progress on a file command; write a received file and
// report it complete). processWrapper and processFile call processFileProgress
// at 0x004D2852 after sending the progress command.
// BFME 2 differences read from these bodies: processWrapper skips everything
// when there is no wrapper list; the file maps are ConnectionManager members
// (+0x12138 commands, +0x12150 eight progress maps), as the matched destructor
// 0x004D2344 and init 0x004D24A2 show.
// The message accessors are folded bodies the ledger holds under other names:
// the file ID word at +0x1C (get 0x004D5767, set 0x004D59AC), the progress or
// file data dword at +0x20 (get 0x0030D377, set 0x00317B9B), the file length
// at +0x24 (0x00091A56) and the real file name (0x004D632D). The progress
// command is the 0x24-byte type built by 0x004D598E. The command map's find
// is held under map<UnsignedShort, Int>'s name and the progress maps'
// operator[] under the Gen_lt_00940b40 instantiation; the trees' code does not
// depend on the mapped type.

#include <map>
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

enum
{
	MAX_SLOTS = 8
};

class File
{
public:
	enum
	{
		WRITE = 0x02,
		CREATE = 0x08,
		BINARY = 0x40
	};

	virtual ~File();
	virtual Bool open(const char *filename, Int access);
	virtual void close();
	virtual Int read(void *buffer, Int bytes);
	virtual Int write(const void *buffer, Int bytes);
};

class FileSystem
{
public:
	File *openFile(const char *filename, Int access = 0, Int bufferSize = 0);
	Bool doesFileExist(const char *filename) const;
};

extern FileSystem *TheFileSystem;

class NetCommandMsg
{
public:
	void detach();
	void setPlayerID(UnsignedInt playerID) { m_playerID = playerID; }
	UnsignedInt getPlayerID() const { return m_playerID; }
	void setID(UnsignedShort id) { m_id = id; }
	UnsignedShort getID() const { return m_id; }
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

class NetCommandRef
{
public:
	NetCommandMsg *getCommand() { return m_msg; }

private:
	NetCommandMsg *m_msg;
};

// Ledger names of the folded accessors.
class NetWrapperCommandMsg
{
public:
	UnsignedShort getWrappedCommandID();
	UnsignedInt getDataLength();	// dword at +0x20
	UnsignedInt getDataOffset();	// dword at +0x24
};

class Rva004D5767WordField
{
public:
	UnsignedShort get() const;		// word at +0x1C
};

class Rva004D59ACWordSlot
{
public:
	void set(UnsignedShort value);	// word at +0x1C
};

class BFMENetInformPlayerLeaveFrameCommandMsg
{
public:
	void setLeavingPlayerID(Int playerID);	// dword at +0x20
};

class Rva004D632D
{
public:
	AsciiString rva004D632D() const;	// the real file name
};

class NetFileCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte *getFileData() { return (UnsignedByte *)((NetWrapperCommandMsg *)this)->getDataLength(); }
	Int getFileLength() { return ((NetWrapperCommandMsg *)this)->getDataOffset(); }
};

class NetFileProgressCommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getFileID() const { return ((const Rva004D5767WordField *)this)->get(); }
	void setFileID(UnsignedShort fileID) { ((Rva004D59ACWordSlot *)this)->set(fileID); }
	Int getProgress() { return ((NetWrapperCommandMsg *)this)->getDataLength(); }
	void setProgress(Int progress) { ((BFMENetInformPlayerLeaveFrameCommandMsg *)this)->setLeavingPlayerID(progress); }

private:
	char m_pad1C[0x24 - 0x1c];
};

// Its constructor, held in the ledger under its address name.
class Rva004D598E : public NetFileProgressCommandMsg
{
public:
	Rva004D598E();
};

class NetCommandWrapperList
{
public:
	void processWrapper(NetCommandRef *ref);
	Int getPercentComplete(UnsignedShort wrappedCommandID);
};

// Zero Hour's max is a macro that evaluates the larger argument twice; this
// body reads the progress once and picks between the two by reference.
template <class NUM>
inline const NUM &progressMax(const NUM &x, const NUM &y)
{
	return (x > y) ? x : y;
}

Bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

struct Gen_lt_00940b40 : public _STL::less<UnsignedShort>
{
};

typedef _STL::map<UnsignedShort, Int> FileCommandMap;
typedef _STL::map<UnsignedShort, Int, Gen_lt_00940b40> FileProgressMap;

class ConnectionManager
{
public:
	void sendLocalCommand(NetCommandMsg *msg, UnsignedByte relay);

private:
	void processWrapper(NetCommandRef *ref);
	void processFile(NetFileCommandMsg *msg);
	void processFileProgress(NetFileProgressCommandMsg *msg);

	char m_pad00000[0x12028];
	Int m_localSlot;
	char m_pad1202C[0x1212c - 0x1202c];
	NetCommandWrapperList *m_netCommandWrapperList;
	char m_pad12130[0x12138 - 0x12130];
	FileCommandMap m_fileCommandMap;
	char m_pad12144[0x12150 - 0x12144];
	FileProgressMap m_fileProgressMap[MAX_SLOTS];
};

void ConnectionManager::processFileProgress(NetFileProgressCommandMsg *msg)
{
	Int oldProgress = m_fileProgressMap[msg->getPlayerID()][msg->getFileID()];

	m_fileProgressMap[msg->getPlayerID()][msg->getFileID()] = progressMax(oldProgress, msg->getProgress());
}
