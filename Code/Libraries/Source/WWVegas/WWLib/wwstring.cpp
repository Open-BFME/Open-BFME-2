// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WWLib/wwstring.cpp); this unit had no counterpart under Code/.
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WWSaveLoad                                                   *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwlib/wwstring.cpp              $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 12/13/01 10:48p                                             $*
 *                                                                                             *
 *                    $Revision:: 17                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// BFME tags its allocations.  StringClass::Resize at 0x00610C70 reaches the
// buffer allocator as `push 0x737472 / push eax / call 0x000B3FC0` -- two
// arguments, the size and a four-byte tag that reads "rts" -- where the Zero
// Hour W3DNEWARRAY passes the size alone.  So the array operator this unit
// wants takes a tag, and Allocate_Buffer (inline in wwstring.h) has to be
// compiled against it.
#include "always.h"
#undef W3DNEWARRAY
void * __cdecl operator new[](unsigned int size, unsigned int tag);
#define W3DNEWARRAY new(0x737472u)

#include "wwstring.h"
#include "win.h"
#include "wwmemlog.h"
#include "mutex.h"
#include <stdio.h>

// BFME's ARRAY operators forward to the scalar ones: always.h declares
// operator new[]/delete[] and defines neither, so an inline forwarder is folded
// away at the call site and array new/delete reach ??2@YAPAXI@Z (0x0002FDA0)
// and ??3@YAXPAX@Z (0x0002FD60) rather than ??_U (0x0002FDE0) / ??_V
// (0x0002FD80).  Kept here only because every row this unit already holds still
// byte-verifies with it.
inline void * __cdecl operator new[](size_t s) { return ::operator new(s); }
inline void __cdecl operator delete[](void * p) { ::operator delete(p); }


///////////////////////////////////////////////////////////////////
//	Static member initialzation
///////////////////////////////////////////////////////////////////

FastCriticalSectionClass StringClass::m_Mutex;

TCHAR		StringClass::m_NullChar					= 0;
TCHAR *	StringClass::m_EmptyString				= &m_NullChar;

//
// A trick to optimize strings that are allocated from the stack and used only temporarily
//
// For alignment reasons we need twice as large block...
char StringClass::m_TempStrings[(StringClass::MAX_TEMP_STRING*2)*StringClass::MAX_TEMP_BYTES];

unsigned StringClass::ReservedMask=0;

///////////////////////////////////////////////////////////////////
//
//	Get_String
//
///////////////////////////////////////////////////////////////////
void
StringClass::Get_String (int length, bool is_temp)
{
	WWMEMLOG(MEM_STRINGS);

	if (!is_temp && length == 0) {
		m_Buffer = m_EmptyString;
		return;
	}

	TCHAR *string = NULL;

	//
	//	Should we attempt to use a temp buffer for this string?
	//
	if (is_temp && length <= MAX_TEMP_LEN && ReservedMask!=ALL_TEMP_STRINGS_USED_MASK) {

		//
		//	Make sure no one else is requesting a temp pointer
		// at the same time we are. There is a slight possibility that another
		// thread stole the last available buffer in between the if sentence and
		// the mutex lock, but that is a feature by design and doesn't cause
		// anything bad to happen.
		//
		FastCriticalSectionClass::LockClass m(m_Mutex);

		//
		//	Try to find an available temporary buffer
		//
		// TODO: Don't loop, there are better ways
		unsigned mask=1;
		for (int index = 0; index < MAX_TEMP_STRING; index ++, mask<<=1) {
			unsigned mask=1<<index;
			if (!(ReservedMask&mask)) {
				ReservedMask|=mask;
				
				//
				//	Grab this unused buffer for our string
				//
				unsigned temp_string=reinterpret_cast<unsigned>(m_TempStrings);
				temp_string+=MAX_TEMP_BYTES*MAX_TEMP_STRING;
				temp_string&=~(MAX_TEMP_BYTES*MAX_TEMP_STRING-1);
				temp_string+=index*MAX_TEMP_BYTES;
				temp_string+=sizeof(_HEADER);	// The buffer contains header as well, and it needs to be at the start
				string=reinterpret_cast<char*>(temp_string);

				Set_Buffer_And_Allocated_Length (string, MAX_TEMP_LEN);
				break;
			}
		}
	}

	if (string == NULL) {
		
		//
		//	Allocate a new string as necessary
		//
		if (length > 0) {
			Set_Buffer_And_Allocated_Length (Allocate_Buffer (length), length);
		} else {
			Free_String ();
		}
	}
}


///////////////////////////////////////////////////////////////////
//
//	Resize
//
///////////////////////////////////////////////////////////////////
void
StringClass::Resize (int new_len)
{
	WWMEMLOG(MEM_STRINGS);

	int allocated_len = Get_Allocated_Length ();
	if (new_len > allocated_len) {

		//
		//	Allocate the new buffer and copy the contents of our current
		// string.
		//
		TCHAR *new_buffer = Allocate_Buffer (new_len);
		_tcscpy (new_buffer, m_Buffer);

		//
		//	Switch to the new buffer
		//
		Set_Buffer_And_Allocated_Length (new_buffer, new_len);
	}

	return ;
}


///////////////////////////////////////////////////////////////////
//
//	Uninitialised_Grow
//
///////////////////////////////////////////////////////////////////
void
StringClass::Uninitialised_Grow (int new_len)
{
	WWMEMLOG(MEM_STRINGS);

	int allocated_len = Get_Allocated_Length ();
	if (new_len > allocated_len) {
		
		//
		//	Switch to a newly allocated buffer
		//
		TCHAR *new_buffer = Allocate_Buffer (new_len);
		Set_Buffer_And_Allocated_Length (new_buffer, new_len);	
	}
		
	//
	// Whenever this function is called, clear the cached length 
	//
	Store_Length (0);
	return ;
}


///////////////////////////////////////////////////////////////////
//
//	Uninitialised_Grow
//
///////////////////////////////////////////////////////////////////
void
StringClass::Free_String (void)
{
	if (m_Buffer != m_EmptyString) {

		unsigned buffer_base=reinterpret_cast<unsigned>(m_Buffer-sizeof (StringClass::_HEADER));
		unsigned temp_base=reinterpret_cast<unsigned>(m_TempStrings+MAX_TEMP_BYTES*MAX_TEMP_STRING);

		if ((buffer_base>>11)==(temp_base>>11)) {
			m_Buffer[0] = 0;

			//
			//	Make sure no one else is changing the reserved mask
			// at the same time we are.
			//
			FastCriticalSectionClass::LockClass m(m_Mutex);

			unsigned index=(buffer_base/MAX_TEMP_BYTES)&(MAX_TEMP_STRING-1);
			unsigned mask=1<<index;
			ReservedMask&=~mask;
		}
		else {

			//
			//	String wasn't temporary, so free the memory
			//
			char *buffer = ((char *)m_Buffer) - sizeof (StringClass::_HEADER);
			delete [] buffer;
		}

		//
		//	Reset the buffer
		//
		m_Buffer = m_EmptyString;
	}

	return ;
}


///////////////////////////////////////////////////////////////////
//
//	Format
//
///////////////////////////////////////////////////////////////////
int _cdecl
StringClass::Format_Args (const TCHAR *format, const va_list & arg_list )
{
	//
	// Make a guess at the maximum length of the resulting string
	//
	TCHAR temp_buffer[512] = { 0 };
	int retval = 0;

	//
	//	Format the string
	//
	#ifdef _UNICODE
		retval = _vsnwprintf (temp_buffer, 512, format, arg_list);
	#else
		retval = _vsnprintf (temp_buffer, 512, format, arg_list);
	#endif
	
	//
	//	Copy the string into our buffer
	//	
	(*this) = temp_buffer;

	return retval;
}


///////////////////////////////////////////////////////////////////
//
//	Format
//
///////////////////////////////////////////////////////////////////
int _cdecl
StringClass::Format (const TCHAR *format, ...)
{
	va_list arg_list;
	va_start (arg_list, format);

	//
	// Make a guess at the maximum length of the resulting string
	//
	TCHAR temp_buffer[512] = { 0 };
	int retval = 0;

	//
	//	Format the string
	//
	#ifdef _UNICODE
		retval = _vsnwprintf (temp_buffer, 512, format, arg_list);
	#else
		retval = _vsnprintf (temp_buffer, 512, format, arg_list);
	#endif
	
	//
	//	Copy the string into our buffer
	//	
	(*this) = temp_buffer;

	va_end (arg_list);
	return retval;
}


///////////////////////////////////////////////////////////////////
//
//	Release_Resources
//
///////////////////////////////////////////////////////////////////
void
StringClass::Release_Resources (void)
{
	Free_String();
}


///////////////////////////////////////////////////////////////////
// Copy_Wide
//
///////////////////////////////////////////////////////////////////
bool StringClass::Copy_Wide (const WCHAR *source)
{
	if (source != NULL) {

		int  length;
		BOOL unmapped;
			
		length = WideCharToMultiByte (CP_ACP, 0 , source, -1, NULL, 0, NULL, &unmapped);
		if (length > 0) {

			// Convert.
			WideCharToMultiByte (CP_ACP, 0, source, -1, Get_Buffer (length), length, NULL, NULL);

			// Update length.
			Store_Length (length - 1);
		}

		// Were all characters successfully mapped?
		return (!unmapped);
	}

	// Failure.
	return (false);
}