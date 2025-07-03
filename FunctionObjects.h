#pragma once
#include <string>
#include <cmath>

using std::string;

namespace FunctionObjects {

	double x = NULL;
	int AmountOfObjects = NULL;
	bool Constant = true;

	// Если деление на ноль то сравнить с INFINITY
	// Если sqrt или pow использовать функцию isnan()

#define Y "y"
#define X "x"
#define COS "cos"
#define SIN "sin"
#define LN "l"
#define COEF "("
#define DEG "^"
#define CONST "c"
#define NOTH "\0"
#define MUL "*"
#define ADD "+"
#define DIV "/"
#define SUB "-"
#define PI 3.14159265359
#define E 2.71828182845

/// <summary>
/// Это класс содеражащий всю информацию необходимую для получения результата функции
/// </summary>
	class FunctionObject {

	private:

		double total;
		double a;

		string Modifier;
		string Action;
		FunctionObject* Degree;
		FunctionObject* Coefficient;
		FunctionObject* MainSequence;
		FunctionObject* SideSequence;

		FunctionObject* MakeDegree(string F, int& i) {

			FunctionObject* NewDegree = new FunctionObject(1, COEF, NOTH);

			i = NewDegree->Inteprer(F, i) + 1;

			if (F[i] == '^' && F[i + 1]) {

				i += 2;
				NewDegree->Degree = new FunctionObject(1, COEF, NOTH);
				i = NewDegree->Degree->Inteprer(F, i) + 1;
			}

			return NewDegree;
		}

		FunctionObject* MakeCoefficient(double a, string F, int& i) {

			FunctionObject* NewCoefficient = new FunctionObject(a, COEF, NOTH);

			i = NewCoefficient->Inteprer(F, i) + 1;

			return NewCoefficient;
		}

		void MakeMainSequence(double a, string Modifier, string Action = NOTH) {

			this->MainSequence = new FunctionObject(a, Modifier, Action);
		}

		void MakeSideSequence(double a, string Modifier, string Action) {

			this->SideSequence = new FunctionObject(a, Modifier, Action);
		}

		void Parse(string F, double& a, string& Modifier, string& Action, int& i, FunctionObject** NewCoefficient, FunctionObject** NewDegree) {

			switch (F[i]) {
			case '+': Action = ADD; i++; break; // Action = "+"
			case '-': Action = SUB; i++; break; // Action = "-"
			case '*': Action = MUL; i++; break; // Action = "*"
			case '/': Action = DIV; i++; break; // Action = "/"
			}

			switch (F[i]) {

			case '-': case '.': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '0': a *= std::stof(&F[i]); i += strspn(&F.c_str()[i], ".0123456789");  break;
			}

			switch (F[i]) {

			case 'p': case 'P': if (F[i + 1] == 'i' || F[i + 1] == 'I') { a *= PI; i += 2; } break; // a = PI
			case 'e':case 'E': a *= E; i++; break; // a = E
			}

			switch (F[i]) {
			case '(': Modifier = COEF; i++; *NewCoefficient = MakeCoefficient(a, F, i); break;
			case 'x':case 'X': Modifier = X; i++; break; // Modifier = "x"
			case 'c':case'C': if ((F[i + 1] == 'o' || F[i + 1] == 'O') && (F[i + 2] == 's' || F[i + 2] == 'S')) { Modifier = COS; i += 3; } break; // Modifier = "c"
			case 's': case 'S': if ((F[i + 1] == 'i' || F[i + 1] == 'I') && (F[i + 2] == 'n' || F[i + 2] == 'N')) { Modifier = SIN; i += 3; } break; // Modifier = "s"
			case 'l': case 'L': if (F[i + 1] == 'n' || F[i + 1] == 'N') { Modifier = LN; i += 2; } break; // Modifier = "l"
			}

			if ((F[i] == '(') && (Modifier == SIN || Modifier == COS || Modifier == LN)) {

				i++;
				*NewCoefficient = MakeCoefficient(1, F, i);
			}

			if (F[i] == '^' && F[i + 1] == '(') { i += 2; *NewDegree = MakeDegree(F, i); }
		}

		void MakeTotal() {

			this->total = 1;

			if (Modifier == CONST) this->total *= abs(this->a);
			else
				switch (this->Modifier[0]) {

				case 'x': this->total *= x; break;
				case 'c': this->total *= cos(this->Coefficient->F()); break;
				case 's': this->total *= sin(this->Coefficient->F()); break;
				case '(': this->total *= this->Coefficient->F(); break;
				case 'l': this->total *= log(this->Coefficient->F()); break;
				}

				if (this->Degree) this->total = pow(this->total, this->Degree->F());

				if (this->Modifier == CONST && this->a < 0) this->total *= -1;

				if(this->Modifier != CONST) this->total *= a;

				if (Action == DIV) this->total = 1 / this->total;
		}

		double FunctionTotal() {

			this->MakeTotal();

			if (this->SideSequence) this->total = this->total * this->SideSequence->FunctionTotal();

			if (this->MainSequence) return this->total + this->MainSequence->FunctionTotal();
			else return this->total;
		}

	public:

		FunctionObject(double a, string Modifier, string Action) {

			this->total = NULL;

			this->a = a;
			this->Modifier = Modifier;
			this->Action = Action;

			this->Degree = nullptr;
			this->Coefficient = nullptr;
			this->MainSequence = nullptr;
			this->SideSequence = nullptr;

			FunctionObjects::AmountOfObjects++;
		}

		~FunctionObject() {

			FunctionObjects::AmountOfObjects--;
		}

		int Inteprer(string F, int i = 0) {

			double a = 1;
			string Action = NOTH;
			string Modifier = CONST;

			FunctionObject* LastMain = this;
			FunctionObject* LastObj = this;
			FunctionObject* NewCoefficient = nullptr;
			FunctionObject* NewDegree = nullptr;

			while ((i < F.size()) && ((this->Modifier == Y) || ((this->Modifier == COEF || this->Modifier == DEG) && F[i] != ')'))) {

				Parse(F, a, Modifier, Action, i, &NewCoefficient, &NewDegree);

				if (Modifier == X) Constant = false;

				if (Action == ADD || Action == SUB || Action == NOTH) {

					if (Action == SUB) a *= -1;

					LastMain->MakeMainSequence(a, Modifier, NOTH);

					if (NewCoefficient) {

						LastMain->MainSequence->Coefficient = NewCoefficient;
						NewCoefficient = nullptr;
					}
					if (NewDegree) {

						LastMain->MainSequence->Degree = NewDegree;
						NewDegree = nullptr;
					}

					LastMain = LastObj = LastMain->MainSequence;
				}

				if (Action == DIV || Action == MUL) {

					LastObj->MakeSideSequence(a, Modifier, Action);

					if (NewCoefficient) {

						LastObj->SideSequence->Coefficient = NewCoefficient;
						NewCoefficient = nullptr;
					}
					if (NewDegree) {

						LastObj->SideSequence->Degree = NewDegree;
						NewDegree = nullptr;
					}

					LastObj = LastObj->SideSequence;
				}

				Action = NOTH;
				Modifier = CONST;
				a = 1;
			}

			return i;
		}

		void DeleteAllObjs() {

			if (this->Degree) this->Degree->DeleteAllObjs();
			if (this->Coefficient) this->Coefficient->DeleteAllObjs();
			if (this->SideSequence) this->SideSequence->DeleteAllObjs();
			if (this->MainSequence)this->MainSequence->DeleteAllObjs();

			delete this;
		}

		double F() {

			this->total = 1;

			if (this->Modifier == Y || this->Modifier == COEF) {

				this->total = this->MainSequence->FunctionTotal();
			}

			if (this->Modifier == Y) {

				try {

					if (isnan(this->total) || this->total == INFINITY) throw(true);
				}
				catch (bool Error) {
					this->total = NULL;
				}
			}

			return this->total;
		}

		double FunctionValue() {

			return this->total;
		}
	};

	int UsedMemory() {

		return AmountOfObjects * sizeof(FunctionObject);
	}
}