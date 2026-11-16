// Rva00226883: canonical declarations for a 12-byte tree container whose node free, clear and
// destructor are rowed; the header node pointer sits at +0x00 and the node count at +0x04.
#ifndef CANONICAL_RVA00226883_H
#define CANONICAL_RVA00226883_H

// The destructor's unit includes <stdlib.h> without dllimport first, so free is a direct call.
#include <stdlib.h>

// Header node holder: retail's destructor 0x0022C612 frees it inline after clear.
struct Rva00226883Header
{
	void *m_00Head;
	__forceinline ~Rva00226883Header()
	{
		if (m_00Head)
			free(m_00Head);
	}
};

class Rva00226883
{
public:
	~Rva00226883();
	void rva00226883(void *node);
	void rva0022999F();

private:
	Rva00226883Header m_header; // +0x00
	int m_04Flag; // +0x04
	char m_08[4]; // +0x08, sizeof 12 from retail's 0x0C member spacing at 0x005EBCCE
};

#endif // CANONICAL_RVA00226883_H
