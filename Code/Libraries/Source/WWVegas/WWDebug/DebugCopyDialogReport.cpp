// cl: /DNDEBUG /MD /EHs-c-
//
// Copy button of the assert/crash dialog, retail 0x0003D3A0 (752 bytes);
// the dialog procedure at 0x0003D6A0 calls it for control 9. It joins the
// dialog title, the report text and the three build-info strings of the
// Debug singleton (virtuals at slots 0xA0/0xA4/0xA8), each non-empty one
// followed by "\r\n", and hands the result to DebugCopyToClipboard; when
// the buffer cannot be allocated it copies the report text alone. The
// title pointer is read before the buffer is cleared, which is where
// retail loads it. The name is descriptive; no symbol survives for it.

#include <string.h>

void *DebugAllocMemory(unsigned int numBytes);
void DebugFreeMemory(void *ptr);
void DebugCopyToClipboard(const char *text);

// Title and report text the dialog shows (set by the dialog driver).
extern "C"
{
	extern const char *g_rva0088E000MessageText;
	extern const char *g_rva0088E000WindowText;
}

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13(); virtual void pad14(); virtual void pad15();
	virtual void pad16(); virtual void pad17(); virtual void pad18(); virtual void pad19();
	virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23();
	virtual void pad24(); virtual void pad25(); virtual void pad26(); virtual void pad27();
	virtual void pad28(); virtual void pad29(); virtual void pad30(); virtual void pad31();
	virtual void pad32(); virtual void pad33(); virtual void pad34(); virtual void pad35();
	virtual void pad36(); virtual void pad37(); virtual void pad38(); virtual void pad39();
	virtual const char *GetVersion();
	virtual const char *GetInternalVersion();
	virtual const char *GetBuildDate();
};

extern Debug *theDebug;

// ?DebugCopyDialogReport@@YAXXZ
void DebugCopyDialogReport()
{
	unsigned int size = 0;
	if (*g_rva0088E000WindowText)
		size = strlen(g_rva0088E000WindowText) + 2;
	if (*g_rva0088E000MessageText)
		size += strlen(g_rva0088E000MessageText) + 2;
	if (*theDebug->GetVersion())
		size += strlen(theDebug->GetVersion()) + 2;
	if (*theDebug->GetInternalVersion())
		size += strlen(theDebug->GetInternalVersion()) + 2;
	if (*theDebug->GetBuildDate())
		size += strlen(theDebug->GetBuildDate()) + 2;

	char *text = (char *)DebugAllocMemory(size + 1);
	if (text)
	{
		const char *title = g_rva0088E000WindowText;
		*text = 0;
		if (*title)
		{
			strcat(text, title);
			strcat(text, "\r\n");
		}
		if (*g_rva0088E000MessageText)
		{
			strcat(text, g_rva0088E000MessageText);
			strcat(text, "\r\n");
		}
		if (*theDebug->GetVersion())
		{
			strcat(text, theDebug->GetVersion());
			strcat(text, "\r\n");
		}
		if (*theDebug->GetInternalVersion())
		{
			strcat(text, theDebug->GetInternalVersion());
			strcat(text, "\r\n");
		}
		if (*theDebug->GetBuildDate())
		{
			strcat(text, theDebug->GetBuildDate());
			strcat(text, "\r\n");
		}

		DebugCopyToClipboard(text);
		DebugFreeMemory(text);
	}
	else
	{
		// out of memory: copy at least the report itself
		DebugCopyToClipboard(g_rva0088E000MessageText);
	}
}
