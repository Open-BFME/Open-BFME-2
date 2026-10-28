// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /G7
#include <string.h>

// VP6 stream destruction and frame decoding.
// ??1Rva007E3C20Vp6Stream@@UAE@XZ, retail 0x00090840..0x000908F6 (182
// bytes, EH): the VP6 stream's destructor, called by its scalar deleting
// destructor (??_GRva0090840, call at 0x00091156; table 0x00BC7F20).
//
// Ported from Open-BFME-1's
// game/GameEngine/Source/Common/Rva007E3C20Vp6StreamDtor.cpp (reference
// @ 575ba2b04). BFME 2 target differences, each read off retail: the +0x2C
// owner is destroyed through its slot-1 virtual destructor and then the
// global operator delete (a ::delete); the +0x54 buffer is released by the
// rowed Rva00090714Free (0x00090714) and cleared under a single test; the
// audio handles at +0x5C/+0x60 go to TheAudio slot 27. The +0x1C member and
// the base use the rowed bodies at 0x00106A2D and 0x0068A110.
// The layout is the rowed constructor 0x000907C1's.

class BfmeThingUC
{
public:
	void bfmeResetUC();
};

// The rowed cleanup restores the base vptr.
class __declspec(novtable) Gen_0081E480
{
public:
	virtual ~Gen_0081E480() { ((BfmeThingUC *)this)->bfmeResetUC(); }
private:
	int m_count;
	int m_first;
	int m_second;
	int m_flags;
};

class Rva00106874Host
{
public:
	~Rva00106874Host();
private:
	int m_word0;
	int m_word1;
	int m_word2;
	int m_word3;
};

class Rva00090840Owner
{
public:
	virtual void spare();
	virtual ~Rva00090840Owner();
	virtual void slot08();
	virtual void slot0c();
	virtual void *lock();
	virtual void unlock();
	unsigned int m_x;
	unsigned int m_y;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_textureWidth;
	unsigned int m_textureHeight;
	int m_pitch;
	float m_at20;
	int m_format;
};

class AudioManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
	virtual void release(int handle);
};
extern AudioManager *TheAudio;

struct CodecState;
extern "C" int __cdecl VP6_StopDecoder(CodecState **p);
void Rva00090714Free(void **p);

class BfmeB996
{
public:
	char movePair(int *output, int *first, unsigned int *second, unsigned int limit);
};

struct VP6Instance;
struct VP6YUVConfig
{
	int yWidth;
	int yHeight;
	int yStride;
	int uvWidth;
	int uvHeight;
	int uvStride;
	unsigned char *y;
	unsigned char *u;
	unsigned char *v;
	unsigned char *yOrigin;
};
extern "C" void __cdecl VP6_GetYUVConfig(VP6Instance *instance, VP6YUVConfig *config);

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

// The YUV to 32-bit tables VideoPlayer 0x0009111B fills (VA 0x00DE2098 ..).
extern unsigned int g_Va00DE3498[0x400];
extern int g_Va00DE3098[0x100];
extern int g_Va00DE2C98[0x100];
extern int g_Va00DE2898[0x100];
extern int g_Va00DE2498[0x100];
extern unsigned int g_Va00DE2098[0x100];

struct PB_INSTANCE;
extern "C" int __cdecl VP6_DecodeFrameToYUV(PB_INSTANCE *pbi, unsigned char *buffer, unsigned int byteCount);
typedef void (__cdecl *Vp6ForwardFn)(int, int, int, int, int);

class Rva007E3C20Vp6Stream;
// The frame decoder writes the active stream and advances the pair counter.
Rva007E3C20Vp6Stream *g_vp6ActiveStream;
int g_vp6PairCounter;

class Rva007E3C20Vp6Stream : public Gen_0081E480
{
public:
	virtual ~Rva007E3C20Vp6Stream();
	void rva000908F6();
	void rva000909B7();
	__forceinline void renderAlpha(VP6YUVConfig &frame, VP6YUVConfig &alpha, void *bits, int pitch);
	__forceinline void renderOpaque(VP6YUVConfig &frame, void *bits, int pitch);

private:
	void *m_at14;
	void *m_at18;
	Rva00106874Host m_parser;
	Rva00090840Owner *m_at2c;
	int m_at30;
	int m_at34;
	unsigned char m_at38;
	int m_at3c;
	int m_at40;
	int m_at44;
	int m_at48;
	int m_at4c;
	int m_at50;
	void *m_at54;
	int m_at58;
	int m_at5c;
	int m_at60;
};

Rva007E3C20Vp6Stream::~Rva007E3C20Vp6Stream()
{
	if (m_at14 != 0) {
		VP6_StopDecoder((CodecState **)&m_at14);
		m_at14 = 0;
	}
	if (m_at18 != 0) {
		VP6_StopDecoder((CodecState **)&m_at18);
		m_at18 = 0;
	}
	if (m_at2c != 0) {
		::delete m_at2c;
		m_at2c = 0;
	}
	if (m_at54 != 0) {
		Rva00090714Free(&m_at54);
		m_at54 = 0;
	}
	if (m_at5c != 1)
		TheAudio->release(m_at5c);
	if (m_at60 != 1)
		TheAudio->release(m_at60);
}

void Rva007E3C20Vp6Stream::rva000908F6()
{
	int tag;
	int size;
	if (m_at38)
	{
		g_vp6ActiveStream = this;
		do
		{
			if (!reinterpret_cast<BfmeB996 *>(&m_parser)->movePair((int *)m_at54, &tag, (unsigned int *)&size, m_at58))
			{
				m_at48 = m_at3c - 1;
				return;
			}
		} while (tag != 0x4b305641 && tag != 0x46305641);
		((Vp6ForwardFn)VP6_DecodeFrameToYUV)((int)m_at18, (int)m_at54 + 8, size, m_at30, m_at34);
	}
	else
		g_vp6ActiveStream = this;
	char ok;
	do
	{
		ok = reinterpret_cast<BfmeB996 *>(&m_parser)->movePair((int *)m_at54, &tag, (unsigned int *)&size, m_at58);
		++g_vp6PairCounter;
		if (!ok)
		{
			m_at48 = m_at3c - 1;
			return;
		}
	} while (tag != 0x4b30564d && tag != 0x4630564d);
	((Vp6ForwardFn)VP6_DecodeFrameToYUV)((int)m_at14, (int)m_at54 + 8, size, m_at30, m_at34);
	++m_at48;
}

// ?rva000909B7@Rva007E3C20Vp6Stream@@QAEXXZ, retail 0x000909B7..0x00090F72
// (1467 bytes, EH): table 0x00BC7F20 slot 3, the frame upload. Under the
// device lock (0x0011F520/0x00120F50) it locks the +0x2C texture (format 5 or
// 2), fetches the decoded planes through VP6_GetYUVConfig (0x001B5C60; a
// second time for the +0x18 alpha decoder on the alpha path) and converts two
// rows per chroma row through the YUV tables at 0x00DE2098.., bottom-up, the
// second row staged in a 4 KB buffer and copied with memcpy. Ported from
// Open-BFME-1's banked reconstruction targets/game/reverse/attempts/
// 0x007e3e60.cpp (at 92f6bbe8e). Read off retail: the plane dimensions are
// assigned inside the two inlined converters in this order (it sets the
// register choice and the reload of alpha.yHeight), the row pointer is
// declared late from the untyped lock result, and the unit compiles /G7 (both
// earlier bodies are unchanged under it).
#define RGB_PIXEL(Y) (((g_Va00DE3498[(Y) + red] << 8) | g_Va00DE3498[(Y) + green]) << 8 | g_Va00DE3498[(Y) + blue])
#define OPAQUE_PIXEL(Y) ((((g_Va00DE3498[(Y) + red] | 0xffffff00U) << 8) | g_Va00DE3498[(Y) + green]) << 8 | g_Va00DE3498[(Y) + blue])

// ?renderAlpha@Rva007E3C20Vp6Stream absent-from-retail
__forceinline void Rva007E3C20Vp6Stream::renderAlpha(VP6YUVConfig &frame, VP6YUVConfig &alpha, void *bits, int pitch)
{
	frame.yHeight = m_at34;
	frame.uvWidth = m_at30 >> 1;
	frame.uvHeight = m_at34 >> 1;
	alpha.yHeight = m_at34;
	alpha.uvWidth = m_at30 >> 1;
	frame.yWidth = m_at30;
	alpha.uvHeight = m_at34 >> 1;
	alpha.yWidth = m_at30;
	unsigned int row[1024];
	unsigned char *colorLumaRow = frame.y + (frame.yHeight - 1) * frame.yStride;
	unsigned char *previousColorLumaRow = colorLumaRow - frame.yStride;
	unsigned char *u = frame.u + (frame.uvHeight - 1) * frame.uvStride;
	unsigned char *v = frame.v + (frame.uvHeight - 1) * frame.uvStride;
	unsigned char *alphaRow = alpha.y + (alpha.yHeight - 1) * alpha.yStride;
	unsigned char *previousAlphaRow = alphaRow - alpha.yStride;
	unsigned int *dest = (unsigned int *)bits;
	unsigned char *next = (unsigned char *)bits + pitch;
	unsigned int *argbRowPixel = row;
	int ystep = -frame.yWidth - 2 * frame.yStride;
	int uvstep = -frame.uvWidth - frame.uvStride;
	int astep = -alpha.yWidth - 2 * alpha.yStride;
	int dststep = (pitch - 2 * frame.yWidth) * 2;
	for (int j = frame.uvHeight - 1; j >= 0; --j) {
		for (int i = frame.uvWidth - 1; i >= 0; --i) {
			int blue = g_Va00DE3098[*u];
			int green = g_Va00DE2C98[*u] + g_Va00DE2898[*v];
			int red = g_Va00DE2498[*v];
			++u; ++v;
			*dest++ = RGB_PIXEL(*colorLumaRow) | g_Va00DE2098[*alphaRow];
			++colorLumaRow; ++alphaRow;
			*dest++ = RGB_PIXEL(*colorLumaRow) | g_Va00DE2098[*alphaRow];
			++colorLumaRow; ++alphaRow;
			*argbRowPixel++ = RGB_PIXEL(*previousColorLumaRow) | g_Va00DE2098[*previousAlphaRow];
			++previousColorLumaRow; ++previousAlphaRow;
			*argbRowPixel++ = RGB_PIXEL(*previousColorLumaRow) | g_Va00DE2098[*previousAlphaRow];
			++previousColorLumaRow; ++previousAlphaRow;
		}
		colorLumaRow += ystep; previousColorLumaRow += ystep;
		u += uvstep; v += uvstep;
		alphaRow += astep; previousAlphaRow += astep;
		dest = (unsigned int *)((unsigned char *)dest + dststep);
		memcpy(next, row, m_at30 * 4);
		argbRowPixel = row;
		next += pitch * 2;
	}
}

// ?renderOpaque@Rva007E3C20Vp6Stream absent-from-retail
__forceinline void Rva007E3C20Vp6Stream::renderOpaque(VP6YUVConfig &frame, void *bits, int pitch)
{
	frame.yWidth = m_at30; frame.yHeight = m_at34;
	frame.uvWidth = m_at30 >> 1; frame.uvHeight = m_at34 >> 1;
	unsigned int row[1024];
	unsigned char *lumaRow = frame.y + (frame.yHeight - 1) * frame.yStride;
	unsigned char *previousLumaRow = lumaRow - frame.yStride;
	unsigned char *u = frame.u + (frame.uvHeight - 1) * frame.uvStride;
	unsigned char *v = frame.v + (frame.uvHeight - 1) * frame.uvStride;
	unsigned int *dest = (unsigned int *)bits;
	unsigned char *next = (unsigned char *)bits + pitch;
	unsigned int *opaqueRowPixel = row;
	int ystep = -frame.yWidth - 2 * frame.yStride;
	int uvstep = -frame.uvWidth - frame.uvStride;
	int dststep = (pitch - 2 * frame.yWidth) * 2;
	for (int j = frame.uvHeight - 1; j >= 0; --j) {
		for (int i = frame.uvWidth - 1; i >= 0; --i) {
			int blue = g_Va00DE3098[*u];
			int green = g_Va00DE2C98[*u] + g_Va00DE2898[*v];
			int red = g_Va00DE2498[*v];
			++u; ++v;
			*dest++ = OPAQUE_PIXEL(*lumaRow); ++lumaRow;
			*dest++ = OPAQUE_PIXEL(*lumaRow); ++lumaRow;
			*opaqueRowPixel++ = OPAQUE_PIXEL(*previousLumaRow); ++previousLumaRow;
			*opaqueRowPixel++ = OPAQUE_PIXEL(*previousLumaRow); ++previousLumaRow;
		}
		lumaRow += ystep; previousLumaRow += ystep;
		u += uvstep; v += uvstep;
		dest = (unsigned int *)((unsigned char *)dest + dststep);
		memcpy(next, row, m_at30 * 4);
		opaqueRowPixel = row;
		next += pitch * 2;
	}
}

