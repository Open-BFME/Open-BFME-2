// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
//
// ?createMemoryReadFile@@YAPAVFile@@PADH@Z
// retail 0x006022CF, 71 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/Common/System/File.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
// stlport
// readable body of ?Free_Definitions@DefinitionMgrClass@@: game/Libraries/Source/WWVegas/WWSaveLoad/definitionmgr.cpp
//
// The File base class. Its three subclasses' vtables all carry
// ?close@File@@UAEXXZ at slot 2, which is what identifies the family, and BFME's
// layout is Zero Hour's 15 File slots with two appended -- so slots 0..14 mean
// exactly what Zero Hour's file.h declares them to mean:
//
//   0x01143A38  MemoryReadFile
//   0x01143AA8  MemoryWriteFile
//   0x01143AF8  File itself
//
// The first two are named by their own constructors. 0x009CB3D0 installs
// 0x01143A38 and then sets the file's name to "<MemoryReadFile>"; 0x009CB4E0
// installs 0x01143AA8 and sets "<MemoryWriteFile>". That is the same kind of
// evidence "<no file>" gives for File -- a literal the object's own constructor
// uses to identify it -- and both classes are BFME-only, appearing nowhere in
// the Zero Hour tree.
//
// There are seven File vtables in all, found by looking for the ones that carry
// File::print (0x009CB6C0) at slot 10, which every subclass here inherits:
//
//   0x01143A38  MemoryReadFile        dtor 0x009CB440
//   0x01143AA8  MemoryWriteFile       dtor 0x009CB650
//   0x01143AF8  File                  dtor 0x009CB950
//   0x01143C10  Win32LocalFile        dtor 0x009D1960   ctor 0x009D1930
//   0x01143C58  RAMFile               dtor 0x009D1C30   ctor 0x009D1980
//   0x01143CA8  StreamingArchiveFile  dtor 0x009D22B0   ctor 0x009D20B0
//   0x01143D38  LocalFile             dtor 0x009D26C0   ctor 0x009D23E0
//
// Measured state of 0x009C9000-0x009CE000, since "the File family" is often
// taken to mean that range: it holds 282 real functions once the 5-byte
// incremental-link thunks are discounted, and 36 of them are claimed. 33 of
// those 36 are this file; the rest are two Win32LocalFileSystem rows,
// ArchiveFileSystem, ArchiveFile and one MASM dump.
//
// The other 246 are not waiting on effort. Running tools/locate.py over
// ArchiveFileSystem.cpp, ArchiveFile.cpp, Win32LocalFileSystem.cpp and
// FileSystem.cpp places nothing at all: 114 definitions come back ambiguous,
// because they are STL instantiations over AsciiString-keyed maps of
// ArchivedFileInfo and DetailedArchivedDirectoryInfo whose bodies are identical
// at six or more addresses, and 245 come back unlocated, because BFME rewrote
// the archive file system and Zero Hour's source no longer assembles to it.
// None of the eighteen largest unclaimed functions references a string, so
// there is nothing to anchor a name to either.
//
// So the range is 13% claimed and the remainder is a rewrite to recover rather
// than a gap to fill. The File subclasses themselves -- the part that had names
// to find -- are done.
//
// So the family runs past 0x009CE000 into 0x009D2xxx. None of the last four set
// an identifying literal the way MemoryReadFile and MemoryWriteFile do, so they
// are named by construction instead:
//
// Win32LocalFileSystem's vtable is 0x01143B98 (its constructor is 0x009CDE10),
// and it is identified by two rows this ledger already carries -- slot 4 is
// ?doesFileExist@Win32LocalFileSystem@@UBE_NPBD@Z and slot 6 is
// ?getFileInfo@Win32LocalFileSystem@@UBE_NABVAsciiString@@PAUFileInfo@@@Z. Its
// slot 3, 0x009CDF50, is openFile: it does push 0x18 / call operator new /
// call 0x009D1930. So 0x009D1930 constructs what a local file system hands
// back, sizeof 0x18, and that constructor installs 0x01143C10 -- Win32LocalFile.
//
// 0x009D1930 chains to 0x009D23E0, which installs 0x01143D38 and stores -1 at
// +0x14. A base of Win32LocalFile holding an invalid-handle sentinel is
// LocalFile, and +0x14 is the OS file handle -- the one File's own +0x10 is not.
//
// The other two are named by the fields their constructors zero, matching Zero
// Hour's declarations exactly: 0x009D1980 calls File::File and zeroes +0x14,
// +0x18 and +0x1c, which is RAMFile's char *m_data / Int m_size / Int m_pos
// (sizeof 0x20); 0x009D20B0 calls that constructor and zeroes +0x20, +0x24 and
// +0x28, which is StreamingArchiveFile's File *m_file / Int m_startingPos /
// Int m_size on top of RAMFile (sizeof 0x2C). That also settles the "Streaming
// from a compressed archive file is not supported" lead: the string belongs to
// StreamingArchiveFile at 0x01143CA8, not to 0x01143C10.
//
// 0x01143AF8 is File's own: MemoryReadFile's constructor calls 0x009CB7A0 first,
// and that is what stores 0x01143AF8 and sets "<no file>", so 0x009CB7A0 is
// File::File and 0x009CB8C0 (which MemoryReadFile's deleting destructor calls)
// is File::~File. Counting slots forward from a vtable overruns into the next
// one -- .rdata packs them adjacently with nothing between -- so all three are
// 17 slots, not the 40 a naive walk reports for the last.
//
// Slots holding the same address in all three are File's own un-overridden
// implementations: slot 2 close (0x009CB880), slot 10 print (0x009CB6C0), and
// slots 15/16 (0x009CB760, 0x009CB790) -- the two BFME added, which Zero Hour
// has no name for.
//
// File and RAMFile are the registered BFME 2 classes (Common/File.h and
// Common/RAMFileClass.h): File is not a MemoryPoolObject (m_deleteOnClose
// closes by deleting through the vtable) and carries the mutex at +0x10.
#include "PreRTS.h"
#include "Common/AsciiString.h"

#include "../../../Include/Common/File.h"
#include "../../../Include/Common/RAMFileClass.h"

//-----------------------------------------------------------------------------
// MemoryReadFile -- a File over a block of memory the caller already has.
// Named by its own constructor at 0x009CB3D0, which installs vtable 0x01143A38
// and then sets the file's name to "<MemoryReadFile>". BFME-only; Zero Hour has
// no such class.
//
// Layout, read off the overrides below: m_data at +0x14, m_size at +0x18 and
// m_pos at +0x1c -- straight after File, whose own last member is the buffer
// pointer at +0x10 that File::File zeroes and File::~File frees.
//-----------------------------------------------------------------------------
// StreamingArchiveFile, 0x01143CA8 in the table above. It lives here rather than
// in StreamingArchiveFile.cpp for one reason: it is laid out on BFME's File, and
// that file compiles against Zero Hour's, which is four bytes shorter because it
// has no m_mutex at +0x10. Its constructor came out zeroing +0x1c through +0x28
// where retail zeroes +0x20 through +0x28 -- the whole class shifted down by the
// missing word.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StreamingArchiveFile.h
class StreamingArchiveFile : public RAMFile
{
public:
	StreamingArchiveFile();

	virtual Bool open( const char *filename, Int access = 0 );
	// close (slot 2) is not re-declared either: retail's vtable 0x01143CA8 holds
	// 0x009D21E0 there, the ILT jump stub whose target= note is 0x009CB880, so it
	// forwards to ?close@File@@UAEXXZ exactly as LocalFile's 0x009D2540 does.
	virtual Int read( void *buffer, Int bytes );
	virtual Int write( const void *buffer, Int bytes );
	virtual Int seek( Int bytes, seekMode mode );
	virtual void nextLine( char *buf, Int bufSize );
	virtual Bool scanInt( Int &newInt );
	virtual Bool scanReal( Real &newReal );
	virtual Bool scanString( AsciiString &newString );
	// Slots 11 and 12 likewise: retail holds File::size and File::position there,
	// so this subclass re-declares neither.
	virtual char *readEntireAndClose( void );
	virtual File *convertToRAMFile( void );

protected:
	File *m_file;			// +0x20
	Int m_startingPos;		// +0x24
	Int m_size;				// +0x28
};

// LocalFile, 0x01143D38. It adds one word to File and initialises it to -1,
// which is INVALID_HANDLE_VALUE -- so this is the class that owns the OS file
// handle, and File's own +0x10 (the mutex) is not it.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LocalFile.h
class LocalFile : public File
{
public:
	LocalFile();

	virtual Bool open( const char *filename, Int access = 0 );
	// close (slot 2) is deliberately not re-declared. Retail's LocalFile vtable
	// 0x01143D38 holds 0x009D2540 there -- the ILT jump stub whose target= note
	// is 0x009CB880 -- so it forwards to ?close@File@@UAEXXZ and this class owns
	// no close of its own.
	virtual Int read( void *buffer, Int bytes );
	virtual Int write( const void *buffer, Int bytes );
	// The mode is File::seekMode, not Int: retail's slot 5 is 0x009D25D0, which
	// is ?seek@LocalFile@@UAEHHW4seekMode@File@@@Z, the spelling the
	// LocalFile.cpp object defines, and the override of File's own seek.
	virtual Int seek( Int bytes, seekMode mode );
	virtual void nextLine( char *buf, Int bufSize );
	virtual Bool scanInt( Int &newInt );
	virtual Bool scanReal( Real &newReal );
	virtual Bool scanString( AsciiString &newString );
	// size (slot 11) and position (slot 12) likewise: retail holds File::size
	// and File::position there, and RAMFile, StreamingArchiveFile and
	// Win32LocalFile inherit the same two through here.
	virtual char *readEntireAndClose( void );
	virtual File *convertToRAMFile( void );

protected:
	HANDLE m_handle;		// +0x14
};

// Win32LocalFile, 0x01143C10. It adds no members of its own -- the constructor
// is a base call and a vptr store, nothing else -- which is what
// Win32LocalFileSystem::openFile allocates 0x18 bytes for.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32LocalFile.h
class Win32LocalFile : public LocalFile
{
public:
	Win32LocalFile();

	// Retail's vtable 0x01143C10 is LocalFile's 0x01143D38 entry for entry except
	// slot 0, so this class overrides exactly one thing and inherits the rest.
	// Only scanString (slot 9, 0x009D26E0) is its own; the other twelve go
	// through LocalFile, which is what spells ?open@LocalFile@@UAE_NPBDH@Z,
	// ?read@LocalFile@@UAEHPAXH@Z, ?write@LocalFile@@UAEHPBXH@Z,
	// ?seek@LocalFile@@UAEHHW4seekMode@File@@@Z, ?nextLine@LocalFile@@UAEXPADH@Z,
	// ?scanInt@LocalFile@@UAE_NAAH@Z, ?scanReal@LocalFile@@UAE_NAAM@Z,
	// ?convertToRAMFile@LocalFile@@UAEPAVFile@@XZ, and -- through LocalFile not
	// overriding them either -- ?close@File@@UAEXXZ, ?size@File@@UAEHXZ and
	// ?position@File@@UAEHXZ, all of which are matched bodies.
	virtual Bool scanString( AsciiString &newString );
};

class MemoryReadFile : public File
{
public:
	virtual Bool open( const char *filename, Int access = 0 );
	virtual Int read( void *buffer, Int bytes );
	virtual Int write( const void *buffer, Int bytes );
	virtual Int seek( Int bytes, seekMode mode );
	virtual void nextLine( char *buf, Int bufSize );
	virtual Bool scanInt( Int &newInt );
	virtual Bool scanReal( Real &newReal );
	virtual Bool scanString( AsciiString &newString );
	virtual Int size( void );
	virtual Int position( void );
	virtual char *readEntireAndClose( void );
	virtual File *convertToRAMFile( void );

public:
	MemoryReadFile( char *data, Int size );

private:
	char *m_data;			// +0x14
	Int m_size;				// +0x18
	Int m_pos;				// +0x1c
};

File *createMemoryReadFile( char *data, Int size )
{
	if( data == NULL && size != 0 )
	{
		return NULL;
	}

	return new MemoryReadFile( data, size );
}

//-----------------------------------------------------------------------------
// MemoryWriteFile -- a File that accumulates into a heap buffer it grows itself.
// Named by its constructor at 0x009CB4E0, which installs vtable 0x01143AA8 and
// sets the file's name to "<MemoryWriteFile>". BFME-only, like MemoryReadFile.
//
// Same three members as MemoryReadFile, plus m_capacity at +0x20: the
// buffer is realloc'd to 2*needed + 0x1000 whenever a write would run past it,
// so it grows geometrically with a 4K floor.
//-----------------------------------------------------------------------------
class MemoryWriteFile : public File
{
public:
	virtual Bool open( const char *filename, Int access = 0 );
	virtual Int read( void *buffer, Int bytes );
	virtual Int write( const void *buffer, Int bytes );
	virtual Int seek( Int bytes, seekMode mode );
	virtual void nextLine( char *buf, Int bufSize );
	virtual Bool scanInt( Int &newInt );
	virtual Bool scanReal( Real &newReal );
	virtual Bool scanString( AsciiString &newString );
	virtual Int size( void );
	virtual Int position( void );
	virtual char *readEntireAndClose( void );
	virtual File *convertToRAMFile( void );

public:
	MemoryWriteFile( const char *name );
	virtual ~MemoryWriteFile();

private:
	char *m_data;			// +0x14
	Int m_size;				// +0x18
	Int m_pos;				// +0x1c
	Int m_capacity;			// +0x20
	AsciiString m_pendingName;	// +0x24 -- the destructor releases it
};

