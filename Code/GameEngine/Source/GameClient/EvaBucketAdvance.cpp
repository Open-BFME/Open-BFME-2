// cl: /O1 /DNDEBUG /MD /EHsc
// ?advance@Rva000411084@@QAEPAXXZ, retail 0x003F7925 (47B).
// Shard TU: the EvaMessageName TU owns next/messageToName under the same
// flags, and defining the 47B advance there would capture next's out-of-line
// advance call site, so the advance lives here (same-TU visibility law).
// The bucket table shape {unused+0 begin+4 end+8} plus the node shape
// {next+0 name+4 key+8} are read off the rowed next/messageToName pins'
// archaeology notes; bucketIndex resolves via its ledger pin.

template <typename T>
class StringBase
{
public:
    void concat(const T *text);

private:
    friend class AsciiString;

    StringBase(const T *text);
    StringBase(const StringBase<T> &that);

    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};

// Inline throughout: retail reaches StringBase's private constructors directly
// from the caller rather than through a wrapper, which is what an inlined
// AsciiString constructor looks like.
class AsciiString
{
public:
    AsciiString(const char *text)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(text);
    }

    AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            (const StringBase<char> &)that);
    }

    ~AsciiString();

private:
    char *m_text;
};


class Rva000411084
{
public:
	void *next();
	void *advance();
	void *m_current;
	void *m_owner;
};

class Rva000427195
{
public:
	void *first(Rva000411084 *iter);
	int bucketIndex(const AsciiString *name);
	void *m_unused00;
	// The begin field reads twice with different scheduling: the count
	// computation folds it into a direct `sub ecx,[esi+4]` (single use, no
	// homing) while the loop re-fetches it every iteration (`mov
	// eax,[esi+4]` plus indexed `mov eax,[eax+edx*4]`), which also defeats
	// the strength reduction that turns the index into a bump pointer.
	// A single spelling serves only one side, so the union carries both:
	// the plain member for count, the volatile member for the loop.
	union {
		void **m_beginBuckets;
		void ** volatile m_beginBucketsVolatile;
	};
	void **m_endBuckets;
};

struct EvaMessageNameNode
{
	EvaMessageNameNode *m_next;
	AsciiString m_name;
	int m_message;
};

// ?advance@Rva000411084@@QAEPAXXZ
void *Rva000411084::advance()
{
	EvaMessageNameNode *node = (EvaMessageNameNode *)m_current;
	Rva000427195 *table = (Rva000427195 *)m_owner;
	unsigned index = (unsigned)table->bucketIndex(&node->m_name);
	unsigned count = (unsigned)(((char *)table->m_endBuckets - (char *)table->m_beginBuckets) >> 2);
	void *head = 0;
	do {
		++index;
		if (index >= count)
			break;
		head = table->m_beginBucketsVolatile[index];
	} while (head == 0);
	return head;
}
