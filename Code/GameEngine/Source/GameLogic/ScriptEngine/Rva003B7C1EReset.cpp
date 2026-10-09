// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX-
//
// ?rva003B7C1E@Rva003B7C1E@@QAEXXZ, retail 0x003B7C1E..0x003B7C42 (36 bytes):
// empties the object by swapping it with a freshly built 0x20-byte one
// (rowed constructor 0x003B761E, rowed swap 0x003B56A5) which the
// destructor 0x003B766B then tears down. Built without EH, as retail.

class Rva003B56A5
{
public:
	void swap(Rva003B56A5 *other);
};

class Rva003B761E
{
public:
	Rva003B761E();
	~Rva003B761E();
	void swapWith(void *other) { reinterpret_cast<Rva003B56A5 *>(this)->swap((Rva003B56A5 *)other); }
private:
	unsigned char m_data[0x20];
};

class Rva003B7C1E
{
public:
	void rva003B7C1E();
};

void Rva003B7C1E::rva003B7C1E()
{
	Rva003B761E().swapWith(this);
}
