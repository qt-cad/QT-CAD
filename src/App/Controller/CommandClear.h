#pragma once
#ifndef INCLUDED_COMMANDCLEAR_H
#define INCLUDED_COMMANDCLEAR_H

#include "Command.h"

class CommandClear : public Command
{
public:
	~CommandClear()= default;
	CommandClear()= default;

	void execute(Model& m, MainWindow& w) override;
};

#endif //  INCLUDED_COMMANDCLEAR_H