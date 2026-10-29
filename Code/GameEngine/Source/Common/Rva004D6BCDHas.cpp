// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva004D6BCD@Rva004D6BCD@@QBE_NPBVObject@@@Z @0x004D6BCD (35B):
// Linear search of the +0x04 ScienceType vector for the Science at arg+0x74.
// Retail loads target to edx, begin to eax, end to ecx, loops dword cmp,
// returns AL 1/0. Callers 0x00260F5D and 0x002AA1A1; unblocks 0x002AA191.
// Honest-address name.

enum ScienceType
{
	SCIENCE_INVALID = 0
};

#include <vector>

class Object
{
public:
	char m_pad[0x74];
	ScienceType m_science;
};

class Rva004D6BCD
{
public:
	bool rva004D6BCD(const Object *obj) const;

private:
	char m_pad04[4];
	_STL::vector<ScienceType> m_vec04;
};

bool Rva004D6BCD::rva004D6BCD(const Object *obj) const
{
	ScienceType target = obj->m_science;
	for (const ScienceType *scienceType = m_vec04.begin(); scienceType != m_vec04.end(); ++scienceType) {
		if (target == *scienceType)
			return true;
	}
	return false;
}
