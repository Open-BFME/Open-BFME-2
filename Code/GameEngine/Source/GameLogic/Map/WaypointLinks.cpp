// cl: /O1 /Ob0
// ?getLink@Waypoint@@QBEPAV1@H@Z @0x00085404
// ?addLink@Waypoint@@QAEXPAV1@@Z @0x00272306
// Waypoint link array: 8 slots at +0x20, count at +0x4C, source at +0x40.
// Dedicated TU so TerrainLogic callers keep out-of-line calls.

class Waypoint
{
public:
	Waypoint *getLink(int index) const;
	void addLink(Waypoint *other);

private:
	char m_pad00[0x20];
	Waypoint *m_links[8];
	Waypoint *m_linkSource;
	char m_pad44[8];
	int m_numLinks;
};

// ?getLink@Waypoint@@QBEPAV1@H@Z
Waypoint *Waypoint::getLink(int index) const
{
	return (index < 0 || index >= 8) ? 0 : m_links[index];
}

// ?addLink@Waypoint@@QAEXPAV1@@Z
void Waypoint::addLink(Waypoint *other)
{
	Waypoint *target = other;
	if (m_numLinks < 8)
	{
		m_links[m_numLinks] = target;
		++m_numLinks;
	}
	target->m_linkSource = this;
}
