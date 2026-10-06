// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004E58F5@Rva004E5821@@QAEPAXI@Z @0x004E58F5 28B.
// Deleting-dtor shape for Rva004E5821: run the rowed 0x004E5821 dtor, free
// through rowed operator delete 0x0002FD60 when the flag bit is set, return
// this. Retail is call / test byte [esp+8],1 / je / push esi / call delete /
// pop ecx / mov eax,esi (28B).
class Rva004E5821
{
public:
	void rva004E5821();
	void *rva004E58F5(unsigned int flags);
};

void *Rva004E5821::rva004E58F5(unsigned int flags)
{
	rva004E5821();
	if (flags & 1)
		::operator delete(this);
	return this;
}
