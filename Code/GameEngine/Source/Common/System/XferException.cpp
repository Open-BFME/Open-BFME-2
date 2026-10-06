// cl: /DNDEBUG /MD
// XferException: the object every Xfer failure throws. Retail's throw
// information for it (__TI1?AVXferException@@ at VA 0x00CFFD18) names the
// destructor at 0x0002BD30 and, through its one catchable type, the copy
// constructor at 0x000588C5; that copy constructor nulls the text and
// assigns through operator= at 0x0002F6D6. The (tag, format, ...)
// constructor is the formatter rowed as _bfmeFormatText at 0x0060C36E, and
// the destructor folds with INIException's: both delete[] the text at +0.
#include <stdarg.h>
#include <string.h>

extern char Rva0134D4B8FormatBuffer[2048];
extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char *, unsigned int, const char *, va_list);
void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *block);

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();
	XferException &operator=(const XferException &that);

	char *text;
	int tag;
};

// ??0XferException@@QAA@HPBDZZ, the same body as _bfmeFormatText.
XferException::XferException(int tag, const char *format, ...)
{
	this->tag = tag;
	text = 0;
	if (format != 0)
	{
		va_list args;
		va_start(args, format);
		int length = _vsnprintf(Rva0134D4B8FormatBuffer, 2047, format, args);
		text = new char[length + 1];
		memcpy(text, Rva0134D4B8FormatBuffer, length);
		text[length] = 0;
		va_end(args);
	}
}

// ??0XferException@@QAE@ABV0@@Z, retail 0x000588C5, 19 bytes.
XferException::XferException(const XferException &that)
{
	text = 0;
	*this = that;
}

// ??1XferException@@QAE@XZ, folded with INIException's at 0x0002BD30.
XferException::~XferException()
{
	delete[] text;
}

// ??4XferException@@QAEAAV0@ABV0@@Z, retail 0x0002F6D6, 68 bytes.
XferException &XferException::operator=(const XferException &that)
{
	if (this != &that)
	{
		delete[] text;
		if (that.text != 0)
		{
			text = new char[strlen(that.text) + 1];
			strcpy(text, that.text);
		}
		else
			text = 0;
		tag = that.tag;
	}
	return *this;
}

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
