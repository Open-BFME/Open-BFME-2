void __cdecl bfmeGo7760(
	int *table, void *destinationAddress, int sourcePitch, int sourceDelta,
	int rows, int columns, void *weights)
{
	if ((unsigned int)rows > 0)
	{
		int columnCount = columns;
		const int *coefficient = (const int *)weights;
		int stride = (sourcePitch - columnCount) * 4;
		int rowCount = rows;
		int *sourcePointer = table;
		do
		{
			int column = 0;
			if ((unsigned int)columnCount > 0)
			{
				int *previous = sourcePointer - sourceDelta;
				do
				{
					int value = sourcePointer[sourceDelta * 2] * coefficient[3];
					value += sourcePointer[sourceDelta] * coefficient[2];
					value += sourcePointer[0] * coefficient[1];
					value += previous[0] * coefficient[0];
					value = (value + 0x40) >> 7;
					if (value < 0)
						value = 0;
					else if (value > 0xFF)
						value = 0xFF;
					((unsigned short *)destinationAddress)[column] = (unsigned short)value;
					++sourcePointer;
					++previous;
					++column;
				}
				while ((unsigned int)column < (unsigned int)columnCount);
			}
			sourcePointer = (int *)((unsigned char *)sourcePointer + stride);
			destinationAddress = (unsigned char *)destinationAddress + columnCount * 2;
		}
		while (--rowCount != 0);
	}
}

// BFME 1 donor 1399ad37d42ea52a63829e417c46a1ba9ed2cd20; native RVA 0x009A76A0.
// BFME 2 caller bfmeGo7820 (0x001B8280) selects this 8-bit input filter.
// Byte-source sibling of bfmeGo7760: four-tap filter from an 8-bit source
// into an int table. Called by bfmeGo7820 (0x009A7820) and bfmeGo79D0.
void __cdecl bfmeGo76A0(
	int sourceAddress, int *table, void *sourcePitch, int sourceDelta,
	int rows, int columns, void *weights)
{
	const int *coefficient = (const int *)weights;
	for (unsigned int row = 0; row < (unsigned int)rows; ++row)
	{
		const unsigned char *&sourcePointer = *(const unsigned char **)&sourceAddress;
		unsigned int column = 0;
		if ((unsigned int)columns > 0)
		do
		{
			const unsigned char *previous = sourcePointer - sourceDelta;
			int value = sourcePointer[sourceDelta + sourceDelta] * coefficient[3];
			value += sourcePointer[0] * coefficient[1];
			value += sourcePointer[sourceDelta] * coefficient[2];
			value = (value + previous[0] * coefficient[0] + 0x40) >> 7;
			if (value < 0)
				value = 0;
			else if (value > 0xFF)
				value = 0xFF;
			++sourcePointer;
			table[column] = value;
			++column;
		}
		while (column < (unsigned int)columns);
		sourcePointer += (int)sourcePitch - columns;
		table += columns;
	}
}
