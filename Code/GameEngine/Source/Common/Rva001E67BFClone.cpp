// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ?rva001E67BF@LocomotorTemplate@@QAE?AV1@XZ, retail 0x001E67BF, 94 bytes.
// By-value copy helper: makes a local LocomotorTemplate from *this through the
// copy-constructor at 0x001E4DEB (same vtable 0x007DE8B4, base Overridable
// and AsciiString at +0x10 as the rowed dtor 0x001E4DB0 proves), copies it
// to the hidden return slot, then destroys the local through the rowed
// dtor. Caller 0x004DA49E. Owner proven by vtable/base/callee layout.
#include "ascii_string.h"

#include "../../Include/Common/Overridable.h"

class LocomotorTemplate : public Overridable
{
public:
	LocomotorTemplate(const LocomotorTemplate &o);
	virtual ~LocomotorTemplate();
	LocomotorTemplate rva001E67BF();
private:
	AsciiString m_10;
	char m_pad14[0x13C];
	bool m_scalesWalls;
	char m_pad151[0x03];
};

LocomotorTemplate LocomotorTemplate::rva001E67BF()
{
	LocomotorTemplate tmp(*this);
	tmp.m_scalesWalls = false;
	return tmp;
}
