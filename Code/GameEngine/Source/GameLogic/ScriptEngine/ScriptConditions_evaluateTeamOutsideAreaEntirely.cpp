// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ScriptConditions::evaluateTeamOutsideAreaEntirely @0x003E674C 56B.
// ZH donor body: neither entirely nor partially inside. Calls the matched
// evaluateTeamInsideAreaEntirely 0x003E66EA and
// evaluateTeamInsideAreaPartially 0x003E5E7D on the same this.
class Parameter;
class ScriptConditions
{
protected:
    bool evaluateTeamInsideAreaEntirely(Parameter *, Parameter *, Parameter *);
    bool evaluateTeamInsideAreaPartially(Parameter *, Parameter *, Parameter *);
    bool evaluateTeamOutsideAreaEntirely(Parameter *, Parameter *, Parameter *);
};
bool ScriptConditions::evaluateTeamOutsideAreaEntirely(Parameter *teamParm, Parameter *triggerParm, Parameter *typeParm)
{
    return !(evaluateTeamInsideAreaEntirely(teamParm, triggerParm, typeParm) ||
             evaluateTeamInsideAreaPartially(teamParm, triggerParm, typeParm));
}
