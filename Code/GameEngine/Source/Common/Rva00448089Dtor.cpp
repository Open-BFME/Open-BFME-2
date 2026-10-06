// cl: /EHsc /MD
// ??1Rva00448089@@QAE@XZ retail 0x00448089 53B
// Dtor releasing two StringBase<unsigned short> members at +0 and +4 via
// rowed releaseBuffer 0x00036E70 with EH state 0 then -1. Evidence: EH_prolog
// push ecx push esi mov esi-ecx mov ebp-0x10-esi lea ecx esi+4 call then
// mov ecx esi call; no vptr store so non-virtual public QAE; unblocks 3.
template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};
class Rva00448089
{
public:
	~Rva00448089();
private:
	StringBase<unsigned short> m_00;
	StringBase<unsigned short> m_04;
};
Rva00448089::~Rva00448089()
{
}
