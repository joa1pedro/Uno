#pragma once
#include <iostream>
#include <string>

class BaseComponent;
class Mediator {
public:
	virtual void Notify(BaseComponent* sender, std::string event) const = 0;
};