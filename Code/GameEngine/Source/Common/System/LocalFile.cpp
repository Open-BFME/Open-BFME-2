// cl: /O1 /DNDEBUG /MD /EHsc /G7
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

// The CRT low-level io family, /MD, so dllimport -- retail reaches all three
// through the IAT (ds:0x135936C, ds:0x1359300, ds:0x1359320) rather than a
// direct call, which is exactly what an import stub gives.
#define NULL 0

// The scanner owns a real AsciiString temporary.  Keep this ABI shim local to
// the TU: its one data pointer is the retail object layout, while concat and
// releaseBuffer remain the shared out-of-line StringBase bodies.
template <typename T> class StringBase
{
    friend class AsciiString;

private:
    struct Header
    {
        int refCount;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;

    StringBase() : m_data(0) {}
    void releaseBuffer();

public:
    void concat(const T *text, int length);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	~AsciiString() { releaseBuffer(); }

	void clear();
	AsciiString &operator=(const AsciiString &other);

	void concat(const char *text, int length)
	{
		StringBase<char>::concat(text, length);
	}

	void concat(char value)
	{
		char text[2];
		text[0] = value;
		StringBase<char>::concat(text, 1);
	}

	const char *str() const
	{
		return m_data ? m_data->data : "";
	}
};

extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);
extern "C" __declspec(dllimport) double __cdecl atof(const char *text);
extern "C" __declspec(dllimport) int __cdecl isspace(int c);

extern "C" __declspec(dllimport) int __cdecl _write(int fd, const void *buffer, unsigned int count);
extern "C" __declspec(dllimport) long __cdecl _lseek(int fd, long offset, int origin);
extern "C" __declspec(dllimport) int __cdecl _read(int fd, void *buffer, unsigned int count);
extern "C" __declspec(dllimport) int __cdecl _close(int fd);
extern "C" __declspec(dllimport) int __cdecl _open(const char *filename, int oflag, ...);
extern "C" __declspec(dllimport) int __cdecl _wopen(const unsigned short *filename, int oflag, ...);

// Wide filename adapter, retail 0x002FB30: UTF16-to-UTF8 through
// WideCharToMultiByte (CP_UTF8). Rowed in Utf8Conversions.cpp; the G spelling
// matches that row so this TU resolves it with no pin.
typedef unsigned short Wide;
int BFME2WideToUtf8(const Wide *source, int count, char *output, int capacity);
int BFME2Utf8ToWide(const char *source, int count, Wide *output, int capacity);

// <fcntl.h> / <sys/stat.h>, spelled out so this TU pulls in no CRT headers.
#define _O_APPEND	0x0008
#define _O_CREAT	0x0100
#define _O_TRUNC	0x0200
#define _O_TEXT		0x4000
#define _O_BINARY	0x8000
#define _O_RDONLY	0x0000
#define _O_WRONLY	0x0001
#define _O_RDWR		0x0002
#define _S_IREAD	0x0100
#define _S_IWRITE	0x0080

// For a POD element type with no explicit `operator new[]` declaration visible,
// this MSVC 7.1 build folds `new T[n]` down to the scalar ??2 as a size-cookie-
// avoidance optimization. Retail's readEntireAndClose calls the array form
// (0x00881F70), so the declaration has to be visible here the way <new> makes
// it visible in the real project TUs.
void *operator new[](unsigned int);
void operator delete[](void *block);

class File
{
public:
	enum access
	{
		READ		= 0x0001,
		WRITE		= 0x0002,
		APPEND		= 0x0004,
		// File.cpp's copy of this enum stops at the bits File::open itself
		// tests, so it has no name for 0x8. LocalFile::open supplies it: the
		// bit that turns into _O_CREAT is CREATE, at Zero Hour's value.
		CREATE		= 0x0008,
		TRUNCATE	= 0x0010,
		TEXT		= 0x0020,
		BINARY		= 0x0040,
		STREAMING	= 0x0100,
		READWRITE	= (READ | WRITE)		// retail: and edx,3 / cmp dl,3
	};

	enum seekMode { START, CURRENT, END };

	File();
	bool eof( void );
	virtual ~File();										// slot 0
	virtual bool open( const char *filename, int access = 0 );	// slot 1
	virtual void close( void );								// slot 2
	virtual int read( void *buffer, int bytes );			// slot 3
	virtual int write( const void *buffer, int bytes );		// slot 4
	virtual int seek( int pos, seekMode mode );				// slot 5
	virtual void nextLine( char *buf, int bufSize );		// slot 6
	virtual bool scanInt( int &newInt );					// slot 7
	virtual bool scanReal( float &newReal );				// slot 8
	virtual bool scanString( AsciiString &newString );				// slot 9
	virtual bool print( const char *format, ... );			// slot 10
	virtual int size( void );								// slot 11
	virtual int position( void );							// slot 12
	virtual char *readEntireAndClose( void );				// slot 13
	virtual File *convertToRAMFile( void );					// slot 14
	virtual void lock( void );								// slot 15
	virtual void unlock( void );							// slot 16

	void deleteOnClose( void )
	{
		m_deleteOnClose = true;
	}

	void deleteInstance( void )
	{
		delete this;
	}

protected:
	void *m_nameStr;		// +0x04  AsciiString, untouched here
	int m_access;			// +0x08
	bool m_open;			// +0x0c
	bool m_deleteOnClose;	// +0x0d
	void *m_mutex;			// +0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LocalFile.h
class LocalFile : public File
{
public:
	virtual ~LocalFile();
	virtual bool open( const char *filename, int access );
	virtual void close( void );
	virtual int read( void *buffer, int bytes );
	virtual int write( const void *buffer, int bytes );
	virtual int seek( int pos, seekMode mode );
	virtual void nextLine( char *buf, int bufSize );
	virtual bool scanInt( int &newInt );
	virtual bool scanReal( float &newReal );
	virtual bool scanString( AsciiString &newString );
	virtual char *readEntireAndClose( void );
	virtual File *convertToRAMFile( void );
	// Retail slot 17 (0x44) is the wide-filename worker (0x00605D36, rowed as
	// narrow-spelled open). Declared-only so gap's virtual call emits
	// call [eax+0x44] with no extra row.
	virtual bool wideOpenStub( const Wide *filename, int access );
	// Retail slot 1 (0x04) narrow adapter 0x00605CFB 59B: Utf8->Wide then
	// slot 17. Honest address name: vtable proves LocalFile slot 1, ret 8
	// plus Utf8ToWide call proves (const char*,int)->bool.
	virtual bool rva00605CFB( const char *filename, int access );

protected:
	int m_handle;			// +0x14, -1 when closed
};

class RAMFile : public File
{
public:
	RAMFile();
	virtual ~RAMFile();
	virtual bool open( File *file );
	virtual void close( void );
	virtual bool copyDataToFile( File *file );

protected:
	char *m_data;
	int m_pos;
	int m_size;
};

class StreamingArchiveFile : public RAMFile
{
public:
	virtual ~StreamingArchiveFile();
	virtual bool openFromArchive(File *archiveFile, const AsciiString &filename, int offset, int size);

protected:
	File *m_file;		// +0x20
	int m_startingPos;	// +0x24
	int m_curPos;		// +0x28
};

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22();
	virtual void SetCrashAddress(void *returnAddress, int set);
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
};

extern Debug *theDebug;
extern void _bfme_debugRecordCallsite(int kind);

// The running count of open local files, retail 0x0134D064. Bumped once per
// successful _open and never read here, so only the increment is visible.
static int s_totalOpen = 0;

// ??1LocalFile@@UAE@XZ
LocalFile::~LocalFile()
{
	if( m_handle != -1 )
	{
		_close( m_handle );
		m_handle = -1;
		--s_totalOpen;
	}

	File::close();

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

// Closes the current file if it is open. Must be called once per successful
// LocalFile::open.
//
// Left unclaimed on purpose. The body is a bare tail jump to File::close, so it
// compiles to the same five bytes an incremental-link thunk does, and the
// address the vtable gives (slot 2, retail 0x009D2540) is already carried by
// ?j_009d2540@@YAXXZ in Code/gen_small/gthunks_086.cpp -- which does jump to
// File::close at 0x009CB880, so the two claims are indistinguishable by bytes.
// Repointing it would orphan that generated definition; the row is worth one
// function and the retraction is a separate commit's work.
// ?close@LocalFile@@UAEXXZ present-unmatched
void LocalFile::close( void )
{
	File::close();
}

// ?convertToRAMFile@LocalFile@@UAEPAVFile@@XZ
// ?convertToRAMFile@LocalFile@@UAEPAVFile@@XZ present-unmatched
File *LocalFile::convertToRAMFile( void )
{
	RAMFile *ramFile = new RAMFile;
	if( ramFile->open( this ) )
	{
		if( m_deleteOnClose )
		{
			ramFile->deleteOnClose();
			close();
		}
		else
		{
			close();
			deleteInstance();
		}
		return ramFile;
	}
	else
	{
		ramFile->close();
		ramFile->deleteInstance();
		return this;
	}
}

// ?read@LocalFile@@UAEHPAXH@Z
int LocalFile::read( void *buffer, int bytes )
{
	if( !m_open )
	{
		return -1;
	}

	if (buffer == NULL)
	{
		_lseek(m_handle, bytes, 1 /* SEEK_CUR */);
		return bytes;
	}

	int ret = _read( m_handle, buffer, bytes );

	return ret;
}

// ?open@LocalFile@@UAE_NPBDH@Z
// Opens a file using the standard C open() call. Access flags are mapped to the
// appropriate open flags. Returns true if the file was opened successfully.
// Retail takes a wide filename: it converts to narrow for File::open's
// bookkeeping, then opens wide through _wopen. The TU keeps the narrow
// override spelling (slot 1, same as File::open) and casts at the two wide
// call sites, which fold to zero bytes.
bool LocalFile::open( const char *filename, int access )
{
	char narrowPath[0x410];

	BFME2WideToUtf8( (const Wide *)filename, -1, narrowPath, 0x410 );

	if( !File::open( narrowPath, access) )
	{
		return false;
	}

	/* here we translate WSYS file access to the std C equivalent */

	int flags = 0;

	if (m_access & CREATE)
	{
		flags |= _O_CREAT;
	}
	if (m_access & TRUNCATE)
	{
		flags |= _O_TRUNC;
	}
	if (m_access & APPEND)
	{
		flags |= _O_APPEND;
	}
	if (m_access & TEXT)
	{
		flags |= _O_TEXT;
	}
	if (m_access & BINARY)
	{
		flags |= _O_BINARY;
	}

	if((m_access & READWRITE )== READWRITE )
	{
		flags |= _O_RDWR;
	}
	else if(m_access & WRITE)
	{
		flags |= _O_WRONLY;
	}
	else
	{
		flags |= _O_RDONLY;
	}

	m_handle = _wopen( (const Wide *)filename, flags , _S_IREAD | _S_IWRITE);

	if( m_handle == -1 )
	{
		goto error;
	}

	++s_totalOpen;
	if ( m_access & APPEND )
	{
		if ( seek ( 0, END ) < 0 )
		{
			goto error;
		}
	}

	return true;

error:

	close();

	return false;
}

// ?write@LocalFile@@UAEHPBXH@Z
int LocalFile::write( const void *buffer, int bytes )
{

	if( !m_open || !buffer )
	{
		return -1;
	}

	int ret = _write( m_handle, buffer, bytes );

	return ret;
}

// ?seek@LocalFile@@UAEHHW4seekMode@File@@@Z
int LocalFile::seek( int pos, seekMode mode )
{
	int lmode;

	switch( mode )
	{
		case START:
			lmode = 0;			// SEEK_SET
			break;
		case CURRENT:
			lmode = 1;			// SEEK_CUR
			break;
		case END:
			lmode = 2;			// SEEK_END
			break;
		default:
			// bad seek mode
			return -1;
	}

	int ret = _lseek( m_handle, pos, lmode );

	return ret;
}

// ?readEntireAndClose@LocalFile@@UAEPADXZ
// Allocate a buffer large enough to hold the entire file, read the entire file
// into the buffer, then close the file. The buffer is owned by the caller, who
// is responsible for freeing it (via delete[]).
//
// NEW here is the plain global array operator new (retail 0x00881F70, a direct
// rel32), not the W3D pool allocator -- so it is spelled `::new`.
char *LocalFile::readEntireAndClose( void )
{
	unsigned int fileSize = size();
	char *buffer = ::new char[fileSize];

	read(buffer, fileSize);

	close();

	return buffer;
}

// ?nextLine@LocalFile@@UAEXPADH@Z
// scans to the first character after a new-line or at EOF
void LocalFile::nextLine( char *buf, int bufSize )
{
	char c = 0;
	int val;
	int i = 0;

	// seek to the next new-line.
	do {
		if ((buf == NULL) || (i >= (bufSize-1))) {
			val = _read(m_handle, &c, 1);
		} else {
			val = _read(m_handle, buf + i, 1);
			c = buf[i];
		}
		++i;
	} while ((val != 0) && (c != '\n'));

	if (buf != NULL) {
		if (i < bufSize) {
			buf[i] = 0;
		} else {
			buf[bufSize] = 0;
		}
	}
}

// ?scanInt@LocalFile@@UAE_NAAH@Z
bool LocalFile::scanInt( int &newInt )
{
	newInt = 0;
	AsciiString tempstr;
	char c;
	int val;

	do {
		val = _read( m_handle, &c, 1 );
	} while ((val != 0) && (((c < '0') || (c > '9')) && (c != '-')));

	if (val == 0) {
		return false;
	}

	do {
		char value[2];
		value[0] = c;
		tempstr.concat( value, 1 );
		val = _read( m_handle, &c, 1 );
	} while ((val != 0) && (c >= '0') && (c <= '9'));

	if (val != 0) {
		_lseek( m_handle, -1, 1 /* SEEK_CUR */ );
	}

	newInt = atoi( tempstr.str() );
	return true;
}

// ?scanString@LocalFile@@UAE_NAAVAsciiString@@@Z
bool LocalFile::scanString( AsciiString &newString )
{
	char c;
	int val;

	newString.clear();

	// skip the preceding whitespace
	do {
		val = _read( m_handle, &c, 1 );
	} while ((val != 0) && (isspace(c)));

	if (val == 0) {
		return false;
	}

	do {
		char value[2];
		value[0] = c;
		newString.concat( value, 1 );
		val = _read( m_handle, &c, 1 );
	} while ((val != 0) && (!isspace(c)));

	if (val != 0) {
		_lseek( m_handle, -1, 1 /* SEEK_CUR */ );
	}

	return true;
}

// ?scanReal@LocalFile@@UAE_NAAM@Z
// ?scanReal@LocalFile@@UAE_NAAM@Z present-unmatched
bool LocalFile::scanReal( float &newReal )
{
	newReal = 0.0f;
	AsciiString tempstr;
	char c;
	int val;
	bool sawDec = false;

	do {
		val = _read( m_handle, &c, 1 );
	} while ((val != 0) && (((c < '0') || (c > '9')) &&
		(c != '-') && (c != '.')));

	if (val == 0) {
		return false;
	}

	do {
		tempstr.concat( c );
		if (c == '.') {
			sawDec = true;
		}
		val = _read( m_handle, &c, 1 );
	} while ((val != 0) && (((c >= '0') && (c <= '9')) ||
		((c == '.') && !sawDec)));

	if (val != 0) {
		_lseek( m_handle, -1, 1 /* SEEK_CUR */ );
	}

	newReal = (float)atof( tempstr.str() );
	return true;
}

// ?rva00605CFB@LocalFile@@UAE_NPBDH@Z @ 0x00605CFB (59B): narrow-to-wide open
// adapter. Retail converts the narrow filename to a 260-wide stack buffer
// via BFME2Utf8ToWide then tail-calls slot 17 (the wide worker rowed as
// ?open@LocalFile). Vtable 0x0087AB28 slot 1 proves LocalFile; ret 8 plus the
// Utf8ToWide call proves (const char*,int)->bool.
bool LocalFile::rva00605CFB( const char *filename, int access )
{
	Wide widePath[0x104];

	BFME2Utf8ToWide( filename, -1, widePath, 0x104 );

	return wideOpenStub( widePath, access );
}

// ?close@RAMFile@@UAEXXZ @ 0x00605547 (29B): ZH RAMFile::close verbatim.
// If m_data is set delete[] it and null it then tail-jump to File::close.
// Vtable 0x0087AA00 slot 2 is the File-family close slot; the delete-zero
// plus File::close tail match the ZH donor exactly. Explicit vector-delete
// call: delete[] on char* folds to scalar ??3 here but retail calls ??_V.
void RAMFile::close( void )
{
	if( m_data )
	{
		::operator delete[]( m_data );
		m_data = NULL;
	}

	File::close();
}

// ?copyDataToFile@RAMFile@@UAE_NPAVFile@@@Z, retail 0x0060565E, 36 bytes.
// Slot 19 (offset 0x4C) of vtable 0x0087AA00; Win32BIGFileOpenArchived donor
// says openFromArchive/copyDataToFile land on 0x48/0x4C. Writes m_data/m_size
// through the File write slot (call [eax+0x10]) and returns (eax == m_size).
// Null file returns false. The if-return-false form folds to cmp/sete;
// a direct return of == uses sub/neg/sbb/inc instead.
bool RAMFile::copyDataToFile( File *file )
{
	if( !file )
	{
		return false;
	}

	if( file->write( m_data, m_size ) != m_size )
	{
		return false;
	}

	return true;
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

	*(AsciiString *)( &m_nameStr ) = filename;

	return true;
}
