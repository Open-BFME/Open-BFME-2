// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// Both calls go through the same Miles import slot.  Retail preserves the
// first preference while querying the second and returns their product.
extern "C" __declspec(dllimport) int __stdcall AIL_get_preference(
	unsigned int preference);

int bfmeMilesPreferenceProduct_006962A0()
{
	return AIL_get_preference(0x2A) * AIL_get_preference(0x22);
}
