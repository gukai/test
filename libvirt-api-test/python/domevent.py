#!/usr/bin/python
import libvirt
import time
import threading
import sys

#def LibvirtLifecycleEvent():
#		print "Suspended"

def myDomainEventCallback2 (conn, dom, event, detail, opaque):
    print "myDomainEventCallback2 EVENT: Domain %s %s" % (dom.name(), dom.ID())

def virEventLoopNativeRun():
    while True:
        libvirt.virEventRunDefaultImpl()
def virEventLoopNativeStart():
#    global eventLoopThread
    libvirt.virEventRegisterDefaultImpl()
    eventLoopThread = threading.Thread(target=virEventLoopNativeRun, name="libvirtEventLoop")
    eventLoopThread.setDaemon(True)
    eventLoopThread.start()
def main():
    libconn=libvirt.open("qemu:///system")
    info = libconn.getInfo()
    print info
    libconn.listAllDomains(libvirt.VIR_CONNECT_LIST_DOMAINS_RUNNING)
    libvirt.virEventRegisterDefaultImpl()
    virEventLoopNativeStart()
    #libvirt.virEventRunDefaultImpl()
    #domainEventRegisterAny(self, dom, eventID, cb, opaque)
    dom=libconn.lookupByName("xp")
    print dom.name()
    ret=libconn.domainEventRegisterAny(dom,libvirt.VIR_DOMAIN_EVENT_ID_LIFECYCLE,myDomainEventCallback2, None)
    #libconn.setKeepAlive(5, 3)
    #time.sleep(1)
    #while 1:
    while True:
        time.sleep(1)
if __name__=="__main__":
    main()
