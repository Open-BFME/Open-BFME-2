// cl: /DNDEBUG /MD
// Clean C++ conversion of the formatted text builder at retail RVA 0x009D6220.
#include <stdarg.h>
#include <string.h>

// This formatter has its own scratch buffer at VA 0x0134D4B8. The INI
// exception constructor's g_bfmeFormatBuffer is the distinct VA 0x0130C650.
// .bss VA 0x00E073F8; the next datum starts 0x800 bytes later.
char Rva0134D4B8FormatBuffer[2048];
extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char *, unsigned int, const char *, va_list);
void *__cdecl operator new[](unsigned int size);

struct BfmeFormattedText
{
	char *text;
	int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *result, int tag, const char *format, ...)
{
	result->tag = tag;
	result->text = 0;
	if (format != 0)
	{
		va_list args;
		va_start(args, format);
		int length = _vsnprintf(Rva0134D4B8FormatBuffer, 2047, format, args);
		result->text = new char[length + 1];
		memcpy(result->text, Rva0134D4B8FormatBuffer, length);
		result->text[length] = 0;
		va_end(args);
	}
	return result;
}
