// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
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

AsciiString Locomotor::getTemplateName() const
{
	return m_template->m_name;
}
