# edge-detection-driver
A driver that receives an image and performs edge detection on it.

## Compile
To compile just run make.

## Install Kernel Module
To install the kernel module just run make install as root

## Uninstall Kernel Module
To uninstall the kernel module just run make uninstall as root

## Test
There is an application that gets compiled as part of the makefile located at ./bin/edge-detector
it receives two arguments file_in and file_out.
file_in: is the image to send to the driver for conversion.
file_out: is where the modified image should be saved.


#Notes:
 - The driver doesn't actually perform any filter yet.
 - the app does not validate input, so if not used as expected it might crash.


