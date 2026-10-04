// cl: /O1 /arch:SSE /DNDEBUG /MD
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
// Retail compares with fcompi, which MSVC 7.1 emits only under /arch:SSE.
// Class and member names are unknown, hence address-derived.
class Object;
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva001E46E1FrameView
{
	char m_pad00[0x40];
	unsigned int m_frame;
};
struct Rva001E46E1Data
{
	char m_pad00[0x44];
	unsigned int m_44;
	char m_pad48[8];
	unsigned int m_50;
};
class Rva001E46E1
{
public:
	float rva001E46E1(Object *obj);
	float rva001E4845(Object *obj);
	float rva001E488A(Object *obj);
	bool rva001E543F(Object *obj);
	float rva001E48CF(Object *obj);
	void *m_00;
	const Rva001E46E1Data *m_data;
	char m_pad08[0x30 - 8];
	float m_30;
	float m_34;
	char m_pad38[0x40 - 0x38];
	float m_40;
	char m_pad44[0x5C - 0x44];
	float m_5C;
	unsigned int m_60;
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
