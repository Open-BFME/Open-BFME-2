// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?rva004AC135@RainOfFireUpdate@@UAEXM@Z, retail 0x004AC135, 19 bytes: slot 1
// of the vtable 0x00C54BA0 that RainOfFireUpdate's ctors (0x004AC0E3,
// 0x004AC272) install at +0x20, beside the rowed slot 0 setter of the same
// float; adds the argument to the float at +0x2C. Compiled with the +0x20
// subobject this. Names by address.
class UpdateModule
{
public:
	virtual ~UpdateModule();
private:
	unsigned char m_pad04[0x20 - 4];
};

class RainOfFireUpdateInterface
{
public:
	virtual void slot0(float value) = 0;
	virtual void rva004AC135(float delta) = 0;
};

class RainOfFireUpdate : public UpdateModule, public RainOfFireUpdateInterface
{
public:
	virtual void rva004AC135(float delta);
private:
	unsigned char m_pad24[0x2C - 0x24];
	float m_2C; // +0x2C
};

void RainOfFireUpdate::rva004AC135(float delta)
{
	m_2C += delta;
}
