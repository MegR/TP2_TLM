#include <systemc.h>
#include "ensitlm.h"
#include "generator.h"
#include "memory.h"
#include "bus.h"
#include "LCDC.h"
#include "constantes.h"
#include "ROM.h"


int sc_main(int argc, char **argv) {
	sc_time period(1.0 / 25, SC_SEC);
	generator g("Generator1");
	Bus router("Bus");
	Memory m("Memory", size_memory);
	LCDC controller("controller_LCDC", period);
	sc_signal <bool, SC_MANY_WRITERS> irq_signal("IRQ");
	ROM rom("mem_rom");

	g.socket.bind(router.target);
	router.initiator.bind(m.target);
	router.map(m.target, addr_deb_memory, size_memory);

	router.initiator.bind(rom.socket);
	router.map(rom.socket, addr_deb_rom, size_rom);
    

	controller.initiator_socket.bind(router.target);

	router.initiator.bind(controller.target_socket);
	router.map(controller.target_socket, addr_deb_LCDC, size_LCDC);

	controller.display_int(irq_signal);
	g.int_signal(irq_signal);

	sc_core::sc_start();

	return 0;
}
