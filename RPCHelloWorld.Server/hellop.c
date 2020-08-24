#include "../RPCHelloWorld.Common/hello.h"
#include <stdio.h>

/* add this function to hellop.c */
void Shutdown(void)
{
    RPC_STATUS status;

    status = RpcMgmtStopServerListening(NULL);

    if (status)
    {
        exit(status);
    }

    status = RpcServerUnregisterIf(NULL, NULL, FALSE);

    if (status)
    {
        exit(status);
    }
} //end Shutdown


void HelloProc(unsigned char* psz)
{
    printf(psz);
}