// cl: /MD /Oi-
// ?rva005423F0@Rva005423F0@@QAEPADPAD@Z @0x005423F0 53B
// Whitespace skip with line counting via isspace IAT and newline check
// updating current at +0x08 and line at +0x0C. Evidence: retail bytes unlock
// lane plus seven callers in 0x005424C4 and 0x00542890 plus isspace import.
// Sibling of landed Rva00542425Skip identifier skip in same page.
extern "C" __declspec(dllimport) int __cdecl isspace(int c);

class Rva005423F0
{
public:
	char *rva005423F0(char *p);
private:
	char m_pad0[8];
	char *m_8;
	int m_C;
};

char *Rva005423F0::rva005423F0(char *p)
{
	char *s = p;
	for (;;) {
		char c = *s;
		if (c == 0)
			break;
		if (!isspace(c))
			break;
		if (*s == '\n') {
			m_C++;
			m_8 = s + 1;
		}
		s++;
	}
	return s;
}
