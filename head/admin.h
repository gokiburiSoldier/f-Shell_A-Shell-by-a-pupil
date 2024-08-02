#ifndef _FS_ADM_HA
#define _FS_ADM_HA

#include <windows.h>

bool isAdministor(void) {
    SID_IDENTIFIER_AUTHORITY nta = SECURITY_NT_AUTHORITY;
    PSID adminGroup;
    BOOL Op = AllocateAndInitializeSid(
        &nta,
        2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0,0,0,0,0,0,
        &adminGroup
    );
    if(Op) {
        CheckTokenMembership(NULL,adminGroup,&Op);
        FreeSid(adminGroup);
    }
    return Op;
}

#endif