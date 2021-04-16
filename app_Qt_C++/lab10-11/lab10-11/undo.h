#pragma once
#include "Disciplina.h"
#include "Repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Disciplina d_adaugata;
	REPO& repo;
public:
	UndoAdauga(REPO& rep, const Disciplina d) : repo{ rep }, d_adaugata{ d } {}
	void doUndo() override;
};

class UndoStergere : public ActiuneUndo {
	Disciplina d_stearsa;
	REPO& repo;
public:

	UndoStergere(REPO& rep, const Disciplina d) : repo{ rep }, d_stearsa{ d } {}
	void doUndo() override;
};

class UndoMod : public ActiuneUndo {
	Disciplina d1, d2;
	REPO& repo;
public:

	UndoMod(REPO& rep, const Disciplina d1, const Disciplina d2) : repo{ rep }, d1{ d1 }, d2{ d2 } {}
	void doUndo() override;
};

class UndoAddContract : public ActiuneUndo {
	string nume;
	Contract& cont;
public:

	UndoAddContract(Contract& cont, string nume) : cont{ cont }, nume{ nume } {}
	void doUndo() override;
};
