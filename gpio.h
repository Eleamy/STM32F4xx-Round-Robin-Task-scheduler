#ifndef gpio_h
#define gpio_h

/*includes*/

#include "std_types.h"
#include "common_macros.h"
#include "stm32f4xx.h"

/*macros*/
#define IS_GPIOx(GPIOx) ((GPIOx == GPIOA) ? 1 : (GPIOx == GPIOB) ? 2 \
                                                                 : 0)

/*data types*/
typedef enum gpioMode
{
    input,
    output,
    alternate_function,
    Analogue
} gpioMode;

typedef enum gpioType
{
    push_pull,
    open_drain
} gpioType;

typedef enum gpioPort
{
    portA,
    portB,
} port;

typedef enum gpioSpeed
{
    low_speed,
    mediuem_speed,
    high_speed,
    very_high_speed
} gpioSpeed;

typedef enum gpioPullDir
{
    no_pull,
    pull_up,
    pull_down
} gpioPullDir;

typedef enum pin
{
    pin_0,
    pin_1,
    pin_2,
    pin_3,
    pin_4,
    pin_5,
    pin_6,
    pin_7,
    pin_8,
    pin_9,
    pin_10,
    pin_11,
    pin_12,
    pin_13,
    pin_14,
    pin_15
} pin;

typedef enum pinState
{
    low,
    high,
} pinState;

typedef enum
{
    AF0,
    AF1,
    AF2,
    AF3,
    AF4,
    AF5, // SPI1..4
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15
} AFType;

typedef struct gpioInitStruct
{
    port port;
    pin pin;
    gpioMode mode; /*input-output, alternate*/
    gpioType type; /*push_pull, open_drain*/
    gpioSpeed speed;
    gpioPullDir dir; /*pullup, pulldown, no_pull*/
} gpioInitStruct;

/*fuction prtotypes*/

/*gpio_init(): initialize a port using gpioInitStruct*/
void gpio_setup_pin(GPIO_TypeDef *GPIOx, pin pin, gpioSpeed speed, gpioMode mode, gpioType type, gpioPullDir direction);
void gpio_set_mode(GPIO_TypeDef *GPIOx, gpioMode mode, pin pin);
void gpio_set_output_speed(GPIO_TypeDef *GPIOx, gpioSpeed speed, pin pin);
void gpio_set_output_type(GPIO_TypeDef *GPIOx, gpioType type, pin pin);
void gpio_set_pull_direction(GPIO_TypeDef *GPIOx, gpioPullDir pullDir, pin pin);
void gpio_toggle_pin(port port, pin pin);
void gpio_write_pin(port port, pin pin, pinState state);
pinState gpio_read_pin(port port, pin pin);
void gpio_setup_AF(GPIO_TypeDef *GPIOx, pin pin, AFType af);
uint8 gpio_is_input_set(port port, pin pin);
#endif