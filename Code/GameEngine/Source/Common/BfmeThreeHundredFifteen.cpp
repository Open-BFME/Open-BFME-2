// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// The partition filter base (ctor 0x000421C8, vftable 0x00BC26E0).
class Object;
class Rva000421C8
{
public:
	virtual ~Rva000421C8();
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

class BfmeAskerRJ
{
public:
	bool bfmeAskRJ(void *what, void *more);
};

// Partition filter vftable 0x00BCECF0 slot 1, built inline by RespawnUpdate
// 0x004AF1CE and 10 more matched users under this address-derived name.
class Rva002614ECFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *what);
	BfmeAskerRJ *m_bfmeSub;
	void *m_bfmeExtra;
	bool m_bfmeFlag;
};

bool Rva002614ECFilter::allow(Object *what)
{
	if (m_bfmeSub->bfmeAskRJ(what, m_bfmeExtra))
		return m_bfmeFlag;
	return !m_bfmeFlag;
}
