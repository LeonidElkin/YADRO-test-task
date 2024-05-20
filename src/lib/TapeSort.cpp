#include "TapeSort.h"
#include <climits>

template<size_t ram_limit>
TapeSort<ram_limit>::TapeSort(Tape<ram_limit> input_tape) : input_tape(input_tape) {}

template<size_t ram_limit>
Tape<ram_limit> TapeSort<ram_limit>::sort() {
	size_t size_of_tape = this->input_tape.get_size();
	auto output_tape = Tape<ram_limit>(size_of_tape);
	while (this->input_tape.get_current_position() != 0) this->input_tape.move_left();
	size_t previous_min_pos = SIZE_MAX;
	int32_t previous_min = INT32_MIN;
	size_t weak_min_position = SIZE_MAX;
	for (int i = 0; i < size_of_tape; i++) {
		int32_t min = INT32_MAX;
		size_t min_position;
		for (int j = 0; j < size_of_tape; j++) {
			int32_t current_value = this->input_tape.read();
			size_t current_value_position = this->input_tape.get_current_position();
			if (i % 2 == 0) {
				if (current_value < min && current_value >= previous_min) {
					min = current_value;
					min_position = current_value_position;
				} else if (current_value == min && current_value_position > previous_min_pos) {
					previous_min_pos = SIZE_MAX;
					min_position = current_value_position;
				}
				try {
					this->input_tape.move_right();
				} catch (std::out_of_range &e) {}

			} else {
				if (current_value < min && current_value >= previous_min) {
					min = current_value;
					min_position = current_value_position;
					weak_min_position = SIZE_MAX;
				} else if (current_value == min && current_value_position > previous_min_pos &&
						   current_value >= previous_min) {
					weak_min_position = current_value_position;
				}
				if (j == size_of_tape - 1 && weak_min_position != SIZE_MAX) {
					min_position = weak_min_position;
				}
				try {
					this->input_tape.move_left();
				} catch (std::out_of_range &e) {}
			}

		}

		output_tape.write(min);
		try {
			output_tape.move_right();
		} catch (std::out_of_range &e) {
			//sorted
		}

		previous_min = min;
		previous_min_pos = min_position;
	}
}
