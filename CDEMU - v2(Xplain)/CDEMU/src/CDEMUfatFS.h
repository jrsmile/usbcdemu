/*
 * CDEMUfatFS.h
 *
 * Created: 1/21/2013 7:29:13 PM
 *  Author: SonicScrewDriver
 */ 


#ifndef CDEMUFATFS_H_
#define CDEMUFATFS_H_

void ramdrive_setup(void);
void test_read_iso_(void);

//common fs routines
void fs_open(void);
void fs_close(void);

#endif /* CDEMUFATFS_H_ */