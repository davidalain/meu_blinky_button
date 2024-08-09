/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   10

/**
 * See: ~\zephyrproject\zephyr\boards\st\nucleo_f303re\nucleo_f303re.dts 
 * 
 * Alias for 'led0' and 'sw0' are defined there.
 */
static const struct gpio_dt_spec led = 
	GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

static const struct gpio_dt_spec button = 
	GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);

int main(void)
{
	int ret;

	if (!gpio_is_ready_dt(&led)) {
		return 0;
	}

	if (!gpio_is_ready_dt(&button)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret < 0) {
		return 0;
	}

	while (1) {
		int v = gpio_pin_get_dt(&button);
		
		gpio_pin_set_dt(&led, v);

		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
