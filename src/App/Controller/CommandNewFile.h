#pragma once
#ifndef INCLUDED_COMMANDNEWFILE_H
#define INCLUDED_COMMANDNEWFILE_H

#include "Command.h"

class CommandNewFile : public Command
{
public:
	virtual ~CommandNewFile()= default;
	CommandNewFile()= default;

	void execute(CADFileManager& fileManager, ViewMediator& viewMediator) override;
};

#endif //  INCLUDED_COMMANDNEWFILE_H