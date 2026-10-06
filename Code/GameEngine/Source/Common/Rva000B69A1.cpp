// cl: /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
// ?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z @0x000B69A1 28B
// Slot 14 (0x38) of many ModuleData vtables (W3DLaserDrawModuleData, AnimalAIUpdateModuleData, etc).
// Returns AsciiString::TheEmptyString via rowed StringBase<char> copy 0x000365F0. No callers.
#include "ascii_string.h"

class Rva000B69A1
{
public:
	AsciiString rva000B69A1(int mode);
};

AsciiString Rva000B69A1::rva000B69A1(int mode)
{
	(void)mode;
	return AsciiString::TheEmptyString;
}
