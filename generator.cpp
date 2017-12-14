#include "generator.h"
#include "constantes.h"
#include "LCDC.h"
#include "LCDC_registermap.h"

using namespace std;
using namespace sc_core;

void generator::thread(void) {
	cout << name() << ": Generator starting" << endl;
	socket.write(addr_deb_LCDC + LCDC_ADDR_REG, addr_deb_video);
	socket.write(addr_deb_LCDC + LCDC_START_REG, 0x00000001);
	socket.write(addr_deb_LCDC + LCDC_INT_REG, 0x00000000);

	sc_time period(1.0 / 25, SC_SEC);
	ensitlm::data_t word;
	ensitlm::data_t output1;
	ensitlm::data_t output2;
	uint32_t mask;
	uint32_t pixel;
	uint32_t defilement(0);

	while (true) {
		wait(period);
		defilement++;

		for (int i = 0; i < size_rom / 4; i++) {
			socket.read(addr_deb_rom + i * 4, word);
			mask = 0xF0000000;
			output1 = 0x00000000;
			output2 = 0x00000000;
			for (int j = 0; j < 4; j++) {
				pixel = word & mask;
				output1 = output1 | (pixel >> j * 4);
				mask = mask >> 4;
			}
			for (int k = 0; k < 4; k++){
				pixel = word & mask;
				output2 = output2 | (pixel << (16 - k * 4));
				mask = mask >> 4;
			}
			socket.write(addr_deb_video + (i * 8 + defilement * 320) % IMG_SIZE, output1);
			socket.write(addr_deb_video + (i * 8 + 4 + defilement * 320) % IMG_SIZE, output2);
		}
		wait(int_event);
	}
}

void generator::method(void) {
	notify(int_event);
	socket.write(addr_deb_LCDC + LCDC_INT_REG, 0x00000000);
	cout << "Interruption notified" << endl;
}

generator::generator(sc_core::sc_module_name name) : sc_core::sc_module(name) {
	SC_THREAD(thread);
	SC_METHOD(method);
	sensitive << int_signal; 
}
