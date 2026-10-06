// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0007240CGet@@YAHH_N@Z, retail 0x0007240C 49B.
// Free __cdecl mapper from small enum 1-5 to D3D-like codes 0x14-0x18.
// Case 5 selects 0x15 when second byte arg is non-zero else 0x16 via
// neg/sbb/add. Default returns 0. Called from 0x000727A7. Evidence:
// ret without stack cleanup plus dec-je chain and push-pop immediates.
int Rva0007240CGet(int kind, bool flag);

int Rva0007240CGet(int kind, bool flag)
{
	int ret = 0;
	switch (kind)
	{
	case 1:
		ret = 0x14;
		break;
	case 2:
		ret = 0x16;
		break;
	case 3:
		ret = 0x17;
		break;
	case 4:
		ret = 0x18;
		break;
	case 5:
		ret = flag ? 0x15 : 0x16;
		break;
	default:
		break;
	}
	return ret;
}
