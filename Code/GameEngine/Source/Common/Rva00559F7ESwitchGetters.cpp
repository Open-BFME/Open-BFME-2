// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Integer switch helpers near GameSpy preferences 0x00559F7E..0x00559FAC (46B).
// Sibling 2-case switch returners emitting push-imm8/pop-eax under /O1.
// Evidence: callers at 0x00559FCE and 0x00559FD4.

int Rva00559F7EGet(int a)
{
	switch (a) {
	case 0: return 2;
	case 1: return 4;
	default: return 0;
	}
}

int Rva00559F95Get(int a)
{
	switch (a) {
	case 0: return 3;
	case 1: return 2;
	default: return 0;
	}
}
