// ?Rva004B0E34Get@@YG_NI@Z
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva004B0E34Get@@YG_NI@Z, retail 0x004B0E34, 32 bytes.
// 12-way switch lowered to a byte index table (0x008B0E5C) plus a two-entry
// jump table (0x008B0E54): true for {3,4,5,6,7,10}, false otherwise.
// Evidence: caller 0x004B0FA0 chases the Gen_0028EF10-style link at +0x9C
// (same member as rowed bfmeValue 0x004B0E1F) and tail-calls this with
// *(int*)(link->m_bfmeNext + 4); both the shared-ret body and the byte table
// reproduce only under /O1.
bool __stdcall Rva004B0E34Get(unsigned int x)
{
	switch (x) {
	case 0: case 1: case 2: case 8: case 9: case 11:
		return false;
	case 3: case 4: case 5: case 6: case 7: case 10:
		return true;
	}
	return false;
}
