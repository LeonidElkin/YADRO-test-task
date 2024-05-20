#include <iostream>

#include "TapeSort.h"

#define RAM_LIMIT 400

int main(int argc, char **argv) {

	if (argc != 3) throw std::runtime_error("There should be two arguments: input file and output file\n");

	std::string input_file = argv[1];
	std::string output_file = argv[2];

	auto input_tape = Tape<>(input_file);
	auto sorter = TapeSort<>(input_tape);

	auto output = sorter.sort();
	output.to_bin(output_file);

	return 0;
}
