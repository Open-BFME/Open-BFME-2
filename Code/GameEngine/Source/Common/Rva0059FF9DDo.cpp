// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva0059FF9DDo@@YAXXZ @ 0x0059FF9D (108B).
// Free record dispatch: local OwnedRecord492 with unknown_00 0x19 and
// payload words from globals g_009C0758/g_009C075C, virtual slot 6 call on
// global g_00A02340 with record pointer. Rows: ctor 0x001EF661 and dtor
// 0x001EF723. Callers 0x005A2211/0x005A332E.
#include <string>
#include <vector>

struct PeerRequest
{
	PeerRequest();
	~PeerRequest();
	int unknown_00;
	std::string unknown_04;
	std::wstring unknown_10;
	std::string unknown_1c;
	std::string unknown_28;
	std::string unknown_34;
	std::string unknown_40;
	std::string unknown_4c;
	std::string unknown_58;
	std::string unknown_64;
	std::string unknown_70[8];
	unsigned int unknown_d0[10];
	std::string unknown_f8;
	std::vector<bool> unknown_104;
	union
	{
		struct { int word; } payload_word0;
		struct { int word; } payload_word1;
		struct { int word; } payload_word2;
		struct { bool value; } payload_flag0;
		struct { bool value; } payload_flag1;
		struct { int word; } payload_word3;
		struct { int words[15]; } payload_60;
		struct { int words[53]; } payload_212a;
		struct { bool value; } payload_flag2;
		struct { int words[26]; } payload_104;
		struct { int words[7]; } payload_28;
		struct { int first; int second; } payload_8c;
	};
};

struct Global003EF728V6
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6(PeerRequest *rec);
};

extern int g_009C0758;
// g_009C0758: matched references place it at VA 0xdc0758 (retail .data initial value -1).
int g_009C0758 = -1;
extern int g_009C075C;
// g_009C075C: matched references place it at VA 0xdc075c (retail .data initial value -1).
int g_009C075C = -1;
// 0x00A02340 is PeerThread.cpp's TheGameSpyPeerMessageQueue; this unit reads it
// through its own view.
extern class GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

void __cdecl Rva0059FF9DDo()
{
	PeerRequest rec;
	rec.unknown_00 = 0x19;
	rec.payload_60.words[0] = g_009C0758;
	rec.payload_60.words[1] = g_009C075C;
	((Global003EF728V6 *)TheGameSpyPeerMessageQueue)->f6(&rec);
}
