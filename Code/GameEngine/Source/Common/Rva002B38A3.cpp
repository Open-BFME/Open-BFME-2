// cl: /MD
//
// ?rva002B38A3@Rva002B38A3@@QAEPAXH@Z 47B @0x002B38A3: linear find over the
// pointer array at +0xCC/+0xD0; returns the element whose virtual slot
// 0x18 equals the key arg, or 0. Caller at 0x002BE9A1; unblocks 0x002BE8F9.

struct Rva002B38A3Elem
{
	virtual int v0();
	virtual int v1();
	virtual int v2();
	virtual int v3();
	virtual int v4();
	virtual int v5();
	virtual int getKey();
};

class Rva002B38A3
{
public:
	void *rva002B38A3(int key);
private:
	unsigned char m_pad00[0xCC];
	Rva002B38A3Elem **m_start; // +0xCC
	Rva002B38A3Elem **m_finish; // +0xD0
};

void *Rva002B38A3::rva002B38A3(int key)
{
	for (Rva002B38A3Elem **it = m_start; it != m_finish; ++it)
	{
		if ((*it)->getKey() == key)
			return *it;
	}
	return 0;
}
