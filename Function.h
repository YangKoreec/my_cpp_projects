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
	/// ��������� �������� ��������� ������� ��� ��������� ��������
	/// </summary>
	/// <param name="x"></param>
	/// <returns>���������� ���������� �������� �������(NULL � ������ ������)</returns>
	double NewValue(double x) {

		if (FunctionObjects::Constant) return y->FunctionValue();

		if (y) {
			FunctionObjects::x = x;

			y->F();
		}

		return y->FunctionValue();
	}

	/// <summary>
	/// ���������� ������� �������� �������(NULL �� ���������)
	/// </summary>
	/// <returns></returns>
	double OldValue() {

		return y->FunctionValue();
	}

	/// <summary>
	/// ������ ����� ������� ��� ������� ��� ������������
	/// </summary>
	/// <param name="F">- ��� ����� �������(�� ��������� ����� x)</param>
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
	/// ������� ������������ �������
	/// </summary>
	void DeletFunction() {

		if(y) y->DeleteAllObjs();

		y = nullptr;
	}
};