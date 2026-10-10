// cl: /Oy- /DNDEBUG /MD /EHsc /DBFME_MODULE_NO_MPO /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?W3DLogicalScreenToPixelScreen@@YAXMMPAH0HH@Z @0x00101E1E 79B
// Zero Hour's W3DLogicalScreenToPixelScreen (W3DConvert.cpp): W3D logical coords
// to pixel screen coords; the rowed PixelScreenToW3DLogicalScreen (0x00101E6D)
// follows it. Formerly named by address (Rva00101E1EConvert).
// Evidence: callers 0x0008619F (166B) and 0x0009AE98 (248B) with 6 cdecl args;
// the 1.0f pool lands at 0x00BBB8D8 and the 0.5f pool at 0x00BC26F0, so the
// body uses those two literals directly rather than extern globals.
// Neighbours 0x00101CDA W3DRopeDraw and 0x00101FD8 place this body in the
// W3DDevice GameClient unit.
void __cdecl W3DLogicalScreenToPixelScreen(float a, float b, int *out1, int *out2, int s1, int s2)
{
	float t1 = (a + 1.0f) * (float)s1 * 0.5f;
	float t0 = (1.0f - b) * (float)s2 * 0.5f;
	*out1 = (int)t1;
	*out2 = (int)t0;
}
