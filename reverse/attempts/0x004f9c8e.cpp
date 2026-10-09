// 0x004F9C8E
// partial score=0.6 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP=
// NEAR (score ~0.85 by bytes: the instruction stream is the same apart from
// register choice and two stack slots). Retail keeps the counted object in
// esi (pushed inside the kind-bit branch) and releases the holder from esi
// after the factory/push_back calls; cl reloads holder.referent from its
// [ebp+8] home instead so it needs one callee-saved register less: this goes
// to edi (retail ebx) pos to esi (retail edi) and the ObjectID temporary gets
// [ebp-0x10] instead of the reused arg slot [ebp+8]. Tried: holder as an
// argument temporary / const holder / const member; none forward the value.
// Retail unwind map: state 0 = ??1Rva004F6093Holder@@QAE@XZ (0x002B2E8E) on
// [ebp+8]; state 1 = 0x004F69C3 (??1Rva0040CB11Entry@@QAE@XZ pin / row
// ??1Rva004F69C3@@QAE@XZ) on the factory result at [ebp-0x18]; with the
// factory row spelled as returning Rva004F6318Entry a landing also needs
// ??1Rva004F6318Entry@@QAE@XZ resolved to 0x004F69C3.
// ?rva004F9C8E@Rva004F971E@@QAEXPAUTreeHintRef00217D4C@@H@Z retail 0x004F9C8E..0x004F9D6A (220 bytes).
// LivingWorld auto-resolve battle: drop one unit (pos into the side's unit
// vector) after the battle loop at 0x004F9D6A found it dead.
// Evidence: both calls come from 0x004F9D6A (backward walk over the two
// 12-byte unit vectors at +0x0C with the side index); WB twin 0x012EF610.
// The unit's object (+0x08) id (+0xB4) goes into the ObjectID vector at
// +0x60 (pinned push_back 0x002E01C6); when the object's template
// (0x0037DC52) has kind bit 90 and the unit has a record at +0x28 the
// record word +0x1C and a counted object reference (refcount base at
// +0xAC; release 0x0007DEEF) are paired through rowed 0x004F6A1A and
// pushed into the entry vector at +0x6C (rowed push_back 0x0040E8D1);
// finally the unit is erased from its side vector (rowed 0x004F70D1).
// Class and method names are structural placeholders.

enum ObjectID { INVALID_ID = 0 };

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

struct Rva004F9C8EKindTemplate
{
	char m_pad[0x110];
	unsigned m_kindWord2;
};

class Rva0037DCA5
{
public:
	void *rva0037DC52();
	char m_pad[0xAC];
	TargetRef00217D4C m_ref;
	ObjectID m_id;
	ObjectID getID() const { return m_id; }
};

struct Rva004F9C8ERecord
{
	char m_pad[0x1C];
	int m_word;
};

struct Rva004F9C8EUnit
{
	char m_pad[8];
	Rva0037DCA5 *m_object;
	char m_pad0C[0x1C];
	Rva004F9C8ERecord *m_record;
	Rva0037DCA5 *getObject() const { return m_object; }
	Rva004F9C8ERecord *getRecord() const { return m_record; }
};

struct TreeHintRef00217D4C
{
	Rva004F9C8EUnit *m_unit;
	Rva004F9C8EUnit *operator->() const { return m_unit; }
};

class Rva004F6093Holder
{
public:
	Rva004F6093Holder(Rva0037DCA5 *p) : referent(p)
	{
		if (p)
			++p->m_ref.references;
	}
	~Rva004F6093Holder()
	{
		if (referent)
			ReleaseTreeHintRef00217D4C(&referent->m_ref);
	}
	Rva0037DCA5 *referent;
};

class Rva004F6318Entry
{
public:
	int key;
	Rva004F6093Holder holder;
};

Rva004F6318Entry Rva004F6A1A(const int *key, const Rva004F6093Holder &holder);

class Rva0040CB11Entry;

namespace _STL
{
template <class _Tp> class allocator {};
template <class _Tp, class _Alloc = allocator<_Tp> > class vector
{
public:
	void push_back(const _Tp &x);
	_Tp *_M_start, *_M_finish, *_M_end_of_storage;
};
}

class Rva004F70D1
{
public:
	TreeHintRef00217D4C *rva004F70D1(TreeHintRef00217D4C *pos);
	TreeHintRef00217D4C *m_begin, *m_finish, *m_end;
};

class Rva004F971E
{
public:
	void rva004F9C8E(TreeHintRef00217D4C *pos, int side);

private:
	char m_pad00[0x0C];
	Rva004F70D1 m_units[2];
	char m_pad24[0x60 - 0x24];
	_STL::vector<ObjectID> m_deadIDs;
	_STL::vector<Rva0040CB11Entry> m_entries;
};

void Rva004F971E::rva004F9C8E(TreeHintRef00217D4C *pos, int side)
{
	if ((*pos)->getObject()->getID() != INVALID_ID)
		m_deadIDs.push_back((*pos)->getObject()->getID());
	if (((Rva004F9C8EKindTemplate *)(*pos)->getObject()->rva0037DC52())->m_kindWord2 & (1u << 26))
	{
		Rva0037DCA5 *object = (*pos)->getObject();
		Rva004F9C8ERecord *record = (*pos)->getRecord();
		if (record)
		{
			int word = record->m_word;
			Rva004F6093Holder holder(object);
			m_entries.push_back((const Rva0040CB11Entry &)Rva004F6A1A(&word, holder));
		}
	}
	m_units[side].rva004F70D1(pos);
}
