// Bounds-checked element accessors and linear searches over a pointer/count
// pair held in the owner.  Three element strides appear -- 0x30, 0x38 and 0x80
// -- and each is spelled by the multiply the compiler chose: lea+shl 4 for
// 0x30, imul for 0x38, shl 7 for 0x80.  The searches compare a dword at offset
// 8 of the element, which is the only element field the bytes name.
struct T2ElemA { char m_head[8]; int m_id; char m_tail[0x30 - 0xC]; };
struct GetterWord { int m_value; };
struct T2ElemB
{
	virtual ~T2ElemB();
	virtual void v1();
	virtual GetterWord get() const;
	char m_body[0x38 - 4];
};
struct T2ArrB
{
	T2ElemB *m_a;
	int m_n;
	__forceinline T2ElemB *at(int index)
	{
		if (index >= m_n)
			return 0;
		return m_a + index;
	}
};
struct T2ElemC { char m_head[8]; int m_id; char m_tail[0x80 - 0xC]; };

struct T2OwnerA
{
	char m_head[0x3C];
	T2ElemA *m_base;
	int m_count;

	T2ElemA *at(int index);
	T2ElemA *find(int id);
};

T2ElemA *T2OwnerA::at(int index)
{
	if (index >= m_count)
		return 0;
	return m_base + index;
}

T2ElemA *T2OwnerA::find(int id)
{
	T2ElemA *p = m_base;
	T2ElemA *end = m_base + m_count;
	while (p < end)
	{
		if (p->m_id == id)
			return p;
		++p;
	}
	return 0;
}

struct T2OwnerB
{
	char m_head[0x20];
	T2ArrB m_20;

	T2ElemB *at(int index);
	T2ElemB *find(int id);
};

T2ElemB *T2OwnerB::at(int index)
{
	if (index >= m_20.m_n)
		return 0;
	return m_20.m_a + index;
}

T2ElemB *T2OwnerB::find(int id)
{
	for (int i = 0; i < m_20.m_n; ++i)
	{
		T2ElemB *slot = m_20.at(i);
		GetterWord key;
		key = slot->get();
		if (key.m_value == id)
			return slot;
	}
	return 0;
}

struct T2OwnerC
{
	char m_head[0x1C];
	T2ElemC *m_base;
	int m_count;

	T2ElemC *at(int index);
	T2ElemC *find(int id);
};

T2ElemC *T2OwnerC::at(int index)
{
	if (index >= m_count)
		return 0;
	return m_base + index;
}

T2ElemC *T2OwnerC::find(int id)
{
	T2ElemC *p = m_base;
	T2ElemC *end = m_base + m_count;
	while (p < end)
	{
		if (p->m_id == id)
			return p;
		++p;
	}
	return 0;
}

// A free function that indexes a pointer table at offset 0x88 of its first
// argument; __cdecl, so the object arrives on the stack rather than in ecx.
struct T2TableOwner
{
	char m_head[0x88];
	void *m_slots[1];
};

void *t2_table_slot(T2TableOwner *owner, int index)
{
	return owner->m_slots[index];
}

// Three disp8 siblings of t2_table_slot (tables at +0xC/+0x3C/+0x6C instead
// of +0x88). One caller passes the same owner object to all three while
// walking 12 string entries, so the tables likely belong to one class, but
// the owner identity is unrecovered: each accessor gets a minimal owner
// struct mirroring T2TableOwner and an address-derived name.
struct T2TableOwner0C
{
	char m_head[0xC];
	void *m_slots[1];
};

void *Rva00021080TableSlot(T2TableOwner0C *owner, int index)
{
	return owner->m_slots[index];
}

struct T2TableOwner3C
{
	char m_head[0x3C];
	void *m_slots[1];
};

void *Rva00021090TableSlot(T2TableOwner3C *owner, int index)
{
	return owner->m_slots[index];
}

struct T2TableOwner6C
{
	char m_head[0x6C];
	void *m_slots[1];
};

void *Rva000210A0TableSlot(T2TableOwner6C *owner, int index)
{
	return owner->m_slots[index];
}

// BFME1 9cbfb551 Weapon.cpp's emitted getFireOCL body is the source lead.
// Native10E4A4..10E4B2 and10E4B2..10E4C6 are complete RET4 entries after
// the preceding RET4. They read raw four-byte slots at +B8, directly or
// through the pointer at +94. These accessed-prefix views assert neither
// original receiver identity nor slot value type or complete array bounds.
struct Rva0010E4A4Words
{
	char unknown00[0xB8];
	unsigned slots[1];
	unsigned rva0010E4A4(unsigned index) const;
};

unsigned Rva0010E4A4Words::rva0010E4A4(unsigned index) const
{
	return slots[index];
}

struct Rva0010E4B2Words
{
	char unknown00[0x94];
	const Rva0010E4A4Words *table;
	unsigned rva0010E4B2(unsigned index) const;
};

unsigned Rva0010E4B2Words::rva0010E4B2(unsigned index) const
{
	return table->slots[index];
}

// BFME1 9cbfb551 LivingWorld/Rva003B46A0.cpp emits the source lead.
// Native564C4C..564C58 is a complete RET4 entry between the independently
// rowed 564C40/12 and 564C58/37 bodies. It indexes the pointer at receiver
// offset zero with a 32-byte stride. Only that physical stride is proven;
// the original owner, element identity and container bounds remain unknown.
struct Rva00564C4CElement { unsigned char unknown[0x20]; };
struct Rva00564C4CArray
{
	Rva00564C4CElement *elements;
	void *at(unsigned index) const;
};

// Size optimization keeps retail's add-from-memory scheduling.
#pragma optimize("s", on)
void *Rva00564C4CArray::at(unsigned index) const
{
	return elements + index;
}
#pragma optimize("", on)

// BFME1 9cbfb551 whole PAVectorEraseRangeFamily003AF.cpp supplies the source
// lead in the clean named Common O2/x87/G6 min5 sweep. Sixteen donor vector
// names place here, so none establishes an original template or owner.
// Native6BE260..6BE26E is independently INT3-bounded: it reads receiver word0,
// shifts the unsigned stack index by4, adds the two words and pops4 bytes.
// No calls, globals, literals or witnessed direct/address references choose
// an element type or original receiver. This accessed-word projection keeps
// the 32-bit address arithmetic without claiming a container or full layout.
struct Rva006BE260
{
    unsigned int addressBits;
    unsigned int elementAddressBits(unsigned int index) const;
};

unsigned int Rva006BE260::elementAddressBits(unsigned int index) const
{
    return addressBits + (index << 4);
}
