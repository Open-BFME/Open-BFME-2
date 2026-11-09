// Target facts: retail table 0x0087AB28 holds 18 slots, its constructor 0x00605C91 and destructor 0x00605CA7 install it, and
// the handle at +0x14 goes to the CRT's low-level io. Slot 1 (0x00605CFB) converts a narrow filename to wide and calls through
// slot 17 (0x00605D36), which converts back for File::open's bookkeeping and opens through _wopen.
// Donor fact: the class name and member spellings follow Zero Hour's Common/LocalFile.h, which has no wide overload.
#pragma once

#ifndef __BFME2_LOCALFILE_H_
#define __BFME2_LOCALFILE_H_

#include "File.h"

typedef unsigned short Wide;

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
	virtual bool open( const Wide *filename, int access );

protected:
	int m_handle;			// +0x14, -1 when closed
};

#endif
