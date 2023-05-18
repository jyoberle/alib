// VSCode's IntelliSense doesn't know about 68000 registers, so suppress warnings
#ifndef __INTELLISENSE__
    #define ASM __asm
#else
    #define ASM(...)
#endif

#include <exec/types.h>
#include <proto/exec.h>
#include <exec/tasks.h>
#include <proto/intuition.h>
#include <proto/commodities.h>
#include <proto/dos.h>
#include <proto/rexxsyslib.h>
#include <proto/utility.h>
#include <proto/icon.h>
#include <graphics/gfxbase.h>
#include <devices/timer.h>
#include <devices/input.h>
#include <dos/dostags.h>
#define FLOAT ULONG
#include <clib/alib_protos.h>
#include <string.h>

extern WORD testHookBoopsiFunctions(void);
extern WORD testFFP(void);
extern WORD testExecSupportFunctions(void);
extern WORD testRandomFunctions(void);
extern WORD testGraphicSupportFunctions(void);
extern WORD testTimerSupportFunctions(void);
extern WORD testCommoditiesFunctions(void);
extern WORD testArexxFunctions(void);
extern WORD testACryptFunction(void);
extern WORD testMulDivFunctions(void);

struct ExecBase *SysBase;
struct IntuitionBase *IntuitionBase = NULL;
struct DosLibrary *DOSBase = NULL;
struct UtilityBase *UtilityBase = NULL;
struct GfxBase *GfxBase = NULL;
struct Library *CxBase = NULL;
struct Library *IconBase = NULL;

// Does the clean up of all ressources
void cleanUP(void)
{
	if(IntuitionBase != NULL)
		CloseLibrary((struct Library *)IntuitionBase);

	if(DOSBase != NULL)
		CloseLibrary((struct Library *)DOSBase);

	if(UtilityBase != NULL)
		CloseLibrary((struct Library *)UtilityBase);

	if(GfxBase != NULL)
		CloseLibrary((struct Library *)GfxBase);

	if(CxBase != NULL)
		CloseLibrary(CxBase);

	if(IconBase != NULL)
		CloseLibrary(IconBase);
}

// Entry of our code
int main(int argc, char **argv) 
{
	SysBase = *((struct ExecBase**)4UL);
	struct Process *proc;
	struct WBStartup *wbmsg = NULL;
	WORD i;

	// We check if our program has been started by the workbench or by the shell
	if (argc == 0) {
		// We have been launched by workbench: we wait for the startup message
		proc = (struct Process *)FindTask(NULL);
		WaitPort(&proc->pr_MsgPort);
		wbmsg = (struct WBStartup *)GetMsg(&proc->pr_MsgPort);
	}

	// We open the required libraries
	// The utility library is used in the aminlib.c file (call of CallHookPkt function)
	IntuitionBase = (struct IntuitionBase *)OpenLibrary((CONST_STRPTR)"intuition.library",0L);
	DOSBase = (struct DosLibrary *)OpenLibrary((CONST_STRPTR)"dos.library",0L);
	UtilityBase = (struct UtilityBase *)OpenLibrary((CONST_STRPTR)"utility.library",0L);
	GfxBase = (struct GfxBase *)OpenLibrary("graphics.library",0);
	CxBase = OpenLibrary("commodities.library",0);
	IconBase = OpenLibrary("icon.library",0);

	if(IntuitionBase && DOSBase && UtilityBase && GfxBase && CxBase && IconBase)
	{
		Printf("Testing alib...\n");
		Printf("Fast floating point functions %s\n",(long unsigned int)((testFFP()==0)?"OK":"FAIL"));
		Printf("Exec support functions %s\n",(long unsigned int)((testExecSupportFunctions()==0)?"OK":"FAIL"));
		Printf("Random functions %s\n",(long unsigned int)((testRandomFunctions()==0)?"OK":"FAIL"));
		Printf("Graphic support functions %s\n",(long unsigned int)((testGraphicSupportFunctions()==0)?"OK":"FAIL"));
		Printf("Timer support functions %s\n",(long unsigned int)((testTimerSupportFunctions()==0)?"OK":"FAIL"));
		Printf("Commodities support functions %s\n",(long unsigned int)((testCommoditiesFunctions()==0)?"OK":"FAIL"));
		Printf("Arexx support functions %s\n",(long unsigned int)((testArexxFunctions()==0)?"OK":"FAIL"));
		Printf("ACrypt function %s\n",(long unsigned int)((testACryptFunction()==0)?"OK":"FAIL"));
		Printf("Hook and boopsi support functions %s\n",(long unsigned int)((testHookBoopsiFunctions()==0)?"OK":"FAIL"));
		Printf("Multiplication and division functions %s\n",(long unsigned int)((testMulDivFunctions()==0)?"OK":"FAIL"));
	}

	// Before leaving, we close all libraries
	cleanUP();

	if(wbmsg != NULL)
	{
		// If needed, we reply to the workbench message
		Forbid();
		ReplyMsg((struct Message *)wbmsg);
	}
}

__attribute__((used)) __attribute__((section(".text.unlikely"))) void _start(int argc, char **argv)
{
	main(argc,argv);
}