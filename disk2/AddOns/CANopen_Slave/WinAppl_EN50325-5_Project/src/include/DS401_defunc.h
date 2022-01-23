#ifndef __DS401_DEFUNC_H__
#define __DS401_DEFUNC_H__

// ..application/DS401_standev.c functions
void process_digital_input(unsigned8 blk, unsigned8 data);
void process_analog_input(unsigned8 chan, int32 data);
void write_digital_output(unsigned8 blk);
void write_analog_output(unsigned8 chan);
unsigned8 read_digital_output_0(void);

// ..application/DS401_manspec.c functions
void process_logical_counter(unsigned8 lcc);
void write_digital_counter(unsigned8 chan, unsigned32 data);
void application_manspec_timer(void);
void control_digital_outputs(void);
void control_analog_outputs(void);
unsigned8 read_int_enable_counter(void);

// ..application/DS401_control.c functions
void print_appl(void *fmt, ...);
void consume_time(canframe *cf);
void reset_emulated_counter(unsigned8 chan, unsigned32 val);
void set_transmit_pdo(canindex index);

#endif
