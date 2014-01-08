TEMP=`getopt -o ab:c:: --long a-long,b-long:,c-long::`

GetOpt(){

    if [ $? != 0 ] ; then echo "Terminating..." >&2 ; exit 1 ; fi

    echo $TEMP
    echo "1 shi $1"

    while true ; do
            case "$1" in
                    -a|--a-long) echo "Option a" ; shift ;;
                    -b|--b-long) echo "Option b, argument \`$2'" ; shift 2 ;;
                    -c|--c-long)
                            # c has an optional argument. As we are in quoted mode,
                            # an empty parameter will be generated if its optional
                            # argument is not found.
                            case "$2" in
                                    "") echo "Option c, no argument"; shift 2 ;;
                                    *)  echo "Option c, argument \`$2'" ; shift 2 ;;
                            esac ;;
                    --) shift ; break ;;
                    *) echo "Internal error!" ; exit 1 ;;
            esac
    done
    echo "Remaining arguments:"
    for arg do
       echo '--> '"\`$arg'" ;
    done
}



case "$1" in
    cmd)
	echo "exec cmd1"
	eval set -- "$TEMP"
	GetOpt
        #cmd1_func && exit 0
        #$1
        ;;
    stop)
        cmd2_func || exit 0
        $1
        ;;
    restart)
        $1
        ;;
    reload)
        rh_status_q || exit 7
        $1
        ;;
    force-reload)
        force_reload
        ;;
    status)
        rh_status
        ;;
    condrestart|try-restart)
        rh_status_q || exit 0
        restart
        ;;
    *)
        echo $"Usage: $0 {start|stop|status|restart|condrestart|try-restart|reload|force-reload}"
        exit 2
esac
exit $?
