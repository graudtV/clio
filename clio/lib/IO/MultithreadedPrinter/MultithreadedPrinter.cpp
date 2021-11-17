#include "MultithreadedPrinter.hpp"

namespace clio {

MultithreadedPrinter MultithreadedPrinter::cout(std::cout);
MultithreadedPrinter MultithreadedPrinter::cerr(std::cerr);

void MultithreadedPrinterEntry::flush() {
	std::lock_guard<std::mutex> lock(m_mutex);
	m_os << m_buf.str();
}

} // clio namespace end