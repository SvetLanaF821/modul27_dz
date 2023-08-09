#pragma once

#include <string>
#include <fstream>
#include <shared_mutex>
#include "Message.h"

class Logger
{
	std::string _fileName;								//имя файла
	std::fstream _fileLog;								//файл логов
	std::shared_mutex _sharedMutex;						//мьютекс

public:
	Logger(const std::string& fileLog);
	~Logger();

	void writeStr(const Message& message);				//записать строку 
	std::string readRow(int number);					//прочитать строку

	void write(int numberTh, const Message& message);	//записать в файл
	void read(int number);								//прочитать из файла
};