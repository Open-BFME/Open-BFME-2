// flags: region default (reverse/retail_inventory/flag_regions.csv)

// ?rva0039D4D8@Rva0039D4D8@@QAEXPAVRva0039D40F@@@Z @0x0039D4D8 (35B).
// Conditional remove of the 0x39D40F/0x39D440 pair: when the node is already
// in the +0x334 head list, unlinks it. Retail shape is head lea plus isInList
// test plus conditional remove plus pop plus ret 4. Sibling of the 0x0039D4B5
// maybe-prepend sharing the same head layout and callee pair; callers at
// 0x0039D504 and 0x003A3604 pass the node. Owner of the head side is unproven
// so the name keeps the address token.

class Rva0039D40F
{
public:
	typedef bool Bool;
	Bool rva0039D40F(Rva0039D40F **head) const;
};

class Rva0039D440
{
public:
	void rva0039D440(Rva0039D440 **head);
};

class Rva0039D4D8
{
public:
	void rva0039D4D8(Rva0039D40F *obj);

private:
	char m_pad00[0x334];
	Rva0039D40F *m_head334; // +0x334
};

void Rva0039D4D8::rva0039D4D8(Rva0039D40F *obj)
{
	Rva0039D40F **head = &m_head334;
	if( !obj->rva0039D40F(head) )
	{
		return;
	}
	((Rva0039D440 *)obj)->rva0039D440((Rva0039D440 **)head);
}
