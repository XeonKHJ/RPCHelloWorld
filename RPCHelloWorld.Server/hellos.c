/* file: hellos.c */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "../RPCHelloWorld.Common/hello.h"
#include <windows.h>


void main()
{
    RPC_STATUS status;

    //以下必须用Unicode宽字符，不能直接用ANSI字符。不然会报RPC_S_PROTSEQ_NOT_SUPPORTED(1703)的错误。
    LPWSTR pszProtocolSequence = L"ncacn_np";
    LPWSTR pszSecurity = NULL;
    LPWSTR pszEndpoint = L"\\pipe\\hello";
    unsigned int    cMinCalls = 1;
    unsigned int    fDontWait = FALSE;

    status = RpcServerUseProtseqEp(pszProtocolSequence,
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,
        pszEndpoint,
        pszSecurity);

    if (status) exit(status);

    status = RpcServerRegisterIf(hello_v1_0_s_ifspec,
        NULL,
        NULL);

    if (status) exit(status);

    status = RpcServerListen(cMinCalls,
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,
        fDontWait);

    if (status) exit(status);
}

/******************************************************/
/*         MIDL allocate and free                     */
/******************************************************/

_Must_inspect_result_
_Ret_maybenull_ _Post_writable_byte_size_(size)
void* __RPC_USER MIDL_user_allocate(_In_ size_t size)
{
    return(malloc(size));
}

void __RPC_USER midl_user_free(_Pre_maybenull_ _Post_invalid_ void* ptr)
{
    free(ptr);
}