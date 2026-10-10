// cl: /O2 /G6 /DNDEBUG /MD
// VP6 clean-room spec reverse/vp6_cleanroom/specs/001bc3d0.md and native
// 001BC3D0..001BC9B5 establish cdecl AL return and five arguments.
// No decoder source consulted. Spec boundary includes padding; RET ends at1509B.
// Three stack locals grouped in storage/value/AC-probability order reproduce
// retail spills while keeping the bank's decoding algorithm unchanged.
// Tables are observed native data; descriptive names are not original identifiers.

struct Rva009B4800State;
int Rva009B4800DecodeBool(Rva009B4800State *, int);

struct Rva009AAF80State
{
	unsigned char m_pad0[4];
	unsigned m_range;
	unsigned m_code;
	int m_bitsRemaining;
	unsigned m_inputCursor;
	const unsigned char *m_inputBase;

	int step(void);
};

struct Vp6TokenQuantizer
{
	unsigned char unknown0[0x13c];
	const int *storageOrder;
};

struct Vp6TokenInstance
{
	unsigned char unknown0[0x13c];
	Vp6TokenQuantizer *quantizer;
	unsigned char unknown140[0x150 - 0x140];
	unsigned char br1[0x20];
	unsigned char br2[0x20];
	unsigned char unknown190[0x19d - 0x190];
	unsigned char profile;
	unsigned char unknown19e[0x3a0 - 0x19e];
	unsigned char DcProbs[2][11];
	unsigned char AcProbs[2][3][6][11];
	unsigned char DcNodeContexts[2][3][5];
	unsigned char ZeroRunProbs[2][14];
	unsigned char unknown57c[0x5bc - 0x57c];
	unsigned char ScanOrder[64];
	unsigned char EobOffsets[64];
	unsigned char unknown63c[0x944 - 0x63c];
	int multiStream;
};

struct Vp6TokenEntry
{
	unsigned short minimum;
	short extraBits;
	unsigned char probs[12];
};

extern const Vp6TokenEntry BfmeVp6TokenExtraBits[12] = {
    {0,-1,{0,0,0,0,0,0,0,0,0,0,0,0}},
    {1,0,{0,0,0,0,0,0,0,0,0,0,0,0}},
    {2,0,{0,0,0,0,0,0,0,0,0,0,0,0}},
    {3,0,{0,0,0,0,0,0,0,0,0,0,0,0}},
    {4,0,{0,0,0,0,0,0,0,0,0,0,0,0}},
    {5,0,{159,0,0,0,0,0,0,0,0,0,0,0}},
    {7,1,{145,165,0,0,0,0,0,0,0,0,0,0}},
    {11,2,{140,148,173,0,0,0,0,0,0,0,0,0}},
    {19,3,{135,140,155,176,0,0,0,0,0,0,0,0}},
    {35,4,{130,134,141,157,180,0,0,0,0,0,0,0}},
    {67,10,{129,130,133,140,153,177,196,230,243,254,254,0}},
    {0,-1,{0,0,0,0,0,0,0,0,0,0,0,0}}
};
extern const int BfmeVp6CoefficientBands[65] = {
    -1,0,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,7
};

struct Vp6TokenSign
{
	static int Read(Rva009AAF80State *br)
	{
		unsigned code = br->m_code;
		int bitsRemaining = br->m_bitsRemaining;
		unsigned range = br->m_range;
		unsigned half = (range + 1) >> 1;
		unsigned threshold = half << 24;
		int bit;

		bit = (code >= threshold);
		range = bit ? range - half : half;
		code = bit ? code - threshold : code;
		code += code;
		range += range;
		if (--bitsRemaining == 0) {
			bitsRemaining = 8;
			code |= br->m_inputBase[br->m_inputCursor];
			++br->m_inputCursor;
		}
		br->m_bitsRemaining = bitsRemaining;
		br->m_range = range;
		br->m_code = code;
		return bit;
	}
};

#define VP6_BOOL(p) Rva009B4800DecodeBool((Rva009B4800State *)br, (p))

extern "C" unsigned char VP6_ReadTokens(Vp6TokenInstance *pbi, short *coeffs, int plane,
	unsigned char *above, unsigned char *left)
{
	
	
	Rva009AAF80State *br;
struct Locals {const int *storage;int value;const unsigned char *acProbs;} locals;
	const unsigned char *dcProbs;
	const unsigned char *nodeProbs;
	const unsigned char *probs;
	unsigned char prec;
	unsigned char i;
	int token,k,sign,run;

	locals.acProbs = pbi->AcProbs[plane][0][0];
	locals.storage = pbi->quantizer->storageOrder;
	if (pbi->multiStream != 0 || pbi->profile == 0)
		br = (Rva009AAF80State *)pbi->br2;
	else
		br = (Rva009AAF80State *)pbi->br1;
	dcProbs = pbi->DcProbs[plane];
	nodeProbs = pbi->DcNodeContexts[plane][*left + *above];

	if (!VP6_BOOL(nodeProbs[0])) {
		prec = 0;
		*left = 0;
		*above = 0;
	} else {
		*left = 1;
		*above = 1;
		if (VP6_BOOL(nodeProbs[2])) {
			prec = 2;
			if (VP6_BOOL(nodeProbs[3])) {
				if (VP6_BOOL(dcProbs[6])) {
					if (VP6_BOOL(dcProbs[8]))
						token = VP6_BOOL(dcProbs[10]) + 9;
					else
						token = VP6_BOOL(dcProbs[9]) + 7;
				} else {
					token = VP6_BOOL(dcProbs[7]) + 5;
				}
				locals.value = BfmeVp6TokenExtraBits[token].minimum;
				k = BfmeVp6TokenExtraBits[token].extraBits;
				do {
					locals.value += VP6_BOOL(BfmeVp6TokenExtraBits[token].probs[k]) << k;
				} while (--k >= 0);
				sign = br->step();
				coeffs[0] = (short)((locals.value ^ -sign) + sign);
			} else {
				if (VP6_BOOL(nodeProbs[4]))
					locals.value = VP6_BOOL(dcProbs[5]) + 3;
				else
					locals.value = 2;
				sign = br->step();
				coeffs[0] = (short)((locals.value ^ -sign) + sign);
			}
		} else {
			prec = 1;
			sign = br->step();
			coeffs[0] = (short)((1 ^ -sign) + sign);
		}
	}

	i = 1;
	do {
		probs = locals.acProbs + (BfmeVp6CoefficientBands[i] + prec * 6) * 11;
		if (i <= 1 || prec != 0) {
			if (!VP6_BOOL(probs[0])) {
				if (!VP6_BOOL(probs[1])) {
					i++;
					break;
				}
				probs = pbi->ZeroRunProbs[i >= 6];
				prec = 0;
				if (!VP6_BOOL(probs[0])) {
					if (!VP6_BOOL(probs[1]))
						run = VP6_BOOL(probs[2]) + 1;
					else
						run = VP6_BOOL(probs[3]) + 3;
				} else if (!VP6_BOOL(probs[4])) {
					if (!VP6_BOOL(probs[5]))
						run = VP6_BOOL(probs[6]) + 5;
					else
						run = VP6_BOOL(probs[7]) + 7;
				} else {
					run = VP6_BOOL(probs[8]);
					run += VP6_BOOL(probs[9]) << 1;
					run += VP6_BOOL(probs[10]) << 2;
					run += VP6_BOOL(probs[11]) << 3;
					run += VP6_BOOL(probs[12]) << 4;
					run += VP6_BOOL(probs[13]) << 5;
					run += 9;
				}
				i += run;
				continue;
			}
		}
		if (VP6_BOOL(probs[2])) {
			prec = 2;
			if (VP6_BOOL(probs[3])) {
				if (VP6_BOOL(probs[6])) {
					if (VP6_BOOL(probs[8]))
						token = VP6_BOOL(probs[10]) + 9;
					else
						token = VP6_BOOL(probs[9]) + 7;
				} else {
					token = VP6_BOOL(probs[7]) + 5;
				}
				locals.value = BfmeVp6TokenExtraBits[token].minimum;
				k = BfmeVp6TokenExtraBits[token].extraBits;
				do {
					locals.value += VP6_BOOL(BfmeVp6TokenExtraBits[token].probs[k]) << k;
				} while (--k >= 0);
				sign = Vp6TokenSign::Read(br);
				coeffs[locals.storage[pbi->ScanOrder[i]]] = (short)((locals.value ^ -sign) + sign);
			} else {
				if (VP6_BOOL(probs[4]))
					locals.value = VP6_BOOL(probs[5]) + 3;
				else
					locals.value = 2;
				sign = Vp6TokenSign::Read(br);
				coeffs[locals.storage[pbi->ScanOrder[i]]] = (short)((locals.value ^ -sign) + sign);
			}
		} else {
			prec = 1;
			sign = Vp6TokenSign::Read(br);
			coeffs[locals.storage[pbi->ScanOrder[i]]] = (short)((1 ^ -sign) + sign);
		}
		i++;
	} while (i < 64);
	return pbi->EobOffsets[--i];
}
