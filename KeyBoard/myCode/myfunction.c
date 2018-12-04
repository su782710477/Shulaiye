#include "myfunction.h"




static uint16_t scan_key_y(void)
{
    uint8_t value = 0;
    if(HAL_GPIO_ReadPin(KEY_Y1_GPIO_Port,KEY_Y1_Pin) == GPIO_PIN_SET)
    {
        value = value | (1<<0);
    }
    if(HAL_GPIO_ReadPin(KEY_Y2_GPIO_Port,KEY_Y2_Pin) == GPIO_PIN_SET)
    {
        value = value | (1<<1);
    }
    if(HAL_GPIO_ReadPin(KEY_Y3_GPIO_Port,KEY_Y3_Pin) == GPIO_PIN_SET)
    {
        value = value | (1<<2);
    }
    if(HAL_GPIO_ReadPin(KEY_Y4_GPIO_Port,KEY_Y4_Pin) == GPIO_PIN_SET)
    {
        value = value | (1<<3);
    }
    return value;
}

/**				-- 1 2 3
	*				-- 4 5 6
	*				-- 7 8 9
	*				-- * 0 #
	*					 | | |	
	*			=============		0000(保留)	0000（第三列）		0000（第二列）		0000（第一列）
	*			e.g. 5被按下			0000			 	0000						0010						0000
	*				1，5，9被按下	0000				0100						0010						0001
	*/
uint16_t scan_key(void)
{
		/***********************/
		uint16_t key_value = 0;
		HAL_GPIO_WritePin(KEY_X1_GPIO_Port,KEY_X1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(KEY_X2_GPIO_Port,KEY_X2_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KEY_X3_GPIO_Port,KEY_X3_Pin,GPIO_PIN_RESET);
		key_value = key_value | ( ( scan_key_y( ) ) << 0 );
		/***********************/
		HAL_GPIO_WritePin(KEY_X1_GPIO_Port,KEY_X1_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KEY_X2_GPIO_Port,KEY_X2_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(KEY_X3_GPIO_Port,KEY_X3_Pin,GPIO_PIN_RESET);
		key_value = key_value | ( ( scan_key_y( ) ) << 4 );
		/***********************/
		HAL_GPIO_WritePin(KEY_X1_GPIO_Port,KEY_X1_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KEY_X2_GPIO_Port,KEY_X2_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KEY_X3_GPIO_Port,KEY_X3_Pin,GPIO_PIN_SET);
		key_value = key_value | ( ( scan_key_y( ) ) << 8 );	
		/***********************/
		HAL_GPIO_WritePin(KEY_X1_GPIO_Port,KEY_X1_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KEY_X2_GPIO_Port,KEY_X2_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KEY_X3_GPIO_Port,KEY_X3_Pin,GPIO_PIN_RESET);
		return key_value;
}





