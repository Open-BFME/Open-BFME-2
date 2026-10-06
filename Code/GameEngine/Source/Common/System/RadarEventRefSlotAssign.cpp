// cl: /DNDEBUG /MD
//
// ??4RadarEventRefSlot@@QAEAAV0@ABV0@@Z @0x0004E490 45B: RadarEventRefSlot copy-assign
// Self-check plus inc new ref plus release old ref plus copy plus return *this.
// Evidence: inc 0x005D1A79 Rva005D1A79DwordCounter disp8+0x04 over RadarEventRef
// m_refCount; release 0x002D335B RadarEventRef; callers 0x0004E66D 0x0004EFC2.
class Rva005D1A79DwordCounter
{
public:
	void inc();
};

class RadarEventRef
{
public:
	void release();
};

class RadarEventRefSlot
{
public:
	RadarEventRefSlot &operator=(const RadarEventRefSlot &other);
private:
	RadarEventRef *m_ref;
};

RadarEventRefSlot &RadarEventRefSlot::operator=(const RadarEventRefSlot &other)
{
	if (this != &other) {
		if (other.m_ref)
			((Rva005D1A79DwordCounter *)other.m_ref)->inc();
		if (m_ref)
			m_ref->release();
		m_ref = other.m_ref;
	}
	return *this;
}
