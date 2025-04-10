
#include <iostream>
extern "C" {
#include <kernel.h>
#include <sio.h>
#include <iopcontrol.h>
#include <iopcontrol_special.h>
#include <loadfile.h>
extern unsigned char ioprp[]; extern unsigned int size_ioprp;
}

void newlib_prepare() {
   sio_puts(__FUNCTION__);
   sio_puts("Replacing FILEIO and making sure CDVDFSV is loaded before Newlib shits the bed!\n");
   while (!SifIopRebootBuffer(ioprp, size_ioprp)) {}; //replace FILEIO
   while (!SifIopSync()) {};
   SifLoadStartModule("rom0:CDVDFSV", 0, NULL, NULL);
}

void hack_init() __attribute__ ((constructor));
 
void hack_init() {
   sio_puts(__FUNCTION__);
   newlib_prepare();
}


int main(int argc, char** argv)
{
   sio_puts(__FUNCTION__);
   std::cout << "Hello world from std::cout\n";
   printf("Hello world from printf (or puts)\n");
   sio_puts("Hello world from EE UART\n");
   SleepThread();
   
   return 0;
}

//this function will replace FILEIO and IOMAN. and will execute CDVDFSV
//Arcade Boards have incompatible FILEIO (different RPC) and CDVDFSV is not loaded by default
//This combined with PS2SDK insisting on Keeping the RPC Binding on endless loops causes more black screens than solutions
void _ps2sdk_memory_init() {
   sio_puts(__FUNCTION__);
   newlib_prepare();
}