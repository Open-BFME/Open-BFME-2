// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
class FreelistPool;
extern FreelistPool g_freelistPool00DB8FEC;
// Small bodies from .text gaps no Ghidra function covers (fifty-first
// batch; see GapBodiesGE01.cpp), all from the /O1 /arch:SSE /G7 retail region
// that starts at 0x001D8E99 (reverse/retail_inventory/flag_regions.csv). Each
// begins after its neighbour's padding or ret and ends in its own ret or tail
// jump. Retail bytes establish every shape; owning classes are not
// recovered, so each keeps an address-derived name and a view of only the
// members it touches. Callees and globals use the ledger's existing
// spellings.

class AsciiString;
class Image;

// --- 0x001E352C (12B): the +0x20 word of the leading object, or INT_MAX
// without one; 0x001E353C (3B): bump the leading word.
struct GapLimitHolder
{
	char m_pad00[0x20];
	int m_20;
};

class Rva001E352C
{
public:
	int rva001E352C() const;
private:
	GapLimitHolder *m_holder;
};

int Rva001E352C::rva001E352C() const
{
	if (m_holder == 0)
		return 0x7FFFFFFF;
	return m_holder->m_20;
}

class Rva001E353C
{
public:
	void rva001E353C();
private:
	int m_count;
};

void Rva001E353C::rva001E353C()
{
	++m_count;
}

// --- 0x001E381E / 0x001E382F (17B each): floats at +0x538 / +0x53C;
// 0x001E3840 (28B): bit n of the +0x4B8 mask.
class Rva001E381E
{
public:
	void rva001E381E(float value);
	void rva001E382F(float value);
	bool rva001E3840(int bit) const;
private:
	char m_pad00[0x4B8];
	unsigned int m_4B8;
	char m_pad4BC[0x538 - 0x4BC];
	float m_538;
	float m_53C;
};

void Rva001E381E::rva001E381E(float value)
{
	m_538 = value;
}

void Rva001E381E::rva001E382F(float value)
{
	m_53C = value;
}

bool Rva001E381E::rva001E3840(int bit) const
{
	return (m_4B8 & (1 << bit)) != 0;
}

// --- 0x001E417C (24B): lower the +0x40 float to a value.

class Rva001E417C
{
public:
	void rva001E417C(float value);

private:
	char m_pad00[0x40];
	float m_40;
};

void Rva001E417C::rva001E417C(float value)
{
	if (m_40 > value)
		m_40 = value;
}


// --- 0x001EAE2E (8B) / 0x001EAE36 (13B): set / read bit 4 of the +0x438
// byte.
class Rva001EAE2E
{
public:
	void rva001EAE2E();
	int rva001EAE36() const;
private:
	char m_pad00[0x438];
	unsigned char m_438;
};

void Rva001EAE2E::rva001EAE2E()
{
	m_438 |= 0x10;
}

int Rva001EAE2E::rva001EAE36() const
{
	return (m_438 >> 4) & 1;
}

// --- 0x001EAF9B (21B) / 0x001EAFB0 (17B): distance between and advance of
// cursors over 0xAC-byte records.
struct GapRecordAC
{
	char m_bytes[0xAC];
};

struct GapRecordCursor
{
	GapRecordAC *m_at;
};

int rva001EAF9B(const GapRecordCursor &gapRecordCursor, const GapRecordCursor &endCursor)
{
	return endCursor.m_at - gapRecordCursor.m_at;
}

void advanceCursor(GapRecordCursor &cursor, int elementOffset)
{
	cursor.m_at += elementOffset;
}

// --- 0x001EB0EA (17B): the +0xC1 flag of the optional +0x10 object.
struct GapFlagC1
{
	char m_pad00[0xC1];
	bool m_C1;
};

class Rva001EB0EA
{
public:
	bool rva001EB0EA() const;
private:
	char m_pad00[0x10];
	GapFlagC1 *m_10;
};

bool Rva001EB0EA::rva001EB0EA() const
{
	if (m_10)
		return m_10->m_C1;
	return false;
}

// --- 0x001EB118 (24B): push a block onto the object-list pool head; 0x001EB786
// (24B): pop one from g_freelistPool00DB8FEC for a single element.

class FreelistPool
{
public:
	void *pop();
};

extern FreelistPool g_freelistPool00DB8FEC;

class Rva001EB118
{
public:
	void deallocate(void *block, unsigned int elementCount);
	void *allocate(unsigned int requestedCount, const void *hint);
};

void Rva001EB118::deallocate(void *block, unsigned int elementCount)
{
	if (block)
	{
		*(void **)block = (*(void **)((char *)&::g_freelistPool00DB8FEC + 8));
		(*(void **)((char *)&::g_freelistPool00DB8FEC + 8)) = block;
	}
}

void *Rva001EB118::allocate(unsigned int requestedCount, const void *hint)
{
	if (requestedCount > 1)
		return 0;
	return g_freelistPool00DB8FEC.pop();
}

// --- 0x001EDFCB (30B): the i-th of the 0x38 names at VA 0x00DB9058, or
// "???" out of range.
extern const char **g_00DB9058;

class Rva001EDFCB
{
public:
	const char *getCursorName(int i) const;
};

const char *Rva001EDFCB::getCursorName(int i) const
{
	const char *name;
	if (i >= 0 && i < 0x38)
		name = ((const char **)&g_00DB9058)[i];
	else
		name = "???";
	return name;
}

// --- 0x001EF05B (20B): two wide strings differ, through the rowed
// StringBase<unsigned short>::compare 0x00006A7A.
template <class T> class StringBase
{
public:
	int compare(const StringBase<T> &that) const;
};

bool rva001EF05B(const StringBase<unsigned short> &leftString, const StringBase<unsigned short> &rightString)
{
	return leftString.compare(rightString) != 0;
}

// --- 0x001F34BF (28B): advance the +0x178C counter; true while it does not
// cover every bit of the +0x1790 mask.
class Rva001F34BF
{
public:
	bool rva001F34BF();
private:
	char m_pad00[0x178C];
	unsigned int m_counter;									// +0x178C
	unsigned int m_mask;									// +0x1790
};

bool Rva001F34BF::rva001F34BF()
{
	++m_counter;
	return (m_mask & m_counter) != m_mask;
}

// --- 0x001FD1E8 / 0x001FD20E (19B each): look up the +0x16C / +0x178 image
// names through TheMappedImageCollection's rowed findImageByName.
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

class Rva001FD1E8
{
public:
	const Image *getHeadWaterMarkImage();
	const Image *getSideIconImage();
private:
	char m_pad00[0x16C];
	char m_headWaterMark[0x178 - 0x16C];							// +0x16C (an AsciiString)
	char m_sideIconImage[4];										// +0x178 (an AsciiString)
};

const Image *Rva001FD1E8::getHeadWaterMarkImage()
{
	return TheMappedImageCollection->findImageByName(*(const AsciiString *)m_headWaterMark);
}

const Image *Rva001FD1E8::getSideIconImage()
{
	return TheMappedImageCollection->findImageByName(*(const AsciiString *)m_sideIconImage);
}

// --- 0x001FD348 (31B): the 0x1DC-byte record in [+0x0C, +0x10) whose +0x10
// id matches, or null.
struct GapRecord1DC
{
	char m_pad00[0x10];
	int m_id;												// +0x10
	char m_pad14[0x1DC - 0x14];
};

class Rva001FD348
{
public:
	GapRecord1DC *rva001FD348(int id);
private:
	char m_pad00[0x0C];
	GapRecord1DC *m_begin;									// +0x0C
	GapRecord1DC *m_end;									// +0x10
};

GapRecord1DC *Rva001FD348::rva001FD348(int id)
{
	for (GapRecord1DC *gapRecord1DC = m_begin; gapRecord1DC != m_end; ++gapRecord1DC)
		if (gapRecord1DC->m_id == id)
			return gapRecord1DC;
	return 0;
}

// --- 0x001FDBEB / 0x001FDBFD (18B each): copy construction through the
// rowed assignments 0x001FD8DF / 0x001FD952.
struct Rva001FD42B
{
	Rva001FD42B(const Rva001FD42B &that);
	Rva001FD42B *rva001FD8DF(const Rva001FD42B &that);	// 0x001FD8DF
};

Rva001FD42B::Rva001FD42B(const Rva001FD42B &that)
{
	rva001FD8DF(that);
}

struct Rva001FD458
{
	Rva001FD458(const Rva001FD458 &that);
	Rva001FD458 *rva001FD952(const Rva001FD458 &that);	// 0x001FD952
};

Rva001FD458::Rva001FD458(const Rva001FD458 &that)
{
	rva001FD952(that);
}

// ?rva001E385C@@YAMMMM@Z, retail 0x001E385C..0x001E3896 (58 B): the
// locomotor slow-down distance helper. cl gives this file-static function a
// private convention (actual speed in XMM1, minimum speed and braking on the
// stack, result in XMM0, plain ret); its only retail caller is the unrowed
// movement update 0x001E6007. Native: no slow-down when the speed is at or
// below the minimum; otherwise (delta / braking + 1) frames at the average of
// the two speeds, times 1.05. The BFME 1 Locomotor slow-down formula is the
// semantic lead; the name stays address-derived.
__declspec(noinline) static float rva001E385C(float actualSpeed, float minSpeed, float braking)
{
	float delta = actualSpeed - minSpeed;
	if (delta <= 0.0f)
		return 0.0f;
	float frames = delta / braking;
	frames += 1.0f;
	float avg = delta * 0.5f + minSpeed;
	return frames * avg * 1.05f;
}

// The retail caller is not in this unit; this anchor makes cl emit the helper
// with that private convention.
// ?rva001E385CAnchor absent-from-retail
float rva001E385CAnchor(float actualSpeed, float minSpeed, float braking)
{
	return rva001E385C(actualSpeed, minSpeed, braking);
}
