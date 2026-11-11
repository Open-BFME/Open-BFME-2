class AptCIH;
void bfmeUnpackTwoColors1280(float *output, const unsigned int *colors);

#include "../../../Libraries/Source/Apt/BfmeSubmitter1283.h"

void BfmeSubmitter1283::bfmeSubmitColors1283(int character, int depth, int pCharacter, int name, int parent,
	int replace, int clipDepth, const unsigned int *colors, int matrix, int actions, int ratio)
{
	float unpacked[8];
	if (colors != 0) {
		bfmeUnpackTwoColors1280(unpacked, colors);
		bfmeSubmit1283((AptCIH *)character, depth, pCharacter, name, parent, replace, clipDepth, unpacked, matrix, actions, ratio, 0);
	} else {
		bfmeSubmit1283((AptCIH *)character, depth, pCharacter, name, parent, replace, clipDepth, 0, matrix, actions, ratio, 0);
	}
}
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
