// cl: /DNDEBUG /MD /EHs
// ??1Rva0056F43E@@QAE@XZ @0x0056F9D4 56B
// Dtor of the Rva0056F43E table (cleanup bodies in Rva0056F43ECleanup.cpp):
// the body calls this->rva0056F503, then the header at m_00 is freed by the
// member's inline destructor. Retail's unwind map destroys that member at
// +0 in state 0 through 0x0007FAB3 (a 14B free-if-non-null body folded with
// the rowed string dtor), and the normal path disarms to -1 before the
// inline free. The disarm survives only under /EHs: with /EHsc the extern
// "C" free is treated as non-throwing and the store is dropped (the banked
// 0.93 attempt, 52 of 56 bytes).
template <typename T>
class StringBase
{
public:
	void clear();
private:
	void *m_data;
};
extern "C" void __cdecl free(void *p);
struct Rva0056F43EHolder
{
	void *m_ptr;
	~Rva0056F43EHolder() { if (m_ptr) free(m_ptr); }
};
struct Rva0056F43E
{
	Rva0056F43EHolder m_00;
	int m_04;
	void *m_08;
	void *m_0c;
	StringBase<unsigned short> m_10;
	void rva0056F43E(void *node);
	void rva0056F503();
	~Rva0056F43E();
};
Rva0056F43E::~Rva0056F43E()
{
	rva0056F503();
}
