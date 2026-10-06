// cl: /MD /EHsc
// Dedicated TU for the fastcall multi-word random helper, retail 0x00233EC3
// (119 bytes). The RandomValue.cpp unit builds /O2, which materialises the
// ADC carry boolean through a hoisted constant; retail uses /O1 inc-shape.
// Split TU in the string_inline pattern so seedRandom keeps its flags.

typedef unsigned int UnsignedInt;

// Add with carry. SUM is replaced with A + B + C, C is replaced with 1  if there was a carry, 0 if there wasn't. A carry occurred if the sum is  less than one of the inputs. This is addition, so carry can never be  more than one.
#define ADC(SUM, A, B, C)   SUM = (A) + (B) + (C); C = ((SUM < (A)) || (SUM < (B)))

UnsignedInt __fastcall randomValue(UnsignedInt *seed)
{
	UnsignedInt ax;
	UnsignedInt c = 0;


	ADC(ax, seed[5], seed[4], c);
	seed[4] = ax;

	ADC(ax, ax, seed[3], c);
	seed[3] = ax;

	ADC(ax, ax, seed[2], c);
	seed[2] = ax;

	ADC(ax, ax, seed[1], c);
	seed[1] = ax;

	ADC(ax, ax, seed[0], c);
	seed[0] = ax;

	/* Increment seed array, bubbling up the carries. */
	if (!++seed[5])
	{
		if (!++seed[4])
		{
			if (!++seed[3])
			{
				if (!++seed[2])
				{
					if (!++seed[1])
					{
						++seed[0];
						++ax;
					}
				}
			}
		}
	}
	return(ax);
}
