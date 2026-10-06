// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva000B2B42Clamp@@YAXPAH0H@Z @0x000B2B42 58B:
// Clamp helper (void,int*,int*,int): *a1 clamped to [0,a3], sum=*a2+*a1orig
// min-clamped then max-clamped to a3, *a2=sum-clamped. Callers 0x000B6ACF
// 0x000B6B29 pass stack int slots plus word value.
void __cdecl Rva000B2B42Clamp(int *a1, int *a2, int a3)
{
	int v1 = *a1;
	int v2 = *a2;
	int sum = v2 + v1;
	if (v1 < 0)
		*a1 = 0;
	else if (v1 > a3)
		*a1 = a3;
	int clamped = *a1;
	if (sum < clamped)
		sum = clamped;
	else if (sum > a3)
		sum = a3;
	*a2 = sum - clamped;
}
