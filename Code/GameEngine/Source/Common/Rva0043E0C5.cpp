// cl: /DNDEBUG /MD
//
// ?rva0043E0C5@Rva0043E0C5@@QAE_NH@Z, retail 0x0043E0C5, 109 bytes.
// Leaf __thiscall (reads ecx, ret 4 = one int arg) on an unproven lobby-UI
// class; honest Rva name. Rowed callees only: Rva0043DA65::rva0043DA65 for
// +0x5c (its int return is used as GameInfo*, per Rva0043DA65Getter.cpp),
// GameInfo::getSlot, GadgetComboBoxGetSelectedPos/GetItemData, and virtual
// slot 5 of +0x58 (bool return propagated as our own).
// Evidence: caller 0x00442E0B; neighbours Rva0043DBE0.cpp (same flags) and
// RvaTreeEraseClearFamily.cpp.

class GameWindow;

class GameSlot
{
public:
	char m_pad0[0x10]; // +0x00..+0x0F
	int m_10; // +0x10 slot tag compared against the value
	char m_pad1[0x20 - 0x14]; // +0x14..+0x1F
	void *m_item; // +0x20 compared against combo item data
};

class GameInfo
{
public:
	GameSlot *getSlot(int slot);
};

// Layout mirrors Code/GameEngine/Source/Common/Rva0043DA65Getter.cpp
// (vptr + two ints); only rva0043DA65 is called here.
class Rva0043DA65
{
public:
	int rva0043DA65();
private:
	virtual void slot0();
	virtual bool validate(int value);
	int m_unk4;
	int m_value;
};

void GadgetComboBoxGetSelectedPos(GameWindow *comboBox, int *selectedIndex);
void *GadgetComboBoxGetItemData(GameWindow *comboBox, int index);

// Identity of +0x58 unproven; slot order is what the bytes need
// (0x14 = 5 used by rva0043E0C5, 0x2C = 11 used by rva0043E132).
class Rva0043E058
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual bool v5(GameSlot *slot, void *data);
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual bool v11(GameSlot *slot, int value);
};

class Rva0043E0C5
{
public:
	bool rva0043E0C5(int index);
	bool rva0043E132(int index, int value);
private:
	char m_pad0[0x58]; // +0x00..+0x57
	Rva0043E058 *m_target; // +0x58
	Rva0043DA65 *m_provider; // +0x5C
	char m_pad1[0x7C - 0x60]; // +0x60..+0x7B
	int m_7c; // +0x7C
	char m_pad2[0x2B9 - 0x80]; // +0x80..+0x2B8
	bool m_2b9; // +0x2B9
	char m_pad3[0x2BE - 0x2BA]; // +0x2BA..+0x2BD
	bool m_2be; // +0x2BE
	bool m_2bf; // +0x2BF
	char m_pad4[0x2C3 - 0x2C0]; // +0x2C0..+0x2C2
	bool m_flag; // +0x2C3
	char m_pad5[0x354 - 0x2C4]; // +0x2C4..+0x353
	GameWindow *m_combo[8]; // +0x354, indexed by slot
};

bool Rva0043E0C5::rva0043E0C5(int index)
{
	GameInfo *info = reinterpret_cast<GameInfo *>(m_provider->rva0043DA65());
	if (info == 0)
		return false;
	m_flag = false;
	GameWindow *combo = m_combo[index];
	int sel;
	GadgetComboBoxGetSelectedPos(combo, &sel);
	void *data = GadgetComboBoxGetItemData(combo, sel);
	GameSlot *slot = info->getSlot(index);
	if (slot == 0)
		return false;
	if (data == slot->m_item)
		return false;
	return m_target->v5(slot, data);
}

// ?rva0043E132@Rva0043E0C5@@QAE_NHH@Z, retail 0x0043E132, 154 bytes.
// Same class: identical +0x58/+0x5C/+0x2C3 use, adjacent body. Two-int args
// (ret 8); rejects duplicate slot tags across getSlot(0..7), then the same
// flag + virtual-slot-11 tail. Evidence: callers 0x0043E712/0x00442ECC/0x00442F29.
bool Rva0043E0C5::rva0043E132(int index, int value)
{
	GameInfo *info = reinterpret_cast<GameInfo *>(m_provider->rva0043DA65());
	if (info == 0)
		return false;
	GameSlot *slot = info->getSlot(index);
	if (slot == 0)
		return false;
	if (value == slot->m_10)
		return false;
	if (value >= 0) {
		for (int i = 0; i < 8; ++i) {
			if (i == index)
				continue;
			GameSlot *other = info->getSlot(i);
			if (other != 0 && other->m_10 == value)
				return false;
		}
	}
	m_flag = false;
	bool ok = m_target->v11(slot, value);
	if (ok) {
		if (m_7c == 1) {
			m_2bf = true;
			m_2b9 = true;
		}
		m_2be = true;
	}
	return ok;
}
