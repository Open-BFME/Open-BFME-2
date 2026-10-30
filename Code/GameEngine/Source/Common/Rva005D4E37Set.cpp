// cl: /Ireference/shims/bfme2_ascii /MD
#include "ascii_string.h"
class Rva005D4E37
{
public:
	void rva005D4E37(int unused, const char *text, bool allowSet);
private:
	char *m_00;
	AsciiString *m_04;
};
void Rva005D4E37::rva005D4E37(int unused, const char *text, bool allowSet)
{
	(void)unused;
	if (text == 0)
		return;
	if (!allowSet)
		return;
	if (*m_00 != 0)
		return;
	m_04->set(text);
	*m_00 = 1;
}
