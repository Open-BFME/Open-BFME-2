// cl: /MD
// ??1Rva005CB4E6Elem@@QAE@XZ retail 0x005CB4E6 69B
// Elem dtor destroying three Rva005CB31D holders at +0x10/+0x14/+0x18 via rowed 0x005CB31D with EH states 1 0 -1. Evidence: chain from 0x005CB31D; ctor 0x005CB4C7 zeroes six dwords (size 0x1C); callers 0x005CB85D deleting dtor and 0x005CB89E clear; neighbours share // cl: /O1 /MD.
class Rva005CB31D
{
public:
	~Rva005CB31D();
private:
	void *m_ptr;
};

class Rva005CB8D4;

class Rva005CB4E6Elem
{
public:
	~Rva005CB4E6Elem();
private:
	Rva005CB8D4 *m_owner;
	int m_04;
	int m_08;
	int m_0C;
	Rva005CB31D m_10;
	Rva005CB31D m_14;
	Rva005CB31D m_18;
};

Rva005CB4E6Elem::~Rva005CB4E6Elem()
{
}
