# Warning
Starting from mbed-os 5.10 this repository is deprecated. 
Please refer to mbed-os 5.10 [documentation](https://github.com/ARMmbed/mbed-os-5-docs/blob/development/docs/api/storage/FlashIAPBlockDevice.md) and [code](https://github.com/ARMmbed/mbed-os/tree/master/components/storage/blockdevice/COMPONENT_FLASHIAP) for more detail on how to enable FLASHIAP support.

# Block Device driver build on top of FlashIAP API

## Warning 
This driver is **EXPERIMENTAL** and improper usage could kill your board's flash.

This driver should only be used on platforms where the FlashIAP implementation is using external flash or in conjunction with a filesystem with wear leveling, that can operate on a page size granularity.

Additional concerns:
- The FlashIAP may freeze code execution for a long period of time while writing to flash. Not even high-priority irqs will be allowed to run, which may interrupt background processes.


## Configuration
None.

## Tested on

* K82F
* K64F
