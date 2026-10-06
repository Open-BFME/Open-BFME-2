// ?evaluateNamedOutsideArea@ScriptConditions@@IAE_NPAVParameter@@0@Z
// Target evidence: template 14 is NAMED_OUTSIDE_AREA. Retail boundary
// 0x003E66D5 calls the pinned inside-area handler at 0x003E5EFF and negates
// its Boolean result. The BFME1 donor implements the same outside-area rule.
// cl: /DNDEBUG /MD /EHsc
class Parameter;
class ScriptConditions
{
protected:
    __declspec(noinline) bool evaluateNamedInsideArea(Parameter *, Parameter *);
    bool evaluateNamedOutsideArea(Parameter *, Parameter *);
};

bool ScriptConditions::evaluateNamedOutsideArea(
    Parameter *unit, Parameter *trigger)
{
    return !evaluateNamedInsideArea(unit, trigger);
}
