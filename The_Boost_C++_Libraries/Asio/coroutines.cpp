#include <boost/asio/io_service.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <list>
#include <string>
#include <ctime>
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;

io_service ioservice;
tcp::endpoint tcp_endpoint{tcp::v4(), 2014};
tcp::acceptor tcp_acceptor{ioservice, tcp_endpoint};
std::list<tcp::socket> tcp_sockets;

void do_write(tcp::socket &tcp_socket, yield_context yield)
{
		std::time_t now = std::time(nullptr);
		std::string data = std::ctime(&now);
		async_write(tcp_socket, buffer(data), yield);
		tcp_socket.shutdown(tcp::socket::shutdown_send);
}

void do_accept(yield_context yield)
{
		for (int i = 0; i < 2; ++i)
		{
				std::cout << "i: " << i << std::endl;
				tcp_sockets.emplace_back(ioservice);
				tcp_acceptor.async_accept(tcp_sockets.back(), yield);
				std::cout << "before spawn " << std::endl;
				spawn(ioservice, [](yield_context yield) { do_write(tcp_sockets.back(), yield); });
				std::cout << "spawn return " << std::endl;
		}
}

int main()
{
		tcp_acceptor.listen();
		spawn(ioservice, do_accept);
		ioservice.run();
		return 0;
}
