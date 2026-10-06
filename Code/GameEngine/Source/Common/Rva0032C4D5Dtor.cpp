// cl: /DNDEBUG /MD /EHs
// ??1Rva0032C4D5@@QAE@XZ @0x0032C4D5 30B
// Vector-like container dtor over Rva00329D0E without EH frame.
// Evidence: retail calls rowed
// ?Rva0032AF56Destroy@@YAXPAVRva00329D0E@@0@Z @0x0032AF56 with
// (m_start, m_finish) at +0 +4 then frees m_start via rowed _free
// @0x00030830; caller @0x0032CB37; chain lane; non-EH twin of
// blocked 63B ??1Rva0032C3A3 at 0x0032C3A3.
class Rva00329D0E
{
public:
	~Rva00329D0E();
};

void Rva0032AF56Destroy(Rva00329D0E *first, Rva00329D0E *last);
extern "C" void __cdecl free(void *block);

class Rva0032C4D5
{
	Rva00329D0E *m_start;
	Rva00329D0E *m_finish;

public:
	~Rva0032C4D5();
};

Rva0032C4D5::~Rva0032C4D5()
{
	Rva0032AF56Destroy(m_start, m_finish);
	if (m_start)
		free(m_start);
}
