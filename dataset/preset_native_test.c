/***************************************Preset events test*******************************************/
 #include <papi.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <time.h>
 #include <sys/timeb.h>
 #include <stdio.h>  
 #include <unistd.h>  
 #include <fcntl.h>  
 #include <sys/types.h>  
 #include <sys/stat.h> 
 #include <pthread.h>

#define TIMEB timeb
typedef long long TIME_T;

#define num_samples 36000
#define num_events 37
#define num_temperature 10

 void handle_error (int retval)
{
     printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
     exit(1);
}

	long long values[num_samples][num_events]; 
	int temperature[num_samples][num_temperature]; 
    
    
int real_wrapper(){
     int EventSet=PAPI_NULL,retval;
     int i_pre,i,counter_sample;

    FILE *file_w=NULL,*file_r=NULL;
	int interval,sleep_time=100;//单位ms

	struct TIMEB ts1,ts2;
    TIME_T t1,t2;
    int ti;
    
	int fd;
	char  buf[12];
	char *temp[num_temperature]={"/sys/class/hwmon/hwmon2/temp1_input",
				"/sys/class/hwmon/hwmon2/temp2_input",
			   "/sys/class/hwmon/hwmon2/temp3_input",
			   "/sys/class/hwmon/hwmon2/temp4_input", 
			   "/sys/class/hwmon/hwmon2/temp5_input",
			   "/sys/class/hwmon/hwmon0/temp1_input",
			   "/sys/class/hwmon/hwmon0/temp2_input",
			   "/sys/class/hwmon/hwmon1/temp1_input",
			   "/sys/class/hwmon/hwmon1/temp2_input",
			   "/sys/class/hwmon/hwmon1/temp3_input"};
	ssize_t numwrite;

	if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
    if (retval != PAPI_OK) handle_error(retval);

	PAPI_create_eventset(&EventSet);
	
	
	/*int set[108]={PAPI_L1_DCM,PAPI_L1_ICM,PAPI_L2_DCM,PAPI_L2_ICM,PAPI_L3_DCM,PAPI_L3_ICM,PAPI_L1_TCM,PAPI_L2_TCM,PAPI_L3_TCM
	,PAPI_CA_SNP,PAPI_CA_SHR,PAPI_CA_CLN,PAPI_CA_INV,PAPI_CA_ITV,PAPI_L3_LDM,PAPI_L3_STM,PAPI_BRU_IDL,PAPI_FXU_IDL
	,PAPI_FPU_IDL,PAPI_LSU_IDL,PAPI_TLB_DM,PAPI_TLB_IM,PAPI_TLB_TL,PAPI_L1_LDM,PAPI_L1_STM,PAPI_L2_LDM,PAPI_L2_STM
	,PAPI_BTAC_M,PAPI_PRF_DM,PAPI_L3_DCH,PAPI_TLB_SD,PAPI_CSR_FAL,PAPI_CSR_SUC,PAPI_CSR_TOT,PAPI_MEM_SCY,PAPI_MEM_RCY
	,PAPI_MEM_WCY,PAPI_STL_ICY,PAPI_FUL_ICY,PAPI_STL_CCY,PAPI_FUL_CCY,PAPI_HW_INT,PAPI_BR_UCN,PAPI_BR_CN,PAPI_BR_TKN
	,PAPI_BR_NTK,PAPI_BR_MSP,PAPI_BR_PRC,PAPI_FMA_INS,PAPI_TOT_IIS,PAPI_TOT_INS,PAPI_INT_INS,PAPI_FP_INS,PAPI_LD_INS
	,PAPI_SR_INS,PAPI_BR_INS,PAPI_VEC_INS,PAPI_RES_STL,PAPI_FP_STAL,PAPI_TOT_CYC,PAPI_LST_INS,PAPI_SYC_INS,PAPI_L1_DCH
	,PAPI_L2_DCH,PAPI_L1_DCA,PAPI_L2_DCA,PAPI_L3_DCA,PAPI_L1_DCR,PAPI_L2_DCR,PAPI_L3_DCR,PAPI_L1_DCW,PAPI_L2_DCW
	,PAPI_L3_DCW,PAPI_L1_ICH,PAPI_L2_ICH,PAPI_L3_ICH,PAPI_L1_ICA,PAPI_L2_ICA,PAPI_L3_ICA,PAPI_L1_ICR,PAPI_L2_ICR
	,PAPI_L3_ICR,PAPI_L1_ICW,PAPI_L2_ICW,PAPI_L3_ICW,PAPI_L1_TCH,PAPI_L2_TCH,PAPI_L3_TCH,PAPI_L1_TCA,PAPI_L2_TCA
	,PAPI_L3_TCA,PAPI_L1_TCR,PAPI_L2_TCR,PAPI_L3_TCR,PAPI_L1_TCW,PAPI_L2_TCW,PAPI_L3_TCW,PAPI_FML_INS,PAPI_FAD_INS
	,PAPI_FDV_INS,PAPI_FSQ_INS,PAPI_FNV_INS,PAPI_FP_OPS,PAPI_SP_OPS,PAPI_DP_OPS,PAPI_VEC_SP,PAPI_VEC_DP,PAPI_REF_CYC
	};*/

	//add preset event to Event Set
	int set[17]={PAPI_L1_DCM,PAPI_L1_ICM,PAPI_L2_DCM,PAPI_L2_ICM,PAPI_L1_TCM,
	PAPI_L2_TCM,PAPI_L3_TCM,PAPI_CA_SNP,PAPI_CA_SHR,PAPI_CA_CLN,PAPI_TOT_INS,
	PAPI_L3_DCA,PAPI_L2_ICA,PAPI_L3_ICA,PAPI_L2_ICR,PAPI_L3_ICR,PAPI_L3_TCA};

    for(i=0;i<17;i++){
     	retval=PAPI_add_event(EventSet, set[i]);
     	if (retval != PAPI_OK) handle_error(retval);
	}

	//add native event to Event Set
	FILE *file_native=NULL;
	char native_event[100];
	file_native=fopen("native_event.txt","r");
	if (file_native == NULL)
    {
        printf("Error! opening file\n");
        exit(1);         
    }
	while (!feof(file_native))
    {
        fscanf(file_native,"%s\n",native_event);
        retval=PAPI_add_named_event(EventSet,native_event);
        if(retval!=PAPI_OK) {
            handle_error(retval);
        }
    }
	fclose(file_native);

	/*int num;
	num=PAPI_num_events(EventSet);
	printf("%d\n",num);*/

	//start count
	retval=PAPI_start(EventSet);
	for(counter_sample=0,ftime(&ts1);counter_sample<num_samples;counter_sample++){
		PAPI_read(EventSet,&values[counter_sample]);
		
		//read temperature
		for(i=0;i<num_temperature;i++){
			fd=open(temp[i],O_RDONLY);
			if (fd != -1)
         	{
				numwrite = read(fd, buf, 12);
				if (numwrite < 1)
				{
					close(fd);
					printf(" TempWatcher::get_cpu_temperature: read temperature error, can not read the file\n");
					exit(1);
				}
				close(fd);
				sscanf(buf, "%d", &temperature[counter_sample][i]);
         	}
		}
		ftime(&ts2);//stop time
		t1=(TIME_T)ts1.time*1000+ts1.millitm;
		t2=(TIME_T)ts2.time*1000+ts2.millitm;
		ti=t2-t1;//获取时间间隔，ms为单位的
		if(ti<sleep_time){
			usleep((sleep_time-ti)*1000);
			printf("interval %dms,sleep %dus\n",ti,(sleep_time-ti)*1000);
			ftime(&ts1);
		}
		else ftime(&ts1);
		PAPI_reset(EventSet);
	}
	PAPI_cleanup_eventset(EventSet);
	PAPI_destroy_eventset(&EventSet);
	PAPI_shutdown();
	
	//write data to file
	file_w=fopen("./EventRecord.csv","w+"); //event record
	FILE *file_temp=NULL;
	file_temp=fopen("./TemperatureRecord.csv","w+");//temperature record
	for(counter_sample=0;counter_sample<num_samples;counter_sample++){
		for(i_pre=0;i_pre<num_events;i_pre++){
			if(i_pre!=num_events-1)
				fprintf(file_w,"%lld,",values[counter_sample][i_pre]);
			else
				fprintf(file_w,"%lld\n",values[counter_sample][i_pre]);
			
			//write temperature to file
			if(i_pre==num_events-1){
				i=0;
				while(i<num_temperature){
					if(i==num_temperature-1)
						fprintf(file_temp,"%d\n",temperature[counter_sample][i]);
					else
						fprintf(file_temp,"%d,",temperature[counter_sample][i]);
					i++;
				}
			}
		}
	}
	fclose(file_w);
	fclose(file_temp);

    return 0;   
    
}


///The runnable thread points to this static function. This function recieves a Thread object, and calls the wrapper function in that object
void static_wrapper()
{

   real_wrapper();
   pthread_exit(NULL);
 
}


 int main(){
   ///The actual pthread variable
   pthread_t thread;

   ///Auxiliary variable to set the thread's attributes
   pthread_attr_t thread_attr;

   ///Auxiliary variable to the set the thread's parameters
   struct sched_param thread_param;
   
      ///This is an auxiliary variable to set the thread's priority
   int policy;
   
      pthread_attr_init(&thread_attr);

   //creating the pthread
   if (pthread_create(&thread, &thread_attr, static_wrapper, NULL))
   {
      printf("Error creating thread\n");
      exit(-1);
   }

   //Setting its priorityy
   int priority = 8;
   pthread_getschedparam(thread, &policy, &thread_param);
   thread_param.sched_priority = priority;
   pthread_setschedparam(thread, SCHED_FIFO, &thread_param);
   
   // join the thread;
   pthread_join(thread, NULL);
   
   return 0;
 }
