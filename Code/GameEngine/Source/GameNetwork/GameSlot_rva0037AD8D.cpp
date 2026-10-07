// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// GameSlot setter, retail 0x0037AD8D, 23 bytes: copies a CreateAHeroData
// into the slot's +0x64 member through the CreateAHeroData assignment
// 0x00409359, the same one GameSlot::reset 0x003FF50C uses on that member,
// then sets the byte at +0x60 that reset clears.
// Callers: the type-20 network handler 0x004CF1AD, with the slot from
// GameInfo::getSlot and the hero data it just loaded, and four unrowed
// callers. No reference source names it; the layout is the matched
// GameSlot's (GameSlotCtor.cpp).

class Xfer;

class CreateAHeroData
{
public:
	virtual ~CreateAHeroData();
	CreateAHeroData &operator=(const CreateAHeroData &that);

private:
	unsigned char m_fields[0x13C];
};

class GameSlot
{
public:
	void rva0037AD8D(const CreateAHeroData &data);

private:
	void *m_vptr;
	unsigned char m_pad04[0x60 - 4];
	bool m_hasHeroData;
	CreateAHeroData m_heroData;
};

void GameSlot::rva0037AD8D(const CreateAHeroData &data)
{
	m_heroData = data;
	m_hasHeroData = true;
}
