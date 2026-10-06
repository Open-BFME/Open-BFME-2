// cl: /DNDEBUG /MD /EHsc
// ?write@RAMFile@@UAEHPBXH@Z retail 0x00574473 6 bytes.
// Slot 4 (offset 0x10) of vtables 0x0087AA00 and 0x0087AA50; ZH donor
// GameEngine/Source/Common/System/RAMFile.cpp RAMFile::write returns -1.
// Evidence: direct callers push 2 args then call at 0x0042C108 and 0x005E592B
// plus jmp at 0x005753AF; cmp eax -1 in 0x005E5920 proves -1 sentinel.
class AsciiString;

class File
{
public:
	enum seekMode { START, CURRENT, END };

	virtual ~File();								// slot 0
	virtual bool open(const char *filename, int access = 0);	// slot 1
	virtual void close(void);						// slot 2
	virtual int read(void *buffer, int bytes);			// slot 3
	virtual int write(const void *buffer, int bytes);		// slot 4
	virtual int seek(int pos, seekMode mode);			// slot 5
	virtual void nextLine(char *buf, int bufSize);			// slot 6
	virtual bool scanInt(int &newInt);				// slot 7
	virtual bool scanReal(float &newReal);				// slot 8
	virtual bool scanString(AsciiString &newString);		// slot 9
	virtual bool print(const char *format, ...);			// slot 10
	virtual int size(void);						// slot 11
	virtual int position(void);					// slot 12
	virtual char *readEntireAndClose(void);				// slot 13
	virtual File *convertToRAMFile(void);				// slot 14
	virtual void lock(void);						// slot 15
	virtual void unlock(void);					// slot 16
};

class RAMFile : public File
{
public:
	virtual int write(const void *buffer, int bytes);
};

int RAMFile::write(const void *buffer, int bytes)
{
	return -1;
}
