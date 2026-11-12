// cl: /Ob0

#include "../../Include/Common/Rva0087DC00Vec.h"

class Rva0087DC00
{
	char m_pad[0x18];
	Rva0087DC00Vec m_18;

public:
	void get(Rva0087DC00Vec *out);
};

void Rva0087DC00::get(Rva0087DC00Vec *out)
{
	*out = m_18;
}
