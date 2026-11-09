// cl: /O1 /DNDEBUG /MD /EHsc /G7 /arch:SSE
// Split from LocalFile.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Open-BFME5: LocalFile, retail vtable 0x01143D38.
//
// File.cpp already pins this class by construction: 0x009D23E0 installs
// 0x01143D38 and stores -1 at +0x14, and a base of Win32LocalFile holding an
// invalid-handle sentinel is LocalFile, so +0x14 is the OS file handle. The
// bodies here confirm it from the other side -- every one of them passes
// [this+0x14] straight to a CRT low-level io import.
//
// The File base is spelled locally rather than included, the same way File.cpp
// spells it: only the layout matters here (m_open at +0xc is what write's
// leading `mov al,[ecx+0xc]` tests), and AsciiString stands in as a raw pointer
// because no body in this file touches the name.
//
// USE_BUFFERED_IO is off in retail: every call site here is a low-level
// _write/_lseek/_read through the IAT, not the stdio pair the Zero Hour source
// takes when that macro is defined.
//
// The vtable itself is the map for the rest of the class. Read out of the image
// at 0x01143D38, seventeen slots, against Zero Hour's file.h declaration order:
//
//   slot  0  0x009D26C0  scalar deleting destructor   (gen_small/dtors_010)
//   slot  1  0x009D2480  open                         landed here
//   slot  2  0x009D2540  close                        5-byte tail jump, see below
//   slot  3  0x009D2550  read                         landed here
//   slot  4  0x009D25A0  write                        landed here
//   slot  5  0x009D25D0  seek                         landed here
//   slot  6  0x009D2610  nextLine                     landed here
//   slot  7  0x009D2850  scanInt                      open, needs AsciiString
//   slot  8  0x009D2970  scanReal                     open, needs AsciiString
//   slot  9  0x009D26E0  scanString                   open, needs AsciiString
//   slot 10  0x009CB6C0  print                        File's, already matched
//   slot 11  0x009CB670  size                         File's, already matched
//   slot 12  0x009CB6B0  position                     File's, already matched
//   slot 13  0x009D2690  readEntireAndClose           landed here
//   slot 14  0x009D2790  convertToRAMFile             open, needs RAMFile
//   slot 15  0x009CB760  lock                         File's
//   slot 16  0x009CB790  unlock                       File's
//
// Slots 10..12 and 15..16 landing on File's own bodies is the independent check
// on the whole table: those five addresses are exactly the ones File.cpp already
// identified as File's un-overridden implementations, so the slot numbering here
// agrees with the numbering derived there from three other vtables.
//
// ~LocalFile is 0x009D2400 and LocalFile::LocalFile 0x009D23E0 (the latter
// already matched in File.cpp), which brackets the class: everything from
// 0x009D23E0 to 0x009D2A00 is one compiland.

#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <new>
#include <stdlib.h>
#include <sys/stat.h>

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

// Wide filename adapter, retail 0x002FB30: UTF16-to-UTF8 through
// WideCharToMultiByte (CP_UTF8). Rowed in Utf8Conversions.cpp; the G spelling
// matches that row so this TU resolves it with no pin.
typedef unsigned short Wide;
int BFME2WideToUtf8(const Wide *source, int count, char *output, int capacity);
int BFME2Utf8ToWide(const char *source, int count, Wide *output, int capacity);

#include "../../../Include/Common/File.h"
#include "../../../Include/Common/RAMFileClass.h"

#include "../../../Include/Common/LocalFile.h"

class StreamingArchiveFile : public RAMFile
{
public:
	StreamingArchiveFile();
	virtual ~StreamingArchiveFile();
	virtual bool open( const char *filename, int access );
	// Retail's slot 17 (vtable 0x00C7AA50) is a plain `return TRUE` body, folded
	// at 0x005CB9FA with other one-argument TRUE stubs.
	virtual bool open( File *file ) { return true; }
	virtual void close( void );
	virtual int seek( int pos, seekMode mode );
	virtual bool openFromArchive(File *archiveFile, const AsciiString &filename, int offset, int size);
	virtual int read(void *buffer, int bytes);

protected:
	File *m_file;		// +0x20
	int m_startingPos;	// +0x24
	int m_curPos;		// +0x28
};

#include "../../../Include/Common/FileSystem.h"

extern FileSystem *TheFileSystem;

#include "../debug.h"

extern Debug *theDebug;
extern void _bfme_debugRecordCallsite(int kind);

// The running count of open local files, retail 0x0134D064. Bumped once per
// successful _open and never read here, so only the increment is visible.
static int s_totalOpen = 0;


// ??0RAMFile@@QAE@XZ, retail 0x006054E7, 29 bytes. Calls the rowed File ctor
// 0x006024FD, zeroes m_data/m_pos/m_size at +0x14/+0x18/+0x1C and stores
// RAMFile's vtable 0x0087AA00 (slot 0 ??_GRAMFile, slots 2/3/5/6 the rowed
// RAMFile close/read/seek/nextLine). ZH RAMFile::RAMFile. Callers are
// LocalFile::convertToRAMFile (new RAMFile) and the StreamingArchiveFile ctor
// 0x00605A28. Previously rowed as DieModuleData's ctor in its own unit.
RAMFile::RAMFile()
	: m_data(0), m_pos(0), m_size(0)
{
}

// ??1RAMFile@@UAE@XZ, retail 0x00605504, 67 bytes. RAMFile destructor: stores
// vtable 0x0087AA00, array-deletes m_data at +0x14 via rowed ??_V 0x0002FD80,
// calls rowed File::close 0x0060259A, then the rowed File dtor 0x006025CE.
// Vtable slots prove RAMFile (slot 2 is rowed RAMFile::close 0x00605547, slot 3
// is 0x00605564 read, slot 5 seek, slot 6 nextLine); donor is BFME1
// RAMFileDestructorThunk (protected spelling) but File-family dtors here are
// public UAE like LocalFile/File, and the ctor at 0x006054E7 is public QAE.
RAMFile::~RAMFile()
{
	::operator delete[](m_data);
	File::close();
}

// ??0StreamingArchiveFile@@QAE@XZ, retail 0x00605A28, 29 bytes. Calls the
// RAMFile ctor 0x006054E7, zeroes m_file/m_startingPos/m_curPos at
// +0x20/+0x24/+0x28 and stores StreamingArchiveFile's vtable 0x0087AA50.
// ZH StreamingArchiveFile::StreamingArchiveFile. Previously rowed as
// EjectPilotDieModuleData's ctor, a whole-.text placement of a body whose
// bytes happen to agree; a ModuleData cannot have a RAMFile base.
StreamingArchiveFile::StreamingArchiveFile()
	: m_file(0), m_startingPos(0), m_curPos(0)
{
}

// ??1StreamingArchiveFile@@UAE@XZ, retail 0x00605A45, 56 bytes.
// StreamingArchiveFile dtor (vtable 0x0087AA50): stores its vtable, calls rowed
// File::close 0x0060259A, then the rowed RAMFile dtor 0x00605504 as base.
// The ctor at 0x00605A28 (mislabeled EjectPilotDieModuleData) calls the RAMFile
// ctor and zeroes +0x20/+0x24/+0x28 (m_file/startingPos/size), matching BFME1
// StreamingArchiveFile layout; slot 3 read at 0x00605A82 uses +0x20 File*.
// Packet class EjectPilotDieModuleData is a ledger mislabel: that ModuleData
// cannot call File::close or a RAMFile base.
StreamingArchiveFile::~StreamingArchiveFile()
{
	File::close();
}


















// ?openFromArchive@StreamingArchiveFile@@UAE_NPAVFile@@ABVAsciiString@@HH@Z @ 0x00605B68 (240B)
// Slot 18 (offset 0x48) of vtable 0x0087AA50. BFME1 StreamingArchiveFile::openFromArchive
// with the BFME2 compressed-archive guard: stores m_file/m_startingPos/RAMFile m_size/m_curPos,
// verifies seek(offset)+seek(size) bracket, rewinds, reads the 2-byte compression marker at
// [ebp+8] (reused dead arg slot), reports 0x15fb through theDebug SkipNext/CrashBegin/operator<</
// CrashDone plus _bfme_debugRecordCallsite(1), rewinds, assigns the name, returns true.
// Donor: reference/open-bfme-1/Code/Libraries/Source/file/StreamingArchiveFile.cpp
// (File::open READ|BINARY|STREAMING, seek START/CURRENT, read 2, 0x15fb, debug, seek, assign).
// Vtable 0x0087AA50 and neighbours ??_GStreamingArchiveFile 0x00605B1A / dtor 0x00605A45 prove
// StreamingArchiveFile; string 0x00C7AAA0 and theDebug 0x00DE0880 are DIR32-filled.
bool StreamingArchiveFile::openFromArchive( File *archiveFile, const AsciiString &filename, int offset, int size )
{
	if( archiveFile == NULL )
	{
		return false;
	}

	if( File::open( filename.str(), File::READ | File::BINARY | File::STREAMING ) == false )
	{
		return false;
	}

	m_file = archiveFile;
	m_startingPos = offset;
	RAMFile::m_size = size;
	m_curPos = 0;

	if( m_file->seek( offset, File::START ) != offset )
	{
		return false;
	}

	if( m_file->seek( size, File::CURRENT ) != m_startingPos + size )
	{
		return false;
	}

	m_file->seek( offset, File::START );

	unsigned short compressionMarker = 0;
	if( m_file->read( &compressionMarker, 2 ) != 2 )
	{
		return false;
	}

	if( compressionMarker == 0x15fb )
	{
		_bfme_debugRecordCallsite( 1 );
		theDebug->SkipNext();
		( theDebug->CrashBegin( 0, 0, 0 ) << "Streaming from a compressed archive file is not supported" ).CrashDone( 1 );
	}

	m_file->seek( offset, File::START );

	*(AsciiString *)( &m_nameStorage ) = filename;

	return true;
}
#pragma comment(linker, "/alternatename:?convertToRAMFile@File@@UAEPAV1@XZ=??0Coord2D@@QAE@XZ")
