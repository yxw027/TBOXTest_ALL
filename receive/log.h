#ifndef AUDIO_LOG_H
#define AUDIO_LOG_H

#include <linux/limits.h>
#include <stdlib.h>
#include "singletonbase.h"

class CLog
{
    REGISTER_SINGLETON(CLog)

private:
    char proc_path[PATH_MAX];
    int  m_fd;
    static void single_proc_inst_lockfile_cleanup(void);
    size_t get_executable_path( char* processdir,char* processname, size_t len);

public:
    bool Init(const char* file, bool bLog = true);
    void Deinit();
    void LogOut(const char* fmt, ...);
    bool Is_single_proc_inst_running();
    const char* GetConfigPath(const char*);
};

#ifndef OUTPUT
#define OUTPUT 0
#endif

#define LOGMSG(cond,print_exp)    \
    ((cond)?(GET_SINGLETON_INSTANCE(CLog)->LogOut print_exp),1:0)


#endif
