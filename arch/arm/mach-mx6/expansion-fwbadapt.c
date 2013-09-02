
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/delay.h>

#include <mach/common.h>
#include <mach/devices-common.h>
#include <mach/gpio.h>

#include "edm.h"

#define FWBADAPT_PRISM_IRQ edm_external_gpio[7]
#define FWBADAPT_PRISM_RESET edm_external_gpio[4]

static struct i2c_board_info fwbadapt_prism_i2c_data[] __initdata = {
	{
		I2C_BOARD_INFO("prism", 0x10),
		.flags = I2C_CLIENT_WAKE,
	},
};

static __init int fwbadapt_init(void) {
	gpio_direction_output(FWBADAPT_PRISM_RESET, 0);
	gpio_set_value(FWBADAPT_PRISM_RESET, 0);
	mdelay(50);
	gpio_set_value(FWBADAPT_PRISM_RESET, 1);
	gpio_direction_input(FWBADAPT_PRISM_IRQ);
	fwbadapt_prism_i2c_data[0].irq = gpio_to_irq(FWBADAPT_PRISM_IRQ);

	i2c_register_board_info(1, &fwbadapt_prism_i2c_data[0], 1);

	gpio_direction_input(edm_external_gpio[5]);
	gpio_direction_input(edm_external_gpio[2]);
	gpio_direction_input(edm_external_gpio[6]);
	gpio_direction_input(edm_external_gpio[3]);

	gpio_direction_input(edm_external_gpio[0]);
	gpio_direction_input(edm_external_gpio[1]);
	return 0;
}
subsys_initcall(fwbadapt_init);

static __exit void fwbadapt_exit(void) {
	/* Actually, this cannot be unloaded. Or loaded as a module..? */
} 
module_exit(fwbadapt_exit);

MODULE_DESCRIPTION("FWBADAPT expansion board driver");
MODULE_LICENSE("GPL");
