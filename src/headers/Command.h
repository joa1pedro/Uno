#pragma once
#include <memory>
#include "IExecutor.h"

class Command {
protected:
	std::shared_ptr<IExecutor> _executor;

public:
	Command() = default;
	Command(std::shared_ptr<IExecutor> executor) : _executor(executor) {}

	void SetExecutor(std::shared_ptr<IExecutor> executor) {
		_executor = executor;
	}

	virtual ~Command() {}

	virtual void Execute() const = 0;
};
