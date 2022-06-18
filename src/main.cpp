#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// O Target define a interface específica do domínio usada pelo código do cliente.
class Target {
public:
	virtual ~Target() = default;

	virtual string Requisicao() {
		return "Target: Quando se utiliza diretamente o target";
	}
};

/**
 * A classe Exemplo contém algum comportamento útil, mas sua interface é
 * incompatívelcom o código do cliente existente. A classe Exemplo precisa de
 * alguma adaptação antes do código do cliente poder usá-lo
 */
class Exemplo {
public:
	string RequisicaoEspecifica() {
		return "olpmexE od ocificepse otnematropmoC";
	}
};

// O Adapter torna a interface do Exemplo compatível com a interface do Target
class Adapter : public Target {
private:
	Exemplo *exemplo_;

public:
	Adapter(Exemplo *exemplo) : exemplo_(exemplo) {}

	string Requisicao() override {
		string to_reverse = this->exemplo_->RequisicaoEspecifica();
		reverse(to_reverse.begin(), to_reverse.end());

		return "Adapter: (TRADUZIDO) " + to_reverse;
	}
};

// O código cliente suporta todas as classes que seguem a interface Target
void ClientCode(Target *target) {
	cout << target->Requisicao() << endl;
};

int main() {
	cout << "Cliente: Eu posso trabalhar muito bem com os objetos Target:\n";

	Target *target = new Target;
	ClientCode(target);

	cout << endl;
	Exemplo *exemplo = new Exemplo;

	cout << "Cliente: A classe Exemplo tem uma interface estranha. Veja, eu não entendo\n";
	cout << "Exemplo: " << exemplo->RequisicaoEspecifica() << endl << endl;

	cout << "Cliente: Mas posso trabalhar com ele através do Adaptador:\n";
	Adapter *adapter = new Adapter(exemplo);
	ClientCode(adapter);

	delete target;
	delete exemplo;
	delete adapter;

	return EXIT_SUCCESS;
}