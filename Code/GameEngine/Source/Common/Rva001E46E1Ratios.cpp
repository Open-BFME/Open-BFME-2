// cl: /DNDEBUG /MD
// Float getters of one object-module class whose shared worker is the
// unrowed 356-byte 0x001E46E1 (pinned by address from these call sites; it
// reads the Object's +0x254 and +0x258 and calls the rowed check at
// 0x001E468F). Layout facts from the bodies: module data at +4 holding
// unsigned counts at +0x44 and +0x50; floats at +0x30, +0x34, +0x40 and a
// cached value at +0x5C stamped with a frame at +0x60, compared against
// TheGameLogic's frame (+0x40).
//   0x001E4845  worker / count44, capped at +0x30
//   0x001E488A  worker / count50, capped at +0x34
//   0x001E48CF  cached +0x5C unless its frame is stale, else the worker
//   0x001E543F  whether +0x40 exceeds a quarter of the worker
//   0x001E53D8  step +0x40 toward a limit by the +0x30-capped ratio, then
//               clamp it to [0, worker]
// Retail compares with fcompi, which MSVC 7.1 emits only under /arch:SSE.
// Class and member names are unknown, hence address-derived.
class Object;
class GameLogic;
extern GameLogic *TheGameLogic;
extern float g_secondsPerLogicFrame;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class Rva001E468F;
struct Rva001E46E1FrameView
{
	char m_pad00[0x40];
	unsigned int m_frame;
};
struct Rva001E46E1Data
{
	char m_pad00[0x24];
	float m_24;
	char m_pad28[0x44 - 0x28];
	unsigned int m_44;
	char m_pad48[8];
	unsigned int m_50;
	char m_pad54[0xEC - 0x54];
	unsigned char m_ec;
	char m_padED[0x104 - 0xED];
	float m_104;
	unsigned char m_108;
	unsigned char m_109;
	char m_pad10A[0x14C - 0x10A];
	float m_14C;
};
class Rva001E46E1
{
public:
	float rva001E46E1(Object *obj);
	float rva001E4845(Object *obj);
	float rva001E488A(Object *obj);
	bool rva001E543F(Object *obj);
	float rva001E48CF(Object *obj);
	void rva001E53D8(float limit, Object *obj);
	void *m_00;
	const Rva001E46E1Data *m_data;
	char m_pad08[0x28 - 8];
	float m_28;
	float m_2c;
	float m_30;
	float m_34;
	char m_pad38[0x40 - 0x38];
	float m_40;
	char m_pad44[0x5C - 0x44];
	float m_5C;
	unsigned int m_60;
};
class Obj254V
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual int s08();
};
struct Obj258Holder
{
	char m_pad[0x1F8];
	float m_1F8;
};
class Object
{
public:
	float rva0028B842() const;
	bool rva0028C15E(int attr, float *val, int a, int b);
	char m_pad00[0x38];
	float m_38;
	float m_3C;
	char m_pad40[0x250 - 0x40];
	void *m_250;
	Obj254V *m_254;
	Obj258Holder *m_258;
};
class GlobalData
{
public:
	char m_pad[0xB3C];
	int m_b3c;
};
class TerrainLogic
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual bool s19(float x, float y, int a, int b, unsigned char *out);
};
class Rva001E468F
{
public:
	bool rva001E468F(Object *obj);
};
float Rva001E46E1::rva001E4845(Object *obj)
{
	float value = rva001E46E1(obj) / (float)m_data->m_44;
	if (value > m_30)
		value = m_30;
	return value;
}
float Rva001E46E1::rva001E488A(Object *obj)
{
	float value = rva001E46E1(obj) / (float)m_data->m_50;
	if (value > m_34)
		value = m_34;
	return value;
}
bool Rva001E46E1::rva001E543F(Object *obj)
{
	float current = m_40;
	return current > rva001E46E1(obj) * 0.25f;
}
float Rva001E46E1::rva001E48CF(Object *obj)
{
	if (m_60 < ((const Rva001E46E1FrameView *)TheGameLogic)->m_frame)
		return rva001E46E1(obj);
	return m_5C;
}

static inline float bfmeClamp(float value, float lo, float hi)
{
	if (value < lo)
		return lo;
	if (value > hi)
		return hi;
	return value;
}

void Rva001E46E1::rva001E53D8(float limit, Object *obj)
{
	if (limit > m_40) {
		m_40 += rva001E4845(obj);
		if (m_40 > limit)
			m_40 = limit;
	} else {
		m_40 = limit;
	}
	float cap = rva001E46E1(obj);
	m_40 = bfmeClamp(m_40, 0.0f, cap);
}
float Rva001E46E1::rva001E46E1(Object *obj)
{
	int cmpVal = obj->m_254->s08();
	float scale = obj->m_258->m_1F8;
	int gv = TheWritableGlobalData->m_b3c;
	float f;
	if (cmpVal >= gv && m_data->m_109 == 0)
		f = m_data->m_24 * g_secondsPerLogicFrame * scale;
	else if (((Rva001E468F *)this)->rva001E468F(obj))
		f = m_data->m_104 * g_secondsPerLogicFrame * scale;
	else
		f = g_secondsPerLogicFrame * scale;
	if (f > m_28)
		f = m_28;
	if (m_data->m_ec != 0)
		f *= obj->rva0028B842();
	float tmp = 0.0f;
	if (obj->rva0028C15E(8, &tmp, 0, 1))
		f = tmp * f;
	if (m_data->m_14C != 1.0f) {
		unsigned char flag = 0;
		if (TheTerrainLogic->s19(obj->m_38, obj->m_3C, 0, 0, &flag) && flag != 0)
			f = m_data->m_14C * f;
	}
	if (m_2c != -1.0f) {
		if (m_2c > f)
			goto done2c;
		f = m_2c;
	}
done2c:
	return f;
}
