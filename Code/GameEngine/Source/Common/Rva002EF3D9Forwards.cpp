// cl: /DNDEBUG /MD /EHsc
// Retail 0x002EF3D9 and 0x002F2865, 21B each: forward (record, record+0x38,
// arg) to a three-argument member on the same object (0x002EC8C3 and
// 0x002F133C respectively). The first worker is now proven _GetOverlapUnits;
// its arguments are Object*, Object position at+0x38, and int* result array.
// The second worker retains its opaque view.

class Object;
struct Coord3D;
class Pathfinder { public: int _GetOverlapUnits(Object *,const Coord3D *,int *); };

class Rva002EF3D9Host
{
public:
	int rva002EF3D9(char *record, int arg);
};

int Rva002EF3D9Host::rva002EF3D9(char *record, int arg)
{
	return reinterpret_cast<Pathfinder *>(this)->_GetOverlapUnits(
        reinterpret_cast<Object *>(record),reinterpret_cast<const Coord3D *>(record+0x38),reinterpret_cast<int *>(arg));
}

class Rva002F2865Host
{
public:
	int rva002F133C(char *record, char *tail, int arg);
	int rva002F2865(char *record, int arg);
};

int Rva002F2865Host::rva002F2865(char *record, int arg)
{
	return rva002F133C(record, record + 0x38, arg);
}
