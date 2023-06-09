#include <proto/exec.h>
#include "l_alib.h"

APTR LibCreatePool(ULONG memFlags,ULONG puddleSize,ULONG threshSize)
{
    struct ExecBase *SysBase = *((struct ExecBase**)4UL);

    if(((struct Library *)SysBase)->lib_Version < MIN_EXEC_VERSION)
        return(NULL);

    // DEBUG_JOB : voir l'utilisation de malloc pour les versions inferieures

    return(CreatePool(memFlags,puddleSize,threshSize));
}