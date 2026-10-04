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
};

class Rva0043DFE0
{
public:
	bool rva0043DFE0(int index);
private:
	char m_pad0[0x58];
	Rva0043DF58 *m_target;
	Rva0043DA65 *m_provider;
	char m_pad1[0x2C3 - 0x60];
	bool m_flag;
	char m_pad2[0x314 - 0x2C4];
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
