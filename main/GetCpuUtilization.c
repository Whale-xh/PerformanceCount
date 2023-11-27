#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define count 3600  //3600 records per hour
 
typedef struct cpu_occupy_          //定义一个cpu occupy的结构体
{
    char name[20];                  //定义一个char类型的数组名name有20个元素
    unsigned int user;              //定义一个无符号的int类型的user
    unsigned int nice;              //定义一个无符号的int类型的nice
    unsigned int system;            //定义一个无符号的int类型的system
    unsigned int idle;              //定义一个无符号的int类型的idle
    unsigned int iowait;
    unsigned int irq;
    unsigned int softirq;
}cpu_occupy_t;
 
double cal_cpuoccupy (cpu_occupy_t *o, cpu_occupy_t *n)
{
    double od, nd;
    double id, sd;
    double cpu_use ;
 
    od = (double) (o->user + o->nice + o->system +o->idle+o->softirq+o->iowait+o->irq);//第一次(用户+优先级+系统+空闲)的时间再赋给od
    nd = (double) (n->user + n->nice + n->system +n->idle+n->softirq+n->iowait+n->irq);//第二次(用户+优先级+系统+空闲)的时间再赋给nd
 
    id = (double) (n->idle);    //用户第一次和第二次的时间之差再赋给id
    sd = (double) (o->idle) ;    //系统第一次和第二次的时间之差再赋给sd
    if((nd-od) != 0)
        cpu_use =100.0 - ((id-sd))/(nd-od)*100.00; //((用户+系统)乖100)除(第一次和第二次的时间差)再赋给g_cpu_used
    else 
        cpu_use = 0;
    return cpu_use;
}
 
void get_cpuoccupy (cpu_occupy_t *cpust,cpu_occupy_t *cpu1st,cpu_occupy_t *cpu2st,cpu_occupy_t *cpu3st,cpu_occupy_t *cpu4st)
{
    FILE *fd;
    int n;
    char buff[256],buff4[256],buff1[256],buff2[256],buff3[256];
    cpu_occupy_t *cpu_occupy,*cpu1_occupy,*cpu2_occupy,*cpu3_occupy,*cpu4_occupy;
    cpu_occupy=cpust;
    cpu1_occupy=cpu1st;
    cpu2_occupy=cpu2st;
    cpu3_occupy=cpu3st;
    cpu4_occupy=cpu4st;
 
    fd = fopen ("/proc/stat", "r");
    if(fd == NULL)
    {
            perror("fopen:");
            exit (0);
    }
    fgets (buff, sizeof(buff), fd);
    sscanf (buff, "%s %u %u %u %u %u %u %u", cpu_occupy->name, &cpu_occupy->user, &cpu_occupy->nice,&cpu_occupy->system, &cpu_occupy->idle ,&cpu_occupy->iowait,&cpu_occupy->irq,&cpu_occupy->softirq);
    
    fgets (buff1, sizeof(buff1), fd);
    sscanf (buff1, "%s %u %u %u %u %u %u %u", cpu1_occupy->name, &cpu1_occupy->user, &cpu1_occupy->nice,&cpu1_occupy->system, &cpu1_occupy->idle ,&cpu1_occupy->iowait,&cpu1_occupy->irq,&cpu1_occupy->softirq);
    
    fgets (buff2, sizeof(buff2), fd);
    sscanf (buff2, "%s %u %u %u %u %u %u %u", cpu2_occupy->name, &cpu2_occupy->user, &cpu2_occupy->nice,&cpu2_occupy->system, &cpu2_occupy->idle ,&cpu2_occupy->iowait,&cpu2_occupy->irq,&cpu2_occupy->softirq);
    
    fgets (buff3, sizeof(buff3), fd);
    sscanf (buff3, "%s %u %u %u %u %u %u %u", cpu3_occupy->name, &cpu3_occupy->user, &cpu3_occupy->nice,&cpu3_occupy->system, &cpu3_occupy->idle ,&cpu3_occupy->iowait,&cpu3_occupy->irq,&cpu3_occupy->softirq);
    
    fgets (buff4, sizeof(buff4), fd);
    sscanf (buff4, "%s %u %u %u %u %u %u %u", cpu4_occupy->name, &cpu4_occupy->user, &cpu4_occupy->nice,&cpu4_occupy->system, &cpu4_occupy->idle ,&cpu4_occupy->iowait,&cpu4_occupy->irq,&cpu4_occupy->softirq);

    fclose(fd);
}

double cpu,cpu1,cpu2,cpu3,cpu4;

double get_sysCpuUsage()
{
    cpu_occupy_t cpu_stat1,cpu1_stat1,cpu2_stat1,cpu3_stat1,cpu4_stat1;
    cpu_occupy_t cpu_stat2,cpu1_stat2,cpu2_stat2,cpu3_stat2,cpu4_stat2;

    get_cpuoccupy((cpu_occupy_t *)&cpu_stat1,(cpu_occupy_t *)&cpu1_stat1,(cpu_occupy_t *)&cpu2_stat1,(cpu_occupy_t *)&cpu3_stat1,(cpu_occupy_t *)&cpu4_stat1);
    //sleep(1);//sleep 1 s
    //第二次获取cpu使用情况
    get_cpuoccupy((cpu_occupy_t *)&cpu_stat2,(cpu_occupy_t *)&cpu1_stat2,(cpu_occupy_t *)&cpu2_stat2,(cpu_occupy_t *)&cpu3_stat2,(cpu_occupy_t *)&cpu4_stat2);

    //计算cpu使用率
    cpu = cal_cpuoccupy ((cpu_occupy_t *)&cpu_stat1, (cpu_occupy_t *)&cpu_stat2);
    cpu1 = cal_cpuoccupy ((cpu_occupy_t *)&cpu1_stat1, (cpu_occupy_t *)&cpu1_stat2);
    cpu2 = cal_cpuoccupy ((cpu_occupy_t *)&cpu2_stat1, (cpu_occupy_t *)&cpu2_stat2);
    cpu3 = cal_cpuoccupy ((cpu_occupy_t *)&cpu3_stat1, (cpu_occupy_t *)&cpu3_stat2);
    cpu4 = cal_cpuoccupy ((cpu_occupy_t *)&cpu4_stat1, (cpu_occupy_t *)&cpu4_stat2);
    return 0;
}
 

/*int main(int argc,char **argv)
{
    
    FILE *file=fopen("./CpuUtilization.csv","a+");
    for(int i=0;i<count;i++){
        get_sysCpuUsage();
        fprintf(file,"%.3f,%.3f,%.3f,%.3f,%.3f\n",cpu,cpu1,cpu2,cpu3,cpu4);
    }
    fclose(file);
    return 0;
}*/
