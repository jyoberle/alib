*
*	$Id: amiga_hookentry.asm,v 1.3 2006-01-08 12:04:22 obarthel Exp $
*
*	:ts=8
*
*	Portable ISO 'C' (1994) runtime library for the Amiga computer
*	Copyright (c) 2002-2015 by Olaf Barthel <obarthel (at) gmx.net>
*	All rights reserved.
*
*	Redistribution and use in source and binary forms, with or without
*	modification, are permitted provided that the following conditions
*	are met:
*
*	  - Redistributions of source code must retain the above copyright
*	    notice, this list of conditions and the following disclaimer.
*
*	  - Neither the name of Olaf Barthel nor the names of contributors
*	    may be used to endorse or promote products derived from this
*	    software without specific prior written permission.
*
*	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*	ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
*	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*	POSSIBILITY OF SUCH DAMAGE.
*

	section	text,code

h_SubEntry equ 12

*	xdef	_HookEntry	modified by JOB
	xdef	HookEntry

*_HookEntry:	modified by JOB
HookEntry:

	move.l   a1,-(sp)
	move.l   a2,-(sp)
	move.l   a0,-(sp)
	move.l   h_SubEntry(a0),a0
	jsr      (a0)
	lea      12(sp),sp

	rts

	end
