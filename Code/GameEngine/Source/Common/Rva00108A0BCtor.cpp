// cl: /EHsc /MD
//
// ??0Rva00108A0B@@QAE@XZ @0x00108A0B 110B. Default ctor allocating two
// HashTableClass(0x800) tables at +0/+4 via rowed operator new 0x0002FDA0.
// Callers at 0x00108DDF. Honest address name; HashTableClass layout verbatim
// from BFME1 hash.h (int + pointer = 8B).
class HashableClass;

class HashTableClass
{
public:
	HashTableClass(int size);
private:
	int m_size;
	HashableClass **m_table;
};

class Rva00108A0B
{
public:
	Rva00108A0B();
private:
	HashTableClass *m_a;
	HashTableClass *m_b;
};

Rva00108A0B::Rva00108A0B()
	: m_a(new HashTableClass(0x800)), m_b(new HashTableClass(0x800))
{
}
