#
# for cygwin, until I get a list of the Archetecture defines
# appropriate for the cgywin environment that can be used in Imakefile
#
gcc -g -O2  -o nasd.exe -L/usr/X11R6/lib  dia/libdia.a  dda/voxware/libvoxware.
a os/libos.a


