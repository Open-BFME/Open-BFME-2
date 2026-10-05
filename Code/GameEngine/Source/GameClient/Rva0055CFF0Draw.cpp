// cl: /O1 /arch:SSE
// ?rva0055CFF0@Rva0055CFF0@@QAEXMMM@Z @0x0055CFF0 229B: draw 4 vertical box edges via TacticalView.
// Evidence: thiscall retC 3 floats vslot4 of BoxEmissionVolumeModule; rowed TheTacticalView; color 0xCCAFFFFF; 0 callers.

struct MiniBox
{
	float x;
	float y;
	float z;
};

class TacticalView
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10();
	virtual void drawBox(const MiniBox *a, const MiniBox *b, int color);
};

extern TacticalView *TheTacticalView;

class Rva0055CFF0
{
public:
	void rva0055CFF0(float x, float y, float z);
	char m_pad[0x24];
	float m_24;
	float m_28;
	float m_2C;
};

void Rva0055CFF0::rva0055CFF0(float x, float y, float z)
{
	int color = 0xCCAAFFFF;
	MiniBox b1;
	MiniBox b2;
	b1.x = x + m_24;
	b1.y = y + m_28;
	b1.z = z + m_2C;
	b2.x = x + m_24;
	b2.y = y + m_28;
	b2.z = z - m_2C;
	TheTacticalView->drawBox(&b1, &b2, color);
	b1.x = x - m_24;
	b2.x = x - m_24;
	TheTacticalView->drawBox(&b1, &b2, color);
	b1.y = y - m_28;
	b2.y = y - m_28;
	TheTacticalView->drawBox(&b1, &b2, color);
	b1.x = x + m_24;
	b2.x = x + m_24;
	TheTacticalView->drawBox(&b1, &b2, color);
}
