// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native005D2575..005D258E is the seven-word manager constructor allocated
// as1C bytes by W3DShadowManager9A710 and stored at nativeVA DEC2CC.
// WB8E1840 independently shows the seven zero stores. Original class name
// remains unknown. The former TimeCodedMotionChannelClass gen-alias also
// names a separate body195CE0; that is not this constructor's identity.
class Rva005D2575
{
public:
    Rva005D2575();
private:
    unsigned m_words[7];
};
Rva005D2575::Rva005D2575()
{
    m_words[0]=0;m_words[1]=0;m_words[2]=0;m_words[3]=0;
    m_words[4]=0;m_words[5]=0;m_words[6]=0;
}
