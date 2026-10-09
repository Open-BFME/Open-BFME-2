// _VP6_ReadTokens
// partial score=0.98 date=2026-10-10
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bc3d0.md plus retail only.
// No decoder source was consulted.
// _VP6_ReadTokens retail 0x001BC3D0..0x001BC9B5 cdecl draft. The real body is
// 1509 bytes (ret c3 at 0x001BC9B4); the spec's 1519 counts padding. Verify
// with --size 1509. NEAR: every instruction matches except the frame-slot
// choice: retail keeps the storage table at [esp+0x10] the token value spill
// at [esp+0x14] and the zero-extended scan position in the dead 'above'
// argument home [esp+0x2c]; this draft gets scan position [esp+0x10]
// storage [esp+0x14] value [esp+0x2c] (11 instructions differ).
// Tables 0x00BD8880 (token extra-bits entries) and 0x00BD8940 (band map)
// are address-named; the ledger's 468-byte string row at 0x007D8874
// (modes.txt) overlaps the token table and needs splitting before landing.

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

extern const Vp6TokenEntry g_00BD8880[12];
extern const int g_00BD8940[65];

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
	const unsigned char *acProbs;
	const int *storage;
	Rva009AAF80State *br;
	const unsigned char *dcProbs;
	const unsigned char *nodeProbs;
	const unsigned char *probs;
	unsigned char prec;
	unsigned char i;
	int token, value, k, sign, run;

	acProbs = pbi->AcProbs[plane][0][0];
	storage = pbi->quantizer->storageOrder;
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
				value = g_00BD8880[token].minimum;
				k = g_00BD8880[token].extraBits;
				do {
					value += VP6_BOOL(g_00BD8880[token].probs[k]) << k;
				} while (--k >= 0);
				sign = br->step();
				coeffs[0] = (short)((value ^ -sign) + sign);
			} else {
				if (VP6_BOOL(nodeProbs[4]))
					value = VP6_BOOL(dcProbs[5]) + 3;
				else
					value = 2;
				sign = br->step();
				coeffs[0] = (short)((value ^ -sign) + sign);
			}
		} else {
			prec = 1;
			sign = br->step();
			coeffs[0] = (short)((1 ^ -sign) + sign);
		}
	}

	i = 1;
	do {
		probs = acProbs + (g_00BD8940[i] + prec * 6) * 11;
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
				value = g_00BD8880[token].minimum;
				k = g_00BD8880[token].extraBits;
				do {
					value += VP6_BOOL(g_00BD8880[token].probs[k]) << k;
				} while (--k >= 0);
				sign = Vp6TokenSign::Read(br);
				coeffs[storage[pbi->ScanOrder[i]]] = (short)((value ^ -sign) + sign);
			} else {
				if (VP6_BOOL(probs[4]))
					value = VP6_BOOL(probs[5]) + 3;
				else
					value = 2;
				sign = Vp6TokenSign::Read(br);
				coeffs[storage[pbi->ScanOrder[i]]] = (short)((value ^ -sign) + sign);
			}
		} else {
			prec = 1;
			sign = Vp6TokenSign::Read(br);
			coeffs[storage[pbi->ScanOrder[i]]] = (short)((1 ^ -sign) + sign);
		}
		i++;
	} while (i < 64);
	return pbi->EobOffsets[--i];
}
