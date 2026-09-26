// cl: /O1 /MD
//
// ScriptList::swap at 0x003B58DF (57B). The by-value ScriptList is 0x4C
// bytes: a 4-byte head, an 8-byte Gen_00350E60-style record at +0x04
// (swapped through the rowed bfmeSwap at 0x003B33FA) and two 0x20-byte
// subrecords at +0x0C/+0x2C (each two 12-byte vectors plus two ints,
// swapped through 0x003B56A5). The Gen argument is a null-checked
// selection (neg/sbb/and): retail passes a possibly-null other through,
// so the source spells the ternary explicitly. The subrecord swap has no
// proven class name yet, so it is called through the address-derived
// ?swap@Rva003B56A5@@QAEXPAV1@@Z pin; the vectors inside it are
// layout-identical 12-byte swaps. Reached via the SidesInfo rowed
// setScriptList tail jump (0x003297F3) and SidesInfo::swap.

class Gen_00350E60
{
public:
	void bfmeSwap(Gen_00350E60 *other);

private:
	int m_first;					// +0x00
	int m_second;					// +0x04
};

class Rva003B56A5
{
public:
	void swap(Rva003B56A5 *other);

private:
	char m_data[0x20];
};

class ScriptList
{
public:
	void swap(ScriptList *other);

private:
	char m_pad[4];					// +0x00
	Gen_00350E60 m_gen;				// +0x04
	Rva003B56A5 m_first;			// +0x0C
	Rva003B56A5 m_second;			// +0x2C
};

// ?swap@ScriptList@@QAEXPAV1@@Z
void ScriptList::swap(ScriptList *other)
{
	m_gen.bfmeSwap(other ? &other->m_gen : 0);
	m_first.swap(&other->m_first);
	m_second.swap(&other->m_second);
}
