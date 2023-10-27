#include "bsp_spi.h"
#include "bsp_usart.h"
#include "main.h"

/**extern SPI_HandleTypeDef hspi1;*/
/**extern DMA_HandleTypeDef hdma_spi1_rx;*/
/**extern DMA_HandleTypeDef hdma_spi1_tx;*/

void SPI1_DMA_init(uint32_t tx_buf, uint32_t rx_buf, uint16_t num)
{
		/**SET_BIT(hspi1.Instance->CR2, SPI_CR2_TXDMAEN);*/
    /**SET_BIT(hspi1.Instance->CR2, SPI_CR2_RXDMAEN);*/
		LL_SPI_EnableDMAReq_RX(SPI1);
		LL_SPI_EnableDMAReq_TX(SPI1);

    /**__HAL_SPI_ENABLE(&hspi1);*/
		LL_SPI_Enable(SPI1);


    //disable DMA
    //失效DMA (rx)
		/**__HAL_DMA_DISABLE(&hdma_spi1_rx);*/
		LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_2);

    /**while(hdma_spi1_rx.Instance->CR & DMA_SxCR_EN)*/
    while(LL_DMA_IsEnabledStream(DMA2, LL_DMA_STREAM_2))
    {
        /**__HAL_DMA_DISABLE(&hdma_spi1_rx);*/
				LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_2);
    }

		// FIXME:
		/**__HAL_DMA_CLEAR_FLAG(&hdma_spi1_rx, DMA_LISR_TCIF2);*/
		WRITE_REG(DMA2->LIFCR, DMA_LISR_TCIF2);

    /**hdma_spi1_rx.Instance->PAR = (uint32_t) & (SPI1->DR);*/
		LL_DMA_SetPeriphAddress(DMA2, LL_DMA_STREAM_2, (uint32_t) & (SPI1->DR));

    //memory buffer 1
    //内存缓冲区1
    /**hdma_spi1_rx.Instance->M0AR = (uint32_t)(rx_buf);*/
		LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_2, (uint32_t)(rx_buf));

    //data length
    //数据长度
		/**__HAL_DMA_SET_COUNTER(&hdma_spi1_rx, num);*/
		LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_2, num);

    /**__HAL_DMA_ENABLE_IT(&hdma_spi1_rx, DMA_IT_TC);*/
		LL_DMA_EnableIT_TC(DMA2, LL_DMA_STREAM_2);
		LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_2);

		LL_SPI_EnableDMAReq_RX(SPI1);


    //disable DMA
    //失效DMA (tx)
		LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_3);

    /**while(hdma_spi1_tx.Instance->CR & DMA_SxCR_EN)*/
    while(LL_DMA_IsEnabledStream(DMA2, LL_DMA_STREAM_3))
    {
        /**__HAL_DMA_DISABLE(&hdma_spi1_tx);*/
				LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_3);
    }

		// FIXME:
    /**__HAL_DMA_CLEAR_FLAG(&hdma_spi1_tx, DMA_LISR_TCIF3);*/
		WRITE_REG(DMA2->LIFCR, DMA_LISR_TCIF3);

    /**hdma_spi1_tx.Instance->PAR = (uint32_t) & (SPI1->DR);*/
		LL_DMA_SetPeriphAddress(DMA2, LL_DMA_STREAM_3, (uint32_t) & (SPI1->DR));
    //memory buffer 1
    //内存缓冲区1
    /**hdma_spi1_tx.Instance->M0AR = (uint32_t)(tx_buf);*/
		LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_3, (uint32_t)(tx_buf));
    //data length
    //数据长度
    /**__HAL_DMA_SET_COUNTER(&hdma_spi1_tx, num);*/
		LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_3, num);
		LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_3);
}

void SPI1_DMA_enable(uint32_t tx_buf, uint32_t rx_buf, uint16_t ndtr)
{
    /**__HAL_DMA_DISABLE(&hdma_spi1_rx);*/
		/**__HAL_DMA_DISABLE(&hdma_spi1_tx);*/
		LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_2);
		LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_3);


    /**while(hdma_spi1_rx.Instance->CR & DMA_SxCR_EN)*/
    /**{*/
    /**    __HAL_DMA_DISABLE(&hdma_spi1_rx);*/
    /**}*/
    /**while(hdma_spi1_tx.Instance->CR & DMA_SxCR_EN)*/
    /**{*/
    /**    __HAL_DMA_DISABLE(&hdma_spi1_tx);*/
    /**}*/
    while(LL_DMA_IsEnabledStream(DMA2, LL_DMA_STREAM_2))
    {
        /**__HAL_DMA_DISABLE(&hdma_spi1_rx);*/
				LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_2);
    }
    while(LL_DMA_IsEnabledStream(DMA2, LL_DMA_STREAM_3))
    {
        /**__HAL_DMA_DISABLE(&hdma_spi1_tx);*/
				LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_3);
    }

		/**__HAL_DMA_CLEAR_FLAG (hspi1.hdmarx, __HAL_DMA_GET_TC_FLAG_INDEX(hspi1.hdmarx));*/
		/**__HAL_DMA_CLEAR_FLAG (hspi1.hdmarx, __HAL_DMA_GET_HT_FLAG_INDEX(hspi1.hdmarx));*/
    /**__HAL_DMA_CLEAR_FLAG (hspi1.hdmarx, __HAL_DMA_GET_TE_FLAG_INDEX(hspi1.hdmarx));*/
    /**__HAL_DMA_CLEAR_FLAG (hspi1.hdmarx, __HAL_DMA_GET_DME_FLAG_INDEX(hspi1.hdmarx));*/
    /**__HAL_DMA_CLEAR_FLAG (hspi1.hdmarx, __HAL_DMA_GET_FE_FLAG_INDEX(hspi1.hdmarx));*/

    /**__HAL_DMA_CLEAR_FLAG (hspi1.hdmatx, __HAL_DMA_GET_TC_FLAG_INDEX(hspi1.hdmatx));*/
    /**__HAL_DMA_CLEAR_FLAG (hspi1.hdmatx, __HAL_DMA_GET_HT_FLAG_INDEX(hspi1.hdmatx));*/
    /**__HAL_DMA_CLEAR_FLAG (hspi1.hdmatx, __HAL_DMA_GET_TE_FLAG_INDEX(hspi1.hdmatx));*/
    /**__HAL_DMA_CLEAR_FLAG (hspi1.hdmatx, __HAL_DMA_GET_DME_FLAG_INDEX(hspi1.hdmatx));*/
    /**__HAL_DMA_CLEAR_FLAG (hspi1.hdmatx, __HAL_DMA_GET_FE_FLAG_INDEX(hspi1.hdmatx));*/

		LL_DMA_ClearFlag_TC2(DMA2);
		LL_DMA_ClearFlag_HT2(DMA2);
		LL_DMA_ClearFlag_TE2(DMA2);
		LL_DMA_ClearFlag_DME2(DMA2);
		LL_DMA_ClearFlag_FE2(DMA2);

		LL_DMA_ClearFlag_TC3(DMA2);
		LL_DMA_ClearFlag_HT3(DMA2);
		LL_DMA_ClearFlag_TE3(DMA2);
		LL_DMA_ClearFlag_DME3(DMA2);
		LL_DMA_ClearFlag_FE3(DMA2);

    /**hdma_spi1_rx.Instance->M0AR = rx_buf;*/
    /**hdma_spi1_tx.Instance->M0AR = tx_buf;*/
		LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_2, rx_buf);
		LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_3, rx_buf);

    /**__HAL_DMA_SET_COUNTER(&hdma_spi1_rx, ndtr);*/
    /**__HAL_DMA_SET_COUNTER(&hdma_spi1_tx, ndtr);*/
		LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_2, ndtr);
		LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_3, ndtr);

    /**__HAL_DMA_ENABLE(&hdma_spi1_rx);*/
    /**__HAL_DMA_ENABLE(&hdma_spi1_tx);*/
		LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_2);
		LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_3);
}

