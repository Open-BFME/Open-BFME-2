// cl: /Ob1 /GX- /GS
// ?updateMinMax@@YAXPAMM0@Z, retail 0x000057D0, 33 bytes.
// Float min/max update: lowers `val` into *min when it is below the current
// minimum, otherwise raises *max when it is above the current maximum.
// Arguments are retail's native stack slots: +4 float* min, +8 float val by
// value, +0xC float* max.
//
// Identity basis, kept separate because the two differ:
//
//   FROM TARGET -- the 33 bytes are a float min/max update. They sit in a
//   min/max family in this run of .text, bounded by other members of it:
//     0x5790  float min, RETURNS a pointer   comiss / cmova
//     0x579d  float max, RETURNS a pointer   comiss / cmovbe
//     0x57b0  int   min, RETURNS a pointer   cmp / cmovge
//     0x57c0  int   max, RETURNS a pointer   cmp / cmovle
//     0x57d0  float update, STORES through both   <-- this body
//     0x57f1  int   update, STORES through both   <-- already rowed separately
//   The preceding integer max helper returns at 0x57CF and the next body
//   begins at 0x57F1, so 0x57D0..0x57F0 is complete, followed by 0xCC padding.
//
//   FROM DONOR -- the NAME `updateMinMax` and the float signature are carried
//   from Open-BFME-1 game/GameEngine/Source/Common/Bfme/updateMinMax.cpp
//   (donor revision 5cc75ddda6455c338a5068307e587a793f96d6b3, blob
//   675764648ccff672480bb22b1cb8734cef170553), unchanged. Retail itself gives
//   no name witness for this body: no Ghidra entry, no E8/E9 caller and no
//   absolute-address reference (all three searched and all empty).
//
//   NOT CLAIMED -- that 0x57D0 and 0x57F1 are overloads of one C++ function.
//   0x57F1 is byte-identical in shape to this body but is already rowed in the
//   ledger under a different name, ?expandRange@@YAXPAHH0@Z
//   (Code/Libraries/Source/WWVegas/WWMath/icoord.cpp), so the two are separate
//   recovered identities here and no overload relationship is asserted.
void updateMinMax(float *min, float val, float *max)
{
	if (val < *min)
	{
		*min = val;
		return;
	}
	if (val > *max)
		*max = val;
}

// Template min and max helpers returning const references:
//   0x0000578A: min<float> comiss / cmova (19B)
//   0x0000579D: max<float> comiss / cmovbe (19B)
//   0x000057B0: min<int>   cmp / cmovge (16B)
//   0x000057C0: max<int>   cmp / cmovle (16B)

template <class T>
const T &min(const T &a, const T &b)
{
	return (a < b) ? a : b;
}

template <class T>
const T &max(const T &a, const T &b)
{
	return (a > b) ? a : b;
}

template const float &min<float>(const float &, const float &);
template const float &max<float>(const float &, const float &);
template const int &min<int>(const int &, const int &);
template const int &max<int>(const int &, const int &);

