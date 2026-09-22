// ?bfmeGo76A0@@YAXHPAHPAXHHH1@Z
// partial score=0.95 date=2026-09-22
// cl: /DNDEBUG /MD /O2
void __cdecl bfmeGo76A0(
	int delta, int *table, void *p2, int a, int rows, int columns, void *weights)
{
	if ((unsigned int)rows > 0)
	{
		const int *coefficient = (const int *)weights;
		unsigned char *sourcePointer = (unsigned char *)delta;
		do
		{
			int column = 0;
			if ((unsigned int)columns > 0)
			{
				unsigned char *previous = sourcePointer - a;
				do
				{
					int value = (sourcePointer + a)[a] * coefficient[3];
					value += sourcePointer[0] * coefficient[1];
					value += (sourcePointer + a)[0] * coefficient[2];
					value += previous[0] * coefficient[0];
					value = (value + 0x40) >> 7;
					if (value < 0)
						value = 0;
					else if (value > 0xFF)
						value = 0xFF;
					table[column] = value;
					++sourcePointer;
					++previous;
					++column;
				}
				while ((unsigned int)column < (unsigned int)columns);
			}
			sourcePointer = sourcePointer + ((int)p2 - columns);
			table = table + columns;
		}
		while (--rows != 0);
	}
}
