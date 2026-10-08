// cl: /O1 /DNDEBUG /MD
// stlport
//
// ?rva002B488E@Rva002BA8F1Logic@@QAEPAURva002B488EResult@@H@Z, retail 0x002B488E, 83B.
// The name is the one 8 matched callers already use. Target evidence: null
// key returns 0; otherwise walks the pointer vector at this+0x8C/+0x90
// (finish-minus-start shr 2 recomputed each pass), asks each element's
// rowed-pin 0x002E0A9F about the key and returns the first non-zero answer,
// else 0. Next to the LivingWorldLogic rows; names are placeholders.
#include <vector>

struct Rva002B488EResult;

class Rva002E0A9FElem
{
public:
	int rva002E0A9F(void *key);	// 0x002E0A9F
};

class Rva002BA8F1Logic
{
public:
	Rva002B488EResult *rva002B488E(int key);

private:
	unsigned char m_pad0[0x8C];
	std::vector<Rva002E0A9FElem *> m_elems;	// +0x8C
};

Rva002B488EResult *Rva002BA8F1Logic::rva002B488E(int key)
{
	if (key == 0)
		return 0;
	for (unsigned int i = 0; i < m_elems.size(); ++i)
	{
		int found = m_elems[i]->rva002E0A9F((void *)key);
		if (found)
			return (Rva002B488EResult *)found;
	}
	return 0;
}
