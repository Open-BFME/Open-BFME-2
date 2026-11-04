// cl: /O1 /G7 /arch:SSE /MD /EHs /EHc- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// StrategicVeterancy::Data::AutoResolve dtor pair.
//
// ??1AutoResolve@Data@StrategicVeterancy@@MAE@XZ   @ 0x005ECFE4 (11 B)
// ??_GAutoResolve@Data@StrategicVeterancy@@MAEPAXI@Z @ 0x005ECFC8 (28 B)
//
// Identity: the rowed ctor ??0AutoResolve@Data@StrategicVeterancy@@QAE@PAX00@Z
// at 0x005ECE81 (327 B) ends exactly at 0x005ECFC8, and the class vtable retail
// installs (0x008785B4, the only vtable emitted for the class by the ctor TU)
// has slot 0 = 0x005ECFC8, the deleting dtor rowed here. The dtor at 0x005ECFE4
// stores that same vtable and tail-jumps to the rowed base dtor at 0x005ECAD0.
// Both bodies are therefore the class's own dtor pair, under the real names the
// ctor row already spells.
//
// Declaring the classes exactly as the ctor TU does (Data between AutoResolve
// and the address-named base) makes the compiler emit the same 11-byte
// "store vtable, jmp base dtor" body with the same two relocations, plus the
// standard 28-byte scalar deleting dtor.

class Rva005ECA91
{
public:
	Rva005ECA91();
protected:
	virtual ~Rva005ECA91();
private:
	char m_unrecovered04[0x18];
};

#include "../../../Include/GameClient/StrategicVeterancy.h"

class StrategicVeterancy::Data : public Rva005ECA91
{
public:
	class AutoResolve;
};

class StrategicVeterancy::Data::AutoResolve : public StrategicVeterancy::Data
{
public:
	AutoResolve(void *arg0, void *arg1, void *arg2);
protected:
	virtual ~AutoResolve();
};

StrategicVeterancy::Data::AutoResolve::~AutoResolve()
{
}
