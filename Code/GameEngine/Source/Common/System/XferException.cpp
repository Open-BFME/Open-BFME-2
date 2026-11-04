// cl: /DNDEBUG /MD
// XferException: the object every Xfer failure throws. Retail's throw
// information for it (__TI1?AVXferException@@ at VA 0x00CFFD18) names the
// destructor at 0x0002BD30 and, through its one catchable type, the copy
// constructor at 0x000588C5; that copy constructor nulls the text and
// assigns through operator= at 0x0002F6D6. The (tag, format, ...)
// constructor is the formatter rowed as _bfmeFormatText at 0x0060C36E, and
// the destructor folds with INIException's: both delete[] the text at +0.
// Retail calls _mbscpy through the import thunk at 0x00629176.
#define _CRTIMP
#include <mbstring.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <new>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

extern char Rva0134D4B8FormatBuffer[2048];

#include "../../../Include/Common/XferException.h"

// ??0XferException@@QAA@HPBDZZ, the same body as _bfmeFormatText.
XferException::XferException(int tag, const char *format, ...)
{
	m_xferField04 = tag;
	m_xferField00 = 0;
	if (format != 0)
	{
		va_list args;
		va_start(args, format);
		int length = _vsnprintf(Rva0134D4B8FormatBuffer, 2047, format, args);
		m_xferField00 = new char[length + 1];
		memcpy(m_xferField00, Rva0134D4B8FormatBuffer, length);
		m_xferField00[length] = 0;
		va_end(args);
	}
}

// ??0XferException@@QAE@ABV0@@Z, retail 0x000588C5, 19 bytes.
XferException::XferException(const XferException &that)
{
	m_xferField00 = 0;
	*this = that;
}

// ??1XferException@@QAE@XZ, folded with INIException's at 0x0002BD30.
XferException::~XferException()
{
	delete[] m_xferField00;
}

// ??4XferException@@QAEAAV0@ABV0@@Z, retail 0x0002F6D6, 68 bytes.
XferException &XferException::operator=(const XferException &that)
{
	if (this != &that)
	{
		delete[] m_xferField00;
		if (that.m_xferField00 != 0)
		{
			m_xferField00 = new char[strlen(that.m_xferField00) + 1];
			_mbscpy(reinterpret_cast<unsigned char *>(m_xferField00), reinterpret_cast<const unsigned char *>(that.m_xferField00));
		}
		else
			m_xferField00 = 0;
		m_xferField04 = that.m_xferField04;
	}
	return *this;
}
