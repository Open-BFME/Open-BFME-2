// cl: /O1 /DNDEBUG /MD /arch:SSE
// Small float-vector fetch around 0x000BBE29 (93B). A two-argument stdcall:
// looks a key up through the pinned map probe (0x000BBDDF), zeroes the
// three-float out-vector and reports false when the probe misses, otherwise
// stages node floats +0x0C/+0x1C/+0x2C through a stack temporary and block
// copies them out (rep movsd), reporting true. The probe's map/value types
// are not established (stlport _M_find at 0x00388F63 works on an int key),
// so the call goes through a fresh-typed symbols.csv pin and the value view
// below is layout only. Names are address-derived.

void *__stdcall rva000BBDDF(int key, int flag);

struct Vector3
{
	float x, y, z;
};

struct Rva000BBDDFNode
{
	char m_pad00[0x0C];
	float m_0C;
	char m_pad10[0x1C - 0x10];
	float m_1C;
	char m_pad20[0x2C - 0x20];
	float m_2C;
};

// ?rva000BBE29@@YG_NHPAUVector3@@@Z @0x000BBE29 93B
bool __stdcall rva000BBE29(int key, Vector3 *out)
{
	Rva000BBDDFNode *node = (Rva000BBDDFNode *)rva000BBDDF(key, 0);
	if (node != 0)
	{
		Vector3 tmp;
		tmp.x = node->m_0C;
		tmp.y = node->m_1C;
		tmp.z = node->m_2C;
		*out = tmp;
		return true;
	}
	out->x = 0.0f;
	out->y = 0.0f;
	out->z = 0.0f;
	return false;
}
