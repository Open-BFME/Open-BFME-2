// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: W3DFileSystem.cpp ////////////////////////////////////////////////////////////////////////
//
// W3D implementation of a file factory.  This replaces the W3D file factory, 
// and uses GDI assets, so that 
// W3D files and targa files are loaded using the GDI file interface.
// Note - this only servers up read only files.
//
// Author: John Ahlquist, Sept 2001
//				 Colin Day, November 2001
//
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////


// for now we maintain old legacy files
// #define MAINTAIN_LEGACY_FILES

#include "Common/Debug.h"
#include "Common/File.h"
#include "Common/FileSystem.h"
#include "Common/GlobalData.h"
#include "Common/MapObject.h"
#include "Common/Registry.h"
#include "W3DDevice/GameClient/W3DFileSystem.h"
// DEFINES ////////////////////////////////////////////////////////////////////////////////////////

#include <io.h>
// Retail calls MSVCR71 _mbscat here (thunk 0x0062988C), not strcat.
extern "C" char *__cdecl _mbscat(char *dest, const char *source);

// BFME's File vtable, which the vendored Zero Hour header does not describe:
// BFME's File is not a MemoryPoolObject, so every slot sits one earlier than
// Common/File.h puts it (read 3, seek 5, size 11 -- the numbering the matched
// File / LocalFile / RAMFile rows prove from their own vtables). Calls through
// m_theFile go through this TU-local view instead of editing the shared header.
class BfmeFileSlots
{
public:
	virtual ~BfmeFileSlots();								// slot 0
	virtual Bool open( const char *filename, Int access );	// slot 1
	virtual void close( void );								// slot 2
	virtual Int read( void *buffer, Int bytes );			// slot 3
	virtual Int write( const void *buffer, Int bytes );		// slot 4
	virtual Int seek( Int bytes, File::seekMode mode );		// slot 5
	virtual void nextLine( char *buf, Int bufSize );		// slot 6
	virtual Bool scanInt( Int &newInt );					// slot 7
	virtual Bool scanReal( Real &newReal );					// slot 8
	virtual Bool scanString( AsciiString &newString );		// slot 9
	virtual Bool print( const char *format, ... );			// slot 10
	virtual Int size( void );								// slot 11
};

// A cast at the call site, not a helper: retail re-reads m_theFile after the
// null test, which the plain member expression gives and a helper call folds.
#define BFME_FILE(file) reinterpret_cast<BfmeFileSlots *>(file)

//-------------------------------------------------------------------------------------------------
/** Game file access.  At present this allows us to access test assets, assets from
	* legacy GDI assets, and the current flat directory access for textures, models etc */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
typedef enum
{
	FILE_TYPE_COMPLETELY_UNKNOWN = 0,	// MBL 08.15.2002 - compile error with FILE_TYPE_UNKNOWN, is constant
	FILE_TYPE_W3D,
	FILE_TYPE_TGA,
	FILE_TYPE_DDS,
} GameFileType;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
GameFileClass::GameFileClass( char const *filename )
{

	m_fileExists = FALSE;
	m_theFile = NULL;
	m_filePath[ 0 ] = 0;
	m_filename[0] = 0;

	if( filename ) 
		Set_Name( filename );

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
GameFileClass::GameFileClass( void )
{

	m_fileExists = FALSE;
	m_theFile = NULL;
	m_filePath[ 0 ] = 0;
	m_filename[ 0 ] = 0;

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
GameFileClass::~GameFileClass()
{

	Close();

}

//-------------------------------------------------------------------------------------------------
/** Gets the file name */
//-------------------------------------------------------------------------------------------------
char const * GameFileClass::File_Name( void ) const
{

	return m_filename;

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
inline static Bool isImageFileType( GameFileType fileType )
{
	return (fileType == FILE_TYPE_TGA || fileType == FILE_TYPE_DDS);
}

//-------------------------------------------------------------------------------------------------
/** 
	Sets the file name, and finds the GDI asset if present. 


	Well, that is the worst comment ever for the most important function there is.
	Everything comes through this.  This builds the directory and tests for the file
	in several different places.  

	First we look in Language subfolders so that our Perforce	build can handle files that have 
	been localized but were in Generals.  

	Then we do the normal TheFileSystem lookup.  In there it does LocalFile (Art/Textures) then it does
	big files (which internally are also Art/Textures).  
	
	Finally we try UserData.
*/
//-------------------------------------------------------------------------------------------------
// GameFileClass::Set_Name is defined in GameFileClassSetName.cpp.

//-------------------------------------------------------------------------------------------------
/** If we found a gdi asset, the file is available. */
//-------------------------------------------------------------------------------------------------
bool GameFileClass::Is_Available( int forced ) 
{

	// not maintaining any GDF compatibility, all files should be where the m_filePath says
	return m_fileExists;

}

//-------------------------------------------------------------------------------------------------
/** Is the file open. */
//-------------------------------------------------------------------------------------------------
bool GameFileClass::Is_Open(void) const
{
	return m_theFile != NULL;
}

//-------------------------------------------------------------------------------------------------
/** Open the named file. */
//-------------------------------------------------------------------------------------------------
int  GameFileClass::Open(char const *filename, int rights) 
{
	Set_Name(filename);
	if (Is_Available(false)) {
		return(Open(rights));
	}
	return(false);
}

//-------------------------------------------------------------------------------------------------
/** Open the file using the current file name. */
//-------------------------------------------------------------------------------------------------
// GameFileClass::Open: defined in GameFileClassOpen.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** Read. */
//-------------------------------------------------------------------------------------------------
int GameFileClass::Read(void *buffer, int len) 
{
	if (m_theFile) {
		return BFME_FILE(m_theFile)->read(buffer, len);
	}
	return(0);
}

//-------------------------------------------------------------------------------------------------
/** Seek. */
//-------------------------------------------------------------------------------------------------
int GameFileClass::Seek(int pos, int dir) 
{
	File::seekMode mode = File::CURRENT;
	switch (dir) {
		default:
		case SEEK_CUR: mode = File::CURRENT; break;
		case SEEK_SET: mode = File::START; break;
		case SEEK_END: mode = File::END; break;
	}
	if (m_theFile) {
		return BFME_FILE(m_theFile)->seek(pos, mode);
	}
	return 0xFFFFFFFF;
}

//-------------------------------------------------------------------------------------------------
/** Size. */
//-------------------------------------------------------------------------------------------------
int GameFileClass::Size(void) 
{
	if (m_theFile) {
		return BFME_FILE(m_theFile)->size();
	}
	return 0xFFFFFFFF;
}

//-------------------------------------------------------------------------------------------------
/** Write. */
//-------------------------------------------------------------------------------------------------
// ?Write@GameFileClass@@UAEHPBXH@Z present-unmatched
int GameFileClass::Write(void const *buffer, Int len) 
{
#ifdef _DEBUG
#endif
	return(0);
}

//-------------------------------------------------------------------------------------------------
/** Close. */
//-------------------------------------------------------------------------------------------------
void GameFileClass::Close(void) 
{
	if (m_theFile) {
		// BFME's File declares one virtual fewer ahead of close(): retail
		// dispatches it through [vtbl+8], where the vendored header puts
		// close() at [vtbl+0xC]. Route the raw slot through a
		// pointer-to-member cast -- that keeps __thiscall without naming the
		// nonstandard keyword, and without touching Common/file.h, which
		// every other matched row in the tree compiles against.
		struct FileCloseThunk { void Call(); };
		typedef void (FileCloseThunk::*FileCloseFn)();
		void **vtbl = *reinterpret_cast<void ***>(m_theFile);
		union { void *asVoid; FileCloseFn asMember; } fnCast;
		fnCast.asVoid = vtbl[2];
		(reinterpret_cast<FileCloseThunk *>(m_theFile)->*fnCast.asMember)();
		m_theFile = NULL;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// W3DFileSystem Class ////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
extern W3DFileSystem *TheW3DFileSystem = NULL;

//-------------------------------------------------------------------------------------------------
/** Constructor.  Creating an instance of this class overrices the default 
W3D file factory.  */
//-------------------------------------------------------------------------------------------------
// ??0W3DFileSystem@@QAE@XZ
W3DFileSystem::W3DFileSystem(void)
{
	_TheFileFactory = this; // override the w3d file factory.
}

//-------------------------------------------------------------------------------------------------
/** Destructor.  This removes the W3D file factory, so shouldn't be done until
after W3D is shutdown.  */
//-------------------------------------------------------------------------------------------------
W3DFileSystem::~W3DFileSystem(void)
{
	_TheFileFactory = NULL; // remove the w3d file factory.
}

//-------------------------------------------------------------------------------------------------
/** Gets a file with the specified filename. */
//-------------------------------------------------------------------------------------------------
FileClass * W3DFileSystem::Get_File( char const *filename )
{
	return NEW GameFileClass( filename );	// poolify
}

//-------------------------------------------------------------------------------------------------
/** Releases a file returned by Get_File. */
//-------------------------------------------------------------------------------------------------
// Slot 2 of the W3DFileSystem vtable 0x007C67D0. Retail destroys through the
// virtual destructor with a zero flag and then frees with the global operator
// delete -- the ::delete form, as the matched File::close spells it.
void W3DFileSystem::Return_File( FileClass *file )
{
	::delete file;
}

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:_strcat=?ji_0062988c@@YAXXZ")
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
