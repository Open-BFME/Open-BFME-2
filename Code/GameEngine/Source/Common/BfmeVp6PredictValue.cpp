// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva009B4880State
{
	unsigned char pad0[4];
	short *values;
	int selector;
};

struct Rva009B4880Neighbor
{
	unsigned char pad0[8];
	short selector;
	short value;
};

// Retail 0x00BD8D00: ten 32-bit mode-to-frame entries. The consumers
// read the low byte or word of each entry through this shared byte array.
unsigned char g_bfmeVp6SelectorMap[40] = {
    1, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  1, 0, 0, 0,  1, 0, 0, 0,
    2, 0, 0, 0,  2, 0, 0, 0,  1, 0, 0, 0,  2, 0, 0, 0,  2, 0, 0, 0
};

void Rva009B4880PredictValue(Rva009B4880State *state, int block,
	short *output, const Rva009B4880Neighbor *left,
	const Rva009B4880Neighbor *above)
{
	unsigned char selector = g_bfmeVp6SelectorMap[state->selector * 4];
	unsigned char count = 0;
	int sum = 0;

	if ((unsigned short)selector == (unsigned short)above->selector) {
		sum = above->value;
		count = 1;
	}
	if ((unsigned short)selector == (unsigned short)left->selector) {
		sum += left->value;
		++count;
	}

	if (count == 0)
		sum = output[selector];
	else if (count == 2)
		sum = (sum + ((unsigned short)sum >> 15)) >> 1;

	state->values[block << 6] += (short)sum;
	output[selector] = state->values[block << 6];
}
