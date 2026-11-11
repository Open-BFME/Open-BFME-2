// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
#include "unicode_string.h"
class Rva003F7D86Inner;
#include "../../../Include/Common/Rva003F81FDProxy.h"
#include "../../../Include/Common/Rva003F8052.h"
#include "../../../Include/Common/Rva0056AC26Owner.h"
UnicodeString Rva0056AC26Owner::rva003F855D(){
 Rva003F7D86Inner *p=reinterpret_cast<Rva003F81FDProxy *>(this)->rva003F81B0();
 return p ? reinterpret_cast<Rva003F8052 *>(p)->rva003F8497() : UnicodeString::TheEmptyString;
}

// Native3F855D..3F85C6 full105B: same-this owned proxy getter3F81B0;
// if present forward to owned UnicodeString-valued3F8497, else copy
// canonical UnicodeString::TheEmptyString. Conditional temporary lifetime
// and return-construction flags establish the hidden-result ABI; constructor
// 56AD80 independently constructs its UnicodeStringC through this call.
// Original owner/getter names remain unknown; these are target-neutral views.
