// cl: /DNDEBUG /MD /EHs
// ??1Rva000C2067@@QAE@XZ @0x000C2067 30B
// Vector-like container dtor over Rva000B9AAA without EH frame.
// Evidence: retail calls rowed
// ?Rva000BDD08Destroy@@YAXPAVRva000B9AAA@@0@Z @0x000BDD08 with
// (m_start, m_finish) at +0 +4 then frees m_start via rowed _free
// @0x00030830; callers @0x000C2109 @0x000C3586; chain lane;
// same recipe as rowed ??1Rva0032C4D5 @0x0032C4D5.
class Rva000B9AAA
{
public:
	~Rva000B9AAA();
};

void Rva000BDD08Destroy(Rva000B9AAA *first, Rva000B9AAA *last);
extern "C" void __cdecl free(void *block);

class Rva000C2067
{
	Rva000B9AAA *m_start;
	Rva000B9AAA *m_finish;

public:
	~Rva000C2067();
};

Rva000C2067::~Rva000C2067()
{
	Rva000BDD08Destroy(m_start, m_finish);
	if (m_start)
		free(m_start);
}
