#include <iostream>

class RingBuffer {
private:
	int16_t allocSize = 0;
	int16_t realSize = 0;
	char* buffer;
	char* firstEl;
	char* lastEl;

public:
	RingBuffer(int32_t size) {
		buffer = new char[size];
		allocSize = size;

		firstEl = buffer;
		lastEl = buffer;
	}

	~RingBuffer() {
		delete[] buffer;
	}

	void push(const char& ch) {
		++firstEl;
		if (firstEl == buffer + allocSize) {
			firstEl = buffer;
		}
		if (firstEl == lastEl){
			++lastEl;
			if (lastEl == buffer + allocSize)
				lastEl = buffer;
		}
		*firstEl = ch;
		if (realSize < allocSize)
			++realSize;
	}

	/*char pop() {

	}*/

	void print_buffer() const {
		for (int i = 0; i < allocSize; ++i) {
			std::cout << i << ": " << buffer[i];
			if (buffer + i == firstEl)
				std::cout << "  --< first";
			if (buffer + i == lastEl)
				std::cout << "  --< last";
			std::cout << '\n';
		}
	}

};


int main() {
	RingBuffer rb = RingBuffer(5);
	rb.print_buffer();
	std::cout << '\n';

	rb.push('k');
	rb.push('g');
	rb.push('e');
	rb.push('a');
	rb.push('b');
	rb.push('c');
	rb.push('d');
	rb.push('d');
	rb.push('d');
	rb.push('d');

	rb.print_buffer();

	return 0;
}