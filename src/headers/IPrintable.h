#pragma once

class IPrintable
{
	virtual void Print() const = 0;
	virtual void PrintFromFile() const {};
};

