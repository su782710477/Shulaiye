#ifndef __RC522_FUNCTION_H
#define	__RC522_FUNCTION_H

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "rc522_config.h"

/* ���Ͷ��� ------------------------------------------------------------------*/
/* �궨�� --------------------------------------------------------------------*/

/* ��չ���� ------------------------------------------------------------------*/
/* �������� ------------------------------------------------------------------*/
void   PcdReset             ( void );                       //��λ
void   M500PcdConfigISOType ( uint8_t type );                    //������ʽ
char   PcdRequest           ( uint8_t req_code, uint8_t * pTagType ); //Ѱ��
char   PcdAnticoll          ( uint8_t * pSnr);                   //������
char   PcdAuthState         ( uint8_t ucAuth_mode, uint8_t ucAddr, uint8_t * pKey, uint8_t * pSnr );//��֤��Ƭ����
char   PcdRead              ( uint8_t ucAddr, uint8_t * pData );      //����
char   PcdSelect            ( uint8_t * pSnr );                  //ѡ��        
#endif /* __RC522_FUNCTION_H */

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/

