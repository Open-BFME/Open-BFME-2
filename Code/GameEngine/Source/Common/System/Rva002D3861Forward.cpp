// cl: /O1
// ?rva002D3861@Rva002D3861@@QAEXXZ @0x002D3861 8B
// Leaf forwarder between 0x002D3850 and 0x002D387A: loads member at +0x10
// and tail-jmps to rowed 0x002D2F32. Callee rowed in Rva002D2F32Post.cpp.
// Caller 0x0042BE7A in unclaimed 0x0042B0DE.
class Rva002D2F32Owner
{
public:
	void rva002D2F32();
};

class Rva002D3861
{
public:
	void rva002D3861();
private:
	unsigned char m_pad00[0x10];
	Rva002D2F32Owner *m_10; // +0x10
};

void Rva002D3861::rva002D3861()
{
	return m_10->rva002D2F32();
}
