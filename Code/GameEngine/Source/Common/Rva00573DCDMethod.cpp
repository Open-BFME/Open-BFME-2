// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva00573DCD@Rva00573B23@@QAEMH@Z @0x00573DCD 77B
// Vtable slot 9 float method: ThingTemplate lookup via AsciiString at +0xC and ObjectID at +8.
// Evidence: vtable slot 9 of 0x0086E270 0x0086E2C8 0x00870B38; callees rowed 0x002D06CA 0x00049DC5
// plus pin 0x0033A69A; globals g_009FF000 and TheGameLogic; fild float return with int arg.
#include "ascii_string.h"

enum ObjectID
{
	OBJECTID_INVALID = 0
};

class Object;
class AsciiString;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *s);
};

class GameLogic
{
public:
	class Object *findObjectByID(enum ObjectID id);
};

class ThingTemplate
{
public:
	int rva0033A69A(class Object *obj, int a, int b) const;
};

extern Rva002D06CA *g_009FF000;
extern GameLogic *TheGameLogic;

class Rva0055B0CC
{
public:
	virtual ~Rva0055B0CC();
};

class Rva00573B23 : public Rva0055B0CC
{
public:
	float rva00573DCD(int arg);
private:
	char m_pad04[4];
	enum ObjectID m_08;
	AsciiString m_0C;
	char m_pad10[0x1C];
	AsciiString m_2C;
};

float Rva00573B23::rva00573DCD(int arg)
{
	void *thing = g_009FF000->rva002D06CA(&m_0C);
	class Object *obj = TheGameLogic->findObjectByID(m_08);
	int value = 0;
	ThingTemplate *tmpl = (ThingTemplate *)thing;
	unsigned char flag = *((unsigned char *)tmpl + 0x11B);
	if ((flag & 0x20) == 0)
		value = tmpl->rva0033A69A((class Object *)arg, (int)obj, -1);
	return (float)value;
}
