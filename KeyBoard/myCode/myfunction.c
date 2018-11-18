#include "myfunction.h"




static uint8_t scan_key_y(void)
{
    uint8_t value = 0;
    if(HAL_GPIO_ReadPin(KEY_Y1_GPIO_Port,KEY_Y1_Pin) == GPIO_PIN_SET)
    {
        value = 1<<0;
    }
    if(HAL_GPIO_ReadPin(KEY_Y2_GPIO_Port,KEY_Y2_Pin) == GPIO_PIN_SET)
    {
        value = 1<<1;
    }
    if(HAL_GPIO_ReadPin(KEY_Y3_GPIO_Port,KEY_Y3_Pin) == GPIO_PIN_SET)
    {
        value = 1<<2;
    }
    if(HAL_GPIO_ReadPin(KEY_Y4_GPIO_Port,KEY_Y4_Pin) == GPIO_PIN_SET)
    {
        value = 1<<3;
    }
    return value;
}

uint8_t scan_key(uint8_t key[3])
{
		uint8_t value = 0;
		/***********************/
		HAL_GPIO_WritePin(KEY_X1_GPIO_Port,KEY_X1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(KEY_X2_GPIO_Port,KEY_X2_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KEY_X3_GPIO_Port,KEY_X3_Pin,GPIO_PIN_RESET);
    key[0] = key[0] | scan_key_y();
    if( (key[0] & 0x0f) != 0 )
    {
			key[0] = 1 << 4;
    }
		else
		{
			key[0] = 0;
		}
		/***********************/
		HAL_GPIO_WritePin(KEY_X1_GPIO_Port,KEY_X1_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KEY_X2_GPIO_Port,KEY_X2_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(KEY_X3_GPIO_Port,KEY_X3_Pin,GPIO_PIN_RESET);
    key[1] = key[1] | scan_key_y();
    if( (key[1] & 0x0f) != 0 )
    {
			key[1] = 1 << 5;
    }
		else
		{
			key[1] = 0;
		}
		/***********************/
		HAL_GPIO_WritePin(KEY_X1_GPIO_Port,KEY_X1_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KEY_X2_GPIO_Port,KEY_X2_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KEY_X3_GPIO_Port,KEY_X3_Pin,GPIO_PIN_SET);
    key[2] = key[2] | scan_key_y();
    if( (key[2] & 0x0f) != 0 )
    {
			key[2] = 1 << 6;
    }
		else
		{
			key[2] = 0;
		}
		/***********************/
		if((key[0] | key[1] | key[2]) == 0)
		{
			return ERROR;
		}
		else
		{
			return SUCCESS;
		}
}





