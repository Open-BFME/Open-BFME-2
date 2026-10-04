// cl: /O1 /DNDEBUG /MD
// ?rva0043DFE0@Rva0043DFE0@@QAE_NH@Z @0x0043DFE0 109B
// Evidence: leaf, provider +0x5C rva0043DA65 0x0043DA65, target +0x58 slot 0x30, flag +0x2C3, combo +0x314, slot item +0x1C, GadgetComboBoxGetSelectedPos 0x003228EB GetItemData 0x00322981 getSlot 0x003FF29F, caller 0x00442DF3.
class GameWindow;

class GameSlot
{
public:
	char m_pad[0x1C];
	void *m_item;
};

class GameInfo
{
public:
	GameSlot *getSlot(int slot);
};

class Rva0043DA65
{
public:
	int rva0043DA65();
};

void GadgetComboBoxGetSelectedPos(GameWindow *comboBox, int *selectedIndex);
void *GadgetComboBoxGetItemData(GameWindow *comboBox, int index);
void Rva00511730(int value);

class Rva0043DF58
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual bool v12(GameSlot *slot, void *data);
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16(int value);
};

class Rva0043DFE0
{
public:
	bool rva0043DFE0(int index);
	void rva0043DBA3();
private:
	char m_pad0[0x58];
	Rva0043DF58 *m_target;
	Rva0043DA65 *m_provider;
	char m_pad1[0x2C3 - 0x60];
	bool m_flag;
	bool m_2c4;
	char m_pad2[0x314 - 0x2C5];
	GameWindow *m_combo[8];
};

bool Rva0043DFE0::rva0043DFE0(int index)
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
	return m_target->v12(slot, data);
}

// ?rva0043DBA3@Rva0043DFE0@@QAEXXZ @0x0043DBA3 39B
// Evidence: leaf, flag +0x2C4, save 0x00511730(0), target +0x58 slot 0x40 with 1, callers 0x004444A0 0x005A4EB6.
void Rva0043DFE0::rva0043DBA3()
{
	if (m_2c4)
		return;
	Rva00511730(0);
	m_target->v16(1);
	m_2c4 = true;
}
