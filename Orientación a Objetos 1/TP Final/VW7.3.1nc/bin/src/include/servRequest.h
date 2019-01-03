/* SccsId is  @(#)servRequest.h	58.10 04/06/05 */
/***************************************************************************
 * File: servRequest.h
 *
 * Definitions for posting, un-posting and checking service requests.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 **************************************************************************/

#ifndef SERVREQUEST_INC
#define SERVREQUEST_INC

#ifndef POLLCOUNT
#define POLLCOUNT 2500
#endif

extern DLUP_IMPORT(int)		interruptPollCount;
extern DLUP_IMPORT(int *)	interruptPoll;

/*
 * anyReq and anyAck are read-only exports from stack/services.c
 * that should only be used via the anyRequest macro.
 */
extern DLUP_IMPORT(volatile int) anyReq;
extern DLUP_IMPORT(volatile int) anyAck;
/* Answer if there are any requests. */
#define anyRequests() (anyReq != anyAck)

/* cookie is either a platform-dependent context descriptor which
 * contains sufficient information to determine the pc of the
 * OE thread, or one of the following values:
 *
 *      (void *)0   an internal call from the OE thread
 *      (void *)1   an internal call from some signal handler
 *      (void *)2   an internal call from some thread other than the OE.
 * needMessageToWakeup is to be set to true whenever OE thread blocks
 * for input (e.g. via poll on unix or WaitMessage on Windows).  It is
 * used by pdWakeup to determine if action must be taken to get the OE
 * out of its blocking wait, e.g. like delivering a wakeup message.
 */
extern DLUP_IMPORT(volatile bool) needMessageToWakeup;
#define ASR_OE_THREAD ((void *)0)
#define ASR_FROM_SIGNAL ((void *)1)
#define ASR_FROM_THREAD ((void *)2)
#define MAX_ASR ASR_FROM_THREAD
extern void asyncSetRequest(unsigned int, void *, bool);
extern void setRequest(unsigned int);
extern void clearRequest(unsigned int);

extern bool anyAsyncRequests(void);
extern void handleRequests(void);
extern void handleAsyncRequests(void);
extern bool isRequested(unsigned int);

extern bool couldBeCodeAllowedAsNPC(machinePC);

/*
 * Event request codes.  These are divided into asynchronous requests and
 * synchronous requests.  Asynchronous requests are those that arise from
 * some source external to Smalltalk asynchronously with Smalltalk execution.
 * These are events like input becomming available or a timer expiring.
 * Synchronous requests are those that arise during Smalltalk execution itself
 * such as a scavenge or a process switch being required.  The distinction is
 * important because the incremental collector in interruptible mode terminates
 * if an asynchronous event occurs, but it ignores synchronous events.
 */
#define MaxRequests (MaxAsyncRequests+4)
#define RescheduleRequest (MaxAsyncRequests+3)
#define LowSpaceRequest (MaxAsyncRequests+2)
#define CompactLargeSpaceRequest (MaxAsyncRequests+1)
#define ScavengeRequest MaxAsyncRequests

#if SIGNALSemaphores
# define MaxAsyncRequests 7
# define SIGNALRequest 6
#else
# define MaxAsyncRequests 6
#endif
#define NBAPIServiceRequest 5
#define ChildDeathRequest 4
#define UserRequest 3
#define TimerRequest 2
#define SensorRequest 1
/* IORequest and InterruptRequest are equivalent; both cause pdSynchronizeInput
 * to be called. SensorRequest is almost equivalent, but is retracted by
 * ntwin.c's pdSynchronizeInput so we retain it for now.
 */
#define IORequest 0
#define InterruptRequest 0

/*
 * Specific response routines.
 */
extern void compactLargeSpaceResponse(void);
extern void lowSpaceResponse(void);
extern void processSwitch(void);
extern void timeExpired(void);
#if SIGNALSemaphores
extern bool  registerSignal(int);
# if defined(SIGALRM)
extern void signalSIGNALSemaphores(sigset_t *);
# endif
#endif

#endif /* SERVREQUEST_INC */
