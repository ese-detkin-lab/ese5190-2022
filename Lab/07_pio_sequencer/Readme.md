## We made following Modifications:

### Modifications were made in the ws2812.pio file to read the boot pin using PIO.

### Assembly language code:

      .program bootpin
      set pindirs, 0
      .wrap_target
      label:
      in pins, 1
      push
      jmp label
      .wrap

### Added new function to initialize bootpin_program:

      static inline void bootpin_program_init(PIO pio, uint sm, uint offset, uint pin) {
      pio_sm_config c = bootpin_program_get_default_config(offset);
      sm_config_set_in_pins(&c, pin);
      sm_config_set_in_shift(&c, false, true, 0);
      pio_gpio_init(pio, pin);
      pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, false);
      pio_sm_init(pio, sm, offset, &c);
      pio_sm_set_enabled(pio, sm, true);
      }

### Modifications were made in the ws2812.c file to use these constructs:

We used pio_sm_get(pio,sm1) function instead of gpio_get(boot_pin) function.

## Output:
https://user-images.githubusercontent.com/73771085/202616164-590b2e2e-2b38-4916-8a20-9b2992f3571c.mp4

## Terminal:
![terminal](https://user-images.githubusercontent.com/73771085/202694841-183029a5-3e65-4429-a3c4-f12596d95814.jpeg)

## TXT File:
![txt file](https://user-images.githubusercontent.com/73771085/202694908-0164c075-3531-4e8a-8698-5e2536bf5f33.jpeg)

