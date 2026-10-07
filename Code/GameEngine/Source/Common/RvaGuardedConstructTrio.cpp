// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Three guarded explicit copy-constructions (18B each): mov ecx, [esp+4],
// test ecx, ecx, je ret, push [esp+8], call <copy-ctor>, ret. Each
// copy-constructs the source into the given buffer unless it is null.
// Nothrow copy ctors keep placement new free of EH scaffolding.
// 0x000A9DF8 and 0x000A9E0A carry peer _Construct pins (read from their
// vector push_back callers); 0x004D9ACE targets the rowed 33B copy ctor
// 0x004D971D, called by its real name. Element identities unproven
// (opaque element types); the wrapper names are address-derived.
// One ledger row per construction.

#include <new>

class Rva000AB3E2Element
{
public:
	Rva000AB3E2Element(const Rva000AB3E2Element &other) throw();
};

class Rva000AB419Element
{
public:
	Rva000AB419Element(const Rva000AB419Element &other) throw();
};

class Rva004D971D
{
public:
	Rva004D971D(const Rva004D971D &other) throw();
};

void Rva000A9DF8(void *buffer, const Rva000AB3E2Element &value)
{
	if (buffer)
		new (buffer) Rva000AB3E2Element(value);
}

void Rva000A9E0A(void *buffer, const Rva000AB419Element &value)
{
	if (buffer)
		new (buffer) Rva000AB419Element(value);
}
