import usb.core
import usb.util
from time import sleep

# find our device
dev = usb.core.find(idVendor=0x03EB, idProduct=0x206C)

# was it found?
if dev is None:
    raise ValueError('Device not found')

# set the active configuration. With no arguments, the first
# configuration will be the active one
#dev.set_configuration()


# get an endpoint instance
#cfg = dev.get_active_configuration()
#intf = cfg[(0,0)]





#ep = usb.util.find_descriptor(
#    intf,
    # match the first OUT endpoint
#    custom_match = \
#    lambda e: \
#        usb.util.endpoint_direction(e.bEndpointAddress) == \
#        usb.util.ENDPOINT_OUT)

#assert ep is not None

dev.ctrl_transfer(0x20, 0, 0, 0, None) 
sleep(1)
dev.ctrl_transfer(0x20, 0, 0, 0, None) 
sleep(1)
dev.ctrl_transfer(0x20, 0, 0, 0, None) 
sleep(1)
dev.ctrl_transfer(0x20, 0, 0, 0, None) 
sleep(1)
dev.ctrl_transfer(0x20, 0, 0, 0, None) 
sleep(1)
dev.ctrl_transfer(0x20, 0, 0, 0, None) 
sleep(1)
dev.ctrl_transfer(0x20, 0, 0, 0, None) 
sleep(1)
dev.ctrl_transfer(0x20, 0, 0, 0, None) 
sleep(1)
dev.ctrl_transfer(0x20, 0, 0, 0, None) 
sleep(1)
dev.ctrl_transfer(0x20, 0, 0, 0, None) 

