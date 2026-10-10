// ?xfer@W3DScriptedModelDraw@@MAEXPAVXfer@@@Z
// partial score=0.9977268533365342 date=2026-10-10
// ?xfer@W3DScriptedModelDraw@@MAEXPAVXfer@@@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
// ?xfer@W3DScriptedModelDraw@@MAEXPAVXfer@@@Z retail 0x000C5C04..0x000C65CB
// (2503 bytes). Slot 3 of the W3DScriptedModelDraw vftable 0x00BCA090;
// W3DTankDraw::xfer (0x000CE03C) calls it as its base xfer. WorldBuilder
// twin 0x00942F90. Zero Hour W3DModelDraw::xfer supplies the HLOD
// animation save/restore shape; BFME2 moves it before the member data,
// versions the block 1..6 and adds the native members below. Field
// offsets come from the retail accesses; names are not asserted.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <vector>
#include <set>
#include <string>

#include "ascii_string.h"
#include "Coord3D.h"

extern const char g_Rva0107301CEmptyString[];

struct XferVersion
{
	XferVersion(unsigned char low, unsigned char high) : version(low), current(high) {}
	unsigned char version, current;
};

class Xfer
{
public:
	virtual void slot00();
	virtual bool isLoading();
	virtual bool isSaving();
	virtual void slot03();
	virtual bool slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void xferCoord3D(Coord3D *);
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(AsciiString *);
	virtual void xferReal(float *);
	virtual void slot29();
	virtual void xferUnsignedInt(unsigned int *);
	virtual void xferInt(int *);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void xferBool(bool *);
};

void XferDrawableID(Xfer *, int *);
Xfer *Rva000BC559Xfer(Xfer *, _STL::set<int> *);
void Rva0030612AXfer(Xfer *, float *);

template <int N> class BitFlags
{
public:
	void xfer(Xfer *);
	unsigned int m_bits[(N + 31) / 32];
};

class HAnimClass
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual int Get_Num_Frames();
};

class RenderObjClass
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual int Class_ID() const;
	virtual void slot04();
	virtual void slot05();
	virtual const char *Get_Name() const;
};

class HLodClass
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44();
	virtual void Set_Animation(HAnimClass *anim, float frame, int mode);
	virtual void s46();
	virtual HAnimClass *Peek_Animation();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71();
	virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75();
	virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79();
	virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83();
	virtual void s84(); virtual void s85(); virtual void s86(); virtual void s87();
	virtual void s88(); virtual void s89(); virtual void s90(); virtual void s91();
	virtual void s92(); virtual void s93(); virtual void s94(); virtual void s95();
	virtual void s96(); virtual void s97(); virtual void s98(); virtual void s99();
	virtual void s100(); virtual void s101(); virtual void s102(); virtual void s103();
	virtual void s104(); virtual void s105(); virtual void s106(); virtual void s107();
	virtual void s108(); virtual void s109(); virtual void s110(); virtual void s111();
	virtual void s112(); virtual void s113(); virtual void s114(); virtual void s115();
	virtual void s116(); virtual void s117(); virtual void s118(); virtual void s119();
	virtual void s120(); virtual void s121(); virtual void s122(); virtual void s123();
	virtual void s124(); virtual void s125(); virtual void s126(); virtual void s127();
	virtual void s128(); virtual void s129();
	virtual HAnimClass *Peek_Animation_And_Info(float &frame, int &numFrames, int &mode, float &mult);
};

RenderObjClass *Create_Render_Obj(const char *name);

class RTS3DScene
{
public:
	virtual void slot0();
	virtual void slot4();
	virtual void Add_Render_Object(RenderObjClass *obj);
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

struct Rva00079EA1Element;
struct BfmeStringRecord000B9534
{
	AsciiString text;
	bool flag;
	float word0, word1, word2, word3;
};

struct BfmeNarrowRecord000BFDC7
{
	BfmeNarrowRecord000BFDC7() {}
	BfmeNarrowRecord000BFDC7(const BfmeNarrowRecord000BFDC7 &o);
	RenderObjClass *word0;
	_STL::basic_string<char> text;
	Coord3D word1;
	int word4;
};

struct BfmeStringRecord000B94D2
{
	AsciiString text0, text1;
};

namespace _STL
{
template <> Rva00079EA1Element *vector<Rva00079EA1Element>::erase(Rva00079EA1Element *, Rva00079EA1Element *);
template <> void vector<BfmeStringRecord000B9534>::reserve(size_t);
template <> void vector<BfmeStringRecord000B9534>::push_back(const BfmeStringRecord000B9534 &);
template <> void vector<BfmeNarrowRecord000BFDC7>::push_back(const BfmeNarrowRecord000BFDC7 &);
template <> void vector<BfmeStringRecord000B94D2>::resize(size_t);
template <> basic_string<char> &basic_string<char>::operator=(const char *);
}

class Rva000B4653
{
public:
	void *rva000B4653(int a);
};

class Rva000B8F5AOuter
{
public:
	void rva000BFB51(float value);
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
	virtual void crc(Xfer *);
	virtual void slot02();
protected:
	virtual void xfer(Xfer *);
public:
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34();
	virtual void setSlot8C(bool value);
	virtual void clearSlot90();
protected:
	void *m_moduleData;
	void *m_object;
};

class DrawModule : public ObjectModule
{
protected:
	virtual void xfer(Xfer *);
};

class Rva000C5C04SecondBase
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28();
	virtual void slot74();
};

class W3DScriptedModelDraw : public DrawModule, public Rva000C5C04SecondBase
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad10[0x14 - 0x10];
	void *m_curState14;
	char m_pad18[0x28 - 0x18];
	unsigned int m_recolorCount28 : 3;
	unsigned int m_recolorUnused28 : 28;
	unsigned int m_recolorFlag28 : 1;
	unsigned int m_recolor2C;
	unsigned int m_recolor30;
	unsigned int m_recolor34;
	_STL::vector<BfmeStringRecord000B94D2> m_vec38;
	int m_44;
	bool m_48, m_49, m_4A, m_4B, m_4C, m_4D;
	char m_pad4E[2];
	RenderObjClass *m_renderObject50;
	AsciiString m_54;
	char m_pad58[0x68 - 0x58];
	_STL::vector<BfmeStringRecord000B9534> m_vec68;
	_STL::vector<BfmeStringRecord000B9534> m_vec74;
	bool m_80, m_81;
	char m_pad82[2];
	int m_84;
	int m_88;
	float m_8C;
	char m_pad90[0x98 - 0x90];
	float m_98;
	float m_9C;
	bool m_A0;
	char m_padA1[3];
	int m_A4;
	_STL::set<int> m_A8;
	AsciiString m_B4;
	char m_padB8[4];
	int m_BC;
	int m_C0;
	char m_padC4[0x164 - 0xC4];
	_STL::vector<BfmeNarrowRecord000BFDC7> m_vec164;
	char m_pad170[0x17C - 0x170];
	BitFlags<591> m_flags17C;
	bool m_1C8, m_1C9, m_1CA, m_1CB;
	char m_pad1CC[0x214 - 0x1CC];
	int m_214;
	char m_pad218[0x25C - 0x218];
	bool m_25C;
	char m_pad25D[3];
	AsciiString m_260;
	AsciiString m_264[2];
	float m_26C;
	bool m_270;
	char m_pad271[3];
	unsigned int m_274;
	unsigned int m_278;
	unsigned int m_27C;
	float m_280;
	char m_pad284[0x28C - 0x284];
	bool m_28C, m_28D;
	char m_pad28E[0x2C8 - 0x28E];
	float m_2C8, m_2CC, m_2D0, m_2D4;
};

void W3DScriptedModelDraw::xfer(Xfer *xfer)
{
	DrawModule::xfer(xfer);
	if (xfer->slot04())
		return;

	XferVersion version(1, 6);
	xfer->xferVersion(&version);

	float percent = 0.0f;
	bool restoreAnimation = false;
	if (xfer->isSaving())
	{
		if (m_renderObject50 && m_renderObject50->Class_ID() == 0x19 && m_curState14)
		{
			HLodClass *hlod = (HLodClass *)m_renderObject50;
			int mode, numFrames;
			float frame, dummy;
			HAnimClass *anim = hlod->Peek_Animation_And_Info(frame, numFrames, mode, dummy);
			bool present = anim != 0;
			xfer->xferBool(&present);
			if (anim)
			{
				xfer->xferInt(&mode);
				percent = frame / (float)(anim->Get_Num_Frames() - 1);
				xfer->xferReal(&percent);
			}
		}
		else
		{
			bool present = false;
			xfer->xferBool(&present);
		}
	}
	else
	{
		bool present;
		xfer->xferBool(&present);
		if (present)
		{
			{
				int mode;
				xfer->xferInt(&mode);
			}
			xfer->xferReal(&percent);
			if (m_renderObject50 && m_renderObject50->Class_ID() == 0x19)
			{
				HLodClass *hlod = (HLodClass *)m_renderObject50;
				HAnimClass *anim = hlod->Peek_Animation();
				if (anim)
				{
					float frame = percent * (float)(anim->Get_Num_Frames() - 1); _ReadWriteBarrier();
					float dummy1, dummy2;
					int curMode, dummy3;
					hlod->Peek_Animation_And_Info(dummy1, dummy3, curMode, dummy2);
					hlod->Set_Animation(anim, frame, curMode);
					restoreAnimation = true;
				}
			}
		}
	}

	xfer->xferBool(&m_A0);
	XferDrawableID(xfer, &m_A4);
	Rva000BC559Xfer(xfer, &m_A8);
	xfer->xferAsciiString(&m_B4);
	xfer->xferInt(&m_BC);
	xfer->xferInt(&m_C0);
	m_flags17C.xfer(xfer);
	xfer->xferInt(&m_214);

	if (xfer->isLoading())
	{
		int count = 0;
		reinterpret_cast<_STL::vector<Rva00079EA1Element> &>(m_vec68).clear();
		reinterpret_cast<_STL::vector<Rva00079EA1Element> &>(m_vec74).clear();
		BfmeStringRecord000B9534 record;
		xfer->xferInt(&count);
		m_vec68.reserve(count);
		for (int i = 0; i < count; ++i)
		{
			xfer->xferAsciiString(&record.text);
			xfer->xferBool(&record.flag);
			xfer->xferReal(&record.word0);
			xfer->xferReal(&record.word1);
			xfer->xferReal(&record.word2);
			xfer->xferReal(&record.word3);
			m_vec68.push_back(record);
		}
		xfer->xferInt(&count);
		m_vec74.reserve(count);
		for (int j = 0; j < count; ++j)
		{
			xfer->xferAsciiString(&record.text);
			xfer->xferBool(&record.flag);
			xfer->xferReal(&record.word0);
			xfer->xferReal(&record.word1);
			xfer->xferReal(&record.word2);
			xfer->xferReal(&record.word3);
			m_vec74.push_back(record);
		}
	}
	else if (xfer->isSaving())
	{
		int count = m_vec68.size();
		xfer->xferInt(&count);
		for (int i = 0; i < count; ++i)
		{
			BfmeStringRecord000B9534 *record = &m_vec68[i];
			xfer->xferAsciiString(&record->text);
			xfer->xferBool(&record->flag);
			xfer->xferReal(&record->word0);
			xfer->xferReal(&record->word1);
			xfer->xferReal(&record->word2);
			xfer->xferReal(&record->word3);
		}
		count = m_vec74.size();
		xfer->xferInt(&count);
		for (int j = 0; j < count; ++j)
		{
			BfmeStringRecord000B9534 *record = &m_vec74[j];
			xfer->xferAsciiString(&record->text);
			xfer->xferBool(&record->flag);
			xfer->xferReal(&record->word0);
			xfer->xferReal(&record->word1);
			xfer->xferReal(&record->word2);
			xfer->xferReal(&record->word3);
		}
	}

	if (xfer->isLoading())
	{
		clearSlot90();
		int count;
		xfer->xferInt(&count);
		for (int i = 0; i < count; ++i)
		{
			BfmeNarrowRecord000BFDC7 record;
			AsciiString renderObjectName(g_Rva0107301CEmptyString);
			AsciiString boneName(g_Rva0107301CEmptyString);
			xfer->xferAsciiString(&renderObjectName);
			xfer->xferAsciiString(&boneName);
			xfer->xferCoord3D(&record.word1);
			xfer->xferInt(&record.word4);
			record.word0 = Create_Render_Obj(renderObjectName.str());
			record.text = boneName.str();
			if (record.word0)
			{
				W3DDisplay::m_3DScene->Add_Render_Object(record.word0);
				m_vec164.push_back(record);
			}
		}
	}
	else if (xfer->isSaving())
	{
		int count = m_vec164.size();
		xfer->xferInt(&count);
		for (int i = 0; i < count; ++i)
		{
			BfmeNarrowRecord000BFDC7 record(m_vec164[i]);
			AsciiString renderObjectName(g_Rva0107301CEmptyString);
			AsciiString boneName(g_Rva0107301CEmptyString);
			if (record.word0)
				renderObjectName.set(record.word0->Get_Name());
			if (!record.text.empty())
				boneName.set(record.text.c_str());
			xfer->xferAsciiString(&renderObjectName);
			xfer->xferAsciiString(&boneName);
			xfer->xferCoord3D(&record.word1);
			xfer->xferInt(&record.word4);
		}
	}

	xfer->xferBool(&m_28C);
	xfer->xferBool(&m_28D);
	xfer->xferBool(&m_270);
	bool value49 = m_49;
	xfer->xferBool(&value49);
	xfer->xferBool(&m_1CA);
	xfer->xferBool(&m_80);
	xfer->xferBool(&m_1CB);
	bool value48 = m_48;
	xfer->xferBool(&m_48);
	m_48 = value48;
	xfer->xferBool(&m_81);
	xfer->xferBool(&m_1C9);
	xfer->xferBool(&m_4A);
	xfer->xferBool(&m_1C8);
	xfer->xferBool(&m_4B);
	xfer->xferBool(&m_25C);

	if (xfer->isLoading())
	{
		unsigned int color = 0;
		xfer->xferUnsignedInt(&color);
		if (color == 0)
		{
			m_recolorCount28 = 0;
			m_recolorUnused28 = 0;
			m_recolor2C = 0;
			m_recolor30 = 0;
			m_recolor34 = 0;
		}
		else
		{
			if ((*(const unsigned char *)(&m_recolor2C - 1) & 7) == 0)
			{
				m_recolorCount28 = 1;
				m_recolorUnused28 = 0;
				m_recolor2C = color;
				m_recolor30 = 0;
				m_recolor34 = 0;
			}
			else
				m_recolor2C = color;
		}
	}
	else
	{
		unsigned int color = (unsigned int)reinterpret_cast<Rva000B4653 *>(&m_recolor2C - 1)->rva000B4653(0);
		if (m_recolorCount28 == 0)
			color = 0;
		xfer->xferUnsignedInt(&color);
	}

	if (version.current < 2)
		xfer->xferInt(&m_44);
	xfer->xferAsciiString(&m_54);
	xfer->xferInt(&m_84);
	if (version.current < 2)
		xfer->xferInt(&m_88);
	xfer->xferReal(&m_8C);
	xfer->xferReal(&m_98);
	xfer->xferReal(&m_9C);
	xfer->xferReal(&m_26C);
	xfer->xferBool(&m_270);
	xfer->xferUnsignedInt(&m_274);
	xfer->xferUnsignedInt(&m_278);
	xfer->xferUnsignedInt(&m_27C);
	Rva0030612AXfer(xfer, &m_280);
	xfer->xferAsciiString(&m_260);
	for (int k = 0; k < 2; ++k)
		xfer->xferAsciiString(&m_264[k]);
	if (version.current >= 3)
		xfer->xferBool(&m_4C);
	if (version.current >= 4)
	{
		xfer->xferReal(&m_2C8);
		xfer->xferReal(&m_2CC);
		xfer->xferReal(&m_2D0);
		xfer->xferReal(&m_2D4);
	}
	if (version.current >= 5)
		xfer->xferBool(&m_4D);
	if (restoreAnimation)
		reinterpret_cast<Rva000B8F5AOuter *>(this)->rva000BFB51(percent);
	if (version.current >= 6)
	{
		int count = m_vec38.size();
		xfer->xferInt(&count);
		m_vec38.resize(count);
		for (BfmeStringRecord000B94D2 *it = m_vec38.begin(); it != m_vec38.end(); ++it)
		{
			xfer->xferAsciiString(&it->text0);
			xfer->xferAsciiString(&it->text1);
		}
	}
	if (xfer->isLoading())
	{
		setSlot8C(value49);
		slot74();
	}
}
