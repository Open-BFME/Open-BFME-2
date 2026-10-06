// cl: /MD /EHsc
// ??1Rva00426745@@UAE@XZ retail 0x00426745 96B
// Two-base dtor: own vptrs C3C408 (+0) and C3C3F8 (+0xC); under EH state 1
// the object at +0x10 is deleted through its slot-0 deleting dtor with flag 0
// and the global ??3@YAXPAX@Z (a global-scope delete) and cleared; the second
// base's inline dtor restores BBB554 and the rowed first-base dtor
// ??1GameEngineDeletingBase@@UAE@XZ 0x001B4E74 runs. Names address-derived.

class Rva00426745Owned
{
public:
	virtual ~Rva00426745Owned();
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[8];
};

class Rva00426745SnapshotBase
{
public:
	virtual ~Rva00426745SnapshotBase() {}
};

class Rva00426745 : public GameEngineDeletingBase, public Rva00426745SnapshotBase
{
public:
	virtual ~Rva00426745();

private:
	Rva00426745Owned *m_owned; // +0x10
};

Rva00426745::~Rva00426745()
{
	::delete m_owned;
	m_owned = 0;
}
