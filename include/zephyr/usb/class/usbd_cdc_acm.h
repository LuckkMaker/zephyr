/*
 * Copyright (c) 2026 LuckkMaker
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief USBD CDC ACM optional RX packet callback API
 *
 * When CONFIG_USBD_CDC_ACM_RX_PACKET_CALLBACK is enabled, applications can
 * register a callback to receive each Bulk OUT transfer as one packet
 * (data + length), similar to DAP backend packet delivery, instead of
 * reading a byte stream from the UART ring buffer.
 */

#ifndef ZEPHYR_INCLUDE_USB_CLASS_USBD_CDC_ACM_H_
#define ZEPHYR_INCLUDE_USB_CLASS_USBD_CDC_ACM_H_

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CONFIG_USBD_CDC_ACM_RX_PACKET_CALLBACK)

/**
 * @brief RX packet callback type.
 *
 * Invoked from USB stack context when a Bulk OUT transfer completes.
 * @p data and @p len are valid only until the callback returns; the caller
 * must copy the packet if needed.
 *
 * @param dev CDC ACM UART device (same as used with uart_* API).
 * @param data Pointer to the received packet payload.
 * @param len Packet length in bytes.
 * @param user_data User pointer passed to usbd_cdc_acm_register_rx_packet_cb().
 */
typedef void (*usbd_cdc_acm_rx_packet_cb_t)(const struct device *dev,
					   const uint8_t *data, size_t len,
					   void *user_data);

/**
 * @brief Register optional RX packet callback for CDC ACM device.
 *
 * When a non-NULL callback is registered, each completed Bulk OUT transfer
 * is delivered to @p cb with (data, len); nothing is pushed to the UART
 * ring buffer. Pass NULL to revert to normal ring-buffer behaviour.
 *
 * @param dev CDC ACM UART device (e.g. from device_get_binding("CDC_ACM_0")).
 * @param cb Callback to invoke per packet, or NULL to use ring buffer only.
 * @param user_data User pointer passed to @p cb.
 */
void usbd_cdc_acm_register_rx_packet_cb(const struct device *dev,
					usbd_cdc_acm_rx_packet_cb_t cb,
					void *user_data);

#endif /* CONFIG_USBD_CDC_ACM_RX_PACKET_CALLBACK */

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_USB_CLASS_USBD_CDC_ACM_H_ */
