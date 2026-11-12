// cl: /MD
// ??1Rva005F1749@@UAE@XZ @ 0x005F1749 14B
// Evidence: vtable 0x00C78EFC slot0; tail-jmp to rowed ?clear@Rva005F13CC@@QAEXXZ at +4; deleting dtor 0x005F1757 calls it; chain from 0x005F13CC which this session landed.
class Rva005F13CC
{
public:
	void clear();
};

namespace StrategicHUD { class RegionDetailsStructuresMovieClip; }

class StrategicHUD::RegionDetailsStructuresMovieClip
{
public:
	virtual ~RegionDetailsStructuresMovieClip();
	// Retail table 0x00C78EFC slots 1-4: the shared empty `ret` (0x000B3FD0).
	virtual void slot1() {}
	virtual void slot2() {}
	virtual void slot3() {}
	virtual void slot4() {}
private:
	Rva005F13CC m_04;
};

StrategicHUD::RegionDetailsStructuresMovieClip::~RegionDetailsStructuresMovieClip()
{
	m_04.clear();
}
