// cl: /DNDEBUG /MD /EHsc
// Retail 0x002EF3D9 and 0x002F2865, 21B each: forward (record, record+0x38,
// arg) to a three-argument member on the same object (0x002EC8C3 and
// 0x002F133C respectively). Types are opaque.

class Rva002EF3D9Host
{
public:
	int rva002EC8C3(char *record, char *tail, int arg);
	int rva002EF3D9(char *record, int arg);
};

int Rva002EF3D9Host::rva002EF3D9(char *record, int arg)
{
	return rva002EC8C3(record, record + 0x38, arg);
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
