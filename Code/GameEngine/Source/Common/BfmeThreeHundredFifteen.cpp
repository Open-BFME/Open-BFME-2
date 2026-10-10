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

// 0x00362437 is rowed as Rva2225E0Filter::accepts(Object *, Player *); the old
// ?bfmeAskRJ@BfmeAskerRJ@@QAE_NPAX0@Z pin names the same body.
class Player;
class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};

// Partition filter vftable 0x00BCECF0 slot 1, built inline by RespawnUpdate
// 0x004AF1CE and 10 more matched users under this address-derived name.
class Rva002614ECFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *what);
	Rva2225E0Filter *m_bfmeSub;
	void *m_bfmeExtra;
	bool m_bfmeFlag;
};

bool Rva002614ECFilter::allow(Object *what)
{
	if (m_bfmeSub->accepts(what, (Player *)m_bfmeExtra))
		return m_bfmeFlag;
	return !m_bfmeFlag;
}
