// cl: /O1 /DNDEBUG /MD /EHsc
// Address-derived owner of two inline StringBase-compatible members.

class Rva0048C200String
{
public:
	Rva0048C200String() : m_data( 0 ) {}
	~Rva0048C200String();
	void release();

private:
	void *m_data;
};

class Rva0048C200Owner
{
public:
	Rva0048C200Owner();

private:
	void *m_head;
	Rva0048C200String m_first;
	Rva0048C200String m_second;
	int m_count;
	unsigned char m_active;
};

// Unresolved member dtor reaches the rowed StringBase release worker (same as
// the dtor TU's binding); the ctor's EH unwind calls it, retail's target.
#pragma comment(linker, "/alternatename:??1Rva0048C200String@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

Rva0048C200Owner::Rva0048C200Owner()
	: m_head( 0 ), m_count( 0 ), m_active( 0 )
{
	m_second.release();
	m_first.release();
}
