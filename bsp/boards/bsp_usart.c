#include "bsp_usart.h"
#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include "string.h"
#include "cmsis_os.h"

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern UART_HandleTypeDef huart6;
extern DMA_HandleTypeDef hdma_usart6_rx;
extern DMA_HandleTypeDef hdma_usart6_tx;

void usart1_tx_dma_init(void)
{

    //enable the DMA transfer for the receiver and tramsmit request
    //ʹ��DMA���ڽ��պͷ���
    SET_BIT(huart1.Instance->CR3, USART_CR3_DMAR);
    SET_BIT(huart1.Instance->CR3, USART_CR3_DMAT);

    //disable DMA
    //ʧЧDMA
    __HAL_DMA_DISABLE(&hdma_usart1_tx);

    while(hdma_usart1_tx.Instance->CR & DMA_SxCR_EN)
    {
        __HAL_DMA_DISABLE(&hdma_usart1_tx);
    }

    hdma_usart1_tx.Instance->PAR = (uint32_t) & (USART1->DR);
    hdma_usart1_tx.Instance->M0AR = (uint32_t)(NULL);
    hdma_usart1_tx.Instance->NDTR = 0;


}
void usart1_tx_dma_enable(uint8_t *data, uint16_t len)
{
    //disable DMA
    //ʧЧDMA
    __HAL_DMA_DISABLE(&hdma_usart1_tx);

    while(hdma_usart1_tx.Instance->CR & DMA_SxCR_EN)
    {
        __HAL_DMA_DISABLE(&hdma_usart1_tx);
    }

    __HAL_DMA_CLEAR_FLAG(&hdma_usart1_tx, DMA_HISR_TCIF7);

    hdma_usart1_tx.Instance->M0AR = (uint32_t)(data);
    __HAL_DMA_SET_COUNTER(&hdma_usart1_tx, len);

    __HAL_DMA_ENABLE(&hdma_usart1_tx);
}

//2022.1.19���� �ӹٷ���������ֲ��USART1 DMA���ͣ��÷���printfһ��
void usart1_printf(const char *fmt,...)
{
    static uint8_t tx_buf[50] = {0};  //����ʹ��static
    static va_list ap;  //����ʹ��static
    static uint16_t len;  //����ʹ��static
    va_start(ap, fmt);
    //return length of string 
    //�����ַ�������
    len = vsprintf((char *)tx_buf, fmt, ap);
    va_end(ap);
    usart1_tx_dma_enable(tx_buf, len);
}


//2022.1.19���� ���Ʒ���Ƶ��
/* ʹ��ɽ�������������ʾ����:
	usart1_debug("\x03\xFC%c%c%c\xFC\x03", data1, data2, data3); */
#define USART_DEBUG_SEND_PERIOD 50
void usart1_debug(const char *fmt,...)
{
		static uint32_t last_time = 0;
		uint32_t time = xTaskGetTickCount();
		if(time - last_time > USART_DEBUG_SEND_PERIOD)
		{
				static uint8_t tx_buf[50] = {0};
				static va_list ap;
				static uint16_t len;
				va_start(ap, fmt);
				//return length of string 
				//�����ַ�������
				len = vsprintf((char *)tx_buf, fmt, ap);
				va_end(ap);
				usart1_tx_dma_enable(tx_buf, len);
				last_time = time;
		}
}
	
void usart6_init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num)
{

    //enable the DMA transfer for the receiver and tramsmit request
    //ʹ��DMA���ڽ��պͷ���
    SET_BIT(huart6.Instance->CR3, USART_CR3_DMAR);
    SET_BIT(huart6.Instance->CR3, USART_CR3_DMAT);

    //enalbe idle interrupt
    //ʹ�ܿ����ж�
    __HAL_UART_ENABLE_IT(&huart6, UART_IT_IDLE);



    //disable DMA
    //ʧЧDMA
    __HAL_DMA_DISABLE(&hdma_usart6_rx);
    
    while(hdma_usart6_rx.Instance->CR & DMA_SxCR_EN)
    {
        __HAL_DMA_DISABLE(&hdma_usart6_rx);
    }

    __HAL_DMA_CLEAR_FLAG(&hdma_usart6_rx, DMA_LISR_TCIF1);

    hdma_usart6_rx.Instance->PAR = (uint32_t) & (USART6->DR);
    //memory buffer 1
    //�ڴ滺����1
    hdma_usart6_rx.Instance->M0AR = (uint32_t)(rx1_buf);
    //memory buffer 2
    //�ڴ滺����2
    hdma_usart6_rx.Instance->M1AR = (uint32_t)(rx2_buf);
    //data length
    //���ݳ���
    __HAL_DMA_SET_COUNTER(&hdma_usart6_rx, dma_buf_num);

    //enable double memory buffer
    //ʹ��˫������
    SET_BIT(hdma_usart6_rx.Instance->CR, DMA_SxCR_DBM);

    //enable DMA
    //ʹ��DMA
    __HAL_DMA_ENABLE(&hdma_usart6_rx);


    //disable DMA
    //ʧЧDMA
    __HAL_DMA_DISABLE(&hdma_usart6_tx);

    while(hdma_usart6_tx.Instance->CR & DMA_SxCR_EN)
    {
        __HAL_DMA_DISABLE(&hdma_usart6_tx);
    }

    hdma_usart6_tx.Instance->PAR = (uint32_t) & (USART6->DR);

}



void usart6_tx_dma_enable(uint8_t *data, uint16_t len)
{
    //disable DMA
    //ʧЧDMA
    __HAL_DMA_DISABLE(&hdma_usart6_tx);

    while(hdma_usart6_tx.Instance->CR & DMA_SxCR_EN)
    {
        __HAL_DMA_DISABLE(&hdma_usart6_tx);
    }

    __HAL_DMA_CLEAR_FLAG(&hdma_usart6_tx, DMA_HISR_TCIF6);

    hdma_usart6_tx.Instance->M0AR = (uint32_t)(data);
    __HAL_DMA_SET_COUNTER(&hdma_usart6_tx, len);

    __HAL_DMA_ENABLE(&hdma_usart6_tx);
}

