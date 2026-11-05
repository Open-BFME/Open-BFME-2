// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// BFME1 donor game/GameEngine/Source/Common/System/File.cpp (6d943426).
// Target factory RVA 0x006022CF allocates 0x20 bytes and calls the rowed
// MemoryReadFile constructor at 0x00602255. Only that factory is defined here.
#include "../../../Include/Common/File.h"

class MemoryReadFile : public File
{
public:
	virtual bool open( const char *filename, int access = 0 );
	virtual int read( void *buffer, int bytes );
	virtual int write( const void *buffer, int bytes );
	virtual int seek( int bytes, seekMode mode );
	virtual void nextLine( char *buf, int bufSize );
	virtual bool scanInt( int &newInt );
	virtual bool scanReal( float &newReal );
	virtual bool scanString( AsciiString &newString );
	virtual int size( void );
	virtual int position( void );
	virtual char *readEntireAndClose( void );
	virtual File *convertToRAMFile( void );

public:
	MemoryReadFile( char *data, int size );

private:
	char *m_data;			// +0x14
	int m_size;				// +0x18
	int m_pos;				// +0x1c
};

File *createMemoryReadFile( char *data, int size )
{
	if( data == 0 && size != 0 )
	{
		return 0;
	}

	return new MemoryReadFile( data, size );
}

