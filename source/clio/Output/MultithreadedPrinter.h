#pragma once

#include <iostream>
#include <sstream>
#include <thread>

namespace clio {

class MultithreadedPrinterEntry {
public:
	~MultithreadedPrinterEntry() { flush(); }

	template <class T>
	MultithreadedPrinterEntry&& operator << (T&& arg) && {
		m_buf << arg;
		return std::move(*this);
	}

	MultithreadedPrinterEntry&& operator << (std::ostream& (*manip)(std::ostream&)) && {
		m_buf << manip;
		return std::move(*this);
	}

private:
	std::ostream& m_os;
	std::mutex& m_mutex;
	std::ostringstream m_buf;

	void flush();
	MultithreadedPrinterEntry(std::ostream& os, std::mutex& mutex) : m_os(os), m_mutex(mutex) {}

	friend class MultithreadedPrinter;
};

/*  This class solves a problem of output lines splitting when
 * printing something in the same file from multiple threads
 *
 *  MultithreadedPrinter::operator ()() creates a temporary object,
 * which can be used like an ostream and which guarantees that
 * all values pipelined with operator << are printed one after one,
 * without any symbols between them from other threads
 *  For std::cout and std::cerr MultithreadedPrinter-s are already provided.
 *
 *  Caution (!): do not create multiple MultithreadedPrinter-s for
 * the same ostream object! In this case MultithreadedPrinter preserves
 * lines only inside each MultithreadedPrinter, but not between them.
 * Similarly, do not print anything to std::cout/std::cerr/any other file
 * directly, if some thread uses MultithreadedPrinter for it.
 */
class MultithreadedPrinter {
public:
	MultithreadedPrinter(std::ostream& os) : m_os(os) {}
	MultithreadedPrinterEntry operator() () { return { m_os, m_mutex }; }

	std::ostream& get_ostream() { return m_os; }

	static MultithreadedPrinter cout;
	static MultithreadedPrinter cerr;
private:
	std::ostream& m_os;
	std::mutex m_mutex;
};

} // clio namespace end