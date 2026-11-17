#ifndef BFME_RVA0056D915_VIEW_H
#define BFME_RVA0056D915_VIEW_H

#include "../../Include/GameClient/_bfme_AptGameWindow.h"

// Accessed native layout, not an original header path or recovered class name.
// Constructor 0x0056DB9B constructs the member at +0x27C and clears +0x29C
// and +0x2A0. Factory 0x0041025D allocates 0x2A4 bytes. The destructor at
// 0x0056D915 destroys that same member before its two-base Apt window.
class Rva005C9B76
{
public:
	Rva005C9B76(void *context);
	virtual ~Rva005C9B76();
private:
	char m_pad[0x1C - 4];
};

class Rva0056D915 : public _bfme_AptGameWindow
{
public:
	Rva0056D915(void *context);
	virtual ~Rva0056D915();
private:
	Rva005C9B76 m_member27C;
	char m_pad298[0x29C - 0x298];
	int m_29C;
	unsigned char m_2A0;
};

typedef char Rva0056D915_extent_2A4[(sizeof(Rva0056D915) == 0x2A4) ? 1 : -1];

#endif
