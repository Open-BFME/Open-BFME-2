// cl: /MD /Oi-
// ?rva005426DB@Rva005426DB@@QAE_NPAE@Z @0x005426DB 96B
// XML entity decoder: ++m_ptr then 5-entry table at 0x00DD1E74 via strlen
// thunk 0x00629170 plus strncmp IAT then advance past name and require ';'
// storing table value to out byte. Caller 0x005427A7. Evidence: retail bytes
// unlock lane plus '&' 0x26 and ';' 0x3B checks and 8-byte entries.
extern "C" unsigned int __cdecl strlen(const char *s);
extern "C" __declspec(dllimport) int __cdecl strncmp(const char *s1, const char *s2, unsigned int n);

struct EntityEntry {
	const char *name;
	unsigned char value;
	char pad[3];
};

extern const EntityEntry g_00DD1E74[];

class Rva005426DB
{
public:
	bool rva005426DB(unsigned char *out);
private:
	char *m_ptr;
};

bool Rva005426DB::rva005426DB(unsigned char *out)
{
	++m_ptr;
	if (*m_ptr == 0)
		return false;
	for (unsigned int i = 0; i < 5; ++i) {
		const EntityEntry *e = &g_00DD1E74[i];
		unsigned int len = strlen(e->name);
		if (strncmp(m_ptr, e->name, len) == 0) {
			m_ptr += len;
			if (*m_ptr != ';')
				return false;
			*out = g_00DD1E74[i].value;
			return true;
		}
	}
	return false;
}
