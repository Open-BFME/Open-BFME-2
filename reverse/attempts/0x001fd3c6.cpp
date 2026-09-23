// ?getNthPlayerTemplate@PlayerTemplateStore@@QBEPBVPlayerTemplate@@H@Z
// partial score=0.93 date=2026-09-23
// cl: /O1 /DNDEBUG /MD
//
// ?getNthPlayerTemplate@PlayerTemplateStore@@QBEPBVPlayerTemplate@@H@Z,
// retail 0x001FD3C6, 62 bytes. PlayerTemplateStore indexed accessor with
// stride-0x1DC bounds check and null-guarded override hop.
//
// Shape: negative-index early-out, (finish-start)/476 via signed idiv
// (byte-diff members force the explicit divide; typed vector would fold
// it), upper-bound early-out, start+index*476 element address, then the
// Overridable hop (ScienceStore precedent: m_nextOverride at +4, out-of-line
// getFinalOverride via pinned 0x1E35DF only when non-null, otherwise the
// element itself). Zero new pins (getFinalOverride resolves via the existing
// Overridable pin). Row supersedes the getNthPlayerTemplate pin.

#define NULL 0

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Overridable
{
public:
	void *m_vftable; // +0
	Overridable *m_nextOverride; // +4
	int m_isOverride; // +8
	int m_third; // +0xC

	const Overridable *getFinalOverride() const;
};

class PlayerTemplate : public Overridable
{
private:
	unsigned char m_pad[0x1DC - 0x10]; // total 0x1DC (476)
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(int index) const;

private:
	unsigned char m_pad[0xC]; // +0..+0xB
	char *m_start; // +0xC
	char *m_finish; // +0x10
};

// ?getNthPlayerTemplate@PlayerTemplateStore@@QBEPBVPlayerTemplate@@H@Z @0x001FD3C6
const PlayerTemplate *PlayerTemplateStore::getNthPlayerTemplate(int index) const
{
	if (index >= 0)
	{
		int count = (int)(m_finish - m_start) / 0x1DC;
		_ReadWriteBarrier();
		if ((unsigned int)index < (unsigned int)count)
		{
			char *elemAddr = m_start + index * 0x1DC;
			Overridable *over = *(Overridable **)(elemAddr + 4);
			if (over == NULL)
				return (const PlayerTemplate *)elemAddr;
			return (const PlayerTemplate *)over->getFinalOverride();
		}
	}
	return NULL;
}
