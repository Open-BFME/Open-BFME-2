// ??0Rva008947A0Owner@@QAE@XZ
// Constructor: a destructible head member zeroed to 0 two further zeroed
// ints a self-pointer to the trailing array and a two-element array member
// built through the EH vector constructor iterator.
// Identity unrecovered; named from the address.

#include "../../Include/Common/BfmeRefVGO.h"

class Rva008947A0Elem : public BfmeRefVGO
{
public:
	Rva008947A0Elem();
};

// The head cleanup binds the chain destructor used by the native unwind state.
class Rva006CEAD0
{
public:
	Rva006CEAD0(void)
	{
		m_a = 0;
	}
	~Rva006CEAD0();

	int m_a;
};

class Rva008947A0Owner
{
public:
	Rva008947A0Owner(void);

	Rva006CEAD0 m_head;
	int m_b;
	int m_c;
	Rva008947A0Elem *m_items;
	Rva008947A0Elem m_array[2];
};

Rva008947A0Owner::Rva008947A0Owner(void)
	: m_b(0), m_c(0), m_items(m_array)
{
}
