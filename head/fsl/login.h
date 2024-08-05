// "sql204.infinityfree.com","if0_36616180","1r0ncunrvbwY","if0_36616180_users"
#ifndef _FSL_LOGIN_H
#define _FSL_LOGIN_H

#include "../../mysql/mysql.h"

namespace lgn {
    MYSQL mysql;
    int connect(void) {
        mysql_init(&mysql);
        if(mysql_real_connect(&mysql,"sql204.infinityfree.com","if0_36616180","1r0ncunrvbwY","if0_36616180_users",3306,0,0))
            return 0;
        return -1;
    }
}


#endif