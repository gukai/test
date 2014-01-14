#!/bin/sh
CPUUSAGE=""


cpu_used(){
    local i=0
    local list=`vmstat 1 1 | awk '{if(NR==3)print $0;}'`
    #echo $list

    for c in $list; do
       i=`expr $i + 1`
       if [ $i -eq 15 ]; then id=$c; fi
    done

    CPUUSAGE=`expr 100 - $id`%
}


#Main from here
cpu_used
echo $CPUUSAGE
