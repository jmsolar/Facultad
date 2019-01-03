# SccsId is @(#)mac.platPowerMac.make	58.10 04/06/05
#
# platPowerMac.make
#
# supplemental makefile included by makefile.vw7 that supplies PowerMac-specific definitions.
# N.B.  This scheme isn';t fully implemented yet; it only makes the PowerMac because there is
# only a PowerMac version of PLATOBJS in makefile.vw7.
# The real question is how to do conditional anything in a makefile.

# Application name
APPNAME= vwpmac
# PROCESSOR is the name of the target's processor.
PROCESSOR=procRS60x

# CC is the C compiler; SC (m68k) or MrC (PowerPC)
# ASM is the assembler; asm (m68k) or PPCAsm (PowerPC)
# LINK is the linker; Link or PPCLink
CC=MrC
ASM=PPCAsm
LINK=PPCLink
LIBRARIAN=PPCLink
RC=Rez

# Compilation Flags
# MrC warnings we suppress:
#  2 :: possible unintended assignment
#  6 :: value of expression not used
#  7 :: possible extraneous ';'
# 23 :: -enum int overrides setting done by -ansi off | on | relaxed
# 35 :: parameter not used
# We *cannot* use -ansi strict because doing so causes MrC to ignore -alloca and not
# recognise alloca as a builtin.  So we use -ansi on, but could use e.g. -ansi relaxed.
SUPPRESSED_WARNINGS=-w 2,6,7,23,35
CCFLAGS= {SUPPRESSED_WARNINGS} -alloca -ansi on -enum int -ieee strict
ASMFLAGS=-case on -sym on -typecheck on
ASMPREFLAGS=-D _LONG_LONG # Need to provide this to .m since MrC defines it

# Subsystem Link flags
LIBOPTS=-mf -sym big -xm library

# Main system link flags
LINKOPT=-mf -sym big

Libs=	"{SharedLibraries}"InterfaceLib		¶
		"{SharedLibraries}"StdCLib_3.5		¶
		"{PPCLibraries}"StdCRuntime.o		¶
		"{PPCLibraries}"PPCCRuntime.o		¶
		"{PPCLibraries}"CarbonAccessors.o	¶
		"{SharedLibraries}"MathLib
