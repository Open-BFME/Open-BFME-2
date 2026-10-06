// cl: /DNDEBUG /MD /EHs
// ??1Rva0022DCDA@@QAE@XZ retail 0x0022DCDA 63B
// Member dtor at +0x0C of the dtor 0x00414166. Vector-shaped: the body
// destroys [start, finish) through the rowed range destroy 0x0022D941, then
// the inline CRT buffer member at +0 frees the storage.
struct Rva0022CD2A;

void Rva0022D941Destroy(Rva0022CD2A *first, Rva0022CD2A *last);

extern "C" void __cdecl free(void *);

struct Rva0022DCDAStorage
{
	Rva0022CD2A *m_block;
	~Rva0022DCDAStorage()
	{
		if (m_block)
			free(m_block);
	}
};

class Rva0022DCDA
{
public:
	~Rva0022DCDA();
private:
	Rva0022DCDAStorage m_start; // +0x00
	Rva0022CD2A *m_finish; // +0x04
	Rva0022CD2A *m_endOfStorage; // +0x08
};

Rva0022DCDA::~Rva0022DCDA()
{
	Rva0022D941Destroy(m_start.m_block, m_finish);
}
