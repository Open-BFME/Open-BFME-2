// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?Rva002AA41A@@YAHPAVObject@@PAX@Z @0x002AA41A 64B
// Best-object iteration callback beside 0x002AA3D4: with non-null user data
// (a point, then best object +0xC and best squared distance +0x10), keep
// the object if it is nearer (squared 2D distance 0x002615E3) and its
// +0x45C is set; always answer 1. Retail keeps the distance on the x87
// stack and skips on best <= distance (fst/fcompi/jbe), which is
// `best > distance` taken as the condition; the earlier banked early-return
// form reloaded the value and inverted the jump. Names are address-derived.
// ?Rva002AA41A@@YAHPAVObject@@PAX@Z @0x002AA41A 64B: best-object callback via rowed distSq 0x002615E3. Evidence: same shape as Player best search 0x002AB22A; writes Object+0xC and float+0x10 over Rva002A996F layout; LINK wants void YAX but retail always returns 1 so int is honest.
class Object
{
public:
	char m_pad[0x45C];
	int m_045C;
};

class Rva000CBA20Point
{
public:
	float x;
	float y;
	float z;
};

class Rva000CBA20
{
public:
	float distSq(const Rva000CBA20Point *point);
};

struct Rva002A996FData
{
	Rva000CBA20Point m_point;
	Object *m_best;
	float m_bestDist;
};

int __cdecl Rva002AA41A(Object *obj, void *userData)
{
	Rva002A996FData *data = reinterpret_cast<Rva002A996FData *>(userData);
	if (data) {
		float d = reinterpret_cast<Rva000CBA20 *>(obj)->distSq(reinterpret_cast<const Rva000CBA20Point *>(data));
		if (data->m_bestDist > d && obj->m_045C != 0) {
			data->m_best = obj;
			data->m_bestDist = d;
		}
	}
	return 1;
}
