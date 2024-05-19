#ifndef YADRO_TEST_TASK_TAPE_H
#define YADRO_TEST_TASK_TAPE_H

#include <cinttypes>
#include <fstream>

#define M 100

class Tape {
	size_t position{};
	int32_t cells[M]{};
public:
	explicit Tape() : position(0) {}

	explicit Tape(const std::string& input_file);

	[[nodiscard]] int32_t read() const;

	void write(int32_t new_value);

	void move_right();

	void move_left();

	void algo();
};


#endif //YADRO_TEST_TASK_TAPE_H
