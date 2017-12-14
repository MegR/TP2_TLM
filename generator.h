#include "ensitlm.h"
#include "bus.h"

using namespace sc_core;

struct generator : sc_core::sc_module {
	ensitlm::initiator_socket<generator> socket;
	sc_core::sc_in<bool> int_signal;
	sc_core::sc_event int_event;

	void thread(void);
	void method(void);
	SC_CTOR(generator);
};
