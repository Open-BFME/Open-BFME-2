// cl: /O1 /arch:SSE /G7 /EHsc /MD
// ?rva005E9163@Rva005E91A9@@UAEXXZ @0x005E9163 23B: applies the check result for the
// object pointer at +0x1C (rowed 0x005E9137) to the flag sub-object at +8 (rowed
// 0x005E1160). Layout views are neutral.
class Rva00318F42;
unsigned char Rva005E9137Check(Rva00318F42 *target);
typedef bool (*Rva005E9137BoolFn)(Rva00318F42 *target);

#include "../../Include/Common/Rva005E1160Flag.h"

class Rva005E91A9
{
public:
	virtual ~Rva005E91A9();
	virtual void rva005E9163();
private:
	char m_pad04[4];
	char m_flag8[0x14];
	Rva00318F42 *m_target;
};

void Rva005E91A9::rva005E9163()
{
	reinterpret_cast<Rva005E1160Flag *>(m_flag8)->rva005E1160(((Rva005E9137BoolFn)Rva005E9137Check)(m_target));
}
