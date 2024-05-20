#ifndef YADRO_TEST_TASK_TAPESORT_H
#define YADRO_TEST_TASK_TAPESORT_H

#include "Tape.h"

template <size_t ram_limit = DEFAULT_RAM_LIMIT>
class TapeSort {
	Tape<ram_limit> input_tape;
public:
	explicit TapeSort(Tape<ram_limit> input_tape);

	Tape<ram_limit> sort();
};


#endif //YADRO_TEST_TASK_TAPESORT_H
