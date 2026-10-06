// cl: /DNDEBUG /MD
// Retail RVA 0x0043F103, 33 bytes.
// ?rva0043F103@Rva0043F103@@QAEPAUTargetRef00217D4C@@H@Z is a lazy holder
// accessor: lea slot from this+index*4+4 with two Rva002BED91 at +4 and +8
// then virtual slot 0x50 creator plus rowed Rva002BED91::set 0x003F8396.
// Callers 0x0043FA68 with index 1 via +0x58 and 0x00441ECE with 0 then 1.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
struct Rva002BED91
{
	TargetRef00217D4C *m_ptr;
	void clear();
	void set(TargetRef00217D4C *p);
};
class Rva0043F103
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual TargetRef00217D4C *_M_slot_50();
	TargetRef00217D4C *rva0043F103(int index);
private:
	Rva002BED91 m_holders[2];
};
TargetRef00217D4C *Rva0043F103::rva0043F103(int index)
{
	Rva002BED91 *slot = &m_holders[index];
	if (!slot->m_ptr)
		slot->set(this->_M_slot_50());
	return slot->m_ptr;
}
