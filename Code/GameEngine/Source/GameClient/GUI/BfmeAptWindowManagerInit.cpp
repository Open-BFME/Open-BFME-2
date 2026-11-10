// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00224296@Rva00062918Host@@QAEXXZ @0x00224296 333B
// Apt/window-manager initializer (the BfmeAptWindowManager view other units
// use for this same object, g_bfmeAptWindowManager). Sequence transcribed from
// the WorldBuilder debug body 0xB90280 (unnamed, 532B) plus retail:
//   Rva006CC380Initialize(0x10000,0x4000,0x10000,0x4000) allocator pools;
//   the Rva00222343 Apt parameter block with m_18/m_0C doubled;
//   Rva006CF230Initialize(&params) (Apt.cpp's 2046B global install);
//   the Apt emit/transform flag cell 0x00E17718 |= 2;
//   the two Apt registration passes 0x00412F14 / 0x004121D1;
//   the three named screens AptLevel0.apt (level 0), InGameNotificationBox.apt
//   (level 0xC) and Messenger.apt (level 0xB) through 0x002239B2;
//   the virtual loadAptWindow("Apt\\","AptLevel0.apt",1,0) at slot +0x50;
//   the screen vector at +0x2FC cleared through the rowed folded range erase
//   0x0031BD55, 0x00223CBD(0xE) (push_back + +0x308 flag), the
//   m_windows[index].m_flags &= ~4 bit and the +0x329 byte reset.
// BFME1's WindowManager::init is the same function shape (its d_00894800
// parameter pass, GcRoots+8 |= 2, the two registration calls, loadAptWindow,
// the screen vector clear, the +0xA4 flag and the apt-window flag clear).
// The class name is the existing pin's vtable host; BfmeAptWindowManager is
// the semantic view. The Apt parameter block and callback names are the
// rowed providers.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN
#include <stl/_algobase.h>
#include <vector>
#include "ascii_string.h"

class ModuleData;

struct Rva001408C0Target
{
	int opaque;
};

struct Rva00222343
{
	Rva00222343(void);
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	bool m_38;
	bool m_39;
};

#include "../../../Include/GameClient/Rva002239B2.h"

class Rva00223CBD
{
public:
	void rva00223CBD(const ModuleData *p);
};

void Rva006CC380Initialize(unsigned int, int, unsigned int, int);
void Rva006CF230Initialize(const Rva00222343 *input);
void Rva00412F14Register(void);
void Rva004121D1RegisterAptComponents(void);

// 0x00E17718: the Apt emit/transform flags. BFME1 owns the same image slot as
// g_bfmeExtra1282Flags (VA 0x01337818, the whole Apt global run matches BFME2's
// at a constant +0x520100 offset); its node walk chooses the transform
// callback over the walk callback from bit 2 and skips an emit from bit 1,
// which is the shape retail 0x006F7720 shows here, and this initializer sets
// bit 1 the way BFME1's WindowManager::init does.
extern unsigned int g_bfmeExtra1282Flags;

// The vtable slots below +0x50 are opaque; slot 20 is the apt-window loader.
class Rva00062918HostLoadView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual int loadAptWindow(AsciiString directory, AsciiString file, int a, int b);
};

// Retail 0x00224296 indexes +0xF0 + index*0x28 and clears bit 2 of the first
// byte; the optimized form is the same address as (index+6)*0x28.
struct AptWindowRecord
{
	unsigned char m_flags;
	char m_pad[0x27];
};

class Rva00062918Host
{
public:
	void rva00224296();

private:
	char m_pad00[0x14];
	void *m_scene14;
	void *m_camera18;
	void *m_renderObj1C;
	char m_pad20[0xF0 - 0x20];
	AptWindowRecord m_windows[13];
	char m_pad2F8[4];
	_STL::vector<const ModuleData *> m_screens;
	bool m_screensChanged308;
	char m_pad309[0x20];
	bool m_flag329;
};

void Rva00062918Host::rva00224296()
{
	unsigned int poolSmall = 0x4000;
	unsigned int poolBig = 0x10000;
	Rva006CC380Initialize(poolBig, poolSmall, poolBig, poolSmall);

	Rva00222343 parameters;
	parameters.m_18 *= 2;
	parameters.m_0C *= 2;

	Rva006CF230Initialize(&parameters);
	g_bfmeExtra1282Flags |= 2;
	Rva00412F14Register();
	Rva004121D1RegisterAptComponents();

	((Rva002239B2 *)this)->rva002239B2((const void *)&AsciiString("AptLevel0.apt"), 0);
	((Rva002239B2 *)this)->rva002239B2(
		(const void *)&AsciiString("InGameNotificationBox.apt"), (Rva001408C0Target *)0xC);
	((Rva002239B2 *)this)->rva002239B2(
		(const void *)&AsciiString("Messenger.apt"), (Rva001408C0Target *)0xB);

	int index = ((Rva00062918HostLoadView *)this)->loadAptWindow(
		AsciiString("Apt\\"), AsciiString("AptLevel0.apt"), 1, 0);

	_STL::vector<const ModuleData *> *screens = &m_screens;
	screens->erase(screens->begin(), screens->end());
	((Rva00223CBD *)this)->rva00223CBD((const ModuleData *)0xE);
	m_windows[index].m_flags &= ~4;
	m_flag329 = false;
}
