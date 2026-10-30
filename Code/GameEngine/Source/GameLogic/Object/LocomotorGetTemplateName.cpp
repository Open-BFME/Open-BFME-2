// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
// ?getTemplateName@Locomotor@@QBE?AVAsciiString@@XZ @0x001E4A63 30B
#include "ascii_string.h"

class LocomotorTemplate
{
public:
	char m_pad[0x10];
	AsciiString m_name;
};

class Locomotor
{
public:
	virtual ~Locomotor();
	const LocomotorTemplate *m_template;
	AsciiString getTemplateName() const;
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline AsciiString Locomotor::getTemplateName() const
{
	return m_template->m_name;
}

// ?bfmeAnchorLocomotorGetTemplateName absent-from-retail
AsciiString bfmeAnchorLocomotorGetTemplateName(const Locomotor *locomotor)
{
	return locomotor->getTemplateName();
}

