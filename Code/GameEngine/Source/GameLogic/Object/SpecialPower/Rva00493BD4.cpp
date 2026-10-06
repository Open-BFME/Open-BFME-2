// cl: /MD /GX /DNDEBUG /Oy-
// ?rva00493BD4@Rva00493BD4@@QAEXPAV1@@Z @0x00493BD4 134B. guarded copy of
// +0x14..0x24 when override ids match; evidence: calls
// ?friend_getFinalOverride@Overridable@@QBEPBV1@XZ at 0x00288609,
// virtual +0x18/+0x0C on embedded object at +0x10, caller 0x004ADCE8.

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;

private:
	unsigned char m_pad00[0x14];

public:
	int m_id14;

private:
	unsigned char m_pad18[0x59 - 0x18];

public:
	unsigned char m_flag59;
};

class Sub10
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual bool isBlocked();
	virtual void v10();
	virtual void v14();
	virtual const Overridable *getOverride();
	virtual void v1C();
};

class Rva00493BD4
{
public:
	void rva00493BD4(Rva00493BD4 *src);

private:
	unsigned char m_pad00[0x10];

public:
	Sub10 m_sub10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	unsigned char m_28;
};

void Rva00493BD4::rva00493BD4(Rva00493BD4 *src)
{
	const Overridable *a = src->m_sub10.getOverride();
	const Overridable *b = m_sub10.getOverride();
	if (a == 0)
		return;
	if (b == 0)
		return;
	if (a->friend_getFinalOverride()->m_id14 != b->friend_getFinalOverride()->m_id14)
		return;
	if (a->friend_getFinalOverride()->m_flag59 != 0)
		return;
	if (src->m_28 != 0)
		return;
	if (src->m_sub10.isBlocked())
		return;
	m_1c = src->m_1c;
	m_14 = src->m_14;
	m_20 = src->m_20;
	m_18 = src->m_18;
	m_24 = src->m_24;
}
