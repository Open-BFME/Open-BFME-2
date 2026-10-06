// cl: /MD
//
// ?rva00569393@Rva00569393@@QAEXPAX@Z @0x00569393 34B.
// Cursor loop over the +0x58/+0x5C pointer vector: for each element call the
// rowed 0x005691DB clear-on-match scan with (this, tag). Unlike the 0x00569373
// drain twin, 0x005691DB erases nothing, so this loop carries an explicit
// cursor. Honest address-derived names.
class BitRange;

class Rva005691DB
{
public:
	void rva005691DB(BitRange *host, void *tag);
};

class Rva00569393
{
public:
	void rva00569393(void *tag);
private:
	char m_pad[0x58];
	Rva005691DB **m_begin;	// +0x58
	Rva005691DB **m_end;	// +0x5C
};

void Rva00569393::rva00569393(void *tag)
{
	for (Rva005691DB **p = m_begin; p != m_end; ++p)
		(*p)->rva005691DB((BitRange *)this, tag);
}
