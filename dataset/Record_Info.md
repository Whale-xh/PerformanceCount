
# Data description 

## In the EventRecord.csv file, the events from left to right are:
### preset event
                    Description (Note)
    PAPI_L1_DCM    : Level 1 data cache misses
    PAPI_L1_ICM    : Level 1 instruction cache misses
    PAPI_L2_DCM    : Level 2 data cache misses
    PAPI_L2_ICM    : Level 2 instruction cache misses
    PAPI_L1_TCM    : Level 1 cache misses
    PAPI_L2_TCM    : Level 2 cache misses
    PAPI_L3_TCM    : Level 3 cache misses
    PAPI_CA_SNP    : Requests for a snoop
    PAPI_CA_SHR    : Requests for exclusive access to shared cache line
    PAPI_CA_CLN    : Requests for exclusive access to clean cache line
    PAPI_TOT_INS   : Total instructions executed
    PAPI_L3_DCA    : Level 3 data cache accesses
    PAPI_L2_ICA    : Level 2 instruction cache accesses
    PAPI_L3_ICA    : Level 3 instruction cache accesses
    PAPI_L2_ICR    : Level 2 instruction cache reads
    PAPI_L3_ICR    : Level 3 instruction cache reads
    PAPI_L3_TCA    : Level 3 total cache accesses


### native event

```markdown
Native Events in Component: perf_event                                           
                                              Description (Note)
perf::PERF_COUNT_HW_REF_CPU_CYCLES       : Total cycles; not affected by CPU frequency scaling.
perf::PERF_COUNT_SW_CPU_CLOCK            : This reports the CPU clock, a high-resolution per-CPU timer.
perf::CPU-CLOCK                          : PERF_COUNT_SW_CPU_CLOCK
perf::PERF_COUNT_SW_TASK_CLOCK           : This reports a clock count specific to the task that is running
perf::TASK-CLOCK                         : PERF_COUNT_SW_TASK_CLOCK
perf::PERF_COUNT_SW_PAGE_FAULTS          : This reports the number of page faults.
perf::PAGE-FAULTS                        : PERF_COUNT_SW_PAGE_FAULTS
perf::FAULTS                             : PERF_COUNT_SW_PAGE_FAULTS
perf::PERF_COUNT_SW_CONTEXT_SWITCHES     : This counts context switches.
perf::CONTEXT-SWITCHES                   : PERF_COUNT_SW_CONTEXT_SWITCHES
perf::CS                                 : PERF_COUNT_SW_CONTEXT_SWITCHES
perf::PERF_COUNT_SW_CPU_MIGRATIONS       : This reports the number of times the process has migrated to a new CPU.
perf::CPU-MIGRATIONS                     : PERF_COUNT_SW_CPU_MIGRATIONS
perf::MIGRATIONS                         : PERF_COUNT_SW_CPU_MIGRATIONS
perf::PERF_COUNT_SW_PAGE_FAULTS_MIN      : This counts the number of minor page faults.
perf::MINOR-FAULTS                       : PERF_COUNT_SW_PAGE_FAULTS_MIN
perf::PERF_COUNT_SW_PAGE_FAULTS_MAJ      : This counts the number of major page faults.
perf::MAJOR-FAULTS                       : PERF_COUNT_SW_PAGE_FAULTS_MAJ
perf::PERF_COUNT_SW_CGROUP_SWITCHES      : This counts cgroup switches.
perf::CGROUP-SWITCHES                    : PERF_COUNT_SW_CGROUP_SWITCHES
```




## In the TempAndCPURecord.csv file, These temperature data from left to right are:

### coretemp-isa-0000
### Adapter: ISA adapter

Package id 0

 Core 0                     : Core Processor 0
 Core 1                     : Core Processor 1
 Core 2                     : Core Processor 2
 Core 3                     : Core Processor 3

### acpitz-acpi-0
### Adapter: ACPI interface

 temp1 
 temp2

### nvme-pci-0100
### Adapter: PCI adapter

 Composite
 Sensor 1
 Sensor 2 

### CPU Utilization  ： record every second
cpu
cpu0
cpu1
cpu2
cpu3

### CPU frequency

cpu0
cpu1
cpu2
cpu3



