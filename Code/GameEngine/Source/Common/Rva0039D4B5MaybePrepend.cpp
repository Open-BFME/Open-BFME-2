// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?prependTo_TeamInstanceList@TeamPrototype@@QAEXPAVRva0039D40F@@@Z @0x0039D4B5 (35B).
// 0x0039D4B5 (35B) chain of the 0x39D40F/0x39D429 pair: when the node is not
// already in the +0x334 head list, prepends it. Retail shape is head lea
// plus isInList test plus conditional prepend plus pop plus ret 4. Caller
// at 0x003A3ADA inserts a fresh node into the +0x334 head of its peer;
// the +0x3C/+0x40 links prove the node side, owner of the head side is
// unproven so the name keeps the address token.

class Rva0039D40F
{
public:
	typedef bool Bool;
	Bool rva0039D40F(Rva0039D40F **head) const;
};

class Rva0039D429
{
public:
	void rva0039D429(Rva0039D429 **head);
};

class TeamPrototype
{
public:
	void prependTo_TeamInstanceList(Rva0039D40F *obj);

private:
	char m_pad00[0x334];
	Rva0039D40F *m_head334; // +0x334
};

void TeamPrototype::prependTo_TeamInstanceList(Rva0039D40F *obj)
{
	Rva0039D40F **head = &m_head334;
	if (obj->rva0039D40F(head)) {
		return;
	}
	((Rva0039D429 *)obj)->rva0039D429((Rva0039D429 **)head);
}
