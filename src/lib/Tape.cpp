#include "Tape.h"

int32_t Tape::read() const {
	return this->cells[this->position];
}

void Tape::write(int32_t new_value) {
	this->cells[this->position] = new_value;
}

void Tape::move_right() {
	if (this->position == M - 1) {
		//Выгрузить это, загрузить другое
	} else {
		this->position++;
	}
}

void Tape::move_left() {
	if (this->position == 0) {
		//Выгрузить это, загрузить другое
	} else {
		this->position--;
	}
}

void Tape::algo() {
	//Сортировка
}

Tape::Tape(const std::string &input_file) {
	//конструктор от входной строки
}
