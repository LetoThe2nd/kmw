kmw
===

These are the Kernel Module Workshop sources that will be used during my work-along presentations on linux driver programming. They show the basics from compiling a module at all, through module parameters and attributes, to a simple driver for the RGB led on a [bacon cape](http://elinux.org/Bacon_Cape).

Please note:
------------

This by no means is meant as a guide on best practises or coding conventions used in the kernel - the examples are more geared towards the flow of the presentation. If in doubt how to do something, please ALWAYS check /Documentation in the kernel sources, also use checkpatch.pl for whatever you want to submit!

Noteworthy literature:
----------------------

[Linux Device Drivers, 3rd edition](http://lwn.net/Kernel/LDD3/) - a little outdated by now, but still contains lots and lots of valuable imformation.

[Linux Cross Reference](http://lxr.free-electrons.com/) - the kernel sources as cross-referenced html. Great for browsing and following symbols!

[LinuxForU's Device Driver series](http://www.linuxforu.com/tag/linux-device-drivers-series/) - a very nice series on device drivers. Some parts have to be taken with a pinch of salt, but definitely a good read.
