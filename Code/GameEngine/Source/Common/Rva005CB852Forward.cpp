// cl: /O1 /DNDEBUG /MD
//
// ?rva005CB852@Rva005CB852@@QAEXXZ @0x005CB852 8B: forwards to the object
// held at +0x04, tail-jumping to its 0x005CB748 (pinned; the body only this
// forwarder reaches). Called by the living-world per-frame method 0x00575038
// on its +0x48 member. Names stay address-derived.

class Rva005CB748
{
public:
	void rva005CB748();
};

class Rva005CB852
{
public:
	void rva005CB852();
private:
	int m_00;
	Rva005CB748 *m_04;	// +0x04
};

void Rva005CB852::rva005CB852()
{
	m_04->rva005CB748();
}
