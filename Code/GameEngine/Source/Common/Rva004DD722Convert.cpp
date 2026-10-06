// cl: /EHsc /DNDEBUG /MD
//
// ?Rva004DD722Get@@YAMH@Z @ 0x004DD722 (25B).
// Free int-to-float scaler: zero returns BfmeZeroRange else (float)value * g_integerToFloatScale.
// Evidence: callers at 0x004DD846 0x004DE0DE 0x004DE4FA 0x004DE518 push one int;
// BfmeZeroRange extern name in use plus g_integerToFloatScale float ref; prev/next both /O1.

// The data ledger identifies the shared read-only operand as float +0.0.
extern float g_integerToFloatScale;

float __cdecl Rva004DD722Get(int value)
{
	if (value == 0)
		return 0.0f;
	return (float)value * g_integerToFloatScale;
}

// The matched multiplier operand places this scalar at VA 0x00C52AD4.
// Its four initialized bytes (92 0A 06 3F) match BFME2 retail; retain the
// existing declaration's writable storage without inferring a retail owner.
float g_integerToFloatScale = 0.52359879f;
