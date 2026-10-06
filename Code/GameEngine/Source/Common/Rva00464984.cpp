// cl: /MD
// Target evidence: Ghidra boundary 0x00464984, 29 bytes. Retail forwards a
// hinted tree insertion call to 0x0046444E and returns the iterator result.
// Addresses are target facts; synthetic Rva names avoid asserting the map type.
class Rva00464984Iterator {
public:
	Rva00464984Iterator(const Rva00464984Iterator &other) : m_node(other.m_node) {}
private:
	void *m_node;
};

class Rva00464984Pair;

class Rva0046444E {
public:
	Rva00464984Iterator rva0046444E(Rva00464984Iterator hint,
		const Rva00464984Pair &value);
};

class Rva00464984 {
public:
	Rva00464984Iterator rva00464984(Rva00464984Iterator hint,
		const Rva00464984Pair &value);
};

Rva00464984Iterator Rva00464984::rva00464984(
	Rva00464984Iterator hint, const Rva00464984Pair &value)
{
	return ((Rva0046444E *)this)->rva0046444E(hint, value);
}
