#include <iostream>

class RingBuffer {
private:
	int16_t allocSize = 0;
	int16_t realSize = 0;
	char* buffer;
	char* firstEl;
	char* lastEl;

	char pop_drop() {
		char ch = *lastEl;
		*lastEl = '=';
		--realSize;
		return ch;
	}

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
		if (firstEl == buffer + allocSize)
			firstEl = buffer;

		if (realSize == 0) ++lastEl;

		if (firstEl == lastEl && realSize > 1) {
			++lastEl;
			if (lastEl == buffer + allocSize)
				lastEl = buffer;
		}
		*firstEl = ch;
		if (realSize < allocSize)
			++realSize;
	}

	char pop() {
		if (realSize == 0) return '=';
		if (realSize == 1) {
			char ch = pop_drop();
			return ch;
		}
		
		char ch = pop_drop();
		++lastEl;
		if (lastEl == buffer + allocSize)
			lastEl = buffer;
		return ch;
	}

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

	rb.print_buffer();
	std::cout << '\n';

	rb.pop();
	rb.pop();
	rb.pop();
	rb.pop();
	rb.pop();

	return 0;
}