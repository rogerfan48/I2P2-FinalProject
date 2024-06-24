#include "Helper/NetworkManager.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <queue>
#include <string>
#include <array>
#include <memory>

#include "Scene/LobbyScene.hpp"
#include "Scene/PlayScene.hpp"

NetworkManager::NetworkManager(boost::asio::io_context& io_context)
    : resolver(io_context), socket(io_context) {}

void NetworkManager::connect() {
    auto endpoints = resolver.resolve("1.34.203.40", "11113");
    boost::asio::async_connect(socket, endpoints,
        [&](const boost::system::error_code& ec, const boost::asio::ip::tcp::endpoint&) {
            if (!ec) {
                std::cout << "Connected successfully" << std::endl;
                async_read_from_server();
            } else {
                std::cerr << "Connect failed: " << ec.message() << std::endl;
            }
        });
}

void NetworkManager::disconnect() {
    socket.close();
    std::cout << "Disconnected" << std::endl;
}

// void NetworkManager::read_from_server() {
//     try {
//         PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
//         std::array<char, 128> buffer;
//         std::cout << "Reading from server..." << std::endl;
//         std::size_t bytes_transferred = socket.read_some(boost::asio::buffer(buffer));
//         std::string data(buffer.data(), bytes_transferred);
//         std::cout << "Received: " << data << std::endl;
//         PS->commandFromServer.push(data);
//     } catch (std::exception& e) {
//         std::cerr << "Read failed: " << e.what() << std::endl;
//     }
// }

void NetworkManager::write_to_server() {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    if (!PS->commandToServer.empty()) {
        try {
            std::string message = PS->commandToServer.front();
            PS->commandToServer.pop();
            std::cout << "Writing to server: " << message << std::endl;
            boost::asio::write(socket, boost::asio::buffer(message));
            std::cout << "Sent: " << message << std::endl;
        } catch (std::exception& e) {
            std::cerr << "Write failed: " << e.what() << std::endl;
        }
    }
}

void NetworkManager::async_read_from_server() {
    auto buffer = std::make_shared<std::array<char, 128>>();
    socket.async_read_some(boost::asio::buffer(*buffer),
        [this, buffer](const boost::system::error_code& ec, std::size_t bytes_transferred) {
            read_handler(ec, bytes_transferred, buffer);
        });
}

void NetworkManager::async_write_to_server() {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    if (!PS->commandToServer.empty()) {
        auto message = std::make_shared<std::string>(PS->commandToServer.front());
        PS->commandToServer.pop();
        boost::asio::async_write(socket, boost::asio::buffer(*message),
            [this, message](const boost::system::error_code& ec, std::size_t bytes_transferred) {
                write_handler(ec, bytes_transferred, message);
            });
    }
}
void NetworkManager::read_handler(const boost::system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<std::array<char, 128>> buffer) {
    if (!ec) {
        PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
        std::string data(buffer->data(), bytes_transferred);
        if (data[0] == '!')  {
            LobbyScene* LS = dynamic_cast<LobbyScene*>(Engine::GameEngine::GetInstance().GetScene("lobby"));
            LS->pairSuccessfully = true;
        } else if (data[0] == '?') {
            socket.close();
            PS->commandFromServer.push(data);   // TODO: 對手已離線
        } else PS->commandFromServer.push(data);
        async_read_from_server(); // 再次啟動讀操作
    } else {
        std::cerr << "Read failed: " << ec.message() << std::endl;
    }
}

void NetworkManager::write_handler(const boost::system::error_code& ec, std::size_t /*bytes_transferred*/, std::shared_ptr<std::string> /*message*/) {
    if (ec) {
        std::cerr << "Write failed: " << ec.message() << std::endl;
    }
}