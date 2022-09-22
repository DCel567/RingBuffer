#include <iostream>

class RingBuffer {
private:
	int16_t bSize = 0;
	char* buffer;
	char* firstEl;
	char* lastEl;

public:
	RingBuffer(int32_t size) {
		buffer = new char[size];
		bSize = size;

		firstEl = buffer;
		lastEl = buffer;
	}

	~RingBuffer() {
		delete[] buffer;
	}

	void push(const char& ch) {
		*firstEl = ch;
		firstEl = firstEl + 1;
	}

	/*char pop() {

	}*/

	void print_buffer() const {
		for (int i = 0; i < bSize; ++i) {
			std::cout << i << ": " << buffer[i] << '\n';
		}
	}

};


int main() {
	RingBuffer rb = RingBuffer(10);
	rb.print_buffer();
	std::cout << '\n';

	rb.push('k');
	rb.push('g');
	rb.push('e');

	rb.print_buffer();

	return 0;
}