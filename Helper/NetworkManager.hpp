#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <boost/asio.hpp>
#include <iostream>
#include <queue>
#include <string>
#include <array>
#include <memory>

class NetworkManager {
public:
    NetworkManager(boost::asio::io_context& io_context);
    void connect();
    void async_read_from_server();
    void async_write_to_server();

    // void read_from_server();
    void write_to_server();

private:
    void read_handler(const boost::system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<std::array<char, 128>> buffer);
    void write_handler(const boost::system::error_code& ec, std::size_t /*bytes_transferred*/, std::shared_ptr<std::string> /*message*/);

    boost::asio::ip::tcp::resolver resolver;
    boost::asio::ip::tcp::socket socket;
};

#endif