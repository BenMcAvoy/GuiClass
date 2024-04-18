#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>

#include "process.h"

namespace globals {
	bool shouldExit = false;

	Process emptyProcess = Process(
		"Select a process",
		0,
		nullptr
	);

	Process process = emptyProcess;

	std::vector<Process> processList;
}

#endif // GLOBALS_H
