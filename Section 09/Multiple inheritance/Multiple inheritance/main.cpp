#include <iostream>
#include <string>;

/*
* In Diamond inheritance, if the parent classes inherit in a normal way the grandfather class,
* in the grandson class there will be 2 instances of the grandparent class, and it can lead to 
* bugs and ambiguous behaviour.

* To prevent this and assure that in grandson class there will be only 1 instance of the grandfather class,
* we have to inherit in the parent classes the grandfather classes with the virtual 
* keyword and, in the grandson class, specify explicitly the parametrized constructor of the grandfather
* class. If it's not explicitly specified, the default constructor of the grandfather class will be invoked.
* 
* Ideally, the constructors in the grandson class should be called in the same order as they were inherited, but
* the compiler will give them the correct order.
* 
* Inheriting as virtual makes no difference of use in the parent classes.
*/

class Stream {
	std::string m_fileName;
public:
	Stream(const std::string& filename): m_fileName(filename) {
		std::cout << "Stream(const std::string& filename)" << std::endl;
	}
	const std::string& GetFileName() const { return m_fileName; }
	~Stream(){
		std::cout << "~Stream()" << std::endl;
	}
};

class OutputStream : public virtual Stream {
	std::ostream& out;
public:
	OutputStream(std::ostream& o, const std::string& filename) : Stream(filename), out(o) {
		std::cout << "OutputStream(std::ostream& o, const std::string& filename)" << std::endl;
	}
	std::ostream& operator <<(const std::string& data) {
		out << data;
		return out;
	}
	~OutputStream() {
		std::cout << "~OutputStream()" << std::endl;
	}
};

class InputStream : public virtual Stream {
	std::istream& in;
public:
	InputStream(std::istream& i, const std::string& filename) : Stream(filename), in(i) {
		std::cout << "InputStream(std::istream& i, const std::string& filename)" << std::endl;
	}
	std::istream & operator >> (std::string& data) {
		in >> data;
		return in;
	}
	~InputStream() {
		std::cout << "~InputStream()" << std::endl;
	}
};

class IOStream : public OutputStream, public InputStream {
public:
	IOStream(std::ostream &o, std::istream &i, const std::string & filename): InputStream(i, filename), OutputStream(o, filename), Stream(filename) {
		std::cout << "IOStream(std::ostream &o, std::istream &i, const std::string & filename)" << std::endl;
	}
	~IOStream() {
		std::cout << "~IOStream()" << std::endl;
	}
};

int main() {
	std::string doc = "HelloDoc.txt";

	OutputStream out(std::cout, doc);
	std::cout << "/////////////////////" << std::endl;
	InputStream in(std::cin, doc);
	std::cout << "/////////////////////" << std::endl;
	IOStream inout(std::cout, std::cin, doc);

	std::string data;
	inout >> data;
	inout << data << std::endl;
	inout << inout.GetFileName() << std::endl;
	return 0;
}