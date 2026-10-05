// cl: /O1 /MD
// ??0ChangeStanceGroupOrder@@QAE@PAVRva0036E346@@H@Z @0x00546AD0 31B evidence: stores vtable 0x0086A36C; base holder ctor rowed 0x00548A25; int at +0x18 from second arg; caller 0x00355A86 news int-sized; sibling default at 0x00546AEF in ChangeStanceGroupOrderCtor.cpp.
// Holder overload of ChangeStanceGroupOrder (naming via vtable).
class Rva0036E346;

class GroupOrder
{
public:
	GroupOrder(Rva0036E346 *holder);

protected:
	void *m_vtable; // +0
private:
	unsigned char m_pad04[0x18 - 4];
};

extern const void *const g_0086A36C[];

class ChangeStanceGroupOrder : public GroupOrder
{
public:
	ChangeStanceGroupOrder(Rva0036E346 *holder, int val);
private:
	int m_18;
};

ChangeStanceGroupOrder::ChangeStanceGroupOrder(Rva0036E346 *holder, int val)
	: GroupOrder(holder)
{
	m_18 = val;
	*(const void **)this = g_0086A36C;
}
