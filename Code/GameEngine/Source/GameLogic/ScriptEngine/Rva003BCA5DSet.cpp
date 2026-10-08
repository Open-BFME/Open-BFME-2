// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCA5DSet@@YGXE@Z @0x003BCA5D 11B evidence: mov ecx [0x00DFDC30] tail-jmp to rowed Rva001DD240::rva001DD276 at 0x001DD276; caller at 0x003CD716; siblings Rva003BCA43Do Rva003BCA7BSet fix stdcall void shape
class Rva001DD240 {
public:
	void rva001DD276(unsigned char flag);
};
extern class Eva *TheEva;
void __stdcall Rva003BCA5DSet(unsigned char flag)
{
	(*(Rva001DD240 **)&TheEva)->rva001DD276(flag);
}
