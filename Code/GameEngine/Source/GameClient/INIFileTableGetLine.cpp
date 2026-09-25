// cl: /O1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
struct INIFileRecord
{
    unsigned int fileId;
    int line;
    unsigned int flags;
};

class INIFileTable
{
public:
    int getLine(int fileIndex) const;

private:
    unsigned int m_reserved;
    INIFileRecord *m_begin;
    INIFileRecord *m_end;
};

int INIFileTable::getLine(int fileIndex) const
{
    int count = ((int)m_end - (int)m_begin) / (int)sizeof(INIFileRecord);
    if (fileIndex < count)
        return (*(INIFileRecord * volatile *)&m_begin)[fileIndex].line;
    return 0;
}
