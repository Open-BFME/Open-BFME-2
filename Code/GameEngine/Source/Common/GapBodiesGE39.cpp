// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small bodies from .text gaps no Ghidra function covers (thirty-ninth
// batch; see GapBodiesGE01.cpp). Each begins after its neighbour's padding or
// ret and ends in its own ret. Retail bytes establish every shape; owning
// classes are not recovered, so each keeps an address-derived name and a view
// of only the members it touches. Callees and globals use the ledger's
// existing spellings.

// --- 0x0010EE29 (38B): a Miles stream callback trampoline: user-data slot 0
// holds a __stdcall callback, slot 1 its argument.
extern "C" __declspec(dllimport) int __stdcall AIL_stream_user_data(void *stream, unsigned int index);

typedef void (__stdcall *GapStreamCallback)(int value);

void __stdcall rva0010EE29(void *stream)
{
	GapStreamCallback callback = (GapStreamCallback)AIL_stream_user_data(stream, 0);
	if (callback)
		callback(AIL_stream_user_data(stream, 1));
}

// --- 0x001100D6 (18B): leading words differ.
class Rva001100D6
{
public:
	bool rva001100D6(const Rva001100D6 &other) const;
private:
	int m_00;
};

bool Rva001100D6::rva001100D6(const Rva001100D6 &other) const
{
	return m_00 != other.m_00;
}

// --- 0x001116E7 (67B): an 8-bit BGR triple scaled to 5:5:5.
unsigned short rva001116E7(const unsigned char *bgr)
{
	int scale = 256;
	int r = (bgr[2] + 1) * 31 / scale;
	int g = (bgr[1] + 1) * 31 / scale;
	int b = (bgr[0] + 1) * 31 / scale;
	return (unsigned short)((((r << 5) | g) << 5) | b);
}

// --- 0x00111772 (18B): the +0x2AB4 counted object with one more reference.
struct GapCounted
{
	int m_00;
	int m_refs;												// +0x04
};

class Rva00111772
{
public:
	GapCounted *rva00111772();
private:
	char m_pad00[0x2AB4];
	GapCounted *m_object;									// +0x2AB4
};

// --- 0x0012CA31 / 0x0012CA39 / 0x0012CA41 (8B each): clear the texture,
// shader and model asset-builder run flags.
extern bool AssetInitRunTextureBuilder;
// Native complete one-byte run flag atDB61EA starts enabled.
bool AssetInitRunShaderBuilder = true;
extern bool AssetInitRunModelBuilder;

void rva0012CA31()
{
	AssetInitRunTextureBuilder = false;
}

void rva0012CA39()
{
	AssetInitRunShaderBuilder = false;
}

void rva0012CA41()
{
	AssetInitRunModelBuilder = false;
}
