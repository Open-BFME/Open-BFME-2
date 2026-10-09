// cl: /O1 /G7 /MD /EHsc
//
// ??1Rva004444D2@@UAE@XZ, retail 0x004444D2, 25 bytes.
// Dtor with vtable 0x0083E020 plus array[2] of Rva005F8F96 at +4
// via CRT vector-dtor helper rowed 0x00629110. Evidence: push dtor
// 0x005F8F96 plus push 2 plus vtable plus push 4 plus add ecx 4
// plus call, 4 unblocked plus 10 callers.

struct Rva005F8F96
{
	Rva005F8F96();
	~Rva005F8F96();
	void *m_00;
};

class Rva004444D2
{
public:
	Rva004444D2();
	virtual ~Rva004444D2();

private:
	Rva005F8F96 m_arr[2];
};

Rva004444D2::~Rva004444D2()
{
}

// Retail 0x004444AE..0x004444D2 constructs the two callback handles at +4.
// AptLanLobby constructor 0x00445EE3 calls this base at +0x27C. The native
// vector-constructor arguments prove count 2, stride 4, handle constructor
// 0x00326BE6 and destructor 0x005F8F96; table 0x0083E020 agrees with teardown.
Rva004444D2::Rva004444D2()
{
}
