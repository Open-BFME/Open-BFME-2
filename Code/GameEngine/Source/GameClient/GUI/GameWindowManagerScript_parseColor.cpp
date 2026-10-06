// cl: /Oy- /DNDEBUG /MD /EHsc
//
// ?parseColor@@YA_NPAHPAD@Z, retail 0x00314F32, 103 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseColor): strtok three color bytes via msvcr71 imports, atoi each,
// winMakeColor through slot 0x118 of the WindowManager at 0x009FEF1C.
// BFME2 facts (all retail-measured):
// - strtok rides the msvcr71 import at 0xBBA5EC, atoi at 0xBBA624
//   (both dllimport decls; retail calls them indirectly via esi/edi).
// - seps " \t\n\r" lives at 0xC0C23C (shared with parseImageOffset).
// - red/green/blue are bytes at [ebp-0xC/-8/-4] (mov al stores).
// - winMakeColor slot 0x118 (70); TheWindowManager global 0x009FEF1C.
// - Identity: caller at 0x00315B3C (mid-function) plus leaf lane.

typedef int Int;
typedef bool Bool;

typedef Int Color;
typedef unsigned char Byte;

#ifndef NULL
#define NULL 0
#endif

class GameWindowManager
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
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
	virtual void f37();
	virtual void f38();
	virtual void f39();
	virtual void f40();
	virtual void f41();
	virtual void f42();
	virtual void f43();
	virtual void f44();
	virtual void f45();
	virtual void f46();
	virtual void f47();
	virtual void f48();
	virtual void f49();
	virtual void f50();
	virtual void f51();
	virtual void f52();
	virtual void f53();
	virtual void f54();
	virtual void f55();
	virtual void f56();
	virtual void f57();
	virtual void f58();
	virtual void f59();
	virtual void f60();
	virtual void f61();
	virtual void f62();
	virtual void f63();
	virtual void f64();
	virtual void f65();
	virtual void f66();
	virtual void f67();
	virtual void f68();
	virtual void f69();
	virtual int winMakeColor(Byte r, Byte g, Byte b, int a);
};

extern GameWindowManager *TheWindowManager;

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *str);

Bool parseColor(Color *color, char *buffer)
{
	char *c;
	Byte red, green, blue;

	c = strtok(buffer, " \t\n\r");
	red = (Byte)atoi(c);

	c = strtok(NULL, " \t\n\r");
	green = (Byte)atoi(c);

	c = strtok(NULL, " \t\n\r");
	blue = (Byte)atoi(c);

	*color = TheWindowManager->winMakeColor(red, green, blue, 255);

	return true;
}
