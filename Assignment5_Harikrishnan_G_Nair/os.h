/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _OS_H_RPCGEN
#define _OS_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define COMM 0x20000001
#define COMMVERSION 1

#if defined(__STDC__) || defined(__cplusplus)
#define COMMRPC 1
extern  int * commrpc_1(char **, CLIENT *);
extern  int * commrpc_1_svc(char **, struct svc_req *);
extern int comm_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define COMMRPC 1
extern  int * commrpc_1();
extern  int * commrpc_1_svc();
extern int comm_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_OS_H_RPCGEN */