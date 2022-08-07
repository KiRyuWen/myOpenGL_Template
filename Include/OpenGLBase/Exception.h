#pragma once
#include "./OpenGLBase.h"

namespace OpenGLBase {
	class Exception {
	private:
		typedef std::string string;
		string message;
	public:
		explicit Exception(const string& _message) :message(_message) {}
		virtual const char* what() { return this->message.c_str(); }
		virtual ~Exception() = default;
	};

	class NotImplement :public Exception {
		using Exception::Exception; //c++ support for super class constructor 
	public:
		static void Print() {
			printf("This is not implemeneted\n");
			throw "Not Implemented\n";
		}

	};
	class NotItialized :public Exception {
		using Exception::Exception; //c++ support for super class constructor 
	public:
		static void Print() {
			printf("This is not Initialize\n");
			throw "Not Initialize\n";
		}

	};
}