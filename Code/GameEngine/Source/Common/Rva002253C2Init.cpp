// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva002253C2Init@@YAXXZ @ 0x002253C2 158B
// Heap setup: lowercases the command line, enables zerofill iff
// "-zerofillmemory" is present without "--zerofillmemory", clears then
// conditionally sets the zerofill flag, probes pool options, then registers
// four heaps via the guarded AddHeap forwarder. Evidence: callers at
// 0x0000179A thunk, strings "-zerofillmemory" "--zerofillmemory"
// " -poolbigblocks" " -bigmemorysentinals", IAT GetCommandLineA _strlwr
// strstr, rowed callees 0x000308B0 0x00030890 0x000308E0. Honest
// address-derived name. No STL.
extern "C" __declspec(dllimport) char *__stdcall GetCommandLineA();
extern "C" __declspec(dllimport) char *__cdecl _strlwr(char *str);
extern "C" __declspec(dllimport) char *__cdecl strstr(const char *s1, const char *s2);

void Rva000308B0Clear();
void Rva00030890Set();
void Rva000308E0AddHeap(unsigned int id, unsigned int size);

void Rva002253C2Init()
{
	char *cmd = _strlwr(GetCommandLineA());
	bool zerofill;
	if (cmd != 0 && strstr(cmd, "-zerofillmemory") != 0 && strstr(cmd, "--zerofillmemory") == 0)
		zerofill = true;
	else
		zerofill = false;
	Rva000308B0Clear();
	if (cmd != 0)
	{
		if (zerofill)
			Rva00030890Set();
		(void)strstr(cmd, " -poolbigblocks");
		(void)strstr(cmd, " -bigmemorysentinals");
	}
	Rva000308E0AddHeap(0, 0x10000000);
	Rva000308E0AddHeap(0x696e6974, 0x3000000);
	Rva000308E0AddHeap(0x61737374, 0x10000000);
	Rva000308E0AddHeap('str', 0x3000000);
}
