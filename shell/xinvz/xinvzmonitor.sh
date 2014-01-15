#!/bin/sh
CPUUSAGE=""
TX_BYTES=""
RX_BYTES=""
DISK_READ=""
DISK_WRITE=""


usage(){
    echo 'xinvzmonitor.sh <CTID | all>'
}

is_online(){
    local i=0
    while [ $i -le 5 ] && ! vzctl exec2 $CTID ifconfig >/dev/null 2>&1 ; do
        i=`expr $i + 1`
        sleep 1
    done

    if [ $i -ge  5 ] ; then
       return 1
    else
       return 0
    fi
}

cpu_used(){
    local i=0
    local list=`vzctl exec $CTID vmstat 1 1 | awk '{if(NR==3)print $0;}'`
    #echo $list

    for c in $list; do
       i=`expr $i + 1`
       if [ $i -eq 15 ]; then id=$c; fi
    done

    CPUUSAGE=`expr 100 - $id`%
}

net_flux(){
    vm_id=$CTID
    ex_nic=veth${vm_id}.1
    TX_BYTES=`cat /sys/devices/virtual/net/${ex_nic}/statistics/tx_bytes 2>/dev/null`
    RX_BYTES=`cat /sys/devices/virtual/net/${ex_nic}/statistics/rx_bytes 2>/dev/null`
}

mom_one(){
    if ! vzlist $CTID -a >/dev/null 2>&1; then
        echo "ERROR"
        echo "The CTID is not exist."
        exit 3
    fi

    if ! is_online; then
        #echo "offline"
        DISK_READ=0
        DISK_WRITE=0
        TX_BYTES=0
        RX_BYTES=0
        CPUUSAGE=0 
        return 0
    fi
    #echo "online"
    cpu_used
    net_flux
}

#Main from here
#if [ $# -ne 1 ]; then
#    usage()
#fi


case "$1" in
    all)
        ;;
    *)
        CTID=$1
        mom_one
        ;;
esac

echo -e ${CTID}"\t" ${CPUUSAGE}"\t" ${RX_BYTES}"\t" ${TX_BYTES}"\t" ${DISK_READ}"\t" ${DISK_WRITE}
