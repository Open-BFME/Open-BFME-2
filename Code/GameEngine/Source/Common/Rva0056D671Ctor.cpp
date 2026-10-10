// cl: /O1 /G7 /arch:SSE /MD /Ireference/shims/bfme2_ascii
// Native56D671..56D690 complete31B RET4, allocation factory410223..41025D
// calls here at41024A with270 bytes. Dtor56D690 establishes the shared
// Rva0056D690 neutral identity, vtable C6DAC4 and AsciiString at26C.
// The base constructor is the existing ledger provider labelled Locomotor
// at5C96EB; that label and template spelling are inherited, not new target
// identity claims. Only its26C prefix and forwarded pointer ABI are modeled.
// Canonical AsciiString default construction is defined initialization.
#include "ascii_string.h"
class LocomotorTemplate;

class Locomotor
{
public:
	Locomotor(const LocomotorTemplate *tmpl);
	virtual ~Locomotor();
private:
	char m_pad[0x26C - 4];
};

class Rva0056D690 : public Locomotor
{
public:
	Rva0056D690(const LocomotorTemplate *tmpl);
	virtual ~Rva0056D690();
private:
	AsciiString m_26C;
};

Rva0056D690::Rva0056D690(const LocomotorTemplate *tmpl)
	: Locomotor(tmpl)
{
}
