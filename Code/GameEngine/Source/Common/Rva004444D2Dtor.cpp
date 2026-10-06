// cl: /MD
//
// ??1Rva004444D2@@UAE@XZ, retail 0x004444D2, 25 bytes.
// Dtor with vtable 0x0083E020 plus array[2] of Rva005F8F96 at +4
// via CRT vector-dtor helper rowed 0x00629110. Evidence: push dtor
// 0x005F8F96 plus push 2 plus vtable plus push 4 plus add ecx 4
// plus call, 4 unblocked plus 10 callers.

struct Rva005F8F96
{
	~Rva005F8F96();
	void *m_00;
};

class Rva004444D2
{
public:
	virtual ~Rva004444D2();

private:
	Rva005F8F96 m_arr[2];
};

Rva004444D2::~Rva004444D2()
{
}
