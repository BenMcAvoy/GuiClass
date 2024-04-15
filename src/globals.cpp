#pragma once

#include "process.h"

namespace globals {
	bool shouldExit = false;

	Process emptyProcess = Process(
		"Select a process",
		0,
		nullptr
	);

	Process process = Process(
		emptyProcess.name,
		emptyProcess.pid,
		emptyProcess.handle
	);
}
