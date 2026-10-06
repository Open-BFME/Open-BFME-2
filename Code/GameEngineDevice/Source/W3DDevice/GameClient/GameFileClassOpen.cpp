// cl: /DNDEBUG /MD /EHsc
// ?Open@GameFileClass@@UAEHH@Z, retail 0x000783F8, 49 bytes: slot 7 of the
// GameFileClass vtable 0x007C6788, where MSVC groups the two Zero Hour Open
// overloads in reverse declaration order (slot 8 is the rowed
// Open(const char *, int), which calls this one).
//
// Zero Hour's GameFileClass::Open(int) verbatim, in its own unit because it
// opens through BFME 2's three-argument FileSystem::openFile (rowed at
// 0x00600C34, third argument 0), which the vendored Common/FileSystem.h that
// W3DFileSystem.cpp compiles against cannot declare. Layout is Zero Hour's:
// m_theFile +0x04, m_fileExists +0x08, m_filePath +0x09.

class File
{
public:
	enum
	{
		READ	= 0x0001,
		BINARY	= 0x0040
	};
};

class FileSystem
{
public:
	File *openFile( const char *filename, int access, int flags );
};

extern FileSystem *TheFileSystem;

class FileClass
{
public:
	enum { READ = 1, WRITE = 2 };
	virtual ~FileClass();
};

class GameFileClass : public FileClass
{
public:
	virtual int Open( int rights = READ );

protected:
	File *m_theFile;
	bool m_fileExists;
	char m_filePath[ 260 ];
	char m_filename[ 260 ];
};

int GameFileClass::Open( int rights )
{
	if( rights != READ )
	{
		return(false);
	}

	// just open up the file in m_filePath
	m_theFile = TheFileSystem->openFile( m_filePath, File::READ | File::BINARY, 0 );

	return (m_theFile != 0);
}
