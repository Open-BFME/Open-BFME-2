// Partial event view consumed by the native setter at 0x002D9508.
// Retail reads the selector at +0x38, copies twelve bytes to +0x3C, then
// clears the selector and sets the byte at +0x48. The earlier bytes and
// the complete object extent remain unasserted; this view is pointer-only.
#ifndef CANONICAL_RVA002D9508_H
#define CANONICAL_RVA002D9508_H

struct Rva002D9508Twelve
{
	int v0, v1, v2;
};

class Rva002D9508
{
public:
	void rva002D9508(const void *position);
	char m_pad[0x38];
	int m_state;
	Rva002D9508Twelve m_data;
	unsigned char m_flag;
};

#endif // CANONICAL_RVA002D9508_H
