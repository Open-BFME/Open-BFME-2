// cl: /MD
// ??0Rva005CC254@@QAE@PAX@Z @0x005CC254 26B evidence: stores 0x00C74E04 at +0 then arg at +4 clears +8 sets +0xC to 1; caller 0x0057525F
// Initializes 13-byte struct: +0 points at g_00C74E04 +4 holds ctor arg +8 zeroed +0xC set to 1.
extern const void *const g_00C74E04[];
class Rva005CC254 {
public:
	Rva005CC254(void *p);
	void *m_00;
	void *m_04;
	int m_08;
	unsigned char m_0c;
};
Rva005CC254::Rva005CC254(void *p)
{
	m_08 = 0;
	m_00 = (void *)g_00C74E04;
	m_04 = p;
	m_0c = 1;
}
