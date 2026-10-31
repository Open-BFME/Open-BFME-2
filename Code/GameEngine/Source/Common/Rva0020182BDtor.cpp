// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva0020182B@@UAE@XZ retail 0x0020182B 79B
// Compiler-generated dtor (no own vptr store): the AsciiString at +0x18
// (EH state 1), then the second base at +0x10 (null-checked this adjust) whose
// inline dtor releases its AsciiString at +4 (state 0), then the rowed first
// base dtor ??1Overridable@@UAE@XZ 0x001E3624. Caller: rowed ??_G 0x0020180F
// (vtable 0x00BE3070). Names address-derived.

#include "ascii_string.h"

#include "../../Include/Common/Overridable.h"

class Rva0020182BSecond
{
public:
	int m_00;
	AsciiString m_name; // +0x04
};

class WeatherSetting : public Overridable, public Rva0020182BSecond
{
public:
	WeatherSetting(int tag);

private:
	AsciiString m_text; // +0x18
};

// The implicit virtual dtor is emitted with the vtable this helper ctor needs.
// ?<WeatherSetting::WeatherSetting> absent-from-retail
WeatherSetting::WeatherSetting(int)
{
}
