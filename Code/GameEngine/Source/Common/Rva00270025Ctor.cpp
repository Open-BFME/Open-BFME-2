// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva00270025@@QAE@XZ @0x00270025 28B
// ?rva00270041@Rva00270025@@QAEXXZ @0x00270041 43B
// ?rva0027006C@Rva00270025@@QAEXH@Z @0x0027006C 44B
// Ctor for 0x74-byte class with vtable 0x007FAD34; zeroes 14 ptrs at +0x04 and 14 ints at +0x3C.
// Cleanup deletes m_04[i]->get(0) then zeroes both arrays.
// Evidence: new 0x74 at 0x00270BB4 calls ctor; deleting dtor at 0x00274E5B calls 0x00270041; honest Rva names.
struct Rva00270025Item
{
	virtual void *get(int x);
};

class Rva00270025
{
public:
	Rva00270025();
	virtual ~Rva00270025();
	void rva00270041();
	void rva0027006C(int index);
private:
	Rva00270025Item *m_04[14];
	int m_3c[14];
};

Rva00270025::Rva00270025()
{
	for (int i = 0; i < 14; i++) {
		m_04[i] = 0;
		m_3c[i] = 0;
	}
}

Rva00270025::~Rva00270025()
{
	rva00270041();
}

void Rva00270025::rva00270041()
{
	for (int i = 0; i < 14; i++) {
		if (m_04[i])
			delete m_04[i]->get(0);
		m_04[i] = 0;
		m_3c[i] = 0;
	}
}

void Rva00270025::rva0027006C(int index)
{
	if (m_04[index]) {
		delete m_04[index]->get(0);
		m_04[index] = 0;
		m_3c[index] = 0;
	}
}
