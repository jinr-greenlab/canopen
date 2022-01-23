#include <can_header.h>

#if CHECK_VERSION(3, 0, 0)
//  CHECK_VERSION(2, 3, 0)
//  CHECK_VERSION(2, 2, 0)
//  CHECK_VERSION(2, 1, 1)
//  CHECK_VERSION(2, 0, 0)
//  CHECK_VERSION(1, 7, 0)

static unsigned16 red_msk_on, red_mask, red_phase, green_msk_on, green_mask, green_phase;
static int32 led_cnt, led_total;

static void set_led_counter(unsigned16 ms)
{
	led_total = 0;
	if (ms == 0) return;
	led_total = (int32)ms * 1000 / CAN_TIMERUSEC;
	if (led_total == 0) led_total = 1;
}

static void switch_leds(void)
{
#if CAN_LED_INDICATOR == SEPARATE
	if (red_phase & red_msk_on) red_led_on();
	else red_led_off();
	if (green_phase & green_msk_on) green_led_on();
	else green_led_off();
#else
	if (red_phase & red_msk_on) {
		green_led_off();
		red_led_on();
	} else {
		red_led_off();
		if (green_phase & green_msk_on) green_led_on();
		else green_led_off();
	}
#endif
	red_phase = (red_phase << 1) & red_mask;
	if (red_phase == 0) red_phase = 0x1;
	green_phase = (green_phase << 1) & green_mask;
	if (green_phase == 0) green_phase = 0x1;
}

void led_control(void)
{
	if (led_total == 0) return;
	led_cnt--;
	if (led_cnt <= 0) {
		led_cnt = led_total;
		switch_leds();
	}
}

void set_led_red_on(void)
{
	set_led_counter(200);
	red_mask = 0x1;
	red_msk_on = 0x1;
}

void set_led_green_on(void)
{
	set_led_counter(200);
	green_mask = 0x1;
	green_msk_on = 0x1;
}

void set_led_red_off(void)
{
	set_led_counter(200);
	red_mask = 0x1;
	red_msk_on = 0x0;
}

void set_led_green_off(void)
{
	set_led_counter(200);
	green_mask = 0x1;
	green_msk_on = 0x0;
}

void set_leds_flickering(void)
{
	set_led_counter(50);
	red_mask = 0x3;
	red_msk_on = 0x1;
	green_mask = 0x3;
	green_msk_on = 0x2;
}

void set_led_red_blinking(void)
{
	set_led_counter(200);
	red_mask = 0x3;
	red_msk_on = 0x1;
}

void set_led_green_blinking(void)
{
	set_led_counter(200);
	green_mask = 0x3;
	green_msk_on = 0x2;
}

void set_led_red_single_flash(void)
{
	set_led_counter(200);
	red_mask = 0x3F;
	red_msk_on = 0x1;
}

void set_led_green_single_flash(void)
{
	set_led_counter(200);
	green_mask = 0x3F;
	green_msk_on = 0x1;
}

void set_led_red_double_flash(void)
{
	set_led_counter(200);
	red_mask = 0xFF;
	red_msk_on = 0x5;
}

void set_led_green_double_flash(void)
{
	set_led_counter(200);
	green_mask = 0xFF;
	green_msk_on = 0x5;
}

void set_led_red_triple_flash(void)
{
	set_led_counter(200);
	red_mask = 0x3FF;
	red_msk_on = 0x15;
}

void set_led_green_triple_flash(void)
{
	set_led_counter(200);
	green_mask = 0x3FF;
	green_msk_on = 0x15;
}

void set_led_red_quadruple_flash(void)
{
	set_led_counter(200);
	red_mask = 0xFFF;
	red_msk_on = 0x55;
}

void set_led_green_quadruple_flash(void)
{
	set_led_counter(200);
	green_mask = 0xFFF;
	green_msk_on = 0x55;
}

void can_init_led_indication(void)
{
	led_total = 0;
	led_cnt = 0;
	red_phase = 0;
	red_msk_on = 0;
	red_mask = 0;
	green_phase = 0;
	green_msk_on = 0;
	green_mask = 0;
	switch_leds();
}

#endif
