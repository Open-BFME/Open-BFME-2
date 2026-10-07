// Opt-in StringClass teardown view. Retained declarations and all other bodies
// from Code/Libraries/Source/WWVegas/WWLib/wwstring.h
// repository header at 5ec1f39a83c557109dc96878953e65e3b991d18e; BFME1 basis revision 6d9434269164392c5ba62aaa7c15a86b5b020d76; input SHA256 6680f5a7e7efc405d988f931967eff9897267e2f69fa5694db2270065465b173.
// Target evidence establishes the teardown binding and39-byte int/bool ctor.
// Other declarations and bodies retain their recorded source basis.
// StringClass, matching the layout and inline bodies of the Generals Zero Hour
// reference (Libraries/Source/WWVegas/WWLib/wwstring.h). StringClass has no vtable
// and a single member (m_Buffer), so this reproduces the object layout exactly.
// RawFileClass only touches the inline members near the top (operator=, ctor, dtor,
// Get_Length, operator[], operator const TCHAR *). The temp-string pool, mutex and
// private helpers below are declared so the out-of-line bodies in wwstring.cpp
// compile and byte-match; the heavyweight WWLib includes (win.h/mutex.h/wwmemlog.h)
// are folded in here as the minimal stand-ins the decomp toolchain can build.
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __WWSTRING_H
#define __WWSTRING_H

#include <string.h>
#include <tchar.h>
#include <stdarg.h>

typedef unsigned short WCHAR;   // see win.h; needed for Copy_Wide's signature

#ifndef WWASSERT
#define WWASSERT(exp)
#endif

// The reference allocates string buffers with W3DNEWARRAY; with no _DEBUG/_INTERNAL
// (release build) it collapses to a plain operator new[], which is what the game emitted.
#ifndef W3DNEWARRAY
#define W3DNEWARRAY new
#endif

// Minimal stand-in for the WWLib mutex.h primitive that Get_String/Free_String lock
// with. In the reference, LockClass's ctor holds an inline asm spin whose labels stop
// MSVC inlining it, so the compiler emits the spin out-of-line and inlines away the
// lock object itself -- every call site becomes `mov ecx,&mutex; call spin`, and the
// dtor a direct `mov [&mutex],0`. Modelling the spin as a fastcall prototype (resolved
// through reverse/symbols.csv to that shared out-of-line body) reproduces exactly that
// codegen; a verbatim asm ctor instead materialises the object and does not match.
#ifndef BFME_FASTCRITICALSECTION_DEFINED
#define BFME_FASTCRITICALSECTION_DEFINED
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mutex.h
class FastCriticalSectionClass
{
	unsigned Flag;

public:
	FastCriticalSectionClass() : Flag(0) {}

	class LockClass
	{
		FastCriticalSectionClass& cs;
		static void __fastcall spin(unsigned* flag);
	public:
		__forceinline LockClass(FastCriticalSectionClass& critical_section) : cs(critical_section)
		{
			spin(&cs.Flag);
		}

		~LockClass()
		{
			cs.Flag=0;
		}

	private:
		LockClass &operator=(const LockClass&);
		LockClass(const LockClass&);
	};

	friend class LockClass;
};
#endif // BFME_FASTCRITICALSECTION_DEFINED

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
class StringClass
{
public:

	StringClass (bool hint_temporary);
	StringClass (int initial_len = 0, bool hint_temporary = false);
	StringClass (const StringClass &string, bool hint_temporary = false);
	StringClass (const TCHAR *string, bool hint_temporary = false);
	~StringClass (void);

	inline const StringClass &operator= (const StringClass &string);
	inline const StringClass &operator= (const TCHAR *string);
#if defined(BFME_WWSTRING_INLINE_CSTR_ASSIGN)
	// Mixed callers retain retail's inline copy at selected sites while the
	// public assignment resolves to the verified 0x000F0E8D worker. The tag
	// preserves inline construction without changing ordinary ctor calls.
	__forceinline const StringClass &bfmeAssignInline(const TCHAR *string);
	enum InlineCopy { COPY_INLINE };
	__forceinline StringClass(const TCHAR *string, bool hint_temporary, InlineCopy);
	enum InlineNativeCopy { COPY_NATIVE };
	__forceinline StringClass(const TCHAR *string, bool hint_temporary, InlineNativeCopy);
#endif

	const StringClass &operator+= (const StringClass &string);
	const StringClass &operator+= (const TCHAR *string);
	const StringClass &operator+= (TCHAR ch);

	friend StringClass operator+ (const StringClass &string1, const StringClass &string2);
	friend StringClass operator+ (const TCHAR *string1, const StringClass &string2);
	friend StringClass operator+ (const StringClass &string1, const TCHAR *string2);

	const TCHAR & operator[] (int index) const;
	TCHAR & operator[] (int index);
	inline operator const TCHAR * (void) const;

	inline int	Get_Length (void) const;
	bool			Is_Empty (void) const;

	int _cdecl  Format (const TCHAR *format, ...);
	int _cdecl  Format_Args (const TCHAR *format, const va_list & arg_list );
	int			Compare (const TCHAR *string) const;
	int			Compare_No_Case (const TCHAR *string) const;
	bool Copy_Wide (const WCHAR *source);

	TCHAR *		Get_Buffer (int new_length);
	TCHAR *		Peek_Buffer (void);
	const TCHAR * Peek_Buffer (void) const;

	void	Release_Resources (void);

private:

	typedef struct _HEADER
	{
		int	allocated_length;
		int	length;
	} HEADER;

	// Note: Don't change these enums without withs checking the Get_String() and Free_String() function!
	enum
	{
		MAX_TEMP_STRING	= 8,
		MAX_TEMP_LEN		= 256-sizeof(_HEADER),
		MAX_TEMP_BYTES		= (MAX_TEMP_LEN * sizeof (TCHAR)) + sizeof (HEADER),
		ALL_TEMP_STRINGS_USED_MASK = 0xff
	};

	void			Get_String (int length, bool is_temp);
	TCHAR *		Allocate_Buffer (int length);
	void			Resize (int size);
	void			Uninitialised_Grow (int length);
	void			Free_String (void);

	inline void	Store_Length (int length);
	inline void	Store_Allocated_Length (int allocated_length);
	inline HEADER * Get_Header (void) const;
	int			Get_Allocated_Length (void) const;

	void			Set_Buffer_And_Allocated_Length (TCHAR *buffer, int length);

	TCHAR *		m_Buffer;

	static TCHAR	m_NullChar;
	static TCHAR *	m_EmptyString;

	static unsigned ReservedMask;
	static char m_TempStrings[];

	static FastCriticalSectionClass m_Mutex;
};

///////////////////////////////////////////////////////////////////
//	operator=
///////////////////////////////////////////////////////////////////
// Opted-in units call the existing 68-byte retail worker at 0x000F0E8D.
// Other units still require the donor inline expansion at verified call sites.
#if !defined(BFME_WWSTRING_NATIVE_CSTR_ASSIGN)
inline const StringClass &
StringClass::operator= (const TCHAR *string)
{
	if (string != 0) {

		int len = _tcslen (string);
		Uninitialised_Grow (len+1);
		Store_Length (len);

		::memcpy (m_Buffer, string, (len + 1) * sizeof (TCHAR));
	}

	return (*this);
}
#endif // BFME_WWSTRING_NATIVE_CSTR_ASSIGN

#if defined(BFME_WWSTRING_INLINE_CSTR_ASSIGN)
// Retain retail inline expansion where an owned caller needs it; the public
// assignment entry point remains the existing byte-verified worker.
__forceinline const StringClass &StringClass::bfmeAssignInline(const TCHAR *string)
{
	if (string != 0) {

		int len = _tcslen (string);
		Uninitialised_Grow (len+1);
		Store_Length (len);

		::memcpy (m_Buffer, string, (len + 1) * sizeof (TCHAR));
	}

	return (*this);
}
#endif

///////////////////////////////////////////////////////////////////
//	StringClass
///////////////////////////////////////////////////////////////////
#if defined(BFME_WWSTRING_INLINE_CSTR_ASSIGN)
__forceinline
StringClass::StringClass (const TCHAR *string, bool hint_temporary, InlineCopy)
	:	m_Buffer (m_EmptyString)
{
	int len=string ? _tcsclen(string) : 0;
	if (hint_temporary || len>0) {
		Get_String (len+1, hint_temporary);
	}

	bfmeAssignInline(string);
	return ;
}
// Retail also inlines the constructor around an out-of-line assignment.
__forceinline
StringClass::StringClass(const TCHAR *string, bool hint_temporary, InlineNativeCopy)
    : m_Buffer(m_EmptyString)
{
    int len=string ? _tcsclen(string) : 0;
    if (hint_temporary || len>0) {
        Get_String(len+1, hint_temporary);
    }
    (*this) = string;
}
#endif

// Public construction uses the verified 72-byte worker at RVA 0x000F0ED1.
#if !defined(BFME_WWSTRING_NATIVE_CSTR_CONSTRUCTOR)
inline
StringClass::StringClass (const TCHAR *string, bool hint_temporary)
	:	m_Buffer (m_EmptyString)
{
	int len=string ? _tcsclen(string) : 0;
	if (hint_temporary || len>0) {
		Get_String (len+1, hint_temporary);
	}

#if defined(BFME_WWSTRING_INLINE_CSTR_CONSTRUCTOR)
	bfmeAssignInline(string);
#else
	(*this) = string;
#endif
	return ;
}
#endif // BFME_WWSTRING_NATIVE_CSTR_CONSTRUCTOR

///////////////////////////////////////////////////////////////////
//	~StringClass
///////////////////////////////////////////////////////////////////
// Retail DX8Wrapper call at0x0006615F targets0x00610A40,
// the existing111-byte Free_String worker; same thiscall receiver and no args.
#pragma comment(linker, "/alternatename:??1StringClass@@QAE@XZ=?Free_String@StringClass@@AAEXXZ")


///////////////////////////////////////////////////////////////////
//	operator const TCHAR *
///////////////////////////////////////////////////////////////////
inline
StringClass::operator const TCHAR * (void) const
{
	return m_Buffer;
}

///////////////////////////////////////////////////////////////////
//	operator[]
///////////////////////////////////////////////////////////////////
inline const TCHAR &
StringClass::operator[] (int index) const
{
	WWASSERT (index >= 0 && index < Get_Length ());
	return m_Buffer[index];
}

///////////////////////////////////////////////////////////////////
//	operator[]
///////////////////////////////////////////////////////////////////
inline TCHAR &
StringClass::operator[] (int index)
{
	WWASSERT (index >= 0 && index < Get_Length ());
	return m_Buffer[index];
}

///////////////////////////////////////////////////////////////////
//	Get_Length
///////////////////////////////////////////////////////////////////
inline int
StringClass::Get_Length (void) const
{
	int length = 0;

	if (m_Buffer != m_EmptyString) {

		//
		//	Read the length from the header
		//
		HEADER *header	= Get_Header ();
		length			= header->length;

		//
		//	Hmmm, a zero length was stored in the header,
		// we better manually get the string length.
		//
		if (length == 0) {
			length = _tcslen (m_Buffer);
			((StringClass *)this)->Store_Length (length);
		}
	}

	return length;
}

///////////////////////////////////////////////////////////////////
//	Get_Buffer
///////////////////////////////////////////////////////////////////
inline TCHAR *
StringClass::Get_Buffer (int new_length)
{
	Uninitialised_Grow (new_length);

	return m_Buffer;
}

///////////////////////////////////////////////////////////////////
//	Get_Allocated_Length
//
//	Return allocated size of the string buffer
///////////////////////////////////////////////////////////////////
inline int
StringClass::Get_Allocated_Length (void) const
{
	int allocated_length = 0;

	//
	//	Read the allocated length from the header
	//
	if (m_Buffer != m_EmptyString) {
		HEADER *header		= Get_Header ();
		allocated_length	= header->allocated_length;
	}

	return allocated_length;
}

///////////////////////////////////////////////////////////////////
// Get_Header
///////////////////////////////////////////////////////////////////
inline StringClass::HEADER *
StringClass::Get_Header (void) const
{
	return reinterpret_cast<HEADER *>(((char *)m_Buffer) - sizeof (StringClass::_HEADER));
}

///////////////////////////////////////////////////////////////////
// Store_Length
///////////////////////////////////////////////////////////////////
inline void
StringClass::Store_Length (int length)
{
	if (m_Buffer != m_EmptyString) {
		HEADER *header		= Get_Header ();
		header->length		= length;
	} else {
		WWASSERT (length == 0);
	}

	return ;
}

///////////////////////////////////////////////////////////////////
// Store_Allocated_Length
///////////////////////////////////////////////////////////////////
inline void
StringClass::Store_Allocated_Length (int allocated_length)
{
	if (m_Buffer != m_EmptyString) {
		HEADER *header					= Get_Header ();
		header->allocated_length	= allocated_length;
	} else {
		WWASSERT (allocated_length == 0);
	}

	return ;
}

///////////////////////////////////////////////////////////////////
//	Set_Buffer_And_Allocated_Length
//
// Set buffer pointer and init size variable. Length is set to 0
// as the contents of the new buffer are not necessarily defined.
///////////////////////////////////////////////////////////////////
inline void
StringClass::Set_Buffer_And_Allocated_Length (TCHAR *buffer, int length)
{
	Free_String ();
	m_Buffer = buffer;

	//
	//	Update the header (if necessary)
	//
	if (m_Buffer != m_EmptyString) {
		Store_Allocated_Length (length);
		Store_Length (0);
	} else {
		WWASSERT (length == 0);
	}

	return ;
}

///////////////////////////////////////////////////////////////////
// Allocate_Buffer
///////////////////////////////////////////////////////////////////
inline TCHAR *
StringClass::Allocate_Buffer (int length)
{
	//
	//	Allocate a buffer that is 'length' characters long, plus the
	// bytes required to hold the header.
	//
	char *buffer = W3DNEWARRAY char[(sizeof (TCHAR) * length) + sizeof (StringClass::_HEADER)];

	//
	//	Fill in the fields of the header
	//
	HEADER *header					= reinterpret_cast<HEADER *>(buffer);
	header->length					= 0;
	header->allocated_length	= length;

	//
	//	Return the buffer as if it was a TCHAR pointer
	//
	return reinterpret_cast<TCHAR *>(buffer + sizeof (StringClass::_HEADER));
}

///////////////////////////////////////////////////////////////////
//	operator=
///////////////////////////////////////////////////////////////////
inline const StringClass &
StringClass::operator= (const StringClass &string)
{
	int len = string.Get_Length();
	Uninitialised_Grow(len+1);
	Store_Length(len);

	::memcpy (m_Buffer, string.m_Buffer, (len+1) * sizeof (TCHAR));
	return (*this);
}

///////////////////////////////////////////////////////////////////
//	StringClass
///////////////////////////////////////////////////////////////////
inline
StringClass::StringClass (bool hint_temporary)
	:	m_Buffer (m_EmptyString)
{
	Get_String (MAX_TEMP_LEN, hint_temporary);
	m_Buffer[0]	= m_NullChar;

	return ;
}

///////////////////////////////////////////////////////////////////
//	StringClass
///////////////////////////////////////////////////////////////////
// Native int/bool ctor0x00065F34 is39B; restore the TU flags after this body.
#pragma optimize("t", off)
#pragma optimize("s", on)
inline
StringClass::StringClass (int initial_len, bool hint_temporary)
	:	m_Buffer (m_EmptyString)
{
	Get_String (initial_len, hint_temporary);
	m_Buffer[0]	= m_NullChar;

	return ;
}
#pragma optimize("", on)

///////////////////////////////////////////////////////////////////
//	StringClass
///////////////////////////////////////////////////////////////////
inline
StringClass::StringClass (const StringClass &string, bool hint_temporary)
	:	m_Buffer (m_EmptyString)
{
	if (hint_temporary || (string.Get_Length()>0)) {
		Get_String (string.Get_Length()+1, hint_temporary);
	}

	(*this) = string;
	return ;
}

///////////////////////////////////////////////////////////////////
//	Is_Empty
///////////////////////////////////////////////////////////////////
inline bool
StringClass::Is_Empty (void) const
{
	return (m_Buffer[0] == m_NullChar);
}

///////////////////////////////////////////////////////////////////
//	Peek_Buffer
///////////////////////////////////////////////////////////////////
inline TCHAR *
StringClass::Peek_Buffer (void)
{
	return m_Buffer;
}

///////////////////////////////////////////////////////////////////
//	Peek_Buffer
///////////////////////////////////////////////////////////////////
inline const TCHAR *
StringClass::Peek_Buffer (void) const
{
	return m_Buffer;
}

///////////////////////////////////////////////////////////////////
//	operator+=
///////////////////////////////////////////////////////////////////
inline const StringClass &
StringClass::operator+= (const TCHAR *string)
{
	WWASSERT (string != NULL);

	int cur_len = Get_Length ();
	int src_len = _tcslen (string);
	int new_len = cur_len + src_len;

	//
	//	Make sure our buffer is large enough to hold the new string
	//
	Resize (new_len + 1);
	Store_Length (new_len);

	//
	//	Copy the new string onto our the end of our existing buffer
	//
	::memcpy (&m_Buffer[cur_len], string, (src_len + 1) * sizeof (TCHAR));
	return (*this);
}

///////////////////////////////////////////////////////////////////
//	operator+=
///////////////////////////////////////////////////////////////////
inline const StringClass &
StringClass::operator+= (TCHAR ch)
{
	int cur_len = Get_Length ();
	Resize (cur_len + 2);

	m_Buffer[cur_len]			= ch;
	m_Buffer[cur_len + 1]	= m_NullChar;

	if (ch != m_NullChar) {
		Store_Length (cur_len + 1);
	}

	return (*this);
}

///////////////////////////////////////////////////////////////////
//	operator+=
///////////////////////////////////////////////////////////////////
inline const StringClass &
StringClass::operator+= (const StringClass &string)
{
	int src_len = string.Get_Length();
	if (src_len > 0) {
		int cur_len = Get_Length ();
		int new_len = cur_len + src_len;

		//
		//	Make sure our buffer is large enough to hold the new string
		//
		Resize (new_len + 1);
		Store_Length (new_len);

		//
		//	Copy the new string onto our the end of our existing buffer
		//
		::memcpy (&m_Buffer[cur_len], (const TCHAR *)string, (src_len + 1) * sizeof (TCHAR));
	}

	return (*this);
}

///////////////////////////////////////////////////////////////////
//	operator+
///////////////////////////////////////////////////////////////////
inline StringClass
operator+ (const StringClass &string1, const StringClass &string2)
{
	StringClass new_string(string1, true);
	new_string += string2;
	return new_string;
}

///////////////////////////////////////////////////////////////////
//	operator+
///////////////////////////////////////////////////////////////////
inline StringClass
operator+ (const TCHAR *string1, const StringClass &string2)
{
#if defined(BFME_WWSTRING_NATIVE_CSTR_CONSTRUCTOR) && defined(BFME_WWSTRING_INLINE_CSTR_ASSIGN)
	StringClass new_string(string1, true, StringClass::COPY_NATIVE);
#else
	StringClass new_string(string1, true);
#endif
	new_string += string2;
	return new_string;
}

///////////////////////////////////////////////////////////////////
//	operator+
///////////////////////////////////////////////////////////////////
inline StringClass
operator+ (const StringClass &string1, const TCHAR *string2)
{
	StringClass new_string(string1, true);
	StringClass new_string2(string2, true);
	new_string += new_string2;
	return new_string;
}


// Grown verbatim from the ZH reference: lean stand-in lacked these; zh TUs
// (mixfile.cpp, widestring.h) call them. Inline, so byte-neutral elsewhere.
inline int
StringClass::Compare (const TCHAR *string) const
{
	return _tcscmp (m_Buffer, string);
}

inline int
StringClass::Compare_No_Case (const TCHAR *string) const
{
	return _tcsicmp (m_Buffer, string);
}

#endif //__WWSTRING_H
