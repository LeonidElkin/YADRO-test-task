#include <iostream>
#include <filesystem>
#include <random>

#include "Tape.h"

template<size_t ram_limit>
uint32_t Tape<ram_limit>::initiate_tape_id() {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist;
	return dist(rng);
}

template<size_t ram_limit>
void Tape<ram_limit>::extract_page_from_ctx(const std::string &page_id) {
	std::fstream input_stream;
	input_stream.open("tmp/" + std::to_string(id) + "/tmp_tape" + page_id + ".tmp", std::ios::binary | std::ios::in);

	if (input_stream) {
		input_stream.read(reinterpret_cast<char *>(this->cells), sizeof(this->cells));
		input_stream.close();
	} else {
		throw std::runtime_error("Couldn't open the temporary tape file during extraction from the context\n");
	}
}

template<size_t ram_limit>
void Tape<ram_limit>::insert_page_to_ctx(const std::string &page_id) {
	std::fstream output_stream;
	output_stream.open("tmp/" + std::to_string(id) + "/tmp_tape" + page_id + ".tmp", std::ios::binary | std::ios::out);

	if (output_stream) {
		output_stream.write(reinterpret_cast<char *>(this->cells), sizeof(this->cells));
		output_stream.close();
	} else {
		throw std::runtime_error("Couldn't open the output tape file during insertion to the context\n");
	}
}

template<size_t ram_limit>
Tape<ram_limit>::Tape(size_t size) : id(initiate_tape_id()), current_position(0), size(size) {}

template<size_t ram_limit>
Tape<ram_limit>::Tape(const std::string &input_file, size_t size) : id(initiate_tape_id()), current_position(0),
																	size(size) {
	std::fstream input_stream;
	if (!std::filesystem::exists(input_file)) throw std::runtime_error("Incorrect input tape was given");
	input_stream.open(input_file, std::ios::binary | std::ios::in);
	int32_t buffer[ram_limit / 4];

	if (input_stream) {

		if (!std::filesystem::is_directory("tmp")) std::filesystem::create_directory("tmp/");
		std::filesystem::create_directory("tmp/" + std::to_string(id) + "/");

		for (int i = 0; !input_stream.eof(); i++) {
			input_stream.read(reinterpret_cast<char *>(buffer), ram_limit);
			if (i == 0) std::copy(std::begin(buffer), std::end(buffer), std::begin(this->cells));
			else insert_page_to_ctx(std::to_string(i));
			if (input_stream.eof() && this->size == 0) this->size = (i * ram_limit + input_stream.gcount()) / 4;
			if (i * ram_limit / 4 > size && size != 0) break;
		}

		input_stream.close();
	} else {
		throw std::runtime_error("Couldn't open the tape input file\n");
	}
}

template<size_t ram_limit>
Tape<ram_limit>::~Tape() {
	std::filesystem::remove_all("tmp/" + std::to_string(id));
	if (std::filesystem::is_empty("tmp")) std::filesystem::remove("tmp");
}

template<size_t ram_limit>
int32_t Tape<ram_limit>::read() const {
	return this->cells[this->current_position % (ram_limit / 4)];
}

template<size_t ram_limit>
void Tape<ram_limit>::write(int32_t new_value) {
	this->cells[this->current_position % (ram_limit / 4)] = new_value;
}

template<size_t ram_limit>
void Tape<ram_limit>::move_right() {
	size_t limit = ram_limit / 4;
	if (this->current_position == this->size - 1) {
		throw std::out_of_range("Tape position can't be more than size value\n");
	} else if (this->current_position % limit == limit - 1) {
		size_t page_id = this->current_position / limit;
		insert_page_to_ctx(std::to_string(page_id));
		page_id++;
		if (std::filesystem::exists("tmp/" + std::to_string(id) + "/tmp_tape" + std::to_string(page_id) + ".tmp")) {
			extract_page_from_ctx(std::to_string(page_id));
		}
	}
	this->current_position++;
}

template<size_t ram_limit>
void Tape<ram_limit>::move_left() {
	size_t limit = ram_limit / 4;
	if (this->current_position == 0) {
		throw std::out_of_range("Tape position can't be below zero\n");
	} else if (this->current_position % limit == 0) {
		size_t page_id = this->current_position / limit;
		insert_page_to_ctx(std::to_string(page_id));
		page_id--;
		if (std::filesystem::exists("tmp/" + std::to_string(id) + "/tmp_tape" + std::to_string(page_id) + ".tmp")) {
			extract_page_from_ctx(std::to_string(page_id));
		}
	}
	this->current_position--;
}

template<size_t ram_limit>
Tape<ram_limit> Tape<ram_limit>::algo() {
	//TODO: sort algo
	return Tape("dfjkd");
}

template<size_t ram_limit>
uint32_t Tape<ram_limit>::get_id() const {
	return this->id;
}

