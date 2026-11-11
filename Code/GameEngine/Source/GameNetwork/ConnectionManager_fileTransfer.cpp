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
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBGH@_STL@@@_STL@@@_STL@@QBEPAU?$_Rb_tree:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_node<pair<unsigned short const ,int> > * allocator<_Rb_tree_node<pair<unsigned short const ,int> > >::allocate(unsigned int,void const *) const; }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline pair<unsigned short const ,int>::pair(unsigned short const &a,int const &b) : first(a), second(b) {} }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned short>::operator()(unsigned short const &x,unsigned short const &y)const  { return x < y; } }

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

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

#include "../../Include/Common/File.h"

#include "../../Include/Common/FileSystem.h"

extern FileSystem *TheFileSystem;

#include "../../Include/GameNetwork/NetCommandMsg.h"
#include "../../Include/GameNetwork/BFMENetInformPlayerLeaveFrameCommandMsg.h"
#include "../../Include/GameNetwork/NetWrapperCommandMsg.h"

inline void NetCommandMsg::setID(unsigned short id)
{
	m_id = id;
}

class NetCommandRef
{
public:
	NetCommandMsg *getCommand() { return m_msg; }

private:
	NetCommandMsg *m_msg;
};

// Ledger names of the folded accessors.
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
	__declspec(dllimport) __forceinline void setFileID(UnsignedShort fileID) { ((Rva004D59ACWordSlot *)this)->set(fileID); }
	Int getProgress() { return ((NetWrapperCommandMsg *)this)->getDataLength(); }
	__declspec(dllimport) __forceinline void setProgress(Int progress) { ((BFMENetInformPlayerLeaveFrameCommandMsg *)this)->setLeavingPlayerID(progress); }

private:
	char m_pad1C[0x24 - 0x1c];
};

// Its constructor, held in the ledger under its address name.
class Rva004D598E : public NetFileProgressCommandMsg
{
public:
	Rva004D598E();
};

#include "../../Include/GameNetwork/NetCommandWrapperListClass.h"

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

void ConnectionManager::processWrapper(NetCommandRef *ref)
{
	NetWrapperCommandMsg *wrapperMsg = (NetWrapperCommandMsg *)(ref->getCommand());
	UnsignedShort commandID = wrapperMsg->getWrappedCommandID();
	Int origProgress = 0;
	FileCommandMap::iterator fcIt = m_fileCommandMap.find(commandID);
	if (fcIt != m_fileCommandMap.end())
	{
		origProgress = m_fileProgressMap[m_localSlot][commandID];
	}

	if (m_netCommandWrapperList != 0)
	{
		m_netCommandWrapperList->processWrapper(ref);

		if (fcIt != m_fileCommandMap.end())
		{
			Int newProgress = m_netCommandWrapperList->getPercentComplete(commandID);
			if (newProgress > origProgress && newProgress < 100)
			{
				m_fileProgressMap[m_localSlot][commandID] = newProgress;

				Int progressMask = 0xff ^ (1 << m_localSlot);
				NetFileProgressCommandMsg *msg = new Rva004D598E;
				msg->setPlayerID(m_localSlot);
				msg->setID(0);
				if (DoesCommandRequireACommandID(msg->getNetCommandType()))
				{
					msg->setID(GenerateNextCommandID());
				}
				msg->setFileID(commandID);
				msg->setProgress(newProgress);
				sendLocalCommand(msg, progressMask);
				processFileProgress(msg);
				msg->detach();
			}
		}
	}
}

void ConnectionManager::processFile(NetFileCommandMsg *msg)
{
	TheFileSystem->doesFileExist(((const Rva004D632D *)msg)->rva004D632D().str());

	UnsignedByte *buf = msg->getFileData();
	Int len = msg->getFileLength();

	File *fp = TheFileSystem->openFile(((const Rva004D632D *)msg)->rva004D632D().str(), File::CREATE | File::BINARY | File::WRITE);
	if (fp)
	{
		fp->write(buf, len);
		fp->close();
		fp = 0;
	}

	Int commandID = msg->getID();
	Int newProgress = 100;

	m_fileProgressMap[m_localSlot][commandID] = newProgress;

	Int progressMask = 0xff ^ (1 << m_localSlot);
	NetFileProgressCommandMsg *progressMsg = new Rva004D598E;
	progressMsg->setPlayerID(m_localSlot);
	progressMsg->setID(0);
	if (DoesCommandRequireACommandID(progressMsg->getNetCommandType()))
	{
		progressMsg->setID(GenerateNextCommandID());
	}
	progressMsg->setFileID(commandID);
	progressMsg->setProgress(newProgress);
	sendLocalCommand(progressMsg, progressMask);
	processFileProgress(progressMsg);
	progressMsg->detach();
}
