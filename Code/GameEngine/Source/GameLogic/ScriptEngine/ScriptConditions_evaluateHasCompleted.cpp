// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ZH donor: GeneralsMD ScriptConditions.cpp evaluateVideoHasCompleted,
// evaluateSpeechHasCompleted and evaluateAudioHasCompleted. Target evidence:
// the evaluateCondition jump table (0x007EC5C0) sends cases 48, 49 and 50 to
// 0x003E41E3, 0x003E41FB and 0x003E4213, which initConditionTemplates names
// HAS_FINISHED_VIDEO, HAS_FINISHED_SPEECH and HAS_FINISHED_AUDIO. Each passes
// the parameter string and true to a ScriptEngine method called directly
// (0x00357A36, 0x00357F5E, 0x00358076: the ZH isVideoComplete,
// isSpeechComplete and isAudioComplete calls, address-named here because
// BFME2 calls them non-virtually). 0x003E41E3 was first rowed as the free
// Rva003E41E3Get; the dispatcher's case shows it is this member.
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
class ScriptEngine
{
public:
    bool rva00357A36(const AsciiString &completedVideo, bool removeFromList);
    bool rva00357F5E(const AsciiString &completedSpeech, bool removeFromList);
    bool rva00358076(const AsciiString &completedAudio, bool removeFromList);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool evaluateVideoHasCompleted(Parameter *);
    bool evaluateSpeechHasCompleted(Parameter *);
    bool evaluateAudioHasCompleted(Parameter *);
};
bool ScriptConditions::evaluateVideoHasCompleted(Parameter *pVideoParm)
{
    return TheScriptEngine->rva00357A36(pVideoParm->getString(), true);
}
bool ScriptConditions::evaluateSpeechHasCompleted(Parameter *pSpeechParm)
{
    return TheScriptEngine->rva00357F5E(pSpeechParm->getString(), true);
}
bool ScriptConditions::evaluateAudioHasCompleted(Parameter *pAudioParm)
{
    return TheScriptEngine->rva00358076(pAudioParm->getString(), true);
}
