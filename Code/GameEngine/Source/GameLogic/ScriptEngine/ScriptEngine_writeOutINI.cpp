// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// _writeOutINI, retail 0x0020CEC7 (414B), the particle editor's INI writer.
//
// Identity (target): the "Data\\INI\\FXParticleSystem" + "%s%d.%s" + "BAK"
// backup loop and the two opens of "Data\\INI\\FXParticleSystem.ini" are Zero
// Hour ScriptEngine.cpp's _writeOutINI with the BFME file names. No call or
// address reference to it is left in the image. It sits between
// evaluateAndProgressAllSequentialScripts and update, behind the sort
// instantiation 0x0020CE84 it calls.
// Donor: BFME 1 ParticleSystemManagerWriteINI.cpp (Open-BFME-1 game/), which
// sorts the template map into a vector before writing. BFME2 opens files with
// a third argument of 0, writes with 0x2A instead of 0x22, and keeps the
// template map at ParticleSystemManager+0x88.
// Retail reads its callees at their REL32s:
// - FileSystem::openFile 0x00600C34;
// - the hash-table head fetch 0x00427195 and the iterator advance 0x00411084,
//   under their address-derived names;
// - the vector base ctor 0x00211E58 and push_back 0x004DFCB0, both ICF folds
//   pinned under the 4-byte long element;
// - sort<int*, Rva00204BB8> 0x0020CE84 with the template name comparator;
// - the per-template writer 0x001FB418, which is ParticleSystemTemplate::writeINI
//   in the BFME 1 donor. Its body opens with the "FXParticleSystem" block name
//   and writes IsOneShot, ParticleName, SlaveSystem and SlavePosOffset (ret 8).
// The vector is freed through the C++-linkage free STLport compiles against,
// which is what keeps the unwind-state store before the call, while sprintf
// stays the CRT import.
#define free bfmeUnusedCRTFree
#include <cstdlib>
#undef free
void free(void *);
#include <stdio.h>
#include <algorithm>
#include <vector>

class File
{
public:
	virtual ~File();
	virtual bool open(const char *, int = 0);
	virtual void close();
	virtual int read(void *, int);
	virtual int write(const void *, int);
	virtual int seek(int, int);
	virtual void nextLine(char *, int);
	virtual bool scanInt(int &);
	virtual bool scanReal(float &);
	virtual bool scanString(void *);
	virtual bool print(const char *, ...);
	virtual int size();
	virtual int position();
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access, int bufferSize);
};

extern FileSystem *TheFileSystem;

namespace FXParticleSystem
{

class ParticleSystemTemplate
{
public:
	void writeINI(File &file, unsigned int flags) const;
};

}

// The user-declared constructor leaves the by-value comparator temporary
// uninitialized, as retail pushes it.
class Rva00204BB8
{
public:
	Rva00204BB8() {}
	bool operator()(int a, int b) const;
};

class Rva000427195;
class Rva000411084
{
public:
	void *m_node;
	Rva000427195 *m_table;
	void *next();
};

class Rva000427195
{
public:
	void *first(Rva000411084 *iterator);
};

// Hash-table nodes are {next+0 name+4 template+8}.
struct TemplateNode
{
	TemplateNode *m_next;
	void *m_name;
	long m_template;
};

class ParticleSystemManager
{
public:
	unsigned char m_pad[0x88];
	Rva000427195 m_templateMap;	// +0x88
};

extern ParticleSystemManager *TheParticleSystemManager;

void _writeOutINI()
{
	const int maxFileLength = 128;
	char buff[maxFileLength];
	File *saveFile = 0;
	int i = 0;

	do
	{
		if (saveFile)
		{
			saveFile->close();
			saveFile = 0;
		}
		sprintf(buff, "%s%d.%s", "Data\\INI\\FXParticleSystem", i, "BAK");
		saveFile = TheFileSystem->openFile(buff, 0x21, 0);
		++i;
	} while (saveFile);

	saveFile = TheFileSystem->openFile(buff, 0x2A, 0);
	if (!saveFile)
		return;

	File *oldINI = TheFileSystem->openFile("Data\\INI\\FXParticleSystem.ini", 0x21, 0);
	if (oldINI)
	{
		char singleChar;
		while (oldINI->position() != oldINI->size())
		{
			oldINI->read(&singleChar, 1);
			saveFile->write(&singleChar, 1);
		}
		oldINI->close();
		oldINI = 0;
		saveFile->close();
		saveFile = 0;
	}

	File *newINI = TheFileSystem->openFile("Data\\INI\\FXParticleSystem.ini", 0x2A, 0);
	if (!newINI)
		return;

	_STL::vector<long> templates;
	{
		Rva000411084 it;
		TheParticleSystemManager->m_templateMap.first(&it);
		for (; it.m_node; it.next())
			templates.push_back(((TemplateNode *)it.m_node)->m_template);
	}

	_STL::sort((int *)templates.begin(), (int *)templates.end(), Rva00204BB8());
	int *first = (int *)templates.begin();
	if (first != (int *)templates.end())
	{
		((FXParticleSystem::ParticleSystemTemplate *)*first)->writeINI(*newINI, 0);
		for (int *p = first + 1; p != (int *)templates.end(); ++p)
		{
			newINI->write("\n", 1);
			((FXParticleSystem::ParticleSystemTemplate *)*p)->writeINI(*newINI, 0);
		}
	}

	newINI->close();
}
