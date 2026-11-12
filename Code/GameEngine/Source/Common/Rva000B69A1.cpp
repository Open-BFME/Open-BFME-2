// cl: /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
// ?slot14@ModuleData@@UBE?AVAsciiString@@H@Z @0x000B69A1 28B
// ModuleData's slot 14 default (ModuleData.h `slot14(int) const`): slot 14 (0x38) of every
// module-data table ModuleFactory registers (W3DLaserDrawModuleData, AnimalAIUpdateModuleData, etc).
// Returns AsciiString::TheEmptyString via rowed StringBase<char> copy 0x000365F0. No callers.
// Formerly rowed as Rva000B69A1::rva000B69A1; the class identity is the reviewed base-slot
// entry MODULE_DATA_SLOT14 in tools/retail_identity.py.
#include "ascii_string.h"
#include "../../Include/Common/ModuleData.h"

AsciiString ModuleData::slot14(int mode) const
{
	(void)mode;
	return AsciiString::TheEmptyString;
}
