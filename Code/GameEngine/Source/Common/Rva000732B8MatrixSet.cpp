// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target facts: counts at +0 and +4 drive nested loops over byte arrays at
// +0x38 and +0x3C. The tree at +0x4C is cleared through rowed 0x72FE6 and
// mismatching flattened indices are inserted through rowed set<int>::insert
// at 0xBC15D. The completion byte at +0x48 is set after the loops.
// Structural inference: the tree is a set<int> and each index counts a byte
// position across both dimensions. The owner stays RVA-derived because no
// named caller or independent class identity was found.
#include <set>

class Rva00072FE6
{
public:
	void rva00072FE6();
};

typedef _STL::set<int> Rva000732B8Set;

class Rva000732B8
{
public:
	void rva000732B8();

private:
	int m_innerCount;			// +0
	int m_outerCount;			// +4
	char m_pad08[0x38 - 0x08];
	unsigned char *m_left;		// +0x38
	unsigned char *m_right;		// +0x3C
	char m_pad40[8];
	unsigned char m_complete;	// +0x48
	char m_pad49[3];
	Rva000732B8Set m_differences;	// +0x4C
};

void Rva000732B8::rva000732B8()
{
	((Rva00072FE6 *)(void *)&m_differences)->rva00072FE6();
	unsigned char *right = m_right;
	unsigned char *left = m_left;
	int key;
	int outer;
	outer = 0;
	key = 0;
	for (; outer < m_outerCount; ++outer) {
		int inner = 0;
		for (; inner < m_innerCount; ++inner, ++right, ++left, ++key) {
			if (*right != *left)
				m_differences.insert(key);
		}
	}
	m_complete = 1;
}

// Native 0x000740CE..0x00074136 is a complete 104-byte no-argument
// method. It repeats the measured nested byte-array comparison, but the
// completion flag is at +0x40 and the set at +0x44. Both calls independently
// reach the existing clear (0x72FE6) and set<int>::insert (0xBC15D) providers.
// The shared STLport operation is a source lead; the owner remains unknown.
typedef _STL::set<int> Rva000740CESet;

class Rva000740CE
{
public:
	void rva000740CE();

private:
	int m_innerCount;			// +0
	int m_outerCount;			// +4
	char m_pad08[0x38 - 0x08];
	unsigned char *m_left;		// +0x38
	unsigned char *m_right;		// +0x3C
	
	unsigned char m_complete;	// +0x40
	char m_pad41[3];
	Rva000740CESet m_differences;	// +0x44
};

void Rva000740CE::rva000740CE()
{
	((Rva00072FE6 *)(void *)&m_differences)->rva00072FE6();
	unsigned char *right = m_right;
	unsigned char *left = m_left;
	int key;
	int outer;
	outer = 0;
	key = 0;
	for (; outer < m_outerCount; ++outer) {
		int inner = 0;
		for (; inner < m_innerCount; ++inner, ++right, ++left, ++key) {
			if (*right != *left)
				m_differences.insert(key);
		}
	}
	m_complete = 1;
}
