// cl: /O1 /DNDEBUG /MD
//
// Three Object methods (retail Object.cpp range; this is the Object: its +0x10C
// model-condition words and the pinned notifier 0x0028AE6D). Names by address.
// Retail 0x00290758 (73 bytes): set condition bit 2*32+21 when the second
// argument is positive, else clear it (cl merges the two notifier calls), then
// forward both arguments to the matched Rva002716Holder broadcast on the +0x84
// member (tail jump).
// Retail 0x00293DAC / 0x00293E08 (92 bytes each): take the Object returned by
// the matched Object::rva002931F5(false); when it has the interface returned by
// the matched Object::rva0028C197, fill a (?, list) pair from its slot 66 and
// set (0x00290963) / clear (0x00290A10) the weapon set flag on every listed
// Object, then on that Object itself. The list is walked through raw nodes
// (next at +0, Object at +8) with the end reloaded each pass, as retail does.
// Retail 0x0029130C (114 bytes): by mode, clear both condition bits 17*32+2 and
// 17*32+3 (mode 2), set the first and clear the second (mode 0), or set the
// second and clear the first (any other mode). Retail tests the bits through a
// pointer to the word computed once (lea edi, [esi+0x150]) while the updates
// address the member directly: the tests go through a const pointer to the
// bits held in a local, the updates through the member itself.
// Retail 0x00293955 (176 bytes) / 0x00293A05 (166 bytes): the same passenger
// walk as 0x00293DAC/0x00293E08 clearing / setting the model condition given as
// argument on every listed Object and on the container (variable index:
// unsigned shr word index, mask hoisted out of the loop by cl).
// Model-condition bits as in ObjectWeaponSetFlags.cpp (word array at +0x10C,
// masked-word accessors).

enum WeaponSetType
{
	WEAPONSET_NONE = 0
};
enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};
class Rva002716Holder
{
public:
	void Rva0027164EBroadcast(int a, int b);
};
class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
	unsigned int testIndex(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void setIndex(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clearIndex(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[20];
};
class Rva00346BC0;
class Object;
struct Rva00293DACNode
{
	Rva00293DACNode *m_next;
	Rva00293DACNode *m_prev;
	Object *m_object;
};
struct Rva00293DACList
{
	Rva00293DACNode *m_head;
};
struct Rva00293DACRange
{
	int m_00;
	const Rva00293DACList *m_list;
};
template <int N> class Rva00293DACSlots : public Rva00293DACSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00293DACSlots<0>
{
};
// Interface returned by the matched Object::rva0028C197: slots 0..65
// placeholders, slot 66 fills a (?, list) pair.
class Rva00293DACIface : public Rva00293DACSlots<66>
{
public:
	virtual void rva00293DACSlot66(Rva00293DACRange *out) = 0;
};
class Object
{
public:
	void rva0028AE6D();
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);
	void rva00293D3B(const Rva00346BC0 &mask, bool set);
	Object *rva002931F5(bool flag);
	void *rva0028C197() const;
	void setWeaponSetFlag(WeaponSetType wst);
	void clearWeaponSetFlag(WeaponSetType wst);
	void rva00290758(int a, int b);
	void rva00293DAC(WeaponSetType wst);
	void rva00293E08(WeaponSetType wst);
	void rva0029130C(int mode);
	void rva00293955(ModelConditionFlagType mc);
	void rva00293A05(ModelConditionFlagType mc);
	void rva00293AAB(ModelConditionFlagType a, ModelConditionFlagType b);
	void rva001E42F2(const int *x);
	void rva00293BBF(const int *x);
	void rva001E431E(const int *x);
	void rva00293C1B(const int *x);
	void rva0028CFB2(const int *a, const int *b);
	void rva00293C77(const int *a, const int *b);
	void rva0028CFF5(const int *a, bool b);
	void rva00293CD9(const int *a, bool b);
	__forceinline void setConditionIndex(ModelConditionFlagType mc)
	{
		if (m_conditionBits.testIndex(mc) == 0)
		{
			m_conditionBits.setIndex(mc);
			rva0028AE6D();
		}
	}
	__forceinline void clearConditionIndex(ModelConditionFlagType mc)
	{
		if (m_conditionBits.testIndex(mc) != 0)
		{
			m_conditionBits.clearIndex(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x84];
	Rva002716Holder *m_84; // +0x84
	unsigned char m_pad088[0x10C - 0x88];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad15C[0x455 - 0x15C];
	bool m_statusPropagationGuard455; // Native 0x293D3B tests this byte; meaning unproven.
};
void Object::rva00290758(int a, int b)
{
	if (b > 0)
	{
		if (m_conditionBits.test(2 * 32 + 21) == 0)
		{
			m_conditionBits.set(2 * 32 + 21);
			rva0028AE6D();
		}
	}
	else
	{
		if (m_conditionBits.test(2 * 32 + 21) != 0)
		{
			m_conditionBits.clear(2 * 32 + 21);
			rva0028AE6D();
		}
	}
	if (m_84)
		m_84->Rva0027164EBroadcast(a, b);
}
void Object::rva00293DAC(WeaponSetType wst)
{
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (iface)
		{
			Rva00293DACRange range;
			iface->rva00293DACSlot66(&range);
			for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
				node->m_object->setWeaponSetFlag(wst);
			top->setWeaponSetFlag(wst);
		}
	}
}
void Object::rva00293E08(WeaponSetType wst)
{
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (iface)
		{
			Rva00293DACRange range;
			iface->rva00293DACSlot66(&range);
			for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
				node->m_object->clearWeaponSetFlag(wst);
			top->clearWeaponSetFlag(wst);
		}
	}
}
void Object::rva0029130C(int mode)
{
	const Rva0010CBits *bits = &m_conditionBits;
	if (mode == 2)
	{
		if (bits->test(546)) { m_conditionBits.clear(546); rva0028AE6D(); }
		if (bits->test(547)) { m_conditionBits.clear(547); rva0028AE6D(); }
	}
	else if (mode == 0)
	{
		if (bits->test(546) == 0) { m_conditionBits.set(546); rva0028AE6D(); }
		if (bits->test(547)) { m_conditionBits.clear(547); rva0028AE6D(); }
	}
	else
	{
		if (bits->test(547) == 0) { m_conditionBits.set(547); rva0028AE6D(); }
		if (bits->test(546)) { m_conditionBits.clear(546); rva0028AE6D(); }
	}
}
void Object::rva00293955(ModelConditionFlagType mc)
{
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (iface)
		{
			Rva00293DACRange range;
			iface->rva00293DACSlot66(&range);
			for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
				node->m_object->clearConditionIndex(mc);
			top->clearConditionIndex(mc);
		}
	}
}
void Object::rva00293A05(ModelConditionFlagType mc)
{
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (iface)
		{
			Rva00293DACRange range;
			iface->rva00293DACSlot66(&range);
			for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
				node->m_object->setConditionIndex(mc);
			top->setConditionIndex(mc);
		}
	}
}
void Object::rva00293AAB(ModelConditionFlagType a, ModelConditionFlagType b)
{
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (iface)
		{
			Rva00293DACRange range;
			iface->rva00293DACSlot66(&range);
			for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
			{
				Object *obj = node->m_object;
				if (obj->m_conditionBits.testIndex(a) != 0 || obj->m_conditionBits.testIndex(b) == 0)
				{
					obj->m_conditionBits.clearIndex(a);
					obj->m_conditionBits.setIndex(b);
					obj->rva0028AE6D();
				}
			}
			if (top->m_conditionBits.testIndex(a) != 0 || top->m_conditionBits.testIndex(b) == 0)
			{
				top->m_conditionBits.clearIndex(a);
				top->m_conditionBits.setIndex(b);
				top->rva0028AE6D();
			}
		}
	}
}
void Object::rva00293BBF(const int *x)
{
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (iface)
		{
			Rva00293DACRange range;
			iface->rva00293DACSlot66(&range);
			for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
				node->m_object->rva001E42F2(x);
			top->rva001E42F2(x);
		}
	}
}
void Object::rva00293C1B(const int *x)
{
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (iface)
		{
			Rva00293DACRange range;
			iface->rva00293DACSlot66(&range);
			for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
				node->m_object->rva001E431E(x);
			top->rva001E431E(x);
		}
	}
}
void Object::rva00293C77(const int *a, const int *b)
{
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (iface)
		{
			Rva00293DACRange range;
			iface->rva00293DACSlot66(&range);
			for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
				node->m_object->rva0028CFB2(a, b);
			top->rva0028CFB2(a, b);
		}
	}
}
void Object::rva00293CD9(const int *a, bool b)
{
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (iface)
		{
			Rva00293DACRange range;
			iface->rva00293DACSlot66(&range);
			for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
				node->m_object->rva0028CFF5(a, b);
			top->rva0028CFF5(a, b);
		}
	}
}

// Native 0x00293D3B, 113 bytes, RET8: mask plus bool. Same Object receiver,
// container/list interface and raw node layout as adjacent matched 0x293DAC.
// Leaf 0x28CDEB independently ends RET8 and reads both incoming arguments.
void Object::rva00293D3B(const Rva00346BC0 &mask, bool set)
{
	if (m_statusPropagationGuard455)
		return;
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (!iface)
			return;
		Rva00293DACRange range;
		iface->rva00293DACSlot66(&range);
		for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
			node->m_object->rva0028CDEB(mask, set);
		top->rva0028CDEB(mask, set);
	}
	else
		rva0028CDEB(mask, set);
}
