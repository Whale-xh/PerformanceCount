import os
import subprocess



    
def run_CountersAndBenchmark():
    proc_event=subprocess.Popen("./preset_native_test",shell=True)
    for i in range(6):
        os.system("python testbenchmark.py")
        proc_benchmark=subprocess.Popen("../mcftp test_benchmark.xml",shell=True)
        pid2=os.getpid()
        bm_outs,bm_errs=proc_benchmark.communicate()
    ev_outs,ev_errs=proc_event.communicate()
    

if __name__=="__main__":
    run_CountersAndBenchmark()
    



    
    
