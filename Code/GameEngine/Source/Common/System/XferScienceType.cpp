// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native [0x00306232,0x003062FE), 204 bytes, cdecl, returns the Xfer pointer.
// "ScienceType" at 0x00C07D14, the four-byte enum, -1 invalid value,
// ScienceStore global at 0x00DFE0E0 and the virtual slots are retail facts.
// Saving writes the name returned by the 51-byte 0x001FF5F2 provider;
// loading resolves it through 0x001FF725 and rejects an unknown science.
// Both providers already byte-verify, including their hidden-result/ret8 ABI.
// The receiver view declares no ScienceStore fields. Its getter uses an
// address-derived spelling because its original C++ signature is unproven.
// Semantic guide: Open-BFME-1 968ca36c3265 GeneralsMD/Common/System/Xfer.cpp,
// Xfer::xferScienceType. Target uses free cdecl ABI, light-CRC enum dispatch,
// branch-local strings and XferException(0,0), instead of the donor's method.
// The original target function spelling remains unknown.
#include "ascii_string.h"

enum ScienceType { SCIENCE_0 = 0 };
enum NameKeyType { NAMEKEY_INVALID = -1 };
#include "XferVectorTypes.h"
#include "../../../Include/Common/BfmeXfer.h"
#include "../../../Include/Common/ScienceStore.h"
extern ScienceStore *TheScienceStore;
#include "../../../Include/Common/XferException.h"

Xfer *Rva00306232XferScience(Xfer *xfer, ScienceType *science)
{
 if (xfer->IsLightCRC()) {
  xfer->XferEnum("ScienceType", science, 4);
 } else if (xfer->IsStoring()) {
  AsciiString scienceName = TheScienceStore->getInternalNameForScience(*science);
  *xfer == scienceName;
 } else {
  AsciiString scienceName;
  *xfer == scienceName;
  *science = TheScienceStore->getScienceFromInternalName(scienceName);
  if ((int)*science == -1)
   throw XferException(0, 0);
 }
 return xfer;
}
