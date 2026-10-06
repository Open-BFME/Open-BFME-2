// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004E7AD7@Rva004E7A76@@QAEPAXI@Z @0x004E7AD7 28B.
// Deleting-dtor shape for Rva004E7A76: run the rowed 0x004E7A76 dtor, free
// through rowed operator delete 0x0002FD60 when the flag bit is set, return
// this. Same 28B twin shape as Rva004E58F5Delete.cpp.
class Rva004E7A76
{
public:
	void rva004E7A76();
	void *rva004E7AD7(unsigned int flags);
};

void *Rva004E7A76::rva004E7AD7(unsigned int flags)
{
	rva004E7A76();
	if (flags & 1)
		::operator delete(this);
	return this;
}
