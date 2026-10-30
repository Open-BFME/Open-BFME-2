// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG
// Small bodies from .text gaps no Ghidra function covers (forty-third
// batch; see GapBodiesGE01.cpp), all from the /O2 /arch:SSE /G7 retail
// regions 0x00137590..0x00148B41 and 0x001541E0..0x00167E59
// (reverse/retail_inventory/flag_regions.csv). Each begins after its
// neighbour's padding or ret and ends in its own ret or tail jump. Retail
// bytes establish every shape; owning classes are not recovered, so each
// keeps an address-derived name and a view of only the members it touches.
// Callees and globals use the ledger's existing spellings.

class RenderObjClass;
class Vector2;

// --- 0x00141760 (25B): remove a render object from the rowed
// BFME2SceneSpatialIndex::Remove 0x00141640 when its +0x8C cell is set.
struct GapIndexedObject
{
	char m_pad00[0x8C];
	int m_cell;												// +0x8C
};

class BFME2SceneSpatialIndex
{
public:
	void Remove(RenderObjClass *obj);
	void rva00141760(RenderObjClass *obj);
};

void BFME2SceneSpatialIndex::rva00141760(RenderObjClass *obj)
{
	if (((GapIndexedObject *)obj)->m_cell >= 0)
		Remove(obj);
}

// --- 0x00143390 (19B): slot i of the +0xE8 table is set.
class Rva00143390
{
public:
	bool rva00143390(int i) const;
private:
	char m_pad00[0xE8];
	void *m_slots[8];										// +0xE8
};

bool Rva00143390::rva00143390(int i) const
{
	return m_slots[i] != 0;
}

// --- 0x001434A0 (33B): count the leading set entries (at most eight) of
// the +0x10 table of the +0x94 object.
struct GapSlotTable
{
	char m_pad00[0x10];
	void *m_entries[9];										// +0x10
};

class Rva001434A0
{
public:
	int rva001434A0() const;
private:
	char m_pad00[0x94];
	GapSlotTable *m_table;									// +0x94
};

int Rva001434A0::rva001434A0() const
{
	int count;
	for (count = 0; m_table->m_entries[count] != 0 && count < 8; ++count)
	{
	}
	return count;
}

// --- 0x00144340 / 0x00144360 (23B each): colour / UV array i of the leading
// model's +0x94 material description (rowed MeshMatDescClass getters).
class MeshMatDescClass
{
public:
	unsigned int *Get_Color_Array(int index, bool create);
	Vector2 *Get_UV_Array_By_Index(int index, bool create);
};

struct GapModelView
{
	unsigned int *colors(int index) { return m_matDesc->Get_Color_Array(index, false); }
	Vector2 *uvs(int index) { return m_matDesc->Get_UV_Array_By_Index(index, false); }
	char m_pad00[0x94];
	MeshMatDescClass *m_matDesc;							// +0x94
};

class Rva00144340
{
public:
	unsigned int *getColorArray(int index);
	Vector2 *getUVArrayByIndex(int index);
private:
	GapModelView *m_model;
};

unsigned int *Rva00144340::getColorArray(int index)
{
	return m_model->colors(index);
}

Vector2 *Rva00144340::getUVArrayByIndex(int index)
{
	return m_model->uvs(index);
}

// --- 0x00144650 (22B): append a present object to the +0x1C multi-list
// through the rowed GenericMultiListClass::Internal_Add_Tail.
class MultiListObjectClass;

class GenericMultiListClass
{
protected:
	bool Internal_Add_Tail(MultiListObjectClass *obj, bool onlyOnce);
};

class GapMultiList : public GenericMultiListClass
{
public:
	bool Add_Tail(MultiListObjectClass *obj) { return Internal_Add_Tail(obj, true); }
};

class Rva00144650
{
public:
	void rva00144650(MultiListObjectClass *obj);
private:
	char m_pad00[0x1C];
	GapMultiList m_list;									// +0x1C
};

void Rva00144650::rva00144650(MultiListObjectClass *obj)
{
	if (obj)
		m_list.Add_Tail(obj);
}

// --- 0x0015A840 / 0x0015A890 (72B each): the referenced item i of a
// stage's list (+0xE8 / +0x108) or, without one, the stage's single item
// (+0xA8 / +0xB8), with a reference added; 0x0015A960 (38B): the same
// lookup over +0x108 / +0xB8 without the reference.
struct GapRefItem
{
	int m_00;
	int m_refs;												// +0x04
};

struct GapRefList
{
	int m_00;
	int m_04;
	GapRefItem **m_items;									// +0x08
};

class Rva0015A840
{
public:
	GapRefItem *getMaterial(int i, int stage);
	GapRefItem *rva0015A890(int i, int stage);
	GapRefItem *rva0015A960(int i, int stage) const;
private:
	char m_pad00[0xA8];
	GapRefItem *m_materials[4];
	GapRefItem *m_B8[12];
	GapRefList *m_E8[8];
	GapRefList *m_108[8];
};

GapRefItem *Rva0015A840::getMaterial(int i, int stage)
{
	GapRefList *list = m_E8[stage];
	if (list)
	{
		GapRefItem *item = list->m_items[i];
		if (item)
			item->m_refs += 1;
		return list->m_items[i];
	}
	GapRefItem *single = m_materials[stage];
	if (single)
	{
		single->m_refs += 1;
		return m_materials[stage];
	}
	return 0;
}

GapRefItem *Rva0015A840::rva0015A890(int i, int stage)
{
	GapRefList *list = m_108[stage];
	if (list)
	{
		GapRefItem *item = list->m_items[i];
		if (item)
			item->m_refs += 1;
		return list->m_items[i];
	}
	GapRefItem *single = m_B8[stage];
	if (single)
	{
		single->m_refs += 1;
		return m_B8[stage];
	}
	return 0;
}

GapRefItem *Rva0015A840::rva0015A960(int i, int stage) const
{
	if (m_108[stage])
		return m_108[stage]->m_items[i];
	return m_B8[stage];
}

// --- 0x0015AB00 (49B): counted-pointer assignment: add a reference to the
// new object, release the old one (slot 0 when the count reaches zero).
class GapCountedObject
{
public:
	virtual void Delete_This();
	int m_refs;												// +0x04
};

class Rva0015AB00
{
public:
	Rva0015AB00 &rva0015AB00(const Rva0015AB00 &that);
private:
	GapCountedObject *m_object;
};

Rva0015AB00 &Rva0015AB00::rva0015AB00(const Rva0015AB00 &that)
{
	if (this != &that)
	{
		if (that.m_object)
			that.m_object->m_refs += 1;
		GapCountedObject *old = m_object;
		if (old && --old->m_refs == 0)
			old->Delete_This();
		m_object = that.m_object;
	}
	return *this;
}

// --- 0x0015DFB0 (24B): copy a three-word value into +0x0C.
struct GapWords3
{
	int a;
	int b;
	int c;
};

class Rva0015DFB0
{
public:
	void rva0015DFB0(const GapWords3 &value);
private:
	char m_pad00[0x0C];
	int m_0C;
	int m_10;
	int m_14;
};

void Rva0015DFB0::rva0015DFB0(const GapWords3 &value)
{
	m_0C = value.a;
	m_10 = value.b;
	m_14 = value.c;
}
