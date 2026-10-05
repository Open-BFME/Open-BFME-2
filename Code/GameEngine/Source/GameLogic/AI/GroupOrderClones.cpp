// cl: /O1 /EHsc /MD /DNDEBUG
//
// Slot 13 of three BFME 2 group orders (no Zero Hour counterpart): a copy of
// the order on the heap, through the rowed operator new and the order's rowed
// copy ctor, the same shape as SynchronizeGroupOrder's slot 13 0x005469FD.
//
//   ChangeStanceGroupOrder    vtable 0x00C6A36C  0x00546B34  new(0x1C)  copy 0x00546B08
//   GarrisonObjectGroupOrder  vtable 0x00C6A3C4  0x00546CB8  new(0x28)  copy 0x00546C7F
//   AttackObjectGroupOrder    vtable 0x00C6A420  0x00546F6C  new(0x2C)  copy 0x00546F2F
//
// Sizes are the ones the group-order factory 0x00354EFC news. Names by address.
class GroupOrder
{
public:
	GroupOrder(const GroupOrder &other);
	virtual ~GroupOrder();
private:
	unsigned char m_pad04[0x18 - 4];
};

class ChangeStanceGroupOrder : public GroupOrder
{
public:
	ChangeStanceGroupOrder(const ChangeStanceGroupOrder &other);
	ChangeStanceGroupOrder *rva00546B34();
private:
	int m_stance; // +0x18
};

class GarrisonObjectGroupOrder : public GroupOrder
{
public:
	GarrisonObjectGroupOrder(const GarrisonObjectGroupOrder &other);
	GarrisonObjectGroupOrder *rva00546CB8();
private:
	unsigned char m_pad18[0x28 - 0x18];
};

class AttackObjectGroupOrder : public GroupOrder
{
public:
	AttackObjectGroupOrder(const AttackObjectGroupOrder &other);
	AttackObjectGroupOrder *rva00546F6C();
private:
	unsigned char m_pad18[0x2C - 0x18];
};

ChangeStanceGroupOrder *ChangeStanceGroupOrder::rva00546B34()
{
	return new ChangeStanceGroupOrder(*this);
}

GarrisonObjectGroupOrder *GarrisonObjectGroupOrder::rva00546CB8()
{
	return new GarrisonObjectGroupOrder(*this);
}

AttackObjectGroupOrder *AttackObjectGroupOrder::rva00546F6C()
{
	return new AttackObjectGroupOrder(*this);
}
