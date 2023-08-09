#pragma once

#include <string>
#include <fstream>

class Message
{
	std::string _sender;						//отправитель
	std::string _receiver;						//получатель
	std::string _text;							//текст сообщения

public:
	Message() = default;
	Message(const std::string& sender, const std::string& receiver, const std::string& text);
	~Message() = default;

	Message(const Message& other);
	Message& operator = (const Message& other);

	friend std::fstream& operator >>(std::fstream& is, Message& obj);
	friend std::ostream& operator <<(std::ostream& os, const Message& obj);

	const std::string& getSender() const;		//получить отправителя
	const std::string& getReceiver() const;		//получить получателя
};