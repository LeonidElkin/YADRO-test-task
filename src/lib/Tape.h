#ifndef TAPE_H
#define TAPE_H

#include <cinttypes>
#include <fstream>

#define DEFAULT_RAM_LIMIT 400

template<size_t ram_limit = DEFAULT_RAM_LIMIT>
class Tape {
private:
	uint32_t id;
	size_t current_position;
	size_t size;
	int32_t cells[ram_limit / 4]{0};

	void insert_page_to_ctx(const std::string &page_id);

	void extract_page_from_ctx(const std::string &page_id);

	uint32_t initiate_tape_id();

public:
	explicit Tape(size_t size);

	explicit Tape(const std::string &input_file, size_t size = 0);

	~Tape();

	[[nodiscard]] int32_t read() const;

	[[nodiscard]] uint32_t get_id() const;

	[[nodiscard]] size_t get_current_position() const;

	[[nodiscard]] size_t get_size() const;

	void write(int32_t new_value);

	void move_right();

	void move_left();
};


#endif //TAPE_H
