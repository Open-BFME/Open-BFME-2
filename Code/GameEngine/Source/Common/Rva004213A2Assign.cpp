// cl: /MD /Ireference/shims/bfme2_ascii
// ??4Rva004213A2@@QAEAAV0@ABV0@@Z @0x004213A2 57B
// Copy-assign with empty base plus AsciiString at +0x10 UnicodeString at +0x14
// vector<uint> at +0x18. Evidence: unlock lane; callees rowed 0x001FD28E
// 0x000366F0 0x00037150 and pinned 0x0026F4F4; caller 0x00421572.
#include "ascii_string.h"
#include "unicode_string.h"

namespace FXParticleSystem
{
class StreakDrawModuleTemplate
{
public:
	StreakDrawModuleTemplate &operator=(const StreakDrawModuleTemplate &other);
};
}

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A = allocator<T> > class vector
{
public:
	vector &operator=(const vector &other);
};
}

class Rva004213A2 : public FXParticleSystem::StreakDrawModuleTemplate
{
public:
	Rva004213A2 &operator=(const Rva004213A2 &other);
private:
	char m_pad[15];
	AsciiString m_ascii;
	UnicodeString m_wide;
	_STL::vector<unsigned int> m_vec;
};

Rva004213A2 &Rva004213A2::operator=(const Rva004213A2 &other)
{
	StreakDrawModuleTemplate::operator=(other);
	m_ascii = other.m_ascii;
	m_wide = other.m_wide;
	m_vec = other.m_vec;
	return *this;
}
