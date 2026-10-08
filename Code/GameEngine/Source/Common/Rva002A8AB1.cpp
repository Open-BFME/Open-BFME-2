// cl: /O1 /DNDEBUG /MD
//
// ?rva002A8AB1@Rva002A8F24@@QAEPAURva002A8AB1Record@@PAX@Z, retail 0x002A8AB1 (51B).
// Scan the pointer range at +0x914/+0x918 and return the first non-null find
// through rowed 0x004E95D4, else null; a null key returns null. 63 matched
// callers reach it under this name.
// Shape: the BFME2 WorldBuilder build has the same function (unnamed there,
// matched by call graph to the 0x004E95D4 callee) as a for loop testing
// `result == 0 && it != end` with a break after the call; that loop is
// retail's exact top-tested shape under /O1, where the plain for/break forms
// rotate the test to the bottom.

struct Rva002A8AB1Record
{
	char m_pad[0x160];
};

class Rva004E9600
{
public:
	void *rva004E95D4(void *p);
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *key);

private:
	char m_pad[0x914];
	Rva004E9600 **m_begin;	// +0x914
	Rva004E9600 **m_end;	// +0x918
};

Rva002A8AB1Record *Rva002A8F24::rva002A8AB1(void *key)
{
	Rva002A8AB1Record *result = 0;
	if (key)
	{
		for (Rva004E9600 **it = m_begin; result == 0 && it != m_end; ++it)
		{
			result = (Rva002A8AB1Record *)(*it)->rva004E95D4(key);
			if (result)
				break;
		}
	}
	return result;
}
