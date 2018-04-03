#pragma once
#ifndef INCLUDED_COMMANDLOADFILE_H
#define INCLUDED_COMMANDLOADFILE_H

#include "Command.h"

class CommandLoadFile : public Command
{
public:
	~CommandLoadFile()= default;
	CommandLoadFile()= default;

	void execute(Model& m, MainWindow& w) override;
};

#endif //  INCLUDED_COMMANDLOADFILE_H