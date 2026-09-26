// cl: /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?rva0015E3E0@SegmentedLineClass@@QAEXABVVector2@@@Z @0x0015E3E0 11B: gap between Set_Texture_Tile_Factor 0x15E3D0 and Set_Merge_Intersections 0x15E3F0 in segline.cpp; add ecx 0xDC tail jmp to rowed Set_Current_UV_Offset 0x191460; honest address name since no donor proves a SegmentedLine mirror.
class Vector2;

class SegLineRendererClass
{
public:
	void Set_Current_UV_Offset(const Vector2 &offset);
};

class SegmentedLineClass
{
	void *m_vtable; // +0
	char m_pad[0xDC - 4]; // +4..+0xDB
public:
	SegLineRendererClass LineRenderer; // +0xDC
	void rva0015E3E0(const Vector2 &offset);
};

void SegmentedLineClass::rva0015E3E0(const Vector2 &offset)
{
	LineRenderer.Set_Current_UV_Offset(offset);
}
