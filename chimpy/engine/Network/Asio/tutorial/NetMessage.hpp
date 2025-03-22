#pragma once

#include "NetCommon.hpp"

namespace EngineG::Network{

// Message Header is sent at start of all messages
// The templates allows to use "enum class"
template<typename T>
struct MessageHeader{
    T id{};
    uint32_t size = 0;
};

template<typename T>
struct Message{
    MessageHeader<T> header{};
    std::vector<uint8_t> body;

    size_t size() const {
      return body.size();
    }

    friend std::ostream& operator<<(std::ostream& os, const Message<T>& msg) {
      os << "ID:" << int(msg.header.id) << " Size:" << msg.header.size();
      return os;
    }

    template<typename DataType>
    friend Message<T>& operator<<(Message<T>& msg, DataType& data) {
      static_assert(std::is_standard_layout<DataType>::value, "DataType must be standard layout! Its too complex to be pushed!");

      // Cache current size of vector, as it will be the point we insert the data
      size_t i = msg.body.size();

      // Resize the vector by the size of the data being pushed
      msg.body.resize(msg.body.size() + sizeof(DataType));

      // Physically copy the data into newly vector space
      std::memcpy(msg.body.data() + i, &data, sizeof(DataType));
      msg.header.size = msg.size();
      return msg;
    }

    template<typename DataType>
    friend Message<T>& operator>>(Message<T>& msg, DataType& data) {
      static_assert(std::is_standard_layout<DataType>::value, "DataType must be standard layout! Its too complex to be pushed!");

      size_t i = msg.body.size() - sizeof(DataType);
      std::memcpy(&data, msg.body.data() + i, sizeof(DataType));
      msg.body.resize(i);
      msg.header.size = msg.size();
      return msg;
    }
};

template<typename T>
class Connection;

template<typename T>
struct OwnedMessage
{
    std::shared_ptr<Connection<T>> remote = nullptr;
    Message<T> message;

    friend std::ostream& operator<<(std::ostream& os, const OwnedMessage<T>& msg)
    {
        os << msg.message;
        return os;
    }
};

enum class CustomMsgTypes: uint32_t
{
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage,
};

}