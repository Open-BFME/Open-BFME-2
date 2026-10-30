// cl: /MD /Ireference/shims/bfme2_ascii
// stlport
// ?rva000E5EC1@Rva000E5EC1@@QBE_NHABV?$StringBase@D@@@Z @0x000E5EC1 36B
// Target facts: 36B matcher called by 0x000E5EE5/0x000E5F60/0x000E6135; reads int at +0x4C
// and StringBase<char> at +0x8C, calls rowed ?compare@?$StringBase@D@@QBEHABV1@@Z (0x000069D6).
// Not established: owning class identity; address-derived honest name and layout.
// The canonical frozen StringBase replaces the private copy; compare stays
// declared, bound to the rowed provider.
#include "string_base.h"

class Rva000E5EC1
{
public:
	bool rva000E5EC1(int id, const StringBase<char> &name) const throw();
	char m_pad00[0x2C];
	int m_2c; // +0x2C
	char m_pad30[0x1C];
	int m_id; // +0x4C
	char m_pad50[0x38];
	float m_88; // +0x88
	StringBase<char> m_name; // +0x8C
	char m_pad90[0xC];
	bool m_9c; // +0x9C
	char m_pad9D[0x3];
};

bool Rva000E5EC1::rva000E5EC1(int id, const StringBase<char> &name) const
{
	return id == m_id && m_name.compare(name) == 0;
}
