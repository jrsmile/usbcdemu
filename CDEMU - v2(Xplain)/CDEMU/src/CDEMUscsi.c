/*
Copyright (c) 2011 Curtis Reno

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "CDEMUscsi.h"
#include "string.h"
#include "CDEMUboard.h"
#include "navigation.h"
#include "fat.h"
#include "file.h"
#include "udi_msc.h"

uint32_t ISOSizebytes;					//holder of current iso file size - size defined in CDEMUscsi.c => void test_read_iso_(void)
extern bool cd_storage_type;			//global flag for cd emulation control

// 0x43 read toc
void CDREAD_TOC(char* scsi_cmd)
{
	int allocation_length = scsi_cmd[8];
	//
	//TOC Read Responce data for single track cdrom/ISO file. LBA / Format 0000
	//
	if(scsi_cmd[1]==0x00 &&	scsi_cmd[2]==0x00)
	{
		uint8_t TOCRet[20];
		//TOC Responce Header
		TOCRet[0] =0x00;			//toc data length	msb 					18 bytes follow
		TOCRet[1] =0x12;			//toc data length	lsb
		TOCRet[2] =0x01;			//first track number						1st track
		TOCRet[3] =0x01;			//last track number							same as first, only 1 track total
		//track 1 info
		TOCRet[4] =0x00;			//reserved
		TOCRet[5] =0x04;			//4bit adr  4bit control	CHANGED ADR TO 0 (NO SUB DATA) was 1 (all sub data)
		TOCRet[6] =0x01;			//tract number								1st track
		TOCRet[7] =0x00;			//reserved
		TOCRet[8] =0x00;			//byte1	msb start track lba					lba of start of track
		TOCRet[9] =0x00;			//byte2
		TOCRet[10]=0x00;			//byte3
		TOCRet[11]=0x00;			//byte4 lsb
		//lead out info
		TOCRet[12]=0x00;			//reserved
		TOCRet[13]=0x04;			//4bit adr  4bit control	CHANGED ADR TO 0 (NO SUB DATA) was 1 (all sub data)
		TOCRet[14]=0xaa;			//tract number								AA=lead out track
		TOCRet[15]=0x00;			//reserved
		TOCRet[16]=ISOSizebytes>>24;//lead out msb
		TOCRet[17]=ISOSizebytes>>16;//lead out
		TOCRet[18]=ISOSizebytes>>8;	//lead out
		TOCRet[19]=ISOSizebytes;	//lead out lsb
		udi_msc_data_send((uint8_t *) & TOCRet, allocation_length);
	}
	//
	//TOC Read Responce data for single track cdrom/ISO files. MSF
	//
	else if( scsi_cmd[1]==0x02 && scsi_cmd[2]==0x00)
	{
		uint8_t TOCRet[20];
		//TOC Responce Header
		TOCRet[0] =0x00;			//toc data length	msb 					18 bytes follow
		TOCRet[1] =0x12;			//toc data length	lsb
		TOCRet[2] =0x01;			//first track number						1st track
		TOCRet[3] =0x01;			//last track number							same as first, only 1 track total
		//track 1 info
		TOCRet[4] =0x00;			//reserved
		TOCRet[5] =0x04;			//4bit adr  4bit control	CHANGED ADR TO 0 (NO SUB DATA) was 1 (all sub data)
		TOCRet[6] =0x01;			//tract number								1st track
		TOCRet[7] =0x00;			//reserved
		TOCRet[8] =0x00;			//byte1	msb start track lba					lba of start of track
		TOCRet[9] =0x00;			//byte2
		TOCRet[10]=0x00;
		TOCRet[11]=0x00;			//byte4 lsb
		//lead out info
		TOCRet[12]=0x00;			//reserved
		TOCRet[13]=0x04;			//4bit adr  4bit control	CHANGED ADR TO 0 (NO SUB DATA) was 1 (all sub data)
		TOCRet[14]=0xaa;		    //tract number								AA=lead out track
		TOCRet[15]=0x00;			//reserved
		TOCRet[16]=ISOSizebytes>>24;//lead out msb
		TOCRet[17]=ISOSizebytes>>16; //lead out
		TOCRet[18]=ISOSizebytes>>8; //lead out
		TOCRet[19]=ISOSizebytes;	//lead out lsb
		udi_msc_data_send((uint8_t *) & TOCRet, allocation_length);
	}
	//
	//TOC Read Responce data for single track cdrom/ISO files. LBA / Format 0001
	//
	else if(scsi_cmd[1]==0x00 && scsi_cmd[2]==0x01)
	{
		uint8_t TOCRet[12];
		//TOC Responce Header
		TOCRet[0] =0x00;			//toc data length	msb 					18 bytes follow
		TOCRet[1] =0x0a;			//toc data length	lsb
		TOCRet[2] =0x01;			//first track number						1st track
		TOCRet[3] =0x01;			//last track number							same as first, only 1 track total
		//track 1 info
		TOCRet[4] =0x00;			//reserved
		TOCRet[5] =0x04;			//4bit adr  4bit control	CHANGED ADR TO 0 (NO SUB DATA) was 1 (all sub data)
		TOCRet[6] =0x01;			//tract number								1st track
		TOCRet[7] =0x00;			//reserved

		TOCRet[8] =0x00;			//byte1	msb start track lba					lba of start of track
		TOCRet[9] =0x00;			//byte2
		TOCRet[10]=0x00;			//byte3
		TOCRet[11]=0x00;			//byte4 lsb
		udi_msc_data_send((uint8_t *) & TOCRet, allocation_length);
	}
		else
		{
			udi_msc_sense_command_invalid();
			udi_msc_csw_process();			
		    allocation_length=0;
		}
}


/****************************************************/
/****************************************************/
// 0x5A SCSI Mode Sense 10
/****************************************************/
void CDModeSense(void)
{
	uint8_t ModeSenseHeader[]={0x00,0x4a,0x70,0x00,0x00,0x00,0x00,0x00,0x2A,0x42,		// need to change later
						0x3F,0x37,0xF1,0x7F,0x29,0x23,0x10,0x8A,0x01,0x00,				// so far reports cap.
						0x08,0x00,0x10,0x8A,0x00,0x10,0x10,0x8A,0x10,0x8A,				// for all devices
						0x00,0x01,0x00,0x00,0x00,0x00,0x10,0x8A,0x00,0x04,
						0x00,0x00,0x10,0x8A,0x00,0x00,0x0D,0xC8,0x00,0x00,
						0x0B,0x06,0x00,0x00,0x06,0xE4};
	udi_msc_data_send((uint8_t *) & ModeSenseHeader, 56);
}

/****************************************************/
/****************************************************/
// 0xBB SCSI READ DISK INFO
/****************************************************/
void CDReadDiskInfo(void)
{
	uint8_t ReadDiskInfo[32];
	//Mode Sense 2A Code Page Return, Mech and Capabilities
	ReadDiskInfo[0] =0x00;
	ReadDiskInfo[1] =0x20;
	ReadDiskInfo[2] =0x0e;
	ReadDiskInfo[3] =0x01;
	ReadDiskInfo[4] =0x01;
	ReadDiskInfo[5] =0x01;
	ReadDiskInfo[6] =0x01;
	ReadDiskInfo[7] =0x80;
	ReadDiskInfo[8] =0x00;
	ReadDiskInfo[9] =0x00;
	ReadDiskInfo[10]=0x00;
	ReadDiskInfo[11]=0x00;
	ReadDiskInfo[12]=0x00;
	ReadDiskInfo[13]=0x00;
	ReadDiskInfo[14]=0x00;
	ReadDiskInfo[15]=0x00;
	ReadDiskInfo[16]=0xff;
	ReadDiskInfo[17]=0xff;
	ReadDiskInfo[18]=0xff;
	ReadDiskInfo[19]=0xff;
	ReadDiskInfo[20]=0xff;
	ReadDiskInfo[21]=0xff;
	ReadDiskInfo[22]=0xff;
	ReadDiskInfo[23]=0xff;
	ReadDiskInfo[24]=0x00;
	ReadDiskInfo[25]=0x00;
	ReadDiskInfo[26]=0x00;
	ReadDiskInfo[27]=0x00;
	ReadDiskInfo[28]=0x00;
	ReadDiskInfo[29]=0x00;
	ReadDiskInfo[30]=0x00;
	ReadDiskInfo[31]=0x00;
	udi_msc_data_send((uint8_t *) & ReadDiskInfo,32);
}

