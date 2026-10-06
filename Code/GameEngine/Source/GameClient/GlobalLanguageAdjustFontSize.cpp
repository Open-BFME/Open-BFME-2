// cl: /O1 /DNDEBUG /MD /EHsc
// ?adjustFontSize@GlobalLanguage@@QAEHH@Z retail 0x001EA40D 54 bytes.
// GlobalLanguage font-size scaler: point size scaled by display width over
// 1024 and floored. BFME1 donor is GlobalLanguage::adjustFontSize in
// reference/open-bfme-1 (ZH donor GlobalLanguage.cpp plus the simple-ratio
// GlobalLanguage_adjustFontSize.cpp): TheGlobalData xResolution over 1024
// floored through REAL_TO_INT_FLOOR. BFME2 deltas retail-measured: xResolution
// at TheGlobalData +0x30 (GlobalDataOptionPreferences.cpp row) and the 1024
// divisor folded to a 1/1024 multiply at 0x007CF7C0. Identity: callers pass
// ecx from TheGlobalLanguageData literal 0x00DFDC84 (GameEngine init pushes
// that literal for initSubsystem<GlobalLanguage>) and feed eax to
// FontLibrary::getFont float size; floor reaches msvcr71 through IAT.

typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) double __cdecl floor(double);

// BaseType.h verbatim: C cast emits out-of-line _ftol plus qword shape;
// retail holds inline fld/fistp so the helper is load-bearing.
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))

class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0x30];
	Int m_xResolution;
};

extern class GlobalData *TheWritableGlobalData;

class GlobalLanguage
{
public:
	Int adjustFontSize(Int theFontSize);
};

Int GlobalLanguage::adjustFontSize(Int theFontSize)
{
	Real ratio = TheWritableGlobalData->m_xResolution / 1024.0f;
	Real size = theFontSize;
	return REAL_TO_INT_FLOOR(size * ratio);
}
