// cl: /O1 /MD
//
// Small dump-range body: 0x4ED3A2 conditionally refreshes a cursor
// through the pinned cdecl 0x5B09D8 then rewinds it. Retail 0x004ED3A2
// 47B. The pin is an honest address-derived candidate. (0x4EDDAA was
// split out: banked as partial 0.7 with stash for its x87 compare.)

void __cdecl rva005B09D8(void *a, void *b, void *c, void *d);

class Rva004ED3A2
{
public:
	void *rva004ED3A2(void *arg);

private:
	char m_pad[4];
	char *m_04;
};

// ?rva004ED3A2@Rva004ED3A2@@QAEPAXPAX@Z @0x004ED3A2 47B.
void *Rva004ED3A2::rva004ED3A2(void *arg)
{
	char tmp;
	char *m = m_04;
	char *p = (char *)arg + 0x14;
	if (p != m)
		rva005B09D8(p, m, arg, &tmp);
	m_04 -= 20;
	return arg;
}
