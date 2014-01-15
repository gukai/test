#!/bin/sh
CPUUSAGE=""
TX_BYTES=
RX_BYTES=

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
#case "$1" in
#        all)
#                qemu_kvm
#                ;;
#        *)
#                vzctl runscript 
#esac



cpu_used
echo $CPUUSAGE
