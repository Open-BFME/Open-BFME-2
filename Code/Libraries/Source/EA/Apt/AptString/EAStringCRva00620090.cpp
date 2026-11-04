// cl: /DNDEBUG /MD
// ?rva00620090@EAStringC@@QBEPBDXZ, RVA 0x00620090, 6 bytes.
// Evidence: pin with date toString callback passing live EAStringC to data-plus-eight
// accessor before SetString; donor GetBuffer/c_str/ConstRawPtr aliases share the
// six-byte mov-plus-eight body so address name retained; StringDataC 8-byte header
// from EAStringCAssign donor gives payload at +8.

#include "../../../Apt/EAStringC.h"

const char *EAStringC::rva00620090() const
{
	return reinterpret_cast<const char *>(data) + sizeof(StringDataC);
}
