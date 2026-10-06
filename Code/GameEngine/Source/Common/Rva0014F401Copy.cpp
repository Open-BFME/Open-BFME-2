// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva0014F401@@QAE@ABV0@@Z retail 0x0014F401 11B: base copy ctor stores vtable 0x007C6F2C at [this] then ret 4 ignoring source. Callers 0x0014F480 0x0014F4A1 0x0014F4C2 push source and call here then install derived vtables 0x007D3854 0x007D385C 0x007D3864 and copy dword at +4. Shape matches Snapshot copy ctor precedent (empty copy with vtable store at /O1).

class Rva0014F401
{
public:
	virtual void dummy();
	Rva0014F401(const Rva0014F401 &other);
};

Rva0014F401::Rva0014F401(const Rva0014F401 &other)
{
}
