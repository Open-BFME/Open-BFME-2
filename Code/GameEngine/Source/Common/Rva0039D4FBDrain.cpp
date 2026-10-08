// flags: region default (reverse/retail_inventory/flag_regions.csv)

// ?removeAll_TeamInstanceList@TeamPrototype@@QAEXP6AXPAVRva0039D40F@@@Z@Z @0x0039D4FB (42B).
// List-drain: while the +0x334 head holds a node, unlinks it via the rowed
// 0x0039D4D8 conditional remove then invokes the callback on it when present.
// Retail shape is head-load loop plus remove call plus null-gated indirect
// call with pop-clean plus ret 4. Sibling of the 0x0039D4B5/0x0039D4D8 pair
// sharing the same head layout; caller at 0x003A33F3 passes the callback.
// Owner of the head side is unproven so the name keeps the address token.

class Rva0039D40F
{
public:
	char m_pad00[0x3C];
	Rva0039D40F *m_prev3C; // +0x3C
	Rva0039D40F *m_next40; // +0x40
};

class Rva0039D4D8
{
public:
	void rva0039D4D8(Rva0039D40F *obj);
};

class TeamPrototype
{
public:
	void removeAll_TeamInstanceList(void (*cb)(Rva0039D40F *));

private:
	char m_pad00[0x334];
	Rva0039D40F *m_head334; // +0x334
};

void TeamPrototype::removeAll_TeamInstanceList(void (*cb)(Rva0039D40F *))
{
	Rva0039D40F *node;
	while( (node = m_head334) != 0 )
	{
		((Rva0039D4D8 *)this)->rva0039D4D8(node);
		if( cb != 0 )
		{
			cb(node);
		}
	}
}
