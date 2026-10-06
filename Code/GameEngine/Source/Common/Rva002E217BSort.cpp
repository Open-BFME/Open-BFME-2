// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva002E217BSort@@YAXPAPAX0PAX@Z @0x002E217B 58B.
// Heap pop-sort via rowed 0x002E1F0A: while byte len>4 call Reinsert then
// shrink end. Evidence: and 0xfffffffc plus cmp 4 with byte-only and al 0xfc
// in loop needs /G7 like siblings; caller 0x002E2379; prev shares /O1.
void Rva002E1F0AReinsert(void **first, void **last, void *extra);
void Rva002E217BSort(void **base, void **end, void *extra)
{
	if ((((char *)end - (char *)base) & ~3) <= 4)
		return;
	do {
		Rva002E1F0AReinsert(base, end, extra);
		--end;
	} while ((((char *)end - (char *)base) & ~3) > 4);
}
