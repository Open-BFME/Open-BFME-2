// cl: /DNDEBUG /MD /EHsc
// ??1RadarMarkerClientUpdate@@UAE@XZ, retail 0x004C9C38, 69 bytes.
//
// RadarMarkerClientUpdate dtor: restores the derived vtable 0x00C5EDB8 then
// releases the smart referent at +0x0C through rowed release at 0x002D76BB
// plus8 slot1 when present then restores the intermediate vtable 0x00C170A4
// and calls the folded base dtor at 0x0049B47C via pinned
// ??1DrawableModule@@MAE@XZ. Layout follows the rowed ctor 0x004C9BCD
// (Rva00362EC7 base plus zeroed +0x0C) and the rowed instance factory
// 0x00252AD9 news 0x10; slot 4 pool key 0x004C9BF3 with string
// RadarMarkerClientUpdate proves the class. Shape follows W3DLightDraw
// dtor (explicit member release plus intermediate inline base).
class RadarMarker
{
public:
	void DeleteReference();
};

class DrawableModule
{
protected:
	virtual ~DrawableModule();

private:
	char m_pad04[8];
};

class Rva00362EC7 : public DrawableModule
{
public:
	~Rva00362EC7() {}
};

class RadarMarkerClientUpdate : public Rva00362EC7
{
public:
	virtual ~RadarMarkerClientUpdate();

private:
	RadarMarker *m_0C;
};

RadarMarkerClientUpdate::~RadarMarkerClientUpdate()
{
	if (m_0C != 0)
		m_0C->DeleteReference();
}
