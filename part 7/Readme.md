# TODO: #
* modify your sequencer to use the PIO as its primary I/O engine, including the ability to R/W any register

# Pio Sequencer #

We modified the ws2812.pio file to read the boot pin using PIO, added new function to initialize bootpin_program. Some other modifications were made in the ws2812.c file to use these constructs: pio_sm_get(pio,sm1) function instead of gpio_get(boot_pin) function.

### Assembly language code:

      .program bootpin
      set pindirs, 0
      .wrap_target
      label:
      in pins, 1
      push
      jmp label
      .wrap

### function to initialize bootpin_program:

      static inline void bootpin_program_init(PIO pio, uint sm, uint offset, uint pin) {
      pio_sm_config c = bootpin_program_get_default_config(offset);
      sm_config_set_in_pins(&c, pin);
      sm_config_set_in_shift(&c, false, true, 0);
      pio_gpio_init(pio, pin);
      pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, false);
      pio_sm_init(pio, sm, offset, &c);
      pio_sm_set_enabled(pio, sm, true);
      }
      
# Output: #

As explained in earlier part 3 a text file will be generated as shown below: 

<img width="600" alt="7b" src="https://user-images.githubusercontent.com/114259992/202722487-b54210df-3cc8-40a1-a2c1-6509970ea33b.png">

The output terminal will be as follow:

<img width="523" alt="7a" src="https://user-images.githubusercontent.com/114259992/202722457-e5e41178-6d88-4288-b652-17abe874a045.png">

Output Video:

https://user-images.githubusercontent.com/73771085/202616164-590b2e2e-2b38-4916-8a20-9b2992f3571c.mp4

