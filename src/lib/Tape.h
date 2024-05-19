#ifndef YADRO_TEST_TASK_TAPE_H
#define YADRO_TEST_TASK_TAPE_H

#include <cinttypes>
#include <fstream>

#define M 100

class Tape {
	uint32_t id;
	size_t current_position;
	int32_t cells[M]{0};
public:
	explicit Tape();

	explicit Tape(const std::string& input_file);

	[[nodiscard]] int32_t read() const;

	void write(int32_t new_value);

	void move_right();

	void move_left();

	void algo();
};


#endif //YADRO_TEST_TASK_TAPE_H
