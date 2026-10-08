// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes) whose shape needs /O1 /G7 (imul-scaled indexing), batch
// Z. As in VslotSmallBodiesA-Y, each class and method is address-derived
// and models only what its body touches. Meanings are not recovered.

typedef int Int;

// 0x00525886: of the sixteen 0x18-byte entries at +0x48, the first whose
// leading word equals the argument takes the +0x10 object's +0x10 word.
struct Rva00525886Entry
{
	Int m_00;
	char m_pad04[0x14];
};
struct Rva00525886Source
{
	char m_pad00[0x10];
	Int m_10;
};
class Rva00525886
{
public:
	void rva00525886(Int key);
private:
	char m_pad00[0x10];
	Rva00525886Source *m_10;
	char m_pad14[0x34];
	Rva00525886Entry m_entries[16];
};
void Rva00525886::rva00525886(Int key)
{
	for (Int i = 0; i < 16; i++)
	{
		if (m_entries[i].m_00 == key)
		{
			m_entries[i].m_00 = m_10->m_10;
			return;
		}
	}
}

// 0x003F468D (nineteen callers): word [b] of the 0x30-byte records that
// entry [a] (0x1C bytes each) of the +0x18 table points at from its +0x04.
struct Rva003F468DRecord
{
	Int m_00;
	char m_pad04[0x2C];
};
struct Rva003F468DRecords
{
	Int size() const { return m_end - m_begin; }
	Rva003F468DRecord *m_begin;
	Rva003F468DRecord *m_end;
};
struct Rva003F468DEntry
{
	Int m_00;
	Rva003F468DRecords m_records; // +0x04
	char m_pad0C[0x10];
};
class Rva003F468D
{
public:
	Int rva003F468D(Int a, Int b);
	Int rva003F4DAE(Int a);
private:
	char m_pad00[0x18];
	Rva003F468DEntry *m_18;
};
Int Rva003F468D::rva003F468D(Int a, Int b)
{
	return m_18[a].m_records.m_begin[b].m_00;
}
// 0x003F4DAE (28 B; LivingWorldLogic battle bodies and the tactical-victor
// lookup call it): the record count of entry [a], (end - begin) / 0x30.
Int Rva003F468D::rva003F4DAE(Int a)
{
	return m_18[a].m_records.size();
}
