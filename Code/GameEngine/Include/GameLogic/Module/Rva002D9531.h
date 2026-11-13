// Partial event view consumed by the native setter at 0x002D9531.
// For selector two/six at +0x38, retail stores the argument at +0x34
// and sets the selector to two. Earlier bytes and the complete object
// extent remain unasserted; this view is used through pointers only.
#ifndef CANONICAL_RVA002D9531_H
#define CANONICAL_RVA002D9531_H

class Rva002D9531
{
public:
	void rva002D9531(int value);
	char m_pad[0x34];
	int m_value;
	int m_state;
};

#endif // CANONICAL_RVA002D9531_H
