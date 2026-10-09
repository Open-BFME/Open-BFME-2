// ?rva0030E961@Rva0030E961@@QAEXPBGHHHH@Z
// partial score=0.67 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0030E961@Rva0030E961@@QAEXPBGHHHH@Z retail 0x0030E961..0x0030EC75
// (788B) thiscall RET 0x14.
//
// Builds the smoothed camera height field (the W3DView +0x2458 member that
// 0x0030E8DF clears and 0x0030E910 resizes). Donor: BFME 1
// GameEngine/Source/Common/Rva0045A000ScalarField.cpp (initialize): read
// the smoothness and the ground height range from the world dictionary
// 0x00E00944 (Dict::getReal 0x003131FC through the name-key caches
// "cameraMapHeightSmoothnessScalar" "cameraGroundMinHeight"
// "cameraGroundMaxHeight" at VA 0x00DBDEFC 0x00DBDF0C 0x00DBDF14; the
// smoothness falls back to TheWritableGlobalData +0xDE4 and a zero smoothness
// leaves the field untouched; the range falls back to -9999999 / 9999999 and
// is ordered), then take the clamped (??$clamp@M 0x0000575A) maximum height
// of every 4x4 block of 16-bit samples (scaled by 0.0390625) and spread it
// to the neighbours less 0.6 x scale x smoothness (x1.4 diagonally) until
// nothing changes or max(width height) passes ran.
// BFME 2 read from retail: the dictionary keys and fallbacks above; scale
// 40; the per-sample clamp is the shared clamp template; the second
// argument is unused.
//
// NEAR (banked draft): the header and the block-maximum pass match retail
// exactly; in the spreading pass cl keeps outputY + 2 as the induction
// variable and x in a register where retail keeps outputY in EDI and x in
// the sourceWidth slot (81 differing instructions of 242).

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned short UnsignedShort;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva00148F5ECache
{
public:
	NameKeyType get();
	NameKeyType m_key;
	const char *m_name;
};

// VA 0x00DBDEFC / 0x00DBDF0C / 0x00DBDF14 (.data): retail bytes 00 00 00 00
// then the string pointer.
Rva00148F5ECache g_00DBDEFC = { NAMEKEY_INVALID, "cameraMapHeightSmoothnessScalar" };
Rva00148F5ECache g_00DBDF0C = { NAMEKEY_INVALID, "cameraGroundMinHeight" };
Rva00148F5ECache g_00DBDF14 = { NAMEKEY_INVALID, "cameraGroundMaxHeight" };

class Dict
{
public:
	float getReal(int key, bool *exists) const;

private:
	struct DictPairData;
	DictPairData *m_data;
};

extern Dict g_Va00E00944;	// VA 0x00E00944

class GlobalData;
extern GlobalData *TheWritableGlobalData;	// VA 0x00DFE758

// The smoothness fallback this unit reads from the writable global data.
struct Rva0030E961Globals
{
	char m_pad0000[0xDE4];
	Real m_cameraMapHeightSmoothnessScalar;	// +0xDE4
};

template <class T> T clamp(T lo, T val, T hi);

struct RvaVector
{
	void **m_begin;
	void **m_end;
	void **m_cap;
	void rva0030E910(unsigned n, float value);
};

class Rva0030E961
{
public:
	void rva0030E961(const UnsignedShort *source, Int unused, Int sourceWidth, Int sourceHeight, Int state);

private:
	Real &at(Int index) { return ((Real *)m_data.m_begin)[index]; }

	RvaVector m_data;		// +0x00
	Int m_width;			// +0x0C
	Int m_height;			// +0x10
	Real m_scale;			// +0x14
	Int m_state;			// +0x18
	Bool m_ready;			// +0x1C
};

void Rva0030E961::rva0030E961(const UnsignedShort *source, Int unused, Int sourceWidth, Int sourceHeight, Int state)
{
	bool found;
	Real setting = g_Va00E00944.getReal(g_00DBDEFC.get(), &found);
	if (!found)
		setting = ((Rva0030E961Globals *)TheWritableGlobalData)->m_cameraMapHeightSmoothnessScalar;
	if (setting == 0.0f)
		return;

	Real low = g_Va00E00944.getReal(g_00DBDF0C.get(), &found);
	if (!found)
		low = -9999999.0f;
	Real high = g_Va00E00944.getReal(g_00DBDF14.get(), &found);
	if (!found)
		high = 9999999.0f;
	if (low > high)
	{
		Real temporary = high;
		high = low;
		low = temporary;
	}

	m_width = (sourceWidth + 3) / 4;
	m_height = (sourceHeight + 3) / 4;
	m_scale = 40.0f;
	m_data.rva0030E910(m_width * m_height, 0.0f);

	Int outputX;
	Int outputY;
	Int x;
	Int y;
	for (outputX = 0; outputX < m_width; ++outputX)
	{
		for (outputY = 0; outputY < m_height; ++outputY)
		{
			Real value = 0.0f;
			for (x = outputX * 4; x < outputX * 4 + 4; ++x)
			{
				for (y = outputY * 4; y < outputY * 4 + 4; ++y)
				{
					if (x < sourceWidth && y < sourceHeight)
					{
						Real sample = clamp(low, source[y * sourceWidth + x] * 0.0390625f, high);
						if (sample > value)
							value = sample;
					}
				}
			}
			at(outputY * m_width + outputX) = value;
		}
	}

	Int y2;
	Bool changed;
	Int passes = m_width;
	if (m_height > passes)
		passes = m_height;
	do
	{
		changed = false;
		for (outputX = 0; outputX < m_width; ++outputX)
		{
			for (outputY = 0; outputY < m_height; ++outputY)
			{
				for (x = outputX - 1; x < outputX + 2; ++x)
				{
					if (x < 0 || x >= m_width)
						continue;
					for (y2 = outputY - 1; y2 < outputY + 2; ++y2)
					{
						if (y2 >= 0 && y2 < m_height)
						{
							Real delta = m_scale * setting * 0.6f;
							if (x != outputX && y2 != outputY)
								delta *= 1.4f;
							Real candidate = at(y2 * m_width + x) - delta;
							Real *current = &at(outputY * m_width + outputX);
							if (candidate > *current)
							{
								*current = candidate;
								changed = true;
							}
						}
					}
				}
			}
		}
		--passes;
	}
	while (changed && passes > 0);

	m_state = state;
	m_ready = true;
}
