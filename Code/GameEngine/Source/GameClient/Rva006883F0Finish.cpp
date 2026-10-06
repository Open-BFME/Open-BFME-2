// ?parseSubtitleLineTable@@YAXPAVINI@@PAX1PBX@Z
// The x87 operand order is a compiler-side rewrite, not a source spelling: declaring
// the running previous value volatile stops MSVC folding the load through the add,
// which is what turns retail fld [previous] / fadd [step] into fadd [step] / fld [previous].
// Retail 0x006883F0, 340 bytes. The BFME2 beta debug string and the
// SubtitleManager field table identify this as the LineTable parser.
// The field table at data VA 0x00CE4410 stores it under "LineTable" at
// SubtitleManager+0x24; the adjacent SubTitle field uses 0x00688B10.
//
// Target behavior reconstructed from the retail body. The 15-point cap,
// [0,1] range and 0.01875 minimum step are data/branch evidence, not donor
// assumptions.
// cl: /Ireference/shims/bfme2_ascii /O2 /DNDEBUG /MD /EHsc

#include "ascii_string.h"

typedef int Int;
typedef float Real;

class INI
{
public:
	AsciiString getFilename() const;
	Int getLineNum() const;
	const char *getNextToken(const char *separators);
	Real scanReal(const char *token);

private:
	char m_pad000[0x418];
	const char *m_defaultSeparators;
};

class VideoPlayerInterface
{
public:
	virtual ~VideoPlayerInterface();
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void *getVideo(const AsciiString &title) = 0;
};

extern VideoPlayerInterface *TheVideoPlayer;

struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

// Canonical 8-byte INIException layout (char * at +0, int at +4; dtor
// ??1INIException@@QAE@XZ 0x0042BD30, copy 0x004588C5, filler
// ??0INIException@@QAA@HPBDZZ 0x0002F681). Consumer only: throws via the
// filler plus _CxxThrowException with the extern TI1, so this TU emits no
// __TI1 COMDAT of its own (the kept retail copy links).
class INIException
{
public:
	INIException(int argumentCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
	char *mFailureMessage;
	int m_argumentCount;
};

// The parser is registered directly in SubtitleManager's FieldParse table.
void parseSubtitleLineTable(INI *ini, void *instance, void *store, const void *userData)
{
	Real *values = (Real *)store;
	void *manager = TheVideoPlayer->getVideo(ini->getFilename());
	if (manager != 0 && values != 0)
	{
		*((unsigned char *)manager + 0x60) = 1;
		volatile Real previous = -3.402823466e+38F;
		for (Int index = 0; index < 15; ++index)
		{
			Real value = ini->scanReal(ini->getNextToken(0));
			if (!(value >= 0.0f && value <= 1.0f && value > previous + 0.01875f))
			{
				throw INIException(8,
					"LineTable values must be in the range (0.0 - 1.0) must increase in value. %s line %d",
					ini->getFilename(), ini->getLineNum());
			}
			previous = value;
			values[index] = value;
		}
		return;
	}
	throw INIException(9, "Could not locate SubTitleManager for %s", ini->getFilename());
}
