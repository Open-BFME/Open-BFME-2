// cl: /O2 /DNDEBUG /MD
// ?tail005E589E@Rva005E589EForwarder@@QAEXXZ, retail 0x005E589E (79 bytes):
// refresh step reached from the forwarder 0x005E590F. Releases the +0x38
// owned pointer unless the +0x3C keep flag is set (rowed clear 0x000AD6F4),
// clears the flag, runs the +0x40 swapper forwarder 0x005F55D6, then hands
// the +0x18 army's command-point pair (rowed 0x00318FBE and
// GetMaxCommandPoints 0x003192B9) to slot 3 of the +0x10 chased target.
// Names address-derived.
#include "../../../../Include/Common/Rva000AD6F4.h"

class Rva005F55D6
{
public:
	void rva005F55D6();
};

#include "../../../../Include/GameClient/Rva00318FBE.h"
int GetMaxCommandPoints(void *army);

class Rva005E589ETarget
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void setCommandPoints(int current, int maximum);	// slot 3
};

class Rva0042D703PtrChaseField
{
public:
	int get() const;	// 0x0042D703
};

class Rva005E589EForwarder
{
public:
	void tail005E589E();
private:
	char m_pad00[0x10];
	Rva0042D703PtrChaseField *m_10;	// +0x10
	int m_14;
	Rva00318FBE *m_18;	// +0x18
	char m_pad1C[0x38 - 0x1C];
	Rva000AD6F4 m_38;	// +0x38
	bool m_keep3C;	// +0x3C
	char m_pad3D[3];
	Rva005F55D6 *m_40;	// +0x40
};

void Rva005E589EForwarder::tail005E589E()
{
	if (!m_keep3C)
		m_38.clear();
	m_keep3C = false;
	if (m_40)
		m_40->rva005F55D6();
	Rva005E589ETarget *target = (Rva005E589ETarget *)m_10->get();
	if (target)
		target->setCommandPoints(m_18->rva00318FBE(), GetMaxCommandPoints(m_18));
}