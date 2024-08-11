The Makefile when combined with Make-default.mk is performing the following:

* make (default target):
```
gcc -E  -M -D__DEPEND__ -I/home/kean/opt/torcs-1.3.7/src/export/include -I/home/kean/opt/torcs-1.3.7/src -D_SVID_SOURCE -D_BSD_SOURCE -DSHM -DHAVE_CONFIG_H   brabham.cpp > .depend
g++ -I/home/kean/opt/torcs-1.3.7/src/export/include -I/home/kean/opt/torcs-1.3.7/src -g -O2 -Wall -fPIC -fno-strict-aliasing -O2 -DUSE_RANDR_EXT -DGL_GLEXT_PROTOTYPES -Wall -fPIC -fno-strict-aliasing -O2 -DUSE_RANDR_EXT -DGL_GLEXT_PROTOTYPES  -D_SVID_SOURCE -D_BSD_SOURCE -DSHM -DHAVE_CONFIG_H  -c brabham.cpp
In file included from /usr/include/x86_64-linux-gnu/bits/libc-header-start.h:33,
                 from /usr/include/stdio.h:27,
                 from brabham.cpp:22:
/usr/include/features.h:194:3: warning: #warning "_BSD_SOURCE and _SVID_SOURCE are deprecated, use _DEFAULT_SOURCE" [-Wcpp]
  194 | # warning "_BSD_SOURCE and _SVID_SOURCE are deprecated, use _DEFAULT_SOURCE"
      |   ^~~~~~~
g++ -shared -o brabham.so brabham.o -L/home/kean/opt/torcs-1.3.7/src/export/lib  -lopenal -lalut -lvorbisfile -L/usr/lib   
mkdir /home/kean/opt/torcs-1.3.7/src/export/drivers/brabham
 Exporting brabham.so to /home/kean/opt/torcs-1.3.7/src/export/drivers/brabham/brabham.so
```

* make install:
```
mkdir /home/kean/opt/torcs-1.3.7/share/games/torcs/drivers/brabham
 /usr/bin/install -c -m 644 brabham.xml /home/kean/opt/torcs-1.3.7/share/games/torcs/drivers/brabham/brabham.xml
 /usr/bin/install -c -m 644 acura-nsx-sz.rgb /home/kean/opt/torcs-1.3.7/share/games/torcs/drivers/brabham/acura-nsx-sz.rgb
 /usr/bin/install -c -m 644 logo.rgb /home/kean/opt/torcs-1.3.7/share/games/torcs/drivers/brabham/logo.rgb
mkdir /home/kean/opt/torcs-1.3.7/lib/torcs/drivers/brabham
 /usr/bin/install -c -m 644 brabham.so /home/kean/opt/torcs-1.3.7/lib/torcs/drivers/brabham/brabham.so
```

