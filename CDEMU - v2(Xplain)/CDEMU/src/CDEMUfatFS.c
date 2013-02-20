/*
 * CDEMUfatFS.c
 *
 * Created: 1/21/2013 7:28:51 PM
 *  Author: CReno
 */ 


#include "CDEMUboard.h"
#include "CDEMUfatFS.h"
#include "navigation.h"
#include "fat.h"
#include "fs_com.h"
#include "file.h"
#include "delay.h"


extern uint32_t ISOSizebytes;			//holder of current iso file size - size defined in CDEMUscsi.c => void test_read_iso_(void)
uint32_t ISOfsoffset;					//holder of current iso file offset

//mount, format, label sdram drive - triggered just before main loop
void ramdrive_setup(void)
{
	fs_open();
	fat_format(FS_FORMAT_DEFAULT);						//format ram drive
	fs_close();
	fs_open();
	nav_partition_label(FS_LABEL_WRITE, "CDEMU_SDRAM");//write drive label
	fs_close();
}


//mount first found iso using navigator to get offset info used during emulation
void test_read_iso_(void)
{
	fs_open();
	nav_filelist_first(FS_FILE);			//make sure file pointer is pointing at first file in list
	bool exit_file_list=false;
	do{										//loop through the files in the rood directory looking for the first iso found
		if(!nav_file_checkext( "iso" ))
		{
			if(!nav_filelist_set( 0 , FS_FIND_NEXT ))
			{
				dbg_attention2();			//will trigger attention2 if iso missing
				exit_file_list=true;		//exit file search, we cannot find any iso's
			}
		}
		else								//iso file found, open in nav to get file offset later
		{
			exit_file_list=true;
			file_open(FOPEN_MODE_R);
			ISOSizebytes=nav_file_lgt();	//set file size global for use later
		}		
	}while(exit_file_list!=true);
	//Global offset, buffer the iso sector offset for emulation i/o 
	ISOfsoffset=fs_g_nav.u32_ptr_fat + fs_g_nav.u32_offset_data + ((fs_g_nav_entry.u32_cluster - 2) * fs_g_nav.u8_BPB_SecPerClus);
	fs_close();
}



//common fs routines
void fs_open(void)
{
	nav_reset();
	nav_drive_set(nav_drive_nb() - 1);
	nav_partition_mount();
}

void fs_close(void)
{
	file_close();
	nav_reset();
}