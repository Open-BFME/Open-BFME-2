// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c63f0.md 001c66b0.md plus retail only.
// No decoder source was consulted.
//
// VP6_decodeModeAndMotionVector (retail 0x001C63F0, 700 bytes) reads the
// macroblock mode and motion vectors; VP6_DecodeMacroBlock (retail 0x001C66B0,
// 705 bytes) decodes the block flag at +0xc8 and points the six 8x8 block
// decodes at their plane offsets. Both are cdecl. The bodies are carried
// unchanged from the byte-identical Open-BFME-1 project donor.

struct Rva009B4800State;
extern "C" int __cdecl nDecodeBool(Rva009B4800State *, int);

// Rowed as _VP6_DecodeBlock (511B at 0x001C61F0, DecodeBlock.cpp); referenced
// here opaquely through the established cast so the six direct calls below
// keep their bytes and resolve.
extern "C" void VP6_DecodeBlock(void);

typedef void (__cdecl *Rva009B58F0Fn)(unsigned char *, int, unsigned int, int);

// Rowed as _VP6_FindNearestandNextNearest (272B at 0x001C5D20,
// FindNearestandNextNearest.cpp); referenced opaquely the same way.
extern "C" void VP6_FindNearestandNextNearest(void);
typedef void (__cdecl *Rva009B5420Vp6FindPredictorFn)(void *, int, int, int, int *);

extern "C" int __cdecl VP6_DecodeMode(unsigned char *, int, int);
extern "C" int __cdecl VP6_DecodeBlockMode(unsigned char *);
extern "C" void __cdecl VP6_decodeMotionVector(void *, short *, int);

struct Rva009B5AF0Mv {
	short x;
	short y;
};

struct Rva009B5AF0State {
	unsigned char pad0[8];
	int mode;
	int blockMode[6];
	Rva009B5AF0Mv blockMv[6];
	Rva009B5AF0Mv candidateMv0;
	Rva009B5AF0Mv candidateMv1;
	int pad44;
	Rva009B5AF0Mv goldenCandidateMv0;
	Rva009B5AF0Mv goldenCandidateMv1;
	unsigned char pad50[0x230 - 0x50];
	int mbCols;
	unsigned char pad234[0x39c - 0x234];
	int lastMode;
	unsigned char pad3a0[0x6f0 - 0x3a0];
	unsigned char *mbModes;
	Rva009B5AF0Mv *mbMvs;
};

// VP6 macroblock mode and motion-vector decode at retail RVA 0x009B5AF0; mode 7 reads
// four block modes and averages their vectors for the chroma blocks.
extern "C" void __cdecl VP6_decodeModeAndMotionVector(unsigned char *ctx, int row, int column)
{
	Rva009B5AF0State *state = (Rva009B5AF0State *)ctx;
	int scratch; // predictor context, later a decoded motion vector
	((Rva009B5420Vp6FindPredictorFn)VP6_FindNearestandNextNearest)(state, row, column, 1, &scratch);

	int mode = VP6_DecodeMode((unsigned char *)state, state->lastMode, scratch);
	state->lastMode = mode;
	state->mbModes[state->mbCols * row + column] = (unsigned char)mode;
	state->mode = mode;

	if (mode == 7) {
		state->blockMode[0] = VP6_DecodeBlockMode((unsigned char *)state);
		state->blockMode[1] = VP6_DecodeBlockMode((unsigned char *)state);
		state->blockMode[2] = VP6_DecodeBlockMode((unsigned char *)state);
		state->blockMode[3] = VP6_DecodeBlockMode((unsigned char *)state);
		state->blockMode[4] = 7;
		state->blockMode[5] = 7;

		int sumX = 0;
		int sumY = 0;
		for (int blockIndex = 0; blockIndex < 4; blockIndex++) {
			int kind = state->blockMode[blockIndex];
			if (kind == 0) {
				state->blockMv[blockIndex].x = 0;
				state->blockMv[blockIndex].y = 0;
			} else if (kind == 3) {
				state->blockMv[blockIndex].x = state->candidateMv0.x;
				state->blockMv[blockIndex].y = state->candidateMv0.y;
				sumX += state->candidateMv0.x;
				sumY += state->candidateMv0.y;
			} else if (kind == 4) {
				state->blockMv[blockIndex].x = state->candidateMv1.x;
				state->blockMv[blockIndex].y = state->candidateMv1.y;
				sumX += state->candidateMv1.x;
				sumY += state->candidateMv1.y;
			} else if (kind == 2) {
				VP6_decodeMotionVector(state, (short *)&scratch, 2);
				short vx = ((short *)&scratch)[0];
				short vy = ((short *)&scratch)[1];
				state->blockMv[blockIndex].x = vx;
				state->blockMv[blockIndex].y = vy;
				sumX += state->blockMv[blockIndex].x;
				sumY += state->blockMv[blockIndex].y;
			}
		}

		int averageX = (sumX + (sumX >= 0 ? 1 : 0) + 1) >> 2;
		int averageY = (sumY + (sumY >= 0 ? 1 : 0) + 1) >> 2;
		state->mbMvs[state->mbCols * row + column].x = state->blockMv[3].x;
		state->mbMvs[state->mbCols * row + column].y = state->blockMv[3].y;
		state->blockMv[4].x = (short)averageX;
		state->blockMv[4].y = (short)averageY;
		state->blockMv[5].x = (short)averageX;
		state->blockMv[5].y = (short)averageY;
		return;
	}

	int x;
	int y;
	switch (mode) {
	case 3:
		x = state->candidateMv0.x;
		y = state->candidateMv0.y;
		break;
	case 4:
		x = state->candidateMv1.x;
		y = state->candidateMv1.y;
		break;
	case 8:
		((Rva009B5420Vp6FindPredictorFn)VP6_FindNearestandNextNearest)(state, row, column, 2, &scratch);
		x = state->goldenCandidateMv0.x;
		y = state->goldenCandidateMv0.y;
		break;
	case 9:
		((Rva009B5420Vp6FindPredictorFn)VP6_FindNearestandNextNearest)(state, row, column, 2, &scratch);
		x = state->goldenCandidateMv1.x;
		y = state->goldenCandidateMv1.y;
		break;
	case 2:
		VP6_decodeMotionVector(state, (short *)&scratch, 2);
		x = ((short *)&scratch)[0];
		y = ((short *)&scratch)[1];
		break;
	case 6:
		((Rva009B5420Vp6FindPredictorFn)VP6_FindNearestandNextNearest)(state, row, column, 2, &scratch);
		VP6_decodeMotionVector(state, (short *)&scratch, 6);
		x = ((short *)&scratch)[0];
		y = ((short *)&scratch)[1];
		break;
	default:
		x = 0;
		y = 0;
		break;
	}
	state->mbMvs[state->mbCols * row + column].x = (short)x;
	state->mbMvs[state->mbCols * row + column].y = (short)y;

	for (int blockIndex = 0; blockIndex < 6; blockIndex++) {
		state->blockMv[blockIndex].x = (short)x;
		state->blockMv[blockIndex].y = (short)y;
		state->blockMode[blockIndex] = mode;
	}
}

extern "C" void __cdecl VP6_DecodeMacroBlock(unsigned char *ctx, int outer, unsigned int column)
{
	if (*(int *)(ctx + 0x1dc) != 0) {
		unsigned char probability = ctx[0x6e8];

		if (column > 3) {
			if (*(int *)(ctx + 0xc8) != 0) {
				probability -= probability >> 1;
			} else {
				probability += (unsigned char)((0x100 - probability) >> 1);
			}
		}

		*(int *)(ctx + 0xc8) = nDecodeBool(
			(Rva009B4800State *)(ctx + 0x150), probability);
	} else {
		*(int *)(ctx + 0xc8) = 0;
	}

	if (ctx[0x1ac] == 0) {
		*(int *)(ctx + 0x8) = 1;
	} else {
		VP6_decodeModeAndMotionVector(ctx, outer, column);
	}

	int width = *(int *)(ctx + 0x1b8);
	int stride;
	if (*(int *)(ctx + 0xc8) == 0) {
		stride = 8;
		*(int *)(ctx + 0x74) = width;
	} else {
		stride = 1;
		*(int *)(ctx + 0x74) = width * 2;
	}
	*(unsigned char **)(ctx + 0xc4) = ctx + 0x124;
	int row16 = outer * 16;
	*(int *)(ctx + 0x64) = row16;
	*(int *)(ctx + 0x88) = width;
	*(int *)(ctx + 0x78) = 0;
	int col16 = column * 16;
	int rowOffset = row16 * width + *(int *)(ctx + 0x21c) + col16;
	*(int *)(ctx + 0x70) = rowOffset;
	int col32 = column * 32;
	*(int *)(ctx + 0x7c) = 2;
	*(int *)(ctx + 0x80) = 3;
	*(int *)(ctx + 0x68) = col16;
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x10c) + col32;
	*(unsigned char **)(ctx + 0xc0) = ctx + 0xcc;
	((Rva009B58F0Fn)VP6_DecodeBlock)(ctx, outer, column, 0);

	*(int *)(ctx + 0x70) += 8;
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x10c) + 0x10 + col32;
	*(unsigned char **)(ctx + 0xc0) = ctx + 0xcc;
	*(int *)(ctx + 0x68) += 8;
	((Rva009B58F0Fn)VP6_DecodeBlock)(ctx, outer, column, 1);

	*(int *)(ctx + 0x70) = *(int *)(ctx + 0x1b8) * stride + rowOffset;
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x10c) + col32;
	*(unsigned char **)(ctx + 0xc0) = ctx + 0xdc;
	*(int *)(ctx + 0x68) -= 8;
	*(int *)(ctx + 0x64) += stride;
	((Rva009B58F0Fn)VP6_DecodeBlock)(ctx, outer, column, 2);

	*(int *)(ctx + 0x70) += 8;
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x10c) + 0x10 + col32;
	*(unsigned char **)(ctx + 0xc0) = ctx + 0xdc;
	*(int *)(ctx + 0x68) += 8;
	((Rva009B58F0Fn)VP6_DecodeBlock)(ctx, outer, column, 3);

	int height = *(int *)(ctx + 0x1bc);
	int row8 = outer * 8;
	*(int *)(ctx + 0x64) = row8;
	*(int *)(ctx + 0x88) = height;
	*(int *)(ctx + 0x74) = height;
	int col8 = column * 8;
	*(int *)(ctx + 0x68) = col8;
	*(int *)(ctx + 0x70) = row8 * height + *(int *)(ctx + 0x220) + col8;
	*(int *)(ctx + 0x7c) = 3;
	*(int *)(ctx + 0x80) = 7;
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x110) + col16;
	*(unsigned char **)(ctx + 0xc0) = ctx + 0xec;
	*(unsigned char **)(ctx + 0xc4) = ctx + 0x12c;
	*(int *)(ctx + 0x78) = 1;
	((Rva009B58F0Fn)VP6_DecodeBlock)(ctx, outer, column, 4);

	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x114) + col16;
	*(unsigned char **)(ctx + 0xc0) = ctx + 0xfc;
	*(int *)(ctx + 0x70) = *(int *)(ctx + 0x74) * *(int *)(ctx + 0x64)
		+ *(int *)(ctx + 0x224) + *(int *)(ctx + 0x68);
	*(unsigned char **)(ctx + 0xc4) = ctx + 0x134;
	*(int *)(ctx + 0x78) = 2;
	((Rva009B58F0Fn)VP6_DecodeBlock)(ctx, outer, column, 5);
}
