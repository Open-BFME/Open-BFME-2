// cl: /EHsc /MD
// ??1Rva0032D279@@QAE@XZ, retail 0x0032D279, 84 bytes.
// Dtor for vector of 8-byte pairs (int key plus polymorphic value at +4):
// deletes each non-null value via virtual dtor plus operator delete,
// then base Rva0032CA4E vector dtor destroys pairs and frees storage.
// Evidence: loop over [this+0, this+4) step 8 with [esi+4] null check,
// virtual call [edx] plus rowed operator delete 0x0002FD60,
// tail calls rowed ??1Rva0032CA4E 0x0032CA4E; EH prolog with fs:0.
class Rva0032CA4E
{
public:
	~Rva0032CA4E();
protected:
	void *m_start;
	void *m_finish;
	void *m_end;
};

class Rva0032D279Value
{
public:
	virtual void *deleteInstance(int pool);
};

struct Rva0032D279Pair
{
	int m_key;
	Rva0032D279Value *m_value;
};

class Rva0032D279 : public Rva0032CA4E
{
public:
	~Rva0032D279();
};

Rva0032D279::~Rva0032D279()
{
	Rva0032D279Pair *last = (Rva0032D279Pair *)m_finish;
	Rva0032D279Pair *first = (Rva0032D279Pair *)m_start;
	for (; first != last; ++first) {
		Rva0032D279Value *v = first->m_value;
		::operator delete(v ? v->deleteInstance(0) : 0);
	}
}
