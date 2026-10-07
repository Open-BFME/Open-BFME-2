// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?Rva000EA1DBTopple@@YAXPAVRva000EA1DBTarget@@H@Z @0x000EA1DB 24B. Free forwarder loading this from [esp+4] and tail-calling vtable slot 0x94 (37) with "W3DToppleState" plus [esp+8] plus 4. Evidence: string data 0x007CECFC plus slot 0x94 plus caller at 0x000ED7D6.
class Rva000EA1DBTarget
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void f19();
	virtual void f20();
	virtual void f21();
	virtual void f22();
	virtual void f23();
	virtual void f24();
	virtual void f25();
	virtual void f26();
	virtual void f27();
	virtual void f28();
	virtual void f29();
	virtual void f30();
	virtual void f31();
	virtual void f32();
	virtual void f33();
	virtual void f34();
	virtual void f35();
	virtual void f36();
	virtual void v37(const char *a0, int a1, int a2);
};

void __cdecl Rva000EA1DBTopple(Rva000EA1DBTarget *obj, int val)
{
	obj->v37("W3DToppleState", val, 4);
}
