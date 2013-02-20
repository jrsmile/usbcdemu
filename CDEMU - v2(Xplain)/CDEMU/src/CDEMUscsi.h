/*
 * SCSI_CD_CMD.h
 *
 *  Created on: Mar 23, 2010
 *      Author: reno
 */

#ifndef SCSI_CD_CMD_H_
#define SCSI_CD_CMD_H_

void CDREAD_TOC(char* scsi_cmd);
void CDModeSense(void);
void CDReadDiskInfo(void);


#endif /* SCSI_CD_CMD_H_ */
