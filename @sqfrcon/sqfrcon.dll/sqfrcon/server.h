#pragma once

#include "package.h"

namespace sqfrcon
{
	class server
	{
	private:
		std::mutex mutex;
		std::condition_variable wd_wait;
		std::thread* wd_thread;
		std::string port;
		std::string ssl_certificate_path;
		bool running;
		bool responsive;
		struct mg_server *mongoose;
		concurrency::concurrent_queue<sqfrcon::package*> output_queue;
		concurrency::concurrent_unordered_map<size_t,sqfrcon::package*> input_storage;
		concurrency::concurrent_unordered_map<std::string, std::string> user_database;
		void server::sendHeaders(struct mg_connection *conn);
		static int event_handler(struct mg_connection *conn, enum mg_event ev);
		void watchdog();
		void queue(sqfrcon::package* pkg);
	public:
		server();
		~server();
		std::string request(std::string& input, size_t size);
		std::string store(std::string& input);
		void addUser(std::string user, std::string password);
		void responsiveCheck();
		void start();
		bool stop();
		void setPort(std::string sPort) { this->port = sPort; };
		void setSSLPath(std::string pSSL_certificate_path) { this->ssl_certificate_path = pSSL_certificate_path; };
	};
}
