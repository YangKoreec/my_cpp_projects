#pragma once
#include "FunctionObjects.h"

class Function {

private:

	FunctionObjects::FunctionObject* y;
	string F;

public:

	Function() {

		y = nullptr;
		this->F = X;
	}

	Function(string F) {

		y = nullptr;
		this->F = F;

		MakeNewFunction(this->F);
	}

	/// <summary>
	/// Вычисляет значение введенной функции для задонного значения
	/// </summary>
	/// <param name="x"></param>
	/// <returns>Возвращает полученное значение функции(NULL в случае ошибки)</returns>
	double NewValue(double x) {

		if (FunctionObjects::Constant) return y->FunctionValue();

		if (y) {
			FunctionObjects::x = x;

			y->F();
		}

		return y->FunctionValue();
	}

	/// <summary>
	/// Возвращает прошлое значение функции(NULL по умолчанию)
	/// </summary>
	/// <returns></returns>
	double OldValue() {

		return y->FunctionValue();
	}

	/// <summary>
	/// Вводит новую функцию или заменят уже существующую
	/// </summary>
	/// <param name="F">- это новая функции(по умолчанию равна x)</param>
	void MakeNewFunction(string F = X) {

		if (y) {

			DeletFunction();

			this->F = F;
		}

		if (!y) y = new FunctionObjects::FunctionObject(1, Y, NOTH);

		y->Inteprer(this->F);

		if (FunctionObjects::Constant) y->F();
	}

	/// <summary>
	/// Удалаят существующую функцию
	/// </summary>
	void DeletFunction() {

		if(y) y->DeleteAllObjs();

		y = nullptr;
	}
};