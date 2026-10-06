// cl: /DNDEBUG /MD

extern int g_bfmeTableC7E0;

extern void __cdecl Rva009A7950(
	int *, unsigned short *, int, int, int, int, const int *);
extern void __cdecl Rva009A7F60(
	int *, unsigned short *, int, int, int, int, const int *);

// Scalar VP6 8x8 interpolation helper at retail RVA 0x009A79D0 (BFME1) and
// 0x001B8430 (BFME2). The table global lives at a different address per game
// (DIR32 auto-patches from retail, no source change); the trailing worker
// resolves via pin. B1 0x009A79D0 295B -> B2 0x001B8430 295B,
// immediate-only drift (table address). The duplicate at B1 0x009A7FE0 is
// carried below (its B2 twin is 0x001B8A40, resolved by the BFME1->BFME2
// address map at prediction error 0).
void __cdecl Rva009A79D0Vp6Filter(
    const unsigned char *source,
	unsigned short *destination,
	int sourcePitch,
	const int *horizontalWeights,
	const int *verticalWeights)
{
    int sourceDelta = sourcePitch;
    sourceDelta -= 8;
    int *table = &g_bfmeTableC7E0;
    table += 2;
    int rows = 9;
    const unsigned char *sourcePointer = source;

    do
    {
        for (int column = -2; column <= 5; column++)
        {
            table[column] = (sourcePointer[0] * horizontalWeights[0] +
                              sourcePointer[1] * horizontalWeights[1] + 0x40) >> 7;
            sourcePointer++;
        }

        sourcePointer += sourceDelta;
		table += 8;
		--rows;
	}
	while (rows != 0);

	Rva009A7950(&g_bfmeTableC7E0, destination, 8, 8, 8, 8, verticalWeights);
}

// Byte-identical duplicate at B1 0x009A7FE0 -> B2 0x001B8A40 (address-map
// resolved, prediction error 0); its trailing call is the sibling worker
// Rva009A7F60 at the equivalent relative offset (0x80 back, same as
// 0x001B8430 -> 0x001B83B0).
void __cdecl Rva009A7FE0Vp6Filter(
    const unsigned char *source,
	unsigned short *destination,
	int sourcePitch,
	const int *horizontalWeights,
	const int *verticalWeights)
{
    int sourceDelta = sourcePitch;
    sourceDelta -= 8;
    int *table = &g_bfmeTableC7E0;
    table += 2;
    int rows = 9;
    const unsigned char *sourcePointer = source;

    do
    {
        for (int column = -2; column <= 5; column++)
        {
            table[column] = (sourcePointer[0] * horizontalWeights[0] +
                              sourcePointer[1] * horizontalWeights[1] + 0x40) >> 7;
            sourcePointer++;
        }

        sourcePointer += sourceDelta;
		table += 8;
		--rows;
	}
	while (rows != 0);

	Rva009A7F60(&g_bfmeTableC7E0, destination, 8, 8, 8, 8, verticalWeights);
}
