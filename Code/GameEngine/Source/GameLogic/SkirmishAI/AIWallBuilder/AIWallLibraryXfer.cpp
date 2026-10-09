// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?Rva004E99F1Xfer@@YAXPAVXfer@@@Z retail 0x004E99F1..0x004E9B46 (341 bytes).
// Save/load of the shared AI wall library (the pointer vector at 0x00A04484
// that AIWallBuilder.cpp's library loader fills): the wall count goes
// through Xfer slot +0x78; when saving, each wall's name key (+0x48) is
// written as its name (rowed NameKeyGenerator::keyToName 0x00148C95, Xfer
// +0x6C) followed by the rowed AIWall::DoXfer 0x004EB092 (false); when
// loading, each name is read back, keyed (rowed nameToKey 0x0009FA65) and
// looked up in the library (rowed 0x004E99D6): a known wall loads into its
// entry, an unknown one into a throwaway wall built by the rowed ctor
// 0x004EB583 (0) and destroyed by the rowed 0x004EB5E9 (DoXfer true).
// Called from 0x002A8C78. WorldBuilder twin 0x01380C90 is unnamed; it keys
// the name through the char* overload.
#include "ascii_string.h"

typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual Xfer &xferAsciiString(AsciiString *value); // +0x6C
	virtual void slot28(); virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt *value); // +0x78
};

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class AIWall
{
public:
	void DoXfer(Xfer *xfer, bool loadingNew);

	unsigned char m_pad00[0x48];
	NameKeyType m_nameKey; // +0x48
};

// The throwaway wall: built by the rowed 0x004EB583 and destroyed by the
// rowed virtual 0x004EB5E9 (the ledger's two address-named halves of one
// 0x4C-byte class).
class Rva004EB583
{
public:
	Rva004EB583(int value);
	virtual ~Rva004EB583();

private:
	unsigned char m_pad04[0x4C - 0x04];
};

class __declspec(novtable) Rva004EB5E9 : public Rva004EB583
{
public:
	Rva004EB5E9(int value) : Rva004EB583(value) {}
	virtual ~Rva004EB5E9();
};

struct RvaVector
{
	void **begin, **end, **capacity;
};

extern RvaVector g_00E04484;

void **rva004E99D6(void **first, void **last, const void *key);

void Rva004E99F1Xfer(Xfer *xfer)
{
	UnsignedInt count = g_00E04484.end - g_00E04484.begin;
	xfer->xferUnsignedInt(&count);
	if (xfer->IsStoring())
	{
		void **end = g_00E04484.end;
		for (void **it = g_00E04484.begin; it != end; ++it)
		{
			AsciiString name = TheNameKeyGenerator->keyToName(((AIWall *)*it)->m_nameKey);
			xfer->xferAsciiString(&name);
			((AIWall *)*it)->DoXfer(xfer, false);
		}
	}
	else if (xfer->IsLoading())
	{
		for (UnsignedInt i = 0; i < count; ++i)
		{
			AsciiString name;
			xfer->xferAsciiString(&name);
			NameKeyType key = TheNameKeyGenerator->nameToKey(name);
			void **found = rva004E99D6(g_00E04484.begin, g_00E04484.end, &key);
			if (found != g_00E04484.end)
			{
				((AIWall *)*found)->DoXfer(xfer, false);
			}
			else
			{
				Rva004EB5E9 wall(0);
				((AIWall *)&wall)->DoXfer(xfer, true);
			}
		}
	}
}
