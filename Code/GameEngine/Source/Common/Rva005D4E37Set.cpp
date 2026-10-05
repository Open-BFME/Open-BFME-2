// cl: /Ireference/shims/bfme2_ascii /O1 /MD
#include "ascii_string.h"
class Rva005D4E37
{
public:
	void rva005D4E37(int unused, const char *a2, bool a3);
private:
	char *m_00;
	AsciiString *m_04;
};
void Rva005D4E37::rva005D4E37(int unused, const char *a2, bool a3)
{
	(void)unused;
	if (a2 == 0)
		return;
	if (!a3)
		return;
	if (*m_00 != 0)
		return;
	m_04->set(a2);
	*m_00 = 1;
}
