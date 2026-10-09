// cl: /Ireference/shims/bfme2_ascii /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??4ShadowTypeInfo@Shadow@@QAEAAU01@ABU01@@Z @0x0009A41B (93B). TU named
// for the row's earlier, wrong AudioEventRTS name.
// Shadow::ShadowTypeInfo copy-assign on the ctor TU's layout
// (AudioEventRTSCtor.cpp): two AsciiStrings then the type, six floats and
// three bytes, member by member. Evidence: W3DShadowManager::addShadow
// 0x0009A8D3 assigns the info it is passed into its locally constructed
// copy through this body; AsciiString op= pin @0x366F0; ctor layout
// @0x79514.

typedef int Int;

#include "ascii_string.h"

class Shadow
{
public:
	struct ShadowTypeInfo
	{
		ShadowTypeInfo &operator=(const ShadowTypeInfo &right);

		AsciiString m_first;
		AsciiString m_second;
		Int m_type;
		float m_floatC;
		float m_float10;
		float m_float14;
		float m_float18;
		float m_float1C;
		float m_float20;
		unsigned char m_byte24;
		unsigned char m_byte25;
		unsigned char m_byte26;
	};
};

Shadow::ShadowTypeInfo &Shadow::ShadowTypeInfo::operator=(const ShadowTypeInfo &right)
{
	m_first = right.m_first;
	m_second = right.m_second;
	m_type = right.m_type;
	m_floatC = right.m_floatC;
	m_float10 = right.m_float10;
	m_float14 = right.m_float14;
	m_float18 = right.m_float18;
	m_float1C = right.m_float1C;
	m_float20 = right.m_float20;
	m_byte24 = right.m_byte24;
	m_byte25 = right.m_byte25;
	m_byte26 = right.m_byte26;
	return *this;
}
