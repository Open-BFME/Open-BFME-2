// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?initOffsets@AODHordeContain@@QAEXPAX@Z, retail 0x0047B690, 757 bytes.
// AODHordeContain::initOffsets (WB 0x1161F80, AODHordeContain.cpp lines 0x20A-0x211
// and the m_numRows<MAX_ROWS assert at 545). After the HordeContain base init
// (0x474519) it reserves the +0x30C per-slot jitter vector (24-byte records)
// to the +0x188 record count, fills each with six GetGameLogicRandomValueReal
// draws, then builds the +0x6FC row table (20 rows of 0x18: distinct record
// x keys, the offset rotated through 0x468E98 and added to the object position,
// the object orientation) and finally passes each row position, last first, to
// the rowed history push 0x0047A729. Layout from the rowed AOD ctor 0x0047B3DB;
// WB offsets run four (rows) / eight (module data) lower than retail's.
#include <vector>

struct BfmePod24 { int a[6]; };
struct Rva0047B35EElement { int opaque[6]; };

struct AODOffset2D
{
	AODOffset2D() {}
	AODOffset2D(float px, float py) : x(px), y(py) {}
	AODOffset2D(const AODOffset2D &other) : x(other.x), y(other.y) {}
	~AODOffset2D() {}
	float x;
	float y;
};
struct Float3
{
	Float3() {}
	Float3(const Float3 &other) : x(other.x), y(other.y), z(other.z) {}
	float x;
	float y;
	float z;
};

float GetGameLogicRandomValueReal(float, float, char *, int);

class Object
{
public:
	unsigned char m_pad00[0x38];
	Float3 m_position;
	float m_orientation;
};

struct AODModuleDataView
{
	unsigned char m_pad[0x278];
	float m_a;
	unsigned char m_pad27C[4];
	float m_b;
	unsigned char m_pad284[8];
	float m_c;
	unsigned char m_pad290[4];
	float m_d;
};

struct Rva00474519Record
{
	float m_pad0;
	float m_key;
	unsigned char m_pad8[0x1C - 8];
};

struct Rva0047B690Row
{
	float m_key;
	float m_orientation;
	Float3 m_position;
	bool m_valid;
	unsigned char m_pad[3];
};

class AODHordeContain
{
public:
	void initOffsets(void *arg);
	void rva00474519(void *arg);
	AODOffset2D *rva00468E98(AODOffset2D *out, AODOffset2D offset);
	void rva0047A729(const Float3 *position);

private:
	unsigned char m_pad00[4];
	const AODModuleDataView *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x188 - 0xC];
	_STL::vector<Rva00474519Record> m_records;
	unsigned char m_pad194[0x30C - 0x194];
	_STL::vector<Rva0047B35EElement> m_jitter;
	unsigned char m_pad318[0x6FC - 0x318];
	Rva0047B690Row m_rows[20];
	int m_numRows;
};

void AODHordeContain::initOffsets(void *arg)
{
	Object *object = m_object;
	const AODModuleDataView *data = m_moduleData;
	rva00474519(arg);
	int count = m_records.size();
	m_jitter.reserve(count);
	for (int i = 0; i < count; ++i)
	{
		float v[6];
		float angle = 6.2831855f * data->m_a;
		v[1] = GetGameLogicRandomValueReal(1.0f - data->m_b, 1.0f + data->m_b, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp", 0x20A);
		v[0] = GetGameLogicRandomValueReal(0.0f, angle, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp", 0x20B);
		v[2] = GetGameLogicRandomValueReal(1.0f - data->m_a, 1.0f + data->m_a, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp", 0x20C);
		angle = 6.2831855f * data->m_c;
		v[4] = GetGameLogicRandomValueReal(1.0f - data->m_d, 1.0f + data->m_d, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp", 0x20F);
		v[3] = GetGameLogicRandomValueReal(0.0f, angle, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp", 0x210);
		v[5] = GetGameLogicRandomValueReal(1.0f - data->m_c, 1.0f + data->m_c, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\AODHordeContain.cpp", 0x211);
		((_STL::vector<BfmePod24> *)&m_jitter)->push_back(*(const BfmePod24 *)v);
	}

	float first = 0.0f;
	for (int i = 0; i < count; ++i)
	{
		float key = m_records[i].m_key;
		bool found = false;
		for (int j = 0; j < m_numRows; ++j)
		{
			if (key == m_rows[j].m_key)
			{
				found = true;
				break;
			}
		}
		if (found)
			continue;
		if (m_numRows >= 20)
			break;
		m_rows[m_numRows].m_key = key;
		if (m_numRows == 0)
			first = key;
		AODOffset2D rotated;
		AODOffset2D offset(key - first, 0.0f);
		rva00468E98(&rotated, offset);
		m_rows[m_numRows].m_valid = true;
		Float3 position(object->m_position);
		position.x += rotated.x;
		position.y += rotated.y;
		m_rows[m_numRows].m_position = position;
		m_rows[m_numRows].m_orientation = object->m_orientation;
		++m_numRows;
	}

	for (int n = m_numRows - 1; n >= 0; --n)
		rva0047A729(&m_rows[n].m_position);
}
