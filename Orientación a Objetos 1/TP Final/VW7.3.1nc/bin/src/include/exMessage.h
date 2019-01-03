/* SccsId is @(#)exMessage.h	58.10 04/06/05 */
/************************************************************************
 * File: exMessage.h
 *
 * Provides facilities which permit C to send messages to Smalltalk
 * objects.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

/*
 * The following protocol is used by client code to send messages
 * or arbitrary Smalltalk objects.  Please consult the implementation
 * and the user's documentation for more details.
 *
 * The following protocol is exported from the ObjectEngine.
 * This should probably be re-organized.
 */
extern oop oeSendMessage0(oop, oop, oop *, oop);
extern oop oeSendMessage1(oop, oop, oop, oop *, oop);
extern oop oeSendMessage2(oop, oop, oop, oop, oop *, oop);
extern oop oeSendMessage3(oop, oop, oop, oop, oop, oop *, oop);
extern oop oeSendMessageMany(oop, oop, oop, oop *, oop);

extern oop oeCSendMessage0(oop, char *, oop *, oop);
extern oop oeCSendMessage1(oop, char *, oop, oop *, oop);
extern oop oeCSendMessage2(oop, char *, oop, oop, oop *, oop);
extern oop oeCSendMessage3(oop, char *, oop, oop, oop, oop *, oop);
extern oop oeCSendMessageMany(oop, char *, oop *, long, oop *, oop);

/*
 * The following protocol is obsolete -- use the oeSend...() versions
 * instead.
 */
extern oop UPSendMessage0(oop, oop, oop *, oop);
extern oop UPSendMessage1(oop, oop, oop, oop *, oop);
extern oop UPSendMessage2(oop, oop, oop, oop, oop *, oop);
extern oop UPSendMessage3(oop, oop, oop, oop, oop, oop *, oop);
extern oop UPSendMessageMany(oop, oop, oop, oop *, oop);

extern oop UPCSendMessageMany(oop, char *, oop *, long, oop *, oop);
extern oop UPCSendMessage0(oop, char *, oop *, oop);
extern oop UPCSendMessage1(oop, char *, oop, oop *, oop);
extern oop UPCSendMessage2(oop, char *, oop, oop, oop *, oop);
extern oop UPCSendMessage3(oop, char *, oop, oop, oop, oop *, oop);
extern oop UPCSendMessageMany(oop, char *, oop *, long, oop *, oop);


/* Synchronous (blocking) call-outs may call/send-back, allowing the garbage
 * collector to run and move objects.  This is specifically a problem for
 * the result object allocated before call-out to hold e.g. structure return
 * values.  We must arrange that the result object reference in the call-out
 * functions (primCallVarArgC et al) is updated if a call-back occurs.
 *
 * The above situation does not affect threaded call-outs since threaded call-
 * outs must always commit the primitive (build a frame for the primitive)
 * and can and must therefore save the result object in the committed primitive
 * frame.  Since the stack is garbage collected, the result object in the frame
 * is updated by the garbage collector.
 *
 * We would like to maintain the efficiency of not committing the call-out
 * unless we call-back.  So it is the call-back and return-from-callback
 * machinery's responsibility to commit the primitive and save and restore the
 * result to and from the committed frame.  The following variable is used by
 * the C callout machinery to reference the result object.  The call-back/
 * return-from-callback machinery updates this variable to point to the
 * (possibly) updated result object in the (possibly) committed frame.
 */

extern oop  calloutResult;
extern bool calloutIsLongComp;

/*
 * The following protocol is exported from this file, and is
 * used locally to the OE but is not exported to client code.
 *
 * This should probably be re-organized.
 */
extern void UPFailPrimitive(int);
extern int  UPFailPrimitiveAtLine(int);
extern oop  UPReturn(oop);

extern oopInt callbackSemaphoreX;
extern oopInt callbackClassX;
extern oopInt callbackSelectorX;
#ifdef NBAPI
extern oopInt nbCallbackSelectorX;
extern oopInt nbForeignCallbackProcessX;
#endif

/*
 * possiblyCommittedReturn
 *
 * When user C code invoked from the VI causes the invocation
 * primitive to commit because of a callback.  The procedures in
 * exCallC.c (primCallC, primCallCWith0) use this function to return.
 * This function checks the return value returns
 * using the correct return procedure.
 *
 * Note: Committed primitives are now handled by the normal primitive
 *       return macros and functions.
 *
 * Arguments:
 *
 * oReturnValue is the return value of the primitive.
 * oReceiver    is never really used, just a placeholder
 * numArgs      is the number of arguments passed to the primitive.
 * oErrorCode   is the error oop for failure.
 *
 * NOTE: "pr.h" must be included if this macro is used.
 */
#define possiblyCommittedReturn(oReturnValue, oReceiver, numArgs, oErrorCode) \
      if (oReturnValue == nonOop) {\
		 primFailReturnWith(oReceiver, numArgs, oErrorCode);\
      } else {\
		 longPrimReturn(oReturnValue);\
	  }
