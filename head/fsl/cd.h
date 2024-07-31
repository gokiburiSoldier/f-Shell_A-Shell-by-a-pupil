#ifndef _FSL_CD
#define _FSL_CD

#include <string>
#include <stdlib.h>
#include <io.h>

namespace cd {
    bool exist_floder(std::string adr) {
        return 1+access((adr+"\\").c_str(),0);
    }
} 


#endif