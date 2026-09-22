// cl: /DNDEBUG /MD /EHs-c-
//
// Debug::GetOutputBuffer, retail 0x000392A0 (19 bytes, ret 4). The
// exception filter (0x0003DCD0) asks it for the text of the exception it
// just logged, passing the Exception string type (3). Retail never reads
// that argument: the buffer comes from ioBuffer[curType], and curType is
// Exception at that point anyway. The name is descriptive.

struct DebugIOInterface
{
	enum StringType { Assert, Check, Crash, Exception = 3 };
};

class Debug
{
public:
	const char *GetOutputBuffer(DebugIOInterface::StringType type) const;

private:
	struct IOBuffer
	{
		char *buffer;
		unsigned int used;
		unsigned int alloc;
		bool lastWasCR;
	};

	unsigned char m_pad00[0x9C84];
	IOBuffer ioBuffer[7];                // +0x9C84
	int curType;                         // +0x9CF4
};

// ?GetOutputBuffer@Debug@@QBEPBDW4StringType@DebugIOInterface@@@Z
const char *Debug::GetOutputBuffer(DebugIOInterface::StringType) const
{
	return ioBuffer[curType].buffer;
}
