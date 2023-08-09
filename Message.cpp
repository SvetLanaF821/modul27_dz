#include "Message.h"

Message::Message(const std::string& sender, const std::string& receiver, const std::string& text) : _sender(sender), _receiver(receiver), _text(text) {}

Message::Message(const Message& other) : _sender(other._sender), _receiver(other._receiver), _text(other._text) {}

Message& Message::operator = (const Message& other) {

    if (this == &other) {
        return *this;
    }

    _sender = other._sender;                    
    _receiver = other._receiver;                
    _text = other._text;                        

    return *this;
}

std::fstream& operator >>(std::fstream& is, Message& obj) {
    is >> obj._sender;
    is >> obj._receiver;
    is.seekg(1, std::ios_base::cur);
    std::getline(is, obj._text);
    return is;
}

std::ostream& operator <<(std::ostream& os, const Message& obj) {
    os << obj._sender << " ";
    os << obj._receiver << " ";
    os << obj._text;
    return os;
}

const std::string& Message::getSender() const { return _sender; }
const std::string& Message::getReceiver() const { return _receiver; }