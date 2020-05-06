#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "log.h"

static int g_single_proc_inst_lock_fd = -1;

void CLog::LogOut(const char *fmt, ...)
{
    char logstr[512];

    time_t timep;
    time(&timep);
    struct tm *p = localtime(&timep); /*取得当地时间*/
    sprintf(logstr,"[%d/%d/%d %d:%d:%d] ",(1900+p->tm_year),(1+p->tm_mon), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);

    va_list args;
    va_start(args,fmt);
    vsnprintf(logstr+strlen(logstr), 512, fmt, args);
    va_end(args);

    if(m_fd != -1)
    {
        write(m_fd,logstr,strlen(logstr));
    }
    else
    {
        printf("%s", logstr);
    }
}

bool CLog::Init(const char* file, bool bLog)
{
    struct stat statbuf;

    stat(file, &statbuf);

    if(statbuf.st_size > 3145728)//3*1024*1024=3MB
    {
        remove(file);
    }

    if(bLog)
    {
        m_fd = open(file, O_WRONLY|O_CREAT|O_APPEND,0644);

        return ((m_fd==-1)?(false):(true));
    }
    else
    {
        m_fd = -1;
    }
    memset(proc_path, 0, PATH_MAX);

    return 1;
}

void CLog::Deinit()
{
    if(m_fd != -1)
        close(m_fd);

    m_fd = -1;
}

const char* CLog::GetConfigPath(const char* configfile)
{
    if(proc_path[0] != 0)
    {
        return proc_path;
    }
    char proc_name[PATH_MAX];

    get_executable_path(proc_path, proc_name, PATH_MAX);
	
	snprintf(proc_name,PATH_MAX,"%s%s",proc_path, configfile);

    stpcpy(proc_path, proc_name);
	
    return proc_path;
}

void CLog::single_proc_inst_lockfile_cleanup(void)
{
    if (g_single_proc_inst_lock_fd != -1)
    {
        close(g_single_proc_inst_lock_fd);

        g_single_proc_inst_lock_fd = -1;
    }
}

size_t CLog::get_executable_path( char* processdir,char* processname, size_t len)
{
    char* path_end;
    if(readlink("/proc/self/exe", processdir,len) <=0)
        return -1;

    path_end = strrchr(processdir,  '/');
    if(path_end == NULL)
        return -1;

    ++path_end;
    strcpy(processname, path_end);
    *path_end = '\0';

    return (size_t)(path_end - processdir);
}

bool CLog::Is_single_proc_inst_running()
{
    char proc_name[PATH_MAX];

    get_executable_path(proc_path,proc_name,PATH_MAX);

    char lock_file[128];

    snprintf(lock_file, sizeof(lock_file), "/var/tmp/%s.lock", proc_name);

    g_single_proc_inst_lock_fd = open(lock_file, O_CREAT|O_RDWR, 0644);

    bool bret;

    if (-1 == g_single_proc_inst_lock_fd)
    {
        printf("Fail to open lock file(%s)", lock_file);

        bret = false;

        goto __RET__;
    }

    if (0 == flock(g_single_proc_inst_lock_fd, LOCK_EX | LOCK_NB))
    {
        atexit(single_proc_inst_lockfile_cleanup);

        bret = false;

        goto __RET__;
    }

    close(g_single_proc_inst_lock_fd);

    g_single_proc_inst_lock_fd = -1;

    //printf("%s is already running.\n",proc_name);

    return true;

__RET__:
    snprintf(proc_name,PATH_MAX,"%saudioconfig.xml",proc_path);

    stpcpy(proc_path,proc_name);

    //printf("%s\n",proc_path);

    return bret;
}
