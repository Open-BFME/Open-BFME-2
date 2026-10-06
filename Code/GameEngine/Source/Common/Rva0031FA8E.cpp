// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?rva0031FA8E@Rva0031FA8E@@QAEXXZ @0x0031FA8E 12B null-checked forward to ControlBarScheme::update.
// Evidence: retail derefs [ecx] then jmp to rowed ?update@ControlBarScheme@@QAEXXZ; caller at 0x0031E282; prev/next TUs share /O1 /EHsc /MD.
#include "ascii_string.h"

class ControlBarScheme
{
public:
	void update();
};

class Rva0031FA8E
{
public:
	void rva0031FA8E();
private:
	ControlBarScheme *m_scheme;
};

void Rva0031FA8E::rva0031FA8E()
{
	if (m_scheme)
		m_scheme->update();
}
