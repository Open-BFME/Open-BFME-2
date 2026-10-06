// cl: /Ob2 /MD /EHsc
// ??1TileData@@UAE@XZ retail 0x0011172A 72B
// Own vptr BCFAC0 (??_7TileData, whose slot 1 is the rowed ??_GTileData
// 0x00111867); under EH state 0 the ref pointer at +0x2AB4 is released
// (decrement the count at +4, Delete_This through slot 0 at zero) and nulled
// when set; then the inline RefCountClass-style base dtor restores BC650C.
// Layout from the rowed ctor 0x00111850 (ref 1, +0x2AB4 zeroed). Helper
// class names are local.

class TileDataRefBase
{
public:
	virtual void Delete_This();
	virtual ~TileDataRefBase() {}

	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}

	int m_numRefs;
};

class TileData : public TileDataRefBase
{
public:
	virtual ~TileData();

private:
	unsigned char m_data[0x2AB4 - 8];
	TileDataRefBase *m_ref; // +0x2AB4
};

TileData::~TileData()
{
	if (m_ref)
	{
		m_ref->Release_Ref();
		m_ref = 0;
	}
}
