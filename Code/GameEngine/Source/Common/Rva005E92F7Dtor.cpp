// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD
// Native destructor 005E92F7 (60B) and constructor 005E93FF (140B).
// Measured prefixes: primary 8B; holder 20B at +8; copied record 12B at +1C.
// Record base construction precedes final derived vtable stores.
// Record-base inheritance is a codegen model; original class identity is unknown.
// Evidence: reverse/identity_evidence/button-record-base-constructor.md
#include "ascii_string.h"

class Image;
const Image *Rva005E936AGet(const void *input);

class Rva005E12D1
{
public:
	Rva005E12D1(void *owner, const AsciiString &kind, void *id);
	virtual ~Rva005E12D1();
private:
	char holderStorage[0x10];
};
class Rva005E1158
{
public:
	void rva005E1158(const Image *image);
	virtual ~Rva005E1158();
private:
	int m_04; // +0x04
	void *m_08; // +0x08
};

class Rva005E92F7Base
{
public:
	Rva005E92F7Base() : m_04(0) {}
	virtual ~Rva005E92F7Base() {}
protected:
	int m_04;
};

// This record's base view destroys to Rva005E92F7Base's vtable. Other button
// views named Rva005F5C77Base0 destroy to different tables; their original
// relationship is unproven, so they cannot share this out-of-line destructor.
class Rva005E92F7RecordBase : public Rva005E92F7Base
{
public:
	virtual ~Rva005E92F7RecordBase() {}
};

struct Rva005E92F7Record
{
	int m_id;
	int m_04;
	const void *m_image;
};

class Rva005E92F7 : public Rva005E92F7RecordBase, public Rva005E12D1, public Rva005E92F7Record
{
public:
	Rva005E92F7(unsigned int owner, void *record);
	virtual ~Rva005E92F7();
};

Rva005E92F7::Rva005E92F7(unsigned int owner, void *record)
	: Rva005E12D1((void *)owner, AsciiString("button"), *(void **)record),
	  Rva005E92F7Record(*(Rva005E92F7Record *)record)
{
	reinterpret_cast<Rva005E1158 *>(static_cast<Rva005E12D1 *>(this))->rva005E1158(Rva005E936AGet(m_image));
}

Rva005E92F7::~Rva005E92F7()
{
}

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;
const Image *__cdecl Rva005E936AGet(const void *p)
{
    static const Image *fallback = TheMappedImageCollection->findImageByName(AsciiString("BuildingNoArt"));
    const AsciiString &name = *(const AsciiString *)((const char *)p + 0x14);
    const Image *result = fallback;
    if (!((const StringBase<char> *)&name)->isEmpty()) {
        result = TheMappedImageCollection->findImageByName(name);
        if (result == 0)
            result = fallback;
    }
    return result;
}
