#include <iostream>
#include <filesystem>
#include <random>

#include "Tape.h"

uint32_t initiate_id() {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist;
	return dist(rng);
}

Tape::Tape() : id(initiate_id()), current_position(0) {}

Tape::Tape(const std::string &input_file) : id(initiate_id()), current_position(0) {
	std::fstream input_stream;
	input_stream.open(input_file, std::ios::binary | std::ios::in);
	int32_t buffer[M];

	if (input_stream) {

		if (!std::filesystem::is_directory("tmp")) std::filesystem::create_directory("tmp/");
		std::string this_tape_path = "tmp/" + std::to_string(id) + "/";
		std::filesystem::create_directory(this_tape_path);

		for (int i = 0; !input_stream.eof(); i++) {

			input_stream.read(reinterpret_cast<char *>(buffer), sizeof(buffer));
			if (i == 1) std::copy(std::begin(buffer), std::end(buffer), std::begin(this->cells));

			std::fstream output_stream;
			output_stream.open(this_tape_path + "tmp_tape" + std::to_string(i) + ".tmp",
							   std::ios::binary | std::ios::out);

			if (output_stream) {
				output_stream.write(reinterpret_cast<char *>(buffer), sizeof(buffer));
				output_stream.close();
			} else {
				throw std::runtime_error("Couldn't open the temporary output tape file\n");
			}

		}
		input_stream.close();
	} else {
		throw std::runtime_error("Couldn't open the tape input file\n");
	}
}

int32_t Tape::read() const {
	return this->cells[this->current_position];
}

void Tape::write(int32_t new_value) {
	this->cells[this->current_position] = new_value;
}

void Tape::move_right() {
	if (this->current_position % M == M - 1) {
		//Выгрузить эту страницу, загрузить другую
	}
	this->current_position++;
}

void Tape::move_left() {
	if (this->current_position == 0) {
		//Выгрузить эту страницу, загрузить другую
	} else {
		this->current_position--;
	}
}

void Tape::algo() {
	//Сортировка
}
