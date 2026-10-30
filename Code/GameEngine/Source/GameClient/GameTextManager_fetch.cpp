// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /EHsc
// stlport
typedef bool Bool;
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
#include "../../../../reference/shims/subsystem_bfme2/subsystem_interface.h"
#include <vector>
struct NoString;
class GameTextTable;
struct FileInfo
{
	int sizeHigh;
	int sizeLow;
	int timestampHigh;
	int timestampLow;
};
// ?fetch@GameTextManager@@UAE?AVUnicodeString@@PBDPA_N@Z 0x002E5719 35B
// Evidence: vslot 15 offset 0x3C of vtable 0x00804FA8 class GameTextManager; forwards to slot 17 offset 0x44 then StringBase<G> copy 0x00037050
#include "unicode_string.h"

class GameTextManager : public SubsystemInterface
{
public:
	GameTextManager();
	virtual ~GameTextManager();
	virtual void init();
	virtual bool vslot04(int);
	virtual void reset();
	virtual void update() {}
	virtual UnicodeString fetch(const char *label, Bool *exists);
	virtual UnicodeString fetch(const AsciiString &label, Bool *exists);
	virtual UnicodeString *fetchPtr(const char *label, Bool *exists);
	virtual UnicodeString *fetchPtr(const AsciiString &label, Bool *exists);
	virtual _STL::vector<AsciiString> &getStringsWithLabelPrefix(const AsciiString &label);
	virtual void initMapStringFile(const AsciiString &filename);
	virtual void setTranslateMode(int mode);
	virtual int getTranslateMode() { return m_translateMode; }
	virtual void deinit();

	FileInfo m_fileInfo;					// +0x0c
	Bool m_usedCSF;							// +0x1c
	Bool m_initialized;						// +0x1d
	UnicodeString m_failed;					// +0x20
	NoString *m_noStringList;				// +0x24
	int m_unk28;							// +0x28
	GameTextTable *m_textTable;				// +0x2c
	GameTextTable *m_mapTable;				// +0x30
	_STL::vector<AsciiString> m_asciiStringVec;	// +0x34
	int m_translateMode;					// +0x40
};

UnicodeString GameTextManager::fetch(const char *label, bool *exists)
{
	return *fetchPtr(label, exists);
}
