#!/bin/bash
COMMAND=""
CTID=""
BRIDGE=""
DEVNAME=""
IPADDR=""
NETMASK=""
GATEWAY=""
DNS1=""


create-usage() {
  echo "usage: --command create <--ctid id>  <--bridge bridge>  <--devname name> <--ipaddr ip> <--netmask mask> <--gateway gateway> <--dns1 dns>"
}

is_online(){
    local i=0
    while [ $i -le 5 ] && ! vzctl exec2 $CTID ifconfig >/dev/null 2>&1 ; do
        #echo "try again $i"
        i=`expr $i + 1`
        sleep 1
    done

    if [ $i -ge  5 ] ; then
       return 1
    else
       return 0
    fi
}

validate-create() {
    
    if [ ! -f /home/gukai/vznet.conf ] ; then
        echo '#!/bin/bash' > /etc/vz/vznet.conf
        echo 'EXTERNAL_SCRIPT="/usr/sbin/vznetaddbr"' >> /etc/vz/vznet.conf
    fi

    if [ -z ${CTID} ];then
        echo "ERROR"
        echo "ctid must be set"
	exit 2;
    fi

    if [ -z ${BRIDGE} ];then
        echo "ERROR"
        echo "bridge must be set"
	exit 2;
    fi

    if [ -z ${DEVNAME} ];then
        echo "ERROR"
        echo "devname must be set"
	exit 2;
    fi

    if [ -z ${IPADDR} ];then
        echo "ERROR"
        echo "ipaddr must be set"
	exit 2;
    fi

    if [ -z ${NETMASK} ];then
        echo "ERROR"
        echo "netmask must be set"
	exit 2;
    fi
    if [ -z ${GATEWAY} ];then
        echo "ERROR"
        echo "gateway must be set"
	exit 2;
    fi
    if [ -z ${DNS1} ];then
        echo "ERROR"
        echo "dns1 must be set"
	exit 2;
    fi
    
    #echo "command:$COMMAND, ctid:$CTID, bridge:$BRIDGE, devname:$DEVNAME, ipaddr:$IPADDR, netmask:$NETMASK, gateway:$GATEWAY, dns1:$DNS1"
}

add-netconfig(){
    local conf="TYPE=Ethernet NM_CONTROLLED=no BOOTPROTO=static ONBOOT=yes DEVICE=$DEVNAME IPADDR=$IPADDR NETMASK=$NETMASK GATEWAY=$GATEWAY DNS1=$DNS1"
    vzctl exec2 $CTID "echo $conf > /etc/sysconfig/network-scripts/ifcfg-$DEVNAME" >/dev/null 2>&1
}

create-veth(){
    if ! vzlist $CTID >/dev/null 2>&1; then
        echo "ERROR"
        echo "The CTID is not exist."
	exit 3
    fi 
    
    validate-create  
 
    if is_online; then
        add-netconfig
    else
       echo "ERROR"
       echo "$CTID is offline"
       exit 4
    fi
    
    local num=`echo $DEVNAME | grep -Eo '[0-9]+'`

    vzctl set $CTID --netif_add $DEVNAME --bridge $BRIDGE --ifname $DEVNAME --save >/dev/null 2>&1
   # vzctl set $CTID --netif_add $DEVNAME --bridge $BRIDGE --ifname $DEVNAME --save >/dev/null 2>&1
    
    #brctl addif $BRIDGE veth$CTID.$num >/dev/null 2>&1
    
    vzctl exec $CTID ifup $DEVNAME >/dev/null 2>&1
        
}

which brctl > /dev/null 2>&1
if [ $? != 0 ]; then
    echo "ERROR"
    echo "It's necessary  to install  bridge-utils"
    exit 5
fi

TEMP=`getopt -o m:c:b:d:i:n:g:s: --long command:,ctid:,bridge:,devname:,ipaddr:,netmask:,gateway:,dns1: \
     -n 'example.bash' -- "$@"`

if [ $? != 0 ] ; then echo "Terminating..." >&2 ; exit 1 ; fi

eval set -- "$TEMP"

while true ; do
        case "$1" in
		-m| --command) COMMAND=$2 ; shift 2 ;;
                -c|--ctid) CTID=$2; shift 2 ;;
                -b|--bridge) BRIDGE=$2 ; shift 2 ;;
                -c|--devname) DEVNAME=$2 ; shift 2 ;;
                -i|--ipaddr) IPADDR=$2 ; shift 2 ;;
                -n|--netmask) NETMASK=$2 ; shift 2 ;;
                -g|--gateway) GATEWAY=$2; shift 2 ;;
                -s|--dns1) DNS1=$2; shift 2 ;;
                --) shift ; break ;;
                *) echo "Unknow Option, verfiy your command" ; create-usage; exit 1 ;;
        esac
done

if [ -z ${COMMAND} ];then
    echo "ERROR"
    echo "command cant be null"
    exit 1
fi

case $COMMAND in
    create) create-veth ;;
    usage) create-usage ;;
esac
exit $?
