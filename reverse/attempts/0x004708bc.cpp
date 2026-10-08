// ?rva004708BC@HordeContain@@UAEPAVObject@@PBVMatrix3D@@@Z
// partial score=0.95 date=2026-10-08
// Banked slot 99 (HordeContain::rva004708BC, 0x004708BC, 613 B) for HordeContainIface11CSlots.cpp.
// Apply: the decls go before 'class HordeContain : public TransportContain, public Rva0046BB38Iface11C';
// also add Object fields m_244 (+0x244 Rva004708BCBehavior **), m_284 (+0x284 int), m_45C (+0x45C int),
// Object::bfmeTransferReplacementState(Object*), setWeaponSetFlag(WeaponSetType), protected findModule(NameKeyType) const,
// GameLogic::rva0023D0C2(Object*, int), iface gap99 -> virtual Object *rva004708BC(const Matrix3D *) = 0, and
// ContainModuleInterface slot93(int *, int). Compiles to 613 B; the only diff is at 0x4709A9: retail keeps the
// template in ebx and reloads the short +0x5D8 after _M_find (0x4DC8AB); MSVC 7.1 compiles the in-TU leaf
// _M_find first (bottom-up) and treats it as pure so it caches the short. Opaque-compare probes reload.
#if 0
// Slot 99's views. The interface at HordeContain +0xFC (vtable 0x00C47834):
// slot 0 (0x00466FE0) builds the replacement Object from a template.
class Rva00466FE0Iface
{
public:
	virtual Object *rva00466FE0(const ThingTemplate *tmpl, Rva0046A2ECContain *contain, Object *obj, const char *name, int a5) = 0;
};
// Rowed helpers, under the owner names their rows carry.
class Rva00469B73
{
public:
	void rva00469B73(void *obj);	// 0x00469B73
};
class Rva0028D891Owner
{
public:
	bool testBit(int bit) const;	// 0x0028D891
};
class Rva0040334B
{
public:
	void rva0040334B(Object *obj);	// 0x0040334B
};
class LifetimeUpdate
{
public:
	void setLifetimeRange(unsigned int minFrames, unsigned int maxFrames);	// 0x003A4AB3
	unsigned char m_pad00[0x20];
	unsigned int m_20; // +0x20 (the frame it dies on)
};
// A behavior module: its interface at +0x0C hands back, from slot 5, an
// optional interface whose slot 1 takes an Object ID.
class Rva004708BCSlot5Iface : public Rva00468D11Slots<1>
{
public:
	virtual void slot1(int id) = 0;
};
class Rva004708BCModuleHead
{
public:
	virtual void moduleHeadAnchor();
	void *m_04;
	void *m_08;
};
class Rva004708BCBehaviorIface : public Rva00468D11Slots<5>
{
public:
	virtual Rva004708BCSlot5Iface *slot5() = 0;
};
class Rva004708BCBehavior : public Rva004708BCModuleHead, public Rva004708BCBehaviorIface
{
};
// The +0x250 module's slot 31 and what it hands back (slots 4 and 121).
class Rva004708BCTail : public Rva00468D11Slots<4>
{
public:
	virtual void slot4(int a1) = 0;
};
class Rva004708BCTail121 : public Rva00468D11Slots<121>
{
public:
	virtual void slot121() = 0;
};
class Rva004708BCContain : public Rva00468D11Slots<31>
{
public:
	virtual Rva004708BCTail *slot31() = 0;
};
#endif
// ?rva004708BC@HordeContain@@UAEPAVObject@@PBVMatrix3D@@@Z @0x004708BC: slot 99;
// replaces the horde Object (which needs its +0x250 module) by one built from
// 0x0046AF12's template through the +0xFC interface: hands over the name and
// defection (status 0x3E), places it at the matrix, carries weapon-set bits
// 0x18-0x1A, its recorded experience (+0x258 map, else 1), contain slot 93
// with the old Object's +0x284, the attribute pool, the remaining lifetime and
// the slot-5 behavior links; then wakes the +0x250 module's slot-31 result.
Object *HordeContain::rva004708BC(const Matrix3D *mtx)
{
	Object *self = m_object;
	if (!self)
		return 0;
	Object *result = 0;
	Rva0046A2ECContain *contain = self->m_250;
	if (contain)
	{
	const ThingTemplate *tmpl = (const ThingTemplate *)rva0046AF12();
	if (tmpl)
	{
		result = ((Rva00466FE0Iface *)((char *)(UpdateModule *)this + 0xFC))->rva00466FE0(tmpl, contain, self, tmpl->m_64.str(), 0);
		if (self->testStatus((ObjectStatusTypes)0x3E))
			self->bfmeTransferReplacementState(result);
		TheGameLogic->rva0023D0C2(result, self->m_45C);
		result->setTransformMatrix(mtx);
		((Rva00469B73 *)(UpdateModule *)this)->rva00469B73(result);
		if (((const Rva0028D891Owner *)self)->testBit(0x18))
			result->setWeaponSetFlag((WeaponSetType)0x18);
		if (((const Rva0028D891Owner *)self)->testBit(0x19))
			result->setWeaponSetFlag((WeaponSetType)0x19);
		if (((const Rva0028D891Owner *)self)->testBit(0x1A))
			result->setWeaponSetFlag((WeaponSetType)0x1A);
		float xp = 1.0f;
		if (((_STL::map<unsigned short, int> *)&m_258)->find(result->m_template->m_5D8) != ((_STL::map<unsigned short, int> *)&m_258)->end())
			xp = m_258[result->m_template->m_5D8];
		result->m_264->rva0039B3D1(xp, false);
		slot93(&self->m_284, 0);
		AttributeModifierPoolUpdate *pool = self->findAttributeModifierPoolUpdate();
		if (pool)
			((Rva0040334B *)pool)->rva0040334B(result);
		static NameKeyType key = TheNameKeyGenerator->nameToKey("LifetimeUpdate");
		LifetimeUpdate *oldLife = (LifetimeUpdate *)self->findModule(key);
		if (oldLife)
		{
			LifetimeUpdate *newLife = (LifetimeUpdate *)result->findModule(key);
			if (newLife)
			{
				unsigned int left = oldLife->m_20 - TheGameLogic->m_frame;
				newLife->setLifetimeRange(left, left);
			}
		}
		for (Rva004708BCBehavior **m = self->m_244; *m; ++m)
		{
			if ((*m)->slot5())
			{
				for (Rva004708BCBehavior **n = result->m_244; *n; ++n)
				{
					Rva004708BCSlot5Iface *link = (*n)->slot5();
					if (link)
						link->slot1(self->m_74);
				}
				break;
			}
		}
	}
	Rva004708BCTail *tail = ((Rva004708BCContain *)contain)->slot31();
	if (tail)
	{
		tail->slot4(0);
		((Rva004708BCTail121 *)tail)->slot121();
	}
	}
	return result;
}
