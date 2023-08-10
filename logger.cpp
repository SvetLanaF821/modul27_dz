#include <iostream>
#include <chrono>
#include "logger.h"

Logger::Logger(const std::string& fileName) : _fileName(fileName)
{
	//открыть файл для чтения и записи
	_fileLog.open(fileName, std::ios::in | std::ios::out |std::ios::trunc);
	if (!_fileLog.is_open())
		std::cout << "ERROR: log file " << fileName << " did't opent\n";
}

Logger::~Logger()
{
	_fileLog.close();							//закрыть файл
}

//записать строку
void Logger::writeStr(const Message& message)
{
	_sharedMutex.lock();						//блокировать мьютекс
	_fileLog.seekp(0, std::ios::end);			//установить позицию в конец файла
	_fileLog << message << "\n";				//записать message в файл
	_sharedMutex.unlock();						//разблокировать мьютекс
}

//читать строку 
std::string Logger::readRow(int number)
{
	std::lock_guard<std::shared_mutex> lock(_sharedMutex);
	_fileLog.seekg(0, std::ios::beg);			//установить позицию в начало файла
	std::string row = "";
	int count = 1;
	while (!_fileLog.eof())						//поиск нужной строки в файле
	{
		getline(_fileLog, row);
		if (count == number) {
			return row;
		}
		count++;
	}
	return "";
}

//записать в файл
void Logger::write(int numberTh, const Message& message) {
	writeStr(message);							//записать строку в файл
	_sharedMutex.lock();						//блокировать мьютекс
	std::cout << numberTh << " write thread :\t" << message << "\n";
	_sharedMutex.unlock();						//разблокировать мьютекс
}

//прочитать из файла
void Logger::read(int number) {
	//сделать паузу, чтобы некоторые потоки-писатели успели что-то записать в файл
	std::this_thread::sleep_for(std::chrono::milliseconds(5));
	std::string row = readRow(number);		//прочитать строку из файла
	
	if (!row.empty()) {
		_sharedMutex.lock();
		std::cout << "read thread: " << number << " row - \t" << row << "\n";
		_sharedMutex.unlock();
	}
	else {
		_sharedMutex.lock();
		std::cout << "read thread: " << number << " row not found\n";
		_sharedMutex.unlock();
	}
}
