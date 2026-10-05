// cl: /O1 /MD
// Dynamic initializer of a file-scope float holding the cosine of 0.2
// degrees. Target evidence: game.dat's __xc_a table points at 0x007AC7FF;
// the body loads the double 0x3F6C987111111111 (0x00BCF1C0), calls the CRT
// cos through its import thunk (0x0062920A) and stores the result as a float
// at 0x00DEBE08, which code near 0x000F310F compares against with fcompi.
// The constant is 0.2 * (double)PI / 180 with PI a float literal: Zero Hour's
// DEG_TO_RADF(0.2) with a double argument folds to exactly these bits, where
// DEG_TO_RADF(0.2f) does not. The owning TU and the global's name are not
// established; the RVA name stands in for it.
extern "C" double __cdecl cos( double );

#define PI 3.14159265359f
#define DEG_TO_RADF(x) ((x)*PI/180.0f)

extern float g_Va00DEBE08;
float g_Va00DEBE08 = (float)cos( DEG_TO_RADF( 0.2 ) );
